#pragma once

#include <vector>
#include <string_view>
#include "Tokens.h"

namespace CHTL
{
    class CssLexer
    {
    public:
        std::vector<CssToken> tokenize(std::string_view css) const;
    };
}