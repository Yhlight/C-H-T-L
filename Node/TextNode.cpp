#include "TextNode.h"
#include <sstream>

namespace CHTL {

TextNode::TextNode(const std::string& text)
    : Node(NodeType::TEXT), text_(text) {
}

void TextNode::accept(NodeVisitor* visitor) {
    if (visitor) {
        visitor->visitNode(this);
    }
}

NodePtr TextNode::clone() const {
    auto cloned = std::make_shared<TextNode>(text_);
    cloned->raw_ = raw_;
    
    // 复制属性
    for (const auto& [key, value] : getAttributes()) {
        cloned->setAttribute(key, value);
    }
    
    return cloned;
}

std::string TextNode::toString() const {
    std::stringstream ss;
    ss << "TextNode[";
    
    // 显示文本内容的前20个字符
    if (text_.length() <= 20) {
        ss << "text=\"" << text_ << "\"";
    } else {
        ss << "text=\"" << text_.substr(0, 20) << "...\"";
    }
    
    ss << ", raw=" << (raw_ ? "true" : "false");
    ss << "]";
    
    return ss.str();
}

} // namespace CHTL