#ifndef CHTL_TOKEN_H
#define CHTL_TOKEN_H

#include <string>
#include <iostream>

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

// Token结构体
struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
    std::string filename;
    
    Token() : type(TokenType::UNKNOWN), line(1), column(1) {}
    
    Token(TokenType t, const std::string& v, int l, int c, const std::string& f = "")
        : type(t), value(v), line(l), column(c), filename(f) {}
    
    // 判断是否为关键字
    bool isKeyword() const {
        return type >= TokenType::TEXT && type <= TokenType::EXCEPT;
    }
    
    // 判断是否为特殊标记
    bool isSpecialMarker() const {
        return type >= TokenType::CUSTOM && type <= TokenType::EXPORT_KW;
    }
    
    // 判断是否为AT前缀
    bool isAtPrefix() const {
        return type >= TokenType::AT_STYLE && type <= TokenType::AT_CHTL;
    }
    
    // 获取Token类型的字符串表示
    std::string getTypeString() const;
    
    // 调试输出
    void print() const {
        std::cout << "Token(" << getTypeString() << ", \"" << value << "\", " 
                  << line << ":" << column << ")" << std::endl;
    }
};

// Token类型转字符串（用于调试）
inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::UNQUOTED_LITERAL: return "UNQUOTED_LITERAL";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::TEXT: return "TEXT";
        case TokenType::STYLE: return "STYLE";
        case TokenType::INHERIT: return "INHERIT";
        case TokenType::DELETE_KW: return "DELETE";
        case TokenType::INSERT: return "INSERT";
        case TokenType::AFTER: return "AFTER";
        case TokenType::BEFORE: return "BEFORE";
        case TokenType::REPLACE: return "REPLACE";
        case TokenType::AT: return "AT";
        case TokenType::TOP: return "TOP";
        case TokenType::BOTTOM: return "BOTTOM";
        case TokenType::FROM: return "FROM";
        case TokenType::AS: return "AS";
        case TokenType::EXCEPT: return "EXCEPT";
        case TokenType::CUSTOM: return "CUSTOM";
        case TokenType::TEMPLATE: return "TEMPLATE";
        case TokenType::ORIGIN: return "ORIGIN";
        case TokenType::IMPORT: return "IMPORT";
        case TokenType::NAMESPACE_KW: return "NAMESPACE";
        case TokenType::CONFIGURATION: return "CONFIGURATION";
        case TokenType::NAME: return "NAME";
        case TokenType::INFO: return "INFO";
        case TokenType::EXPORT_KW: return "EXPORT";
        case TokenType::AT_STYLE: return "@Style";
        case TokenType::AT_ELEMENT: return "@Element";
        case TokenType::AT_VAR: return "@Var";
        case TokenType::AT_HTML: return "@Html";
        case TokenType::AT_JAVASCRIPT: return "@JavaScript";
        case TokenType::AT_CHTL: return "@Chtl";
        case TokenType::COLON: return "COLON";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::EQUALS: return "EQUALS";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::ARROW: return "ARROW";
        case TokenType::AMPERSAND: return "AMPERSAND";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::SINGLE_LINE_COMMENT: return "SINGLE_LINE_COMMENT";
        case TokenType::MULTI_LINE_COMMENT: return "MULTI_LINE_COMMENT";
        case TokenType::HTML_COMMENT: return "HTML_COMMENT";
        case TokenType::DOUBLE_LEFT_BRACE: return "DOUBLE_LEFT_BRACE";
        case TokenType::DOUBLE_RIGHT_BRACE: return "DOUBLE_RIGHT_BRACE";
        case TokenType::WILDCARD: return "WILDCARD";
        case TokenType::EOF_TOKEN: return "EOF";
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

inline std::string Token::getTypeString() const {
    return tokenTypeToString(type);
}

} // namespace chtl

#endif // CHTL_TOKEN_H