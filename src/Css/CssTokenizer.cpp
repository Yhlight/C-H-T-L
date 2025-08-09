#include "Css/CssTokenizer.h"
#include <cctype>

namespace chtl {
namespace css {

CssTokenizer::CssTokenizer() 
    : position_(0), line_(1), column_(1) {
}

void CssTokenizer::initialize(const std::string& input) {
    input_ = input;
    position_ = 0;
    line_ = 1;
    column_ = 1;
}

char CssTokenizer::current() const {
    if (position_ >= input_.length()) {
        return '\0';
    }
    return input_[position_];
}

char CssTokenizer::peek(size_t offset) const {
    size_t pos = position_ + offset;
    if (pos >= input_.length()) {
        return '\0';
    }
    return input_[pos];
}

void CssTokenizer::advance() {
    if (position_ < input_.length()) {
        if (input_[position_] == '\n') {
            line_++;
            column_ = 1;
        } else {
            column_++;
        }
        position_++;
    }
}

bool CssTokenizer::isAtEnd() const {
    return position_ >= input_.length();
}

void CssTokenizer::skipWhitespace() {
    while (!isAtEnd() && isWhitespace(current())) {
        advance();
    }
}

void CssTokenizer::skipComment() {
    if (current() == '/' && peek() == '*') {
        advance(); // skip /
        advance(); // skip *
        
        while (!isAtEnd() && !(current() == '*' && peek() == '/')) {
            advance();
        }
        
        if (!isAtEnd()) {
            advance(); // skip *
            advance(); // skip /
        }
    }
}

CssToken CssTokenizer::nextToken() {
    skipWhitespace();
    skipComment();
    
    if (isAtEnd()) {
        return CssToken(CssTokenType::EOF_TOKEN, "", line_, column_);
    }
    
    size_t startLine = line_;
    size_t startColumn = column_;
    char c = current();
    
    // 单字符标记
    switch (c) {
        case '{':
            advance();
            return CssToken(CssTokenType::LEFT_BRACE, "{", startLine, startColumn);
        case '}':
            advance();
            return CssToken(CssTokenType::RIGHT_BRACE, "}", startLine, startColumn);
        case '(':
            advance();
            return CssToken(CssTokenType::LEFT_PAREN, "(", startLine, startColumn);
        case ')':
            advance();
            return CssToken(CssTokenType::RIGHT_PAREN, ")", startLine, startColumn);
        case '[':
            advance();
            return CssToken(CssTokenType::LEFT_BRACKET, "[", startLine, startColumn);
        case ']':
            advance();
            return CssToken(CssTokenType::RIGHT_BRACKET, "]", startLine, startColumn);
        case ';':
            advance();
            return CssToken(CssTokenType::SEMICOLON, ";", startLine, startColumn);
        case ',':
            advance();
            return CssToken(CssTokenType::COMMA, ",", startLine, startColumn);
        case '.':
            advance();
            return CssToken(CssTokenType::DOT, ".", startLine, startColumn);
        case '#':
            advance();
            return CssToken(CssTokenType::HASH, "#", startLine, startColumn);
        case '&':
            advance();
            return CssToken(CssTokenType::AMPERSAND, "&", startLine, startColumn);
        case '*':
            advance();
            return CssToken(CssTokenType::STAR, "*", startLine, startColumn);
        case '+':
            advance();
            return CssToken(CssTokenType::PLUS, "+", startLine, startColumn);
        case '-':
            advance();
            return CssToken(CssTokenType::MINUS, "-", startLine, startColumn);
        case '/':
            advance();
            return CssToken(CssTokenType::SLASH, "/", startLine, startColumn);
        case '%':
            advance();
            return CssToken(CssTokenType::PERCENT, "%", startLine, startColumn);
    }
    
    // 冒号和双冒号
    if (c == ':') {
        advance();
        if (current() == ':') {
            advance();
            return CssToken(CssTokenType::DOUBLE_COLON, "::", startLine, startColumn);
        }
        return CssToken(CssTokenType::COLON, ":", startLine, startColumn);
    }
    
    // !important
    if (c == '!') {
        advance();
        std::string value = "!";
        skipWhitespace();
        if (isIdentifierStart(current())) {
            std::string ident = readIdentifier().value;
            if (ident == "important") {
                return CssToken(CssTokenType::IMPORTANT, "!important", startLine, startColumn);
            }
        }
        return CssToken(CssTokenType::EXCLAMATION, "!", startLine, startColumn);
    }
    
    // @规则
    if (c == '@') {
        return readAtRule();
    }
    
    // 字符串
    if (c == '"' || c == '\'') {
        return readString(c);
    }
    
    // 数字
    if (isDigit(c) || (c == '.' && isDigit(peek()))) {
        return readNumber();
    }
    
    // 标识符
    if (isIdentifierStart(c)) {
        return readIdentifier();
    }
    
    // 未知字符
    advance();
    return CssToken(CssTokenType::UNKNOWN, std::string(1, c), startLine, startColumn);
}

CssToken CssTokenizer::readString(char quote) {
    size_t startLine = line_;
    size_t startColumn = column_;
    std::string value;
    
    advance(); // 跳过开始引号
    
    while (!isAtEnd() && current() != quote) {
        if (current() == '\\' && peek() == quote) {
            advance(); // 跳过反斜杠
            value += quote;
            advance();
        } else {
            value += current();
            advance();
        }
    }
    
    if (!isAtEnd()) {
        advance(); // 跳过结束引号
    }
    
    return CssToken(CssTokenType::STRING, value, startLine, startColumn);
}

CssToken CssTokenizer::readNumber() {
    size_t startLine = line_;
    size_t startColumn = column_;
    std::string value;
    
    // 整数部分
    while (isDigit(current())) {
        value += current();
        advance();
    }
    
    // 小数部分
    if (current() == '.' && isDigit(peek())) {
        value += current();
        advance();
        while (isDigit(current())) {
            value += current();
            advance();
        }
    }
    
    // 单位
    if (isIdentifierStart(current())) {
        while (isIdentifierPart(current())) {
            value += current();
            advance();
        }
    }
    
    return CssToken(CssTokenType::NUMBER, value, startLine, startColumn);
}

CssToken CssTokenizer::readIdentifier() {
    size_t startLine = line_;
    size_t startColumn = column_;
    std::string value;
    
    while (isIdentifierPart(current())) {
        value += current();
        advance();
    }
    
    // 检查是否是url()函数
    if (value == "url" && current() == '(') {
        return readUrl();
    }
    
    // 检查是否是其他函数
    if (current() == '(') {
        return CssToken(CssTokenType::FUNCTION, value, startLine, startColumn);
    }
    
    return CssToken(CssTokenType::IDENTIFIER, value, startLine, startColumn);
}

CssToken CssTokenizer::readUrl() {
    size_t startLine = line_;
    size_t startColumn = column_;
    std::string value = "url";
    
    advance(); // 跳过 (
    value += "(";
    
    skipWhitespace();
    
    // URL可以是带引号或不带引号的
    if (current() == '"' || current() == '\'') {
        char quote = current();
        value += quote;
        advance();
        
        while (!isAtEnd() && current() != quote) {
            value += current();
            advance();
        }
        
        if (!isAtEnd()) {
            value += current();
            advance();
        }
    } else {
        // 不带引号的URL
        while (!isAtEnd() && current() != ')' && !isWhitespace(current())) {
            value += current();
            advance();
        }
    }
    
    skipWhitespace();
    
    if (current() == ')') {
        value += ')';
        advance();
    }
    
    return CssToken(CssTokenType::URL, value, startLine, startColumn);
}

CssToken CssTokenizer::readAtRule() {
    size_t startLine = line_;
    size_t startColumn = column_;
    std::string value = "@";
    
    advance(); // 跳过 @
    
    // 读取@规则名称
    while (isIdentifierPart(current())) {
        value += current();
        advance();
    }
    
    return CssToken(CssTokenType::AT, value, startLine, startColumn);
}

bool CssTokenizer::isIdentifierStart(char c) {
    return std::isalpha(c) || c == '_' || c == '-';
}

bool CssTokenizer::isIdentifierPart(char c) {
    return std::isalnum(c) || c == '_' || c == '-';
}

bool CssTokenizer::isDigit(char c) {
    return std::isdigit(c);
}

bool CssTokenizer::isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

} // namespace css
} // namespace chtl