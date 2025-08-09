#pragma once

#include <vector>
#include <string>
#include <utility>

#include "../Common/Token.h"

namespace CHTL
{
    class BasicContext
    {
    public:
        virtual ~BasicContext() = default;

        void addToken(TokenType type, const std::string& lexeme,
                      std::uint32_t line, std::uint32_t column)
        {
            tokens_.emplace_back(type, lexeme, line, column);
        }

        void advance(char c)
        {
            if (c == '\n')
            {
                ++line_;
                column_ = 1;
            }
            else
            {
                ++column_;
            }
        }

        void advanceMultiple(const std::string& s)
        {
            for (char c : s) advance(c);
        }

        void newLine()
        {
            ++line_;
            column_ = 1;
        }

        std::pair<std::uint32_t, std::uint32_t> position() const noexcept
        {
            return { line_, column_ };
        }

        const std::vector<Token>& tokens() const noexcept { return tokens_; }
        std::vector<Token>& tokens() noexcept { return tokens_; }

    protected:
        std::vector<Token> tokens_ {};
        std::uint32_t line_ { 1 };
        std::uint32_t column_ { 1 };
    };
}