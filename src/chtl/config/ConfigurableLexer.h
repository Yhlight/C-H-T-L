#pragma once

#include "ConfigurationSystem.h"
#include "antlr4-runtime.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace chtl {
namespace config {

/**
 * 可配置的Lexer适配器
 * 在DISABLE_NAME_GROUP = false时，动态替换关键字
 */
class ConfigurableLexer {
public:
    ConfigurableLexer(antlr4::Lexer* baseLexer);
    ~ConfigurableLexer() = default;
    
    /**
     * 配置Lexer使用自定义关键字
     */
    void configure();
    
    /**
     * 获取下一个Token
     * 如果启用了Name组，会动态替换关键字
     */
    std::unique_ptr<antlr4::Token> nextToken();
    
    /**
     * 检查Token是否匹配配置的关键字
     */
    bool isConfiguredKeyword(const std::string& text, size_t& tokenType) const;
    
    /**
     * 获取所有配置的关键字映射
     */
    const std::unordered_map<std::string, size_t>& getKeywordMap() const { 
        return keywordToTokenType; 
    }
    
private:
    antlr4::Lexer* lexer;
    ConfigurationSystem& config;
    
    // 关键字到Token类型的映射
    std::unordered_map<std::string, size_t> keywordToTokenType;
    
    // Token类型到关键字类型的映射
    std::unordered_map<size_t, std::string> tokenTypeToKeywordType;
    
    // 初始化关键字映射
    void initializeKeywordMappings();
    
    // 创建自定义Token
    std::unique_ptr<antlr4::Token> createCustomToken(
        antlr4::Token* originalToken,
        size_t newType,
        const std::string& newText
    );
};

/**
 * ANTLR Lexer的包装器，支持配置驱动的关键字
 */
template<typename BaseLexer>
class ConfigurableLexerWrapper : public BaseLexer {
public:
    template<typename... Args>
    ConfigurableLexerWrapper(Args&&... args) 
        : BaseLexer(std::forward<Args>(args)...)
        , adapter(this) {
        adapter.configure();
    }
    
    std::unique_ptr<antlr4::Token> nextToken() override {
        if (ConfigurationSystem::getInstance().isNameGroupDisabled()) {
            // 使用原生Lexer行为
            return BaseLexer::nextToken();
        }
        
        // 使用配置驱动的行为
        return adapter.nextToken();
    }
    
private:
    ConfigurableLexer adapter;
};

/**
 * 关键字类型枚举
 */
enum class KeywordType {
    // 样式相关
    CUSTOM_STYLE,
    CUSTOM_ELEMENT,
    CUSTOM_VAR,
    TEMPLATE_STYLE,
    TEMPLATE_ELEMENT,
    TEMPLATE_VAR,
    
    // 原始嵌入
    ORIGIN_HTML,
    ORIGIN_STYLE,
    ORIGIN_JAVASCRIPT,
    
    // 导入
    IMPORT_HTML,
    IMPORT_STYLE,
    IMPORT_JAVASCRIPT,
    IMPORT_CHTL,
    IMPORT_CJMOD,
    
    // 操作关键字
    KEYWORD_INHERIT,
    KEYWORD_DELETE,
    KEYWORD_INSERT,
    KEYWORD_AFTER,
    KEYWORD_BEFORE,
    KEYWORD_REPLACE,
    KEYWORD_AT_TOP,
    KEYWORD_AT_BOTTOM,
    KEYWORD_FROM,
    KEYWORD_AS,
    KEYWORD_EXCEPT,
    
    // 节点关键字
    KEYWORD_TEXT,
    KEYWORD_STYLE,
    KEYWORD_SCRIPT,
    
    // 声明关键字
    KEYWORD_CUSTOM,
    KEYWORD_TEMPLATE,
    KEYWORD_ORIGIN,
    KEYWORD_IMPORT,
    KEYWORD_NAMESPACE
};

/**
 * 关键字信息结构
 */
struct KeywordInfo {
    KeywordType type;
    std::string configKey;
    size_t defaultTokenType;
    bool isArray;  // 是否支持多个变体
    
    KeywordInfo(KeywordType t, const std::string& key, size_t tokenType, bool arr = false)
        : type(t), configKey(key), defaultTokenType(tokenType), isArray(arr) {}
};

/**
 * 关键字注册表
 */
class KeywordRegistry {
public:
    static KeywordRegistry& getInstance();
    
    // 注册关键字
    void registerKeyword(const KeywordInfo& info);
    
    // 获取所有关键字
    const std::vector<KeywordInfo>& getAllKeywords() const { return keywords; }
    
    // 根据配置键获取关键字信息
    const KeywordInfo* getKeywordByConfigKey(const std::string& configKey) const;
    
    // 根据Token类型获取关键字信息
    const KeywordInfo* getKeywordByTokenType(size_t tokenType) const;
    
private:
    KeywordRegistry();
    std::vector<KeywordInfo> keywords;
    std::unordered_map<std::string, size_t> configKeyToIndex;
    std::unordered_map<size_t, size_t> tokenTypeToIndex;
};

} // namespace config
} // namespace chtl