#include "v2/Js/JsTokenizer.h"
#include <cctype>
#include <algorithm>

namespace chtl::v2::js {

JsTokenizer::JsTokenizer(const std::string& source) 
    : source_(source), position_(0), line_(1), column_(1) {}

std::vector<JsToken> JsTokenizer::tokenize() {
    tokens_.clear();
    position_ = 0;
    line_ = 1;
    column_ = 1;
    
    while (!isAtEnd()) {
        scanToken();
    }
    
    addToken(JsTokenType::EOF_TOKEN, "");
    return tokens_;
}

void JsTokenizer::scanToken() {
    skipWhitespace();
    
    if (isAtEnd()) return;
    
    char c = advance();
    
    switch (c) {
        // Single character tokens
        case '(': addToken(JsTokenType::LEFT_PAREN, "("); break;
        case ')': addToken(JsTokenType::RIGHT_PAREN, ")"); break;
        case '{': addToken(JsTokenType::LEFT_BRACE, "{"); break;
        case '}': addToken(JsTokenType::RIGHT_BRACE, "}"); break;
        case '[': addToken(JsTokenType::LEFT_BRACKET, "["); break;
        case ']': addToken(JsTokenType::RIGHT_BRACKET, "]"); break;
        case ',': addToken(JsTokenType::COMMA, ","); break;
        case '.': addToken(JsTokenType::DOT, "."); break;
        case ';': addToken(JsTokenType::SEMICOLON, ";"); break;
        case ':': addToken(JsTokenType::COLON, ":"); break;
        case '?': addToken(JsTokenType::QUESTION, "?"); break;
        
        // Operators
        case '+':
            if (match('=')) addToken(JsTokenType::PLUS_EQUAL, "+=");
            else if (match('+')) addToken(JsTokenType::PLUS_PLUS, "++");
            else addToken(JsTokenType::PLUS, "+");
            break;
            
        case '-':
            if (match('=')) addToken(JsTokenType::MINUS_EQUAL, "-=");
            else if (match('-')) addToken(JsTokenType::MINUS_MINUS, "--");
            else if (match('>')) addToken(JsTokenType::ARROW, "->");
            else addToken(JsTokenType::MINUS, "-");
            break;
            
        case '*':
            if (match('=')) addToken(JsTokenType::STAR_EQUAL, "*=");
            else if (match('*')) {
                if (match('=')) addToken(JsTokenType::STAR_STAR_EQUAL, "**=");
                else addToken(JsTokenType::STAR_STAR, "**");
            }
            else addToken(JsTokenType::STAR, "*");
            break;
            
        case '/':
            if (match('/')) {
                // Line comment
                while (!isAtEnd() && peek() != '\n') advance();
            } else if (match('*')) {
                // Block comment
                scanBlockComment();
            } else if (match('=')) {
                addToken(JsTokenType::SLASH_EQUAL, "/=");
            } else {
                // Could be division or regex
                if (isRegexContext()) {
                    scanRegex();
                } else {
                    addToken(JsTokenType::SLASH, "/");
                }
            }
            break;
            
        case '=':
            if (match('=')) {
                if (match('=')) addToken(JsTokenType::EQUAL_EQUAL_EQUAL, "===");
                else addToken(JsTokenType::EQUAL_EQUAL, "==");
            } else if (match('>')) {
                addToken(JsTokenType::ARROW, "=>");
            } else {
                addToken(JsTokenType::EQUAL, "=");
            }
            break;
            
        case '!':
            if (match('=')) {
                if (match('=')) addToken(JsTokenType::BANG_EQUAL_EQUAL, "!==");
                else addToken(JsTokenType::BANG_EQUAL, "!=");
            } else {
                addToken(JsTokenType::BANG, "!");
            }
            break;
            
        case '<':
            if (match('=')) addToken(JsTokenType::LESS_EQUAL, "<=");
            else if (match('<')) {
                if (match('=')) addToken(JsTokenType::LESS_LESS_EQUAL, "<<=");
                else addToken(JsTokenType::LESS_LESS, "<<");
            } else {
                addToken(JsTokenType::LESS, "<");
            }
            break;
            
        case '>':
            if (match('=')) addToken(JsTokenType::GREATER_EQUAL, ">=");
            else if (match('>')) {
                if (match('=')) addToken(JsTokenType::GREATER_GREATER_EQUAL, ">>=");
                else if (match('>')) {
                    if (match('=')) addToken(JsTokenType::GREATER_GREATER_GREATER_EQUAL, ">>>=");
                    else addToken(JsTokenType::GREATER_GREATER_GREATER, ">>>");
                } else {
                    addToken(JsTokenType::GREATER_GREATER, ">>");
                }
            } else {
                addToken(JsTokenType::GREATER, ">");
            }
            break;
            
        case '&':
            if (match('&')) {
                if (match('=')) addToken(JsTokenType::AND_AND_EQUAL, "&&=");
                else addToken(JsTokenType::AND_AND, "&&");
            } else if (match('=')) {
                addToken(JsTokenType::AND_EQUAL, "&=");
            } else {
                addToken(JsTokenType::AND, "&");
            }
            break;
            
        case '|':
            if (match('|')) {
                if (match('=')) addToken(JsTokenType::OR_OR_EQUAL, "||=");
                else addToken(JsTokenType::OR_OR, "||");
            } else if (match('=')) {
                addToken(JsTokenType::OR_EQUAL, "|=");
            } else {
                addToken(JsTokenType::OR, "|");
            }
            break;
            
        case '^':
            if (match('=')) addToken(JsTokenType::XOR_EQUAL, "^=");
            else addToken(JsTokenType::XOR, "^");
            break;
            
        case '%':
            if (match('=')) addToken(JsTokenType::PERCENT_EQUAL, "%=");
            else addToken(JsTokenType::PERCENT, "%");
            break;
            
        case '~':
            addToken(JsTokenType::TILDE, "~");
            break;
            
        // Strings
        case '"':
        case '\'':
            scanString(c);
            break;
            
        // Template literal
        case '`':
            scanTemplateLiteral();
            break;
            
        default:
            if (isDigit(c)) {
                scanNumber();
            } else if (isAlpha(c) || c == '_' || c == '$') {
                scanIdentifier();
            } else {
                // Unknown character
                addToken(JsTokenType::UNKNOWN, std::string(1, c));
            }
            break;
    }
}

void JsTokenizer::scanString(char quote) {
    size_t start = position_;
    
    while (!isAtEnd() && peek() != quote) {
        if (peek() == '\n') {
            line_++;
            column_ = 1;
        }
        if (peek() == '\\') {
            advance(); // Skip escape
            if (!isAtEnd()) advance(); // Skip escaped char
        } else {
            advance();
        }
    }
    
    if (isAtEnd()) {
        // Unterminated string
        addToken(JsTokenType::STRING, source_.substr(start - 1, position_ - start + 1));
        return;
    }
    
    // Closing quote
    advance();
    
    addToken(JsTokenType::STRING, source_.substr(start - 1, position_ - start + 1));
}

void JsTokenizer::scanTemplateLiteral() {
    size_t start = position_ - 1;
    std::string value = "`";
    
    while (!isAtEnd() && peek() != '`') {
        if (peek() == '$' && peekNext() == '{') {
            // Template expression
            value += source_.substr(position_, 2);
            advance(); // $
            advance(); // {
            
            // Scan the expression
            int braceCount = 1;
            while (!isAtEnd() && braceCount > 0) {
                char c = advance();
                value += c;
                if (c == '{') braceCount++;
                else if (c == '}') braceCount--;
            }
        } else {
            if (peek() == '\n') {
                line_++;
                column_ = 1;
            }
            value += advance();
        }
    }
    
    if (!isAtEnd()) {
        value += advance(); // closing `
    }
    
    addToken(JsTokenType::TEMPLATE_LITERAL, value);
}

void JsTokenizer::scanNumber() {
    size_t start = position_ - 1;
    
    // Integer part
    while (isDigit(peek())) advance();
    
    // Decimal part
    if (peek() == '.' && isDigit(peekNext())) {
        advance(); // .
        while (isDigit(peek())) advance();
    }
    
    // Exponent
    if (peek() == 'e' || peek() == 'E') {
        advance();
        if (peek() == '+' || peek() == '-') advance();
        while (isDigit(peek())) advance();
    }
    
    // BigInt
    if (peek() == 'n') {
        advance();
    }
    
    addToken(JsTokenType::NUMBER, source_.substr(start, position_ - start));
}

void JsTokenizer::scanIdentifier() {
    size_t start = position_ - 1;
    
    while (isAlphaNumeric(peek()) || peek() == '_' || peek() == '$') {
        advance();
    }
    
    std::string value = source_.substr(start, position_ - start);
    JsTokenType type = getIdentifierType(value);
    addToken(type, value);
}

void JsTokenizer::scanRegex() {
    size_t start = position_ - 1;
    
    // Scan pattern
    while (!isAtEnd() && peek() != '/') {
        if (peek() == '\\') {
            advance(); // Skip escape
            if (!isAtEnd()) advance();
        } else if (peek() == '\n') {
            // Invalid regex
            break;
        } else {
            advance();
        }
    }
    
    if (!isAtEnd() && peek() == '/') {
        advance(); // closing /
        
        // Scan flags
        while (isAlpha(peek())) {
            advance();
        }
    }
    
    addToken(JsTokenType::REGEX, source_.substr(start, position_ - start));
}

void JsTokenizer::scanBlockComment() {
    while (!isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
            advance(); // *
            advance(); // /
            break;
        }
        
        if (peek() == '\n') {
            line_++;
            column_ = 1;
        }
        
        advance();
    }
}

JsTokenType JsTokenizer::getIdentifierType(const std::string& identifier) {
    // Keywords
    static const std::unordered_map<std::string, JsTokenType> keywords = {
        {"break", JsTokenType::BREAK},
        {"case", JsTokenType::CASE},
        {"catch", JsTokenType::CATCH},
        {"class", JsTokenType::CLASS},
        {"const", JsTokenType::CONST},
        {"continue", JsTokenType::CONTINUE},
        {"debugger", JsTokenType::DEBUGGER},
        {"default", JsTokenType::DEFAULT},
        {"delete", JsTokenType::DELETE},
        {"do", JsTokenType::DO},
        {"else", JsTokenType::ELSE},
        {"export", JsTokenType::EXPORT},
        {"extends", JsTokenType::EXTENDS},
        {"false", JsTokenType::FALSE},
        {"finally", JsTokenType::FINALLY},
        {"for", JsTokenType::FOR},
        {"function", JsTokenType::FUNCTION},
        {"if", JsTokenType::IF},
        {"import", JsTokenType::IMPORT},
        {"in", JsTokenType::IN},
        {"instanceof", JsTokenType::INSTANCEOF},
        {"let", JsTokenType::LET},
        {"new", JsTokenType::NEW},
        {"null", JsTokenType::NULL_LITERAL},
        {"of", JsTokenType::OF},
        {"return", JsTokenType::RETURN},
        {"super", JsTokenType::SUPER},
        {"switch", JsTokenType::SWITCH},
        {"this", JsTokenType::THIS},
        {"throw", JsTokenType::THROW},
        {"true", JsTokenType::TRUE},
        {"try", JsTokenType::TRY},
        {"typeof", JsTokenType::TYPEOF},
        {"undefined", JsTokenType::UNDEFINED},
        {"var", JsTokenType::VAR},
        {"void", JsTokenType::VOID},
        {"while", JsTokenType::WHILE},
        {"with", JsTokenType::WITH},
        {"yield", JsTokenType::YIELD},
        {"async", JsTokenType::ASYNC},
        {"await", JsTokenType::AWAIT},
        {"static", JsTokenType::STATIC},
        {"get", JsTokenType::GET},
        {"set", JsTokenType::SET},
        {"from", JsTokenType::FROM},
        {"as", JsTokenType::AS}
    };
    
    auto it = keywords.find(identifier);
    if (it != keywords.end()) {
        return it->second;
    }
    
    return JsTokenType::IDENTIFIER;
}

bool JsTokenizer::isRegexContext() {
    // Simple heuristic: regex likely after = ( [ , ! : ; ? & | ^ ~ + - * / % return throw
    if (tokens_.empty()) return true;
    
    JsTokenType lastType = tokens_.back().type;
    return lastType == JsTokenType::EQUAL ||
           lastType == JsTokenType::LEFT_PAREN ||
           lastType == JsTokenType::LEFT_BRACKET ||
           lastType == JsTokenType::COMMA ||
           lastType == JsTokenType::BANG ||
           lastType == JsTokenType::COLON ||
           lastType == JsTokenType::SEMICOLON ||
           lastType == JsTokenType::QUESTION ||
           lastType == JsTokenType::AND ||
           lastType == JsTokenType::OR ||
           lastType == JsTokenType::XOR ||
           lastType == JsTokenType::TILDE ||
           lastType == JsTokenType::PLUS ||
           lastType == JsTokenType::MINUS ||
           lastType == JsTokenType::STAR ||
           lastType == JsTokenType::SLASH ||
           lastType == JsTokenType::PERCENT ||
           lastType == JsTokenType::RETURN ||
           lastType == JsTokenType::THROW;
}

void JsTokenizer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line_++;
                column_ = 1;
                advance();
                break;
            default:
                return;
        }
    }
}

void JsTokenizer::addToken(JsTokenType type, const std::string& lexeme) {
    tokens_.push_back({type, lexeme, line_, column_ - lexeme.length()});
}

bool JsTokenizer::isAtEnd() const {
    return position_ >= source_.length();
}

char JsTokenizer::advance() {
    column_++;
    return source_[position_++];
}

char JsTokenizer::peek() const {
    if (isAtEnd()) return '\0';
    return source_[position_];
}

char JsTokenizer::peekNext() const {
    if (position_ + 1 >= source_.length()) return '\0';
    return source_[position_ + 1];
}

bool JsTokenizer::match(char expected) {
    if (isAtEnd()) return false;
    if (source_[position_] != expected) return false;
    position_++;
    column_++;
    return true;
}

bool JsTokenizer::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool JsTokenizer::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

bool JsTokenizer::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

} // namespace chtl::v2::js