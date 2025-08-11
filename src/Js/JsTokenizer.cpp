#include "Js/JsTokenizer.h"
#include <unordered_map>

namespace chtl {

JsTokenizer::JsTokenizer() 
    : position_(0), currentLine_(1), currentColumn_(1) {
}

std::vector<JsToken> JsTokenizer::tokenize(const std::string& js) {
    reset(js);
    std::vector<JsToken> tokens;
    
    while (hasMoreTokens()) {
        JsToken token = nextToken();
        if (token.type != JsTokenType::WHITESPACE) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

void JsTokenizer::reset(const std::string& js) {
    input_ = js;
    position_ = 0;
    currentLine_ = 1;
    currentColumn_ = 1;
}

JsToken JsTokenizer::nextToken() {
    skipWhitespace();
    
    if (!hasMoreTokens()) {
        return JsToken(JsTokenType::EOF_TOKEN, "", currentLine_, currentColumn_);
    }
    
    char c = currentChar();
    
    // 注释
    if (c == '/' && (peekChar() == '/' || peekChar() == '*')) {
        return readComment();
    }
    
    // 字符串
    if (c == '"' || c == '\'' || c == '`') {
        return readString();
    }
    
    // 数字
    if (std::isdigit(c)) {
        return readNumber();
    }
    
    // 标识符或关键字
    if (isIdentifierStart(c)) {
        return readIdentifier();
    }
    
    // 运算符和标点
    return readOperator();
}

bool JsTokenizer::hasMoreTokens() const {
    return position_ < input_.length();
}

char JsTokenizer::currentChar() const {
    if (position_ >= input_.length()) {
        return '\0';
    }
    return input_[position_];
}

char JsTokenizer::peekChar(int offset) const {
    size_t pos = position_ + offset;
    if (pos >= input_.length()) {
        return '\0';
    }
    return input_[pos];
}

void JsTokenizer::advance() {
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

void JsTokenizer::skipWhitespace() {
    while (position_ < input_.length() && std::isspace(input_[position_])) {
        if (input_[position_] == '\n') {
            currentLine_++;
            currentColumn_ = 1;
        } else {
            currentColumn_++;
        }
        position_++;
    }
}

void JsTokenizer::skipComment() {
    if (currentChar() == '/' && peekChar() == '/') {
        // 单行注释
        while (position_ < input_.length() && currentChar() != '\n') {
            advance();
        }
    } else if (currentChar() == '/' && peekChar() == '*') {
        // 多行注释
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

JsToken JsTokenizer::readIdentifier() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    while (isIdentifierPart(currentChar())) {
        value += currentChar();
        advance();
    }
    
    // 检查是否是关键字
    JsTokenType type = getKeywordType(value);
    if (type == JsTokenType::UNKNOWN) {
        type = JsTokenType::IDENTIFIER;
    }
    
    return JsToken(type, value, startLine, startCol);
}

JsToken JsTokenizer::readNumber() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    while (std::isdigit(currentChar()) || currentChar() == '.') {
        value += currentChar();
        advance();
    }
    
    // 科学记数法
    if (currentChar() == 'e' || currentChar() == 'E') {
        value += currentChar();
        advance();
        if (currentChar() == '+' || currentChar() == '-') {
            value += currentChar();
            advance();
        }
        while (std::isdigit(currentChar())) {
            value += currentChar();
            advance();
        }
    }
    
    // BigInt
    if (currentChar() == 'n') {
        value += currentChar();
        advance();
    }
    
    return JsToken(JsTokenType::NUMBER, value, startLine, startCol);
}

JsToken JsTokenizer::readString() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    char quote = currentChar();
    std::string value;
    
    advance(); // 跳过引号
    
    if (quote == '`') {
        // 模板字符串
        while (position_ < input_.length() && currentChar() != quote) {
            if (currentChar() == '\\') {
                advance();
                if (position_ < input_.length()) {
                    advance();
                }
            } else {
                value += currentChar();
                advance();
            }
        }
        if (currentChar() == quote) {
            advance();
        }
        return JsToken(JsTokenType::TEMPLATE_STRING, value, startLine, startCol);
    } else {
        // 普通字符串
        while (position_ < input_.length() && currentChar() != quote) {
            if (currentChar() == '\\') {
                advance();
                if (position_ < input_.length()) {
                    advance();
                }
            } else {
                value += currentChar();
                advance();
            }
        }
        if (currentChar() == quote) {
            advance();
        }
        return JsToken(JsTokenType::STRING, value, startLine, startCol);
    }
}

JsToken JsTokenizer::readTemplateString() {
    // 已在readString中处理
    return readString();
}

JsToken JsTokenizer::readOperator() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    char c = currentChar();
    std::string value(1, c);
    JsTokenType type = JsTokenType::UNKNOWN;
    
    advance();
    
    switch (c) {
        case '+':
            if (currentChar() == '+') {
                value += currentChar();
                advance();
                type = JsTokenType::INCREMENT;
            } else if (currentChar() == '=') {
                value += currentChar();
                advance();
                type = JsTokenType::ASSIGN;
            } else {
                type = JsTokenType::PLUS;
            }
            break;
        
        case '-':
            if (currentChar() == '-') {
                value += currentChar();
                advance();
                type = JsTokenType::DECREMENT;
            } else if (currentChar() == '=') {
                value += currentChar();
                advance();
                type = JsTokenType::ASSIGN;
            } else {
                type = JsTokenType::MINUS;
            }
            break;
        
        case '=':
            if (currentChar() == '=') {
                value += currentChar();
                advance();
                if (currentChar() == '=') {
                    value += currentChar();
                    advance();
                    type = JsTokenType::STRICT_EQUAL;
                } else {
                    type = JsTokenType::EQUAL;
                }
            } else if (currentChar() == '>') {
                value += currentChar();
                advance();
                type = JsTokenType::ARROW;
            } else {
                type = JsTokenType::ASSIGN;
            }
            break;
        
        case '?':
            if (currentChar() == '.') {
                value += currentChar();
                advance();
                type = JsTokenType::OPTIONAL_CHAIN;
            } else if (currentChar() == '?') {
                value += currentChar();
                advance();
                type = JsTokenType::NULLISH_COALESCE;
            } else {
                type = JsTokenType::QUESTION;
            }
            break;
        
        case '(': type = JsTokenType::LEFT_PAREN; break;
        case ')': type = JsTokenType::RIGHT_PAREN; break;
        case '{': type = JsTokenType::LEFT_BRACE; break;
        case '}': type = JsTokenType::RIGHT_BRACE; break;
        case '[': type = JsTokenType::LEFT_BRACKET; break;
        case ']': type = JsTokenType::RIGHT_BRACKET; break;
        case ';': type = JsTokenType::SEMICOLON; break;
        case ',': type = JsTokenType::COMMA; break;
        case '.': type = JsTokenType::DOT; break;
        case ':': type = JsTokenType::COLON; break;
        case '*': type = JsTokenType::MULTIPLY; break;
        case '/': type = JsTokenType::DIVIDE; break;
        case '%': type = JsTokenType::MODULO; break;
        case '<': type = JsTokenType::LESS_THAN; break;
        case '>': type = JsTokenType::GREATER_THAN; break;
        case '&': type = JsTokenType::BITWISE_AND; break;
        case '|': type = JsTokenType::BITWISE_OR; break;
        case '^': type = JsTokenType::BITWISE_XOR; break;
        case '~': type = JsTokenType::BITWISE_NOT; break;
        case '!': type = JsTokenType::LOGICAL_NOT; break;
    }
    
    return JsToken(type, value, startLine, startCol);
}

JsToken JsTokenizer::readComment() {
    int startLine = currentLine_;
    int startCol = currentColumn_;
    std::string value;
    
    if (currentChar() == '/' && peekChar() == '/') {
        // 单行注释
        advance(); // /
        advance(); // /
        while (position_ < input_.length() && currentChar() != '\n') {
            value += currentChar();
            advance();
        }
    } else if (currentChar() == '/' && peekChar() == '*') {
        // 多行注释
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
    }
    
    return JsToken(JsTokenType::COMMENT, value, startLine, startCol);
}

bool JsTokenizer::isIdentifierStart(char c) const {
    return std::isalpha(c) || c == '_' || c == '$';
}

bool JsTokenizer::isIdentifierPart(char c) const {
    return std::isalnum(c) || c == '_' || c == '$';
}

JsTokenType JsTokenizer::getKeywordType(const std::string& identifier) const {
    static const std::unordered_map<std::string, JsTokenType> keywords = {
        {"function", JsTokenType::FUNCTION},
        {"class", JsTokenType::CLASS},
        {"const", JsTokenType::CONST},
        {"let", JsTokenType::LET},
        {"var", JsTokenType::VAR},
        {"if", JsTokenType::IF},
        {"else", JsTokenType::ELSE},
        {"for", JsTokenType::FOR},
        {"while", JsTokenType::WHILE},
        {"do", JsTokenType::DO},
        {"return", JsTokenType::RETURN},
        {"break", JsTokenType::BREAK},
        {"continue", JsTokenType::CONTINUE},
        {"switch", JsTokenType::SWITCH},
        {"case", JsTokenType::CASE},
        {"default", JsTokenType::DEFAULT},
        {"try", JsTokenType::TRY},
        {"catch", JsTokenType::CATCH},
        {"finally", JsTokenType::FINALLY},
        {"throw", JsTokenType::THROW},
        {"new", JsTokenType::NEW},
        {"this", JsTokenType::THIS},
        {"super", JsTokenType::SUPER},
        {"import", JsTokenType::IMPORT},
        {"export", JsTokenType::EXPORT},
        {"async", JsTokenType::ASYNC},
        {"await", JsTokenType::AWAIT},
        {"yield", JsTokenType::YIELD}
    };
    
    auto it = keywords.find(identifier);
    if (it != keywords.end()) {
        return it->second;
    }
    
    return JsTokenType::UNKNOWN;
}

} // namespace chtl