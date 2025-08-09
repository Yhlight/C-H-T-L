#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "../Segment/Segment.h"

namespace CHTL
{
    class BridgeScanner
    {
    public:
        // 简化：基于启发式规则扫描，将源拆分为 JS 段与 CHTL-JS 段
        std::vector<Segment> scan(std::string_view source) const;

    private:
        // 识别是否为 CHTL-JS 的启发式：
        // - 包含 {{ 与 }} 的增强选择器
        // - 存在 ->listen( 或 ->delegate(
        // - 出现 animate({ 的调用
        bool likelyChtlJs(std::string_view text) const;
    };
}