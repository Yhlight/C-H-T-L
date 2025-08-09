#pragma once

#include <string>
#include <vector>
#include <set>

namespace CHTL
{
    struct JsFindings
    {
        std::set<std::string> functionNames;
        std::set<std::string> classNames;
        std::set<std::string> importSources;
        std::set<std::string> eventNames;      // addEventListener keys
        std::set<std::string> selectors;       // from querySelector etc
    };
}