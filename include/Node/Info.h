#ifndef CHTL_INFO_H
#define CHTL_INFO_H

#include "Node/Node.h"
#include <string>
#include <unordered_map>

namespace chtl {

// Info节点 - 模块信息节点，用于[Info]语句
class Info : public Node {
private:
    std::unordered_map<std::string, std::string> properties_;
    
public:
    Info() : Node(NodeType::INFO, "[Info]") {}
    
    // 属性管理
    void setProperty(const std::string& key, const std::string& value) {
        properties_[key] = value;
    }
    
    std::string getProperty(const std::string& key) const {
        auto it = properties_.find(key);
        return (it != properties_.end()) ? it->second : "";
    }
    
    bool hasProperty(const std::string& key) const {
        return properties_.find(key) != properties_.end();
    }
    
    const std::unordered_map<std::string, std::string>& getProperties() const {
        return properties_;
    }
    
    // 常用属性的便捷访问方法
    std::string getName() const { return getProperty("name"); }
    void setName(const std::string& name) { setProperty("name", name); }
    
    std::string getVersion() const { return getProperty("version"); }
    void setVersion(const std::string& version) { setProperty("version", version); }
    
    std::string getDescription() const { return getProperty("description"); }
    void setDescription(const std::string& desc) { setProperty("description", desc); }
    
    std::string getAuthor() const { return getProperty("author"); }
    void setAuthor(const std::string& author) { setProperty("author", author); }
    
    std::string getLicense() const { return getProperty("license"); }
    void setLicense(const std::string& license) { setProperty("license", license); }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_INFO_H