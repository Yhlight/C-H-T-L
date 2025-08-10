#ifndef CHTL_CSS_TOKENIZER_H
#define CHTL_CSS_TOKENIZER_H

#include <string>
#include <vector>

namespace chtl {

// CSS Token类型
enum class CssTokenType {
    // 基本标记
    SELECTOR,
    PROPERTY,
    VALUE,
    SEMICOLON,
    COLON,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    
    // 特殊标记
    AT_RULE,        // @import, @media等
    COMMENT,
    STRING,
    NUMBER,
    UNIT,           // px, em, %等
    COLOR,          // #fff, rgb()等
    FUNCTION,       // calc(), var()等
    
    // 运算符
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    
    // 其他
    WHITESPACE,
    NEWLINE,
    EOF_TOKEN,
    UNKNOWN
};

// CSS Token
struct CssToken {
    CssTokenType type;
    std::string value;
    int line;
    int column;
    
    CssToken(CssTokenType t, const std::string& v, int l = 0, int c = 0)
        : type(t), value(v), line(l), column(c) {}
};

// CSS分词器
class CssTokenizer {
public:
    CssTokenizer();
    ~CssTokenizer() = default;
    
    // 分词
    std::vector<CssToken> tokenize(const std::string& css);
    
    // 流式分词
    void reset(const std::string& css);
    CssToken nextToken();
    bool hasMoreTokens() const;
    
    // 获取当前位置
    int getCurrentLine() const { return currentLine_; }
    int getCurrentColumn() const { return currentColumn_; }
    
private:
    std::string input_;
    size_t position_;
    int currentLine_;
    int currentColumn_;
    
    // 辅助方法
    char currentChar() const;
    char peekChar(int offset = 1) const;
    void advance();
    void skipWhitespace();
    void skipComment();
    
    // Token识别
    CssToken readSelector();
    CssToken readProperty();
    CssToken readValue();
    CssToken readString();
    CssToken readNumber();
    CssToken readAtRule();
    CssToken readFunction();
    CssToken readColor();
    
    bool isValidPropertyChar(char c) const;
    bool isValidSelectorChar(char c) const;
};

} // namespace chtl

#endif // CHTL_CSS_TOKENIZER_H