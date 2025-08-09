#pragma once

#include "StandardState.h"

namespace CHTL
{
    class JsState : public StandardState
    {
    public:
        // 占位：目前沿用标准处理
        const char* name() const noexcept override { return "JsState"; }
    };
}