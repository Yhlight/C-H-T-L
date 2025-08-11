#ifndef CHTL_CONFIG_PARSER_H
#define CHTL_CONFIG_PARSER_H

#include "Parser/BasicParser.h"
#include "Node/Config.h"
#include <unordered_set>
#include <optional>

namespace chtl {

class Config;

/**
 * ConfigParser - 专门用于解析 [Configuration] 块
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
    
    // 解析配置块
    std::shared_ptr<Config> parseConfiguration();
    
    // 导出配置
    bool exportConfig(std::shared_ptr<Config> config, 
                     const std::string& filename,
                     ConfigFormat format = ConfigFormat::CHTL);
    
private:
    // 辅助方法
    bool check(TokenType type);
    bool match(TokenType type);
    Token advance();
    void addError(const std::string& message);
    bool isAtEnd();
    
    // 解析方法
    void parseConfigContent(std::shared_ptr<Config> configNode);
    void parseConfigGroup(std::shared_ptr<Config> configNode, const std::string& groupName);
    void parseConfigItem(std::shared_ptr<Config> configNode, const std::string& groupPrefix = "");
    std::optional<ConfigValue> parseConfigValue();
    void skipToNextStatement();
    
    // 导出方法
    std::string exportToJSON(std::shared_ptr<Config> config);
    std::string exportToYAML(std::shared_ptr<Config> config);
    std::string exportToINI(std::shared_ptr<Config> config);
    std::string exportToTOML(std::shared_ptr<Config> config);
    std::string exportToXML(std::shared_ptr<Config> config);
    std::string exportToCHTL(std::shared_ptr<Config> config);
    
    // 格式检测
    ConfigFormat detectFormat(const std::string& content);
    
    // 当前格式和配置
    // ConfigFormat currentFormat_; // TODO: Remove if not needed
    std::shared_ptr<Config> currentConfig_;
    
    // 有效的配置键
    static const std::unordered_set<std::string> VALID_CONFIG_KEYS;
};

} // namespace chtl

#endif // CHTL_CONFIG_PARSER_H