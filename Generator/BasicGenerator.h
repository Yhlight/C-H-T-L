#pragma once

#include <string>
#include <memory>

namespace CHTL
{
    class Node;

    class BasicGenerator
    {
    public:
        virtual ~BasicGenerator() = default;

        // 简化：生成目标文本（例如 HTML/CSS/JS 或中间代码）
        virtual std::string generate(const Node& root) = 0;
    };
}