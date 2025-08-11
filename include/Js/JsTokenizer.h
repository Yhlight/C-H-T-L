#ifndef CHTL_JS_TOKENIZER_H
#define CHTL_JS_TOKENIZER_H

#include <string>
#include <vector>

namespace chtl {

// JavaScript Token类型
enum class JsTokenType {
    // 字面量
    IDENTIFIER,
    NUMBER,
    STRING,
    TEMPLATE_STRING,
    REGEXP,
    
    // 关键字
    FUNCTION,
    CLASS,
    CONST,
    LET,
    VAR,
    IF,
    ELSE,
    FOR,
    WHILE,
    DO,
    RETURN,
    BREAK,
    CONTINUE,
    SWITCH,
    CASE,
    DEFAULT,
    TRY,
    CATCH,
    FINALLY,
    THROW,
    NEW,
    THIS,
    SUPER,
    IMPORT,
    EXPORT,
    ASYNC,
    AWAIT,
    YIELD,
    
    // 运算符
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    ASSIGN,
    EQUAL,
    NOT_EQUAL,
    STRICT_EQUAL,
    STRICT_NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUAL,
    GREATER_EQUAL,
    LOGICAL_AND,
    LOGICAL_OR,
    LOGICAL_NOT,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR,
    BITWISE_NOT,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    UNSIGNED_RIGHT_SHIFT,
    INCREMENT,
    DECREMENT,
    ARROW,
    OPTIONAL_CHAIN,
    NULLISH_COALESCE,
    
    // 分隔符
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    SEMICOLON,
    COMMA,
    DOT,
    COLON,
    QUESTION,
    
    // 特殊
    COMMENT,
    WHITESPACE,
    NEWLINE,
    EOF_TOKEN,
    UNKNOWN
};

// JavaScript Token
struct JsToken {
    JsTokenType type;
    std::string value;
    int line;
    int column;
    
    JsToken(JsTokenType t, const std::string& v, int l, int c)
        : type(t), value(v), line(l), column(c) {}
};

// JavaScript分词器
class JsTokenizer {
public:
    JsTokenizer();
    
    // 分词
    std::vector<JsToken> tokenize(const std::string& js);
    void reset(const std::string& js);
    
    // Token操作
    JsToken nextToken();
    bool hasMoreTokens() const;
    
    // 位置信息
    int getCurrentLine() const { return currentLine_; }
    int getCurrentColumn() const { return currentColumn_; }
    
private:
    std::string input_;
    size_t position_;
    int currentLine_;
    int currentColumn_;
    
    // 字符操作
    char currentChar() const;
    char peekChar(int offset = 1) const;
    void advance();
    void skipWhitespace();
    void skipComment();
    
    // Token识别
    JsToken readIdentifier();
    JsToken readNumber();
    JsToken readString();
    JsToken readTemplateString();
    JsToken readOperator();
    JsToken readComment();
    
    bool isIdentifierStart(char c) const;
    bool isIdentifierPart(char c) const;
    JsTokenType getKeywordType(const std::string& identifier) const;
};

} // namespace chtl

#endif // CHTL_JS_TOKENIZER_H