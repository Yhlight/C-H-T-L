#include "StandardState.h"

#include <cctype>
#include <string>

#include "../Common/Token.h"
#include "../Common/GlobalMap.h"
#include "../Context/BasicContext.h"

namespace CHTL
{
    namespace
    {
        inline bool isIdentifierStart(char c)
        {
            return std::isalpha(static_cast<unsigned char>(c)) || c == '_' || c == '@' || c == '[' || c == ']';
        }

        inline bool isIdentifierPart(char c)
        {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-' || c == '@' || c == '.' || c == '[' || c == ']';
        }
    }

    bool StandardState::process(const std::string& src, std::size_t& index, BasicContext& context)
    {
        const std::size_t n = src.size();
        if (index >= n) return false;

        const char c = src[index];

        // 跳过空白
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            context.advance(c);
            ++index;
            return true;
        }

        // 单行注释 //
        if (c == '/' && index + 1 < n && src[index + 1] == '/')
        {
            while (index < n && src[index] != '\n') { ++index; }
            context.newLine();
            if (index < n) ++index;
            return true;
        }

        // 多行注释 /* ... */
        if (c == '/' && index + 1 < n && src[index + 1] == '*')
        {
            index += 2;
            while (index + 1 < n && !(src[index] == '*' && src[index + 1] == '/'))
            {
                if (src[index] == '\n') context.newLine();
                else context.advance(src[index]);
                ++index;
            }
            if (index + 1 < n) index += 2;
            return true;
        }

        // 字符串 "..." 或 '...'
        if (c == '"' || c == '\'')
        {
            const char quote = c;
            const auto [line, col] = context.position();
            std::string buf;
            ++index; // skip quote
            while (index < n)
            {
                char ch = src[index++];
                if (ch == '\\' && index < n)
                {
                    buf.push_back(ch);
                    buf.push_back(src[index++]);
                    continue;
                }
                if (ch == quote) break;
                if (ch == '\n') context.newLine(); else context.advance(ch);
                buf.push_back(ch);
            }
            context.addToken(TokenType::StringLiteral, buf, line, col);
            context.advance(quote);
            return true;
        }

        // 数字
        if (std::isdigit(static_cast<unsigned char>(c)))
        {
            const auto [line, col] = context.position();
            std::string buf;
            std::size_t i = index;
            while (i < n && (std::isdigit(static_cast<unsigned char>(src[i])) || src[i] == '.' ))
            {
                buf.push_back(src[i]);
                ++i;
            }
            context.addToken(TokenType::NumberLiteral, buf, line, col);
            context.advanceMultiple(buf);
            index = i;
            return true;
        }

        // 标识符 / 关键字 / 方括号指令
        if (isIdentifierStart(c))
        {
            const auto [line, col] = context.position();
            std::string buf;
            std::size_t i = index;
            while (i < n && isIdentifierPart(src[i]))
            {
                buf.push_back(src[i]);
                ++i;
            }

            // 将形如 [Template] 视作整体关键字
            // 使用全局映射做关键字识别
            auto mapped = GlobalMap::findTokenTypeByKeyword(buf);
            if (mapped)
            {
                context.addToken(*mapped, buf, line, col);
            }
            else
            {
                context.addToken(TokenType::Identifier, buf, line, col);
            }
            context.advanceMultiple(buf);
            index = i;
            return true;
        }

        // 符号
        {
            const auto [line, col] = context.position();
            TokenType type = TokenType::Unknown;
            std::string lex(1, c);
            switch (c)
            {
            case '{': type = TokenType::LBrace; break;
            case '}': type = TokenType::RBrace; break;
            case '[': type = TokenType::LBracket; break;
            case ']': type = TokenType::RBracket; break;
            case '(': type = TokenType::LParen; break;
            case ')': type = TokenType::RParen; break;
            case ':': type = TokenType::Colon; break;
            case ';': type = TokenType::Semicolon; break;
            case '=': type = TokenType::Equal; break;
            case ',': type = TokenType::Comma; break;
            case '.': type = TokenType::Dot; break;
            case '#': type = TokenType::Hash; break;
            case '@': type = TokenType::At; break;
            default: type = TokenType::Unknown; break;
            }
            context.addToken(type, lex, line, col);
            context.advance(c);
            ++index;
            return true;
        }
    }
}