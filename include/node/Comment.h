#ifndef CHTL_COMMENT_H
#define CHTL_COMMENT_H

#include "node/Node.h"

namespace chtl {

// Comment节点 - 支持三种注释类型：单行注释(//)、多行注释(/**/)、HTML注释(<!---->)
class Comment : public Node {
public:
    enum class CommentType {
        SINGLE_LINE,    // //
        MULTI_LINE,     // /* */
        HTML            // <!-- -->
    };
    
private:
    CommentType commentType_;
    std::string content_;
    
public:
    Comment(CommentType type, const std::string& content = "")
        : Node(NodeType::COMMENT, "#comment"), commentType_(type), content_(content) {}
    
    CommentType getCommentType() const { return commentType_; }
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_COMMENT_H