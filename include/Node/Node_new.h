#ifndef CHTL_NODE_NEW_H
#define CHTL_NODE_NEW_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <variant>

namespace chtl {

// 前向声明
class Node;
class Element;
class Text;

// Node类型枚举
enum class NodeType {
    ELEMENT,
    TEXT,
    COMMENT,
    TEMPLATE,
    CUSTOM,
    STYLE,
    CONFIG,
    IMPORT,
    NAMESPACE,
    OPERATE,
    ORIGIN,
    REFERENCE,
    DELETE,
    INFO,
    EXPORT,
    SCRIPT
};

// 属性值类型
using AttributeValue = std::variant<std::string, int, double, bool>;

// 新的 Node 基类 - 使用 unique_ptr 管理子节点
class Node {
protected:
    NodeType type_;
    Node* parent_;  // 原始指针，不拥有所有权
    std::vector<std::unique_ptr<Node>> children_;  // unique_ptr 管理子节点
    std::string nodeName_;
    std::string tagName_;
    std::unordered_map<std::string, AttributeValue> attributes_;
    std::vector<std::string> constraints_;
    std::vector<std::string> inheritances_;
    std::string text_;
    std::vector<std::string> classes_;
    
public:
    Node(NodeType type, const std::string& name = "")
        : type_(type), parent_(nullptr), nodeName_(name) {}
    
    virtual ~Node() = default;
    
    // 禁用拷贝，只允许移动
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = default;
    Node& operator=(Node&&) = default;
    
    // 基本属性访问
    NodeType getType() const { return type_; }
    const std::string& getNodeName() const { return nodeName_; }
    void setNodeName(const std::string& name) { nodeName_ = name; }
    const std::string& getTagName() const { return tagName_; }
    void setTagName(const std::string& tagName) { tagName_ = tagName; }
    
    // 父节点管理
    Node* getParent() { return parent_; }
    const Node* getParent() const { return parent_; }
    
    // 子节点管理 - 使用 unique_ptr
    void appendChild(std::unique_ptr<Node> child) {
        if (child) {
            child->parent_ = this;
            children_.push_back(std::move(child));
        }
    }
    
    // 移除并返回子节点（转移所有权）
    std::unique_ptr<Node> removeChild(size_t index) {
        if (index >= children_.size()) return nullptr;
        
        auto child = std::move(children_[index]);
        children_.erase(children_.begin() + index);
        if (child) {
            child->parent_ = nullptr;
        }
        return child;
    }
    
    // 获取子节点（不转移所有权）
    Node* getChild(size_t index) {
        return index < children_.size() ? children_[index].get() : nullptr;
    }
    
    const Node* getChild(size_t index) const {
        return index < children_.size() ? children_[index].get() : nullptr;
    }
    
    size_t getChildCount() const { return children_.size(); }
    
    // 遍历子节点
    template<typename Func>
    void forEachChild(Func func) {
        for (auto& child : children_) {
            func(child.get());
        }
    }
    
    // 查找子节点
    Node* findChild(const std::string& tagName) {
        for (auto& child : children_) {
            if (child->getTagName() == tagName) {
                return child.get();
            }
        }
        return nullptr;
    }
    
    // 属性管理
    void setAttribute(const std::string& name, const AttributeValue& value) {
        attributes_[name] = value;
    }
    
    AttributeValue getAttribute(const std::string& name) const {
        auto it = attributes_.find(name);
        return it != attributes_.end() ? it->second : AttributeValue("");
    }
    
    bool hasAttribute(const std::string& name) const {
        return attributes_.find(name) != attributes_.end();
    }
    
    // 文本内容
    const std::string& getText() const { return text_; }
    void setText(const std::string& text) { text_ = text; }
    
    // 类名管理
    void addClass(const std::string& className) {
        if (std::find(classes_.begin(), classes_.end(), className) == classes_.end()) {
            classes_.push_back(className);
        }
    }
    
    const std::vector<std::string>& getClasses() const { return classes_; }
    
    // 约束管理
    void addConstraint(const std::string& constraint) {
        constraints_.push_back(constraint);
    }
    
    const std::vector<std::string>& getConstraints() const { return constraints_; }
    
    // 继承管理
    void addInheritance(const std::string& inheritance) {
        inheritances_.push_back(inheritance);
    }
    
    const std::vector<std::string>& getInheritances() const { return inheritances_; }
    
    // 虚函数，子类可以重写
    virtual std::string toString() const {
        return "Node[" + nodeName_ + "]";
    }
    
    virtual void accept(class NodeVisitor* visitor) = 0;
};

// 访问者模式接口
class NodeVisitor {
public:
    virtual ~NodeVisitor() = default;
    virtual void visitElement(Element* element) = 0;
    virtual void visitText(Text* text) = 0;
    virtual void visitTemplate(class Template* tmpl) = 0;
    virtual void visitCustom(class Custom* custom) = 0;
    virtual void visitStyle(class Style* style) = 0;
    // ... 其他节点类型
};

} // namespace chtl

#endif // CHTL_NODE_NEW_H