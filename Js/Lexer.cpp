#include "Lexer.h"

#include <cctype>
#include <unordered_set>

namespace CHTL
{
    namespace
    {
        const std::unordered_set<std::string> kKeywords = {
            "break","case","catch","class","const","continue","debugger","default","delete","do","else","export","extends","finally","for","function","if","import","in","instanceof","new","return","super","switch","this","throw","try","typeof","var","void","while","with","yield","let","static","async","await","of"
        };

        bool isIdentStart(char c)
        {
            return std::isalpha(static_cast<unsigned char>(c)) || c == '_' || c == '$';
        }
        bool isIdentPart(char c)
        {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '$';
        }
    }

    std::vector<JsToken> JsLexer::tokenize(std::string_view code) const
    {
        std::vector<JsToken> out;
        std::uint32_t line = 1, col = 1;
        const std::size_t n = code.size();
        std::size_t i = 0;
        auto emit = [&](JsTokenType t, std::string_view s, std::uint32_t l, std::uint32_t c){ out.push_back({t, std::string(s), l, c}); };
        auto adv = [&](char c){ if (c=='\n'){++line; col=1;} else {++col;} };

        while (i < n)
        {
            char c = code[i];
            if (std::isspace(static_cast<unsigned char>(c))) { adv(c); ++i; continue; }

            // comments
            if (c == '/' && i + 1 < n)
            {
                if (code[i+1] == '/') { i += 2; while (i < n && code[i] != '\n') ++i; continue; }
                if (code[i+1] == '*') { i += 2; while (i + 1 < n && !(code[i]=='*' && code[i+1]=='/')) { adv(code[i]); ++i; } if (i+1<n){ i+=2; } continue; }
            }

            // string
            if (c=='"' || c=='\'')
            {
                std::uint32_t l=line, c0=col; char q=c; ++i; adv(q);
                std::size_t start=i;
                while (i < n)
                {
                    char ch = code[i++]; adv(ch);
                    if (ch=='\\' && i<n) { adv(code[i]); ++i; continue; }
                    if (ch==q) break;
                }
                emit(JsTokenType::String, code.substr(start, (i>start?i-1:start)-start), l, c0);
                continue;
            }

            // template literal (skip content roughly)
            if (c=='`')
            {
                std::uint32_t l=line, c0=col; ++i; adv('`');
                std::size_t depth=1;
                while (i<n && depth>0)
                {
                    char ch = code[i++]; adv(ch);
                    if (ch=='`') { --depth; break; }
                    if (ch=='\\' && i<n) { adv(code[i]); ++i; }
                }
                emit(JsTokenType::Template, "`, template", l, c0);
                continue;
            }

            // number
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                std::uint32_t l=line, c0=col; std::size_t start=i;
                while (i<n && (std::isalnum(static_cast<unsigned char>(code[i])) || code[i]=='.' || code[i]=='x' || code[i]=='X' || code[i]=='b' || code[i]=='B' || code[i]=='o' || code[i]=='O' || code[i]=='n')) { adv(code[i]); ++i; }
                emit(JsTokenType::Number, code.substr(start, i-start), l, c0);
                continue;
            }

            // identifier/keyword
            if (isIdentStart(c))
            {
                std::uint32_t l=line, c0=col; std::size_t start=i; adv(c); ++i;
                while (i<n && isIdentPart(code[i])) { adv(code[i]); ++i; }
                std::string_view sv = code.substr(start, i-start);
                if (kKeywords.count(std::string(sv))) emit(JsTokenType::Keyword, sv, l, c0);
                else emit(JsTokenType::Identifier, sv, l, c0);
                continue;
            }

            // punctuator
            {
                std::uint32_t l=line, c0=col; adv(c); ++i;
                emit(JsTokenType::Punctuator, code.substr(i-1,1), l, c0);
            }
        }

        out.push_back({JsTokenType::Eof, "", line, col});
        return out;
    }
}