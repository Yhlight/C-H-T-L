#pragma once

#include <string>
#include <vector>

namespace CHTL
{
    struct JsFunctionDecl { std::string name; };
    struct JsClassDecl { std::string name; };
    struct JsImport { std::string source; };
    struct JsEventBind { std::string event; };
    struct JsSelector { std::string selector; };

    struct JsAst
    {
        std::vector<JsFunctionDecl> functions;
        std::vector<JsClassDecl> classes;
        std::vector<JsImport> imports;
        std::vector<JsEventBind> events;
        std::vector<JsSelector> selectors;
    };
}