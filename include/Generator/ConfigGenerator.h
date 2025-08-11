#ifndef CHTL_CONFIG_GENERATOR_H
#define CHTL_CONFIG_GENERATOR_H

#include "Generator/BasicGenerator.h"
#include "Node/Config.h"
#include <unordered_map>

namespace chtl {

/**
 * ConfigGenerator - 专门用于生成各种配置格式
 */
class ConfigGenerator : public BasicGenerator {
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
    
    ConfigGenerator();
    virtual ~ConfigGenerator() = default;
    
    // 覆盖基类方法
    bool generate(std::shared_ptr<Node> node) override;
    
    // 扩展的生成方法
    void generate(std::shared_ptr<Node> root, std::ostream& output);
    
    // 设置输出格式
    void setFormat(ConfigFormat format) { currentFormat_ = format; }
    ConfigFormat getFormat() const { return currentFormat_; }
    
    // 设置选项
    void setSortKeys(bool sort) { sortKeys_ = sort; }
    void setPrettyPrint(bool pretty) { prettyPrint_ = pretty; }
    void setIndentSize(int size) { indentSize_ = size; }
    
protected:
    // 生成方法
    void generateNode(std::shared_ptr<Node> node) override;
    void generateElement(std::shared_ptr<Node> node) override;
    void generateText(std::shared_ptr<Node> node) override;
    void generateTemplate(std::shared_ptr<Node> node) override;
    void generateCustom(std::shared_ptr<Node> node) override;
    void generateStyle(std::shared_ptr<Node> node) override;
    void generateComment(std::shared_ptr<Node> node) override;
    void generateConfig(std::shared_ptr<Node> node) override;
    
private:
    // 格式特定的生成方法
    std::string generateJSON(std::shared_ptr<Config> config);
    std::string generateYAML(std::shared_ptr<Config> config);
    std::string generateINI(std::shared_ptr<Config> config);
    std::string generateTOML(std::shared_ptr<Config> config);
    std::string generateXML(std::shared_ptr<Config> config);
    std::string generateCHTL(std::shared_ptr<Config> config);
    
    // 辅助方法
    void write(const std::string& str);
    void writeLine(const std::string& str = "");
    void writeIndent();
    void increaseIndent();
    void decreaseIndent();
    
    // 转义方法
    std::string escapeJSON(const std::string& str);
    std::string escapeXML(const std::string& str);
    
    // 工具方法
    std::vector<std::string> getSortedKeys(const std::unordered_map<std::string, ConfigValue>& map);
    void reportWarning(const std::string& message);
    
    // 配置选项
    ConfigFormat currentFormat_ = ConfigFormat::CHTL;
    bool sortKeys_;
    bool prettyPrint_;
    int indentSize_;
    int currentIndent_;
    std::ostream* output_;
};

} // namespace chtl

#endif // CHTL_CONFIG_GENERATOR_H