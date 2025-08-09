#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../Common/Types.h"
#include "../Common/Token.h"

namespace CHTL
{
    class BasicState;
    class BasicContext;

    class BasicLexer
    {
    public:
        explicit BasicLexer(LanguageMode mode)
            : mode_(mode)
        {}
        virtual ~BasicLexer() = default;

        virtual std::vector<Token> tokenize(const std::string& source) = 0;

        LanguageMode mode() const noexcept { return mode_; }

    protected:
        LanguageMode mode_;
    };
}