#pragma once

#include "StandardContext.h"

namespace CHTL
{
    class ChtlContext : public StandardContext
    {
    public:
        // 未来可加入 CHTL 特有配置，如 Name 组选项等
        ~ChtlContext() override = default;
    };
}