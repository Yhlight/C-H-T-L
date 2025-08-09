#ifndef CHTL_CONFIG_GENERATOR_H
#define CHTL_CONFIG_GENERATOR_H

#include "Generator/BasicGenerator.h"
#include "Node/Config.h"
#include <unordered_map>

namespace chtl {

// 配置生成器 - 生成各种配置格式
class ConfigGenerator : public BasicGenerator {
public:
    // 配置格式类型
    enum class ConfigFormat {
        JSON,       // JSON格式
        YAML,       // YAML格式
        INI,        // INI格式
        XML,        // XML格式
        PROPERTIES, // Java Properties格式
        TOML,       // TOML格式
        CHTL        // CHTL原生格式
    };
    
private:
    ConfigFormat format_;
    bool sortKeys_;          // 是否按键排序
    bool includeComments_;   // 是否包含注释
    int maxLineLength_;      // 最大行长度（用于折行）
    
    // 格式特定的配置
    struct JsonConfig {
        bool trailingComma = false;
        bool singleQuotes = false;
    } jsonConfig_;
    
    struct YamlConfig {
        bool flowStyle = false;
        bool explicitStart = false;
        bool explicitEnd = false;
    } yamlConfig_;
    
public:
    ConfigGenerator(ConfigFormat format = ConfigFormat::JSON);
    virtual ~ConfigGenerator() = default;
    
    // 设置格式
    void setFormat(ConfigFormat format) { format_ = format; }
    ConfigFormat getFormat() const { return format_; }
    
    // 配置选项
    void setSortKeys(bool sort) { sortKeys_ = sort; }
    void setIncludeComments(bool include) { includeComments_ = include; }
    void setMaxLineLength(int length) { maxLineLength_ = length; }
    
    // 格式特定配置
    JsonConfig& getJsonConfig() { return jsonConfig_; }
    YamlConfig& getYamlConfig() { return yamlConfig_; }
    
    // 主生成方法
    bool generate(std::shared_ptr<Node> node) override;
    
    // 生成特定格式
    bool generateJson(std::shared_ptr<Config> config);
    bool generateYaml(std::shared_ptr<Config> config);
    bool generateIni(std::shared_ptr<Config> config);
    bool generateXml(std::shared_ptr<Config> config);
    bool generateProperties(std::shared_ptr<Config> config);
    bool generateToml(std::shared_ptr<Config> config);
    bool generateChtl(std::shared_ptr<Config> config);
    
protected:
    // 实现基类的纯虚函数
    void generateElement(std::shared_ptr<Node> node) override;
    void generateText(std::shared_ptr<Node> node) override;
    void generateComment(std::shared_ptr<Node> node) override;
    
    // 重写Config节点生成
    void generateConfig(std::shared_ptr<Node> node) override;
    
private:
    // JSON生成辅助方法
    void writeJsonValue(const std::string& value, bool isLast = false);
    void writeJsonArray(const std::vector<std::string>& array, bool isLast = false);
    void writeJsonObject(const std::unordered_map<std::string, std::string>& object);
    void writeJsonObjectArray(const std::unordered_map<std::string, std::vector<std::string>>& arrays);
    
    // YAML生成辅助方法
    void writeYamlValue(const std::string& key, const std::string& value);
    void writeYamlArray(const std::string& key, const std::vector<std::string>& array);
    void writeYamlComment(const std::string& comment);
    
    // INI生成辅助方法
    void writeIniSection(const std::string& section);
    void writeIniKeyValue(const std::string& key, const std::string& value);
    void writeIniComment(const std::string& comment);
    
    // XML生成辅助方法
    void writeXmlElement(const std::string& name, const std::string& value);
    void writeXmlArrayElement(const std::string& name, const std::vector<std::string>& values);
    
    // Properties生成辅助方法
    void writePropertiesKeyValue(const std::string& key, const std::string& value);
    void writePropertiesComment(const std::string& comment);
    std::string escapeProperties(const std::string& value);
    
    // TOML生成辅助方法
    void writeTomlKeyValue(const std::string& key, const std::string& value);
    void writeTomlArray(const std::string& key, const std::vector<std::string>& array);
    void writeTomlTable(const std::string& table);
    
    // 通用辅助方法
    std::vector<std::string> getSortedKeys(const std::unordered_map<std::string, std::string>& map);
    std::string wrapLongLine(const std::string& line, const std::string& prefix = "");
    bool needsQuoting(const std::string& value, ConfigFormat format);
    std::string quote(const std::string& value, ConfigFormat format);
};

} // namespace chtl

#endif // CHTL_CONFIG_GENERATOR_H