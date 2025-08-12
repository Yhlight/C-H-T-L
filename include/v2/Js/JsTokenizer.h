#pragma once

#include <string>
#include <vector>
#include <variant>

namespace chtl::v2::js {

/**
 * JavaScript Token 类型
 */
enum class JsTokenType {
    // 字面量
    IDENTIFIER,         // 标识符
    NUMBER,            // 数字
    STRING,            // 字符串
    TEMPLATE,          // 模板字符串
    REGEX,             // 正则表达式
    TRUE,              // true
    FALSE,             // false
    NULL_TOKEN,        // null
    UNDEFINED,         // undefined
    
    // 关键字
    CONST,             // const
    LET,               // let
    VAR,               // var
    FUNCTION,          // function
    CLASS,             // class
    IF,                // if
    ELSE,              // else
    FOR,               // for
    WHILE,             // while
    DO,                // do
    RETURN,            // return
    BREAK,             // break
    CONTINUE,          // continue
    SWITCH,            // switch
    CASE,              // case
    DEFAULT,           // default
    TRY,               // try
    CATCH,             // catch
    FINALLY,           // finally
    THROW,             // throw
    NEW,               // new
    THIS,              // this
    SUPER,             // super
    IMPORT,            // import
    EXPORT,            // export
    ASYNC,             // async
    AWAIT,             // await
    YIELD,             // yield
    TYPEOF,            // typeof
    INSTANCEOF,        // instanceof
    IN,                // in
    OF,                // of
    DELETE,            // delete
    VOID,              // void
    
    // 操作符
    PLUS,              // +
    MINUS,             // -
    STAR,              // *
    SLASH,             // /
    PERCENT,           // %
    POWER,             // **
    EQUALS,            // =
    PLUS_EQUALS,       // +=
    MINUS_EQUALS,      // -=
    STAR_EQUALS,       // *=
    SLASH_EQUALS,      // /=
    PERCENT_EQUALS,    // %=
    POWER_EQUALS,      // **=
    EQUALS_EQUALS,     // ==
    NOT_EQUALS,        // !=
    TRIPLE_EQUALS,     // ===
    NOT_TRIPLE_EQUALS, // !==
    LESS,              // <
    GREATER,           // >
    LESS_EQUALS,       // <=
    GREATER_EQUALS,    // >=
    LOGICAL_AND,       // &&
    LOGICAL_OR,        // ||
    LOGICAL_NOT,       // !
    BITWISE_AND,       // &
    BITWISE_OR,        // |
    BITWISE_XOR,       // ^
    BITWISE_NOT,       // ~
    LEFT_SHIFT,        // <<
    RIGHT_SHIFT,       // >>
    UNSIGNED_RIGHT_SHIFT, // >>>
    INCREMENT,         // ++
    DECREMENT,         // --
    QUESTION,          // ?
    NULLISH_COALESCING,// ??
    OPTIONAL_CHAIN,    // ?.
    
    // 分隔符
    LEFT_PAREN,        // (
    RIGHT_PAREN,       // )
    LEFT_BRACE,        // {
    RIGHT_BRACE,       // }
    LEFT_BRACKET,      // [
    RIGHT_BRACKET,     // ]
    SEMICOLON,         // ;
    COMMA,             // ,
    DOT,               // .
    COLON,             // :
    ARROW,             // =>
    SPREAD,            // ...
    
    // 特殊
    COMMENT,           // 注释
    WHITESPACE,        // 空白
    NEWLINE,           // 换行
    EOF_TOKEN,         // 文件结束
    ERROR              // 错误
};

/**
 * JavaScript Token
 */
struct JsToken {
    JsTokenType type;
    std::string value;
    int line;
    int column;
    
    // 额外信息
    struct {
        double numericValue;    // 数字值
        bool isFloat;          // 是否浮点数
        bool isBigInt;         // 是否 BigInt
        std::string flags;     // 正则表达式标志
    } extra;
    
    JsToken(JsTokenType t = JsTokenType::ERROR, 
            const std::string& v = "", 
            int l = 0, int c = 0)
        : type(t), value(v), line(l), column(c) {}
        
    bool isKeyword() const;
    bool isOperator() const;
    bool isLiteral() const;
};

/**
 * JavaScript 词法分析器
 */
class JsTokenizer {
public:
    explicit JsTokenizer(const std::string& input);
    
    /**
     * 获取下一个 Token
     */
    JsToken nextToken();
    
    /**
     * 查看下一个 Token（不消费）
     */
    JsToken peekToken();
    
    /**
     * 是否到达结尾
     */
    bool isAtEnd() const;
    
    /**
     * 获取所有 Token
     */
    std::vector<JsToken> tokenize();
    
private:
    /**
     * 消费字符
     */
    char consume();
    
    /**
     * 查看当前字符
     */
    char peek() const;
    
    /**
     * 查看下一个字符
     */
    char peekNext() const;
    
    /**
     * 查看第 n 个字符
     */
    char peekAhead(int n) const;
    
    /**
     * 跳过空白和换行
     */
    void skipWhitespace();
    
    /**
     * 扫描注释
     */
    bool scanComment();
    
    /**
     * 扫描标识符或关键字
     */
    JsToken scanIdentifier();
    
    /**
     * 扫描数字
     */
    JsToken scanNumber();
    
    /**
     * 扫描字符串
     */
    JsToken scanString(char quote);
    
    /**
     * 扫描模板字符串
     */
    JsToken scanTemplate();
    
    /**
     * 扫描正则表达式
     */
    JsToken scanRegex();
    
    /**
     * 判断是否可能是正则表达式
     */
    bool isRegexContext() const;
    
    /**
     * 检查是否是标识符开始字符
     */
    bool isIdentStart(char c) const;
    
    /**
     * 检查是否是标识符字符
     */
    bool isIdent(char c) const;
    
    /**
     * 检查是否是数字
     */
    bool isDigit(char c) const;
    
    /**
     * 创建 Token
     */
    JsToken makeToken(JsTokenType type);
    
    /**
     * 获取关键字类型
     */
    JsTokenType getKeywordType(const std::string& word) const;
    
private:
    std::string input_;
    size_t current_ = 0;
    size_t start_ = 0;
    int line_ = 1;
    int column_ = 1;
    int tokenStartLine_ = 1;
    int tokenStartColumn_ = 1;
    
    std::vector<JsToken> tokenBuffer_;
    JsToken lastToken_;  // 用于判断正则表达式上下文
};

} // namespace chtl::v2::js