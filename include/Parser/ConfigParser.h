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
public:
    // 配置格式
    enum class ConfigFormat {
        JSON,
        YAML,
        INI,
        TOML,
        XML,
        CHTL  // 默认CHTL格式
    };
    
    ConfigParser() = default;
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