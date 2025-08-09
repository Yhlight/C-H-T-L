#pragma once

#include <string_view>
#include "JsFindings.h"

namespace CHTL
{
    class IJsBackend
    {
    public:
        virtual ~IJsBackend() = default;
        virtual JsFindings analyze(std::string_view js) const = 0;
    };
}