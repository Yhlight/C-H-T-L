#include "SelfCssBackend.h"

namespace CHTL
{
    CssFindings SelfCssBackend::analyze(std::string_view css) const
    {
        CssLexer lex; auto tokens = lex.tokenize(css);
        CssParser parser; auto ast = parser.parse(tokens);
        CssFindings out;
        // From selectors, collect .class and #id rough scan
        for (const auto& rule : ast.rules)
        {
            const std::string& sel = rule.selector;
            for (std::size_t i=0;i<sel.size();++i)
            {
                if (sel[i]=='.' || sel[i]=='#')
                {
                    std::size_t j=i+1; std::string name;
                    while (j<sel.size() && (std::isalnum(static_cast<unsigned char>(sel[j])) || sel[j]=='-' || sel[j]=='_')) name.push_back(sel[j++]);
                    if (!name.empty())
                    {
                        if (sel[i]=='.') { if (out.classSelectors.insert(name).second) out.all.push_back({CssSymbolKind::ClassSelector, name}); }
                        else { if (out.idSelectors.insert(name).second) out.all.push_back({CssSymbolKind::IdSelector, name}); }
                    }
                    i=j;
                }
            }
            // properties
            for (const auto& [prop, _] : rule.declarations)
            {
                if (out.propertyNames.insert(prop).second) out.all.push_back({CssSymbolKind::PropertyName, prop});
            }
        }
        return out;
    }
}