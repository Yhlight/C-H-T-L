#pragma once

#include <string>
#include <vector>
#include "CssFindings.h"

namespace CHTL
{
    struct CssCompileResult
    {
        std::string original;
        CssFindings findings;
        std::vector<std::string> warnings;
    };
}