#ifndef CHTL_COMMON_TYPES_H
#define CHTL_COMMON_TYPES_H

namespace CHTL {

/**
 * Token类型枚举
 */
enum class TokenType {
    // 特殊标记
    UNKNOWN = 0,
    END_OF_FILE,
    
    // 字面量
    IDENTIFIER,
    STRING_LITERAL,
    NUMBER_LITERAL,
    BOOLEAN_LITERAL,
    
    // 注释
    LINE_COMMENT,
    BLOCK_COMMENT,
    GENERATOR_COMMENT,
    
    // 括号
    LBRACE,         // {
    RBRACE,         // }
    LPAREN,         // (
    RPAREN,         // )
    LBRACKET,       // [
    RBRACKET,       // ]
    
    // 操作符标记起始
    OPERATOR_START = 100,
    
    // 操作符
    COLON,          // :
    SEMICOLON,      // ;
    COMMA,          // ,
    DOT,            // .
    EQUALS,         // =
    PLUS,           // +
    MINUS,          // -
    STAR,           // *
    SLASH,          // /
    PERCENT,        // %
    AMPERSAND,      // &
    PIPE,           // |
    CARET,          // ^
    TILDE,          // ~
    EXCLAMATION,    // !
    QUESTION,       // ?
    HASH,           // #
    AT,             // @
    DOLLAR,         // $
    ARROW,          // ->
    DOUBLE_LBRACE,  // {{
    DOUBLE_RBRACE,  // }}
    
    // 操作符标记结束
    OPERATOR_END = 199,
    
    // 关键字标记起始
    KEYWORD_START = 200,
    
    // CHTL关键字
    TEXT,
    STYLE,
    SCRIPT,
    TEMPLATE,
    CUSTOM,
    ORIGIN,
    IMPORT,
    NAMESPACE,
    CONFIGURATION,
    NAME,
    INFO,
    EXPORT,
    
    // 修饰符
    INHERIT,
    DELETE,
    INSERT,
    EXCEPT,
    FROM,
    AS,
    
    // 位置关键字
    AFTER,
    BEFORE,
    REPLACE,
    AT_TOP,
    AT_BOTTOM,
    
    // 类型标识
    AT_STYLE,
    AT_ELEMENT,
    AT_VAR,
    AT_HTML,
    AT_JAVASCRIPT,
    AT_CHTL,
    
    // JavaScript关键字
    VAR,
    LET,
    CONST,
    FUNCTION,
    CLASS,
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
    ASYNC,
    AWAIT,
    YIELD,
    
    // CHTL JS扩展关键字
    LISTEN,
    DELEGATE,
    ANIMATE,
    TARGET,
    DURATION,
    EASING,
    BEGIN,
    END,
    WHEN,
    LOOP,
    DELAY,
    CALLBACK,
    
    // 关键字标记结束
    KEYWORD_END = 299,
    
    // HTML标签（可扩展）
    HTML_TAG_START = 300,
    // ... HTML标签 ...
    HTML_TAG_END = 399,
    
    // CSS属性（可扩展）
    CSS_PROPERTY_START = 400,
    // ... CSS属性 ...
    CSS_PROPERTY_END = 499
};

/**
 * 语言类型
 */
enum class LanguageType {
    CHTL,
    CSS,
    JAVASCRIPT,
    CHTL_JAVASCRIPT,
    HTML
};

/**
 * 节点类型
 */
enum class NodeType {
    // 基础节点
    UNKNOWN,
    ROOT,
    
    // CHTL节点
    ELEMENT,
    TEXT,
    ATTRIBUTE,
    STYLE,          // 添加STYLE
    SCRIPT,         // 添加SCRIPT
    TEMPLATE,       // 添加TEMPLATE
    CUSTOM,         // 添加CUSTOM
    STYLE_BLOCK,
    SCRIPT_BLOCK,
    
    // 声明节点
    TEMPLATE_DECLARATION,
    CUSTOM_DECLARATION,
    NAMESPACE_DECLARATION,
    CONFIGURATION_BLOCK,
    
    // 特殊节点
    ORIGIN_BLOCK,
    IMPORT_STATEMENT,
    COMMENT,
    
    // 操作节点
    INSERT_OPERATION,
    DELETE_OPERATION,
    EXCEPT_OPERATION,
    
    // CSS节点
    CSS_RULESET,
    CSS_SELECTOR,
    CSS_DECLARATION,
    CSS_MEDIA_QUERY,
    CSS_KEYFRAMES,
    
    // JavaScript节点
    JS_STATEMENT,
    JS_EXPRESSION,
    JS_FUNCTION,
    JS_CLASS,
    JS_VARIABLE,
    
    // CHTL JS扩展节点
    CHTL_SELECTOR,
    CHTL_ARROW_ACCESS,
    CHTL_LISTEN,
    CHTL_DELEGATE,
    CHTL_ANIMATE
};

/**
 * 符号类型
 */
enum class SymbolType {
    TEMPLATE_STYLE,
    TEMPLATE_ELEMENT,
    TEMPLATE_VAR,
    CUSTOM_STYLE,
    CUSTOM_ELEMENT,
    CUSTOM_VAR,
    NAMESPACE,
    IMPORT,
    VARIABLE,
    FUNCTION,
    CLASS,
    CONFIG  // 添加CONFIG
};

/**
 * 编译器状态
 */
enum class CompilerState {
    IDLE,
    SCANNING,
    LEXING,
    PARSING,
    ANALYZING,
    GENERATING,
    COMPLETE,
    ERROR
};

} // namespace CHTL

#endif // CHTL_COMMON_TYPES_H