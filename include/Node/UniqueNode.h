#ifndef CHTL_UNIQUE_NODE_H
#define CHTL_UNIQUE_NODE_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

namespace chtl {

// 前向声明
class UniqueNode;
class Visitor;

// 节点类型枚举
enum class NodeType {
    NODE,
    ELEMENT,
    TEXT,
    COMMENT,
    TEMPLATE,
    CUSTOM,
    STYLE,
    SCRIPT,
    IMPORT,
    EXPORT,
    OPERATE,
    ORIGIN,
    INFO,
    CONFIG,
    NAMESPACE
};

// 基于 unique_ptr 的节点基类
class UniqueNode {
public:
    using NodePtr = std::unique_ptr<UniqueNode>;
    using AttributeValue = std::variant<std::string, int, double, bool>;
    
protected:
    NodeType type_;
    std::string tagName_;
    std::vector<NodePtr> children_;
    std::unordered_map<std::string, AttributeValue> attributes_;
    UniqueNode* parent_ = nullptr; // 原始指针，不拥有所有权
    
public:
    // 构造函数
    explicit UniqueNode(NodeType type = NodeType::NODE, 
                       const std::string& tagName = "")
        : type_(type), tagName_(tagName) {}
    
    // 禁用拷贝构造和赋值
    UniqueNode(const UniqueNode&) = delete;
    UniqueNode& operator=(const UniqueNode&) = delete;
    
    // 启用移动语义
    UniqueNode(UniqueNode&&) = default;
    UniqueNode& operator=(UniqueNode&&) = default;
    
    // 虚析构函数
    virtual ~UniqueNode() = default;
    
    // 基本访问器
    NodeType getType() const { return type_; }
    const std::string& getTagName() const { return tagName_; }
    void setTagName(const std::string& name) { tagName_ = name; }
    
    // 父节点管理（使用原始指针）
    UniqueNode* getParent() const { return parent_; }
    void setParent(UniqueNode* parent) { parent_ = parent; }
    
    // 子节点管理（使用 unique_ptr）
    void addChild(NodePtr child) {
        if (child) {
            child->setParent(this);
            children_.push_back(std::move(child));
        }
    }
    
    void removeChild(size_t index) {
        if (index < children_.size()) {
            children_.erase(children_.begin() + index);
        }
    }
    
    size_t getChildCount() const { return children_.size(); }
    
    UniqueNode* getChild(size_t index) const {
        return index < children_.size() ? children_[index].get() : nullptr;
    }
    
    // 转移子节点所有权
    NodePtr takeChild(size_t index) {
        if (index >= children_.size()) return nullptr;
        
        NodePtr child = std::move(children_[index]);
        children_.erase(children_.begin() + index);
        if (child) {
            child->setParent(nullptr);
        }
        return child;
    }
    
    // 属性管理
    void setAttribute(const std::string& name, const AttributeValue& value) {
        attributes_[name] = value;
    }
    
    bool hasAttribute(const std::string& name) const {
        return attributes_.find(name) != attributes_.end();
    }
    
    const AttributeValue* getAttribute(const std::string& name) const {
        auto it = attributes_.find(name);
        return it != attributes_.end() ? &it->second : nullptr;
    }
    
    const std::unordered_map<std::string, AttributeValue>& getAttributes() const {
        return attributes_;
    }
    
    // 深拷贝
    virtual NodePtr clone() const {
        auto cloned = std::make_unique<UniqueNode>(type_, tagName_);
        cloned->attributes_ = attributes_;
        
        for (const auto& child : children_) {
            if (child) {
                cloned->addChild(child->clone());
            }
        }
        
        return cloned;
    }
    
    // 访问者模式
    virtual void accept(Visitor* visitor);
    
    // 调试辅助
    virtual std::string toString() const {
        return "[" + std::to_string(static_cast<int>(type_)) + "] " + tagName_;
    }
};

} // namespace chtl

#endif // CHTL_UNIQUE_NODE_H