#pragma once

#include <vector>
#include "Tokens.h"
#include "Ast.h"

namespace CHTL
{
    class CssParser
    {
    public:
        CssAst parse(const std::vector<CssToken>& tokens) const;
    };
}