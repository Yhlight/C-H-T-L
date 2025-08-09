#pragma once

#include <string>
#include <cstdint>

namespace CHTL
{
    enum class CssTokenType : std::uint16_t
    {
        Ident,
        String,
        Number,
        Hash,
        Delim,
        Colon,
        Semicolon,
        Comma,
        LBrace,
        RBrace,
        At,
        Eof
    };

    struct CssToken
    {
        CssTokenType type { CssTokenType::Eof };
        std::string lexeme {};
        std::uint32_t line { 1 };
        std::uint32_t column { 1 };
    };
}