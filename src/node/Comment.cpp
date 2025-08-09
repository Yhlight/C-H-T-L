#include "node/Comment.h"

namespace chtl {

std::shared_ptr<Node> Comment::clone(bool deep) const {
    (void)deep; // 注释节点没有子节点
    return std::make_shared<Comment>(content_);
}

std::string Comment::toString() const {
    return "-- " + content_;
}

void Comment::accept(Visitor* visitor) {
    // 基础Visitor不支持Comment，需要使用ExtendedVisitor
    // 这里暂时留空，后续实现ExtendedVisitor时再处理
    (void)visitor;
}

} // namespace chtl