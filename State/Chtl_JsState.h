#pragma once

#include "JsState.h"

namespace CHTL
{
    class Chtl_JsState : public JsState
    {
    public:
        // 占位：目前沿用 JS 处理
        const char* name() const noexcept override { return "Chtl_JsState"; }
    };
}