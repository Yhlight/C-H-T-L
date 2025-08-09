#pragma once

#include <string>
#include "Node.h"

namespace CHTL
{
    enum class CommentType
    {
        Line,       // // 注释
        Block,      // /* ... */ 注释
        Generator   // -- 生成器识别的注释
    };

    class Comment : public Node
    {
    public:
        Comment() = default;
        Comment(CommentType type, std::string content)
            : type_(type), content_(std::move(content)) {}

        CommentType type() const noexcept { return type_; }
        const std::string& content() const noexcept { return content_; }

        void setType(CommentType t) noexcept { type_ = t; }
        void setContent(std::string c) { content_ = std::move(c); }

    private:
        CommentType type_ { CommentType::Line };
        std::string content_ {};
    };
}