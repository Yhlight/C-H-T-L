#pragma once

#include <string>
#include <vector>
#include <set>

namespace CHTL
{
    struct JsFindings
    {
        std::set<std::string> functionNames;
        std::set<std::string> eventNames;      // addEventListener / listen keys
        std::set<std::string> selectors;       // from querySelector / {{ }}
    };
}