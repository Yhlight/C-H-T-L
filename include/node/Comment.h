#ifndef CHTL_COMMENT_H
#define CHTL_COMMENT_H

#include "node/Node.h"

namespace chtl {

// Comment节点 - CHTL的 "--" 注释
class Comment : public Node {
private:
    std::string content_;
    
public:
    Comment(const std::string& content = "")
        : Node(NodeType::COMMENT, "#comment"), content_(content) {}
    
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_COMMENT_H