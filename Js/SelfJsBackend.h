#pragma once

#include "JsBackend.h"
#include "Lexer.h"
#include "Parser.h"

namespace CHTL
{
    class SelfJsBackend : public IJsBackend
    {
    public:
        JsFindings analyze(std::string_view js) const override;
    };
}