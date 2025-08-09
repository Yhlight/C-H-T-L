#pragma once

#include <vector>
#include "Tokens.h"
#include "Ast.h"

namespace CHTL
{
    class JsParser
    {
    public:
        JsAst parse(const std::vector<JsToken>& tokens) const;
    };
}