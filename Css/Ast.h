#pragma once

#include <string>
#include <vector>

namespace CHTL
{
    struct CssRule
    {
        std::string selector;
        std::vector<std::pair<std::string,std::string>> declarations;
    };

    struct CssAtRule
    {
        std::string name; // @media/@supports/@container/@layer
        std::string prelude;
    };

    struct CssAst
    {
        std::vector<CssRule> rules;
        std::vector<CssAtRule> atRules;
    };
}