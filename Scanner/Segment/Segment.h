#pragma once

#include <string>
#include <cstddef>

namespace CHTL
{
    enum class SegmentKind
    {
        JavaScript,
        ChtlJs
    };

    struct Segment
    {
        SegmentKind kind { SegmentKind::JavaScript };
        std::size_t startOffset { 0 };
        std::size_t endOffset { 0 }; // [start, end)
        std::string_view view;        // 指向原文的视图
    };
}