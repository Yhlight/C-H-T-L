#include "v2/Js/JsTokenizer.h"
#include <cctype>
#include <algorithm>
#include <unordered_map>

namespace chtl::v2::js {

// Static keyword map
static const std::unordered_map<std::string, JsTokenType> keywords = {
    {"const", JsTokenType::CONST},
    {"let", JsTokenType::LET},
    {"var", JsTokenType::VAR},
    {"function", JsTokenType::FUNCTION},
    {"class", JsTokenType::CLASS},
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
    {"yield", JsTokenType::YIELD},
    {"typeof", JsTokenType::TYPEOF},
    {"instanceof", JsTokenType::INSTANCEOF},
    {"in", JsTokenType::IN},
    {"of", JsTokenType::OF},
    {"delete", JsTokenType::DELETE},
    {"void", JsTokenType::VOID},
    {"true", JsTokenType::TRUE},
    {"false", JsTokenType::FALSE},
    {"null", JsTokenType::NULL_TOKEN},
    {"undefined", JsTokenType::UNDEFINED}
};

JsTokenizer::JsTokenizer(const std::string& input) 
    : input_(input), current_(0), line_(1), column_(1) {}

JsToken JsTokenizer::nextToken() {
    skipWhitespace();
    
    if (isAtEnd()) {
        return makeToken(JsTokenType::EOF_TOKEN);
    }
    
    start_ = current_;
    tokenStartLine_ = line_;
    tokenStartColumn_ = column_;
    
    char c = consume();
    
    // Comments
    if (c == '/' && (peek() == '/' || peek() == '*')) {
        if (scanComment()) {
            return JsToken(JsTokenType::COMMENT, 
                         input_.substr(start_, current_ - start_),
                         tokenStartLine_, tokenStartColumn_);
        }
    }
    
    // Identifiers and keywords
    if (isIdentStart(c)) {
        current_--; // Put back the character
        column_--;
        return scanIdentifier();
    }
    
    // Numbers
    if (isDigit(c)) {
        current_--; // Put back the character
        column_--;
        return scanNumber();
    }
    
    // Strings
    if (c == '"' || c == '\'') {
        return scanString(c);
    }
    
    // Template literals
    if (c == '`') {
        return scanTemplate();
    }
    
    // Single and multi-character tokens
    switch (c) {
        case '(': return makeToken(JsTokenType::LEFT_PAREN);
        case ')': return makeToken(JsTokenType::RIGHT_PAREN);
        case '{': return makeToken(JsTokenType::LEFT_BRACE);
        case '}': return makeToken(JsTokenType::RIGHT_BRACE);
        case '[': return makeToken(JsTokenType::LEFT_BRACKET);
        case ']': return makeToken(JsTokenType::RIGHT_BRACKET);
        case ',': return makeToken(JsTokenType::COMMA);
        case ';': return makeToken(JsTokenType::SEMICOLON);
        case ':': return makeToken(JsTokenType::COLON);
        
        case '.':
            if (peek() == '.' && peekNext() == '.') {
                consume(); consume();
                return makeToken(JsTokenType::SPREAD);
            }
            return makeToken(JsTokenType::DOT);
            
        case '+':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::PLUS_EQUALS);
            } else if (peek() == '+') {
                consume();
                return makeToken(JsTokenType::INCREMENT);
            }
            return makeToken(JsTokenType::PLUS);
            
        case '-':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::MINUS_EQUALS);
            } else if (peek() == '-') {
                consume();
                return makeToken(JsTokenType::DECREMENT);
            }
            return makeToken(JsTokenType::MINUS);
            
        case '*':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::STAR_EQUALS);
            } else if (peek() == '*') {
                consume();
                if (peek() == '=') {
                    consume();
                    return makeToken(JsTokenType::POWER_EQUALS);
                }
                return makeToken(JsTokenType::POWER);
            }
            return makeToken(JsTokenType::STAR);
            
        case '/':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::SLASH_EQUALS);
            }
            // Check for regex
            if (isRegexContext()) {
                return scanRegex();
            }
            return makeToken(JsTokenType::SLASH);
            
        case '%':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::PERCENT_EQUALS);
            }
            return makeToken(JsTokenType::PERCENT);
            
        case '=':
            if (peek() == '=') {
                consume();
                if (peek() == '=') {
                    consume();
                    return makeToken(JsTokenType::TRIPLE_EQUALS);
                }
                return makeToken(JsTokenType::EQUALS_EQUALS);
            } else if (peek() == '>') {
                consume();
                return makeToken(JsTokenType::ARROW);
            }
            return makeToken(JsTokenType::EQUALS);
            
        case '!':
            if (peek() == '=') {
                consume();
                if (peek() == '=') {
                    consume();
                    return makeToken(JsTokenType::NOT_TRIPLE_EQUALS);
                }
                return makeToken(JsTokenType::NOT_EQUALS);
            }
            return makeToken(JsTokenType::LOGICAL_NOT);
            
        case '<':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::LESS_EQUALS);
            } else if (peek() == '<') {
                consume();
                return makeToken(JsTokenType::LEFT_SHIFT);
            }
            return makeToken(JsTokenType::LESS);
            
        case '>':
            if (peek() == '=') {
                consume();
                return makeToken(JsTokenType::GREATER_EQUALS);
            } else if (peek() == '>') {
                consume();
                if (peek() == '>') {
                    consume();
                    return makeToken(JsTokenType::UNSIGNED_RIGHT_SHIFT);
                }
                return makeToken(JsTokenType::RIGHT_SHIFT);
            }
            return makeToken(JsTokenType::GREATER);
            
        case '&':
            if (peek() == '&') {
                consume();
                return makeToken(JsTokenType::LOGICAL_AND);
            }
            return makeToken(JsTokenType::BITWISE_AND);
            
        case '|':
            if (peek() == '|') {
                consume();
                return makeToken(JsTokenType::LOGICAL_OR);
            }
            return makeToken(JsTokenType::BITWISE_OR);
            
        case '^':
            return makeToken(JsTokenType::BITWISE_XOR);
            
        case '~':
            return makeToken(JsTokenType::BITWISE_NOT);
            
        case '?':
            if (peek() == '?') {
                consume();
                return makeToken(JsTokenType::NULLISH_COALESCING);
            } else if (peek() == '.') {
                consume();
                return makeToken(JsTokenType::OPTIONAL_CHAIN);
            }
            return makeToken(JsTokenType::QUESTION);
            
        default:
            return makeToken(JsTokenType::ERROR);
    }
}

JsToken JsTokenizer::peekToken() {
    size_t savedCurrent = current_;
    int savedLine = line_;
    int savedColumn = column_;
    
    JsToken token = nextToken();
    
    current_ = savedCurrent;
    line_ = savedLine;
    column_ = savedColumn;
    
    return token;
}

bool JsTokenizer::isAtEnd() const {
    return current_ >= input_.size();
}

std::vector<JsToken> JsTokenizer::tokenize() {
    std::vector<JsToken> tokens;
    current_ = 0;
    line_ = 1;
    column_ = 1;
    
    while (!isAtEnd()) {
        JsToken token = nextToken();
        if (token.type != JsTokenType::WHITESPACE && 
            token.type != JsTokenType::COMMENT) {
            tokens.push_back(token);
        }
        if (token.type == JsTokenType::EOF_TOKEN) {
            break;
        }
    }
    
    return tokens;
}

char JsTokenizer::consume() {
    char c = input_[current_++];
    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }
    return c;
}

char JsTokenizer::peek() const {
    if (isAtEnd()) return '\0';
    return input_[current_];
}

char JsTokenizer::peekNext() const {
    if (current_ + 1 >= input_.size()) return '\0';
    return input_[current_ + 1];
}

char JsTokenizer::peekAhead(int n) const {
    if (current_ + n >= input_.size()) return '\0';
    return input_[current_ + n];
}

void JsTokenizer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
            consume();
        } else {
            break;
        }
    }
}

bool JsTokenizer::scanComment() {
    if (peek() == '/') {
        // Line comment
        consume(); // second /
        while (peek() != '\n' && !isAtEnd()) {
            consume();
        }
        return true;
    } else if (peek() == '*') {
        // Block comment
        consume(); // *
        while (!isAtEnd()) {
            if (peek() == '*' && peekNext() == '/') {
                consume(); // *
                consume(); // /
                return true;
            }
            consume();
        }
        // Unterminated comment
        return true;
    }
    return false;
}

JsToken JsTokenizer::scanIdentifier() {
    while (isIdent(peek())) {
        consume();
    }
    
    std::string value = input_.substr(start_, current_ - start_);
    JsTokenType type = getKeywordType(value);
    
    JsToken token = makeToken(type);
    token.value = value;
    return token;
}

JsToken JsTokenizer::scanNumber() {
    bool isFloat = false;
    
    // Integer part
    while (isDigit(peek())) {
        consume();
    }
    
    // Decimal part
    if (peek() == '.' && isDigit(peekNext())) {
        isFloat = true;
        consume(); // .
        while (isDigit(peek())) {
            consume();
        }
    }
    
    // Exponent part
    if (peek() == 'e' || peek() == 'E') {
        isFloat = true;
        consume();
        if (peek() == '+' || peek() == '-') {
            consume();
        }
        while (isDigit(peek())) {
            consume();
        }
    }
    
    // BigInt suffix
    bool isBigInt = false;
    if (peek() == 'n' && !isFloat) {
        consume();
        isBigInt = true;
    }
    
    std::string value = input_.substr(start_, current_ - start_);
    JsToken token = makeToken(JsTokenType::NUMBER);
    token.value = value;
    token.extra.isFloat = isFloat;
    token.extra.isBigInt = isBigInt;
    
    if (!isBigInt) {
        try {
            token.extra.numericValue = std::stod(value);
        } catch (...) {
            token.extra.numericValue = 0.0;
        }
    }
    
    return token;
}

JsToken JsTokenizer::scanString(char quote) {
    while (peek() != quote && !isAtEnd()) {
        if (peek() == '\n') {
            // Unterminated string
            return makeToken(JsTokenType::ERROR);
        }
        if (peek() == '\\') {
            consume(); // backslash
            if (!isAtEnd()) {
                consume(); // escaped character
            }
        } else {
            consume();
        }
    }
    
    if (isAtEnd()) {
        return makeToken(JsTokenType::ERROR);
    }
    
    consume(); // closing quote
    
    JsToken token = makeToken(JsTokenType::STRING);
    // Extract string content without quotes
    token.value = input_.substr(start_ + 1, current_ - start_ - 2);
    return token;
}

JsToken JsTokenizer::scanTemplate() {
    while (peek() != '`' && !isAtEnd()) {
        if (peek() == '\\') {
            consume(); // backslash
            if (!isAtEnd()) {
                consume(); // escaped character
            }
        } else if (peek() == '$' && peekNext() == '{') {
            // Template expression - for now, we'll include it in the template
            // A full implementation would handle nested expressions
            consume(); // $
            consume(); // {
            int braceCount = 1;
            while (braceCount > 0 && !isAtEnd()) {
                if (peek() == '{') braceCount++;
                else if (peek() == '}') braceCount--;
                consume();
            }
        } else {
            consume();
        }
    }
    
    if (isAtEnd()) {
        return makeToken(JsTokenType::ERROR);
    }
    
    consume(); // closing backtick
    
    JsToken token = makeToken(JsTokenType::TEMPLATE);
    // Extract template content without backticks
    token.value = input_.substr(start_ + 1, current_ - start_ - 2);
    return token;
}

JsToken JsTokenizer::scanRegex() {
    // Scan regex pattern
    while (peek() != '/' && !isAtEnd()) {
        if (peek() == '\\') {
            consume(); // backslash
            if (!isAtEnd()) {
                consume(); // escaped character
            }
        } else if (peek() == '\n') {
            // Unterminated regex
            return makeToken(JsTokenType::ERROR);
        } else {
            consume();
        }
    }
    
    if (isAtEnd()) {
        return makeToken(JsTokenType::ERROR);
    }
    
    consume(); // closing /
    
    // Scan flags
    std::string flags;
    while (isAlpha(peek())) {
        flags += peek();
        consume();
    }
    
    JsToken token = makeToken(JsTokenType::REGEX);
    // Extract regex without slashes
    size_t patternStart = start_ + 1;
    size_t patternEnd = current_ - 1 - flags.length();
    token.value = input_.substr(patternStart, patternEnd - patternStart);
    token.extra.flags = flags;
    return token;
}

bool JsTokenizer::isRegexContext() const {
    // Simple heuristic: regex is likely after certain tokens
    if (tokenBuffer_.empty() && lastToken_.type == JsTokenType::ERROR) {
        return true; // Beginning of input
    }
    
    switch (lastToken_.type) {
        case JsTokenType::EQUALS:
        case JsTokenType::LEFT_PAREN:
        case JsTokenType::LEFT_BRACKET:
        case JsTokenType::LOGICAL_NOT:
        case JsTokenType::BITWISE_NOT:
        case JsTokenType::LEFT_BRACE:
        case JsTokenType::SEMICOLON:
        case JsTokenType::COMMA:
        case JsTokenType::COLON:
        case JsTokenType::PLUS:
        case JsTokenType::MINUS:
        case JsTokenType::STAR:
        case JsTokenType::SLASH:
        case JsTokenType::PERCENT:
        case JsTokenType::LESS:
        case JsTokenType::GREATER:
        case JsTokenType::BITWISE_AND:
        case JsTokenType::BITWISE_OR:
        case JsTokenType::BITWISE_XOR:
        case JsTokenType::QUESTION:
        case JsTokenType::RETURN:
        case JsTokenType::THROW:
        case JsTokenType::NEW:
        case JsTokenType::DELETE:
        case JsTokenType::VOID:
        case JsTokenType::TYPEOF:
        case JsTokenType::INSTANCEOF:
        case JsTokenType::IN:
            return true;
        default:
            return false;
    }
}

bool JsTokenizer::isIdentStart(char c) const {
    return isAlpha(c) || c == '_' || c == '$';
}

bool JsTokenizer::isIdent(char c) const {
    return isAlphaNumeric(c) || c == '_' || c == '$';
}

bool JsTokenizer::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool JsTokenizer::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool JsTokenizer::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

JsToken JsTokenizer::makeToken(JsTokenType type) {
    std::string value = input_.substr(start_, current_ - start_);
    JsToken token(type, value, tokenStartLine_, tokenStartColumn_);
    lastToken_ = token;
    return token;
}

JsTokenType JsTokenizer::getKeywordType(const std::string& word) const {
    auto it = keywords.find(word);
    if (it != keywords.end()) {
        return it->second;
    }
    return JsTokenType::IDENTIFIER;
}

// JsToken methods
bool JsToken::isKeyword() const {
    return type >= JsTokenType::CONST && type <= JsTokenType::VOID;
}

bool JsToken::isOperator() const {
    return type >= JsTokenType::PLUS && type <= JsTokenType::SPREAD;
}

bool JsToken::isLiteral() const {
    return type == JsTokenType::NUMBER || 
           type == JsTokenType::STRING || 
           type == JsTokenType::TEMPLATE ||
           type == JsTokenType::REGEX ||
           type == JsTokenType::TRUE ||
           type == JsTokenType::FALSE ||
           type == JsTokenType::NULL_TOKEN ||
           type == JsTokenType::UNDEFINED;
}

} // namespace chtl::v2::js