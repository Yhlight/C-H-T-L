#pragma once

#include "ConfigurationSystem.h"
#include "ConfigurableLexer.h"
#include "antlr4-runtime.h"
#include <memory>
#include <functional>

namespace chtl {
namespace config {

/**
 * 可配置的Parser适配器
 * 在DISABLE_NAME_GROUP = false时，支持动态关键字解析
 */
class ConfigurableParser {
public:
    ConfigurableParser(antlr4::Parser* baseParser);
    ~ConfigurableParser() = default;
    
    /**
     * 配置Parser使用自定义关键字
     */
    void configure();
    
    /**
     * 检查当前Token是否匹配指定的关键字类型
     */
    bool matchKeyword(const std::string& keywordType);
    
    /**
     * 消费并匹配指定的关键字类型
     */
    bool consumeKeyword(const std::string& keywordType);
    
    /**
     * 获取当前Token的文本
     */
    std::string getCurrentTokenText() const;
    
    /**
     * 检查当前Token是否是配置的关键字
     */
    bool isCurrentTokenConfiguredKeyword() const;
    
    /**
     * 获取基础Parser
     */
    antlr4::Parser* getBaseParser() { return parser; }
    
private:
    antlr4::Parser* parser;
    ConfigurationSystem& config;
};

/**
 * ANTLR Parser的包装器，支持配置驱动的关键字
 */
template<typename BaseParser>
class ConfigurableParserWrapper : public BaseParser {
public:
    template<typename... Args>
    ConfigurableParserWrapper(Args&&... args)
        : BaseParser(std::forward<Args>(args)...)
        , adapter(this) {
        adapter.configure();
    }
    
    /**
     * 重载match方法以支持动态关键字
     */
    antlr4::Token* match(size_t ttype) override {
        if (ConfigurationSystem::getInstance().isNameGroupDisabled()) {
            // 使用原生Parser行为
            return BaseParser::match(ttype);
        }
        
        // 检查是否是配置的关键字Token类型
        if (isConfiguredKeywordToken(ttype)) {
            return matchConfiguredKeyword(ttype);
        }
        
        return BaseParser::match(ttype);
    }
    
protected:
    /**
     * 检查Token类型是否是可配置的关键字
     */
    bool isConfiguredKeywordToken(size_t ttype) const;
    
    /**
     * 匹配配置的关键字
     */
    antlr4::Token* matchConfiguredKeyword(size_t expectedType);
    
private:
    ConfigurableParser adapter;
};

/**
 * Parser规则重写器
 * 用于在运行时动态修改Parser规则以支持自定义关键字
 */
class ParserRuleRewriter {
public:
    using RuleFunction = std::function<void(antlr4::Parser*)>;
    
    /**
     * 注册规则重写函数
     */
    static void registerRuleRewriter(const std::string& ruleName, RuleFunction rewriter);
    
    /**
     * 执行规则重写
     */
    static void rewriteRule(const std::string& ruleName, antlr4::Parser* parser);
    
    /**
     * 清除所有重写器
     */
    static void clearRewriters();
    
private:
    static std::unordered_map<std::string, RuleFunction> rewriters;
};

/**
 * 配置感知的解析上下文
 * 提供了访问配置系统的便捷方法
 */
class ConfigurableParserContext {
public:
    ConfigurableParserContext(antlr4::Parser* parser)
        : parser(parser)
        , config(ConfigurationSystem::getInstance()) {}
    
    /**
     * 检查文本是否匹配任何配置的关键字变体
     */
    bool matchesAnyKeywordVariant(const std::string& text, const std::string& keywordType) const;
    
    /**
     * 获取所有可能的关键字变体
     */
    std::vector<std::string> getKeywordVariants(const std::string& keywordType) const;
    
    /**
     * 创建错误消息，包含所有可能的关键字变体
     */
    std::string createExpectedKeywordMessage(const std::string& keywordType) const;
    
private:
    antlr4::Parser* parser;
    ConfigurationSystem& config;
};

/**
 * 用于语法规则的辅助宏
 * 使得在语法文件中更容易使用配置驱动的关键字
 */
#define MATCH_CONFIGURED_KEYWORD(keywordType) \
    (ConfigurationSystem::getInstance().isNameGroupDisabled() ? \
     match(getTokenType(keywordType)) : \
     matchConfiguredKeyword(keywordType))

#define CHECK_CONFIGURED_KEYWORD(keywordType) \
    (ConfigurationSystem::getInstance().isNameGroupDisabled() ? \
     (getCurrentToken()->getType() == getTokenType(keywordType)) : \
     isCurrentTokenMatchingKeyword(keywordType))

} // namespace config
} // namespace chtl