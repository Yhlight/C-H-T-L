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
    TEMPLATE_LITERAL,     // 模板字面量 `string`
    
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
    EXPORT,               // [Export]
    
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
    
    // 操作符
    ASSIGN,               // =
    LESS_THAN,            // <
    GREATER_THAN,         // >
    SLASH,                // /
    HYPHEN,               // -
    PLUS,                 // +
    ASTERISK,             // *
    DOUBLE_DOT,           // ..
    EXCLAMATION,          // !
    OPERATOR,             // 通用操作符
    
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
    
    // JavaScript关键字
    VAR,                  // var
    LET,                  // let
    CONST,                // const
    FUNCTION,             // function
    CLASS,                // class
    IF,                   // if
    ELSE,                 // else
    FOR,                  // for
    WHILE,                // while
    RETURN,               // return
    TRUE,                 // true
    FALSE,                // false
    NULL_LITERAL,         // null
    UNDEFINED,            // undefined
    NEW,                  // new
    THIS,                 // this
    ASYNC,                // async
    AWAIT,                // await
    EXPORT_KW,            // export
    
    // CHTL-JS扩展
    CHTL_SELECTOR,        // {{selector}} CHTL选择器
    CHTL_ARROW,           // -> CHTL箭头操作符
    CHTL_METHOD,          // CHTL方法名
    
    // 其他
    WILDCARD,             // *
    EOF_TOKEN,            // 文件结束
    UNKNOWN               // 未知token
};

} // namespace chtl

#endif // CHTL_TOKEN_TYPE_H