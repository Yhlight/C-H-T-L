#pragma once

#include "CssBackend.h"
#include "Lexer.h"
#include "Parser.h"

namespace CHTL
{
    class SelfCssBackend : public ICssBackend
    {
    public:
        CssFindings analyze(std::string_view css) const override;
    };
}