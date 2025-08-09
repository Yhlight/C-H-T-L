#pragma once

#include <string>
#include <vector>
#include <string_view>
#include "Tokens.h"

namespace CHTL
{
    class JsLexer
    {
    public:
        std::vector<JsToken> tokenize(std::string_view code) const;
    };
}