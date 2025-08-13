#include "ScannerParserIntegration.h"
#include "../config/ConfigurationSystem.h"
#include "../config/ConfigurableLexer.h"
#include "../config/ConfigurableParser.h"
#include <sstream>

namespace chtl {
namespace scanner {

// IntegrationErrorListener 实现

void IntegrationErrorListener::syntaxError(
    antlr4::Recognizer* recognizer,
    antlr4::Token* offendingSymbol,
    size_t line,
    size_t charPositionInLine,
    const std::string& msg,
    std::exception_ptr e) {
    
    std::stringstream ss;
    ss << "Line " << line << ":" << charPositionInLine << " - " << msg;
    
    if (offendingSymbol != nullptr) {
        ss << " (at '" << offendingSymbol->getText() << "')";
    }
    
    errors.push_back(ss.str());
}

// ScannerParserIntegration 实现

ScannerParserIntegration::ScannerParserIntegration(std::shared_ptr<CHTLContext> context)
    : context(context) {
    errorListener = std::make_unique<IntegrationErrorListener>();
}

ScannerParserIntegration::~ScannerParserIntegration() = default;

ParseResult ScannerParserIntegration::parse(
    const std::string& source, 
    const std::string& configPath) {
    
    // 如果提供了配置文件，加载它
    if (!configPath.empty() && useConfiguration) {
        auto& configSystem = config::ConfigurationSystem::getInstance();
        if (!configSystem.loadConfigurationFromFile(configPath)) {
            ParseResult result;
            result.success = false;
            result.errorMessage = "Failed to load configuration file: " + configPath;
            return result;
        }
    }
    
    // 创建Scanner
    CHTLUnifiedScanner scanner(source, context);
    
    // 配置Scanner
    ScannerConfig scannerConfig;
    scannerConfig.enableOptimization = true;
    scannerConfig.enableValidation = true;
    scanner.setConfig(scannerConfig);
    
    // 执行扫描
    scanner.scan();
    
    // 解析扫描结果
    return parseFromScanner(scanner);
}

ParseResult ScannerParserIntegration::parseFromScanner(CHTLUnifiedScanner& scanner) {
    ParseResult result;
    result.success = true;
    
    try {
        // 获取Scanner的tokens
        auto tokens = scanner.getTokens();
        
        // 合并连续的同语言片段
        auto fragments = mergeFragments(tokens, scanner.getSource());
        result.fragments = fragments;
        
        // 按语言分组
        auto languageGroups = groupFragmentsByLanguage(fragments);
        
        // 解析各语言片段
        if (languageGroups.count(LanguageContext::CHTL) > 0) {
            result.chtlTree = parseCHTLFragments(languageGroups[LanguageContext::CHTL]);
        }
        
        if (languageGroups.count(LanguageContext::CSS) > 0) {
            result.cssTree = parseCSSFragments(languageGroups[LanguageContext::CSS]);
        }
        
        if (languageGroups.count(LanguageContext::JavaScript) > 0) {
            result.jsTree = parseJSFragments(languageGroups[LanguageContext::JavaScript]);
        }
        
        if (languageGroups.count(LanguageContext::CHTLJavaScript) > 0) {
            result.chtljsTree = parseCHTLJSFragments(languageGroups[LanguageContext::CHTLJavaScript]);
        }
        
        // 检查错误
        auto errorListener = static_cast<IntegrationErrorListener*>(this->errorListener.get());
        if (errorListener->hasErrors()) {
            result.success = false;
            std::stringstream ss;
            for (const auto& error : errorListener->getErrors()) {
                ss << error << "\n";
            }
            result.errorMessage = ss.str();
        }
        
    } catch (const std::exception& e) {
        result.success = false;
        result.errorMessage = std::string("Parser error: ") + e.what();
    }
    
    return result;
}

std::vector<ScanFragment> ScannerParserIntegration::mergeFragments(
    const std::vector<Token>& tokens,
    const std::string& source) {
    
    std::vector<ScanFragment> fragments;
    
    if (tokens.empty()) {
        return fragments;
    }
    
    // 初始化第一个片段
    ScanFragment currentFragment;
    currentFragment.token = tokens[0];
    currentFragment.language = tokens[0].context;
    currentFragment.startLine = tokens[0].line;
    currentFragment.startColumn = tokens[0].column;
    currentFragment.content = tokens[0].value;
    
    for (size_t i = 1; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        
        // 如果语言上下文改变，保存当前片段并开始新片段
        if (token.context != currentFragment.language ||
            token.type == TokenType::CHTL_BLOCK_START ||
            token.type == TokenType::CSS_BLOCK_START ||
            token.type == TokenType::JS_BLOCK_START) {
            
            // 保存当前片段
            currentFragment.endLine = tokens[i-1].line;
            currentFragment.endColumn = tokens[i-1].column + tokens[i-1].value.length();
            fragments.push_back(currentFragment);
            
            // 开始新片段
            currentFragment = ScanFragment();
            currentFragment.token = token;
            currentFragment.language = token.context;
            currentFragment.startLine = token.line;
            currentFragment.startColumn = token.column;
            currentFragment.content = token.value;
        } else {
            // 继续累积内容
            currentFragment.content += token.value;
        }
    }
    
    // 保存最后一个片段
    if (!tokens.empty()) {
        currentFragment.endLine = tokens.back().line;
        currentFragment.endColumn = tokens.back().column + tokens.back().value.length();
        fragments.push_back(currentFragment);
    }
    
    return fragments;
}

std::unordered_map<LanguageContext, std::vector<ScanFragment>> 
ScannerParserIntegration::groupFragmentsByLanguage(
    const std::vector<ScanFragment>& fragments) {
    
    std::unordered_map<LanguageContext, std::vector<ScanFragment>> groups;
    
    for (const auto& fragment : fragments) {
        groups[fragment.language].push_back(fragment);
    }
    
    return groups;
}

std::unique_ptr<antlr4::ANTLRInputStream> 
ScannerParserIntegration::createInputStream(
    const std::vector<ScanFragment>& fragments,
    LanguageContext targetLanguage) {
    
    std::stringstream ss;
    
    for (const auto& fragment : fragments) {
        if (fragment.language == targetLanguage) {
            ss << fragment.content;
        }
    }
    
    return std::make_unique<antlr4::ANTLRInputStream>(ss.str());
}

antlr4::tree::ParseTree* ScannerParserIntegration::parseCHTLFragments(
    const std::vector<ScanFragment>& fragments) {
    
    auto input = createInputStream(fragments, LanguageContext::CHTL);
    
    // 创建Lexer
    std::unique_ptr<antlr4::Lexer> lexer;
    if (useConfiguration && !config::ConfigurationSystem::getInstance().isNameGroupDisabled()) {
        // 使用可配置的Lexer
        lexer = std::make_unique<config::ConfigurableLexerWrapper<CHTLLexer>>(input.get());
    } else {
        // 使用标准Lexer
        lexer = std::make_unique<CHTLLexer>(input.get());
    }
    
    // 移除默认错误监听器，添加自定义的
    lexer->removeErrorListeners();
    lexer->addErrorListener(errorListener.get());
    
    // 创建Token流
    antlr4::CommonTokenStream tokens(lexer.get());
    
    // 创建Parser
    if (useConfiguration && !config::ConfigurationSystem::getInstance().isNameGroupDisabled()) {
        // 使用可配置的Parser
        chtlParser = std::make_unique<config::ConfigurableParserWrapper<CHTLParser>>(&tokens);
    } else {
        // 使用标准Parser
        chtlParser = std::make_unique<CHTLParser>(&tokens);
    }
    
    // 配置错误监听器
    chtlParser->removeErrorListeners();
    chtlParser->addErrorListener(errorListener.get());
    
    // 解析
    return chtlParser->compilationUnit();
}

antlr4::tree::ParseTree* ScannerParserIntegration::parseCSSFragments(
    const std::vector<ScanFragment>& fragments) {
    
    auto input = createInputStream(fragments, LanguageContext::CSS);
    
    // CSS不需要配置驱动，使用标准解析器
    CSSLexer lexer(input.get());
    lexer.removeErrorListeners();
    lexer.addErrorListener(errorListener.get());
    
    antlr4::CommonTokenStream tokens(&lexer);
    
    cssParser = std::make_unique<CSSParser>(&tokens);
    cssParser->removeErrorListeners();
    cssParser->addErrorListener(errorListener.get());
    
    return cssParser->stylesheet();
}

antlr4::tree::ParseTree* ScannerParserIntegration::parseJSFragments(
    const std::vector<ScanFragment>& fragments) {
    
    auto input = createInputStream(fragments, LanguageContext::JavaScript);
    
    JSLexer lexer(input.get());
    lexer.removeErrorListeners();
    lexer.addErrorListener(errorListener.get());
    
    antlr4::CommonTokenStream tokens(&lexer);
    
    jsParser = std::make_unique<JSParser>(&tokens);
    jsParser->removeErrorListeners();
    jsParser->addErrorListener(errorListener.get());
    
    return jsParser->program();
}

antlr4::tree::ParseTree* ScannerParserIntegration::parseCHTLJSFragments(
    const std::vector<ScanFragment>& fragments) {
    
    auto input = createInputStream(fragments, LanguageContext::CHTLJavaScript);
    
    CHTLJSLexer lexer(input.get());
    lexer.removeErrorListeners();
    lexer.addErrorListener(errorListener.get());
    
    antlr4::CommonTokenStream tokens(&lexer);
    
    chtljsParser = std::make_unique<CHTLJSParser>(&tokens);
    chtljsParser->removeErrorListeners();
    chtljsParser->addErrorListener(errorListener.get());
    
    return chtljsParser->program();
}

} // namespace scanner
} // namespace chtl