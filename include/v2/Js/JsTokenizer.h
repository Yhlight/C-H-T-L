#pragma once

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>

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
    explicit JsTokenizer(const std::string& source);
    
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
     * 扫描单个 Token（内部使用）
     */
    void scanToken();
    
    /**
     * 获取所有 Token
     */
    std::vector<JsToken> tokenize();
    
private:
    char advance();

    /**
     * 与期望的字符匹配
     */
    bool match(char expected);
    
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

    // 模板字面量
    void scanTemplateLiteral();

    // 块注释
    void scanBlockComment();
    
    /**
     * 扫描标识符或关键字
     */
    void scanIdentifier();
    
    /**
     * 扫描数字
     */
    void scanNumber();
    
    /**
     * 扫描字符串
     */
    void scanString(char quote);
    
    /**
     * 扫描模板字符串
     */
    JsToken scanTemplate(); // TODO remove if unused
    
    /**
     * 扫描正则表达式
     */
    void scanRegex();
    
    /**
     * 判断是否可能是正则表达式
     */
    bool isRegexContext();
    
    /**
     * 检查是否是标识符开始字符
     */
    bool isAlpha(char c) const;
    bool isAlphaNumeric(char c) const;
    // 检查是否是数字
    bool isDigit(char c) const;
    
    /**
     * 创建 Token
     */
    JsToken makeToken(JsTokenType type);

    /**
     * 标识符对应的 Token 类型
     */
    JsTokenType getIdentifierType(const std::string& identifier);
    
private:
    std::string source_;
    size_t position_ = 0;
    int line_ = 1;
    int column_ = 1;
    int tokenStartLine_ = 1;
    int tokenStartColumn_ = 1;
    
    std::vector<JsToken> tokens_;
};

} // namespace chtl::v2::js