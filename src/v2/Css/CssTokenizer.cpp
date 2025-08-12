#include "v2/Css/CssTokenizer.h"
#include <cctype>
#include <algorithm>

namespace chtl::v2::css {

CssTokenizer::CssTokenizer(const std::string& input) 
    : input_(input) {
}

CssToken CssTokenizer::nextToken() {
    if (!tokenBuffer_.empty()) {
        CssToken token = tokenBuffer_.front();
        tokenBuffer_.erase(tokenBuffer_.begin());
        return token;
    }
    
    skipWhitespace();
    
    if (isAtEnd()) {
        return makeToken(CssTokenType::EOF_TOKEN);
    }
    
    start_ = current_;
    tokenStartLine_ = line_;
    tokenStartColumn_ = column_;
    
    char c = consume();
    
    // 单字符 tokens
    switch (c) {
        case ':': return makeToken(CssTokenType::COLON);
        case ';': return makeToken(CssTokenType::SEMICOLON);
        case ',': return makeToken(CssTokenType::COMMA);
        case '{': return makeToken(CssTokenType::LEFT_BRACE);
        case '}': return makeToken(CssTokenType::RIGHT_BRACE);
        case '(': return makeToken(CssTokenType::LEFT_PAREN);
        case ')': return makeToken(CssTokenType::RIGHT_PAREN);
        case '[': return makeToken(CssTokenType::LEFT_BRACKET);
        case ']': return makeToken(CssTokenType::RIGHT_BRACKET);
        case '.': {
            // 可能是类选择器或小数
            if (isDigit(peek())) {
                current_--; // 回退
                column_--;
                return scanNumber();
            }
            return makeToken(CssTokenType::DOT);
        }
        case '+': return makeToken(CssTokenType::PLUS);
        case '-': {
            // 可能是负数或 CSS 变量
            if (isDigit(peek()) || (peek() == '.' && isDigit(peekNext()))) {
                current_--; // 回退
                column_--;
                return scanNumber();
            } else if (peek() == '-') {
                // CSS 变量
                return scanIdent();
            }
            return makeToken(CssTokenType::MINUS);
        }
        case '*': return makeToken(CssTokenType::STAR);
        case '/': {
            if (peek() == '*') {
                scanComment();
                return nextToken(); // 跳过注释，返回下一个 token
            }
            return makeToken(CssTokenType::SLASH);
        }
        case '>': return makeToken(CssTokenType::GT);
        case '~': return makeToken(CssTokenType::TILDE);
        case '|': return makeToken(CssTokenType::PIPE);
        case '^': return makeToken(CssTokenType::CARET);
        case '$': return makeToken(CssTokenType::DOLLAR);
        case '=': return makeToken(CssTokenType::EQUALS);
        case '#': return scanHash();
        case '@': return scanAtKeyword();
        case '"': case '\'': return scanString(c);
        case '!': {
            // 检查 !important
            if (input_.substr(current_).find("important") == 0) {
                current_ += 9; // "important" 的长度
                column_ += 9;
                return makeToken(CssTokenType::IMPORTANT);
            }
            break;
        }
        case '<': {
            // 检查 <!--
            if (peek() == '!' && peekNext() == '-' && 
                current_ + 2 < input_.length() && input_[current_ + 2] == '-') {
                current_ += 3;
                column_ += 3;
                return makeToken(CssTokenType::CDO);
            }
            break;
        }
    }
    
    // 标识符或函数
    if (isIdentStart(c) || c == '-') {
        current_--; // 回退
        column_--;
        return scanIdent();
    }
    
    // 数字
    if (isDigit(c)) {
        current_--; // 回退
        column_--;
        return scanNumber();
    }
    
    // URL
    if (c == 'u' && peek() == 'r' && peekNext() == 'l') {
        current_--; // 回退
        column_--;
        return scanUrl();
    }
    
    return makeToken(CssTokenType::ERROR);
}

CssToken CssTokenizer::peekToken() {
    if (tokenBuffer_.empty()) {
        tokenBuffer_.push_back(nextToken());
    }
    return tokenBuffer_.front();
}

bool CssTokenizer::isAtEnd() const {
    return current_ >= input_.length();
}

std::vector<CssToken> CssTokenizer::tokenize() {
    std::vector<CssToken> tokens;
    CssToken token;
    do {
        token = nextToken();
        if (token.type != CssTokenType::WHITESPACE && 
            token.type != CssTokenType::COMMENT) {
            tokens.push_back(token);
        }
    } while (token.type != CssTokenType::EOF_TOKEN && 
             token.type != CssTokenType::ERROR);
    
    return tokens;
}

char CssTokenizer::consume() {
    if (isAtEnd()) return '\0';
    char c = input_[current_++];
    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }
    return c;
}

char CssTokenizer::peek() const {
    if (isAtEnd()) return '\0';
    return input_[current_];
}

char CssTokenizer::peekNext() const {
    if (current_ + 1 >= input_.length()) return '\0';
    return input_[current_ + 1];
}

void CssTokenizer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek())) {
        consume();
    }
}

void CssTokenizer::scanComment() {
    // 已经消费了 /*
    consume(); // *
    
    while (!isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
            consume(); // *
            consume(); // /
            break;
        }
        consume();
    }
}

CssToken CssTokenizer::scanIdent() {
    // 处理可能的 - 开头
    if (peek() == '-') {
        consume();
    }
    
    while (!isAtEnd() && isIdent(peek())) {
        consume();
    }
    
    std::string value = input_.substr(start_, current_ - start_);
    
    // 检查是否是函数
    if (peek() == '(') {
        return CssToken(CssTokenType::FUNCTION, value, tokenStartLine_, tokenStartColumn_);
    }
    
    return CssToken(CssTokenType::IDENT, value, tokenStartLine_, tokenStartColumn_);
}

CssToken CssTokenizer::scanNumber() {
    bool hasDecimal = false;
    
    // 可能的负号
    if (peek() == '-') {
        consume();
    }
    
    // 整数部分
    while (!isAtEnd() && isDigit(peek())) {
        consume();
    }
    
    // 小数部分
    if (peek() == '.' && isDigit(peekNext())) {
        hasDecimal = true;
        consume(); // .
        while (!isAtEnd() && isDigit(peek())) {
            consume();
        }
    }
    
    std::string numStr = input_.substr(start_, current_ - start_);
    double numValue = std::stod(numStr);
    
    // 检查单位或百分比
    if (peek() == '%') {
        consume();
        CssToken token(CssTokenType::PERCENTAGE, numStr + "%", 
                      tokenStartLine_, tokenStartColumn_);
        token.extra.numericValue = numValue;
        return token;
    }
    
    // 检查单位
    size_t unitStart = current_;
    if (isIdentStart(peek()) || peek() == '-') {
        while (!isAtEnd() && isIdent(peek())) {
            consume();
        }
        std::string unit = input_.substr(unitStart, current_ - unitStart);
        CssToken token(CssTokenType::DIMENSION, 
                      input_.substr(start_, current_ - start_),
                      tokenStartLine_, tokenStartColumn_);
        token.extra.numericValue = numValue;
        token.extra.unit = unit;
        return token;
    }
    
    CssToken token(CssTokenType::NUMBER, numStr, tokenStartLine_, tokenStartColumn_);
    token.extra.numericValue = numValue;
    return token;
}

CssToken CssTokenizer::scanString(char quote) {
    std::string value;
    
    while (!isAtEnd() && peek() != quote) {
        if (peek() == '\\') {
            consume(); // 转义字符
            if (!isAtEnd()) {
                value += consume();
            }
        } else {
            value += consume();
        }
    }
    
    if (!isAtEnd()) {
        consume(); // 结束引号
    }
    
    return CssToken(CssTokenType::STRING, value, tokenStartLine_, tokenStartColumn_);
}

CssToken CssTokenizer::scanUrl() {
    // 消费 "url"
    consume(); // u
    consume(); // r
    consume(); // l
    
    skipWhitespace();
    
    if (peek() != '(') {
        return CssToken(CssTokenType::ERROR, "url", tokenStartLine_, tokenStartColumn_);
    }
    consume(); // (
    
    skipWhitespace();
    
    std::string url;
    char quote = '\0';
    
    // URL 可能有引号也可能没有
    if (peek() == '"' || peek() == '\'') {
        quote = consume();
    }
    
    while (!isAtEnd()) {
        if (quote) {
            if (peek() == quote) {
                consume();
                break;
            }
        } else {
            if (peek() == ')') {
                break;
            }
        }
        
        if (peek() == '\\') {
            consume();
            if (!isAtEnd()) {
                url += consume();
            }
        } else {
            url += consume();
        }
    }
    
    skipWhitespace();
    
    if (peek() == ')') {
        consume();
    }
    
    return CssToken(CssTokenType::URL, url, tokenStartLine_, tokenStartColumn_);
}

CssToken CssTokenizer::scanHash() {
    // 已经消费了 #
    
    std::string value;
    bool isId = isIdentStart(peek());
    
    while (!isAtEnd() && (isIdent(peek()) || isDigit(peek()))) {
        value += consume();
    }
    
    CssToken token(CssTokenType::HASH, value, tokenStartLine_, tokenStartColumn_);
    token.extra.isId = isId;
    return token;
}

CssToken CssTokenizer::scanAtKeyword() {
    // 已经消费了 @
    
    std::string keyword;
    while (!isAtEnd() && isIdent(peek())) {
        keyword += consume();
    }
    
    return CssToken(CssTokenType::AT_KEYWORD, keyword, tokenStartLine_, tokenStartColumn_);
}

bool CssTokenizer::isIdentStart(char c) const {
    return std::isalpha(c) || c == '_' || c >= 128; // 支持 Unicode
}

bool CssTokenizer::isIdent(char c) const {
    return isIdentStart(c) || std::isdigit(c) || c == '-';
}

bool CssTokenizer::isDigit(char c) const {
    return std::isdigit(c);
}

CssToken CssTokenizer::makeToken(CssTokenType type) {
    std::string value = input_.substr(start_, current_ - start_);
    return CssToken(type, value, tokenStartLine_, tokenStartColumn_);
}

} // namespace chtl::v2::css