#pragma once

#include <string_view>
#include "CssFindings.h"

namespace CHTL
{
    class ICssBackend
    {
    public:
        virtual ~ICssBackend() = default;
        virtual CssFindings analyze(std::string_view css) const = 0;
    };
}