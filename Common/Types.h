#pragma once

#include <cstdint>

namespace CHTL
{
    enum class LanguageMode : std::uint8_t
    {
        Standard = 0,
        Chtl,
        Css,
        Js,
        ChtlJs,
        Config
    };
}