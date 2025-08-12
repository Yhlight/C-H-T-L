#include "ScriptNode.h"
#include <sstream>

namespace CHTL {

ScriptNode::ScriptNode()
    : Node(NodeType::SCRIPT) {
}

ScriptNode::ScriptNode(const std::string& code, bool isCHTLJS)
    : Node(NodeType::SCRIPT), code_(code), isCHTLJS_(isCHTLJS) {
}

void ScriptNode::accept(NodeVisitor* visitor) {
    if (visitor) {
        visitor->visitNode(this);
    }
}

NodePtr ScriptNode::clone() const {
    auto cloned = std::make_shared<ScriptNode>(code_, isCHTLJS_);
    cloned->type_ = type_;
    cloned->src_ = src_;
    cloned->async_ = async_;
    cloned->defer_ = defer_;
    cloned->module_ = module_;
    
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

std::string ScriptNode::toString() const {
    std::stringstream ss;
    ss << "ScriptNode[";
    
    if (!code_.empty()) {
        ss << "hasCode=true";
        if (code_.length() <= 30) {
            ss << ", code=\"" << code_ << "\"";
        } else {
            ss << ", code=\"" << code_.substr(0, 30) << "...\"";
        }
    }
    
    if (!src_.empty()) {
        ss << ", src=\"" << src_ << "\"";
    }
    
    ss << ", isCHTLJS=" << (isCHTLJS_ ? "true" : "false");
    ss << ", type=\"" << type_ << "\"";
    
    if (async_) ss << ", async=true";
    if (defer_) ss << ", defer=true";
    if (module_) ss << ", module=true";
    
    ss << "]";
    
    return ss.str();
}

} // namespace CHTL