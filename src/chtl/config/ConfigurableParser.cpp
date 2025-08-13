#include "ConfigurableParser.h"
#include <sstream>

namespace chtl {
namespace config {

// 静态成员定义
std::unordered_map<std::string, ParserRuleRewriter::RuleFunction> ParserRuleRewriter::rewriters;

// ConfigurableParser 实现

ConfigurableParser::ConfigurableParser(antlr4::Parser* baseParser)
    : parser(baseParser)
    , config(ConfigurationSystem::getInstance()) {
}

void ConfigurableParser::configure() {
    // 配置工作主要在Lexer端完成
    // Parser端主要是提供便捷的匹配方法
}

bool ConfigurableParser::matchKeyword(const std::string& keywordType) {
    if (config.isNameGroupDisabled()) {
        // 使用默认行为
        return false;  // 让调用者使用原生match
    }
    
    antlr4::Token* currentToken = parser->getCurrentToken();
    if (!currentToken) {
        return false;
    }
    
    std::string tokenText = currentToken->getText();
    return config.isKeyword(tokenText, keywordType);
}

bool ConfigurableParser::consumeKeyword(const std::string& keywordType) {
    if (matchKeyword(keywordType)) {
        parser->consume();  // 消费当前Token
        return true;
    }
    return false;
}

std::string ConfigurableParser::getCurrentTokenText() const {
    antlr4::Token* currentToken = parser->getCurrentToken();
    return currentToken ? currentToken->getText() : "";
}

bool ConfigurableParser::isCurrentTokenConfiguredKeyword() const {
    antlr4::Token* currentToken = parser->getCurrentToken();
    if (!currentToken) {
        return false;
    }
    
    // 检查是否是任何配置的关键字
    const auto& registry = KeywordRegistry::getInstance();
    for (const auto& info : registry.getAllKeywords()) {
        size_t tokenType;
        ConfigurableLexer tempLexer(nullptr);  // 临时对象用于检查
        if (tempLexer.isConfiguredKeyword(currentToken->getText(), tokenType)) {
            return true;
        }
    }
    
    return false;
}

// ConfigurableParserWrapper 模板方法实现

template<typename BaseParser>
bool ConfigurableParserWrapper<BaseParser>::isConfiguredKeywordToken(size_t ttype) const {
    const auto& registry = KeywordRegistry::getInstance();
    return registry.getKeywordByTokenType(ttype) != nullptr;
}

template<typename BaseParser>
antlr4::Token* ConfigurableParserWrapper<BaseParser>::matchConfiguredKeyword(size_t expectedType) {
    antlr4::Token* currentToken = this->getCurrentToken();
    if (!currentToken) {
        throw antlr4::RecognitionException("Unexpected end of input", 
                                          this, this->getInputStream(), this->getContext());
    }
    
    // 获取期望的关键字信息
    const auto& registry = KeywordRegistry::getInstance();
    const KeywordInfo* keywordInfo = registry.getKeywordByTokenType(expectedType);
    
    if (!keywordInfo) {
        // 不是配置的关键字，使用默认行为
        return BaseParser::match(expectedType);
    }
    
    // 检查当前Token是否匹配任何配置的关键字变体
    std::string tokenText = currentToken->getText();
    if (ConfigurationSystem::getInstance().isKeyword(tokenText, keywordInfo->configKey)) {
        // 匹配成功，消费Token
        this->consume();
        return currentToken;
    }
    
    // 创建错误消息
    ConfigurableParserContext ctx(this);
    std::string expectedMsg = ctx.createExpectedKeywordMessage(keywordInfo->configKey);
    
    throw antlr4::RecognitionException(
        "Expected " + expectedMsg + " but found '" + tokenText + "'",
        this, this->getInputStream(), this->getContext()
    );
}

// ParserRuleRewriter 实现

void ParserRuleRewriter::registerRuleRewriter(const std::string& ruleName, RuleFunction rewriter) {
    rewriters[ruleName] = rewriter;
}

void ParserRuleRewriter::rewriteRule(const std::string& ruleName, antlr4::Parser* parser) {
    auto it = rewriters.find(ruleName);
    if (it != rewriters.end()) {
        it->second(parser);
    }
}

void ParserRuleRewriter::clearRewriters() {
    rewriters.clear();
}

// ConfigurableParserContext 实现

bool ConfigurableParserContext::matchesAnyKeywordVariant(
    const std::string& text, const std::string& keywordType) const {
    
    if (config.isNameGroupDisabled()) {
        // 使用默认关键字
        return text == config.getCanonicalKeyword(keywordType);
    }
    
    // 检查所有变体
    return config.isKeyword(text, keywordType);
}

std::vector<std::string> ConfigurableParserContext::getKeywordVariants(
    const std::string& keywordType) const {
    
    if (config.isNameGroupDisabled()) {
        // 返回默认关键字
        return {config.getCanonicalKeyword(keywordType)};
    }
    
    return config.getNameGroup().getAllKeywordVariants(keywordType);
}

std::string ConfigurableParserContext::createExpectedKeywordMessage(
    const std::string& keywordType) const {
    
    auto variants = getKeywordVariants(keywordType);
    
    if (variants.empty()) {
        return keywordType;
    }
    
    if (variants.size() == 1) {
        return "'" + variants[0] + "'";
    }
    
    // 多个变体
    std::stringstream ss;
    ss << "one of ";
    for (size_t i = 0; i < variants.size(); ++i) {
        if (i > 0) {
            if (i == variants.size() - 1) {
                ss << " or ";
            } else {
                ss << ", ";
            }
        }
        ss << "'" << variants[i] << "'";
    }
    
    return ss.str();
}

} // namespace config
} // namespace chtl