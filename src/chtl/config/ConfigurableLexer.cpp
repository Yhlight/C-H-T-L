#include "ConfigurableLexer.h"
#include "../generated/CHTLLexer.h"  // 假设这是ANTLR生成的Lexer

namespace chtl {
namespace config {

// ConfigurableLexer 实现

ConfigurableLexer::ConfigurableLexer(antlr4::Lexer* baseLexer)
    : lexer(baseLexer)
    , config(ConfigurationSystem::getInstance()) {
}

void ConfigurableLexer::configure() {
    if (config.isNameGroupDisabled()) {
        return;  // 使用默认行为
    }
    
    initializeKeywordMappings();
}

void ConfigurableLexer::initializeKeywordMappings() {
    keywordToTokenType.clear();
    tokenTypeToKeywordType.clear();
    
    const auto& nameGroup = config.getNameGroup();
    const auto& registry = KeywordRegistry::getInstance();
    
    // 遍历所有注册的关键字
    for (const auto& info : registry.getAllKeywords()) {
        if (info.isArray) {
            // 处理数组类型（如CUSTOM_STYLE）
            auto variants = nameGroup.getAllKeywordVariants(info.configKey);
            for (const auto& variant : variants) {
                keywordToTokenType[variant] = info.defaultTokenType;
                tokenTypeToKeywordType[info.defaultTokenType] = info.configKey;
            }
        } else {
            // 处理单个关键字
            std::string keyword = config.getCanonicalKeyword(info.configKey);
            if (!keyword.empty()) {
                keywordToTokenType[keyword] = info.defaultTokenType;
                tokenTypeToKeywordType[info.defaultTokenType] = info.configKey;
            }
        }
    }
}

std::unique_ptr<antlr4::Token> ConfigurableLexer::nextToken() {
    auto token = lexer->nextToken();
    
    if (!token || config.isNameGroupDisabled()) {
        return token;
    }
    
    // 检查是否需要替换关键字
    std::string text = token->getText();
    size_t newTokenType;
    
    if (isConfiguredKeyword(text, newTokenType)) {
        return createCustomToken(token.get(), newTokenType, text);
    }
    
    return token;
}

bool ConfigurableLexer::isConfiguredKeyword(const std::string& text, size_t& tokenType) const {
    auto it = keywordToTokenType.find(text);
    if (it != keywordToTokenType.end()) {
        tokenType = it->second;
        return true;
    }
    return false;
}

std::unique_ptr<antlr4::Token> ConfigurableLexer::createCustomToken(
    antlr4::Token* originalToken,
    size_t newType,
    const std::string& newText) {
    
    // 创建一个新的Token，保持原始Token的位置信息
    class CustomToken : public antlr4::CommonToken {
    public:
        CustomToken(antlr4::Token* original, size_t type, const std::string& text)
            : antlr4::CommonToken(type) {
            setText(text);
            setLine(original->getLine());
            setCharPositionInLine(original->getCharPositionInLine());
            setStartIndex(original->getStartIndex());
            setStopIndex(original->getStopIndex());
            setTokenIndex(original->getTokenIndex());
            setChannel(original->getChannel());
        }
    };
    
    return std::make_unique<CustomToken>(originalToken, newType, newText);
}

// KeywordRegistry 实现

KeywordRegistry& KeywordRegistry::getInstance() {
    static KeywordRegistry instance;
    return instance;
}

KeywordRegistry::KeywordRegistry() {
    // 注册所有关键字
    // 注意：这里的Token类型值需要与ANTLR生成的Lexer中的值对应
    
    // 样式相关
    registerKeyword(KeywordInfo(KeywordType::CUSTOM_STYLE, "CUSTOM_STYLE", 
        CHTLLexer::AT_STYLE, true));  // 支持数组
    registerKeyword(KeywordInfo(KeywordType::CUSTOM_ELEMENT, "CUSTOM_ELEMENT", 
        CHTLLexer::AT_ELEMENT));
    registerKeyword(KeywordInfo(KeywordType::CUSTOM_VAR, "CUSTOM_VAR", 
        CHTLLexer::AT_VAR));
    
    registerKeyword(KeywordInfo(KeywordType::TEMPLATE_STYLE, "TEMPLATE_STYLE", 
        CHTLLexer::AT_STYLE));
    registerKeyword(KeywordInfo(KeywordType::TEMPLATE_ELEMENT, "TEMPLATE_ELEMENT", 
        CHTLLexer::AT_ELEMENT));
    registerKeyword(KeywordInfo(KeywordType::TEMPLATE_VAR, "TEMPLATE_VAR", 
        CHTLLexer::AT_VAR));
    
    // 原始嵌入
    registerKeyword(KeywordInfo(KeywordType::ORIGIN_HTML, "ORIGIN_HTML", 
        CHTLLexer::AT_HTML));
    registerKeyword(KeywordInfo(KeywordType::ORIGIN_STYLE, "ORIGIN_STYLE", 
        CHTLLexer::AT_STYLE));
    registerKeyword(KeywordInfo(KeywordType::ORIGIN_JAVASCRIPT, "ORIGIN_JAVASCRIPT", 
        CHTLLexer::AT_JAVASCRIPT));
    
    // 导入
    registerKeyword(KeywordInfo(KeywordType::IMPORT_HTML, "IMPORT_HTML", 
        CHTLLexer::AT_HTML));
    registerKeyword(KeywordInfo(KeywordType::IMPORT_STYLE, "IMPORT_STYLE", 
        CHTLLexer::AT_STYLE));
    registerKeyword(KeywordInfo(KeywordType::IMPORT_JAVASCRIPT, "IMPORT_JAVASCRIPT", 
        CHTLLexer::AT_JAVASCRIPT));
    registerKeyword(KeywordInfo(KeywordType::IMPORT_CHTL, "IMPORT_CHTL", 
        CHTLLexer::AT_CHTL));
    registerKeyword(KeywordInfo(KeywordType::IMPORT_CJMOD, "IMPORT_CJMOD", 
        CHTLLexer::AT_CJMOD));
    
    // 操作关键字
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_INHERIT, "KEYWORD_INHERIT", 
        CHTLLexer::INHERIT));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_DELETE, "KEYWORD_DELETE", 
        CHTLLexer::DELETE));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_INSERT, "KEYWORD_INSERT", 
        CHTLLexer::INSERT));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_AFTER, "KEYWORD_AFTER", 
        CHTLLexer::AFTER));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_BEFORE, "KEYWORD_BEFORE", 
        CHTLLexer::BEFORE));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_REPLACE, "KEYWORD_REPLACE", 
        CHTLLexer::REPLACE));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_AT_TOP, "KEYWORD_ATTOP", 
        CHTLLexer::AT_TOP));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_AT_BOTTOM, "KEYWORD_ATBOTTOM", 
        CHTLLexer::AT_BOTTOM));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_FROM, "KEYWORD_FROM", 
        CHTLLexer::FROM));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_AS, "KEYWORD_AS", 
        CHTLLexer::AS));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_EXCEPT, "KEYWORD_EXCEPT", 
        CHTLLexer::EXCEPT));
    
    // 节点关键字
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_TEXT, "KEYWORD_TEXT", 
        CHTLLexer::TEXT));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_STYLE, "KEYWORD_STYLE", 
        CHTLLexer::STYLE));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_SCRIPT, "KEYWORD_SCRIPT", 
        CHTLLexer::SCRIPT));
    
    // 声明关键字
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_CUSTOM, "KEYWORD_CUSTOM", 
        CHTLLexer::LBRACKET_CUSTOM));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_TEMPLATE, "KEYWORD_TEMPLATE", 
        CHTLLexer::LBRACKET_TEMPLATE));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_ORIGIN, "KEYWORD_ORIGIN", 
        CHTLLexer::LBRACKET_ORIGIN));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_IMPORT, "KEYWORD_IMPORT", 
        CHTLLexer::LBRACKET_IMPORT));
    registerKeyword(KeywordInfo(KeywordType::KEYWORD_NAMESPACE, "KEYWORD_NAMESPACE", 
        CHTLLexer::LBRACKET_NAMESPACE));
}

void KeywordRegistry::registerKeyword(const KeywordInfo& info) {
    size_t index = keywords.size();
    keywords.push_back(info);
    configKeyToIndex[info.configKey] = index;
    tokenTypeToIndex[info.defaultTokenType] = index;
}

const KeywordInfo* KeywordRegistry::getKeywordByConfigKey(const std::string& configKey) const {
    auto it = configKeyToIndex.find(configKey);
    if (it != configKeyToIndex.end()) {
        return &keywords[it->second];
    }
    return nullptr;
}

const KeywordInfo* KeywordRegistry::getKeywordByTokenType(size_t tokenType) const {
    auto it = tokenTypeToIndex.find(tokenType);
    if (it != tokenTypeToIndex.end()) {
        return &keywords[it->second];
    }
    return nullptr;
}

} // namespace config
} // namespace chtl