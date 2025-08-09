#pragma once

#include "CssBackend.h"

namespace CHTL
{
    class HeuristicCssBackend : public ICssBackend
    {
    public:
        CssFindings analyze(std::string_view css) const override;
    };
}