#include "Parser.h"

namespace CHTL
{
    JsAst JsParser::parse(const std::vector<JsToken>& tokens) const
    {
        JsAst ast;
        const std::size_t n = tokens.size();
        for (std::size_t i = 0; i + 1 < n; ++i)
        {
            const auto& t = tokens[i];
            // function name
            if (t.type == JsTokenType::Keyword && t.lexeme == "function")
            {
                if (i + 1 < n && tokens[i+1].type == JsTokenType::Identifier)
                    ast.functions.push_back({ tokens[i+1].lexeme });
                continue;
            }
            // class name
            if (t.type == JsTokenType::Keyword && t.lexeme == "class")
            {
                if (i + 1 < n && tokens[i+1].type == JsTokenType::Identifier)
                    ast.classes.push_back({ tokens[i+1].lexeme });
                continue;
            }
            // import ... from "src"
            if (t.type == JsTokenType::Keyword && t.lexeme == "import")
            {
                for (std::size_t k = i + 1; k < n; ++k)
                {
                    if (tokens[k].type == JsTokenType::Keyword && tokens[k].lexeme == "from")
                    {
                        if (k + 1 < n && tokens[k+1].type == JsTokenType::String)
                            ast.imports.push_back({ tokens[k+1].lexeme });
                        break;
                    }
                    if (tokens[k].type == JsTokenType::String)
                    {
                        ast.imports.push_back({ tokens[k].lexeme });
                        break;
                    }
                    if (tokens[k].type == JsTokenType::Punctuator && tokens[k].lexeme == ";") break;
                }
                continue;
            }
            // .addEventListener('evt'
            if (t.type == JsTokenType::Identifier && t.lexeme == "addEventListener")
            {
                if (i > 0 && tokens[i-1].type == JsTokenType::Punctuator && tokens[i-1].lexeme == ".")
                {
                    for (std::size_t k = i + 1; k < n; ++k)
                    {
                        if (tokens[k].type == JsTokenType::String)
                        {
                            ast.events.push_back({ tokens[k].lexeme });
                            break;
                        }
                        if (tokens[k].type == JsTokenType::Punctuator && tokens[k].lexeme == ")") break;
                    }
                }
                continue;
            }
            // querySelector('...') / querySelectorAll('...')
            if (t.type == JsTokenType::Identifier && (t.lexeme == "querySelector" || t.lexeme == "querySelectorAll"))
            {
                for (std::size_t k = i + 1; k < n; ++k)
                {
                    if (tokens[k].type == JsTokenType::String)
                    {
                        ast.selectors.push_back({ tokens[k].lexeme });
                        break;
                    }
                    if (tokens[k].type == JsTokenType::Punctuator && tokens[k].lexeme == ")") break;
                }
                continue;
            }
        }
        return ast;
    }
}