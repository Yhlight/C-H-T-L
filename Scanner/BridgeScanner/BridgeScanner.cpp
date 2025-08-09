#include "BridgeScanner.h"

#include <string_view>

namespace CHTL
{
    bool BridgeScanner::likelyChtlJs(std::string_view text) const
    {
        // 简单启发式：出现特征即判为 CHTL-JS
        return (text.find("{{") != std::string_view::npos && text.find("}}") != std::string_view::npos)
            || (text.find("->listen(") != std::string_view::npos)
            || (text.find("->delegate(") != std::string_view::npos)
            || (text.find("animate(") != std::string_view::npos);
    }

    std::vector<Segment> BridgeScanner::scan(std::string_view source) const
    {
        std::vector<Segment> segments;
        if (source.empty()) return segments;

        std::size_t begin = 0;
        std::size_t cursor = 0;
        SegmentKind currentKind = SegmentKind::JavaScript; // 默认 JS

        auto flush = [&](std::size_t flushPos)
        {
            if (flushPos > begin)
            {
                segments.push_back({ currentKind, begin, flushPos, source.substr(begin, flushPos - begin) });
                begin = flushPos;
            }
        };

        // 基于行的扫描，遇到“像 CHTL-JS”的行则切换，遇到“不像”的行切回
        while (cursor < source.size())
        {
            std::size_t eol = source.find('\n', cursor);
            if (eol == std::string_view::npos) eol = source.size();

            std::string_view line = source.substr(cursor, eol - cursor);
            bool isChtl = likelyChtlJs(line);
            SegmentKind lineKind = isChtl ? SegmentKind::ChtlJs : SegmentKind::JavaScript;

            if (lineKind != currentKind)
            {
                flush(cursor);
                currentKind = lineKind;
            }

            cursor = (eol < source.size()) ? eol + 1 : eol; // 包含换行
        }

        flush(source.size());
        return segments;
    }
}