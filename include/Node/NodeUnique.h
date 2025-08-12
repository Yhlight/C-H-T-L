#ifndef CHTL_NODE_UNIQUE_H
#define CHTL_NODE_UNIQUE_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

namespace chtl {

// 前向声明
class NodeUnique;
class ElementUnique;
class TextUnique;

// 节点类型枚举
enum class NodeTypeUnique {
    ELEMENT,
    TEXT,
    COMMENT,
    STYLE,
    SCRIPT,
    TEMPLATE,
    CUSTOM,
    // ... 其他类型
};

// 属性值类型
using AttributeValueUnique = std::variant<std::string, int, double, bool>;

// 基础节点类 - 使用 unique_ptr
class NodeUnique {
public:
    explicit NodeUnique(NodeTypeUnique type) : type_(type) {}
    virtual ~NodeUnique() = default;
    
    // 删除拷贝构造和赋值
    NodeUnique(const NodeUnique&) = delete;
    NodeUnique& operator=(const NodeUnique&) = delete;
    
    // 允许移动
    NodeUnique(NodeUnique&&) = default;
    NodeUnique& operator=(NodeUnique&&) = default;
    
    // 类型访问
    NodeTypeUnique getType() const { return type_; }
    
    // 子节点管理 - 使用 unique_ptr
    void addChild(std::unique_ptr<NodeUnique> child) {
        if (child) {
            child->parent_ = this;
            children_.push_back(std::move(child));
        }
    }
    
    // 获取子节点（返回原始指针，不转移所有权）
    NodeUnique* getChild(size_t index) {
        return index < children_.size() ? children_[index].get() : nullptr;
    }
    
    const NodeUnique* getChild(size_t index) const {
        return index < children_.size() ? children_[index].get() : nullptr;
    }
    
    // 移除并返回子节点（转移所有权）
    std::unique_ptr<NodeUnique> removeChild(size_t index) {
        if (index >= children_.size()) return nullptr;
        
        auto child = std::move(children_[index]);
        children_.erase(children_.begin() + index);
        if (child) {
            child->parent_ = nullptr;
        }
        return child;
    }
    
    // 获取所有子节点的只读访问
    const std::vector<std::unique_ptr<NodeUnique>>& getChildren() const {
        return children_;
    }
    
    // 获取父节点（原始指针）
    NodeUnique* getParent() { return parent_; }
    const NodeUnique* getParent() const { return parent_; }
    
    // 克隆节点（深拷贝）
    virtual std::unique_ptr<NodeUnique> clone() const = 0;
    
protected:
    NodeTypeUnique type_;
    NodeUnique* parent_ = nullptr;  // 父节点使用原始指针（不拥有）
    std::vector<std::unique_ptr<NodeUnique>> children_;  // 子节点使用unique_ptr（拥有）
};

// 元素节点 - 使用 unique_ptr
class ElementUnique : public NodeUnique {
public:
    explicit ElementUnique(const std::string& tagName) 
        : NodeUnique(NodeTypeUnique::ELEMENT), tagName_(tagName) {}
    
    const std::string& getTagName() const { return tagName_; }
    
    // 属性管理
    void setAttribute(const std::string& name, const AttributeValueUnique& value) {
        attributes_[name] = value;
    }
    
    AttributeValueUnique getAttribute(const std::string& name) const {
        auto it = attributes_.find(name);
        return it != attributes_.end() ? it->second : AttributeValueUnique("");
    }
    
    const auto& getAttributes() const { return attributes_; }
    
    // 克隆
    std::unique_ptr<NodeUnique> clone() const override {
        auto cloned = std::make_unique<ElementUnique>(tagName_);
        cloned->attributes_ = attributes_;
        
        // 深拷贝子节点
        for (const auto& child : children_) {
            cloned->addChild(child->clone());
        }
        
        return cloned;
    }
    
private:
    std::string tagName_;
    std::unordered_map<std::string, AttributeValueUnique> attributes_;
};

// 文本节点 - 使用 unique_ptr
class TextUnique : public NodeUnique {
public:
    explicit TextUnique(const std::string& content) 
        : NodeUnique(NodeTypeUnique::TEXT), content_(content) {}
    
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    
    // 克隆
    std::unique_ptr<NodeUnique> clone() const override {
        return std::make_unique<TextUnique>(content_);
    }
    
private:
    std::string content_;
};

} // namespace chtl

#endif // CHTL_NODE_UNIQUE_H