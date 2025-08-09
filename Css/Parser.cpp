#include "Parser.h"

namespace CHTL
{
    CssAst CssParser::parse(const std::vector<CssToken>& tokens) const
    {
        CssAst ast;
        const std::size_t n = tokens.size();
        std::size_t i = 0;
        auto at = [&](std::size_t k){ return k<n ? tokens[k] : CssToken{CssTokenType::Eof, "" ,0,0}; };

        while (i < n)
        {
            const auto& t = tokens[i];
            if (t.type == CssTokenType::Eof) break;

            if (t.type == CssTokenType::At)
            {
                // @name ... { or ;
                std::string name = t.lexeme; // includes '@'
                ++i;
                std::string prelude;
                while (i<n && tokens[i].type != CssTokenType::LBrace && tokens[i].type != CssTokenType::Semicolon)
                {
                    prelude += tokens[i].lexeme;
                    ++i;
                }
                ast.atRules.push_back({ name, prelude });
                // skip block or semicolon
                if (i<n && tokens[i].type == CssTokenType::LBrace)
                {
                    int depth=1; ++i;
                    while (i<n && depth>0)
                    {
                        if (tokens[i].type == CssTokenType::LBrace) ++depth;
                        else if (tokens[i].type == CssTokenType::RBrace) --depth;
                        ++i;
                    }
                }
                if (i<n && tokens[i].type == CssTokenType::Semicolon) ++i;
                continue;
            }

            // selector prelude until '{'
            std::string selector;
            while (i<n && tokens[i].type != CssTokenType::LBrace && tokens[i].type != CssTokenType::Eof)
            {
                selector += tokens[i].lexeme;
                ++i;
            }
            if (i<n && tokens[i].type == CssTokenType::LBrace)
            {
                ++i; // skip '{'
                CssRule rule; rule.selector = selector;
                while (i<n && tokens[i].type != CssTokenType::RBrace)
                {
                    // property
                    if (tokens[i].type == CssTokenType::Ident)
                    {
                        std::string prop = tokens[i].lexeme; ++i;
                        if (i<n && tokens[i].type == CssTokenType::Colon) ++i;
                        std::string value;
                        while (i<n && tokens[i].type != CssTokenType::Semicolon && tokens[i].type != CssTokenType::RBrace)
                        {
                            value += tokens[i].lexeme;
                            ++i;
                        }
                        rule.declarations.emplace_back(prop, value);
                        if (i<n && tokens[i].type == CssTokenType::Semicolon) ++i;
                        continue;
                    }
                    ++i; // skip unknown
                }
                if (i<n && tokens[i].type == CssTokenType::RBrace) ++i;
                ast.rules.push_back(std::move(rule));
                continue;
            }
            ++i;
        }
        return ast;
    }
}