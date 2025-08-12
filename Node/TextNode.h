#ifndef CHTL_NODE_TEXTNODE_H
#define CHTL_NODE_TEXTNODE_H

#include "Node.h"

namespace CHTL {

/**
 * 文本节点 - 表示纯文本内容
 */
class TextNode : public Node {
public:
    explicit TextNode(const std::string& text);
    ~TextNode() = default;
    
    // 实现visitor模式
    void accept(NodeVisitor* visitor) override;
    
    // 文本内容
    const std::string& getText() const { return text_; }
    void setText(const std::string& text) { text_ = text; }
    
    // 是否是原始文本（不进行HTML转义）
    void setRaw(bool raw) { raw_ = raw; }
    bool isRaw() const { return raw_; }
    
    // 克隆
    NodePtr clone() const override;
    
    // 调试信息
    std::string toString() const override;
    
private:
    std::string text_;
    bool raw_ = false;
};

} // namespace CHTL

#endif // CHTL_NODE_TEXTNODE_H