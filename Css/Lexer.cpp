#include "Lexer.h"

#include <cctype>

namespace CHTL
{
    std::vector<CssToken> CssLexer::tokenize(std::string_view css) const
    {
        std::vector<CssToken> out;
        std::uint32_t line = 1, col = 1;
        const std::size_t n = css.size();
        std::size_t i = 0;
        auto emit = [&](CssTokenType t, std::string_view s, std::uint32_t l, std::uint32_t c){ out.push_back({t, std::string(s), l, c}); };
        auto adv = [&](char c){ if (c=='\n'){++line; col=1;} else {++col;} };

        while (i < n)
        {
            char c = css[i];
            if (std::isspace(static_cast<unsigned char>(c))) { adv(c); ++i; continue; }

            // comments /* ... */
            if (c=='/' && i+1<n && css[i+1]=='*')
            {
                i+=2; while (i+1<n && !(css[i]=='*' && css[i+1]=='/')) { adv(css[i]); ++i; } if (i+1<n) i+=2; continue;
            }

            if (c=='{' ) { emit(CssTokenType::LBrace, css.substr(i,1), line, col); adv(c); ++i; continue; }
            if (c=='}' ) { emit(CssTokenType::RBrace, css.substr(i,1), line, col); adv(c); ++i; continue; }
            if (c==':' ) { emit(CssTokenType::Colon,  css.substr(i,1), line, col); adv(c); ++i; continue; }
            if (c==';' ) { emit(CssTokenType::Semicolon, css.substr(i,1), line, col); adv(c); ++i; continue; }
            if (c==',' ) { emit(CssTokenType::Comma, css.substr(i,1), line, col); adv(c); ++i; continue; }
            if (c=='#' ) { std::uint32_t l=line, c0=col; std::size_t start=i++; adv('#'); while (i<n && (std::isalnum(static_cast<unsigned char>(css[i])) || css[i]=='-' || css[i]=='_')) { adv(css[i]); ++i; } emit(CssTokenType::Hash, css.substr(start, i-start), l, c0); continue; }
            if (c=='@' ) { std::uint32_t l=line, c0=col; std::size_t start=i++; adv('@'); while (i<n && (std::isalnum(static_cast<unsigned char>(css[i])) || css[i]=='-' )) { adv(css[i]); ++i; } emit(CssTokenType::At, css.substr(start, i-start), l, c0); continue; }
            if (c=='\'' || c=='"') { std::uint32_t l=line, c0=col; char q=c; ++i; adv(q); std::size_t start=i; while (i<n){ char ch=css[i++]; adv(ch); if (ch=='\\' && i<n){ adv(css[i]); ++i; continue; } if (ch==q) break; } emit(CssTokenType::String, css.substr(start, (i>start?i-1:start)-start), l, c0); continue; }
            if (std::isdigit(static_cast<unsigned char>(c))) { std::uint32_t l=line, c0=col; std::size_t start=i; while (i<n && (std::isalnum(static_cast<unsigned char>(css[i])) || css[i]=='.' || css[i]=='%')) { adv(css[i]); ++i; } emit(CssTokenType::Number, css.substr(start, i-start), l, c0); continue; }
            if (std::isalpha(static_cast<unsigned char>(c)) || c=='-' || c=='_') { std::uint32_t l=line, c0=col; std::size_t start=i; while (i<n && (std::isalnum(static_cast<unsigned char>(css[i])) || css[i]=='-' || css[i]=='_' )) { adv(css[i]); ++i; } emit(CssTokenType::Ident, css.substr(start, i-start), l, c0); continue; }

            // delim
            { std::uint32_t l=line, c0=col; emit(CssTokenType::Delim, css.substr(i,1), l, c0); adv(c); ++i; }
        }
        out.push_back({CssTokenType::Eof, "", line, col});
        return out;
    }
}