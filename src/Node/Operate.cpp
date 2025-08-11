#include "Node/Operate.h"
#include <sstream>

namespace chtl {

std::string Operate::getOperationTypeString() const {
    switch (operationType_) {
        case OperationType::INSERT:  return "insert";
        case OperationType::DELETE:  return "delete";
        case OperationType::REPLACE: return "replace";
        case OperationType::MOVE:    return "move";
        default: return "unknown";
    }
}

std::string Operate::getPositionString() const {
    switch (position_) {
        case Position::BEFORE:  return "before";
        case Position::AFTER:   return "after";
        case Position::AT:      return "at";
        case Position::TOP:     return "top";
        case Position::BOTTOM:  return "bottom";
        case Position::DEFAULT: return "";
        default: return "";
    }
}

std::shared_ptr<Node> Operate::clone(bool deep) const {
    auto cloned = std::make_shared<Operate>(operationType_);
    cloned->position_ = position_;
    cloned->target_ = target_;
    cloned->selector_ = selector_;
    cloned->constraints_ = constraints_;
    
    if (content_) {
        cloned->content_ = deep ? content_->clone(true) : content_;
    }
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Operate::toString() const {
    std::stringstream ss;
    
    // 操作类型
    ss << getOperationTypeString();
    
    // 位置
    std::string pos = getPositionString();
    if (!pos.empty()) {
        ss << " " << pos;
    }
    
    // 目标
    if (!target_.empty()) {
        ss << " " << target_;
    }
    
    // 选择器
    if (!selector_.empty()) {
        ss << " " << selector_;
    }
    
    // 约束
    if (!constraints_.empty()) {
        ss << " except ";
        bool first = true;
        for (const auto& constraint : constraints_) {
            if (!first) ss << ", ";
            ss << constraint;
            first = false;
        }
    }
    
    // 内容
    if (operationType_ != OperationType::DELETE && (content_ || !children_.empty())) {
        ss << "\n{";
        
        if (content_) {
            std::string contentStr = content_->toString();
            std::istringstream iss(contentStr);
            std::string line;
            while (std::getline(iss, line)) {
                ss << "\n  " << line;
            }
        }
        
        for (const auto& child : children_) {
            std::string childStr = child->toString();
            std::istringstream iss(childStr);
            std::string line;
            while (std::getline(iss, line)) {
                ss << "\n  " << line;
            }
        }
        
        ss << "\n}";
    } else {
        ss << ";";
    }
    
    return ss.str();
}

void Operate::accept(Visitor* visitor) {
    // 基础Visitor不支持Operate，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl