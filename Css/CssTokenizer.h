#ifndef CHTL_CSS_TOKENIZER_H
#define CHTL_CSS_TOKENIZER_H

#include "CssTypes.h"
#include <string>
#include <memory>

namespace chtl {
namespace css {

struct CssToken {
    CssTokenType type;
    std::string value;
    size_t line;
    size_t column;
    
    CssToken(CssTokenType t = CssTokenType::UNKNOWN, 
             const std::string& v = "",
             size_t l = 0, 
             size_t c = 0)
        : type(t), value(v), line(l), column(c) {}
};

class CssTokenizer {
private:
    std::string input_;
    size_t position_;
    size_t line_;
    size_t column_;
    
    char current() const;
    char peek(size_t offset = 1) const;
    void advance();
    void skipWhitespace();
    void skipComment();
    
    CssToken readString(char quote);
    CssToken readNumber();
    CssToken readIdentifier();
    CssToken readUrl();
    CssToken readAtRule();
    
public:
    CssTokenizer();
    
    void initialize(const std::string& input);
    CssToken nextToken();
    bool isAtEnd() const;
    
    // 工具方法
    static bool isIdentifierStart(char c);
    static bool isIdentifierPart(char c);
    static bool isDigit(char c);
    static bool isWhitespace(char c);
};

} // namespace css
} // namespace chtl

#endif // CHTL_CSS_TOKENIZER_H