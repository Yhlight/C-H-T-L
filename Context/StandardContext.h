#pragma once

#include "BasicContext.h"

namespace CHTL
{
    class StandardContext : public BasicContext
    {
    public:
        // 未来可加入标准上下文专有配置
        ~StandardContext() override = default;
    };
}