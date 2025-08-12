#ifndef CHTL_NODE_NODE_H
#define CHTL_NODE_NODE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Common/Types.h"

namespace CHTL {

// 前向声明
class NodeVisitor;

/**
 * AST节点基类
 */
class Node {
public:
    explicit Node(NodeType type) : type_(type) {}
    virtual ~Node() = default;
    
    // 访问者模式
    virtual void accept(NodeVisitor* visitor) = 0;
    
    // 获取节点类型
    NodeType getType() const { return type_; }
    
    // 子节点管理
    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);
    void insertChild(size_t index, std::shared_ptr<Node> child);
    std::shared_ptr<Node> getChild(size_t index) const;
    const std::vector<std::shared_ptr<Node>>& getChildren() const { return children_; }
    size_t getChildCount() const { return children_.size(); }
    
    // 父节点管理
    void setParent(Node* parent) { parent_ = parent; }
    Node* getParent() const { return parent_; }
    
    // 属性管理
    void setAttribute(const std::string& key, const std::string& value);
    std::string getAttribute(const std::string& key) const;
    bool hasAttribute(const std::string& key) const;
    void removeAttribute(const std::string& key);
    const std::unordered_map<std::string, std::string>& getAttributes() const { return attributes_; }
    
    // 源码位置信息
    void setLocation(int startLine, int startColumn, int endLine, int endColumn);
    int getStartLine() const { return startLine_; }
    int getStartColumn() const { return startColumn_; }
    int getEndLine() const { return endLine_; }
    int getEndColumn() const { return endColumn_; }
    
    // 调试信息
    virtual std::string toString() const;
    
    // 深拷贝
    virtual std::shared_ptr<Node> clone() const = 0;
    
protected:
    NodeType type_;
    Node* parent_ = nullptr;
    std::vector<std::shared_ptr<Node>> children_;
    std::unordered_map<std::string, std::string> attributes_;
    
    // 源码位置
    int startLine_ = 0;
    int startColumn_ = 0;
    int endLine_ = 0;
    int endColumn_ = 0;
};

/**
 * 访问者接口
 */
class NodeVisitor {
public:
    virtual ~NodeVisitor() = default;
    
    // 基础访问方法
    virtual void visitNode(Node* node) {}
    
    // 具体节点类型的访问方法（子类实现）
};

// 类型别名
using NodePtr = std::shared_ptr<Node>;

} // namespace CHTL

#endif // CHTL_NODE_NODE_H