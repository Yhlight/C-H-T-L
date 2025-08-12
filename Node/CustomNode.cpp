#include "CustomNode.h"
#include <sstream>

namespace CHTL {

CustomNode::CustomNode(CustomType type, const std::string& name)
    : Node(NodeType::CUSTOM), customType_(type), name_(name) {
}

void CustomNode::accept(NodeVisitor* visitor) {
    if (visitor) {
        visitor->visitNode(this);
    }
}

void CustomNode::addNoValueStyle(const std::string& property) {
    if (!property.empty()) {
        noValueStyles_.push_back(property);
    }
}

void CustomNode::setParameter(const std::string& name, const std::string& value) {
    if (!name.empty()) {
        parameters_[name] = value;
    }
}

std::string CustomNode::getQualifiedName() const {
    if (namespace_.empty()) {
        return name_;
    }
    return namespace_ + "::" + name_;
}

NodePtr CustomNode::clone() const {
    auto cloned = std::make_shared<CustomNode>(customType_, name_);
    cloned->specialization_ = specialization_;
    cloned->elementOp_ = elementOp_;
    cloned->opIndex_ = opIndex_;
    cloned->noValueStyles_ = noValueStyles_;
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

std::string CustomNode::toString() const {
    std::stringstream ss;
    ss << "CustomNode[";
    
    switch (customType_) {
        case CustomType::STYLE:
            ss << "type=@Style";
            break;
        case CustomType::ELEMENT:
            ss << "type=@Element";
            break;
        case CustomType::VAR:
            ss << "type=@Var";
            break;
    }
    
    ss << ", name=" << name_;
    
    if (!specialization_.empty()) {
        ss << ", specialization=" << specialization_;
    }
    
    if (elementOp_ != ElementOperation::NONE) {
        ss << ", operation=";
        switch (elementOp_) {
            case ElementOperation::INDEX:
                ss << "INDEX[" << opIndex_ << "]";
                break;
            case ElementOperation::INSERT:
                ss << "INSERT[" << opIndex_ << "]";
                break;
            case ElementOperation::DELETE:
                ss << "DELETE[" << opIndex_ << "]";
                break;
            default:
                break;
        }
    }
    
    if (!noValueStyles_.empty()) {
        ss << ", noValueStyles=" << noValueStyles_.size();
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