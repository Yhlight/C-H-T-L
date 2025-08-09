#ifndef CHTL_CONFIG_PARSER_H
#define CHTL_CONFIG_PARSER_H

#include "Parser/BasicParser.h"
#include "Node/Config.h"
#include <unordered_set>

namespace chtl {

// 配置解析器 - 专门解析[Configuration]块
class ConfigParser : public BasicParser {
private:
    // 配置解析状态
    enum class ConfigParseState {
        INITIAL,
        EXPECT_CONFIGURATION,
        EXPECT_NAME_OR_BRACE,
        IN_CONFIG_BLOCK,
        PARSING_KEY,
        PARSING_VALUE,
        PARSING_ARRAY,
        COMPLETE
    };
    
    ConfigParseState configState_;
    std::shared_ptr<Config> currentConfig_;
    std::string currentKey_;
    std::vector<std::string> currentArray_;
    
    // 有效的配置键
    static const std::unordered_set<std::string> VALID_CONFIG_KEYS;
    static const std::unordered_set<std::string> ARRAY_CONFIG_KEYS;
    
public:
    ConfigParser();
    virtual ~ConfigParser() = default;
    
    // 覆盖基类方法
    std::shared_ptr<Node> parse() override;
    
    // 配置特定的解析方法
    std::shared_ptr<Config> parseConfiguration();
    std::shared_ptr<Config> parseConfigurationFromFile(const std::string& filename);
    std::shared_ptr<Config> parseConfigurationFromString(const std::string& content);
    
    // 获取最后解析的配置
    std::shared_ptr<Config> getLastConfig() const { return currentConfig_; }
    
protected:
    // 覆盖基类初始化方法
    void initializeParser() override;
    void finalizeParser() override;
    
private:
    // 解析辅助方法
    bool parseConfigurationBlock();
    bool parseConfigKey();
    bool parseConfigValue();
    bool parseConfigArray();
    bool parseStringValue(std::string& result);
    bool parseArrayElement(std::string& result);
    
    // 验证方法
    bool isValidConfigKey(const std::string& key) const;
    bool isArrayConfigKey(const std::string& key) const;
    bool validateConfigValue(const std::string& key, const std::string& value);
    bool validateArrayValues(const std::string& key, const std::vector<std::string>& values);
    
    // 特殊配置处理
    void applySpecialConfigurations();
    void applyKeywordAliases();
    void applyImportPaths();
};

} // namespace chtl

#endif // CHTL_CONFIG_PARSER_H