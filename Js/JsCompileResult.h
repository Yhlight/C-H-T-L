#pragma once

#include <string>
#include <vector>
#include "JsFindings.h"

namespace CHTL
{
    struct JsCompileResult
    {
        std::string original;
        JsFindings findings;
        std::vector<std::string> warnings;
    };
}