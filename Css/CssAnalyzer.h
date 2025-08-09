#pragma once

#include <string>
#include <string_view>

#include "CssFindings.h"

namespace CHTL
{
    class CssAnalyzer
    {
    public:
        CssFindings analyze(std::string_view css) const;
    };
}