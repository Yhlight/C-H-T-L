#ifndef CHTL_TOKEN_TYPE_H
#define CHTL_TOKEN_TYPE_H

namespace chtl {

// Token类型枚举
enum class TokenType {
    // 字面量
    IDENTIFIER,           // 标识符
    STRING_LITERAL,       // 字符串字面量 "string" 或 'string'
    UNQUOTED_LITERAL,     // 无引号字面量
    NUMBER,               // 数字
    
    // 关键字
    TEXT,                 // text
    STYLE,                // style
    INHERIT,              // inherit
    DELETE_KW,            // delete (使用DELETE_KW避免与C++关键字冲突)
    INSERT,               // insert
    AFTER,                // after
    BEFORE,               // before
    REPLACE,              // replace
    AT,                   // at
    TOP,                  // top
    BOTTOM,               // bottom
    FROM,                 // from
    AS,                   // as
    EXCEPT,               // except
    
    // 特殊标记
    CUSTOM,               // [Custom]
    TEMPLATE,             // [Template]
    ORIGIN,               // [Origin]
    IMPORT,               // [Import]
    NAMESPACE_KW,         // [Namespace]
    CONFIGURATION,        // [Configuration]
    NAME,                 // [Name]
    INFO,                 // [Info]
    EXPORT_KW,            // [Export]
    
    // 特殊前缀
    AT_STYLE,             // @Style
    AT_ELEMENT,           // @Element
    AT_VAR,               // @Var
    AT_HTML,              // @Html
    AT_JAVASCRIPT,        // @JavaScript
    AT_CHTL,              // @Chtl
    
    // 运算符和分隔符
    COLON,                // :
    SEMICOLON,            // ;
    EQUALS,               // =
    COMMA,                // ,
    DOT,                  // .
    ARROW,                // ->
    AMPERSAND,            // &
    
    // 括号
    LEFT_BRACE,           // {
    RIGHT_BRACE,          // }
    LEFT_PAREN,           // (
    RIGHT_PAREN,          // )
    LEFT_BRACKET,         // [
    RIGHT_BRACKET,        // ]
    
    // 注释
    SINGLE_LINE_COMMENT,  // //
    MULTI_LINE_COMMENT,   // /* */
    HTML_COMMENT,         // --
    
    // JavaScript增强语法
    DOUBLE_LEFT_BRACE,    // {{
    DOUBLE_RIGHT_BRACE,   // }}
    
    // 其他
    WILDCARD,             // *
    EOF_TOKEN,            // 文件结束
    UNKNOWN               // 未知token
};

} // namespace chtl

#endif // CHTL_TOKEN_TYPE_H