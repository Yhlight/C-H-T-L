#ifndef CHTL_CONFIG_H
#define CHTL_CONFIG_H

#include "node/Node.h"

namespace chtl {

// Config节点 - 配置节点，用于存储[Configuration]块
class Config : public Node {
private:
    std::unordered_map<std::string, std::string> configItems_;
    std::unordered_map<std::string, std::vector<std::string>> arrayItems_;
    std::string configName_;  // 可选的配置名称
    
public:
    Config(const std::string& name = "")
        : Node(NodeType::CONFIG, "[Configuration]"), configName_(name) {}
    
    // 配置名称
    const std::string& getConfigName() const { return configName_; }
    void setConfigName(const std::string& name) { configName_ = name; }
    
    // 配置项管理
    void setConfig(const std::string& key, const std::string& value) { configItems_[key] = value; }
    std::string getConfig(const std::string& key) const;
    bool hasConfig(const std::string& key) const { return configItems_.find(key) != configItems_.end(); }
    const std::unordered_map<std::string, std::string>& getConfigs() const { return configItems_; }
    void removeConfig(const std::string& key) { configItems_.erase(key); }
    
    // 数组配置项管理
    void setArrayConfig(const std::string& key, const std::vector<std::string>& values) { arrayItems_[key] = values; }
    void addArrayConfigItem(const std::string& key, const std::string& value);
    std::vector<std::string> getArrayConfig(const std::string& key) const;
    bool hasArrayConfig(const std::string& key) const { return arrayItems_.find(key) != arrayItems_.end(); }
    void removeArrayConfig(const std::string& key) { arrayItems_.erase(key); }
    
    // 合并配置
    void mergeConfig(const Config& other);
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_CONFIG_H