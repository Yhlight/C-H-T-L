#pragma once

#include "JsBackend.h"

namespace CHTL
{
    class HeuristicJsBackend : public IJsBackend
    {
    public:
        JsFindings analyze(std::string_view js) const override;
    };
}