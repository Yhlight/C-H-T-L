#pragma once

#include <string>

namespace CHTL
{
    class BasicContext; // forward declaration

    class BasicState
    {
    public:
        virtual ~BasicState() = default;

        // 处理从 src[index] 开始的一个 token，成功则前进 index，失败返回 false
        virtual bool process(const std::string& src,
                             std::size_t& index,
                             BasicContext& context) = 0;

        virtual const char* name() const noexcept = 0;
    };
}