#include "ElementNode.h"
#include <sstream>

namespace CHTL {

ElementNode::ElementNode(const std::string& tagName)
    : Node(NodeType::ELEMENT), tagName_(tagName) {
}

void ElementNode::accept(NodeVisitor* visitor) {
    if (visitor) {
        visitor->visitNode(this);
    }
}

void ElementNode::addClass(const std::string& className) {
    if (!className.empty()) {
        classes_.insert(className);
    }
}

void ElementNode::removeClass(const std::string& className) {
    classes_.erase(className);
}

bool ElementNode::hasClass(const std::string& className) const {
    return classes_.find(className) != classes_.end();
}

NodePtr ElementNode::clone() const {
    auto cloned = std::make_shared<ElementNode>(tagName_);
    cloned->id_ = id_;
    cloned->classes_ = classes_;
    cloned->selfClosing_ = selfClosing_;
    
    // 复制属性
    for (const auto& [key, value] : getAttributes()) {
        cloned->setAttribute(key, value);
    }
    
    // 复制子节点
    for (const auto& child : getChildren()) {
        cloned->addChild(child->clone());
    }
    
    return cloned;
}

std::string ElementNode::toString() const {
    std::stringstream ss;
    ss << "ElementNode[tag=" << tagName_;
    
    if (!id_.empty()) {
        ss << ", id=" << id_;
    }
    
    if (!classes_.empty()) {
        ss << ", classes=";
        bool first = true;
        for (const auto& cls : classes_) {
            if (!first) ss << ",";
            ss << cls;
            first = false;
        }
    }
    
    ss << ", children=" << getChildCount();
    ss << ", selfClosing=" << (selfClosing_ ? "true" : "false");
    ss << "]";
    
    return ss.str();
}

} // namespace CHTL