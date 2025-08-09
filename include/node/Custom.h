#ifndef CHTL_CUSTOM_H
#define CHTL_CUSTOM_H

#include "node/Node.h"

namespace chtl {

// Custom节点 - 支持三种自定义类型：@Element、@Style、@Var
class Custom : public Node {
public:
    enum class CustomType {
        ELEMENT,    // 自定义元素
        STYLE,      // 自定义样式
        VAR         // 自定义变量
    };
    
private:
    CustomType customType_;
    std::string customName_;
    std::unordered_map<std::string, std::string> properties_;
    std::vector<std::string> deleteList_;  // delete语句删除的属性
    
public:
    Custom(CustomType type, const std::string& name)
        : Node(NodeType::CUSTOM, "[Custom]"), customType_(type), customName_(name) {}
    
    // 自定义类型和名称
    CustomType getCustomType() const { return customType_; }
    const std::string& getCustomName() const { return customName_; }
    void setCustomName(const std::string& name) { customName_ = name; }
    
    // 属性管理
    void setProperty(const std::string& name, const std::string& value) { properties_[name] = value; }
    std::string getProperty(const std::string& name) const;
    bool hasProperty(const std::string& name) const { return properties_.find(name) != properties_.end(); }
    const std::unordered_map<std::string, std::string>& getProperties() const { return properties_; }
    
    // 删除列表管理
    void addDelete(const std::string& property) { deleteList_.push_back(property); }
    const std::vector<std::string>& getDeleteList() const { return deleteList_; }
    bool hasDelete(const std::string& property) const;
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_CUSTOM_H