#pragma once

#include <string>
#include <vector>

namespace chtl::v2::css {

/**
 * CSS Token 类型
 */
enum class CssTokenType {
    // 字面量
    IDENT,              // 标识符
    FUNCTION,           // 函数名
    AT_KEYWORD,         // @规则
    HASH,               // #号（ID或颜色）
    STRING,             // 字符串
    URL,                // url()
    NUMBER,             // 数字
    PERCENTAGE,         // 百分比
    DIMENSION,          // 带单位的数字
    
    // 分隔符
    COLON,              // :
    SEMICOLON,          // ;
    COMMA,              // ,
    LEFT_BRACE,         // {
    RIGHT_BRACE,        // }
    LEFT_PAREN,         // (
    RIGHT_PAREN,        // )
    LEFT_BRACKET,       // [
    RIGHT_BRACKET,      // ]
    
    // 操作符
    DOT,                // .
    PLUS,               // +
    MINUS,              // -
    STAR,               // *
    SLASH,              // /
    GT,                 // >
    TILDE,              // ~
    PIPE,               // |
    CARET,              // ^
    DOLLAR,             // $
    EQUALS,             // =
    
    // 特殊
    WHITESPACE,         // 空白
    COMMENT,            // 注释
    CDO,                // <!--
    CDC,                // -->
    IMPORTANT,          // !important
    
    // 结束
    EOF_TOKEN,
    ERROR
};

/**
 * CSS Token
 */
struct CssToken {
    CssTokenType type;
    std::string value;
    int line;
    int column;
    
    // 额外信息
    struct {
        std::string unit;       // 单位（对于 DIMENSION）
        double numericValue;    // 数值（对于 NUMBER, PERCENTAGE, DIMENSION）
        bool isId;             // 是否是 ID（对于 HASH）
    } extra;
    
    CssToken(CssTokenType t = CssTokenType::ERROR, 
             const std::string& v = "", 
             int l = 0, int c = 0)
        : type(t), value(v), line(l), column(c) {}
};

/**
 * CSS 词法分析器
 */
class CssTokenizer {
public:
    explicit CssTokenizer(const std::string& input);
    
    /**
     * 获取下一个 Token
     */
    CssToken nextToken();
    
    /**
     * 查看下一个 Token（不消费）
     */
    CssToken peekToken();
    
    /**
     * 是否到达结尾
     */
    bool isAtEnd() const;
    
    /**
     * 获取所有 Token
     */
    std::vector<CssToken> tokenize();
    
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
     * 跳过空白
     */
    void skipWhitespace();
    
    /**
     * 扫描注释
     */
    void scanComment();
    
    /**
     * 扫描标识符
     */
    CssToken scanIdent();
    
    /**
     * 扫描数字
     */
    CssToken scanNumber();
    
    /**
     * 扫描字符串
     */
    CssToken scanString(char quote);
    
    /**
     * 扫描 URL
     */
    CssToken scanUrl();
    
    /**
     * 扫描 Hash
     */
    CssToken scanHash();
    
    /**
     * 扫描 @规则
     */
    CssToken scanAtKeyword();
    
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
    CssToken makeToken(CssTokenType type);
    
private:
    std::string input_;
    size_t current_ = 0;
    size_t start_ = 0;
    int line_ = 1;
    int column_ = 1;
    int tokenStartLine_ = 1;
    int tokenStartColumn_ = 1;
    
    std::vector<CssToken> tokenBuffer_;
};

} // namespace chtl::v2::css