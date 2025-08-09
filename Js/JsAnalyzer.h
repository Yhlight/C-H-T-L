#pragma once

#include <string>
#include <string_view>

#include "JsFindings.h"

namespace CHTL
{
    class JsAnalyzer
    {
    public:
        JsFindings analyze(std::string_view js) const;
    };
}