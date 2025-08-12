#include "StyleNode.h"
#include <sstream>

namespace CHTL {

StyleNode::StyleNode()
    : Node(NodeType::STYLE) {
}

void StyleNode::accept(NodeVisitor* visitor) {
    if (visitor) {
        visitor->visitNode(this);
    }
}

void StyleNode::addInlineStyle(const std::string& property, const std::string& value) {
    if (!property.empty() && !value.empty()) {
        inlineStyles_[property] = value;
    }
}

void StyleNode::addClassSelector(const std::string& className) {
    if (!className.empty()) {
        classSelectors_.push_back(className);
    }
}

void StyleNode::addClassRule(const std::string& className, const std::string& property, const std::string& value) {
    if (!className.empty() && !property.empty() && !value.empty()) {
        classRules_[className][property] = value;
    }
}

void StyleNode::addIdSelector(const std::string& id) {
    if (!id.empty()) {
        idSelectors_.push_back(id);
    }
}

void StyleNode::addIdRule(const std::string& id, const std::string& property, const std::string& value) {
    if (!id.empty() && !property.empty() && !value.empty()) {
        idRules_[id][property] = value;
    }
}

NodePtr StyleNode::clone() const {
    auto cloned = std::make_shared<StyleNode>();
    cloned->inlineStyles_ = inlineStyles_;
    cloned->classSelectors_ = classSelectors_;
    cloned->classRules_ = classRules_;
    cloned->idSelectors_ = idSelectors_;
    cloned->idRules_ = idRules_;
    cloned->rawCSS_ = rawCSS_;
    cloned->scope_ = scope_;
    cloned->global_ = global_;
    
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

std::string StyleNode::toString() const {
    std::stringstream ss;
    ss << "StyleNode[";
    
    if (!inlineStyles_.empty()) {
        ss << "inline=" << inlineStyles_.size() << " rules";
    }
    
    if (!classSelectors_.empty()) {
        ss << ", classes=" << classSelectors_.size();
    }
    
    if (!idSelectors_.empty()) {
        ss << ", ids=" << idSelectors_.size();
    }
    
    if (!rawCSS_.empty()) {
        ss << ", hasRawCSS=true";
    }
    
    if (!scope_.empty()) {
        ss << ", scope=" << scope_;
    }
    
    ss << ", global=" << (global_ ? "true" : "false");
    ss << "]";
    
    return ss.str();
}

} // namespace CHTL