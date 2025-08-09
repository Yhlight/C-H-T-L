#include "SelfJsBackend.h"

namespace CHTL
{
    JsFindings SelfJsBackend::analyze(std::string_view js) const
    {
        JsLexer lex;
        auto tokens = lex.tokenize(js);
        JsParser parser;
        auto ast = parser.parse(tokens);
        JsFindings out;
        for (const auto& f : ast.functions) out.functionNames.insert(f.name);
        for (const auto& c : ast.classes) out.classNames.insert(c.name);
        for (const auto& im : ast.imports) out.importSources.insert(im.source);
        for (const auto& e : ast.events) out.eventNames.insert(e.event);
        for (const auto& s : ast.selectors) out.selectors.insert(s.selector);
        return out;
    }
}