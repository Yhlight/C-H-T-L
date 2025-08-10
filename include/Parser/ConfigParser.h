#ifndef CHTL_CONFIG_PARSER_H
#define CHTL_CONFIG_PARSER_H

#include "Parser/BasicParser.h"
#include "Node/Config.h"
#include <unordered_set>

namespace chtl {

class ConfigLexer;
class Config;

// 配置格式枚举
enum class ConfigFormat {
    CHTL,    // 默认CHTL格式
    JSON,
    YAML,
    INI,
    TOML,
    XML
};

/**
 * 配置解析器
 * 专门用于解析 [Configuration] 块中的各种配置格式
 */
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
    
    // 当前格式
    ConfigFormat currentFormat_;
    
    // 当前配置节点
    std::shared_ptr<Config> currentConfig_;
    
    // 辅助方法
    void parseConfigContent(std::shared_ptr<Config> configNode);
    void parseConfigGroup(std::shared_ptr<Config> configNode, const std::string& groupName);
    void parseConfigItem(std::shared_ptr<Config> configNode, const std::string& groupPrefix = "");
    std::string parseConfigValue();
    void skipToNextStatement();
    
    // 格式检测
    ConfigFormat detectFormat();
    
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
    
    // 导出功能
    void exportConfig(std::shared_ptr<Config> configNode, ConfigFormat format, const std::string& filename);
    
protected:
    // 覆盖基类初始化方法
    void initializeParser() override;
    void finalizeParser() override;
    
private:
    // 解析辅助方法
    bool parseConfigurationBlock();
    bool parseConfigKey();

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

    // 导出方法
    std::string exportToJSON(std::shared_ptr<Config> configNode);
    std::string exportToYAML(std::shared_ptr<Config> configNode);
    std::string exportToINI(std::shared_ptr<Config> configNode);
    std::string exportToTOML(std::shared_ptr<Config> configNode);
    std::string exportToXML(std::shared_ptr<Config> configNode);
    std::string exportToCHTL(std::shared_ptr<Config> configNode);
};

} // namespace chtl

#endif // CHTL_CONFIG_PARSER_H