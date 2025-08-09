#pragma once

#include <string>
#include <cstdint>

namespace CHTL
{
    enum class JsTokenType : std::uint16_t
    {
        Identifier,
        Keyword,
        String,
        Number,
        Template,
        Punctuator,
        Eof
    };

    struct JsToken
    {
        JsTokenType type { JsTokenType::Eof };
        std::string lexeme {};
        std::uint32_t line { 1 };
        std::uint32_t column { 1 };
    };
}