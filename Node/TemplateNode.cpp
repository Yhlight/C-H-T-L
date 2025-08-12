#include "TemplateNode.h"
#include <sstream>

namespace CHTL {

TemplateNode::TemplateNode(TemplateType type, const std::string& name)
    : Node(NodeType::TEMPLATE), templateType_(type), name_(name) {
}

void TemplateNode::accept(NodeVisitor* visitor) {
    if (visitor) {
        visitor->visitNode(this);
    }
}

void TemplateNode::addParameter(const std::string& name, const std::string& defaultValue) {
    if (!name.empty()) {
        parameters_.push_back({name, defaultValue});
    }
}

bool TemplateNode::hasParameter(const std::string& name) const {
    for (const auto& [paramName, _] : parameters_) {
        if (paramName == name) {
            return true;
        }
    }
    return false;
}

const std::string& TemplateNode::getParameterDefault(const std::string& name) const {
    static const std::string empty;
    for (const auto& [paramName, defaultValue] : parameters_) {
        if (paramName == name) {
            return defaultValue;
        }
    }
    return empty;
}

std::string TemplateNode::getQualifiedName() const {
    if (namespace_.empty()) {
        return name_;
    }
    return namespace_ + "::" + name_;
}

NodePtr TemplateNode::clone() const {
    auto cloned = std::make_shared<TemplateNode>(templateType_, name_);
    cloned->inherits_ = inherits_;
    cloned->parameters_ = parameters_;
    cloned->exported_ = exported_;
    cloned->namespace_ = namespace_;
    
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

std::string TemplateNode::toString() const {
    std::stringstream ss;
    ss << "TemplateNode[";
    
    switch (templateType_) {
        case TemplateType::STYLE:
            ss << "type=@Style";
            break;
        case TemplateType::ELEMENT:
            ss << "type=@Element";
            break;
        case TemplateType::VAR:
            ss << "type=@Var";
            break;
    }
    
    ss << ", name=" << name_;
    
    if (!inherits_.empty()) {
        ss << ", inherits=" << inherits_;
    }
    
    if (!parameters_.empty()) {
        ss << ", params=" << parameters_.size();
    }
    
    if (exported_) {
        ss << ", exported=true";
    }
    
    if (!namespace_.empty()) {
        ss << ", namespace=" << namespace_;
    }
    
    ss << ", children=" << getChildCount();
    ss << "]";
    
    return ss.str();
}

} // namespace CHTL