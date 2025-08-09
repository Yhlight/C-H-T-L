#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

namespace CHTL
{
    enum class CssSymbolKind
    {
        ClassSelector,
        IdSelector,
        PropertyName
    };

    struct CssFinding
    {
        CssSymbolKind kind;
        std::string name;
    };

    struct CssFindings
    {
        std::set<std::string> classSelectors;
        std::set<std::string> idSelectors;
        std::set<std::string> propertyNames;
        std::vector<CssFinding> all;
    };
}