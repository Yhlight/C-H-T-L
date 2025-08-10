#ifndef CHTL_CONFIG_H
#define CHTL_CONFIG_H

#include "Node/Node.h"
#include <variant>
#include <optional>

namespace chtl {

// 配置值类型 - 可以是字符串或字符串数组
using ConfigValue = std::variant<std::string, std::vector<std::string>>;

// Config节点 - 配置节点，用于存储[Configuration]块
class Config : public Node {
private:
    std::unordered_map<std::string, ConfigValue> configItems_;
    std::string configName_;  // 可选的配置名称
    
public:
    Config(const std::string& name = "")
        : Node(NodeType::CONFIG, "[Configuration]"), configName_(name) {}
    
    // 配置名称
    const std::string& getConfigName() const { return configName_; }
    void setConfigName(const std::string& name) { configName_ = name; }
    
    // 配置项管理（新接口）
    void setConfigItem(const std::string& key, const ConfigValue& value) { configItems_[key] = value; }
    std::optional<ConfigValue> getConfigItem(const std::string& key) const {
        auto it = configItems_.find(key);
        if (it != configItems_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    bool hasConfigItem(const std::string& key) const { return configItems_.find(key) != configItems_.end(); }
    const std::unordered_map<std::string, ConfigValue>& getConfigItems() const { return configItems_; }
    void removeConfigItem(const std::string& key) { configItems_.erase(key); }
    
    // 向后兼容的旧接口
    void setConfig(const std::string& key, const std::string& value) { 
        configItems_[key] = value; 
    }
    std::string getConfig(const std::string& key) const;
    bool hasConfig(const std::string& key) const { return hasConfigItem(key); }
    void removeConfig(const std::string& key) { removeConfigItem(key); }
    
    // 数组配置项管理（向后兼容）
    void setArrayConfig(const std::string& key, const std::vector<std::string>& values) { 
        configItems_[key] = values; 
    }
    void addArrayConfigItem(const std::string& key, const std::string& value);
    std::vector<std::string> getArrayConfig(const std::string& key) const;
    bool hasArrayConfig(const std::string& key) const;
    void removeArrayConfig(const std::string& key) { removeConfigItem(key); }
    
    // 合并配置
    void mergeConfig(const Config& other);
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_CONFIG_H