#include "v2/Node/Node.h"

namespace chtl::v2 {

// Node 基类方法
void Node::addChild(NodePtr child) {
    if (child) {
        child->setParent(this);
        children_.push_back(child);
    }
}

// Document 方法
void Document::accept(NodeVisitor& visitor) {
    visitor.visitDocument(this);
}

// Element 方法
void Element::accept(NodeVisitor& visitor) {
    visitor.visitElement(this);
}

// Text 方法
void Text::accept(NodeVisitor& visitor) {
    visitor.visitText(this);
}

// Style 方法
void Style::accept(NodeVisitor& visitor) {
    visitor.visitStyle(this);
}

// Script 方法
void Script::accept(NodeVisitor& visitor) {
    visitor.visitScript(this);
}

// Template 方法
void Template::accept(NodeVisitor& visitor) {
    visitor.visitTemplate(this);
}

// Reference 方法
void Reference::accept(NodeVisitor& visitor) {
    visitor.visitReference(this);
}

} // namespace chtl::v2