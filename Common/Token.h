#pragma once

#include <string>
#include <cstdint>

namespace CHTL
{
    enum class TokenType : std::uint16_t
    {
        // 标识与字面量
        Identifier,
        StringLiteral,
        NumberLiteral,
        RawLiteral, // 无引号字面量

        // 关键字
        KeywordText,
        KeywordStyle,
        KeywordTemplate,
        KeywordCustom,
        KeywordOrigin,
        KeywordImport,
        KeywordNamespace,
        KeywordConfiguration,
        KeywordInherit,
        KeywordDelete,
        KeywordInsert,
        KeywordAfter,
        KeywordBefore,
        KeywordReplace,
        KeywordAtTop,
        KeywordAtBottom,
        KeywordFrom,
        KeywordAs,
        KeywordExcept,

        // 符号
        LBrace,      // {
        RBrace,      // }
        LBracket,    // [
        RBracket,    // ]
        LParen,      // (
        RParen,      // )
        Colon,       // :
        Semicolon,   // ;
        Equal,       // =
        Comma,       // ,
        Dot,         // .
        Hash,        // #
        At,          // @

        // 其他
        EndOfFile,
        Unknown
    };

    class Token
    {
    public:
        Token() = default;

        Token(TokenType type,
              std::string lexeme,
              std::uint32_t line,
              std::uint32_t column)
            : type_(type), lexeme_(std::move(lexeme)), line_(line), column_(column) {}

        TokenType type() const noexcept { return type_; }
        const std::string& lexeme() const noexcept { return lexeme_; }
        std::uint32_t line() const noexcept { return line_; }
        std::uint32_t column() const noexcept { return column_; }

        void setType(TokenType type) noexcept { type_ = type; }
        void setLexeme(std::string value) { lexeme_ = std::move(value); }
        void setLine(std::uint32_t value) noexcept { line_ = value; }
        void setColumn(std::uint32_t value) noexcept { column_ = value; }

    private:
        TokenType type_ { TokenType::Unknown };
        std::string lexeme_ {};
        std::uint32_t line_ { 0 };
        std::uint32_t column_ { 0 };
    };
}