#ifndef CHTL_NODE_ELEMENTNODE_H
#define CHTL_NODE_ELEMENTNODE_H

#include "Node.h"
#include <set>

namespace CHTL {

/**
 * 元素节点 - 表示HTML元素
 */
class ElementNode : public Node {
public:
    explicit ElementNode(const std::string& tagName);
    ~ElementNode() = default;
    
    // 实现visitor模式
    void accept(NodeVisitor* visitor) override;
    
    // 元素特有方法
    const std::string& getTagName() const { return tagName_; }
    
    // ID管理
    void setId(const std::string& id) { id_ = id; }
    const std::string& getId() const { return id_; }
    
    // Class管理
    void addClass(const std::string& className);
    void removeClass(const std::string& className);
    bool hasClass(const std::string& className) const;
    const std::set<std::string>& getClasses() const { return classes_; }
    
    // 自闭合标签
    void setSelfClosing(bool selfClosing) { selfClosing_ = selfClosing; }
    bool isSelfClosing() const { return selfClosing_; }
    
    // 克隆
    NodePtr clone() const override;
    
    // 调试信息
    std::string toString() const override;
    
private:
    std::string tagName_;
    std::string id_;
    std::set<std::string> classes_;
    bool selfClosing_ = false;
};

} // namespace CHTL

#endif // CHTL_NODE_ELEMENTNODE_H