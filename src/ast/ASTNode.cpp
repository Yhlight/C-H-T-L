#include "ASTNode.h"

namespace CHTL {

// ASTNode基类实现
ASTNode::ASTNode(ASTNodeType type) : type_(type) {}

void ASTNode::addChild(std::shared_ptr<ASTNode> child) {
    if (child) {
        children_.push_back(child);
    }
}

void ASTNode::setAttribute(const std::string& key, const std::string& value) {
    attributes_[key] = value;
}

std::string ASTNode::getAttribute(const std::string& key) const {
    auto it = attributes_.find(key);
    return (it != attributes_.end()) ? it->second : "";
}

bool ASTNode::hasAttribute(const std::string& key) const {
    return attributes_.find(key) != attributes_.end();
}

void ASTNode::setLocation(int line, int column) {
    line_ = line;
    column_ = column;
}

// ElementNode实现
ElementNode::ElementNode(const std::string& tagName) 
    : ASTNode(ASTNodeType::ELEMENT), tagName_(tagName) {}

void ElementNode::accept(ASTVisitor* visitor) {
    visitor->visitElement(this);
}

// TextNode实现
TextNode::TextNode(const std::string& text) 
    : ASTNode(ASTNodeType::TEXT_NODE), text_(text) {}

void TextNode::accept(ASTVisitor* visitor) {
    visitor->visitText(this);
}

// StyleBlockNode实现
StyleBlockNode::StyleBlockNode() : ASTNode(ASTNodeType::STYLE_BLOCK) {}

void StyleBlockNode::accept(ASTVisitor* visitor) {
    visitor->visitStyleBlock(this);
}

void StyleBlockNode::addInlineStyle(const std::string& property, const std::string& value) {
    inlineStyles_[property] = value;
}

void StyleBlockNode::addClassSelector(const std::string& className) {
    classSelectors_.push_back(className);
}

void StyleBlockNode::addIdSelector(const std::string& id) {
    idSelectors_.push_back(id);
}

// ScriptBlockNode实现
ScriptBlockNode::ScriptBlockNode(const std::string& code, bool isCHTLJS) 
    : ASTNode(ASTNodeType::SCRIPT_BLOCK), code_(code), isCHTLJS_(isCHTLJS) {}

void ScriptBlockNode::accept(ASTVisitor* visitor) {
    visitor->visitScriptBlock(this);
}

// TemplateNode实现
TemplateNode::TemplateNode(TemplateType templateType, const std::string& name)
    : ASTNode(ASTNodeType::TEMPLATE_DECLARATION), templateType_(templateType), name_(name) {}

void TemplateNode::accept(ASTVisitor* visitor) {
    visitor->visitTemplate(this);
}

// CustomNode实现
CustomNode::CustomNode(CustomType customType, const std::string& name)
    : ASTNode(ASTNodeType::CUSTOM_DECLARATION), customType_(customType), name_(name) {}

void CustomNode::accept(ASTVisitor* visitor) {
    visitor->visitCustom(this);
}

// 工厂函数
std::shared_ptr<ASTNode> createASTNode(ASTNodeType type) {
    switch (type) {
        case ASTNodeType::ELEMENT:
            return std::make_shared<ElementNode>("");
        case ASTNodeType::TEXT_NODE:
            return std::make_shared<TextNode>("");
        case ASTNodeType::STYLE_BLOCK:
            return std::make_shared<StyleBlockNode>();
        case ASTNodeType::SCRIPT_BLOCK:
            return std::make_shared<ScriptBlockNode>("", false);
        case ASTNodeType::TEMPLATE_DECLARATION:
            return std::make_shared<TemplateNode>(TemplateNode::TemplateType::STYLE, "");
        case ASTNodeType::CUSTOM_DECLARATION:
            return std::make_shared<CustomNode>(CustomNode::CustomType::STYLE, "");
        default:
            return nullptr;
    }
}

} // namespace CHTL