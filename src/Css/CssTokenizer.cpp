#include "Css/CssTokenizer.h"

namespace chtl {

CssTokenizer::CssTokenizer() 
    : position_(0), currentLine_(1), currentColumn_(1) {
}

std::vector<CssToken> CssTokenizer::tokenize(const std::string& css) {
    reset(css);
    std::vector<CssToken> tokens;
    
    while (hasMoreTokens()) {
        CssToken token = nextToken();
        if (token.type != CssTokenType::WHITESPACE) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

void CssTokenizer::reset(const std::string& css) {
    input_ = css;
    position_ = 0;
    currentLine_ = 1;
    currentColumn_ = 1;
}

CssToken CssTokenizer::nextToken() {
    skipWhitespace();
    
    if (!hasMoreTokens()) {
        return CssToken(CssTokenType::EOF_TOKEN, "", currentLine_, currentColumn_);
    }
    
    char c = currentChar();
    
    // 注释
    if (c == '/' && peekChar() == '*') {
        return readComment();
    }
    
    // 字符串
    if (c == '"' || c == '\'') {
        return readString();
    }
    
    // 数字
    if (std::isdigit(c) || (c == '.' && std::isdigit(peekChar()))) {
        return readNumber();
    }
    
    // @规则
    if (c == '@') {
        return readAtRule();
    }
    
    // 颜色
    if (c == '#') {
        return readColor();
    }
    
    // 选择器或属性
    if (std::isalpha(c) || c == '_' || c == '-' || c == '.' || c == '#' || c == ':' || c == '*') {
        return readSelector();
    }
    
    // 单字符token
    CssToken token(CssTokenType::UNKNOWN, std::string(1, c), currentLine_, currentColumn_);
    
    switch (c) {
        case '{': token.type = CssTokenType::LEFT_BRACE; break;
        case '}': token.type = CssTokenType::RIGHT_BRACE; break;
        case '[': token.type = CssTokenType::LEFT_BRACKET; break;
        case ']': token.type = CssTokenType::RIGHT_BRACKET; break;
        case '(': token.type = CssTokenType::LEFT_PAREN; break;
        case ')': token.type = CssTokenType::RIGHT_PAREN; break;
        case ';': token.type = CssTokenType::SEMICOLON; break;
        case ':': token.type = CssTokenType::COLON; break;
        case ',': token.type = CssTokenType::COMMA; break;
        case '+': token.type = CssTokenType::PLUS; break;
        case '-': token.type = CssTokenType::MINUS; break;
        case '*': token.type = CssTokenType::MULTIPLY; break;
        case '/': token.type = CssTokenType::DIVIDE; break;
    }
    
    advance();
    return token;
}

bool CssTokenizer::hasMoreTokens() const {
    return position_ < input_.length();
}

char CssTokenizer::currentChar() const {
    if (position_ >= input_.length()) {
        return '\0';
    }
    return input_[position_];
}

char CssTokenizer::peekChar(int offset) const {
    size_t pos = position_ + offset;
    if (pos >= input_.length()) {
        return '\0';
    }
    return input_[pos];
}

void CssTokenizer::advance() {
    if (position_ < input_.length()) {
        if (input_[position_] == '\n') {
            currentLine_++;
            currentColumn_ = 1;
        } else {
            currentColumn_++;
        }
        position_++;
    }
}

void CssTokenizer::skipWhitespace() {
    while (position_ < input_.length() && std::isspace(input_[position_])) {
        advance();
    }
}

void CssTokenizer::skipComment() {
    if (currentChar() == '/' && peekChar() == '*') {
        advance(); // /
        advance(); // *
        
        while (position_ < input_.length() - 1) {
            if (currentChar() == '*' && peekChar() == '/') {
                advance(); // *
                advance(); // /
                break;
            }
            advance();
        }
    }
}

CssToken CssTokenizer::readComment() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    advance(); // /
    advance(); // *
    
    while (position_ < input_.length() - 1) {
        if (currentChar() == '*' && peekChar() == '/') {
            advance(); // *
            advance(); // /
            break;
        }
        value += currentChar();
        advance();
    }
    
    return CssToken(CssTokenType::COMMENT, value, startLine, startCol);
}

CssToken CssTokenizer::readString() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    char quote = currentChar();
    std::string value;
    
    advance(); // 跳过引号
    
    while (position_ < input_.length() && currentChar() != quote) {
        if (currentChar() == '\\' && peekChar() == quote) {
            value += quote;
            advance();
            advance();
        } else {
            value += currentChar();
            advance();
        }
    }
    
    if (currentChar() == quote) {
        advance(); // 跳过结束引号
    }
    
    return CssToken(CssTokenType::STRING, value, startLine, startCol);
}

CssToken CssTokenizer::readNumber() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    // 读取数字部分
    while (std::isdigit(currentChar()) || currentChar() == '.') {
        value += currentChar();
        advance();
    }
    
    // 读取单位
    std::string unit;
    if (std::isalpha(currentChar()) || currentChar() == '%') {
        while (std::isalpha(currentChar()) || currentChar() == '%') {
            unit += currentChar();
            advance();
        }
        return CssToken(CssTokenType::UNIT, value + unit, startLine, startCol);
    }
    
    return CssToken(CssTokenType::NUMBER, value, startLine, startCol);
}

CssToken CssTokenizer::readSelector() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    while (isValidSelectorChar(currentChar())) {
        value += currentChar();
        advance();
    }
    
    return CssToken(CssTokenType::SELECTOR, value, startLine, startCol);
}

CssToken CssTokenizer::readProperty() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    while (isValidPropertyChar(currentChar())) {
        value += currentChar();
        advance();
    }
    
    return CssToken(CssTokenType::PROPERTY, value, startLine, startCol);
}

CssToken CssTokenizer::readValue() {
    // 简单实现
    return readSelector();
}

CssToken CssTokenizer::readAtRule() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    advance(); // @
    
    while (std::isalpha(currentChar()) || currentChar() == '-') {
        value += currentChar();
        advance();
    }
    
    return CssToken(CssTokenType::AT_RULE, "@" + value, startLine, startCol);
}

CssToken CssTokenizer::readFunction() {
    // 简单实现
    return readSelector();
}

CssToken CssTokenizer::readColor() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    value += currentChar(); // #
    advance();
    
    while (std::isxdigit(currentChar())) {
        value += currentChar();
        advance();
    }
    
    return CssToken(CssTokenType::COLOR, value, startLine, startCol);
}

bool CssTokenizer::isValidPropertyChar(char c) const {
    return std::isalnum(c) || c == '-' || c == '_';
}

bool CssTokenizer::isValidSelectorChar(char c) const {
    return std::isalnum(c) || c == '-' || c == '_' || c == '.' || 
           c == '#' || c == ':' || c == '[' || c == ']' || 
           c == '>' || c == '+' || c == '~' || c == '*' || c == ' ';
}

} // namespace chtl