#pragma once

#include "BasicLexer.h"

#include <memory>

namespace CHTL
{
    class ConfigLexer : public BasicLexer
    {
    public:
        ConfigLexer() : BasicLexer(LanguageMode::Config) {}
        std::vector<Token> tokenize(const std::string& source) override;
    };
}