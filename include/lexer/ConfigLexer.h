#ifndef CHTL_CONFIG_LEXER_H
#define CHTL_CONFIG_LEXER_H

#include "lexer/BasicLexer.h"
#include <unordered_map>
#include <unordered_set>

namespace chtl {

// 配置文件词法分析器
// 用于解析CHTL的[Configuration]块
class ConfigLexer : public BasicLexer {
private:
    // 配置项
    std::unordered_map<std::string, std::string> configItems_;
    std::unordered_map<std::string, std::vector<std::string>> arrayConfigItems_;
    
    // 当前解析状态
    enum class ParseState {
        INITIAL,
        IN_CONFIGURATION,
        IN_NAME_BLOCK,
        PARSING_KEY,
        PARSING_VALUE,
        PARSING_ARRAY
    };
    
    ParseState parseState_;
    std::string currentKey_;
    std::string currentValue_;
    std::vector<std::string> currentArray_;
    
public:
    ConfigLexer();
    virtual ~ConfigLexer() = default;
    
    // 解析配置
    bool parseConfiguration(const std::string& configText);
    bool parseConfigurationFile(const std::string& filename);
    
    // 获取配置值
    std::string getConfigValue(const std::string& key, const std::string& defaultValue = "") const;
    std::vector<std::string> getConfigArray(const std::string& key) const;
    bool hasConfig(const std::string& key) const;
    
    // 获取所有配置
    const std::unordered_map<std::string, std::string>& getAllConfigs() const { return configItems_; }
    const std::unordered_map<std::string, std::vector<std::string>>& getAllArrayConfigs() const { return arrayConfigItems_; }
    
    // 应用配置到GlobalMap（如果需要）
    void applyKeywordAliases();
    
    // 调试输出
    void printConfig() const;
    
protected:
    // 实现基类的纯虚函数
    std::shared_ptr<BasicState> createInitialState() override;
    std::shared_ptr<BasicContext> createInitialContext() override;
    
private:
    // 解析辅助方法
    Token parseConfigToken();
    void processConfigLine(const std::string& line);
    bool isValidConfigKey(const std::string& key) const;
    std::string trimWhitespace(const std::string& str) const;
    std::vector<std::string> parseArrayValue(const std::string& value) const;
    
    // 预定义的配置键
    static const std::unordered_set<std::string> VALID_CONFIG_KEYS;
    static const std::unordered_set<std::string> ARRAY_CONFIG_KEYS;
};

// 预定义的配置键
inline const std::unordered_set<std::string> ConfigLexer::VALID_CONFIG_KEYS = {
    // 通用配置
    "INDEX_INITIAL_COUNT",
    "DISABLE_NAME_GROUP",
    "DEBUG_MODE",
    
    // Name配置块中的键
    "CUSTOM_STYLE",
    "CUSTOM_ELEMENT", 
    "CUSTOM_VAR",
    "TEMPLATE_STYLE",
    "TEMPLATE_ELEMENT",
    "TEMPLATE_VAR",
    "ORIGIN_HTML",
    "ORIGIN_STYLE",
    "ORIGIN_JAVASCRIPT",
    "KEYWORD_INHERIT",
    "KEYWORD_DELETE",
    "KEYWORD_INSERT",
    "KEYWORD_AFTER",
    "KEYWORD_BEFORE",
    "KEYWORD_REPLACE",
    "KEYWORD_ATTOP",
    "KEYWORD_ATBOTTOM",
    "KEYWORD_FROM",
    "KEYWORD_AS",
    "KEYWORD_EXCEPT",
    "KEYWORD_TEXT",
    "KEYWORD_STYLE",
    "KEYWORD_CUSTOM",
    "KEYWORD_TEMPLATE",
    "KEYWORD_ORIGIN",
    "KEYWORD_IMPORT",
    "KEYWORD_NAMESPACE",
    
    // 其他配置
    "OPTION_COUNT"
};

// 支持数组值的配置键
inline const std::unordered_set<std::string> ConfigLexer::ARRAY_CONFIG_KEYS = {
    "CUSTOM_STYLE",
    "CUSTOM_ELEMENT",
    "CUSTOM_VAR",
    "TEMPLATE_STYLE",
    "TEMPLATE_ELEMENT",
    "TEMPLATE_VAR",
    "ORIGIN_HTML",
    "ORIGIN_STYLE",
    "ORIGIN_JAVASCRIPT"
};

} // namespace chtl

#endif // CHTL_CONFIG_LEXER_H