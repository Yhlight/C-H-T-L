#pragma once

#include <string>
#include <variant>

namespace chtl::v2 {

/**
 * Token 类型
 * 注意：某些类型的确定依赖于当前的解析状态
 */
enum class TokenType {
    // ===== 字面量 =====
    IDENTIFIER,         // 标识符（具体含义依赖状态）
    STRING,             // 字符串字面量
    NUMBER,             // 数字字面量
    
    // ===== 关键字（状态相关） =====
    STYLE,              // style（在不同状态下含义不同）
    SCRIPT,             // script
    TEXT,               // text
    INHERIT,            // inherit
    DELETE,             // delete
    INSERT,             // insert
    
    // ===== 声明标记 =====
    TEMPLATE,           // Template（在 [ ] 内）
    CUSTOM,             // Custom（在 [ ] 内）
    IMPORT,             // Import（在 [ ] 内或独立）
    CONFIGURATION,      // Configuration
    ORIGIN,             // Origin
    EXPORT,             // Export
    INFO,               // Info
    
    // ===== 引用标记 =====
    AT_ELEMENT,         // @Element
    AT_STYLE,           // @Style
    AT_VAR,             // @Var
    AT_HTML,            // @Html
    AT_JAVASCRIPT,      // @JavaScript
    AT_CHTL,            // @Chtl
    AT_CJMOD,           // @CJMOD
    
    // ===== 操作符 =====
    LEFT_BRACE,         // {
    RIGHT_BRACE,        // }
    LEFT_BRACKET,       // [
    RIGHT_BRACKET,      // ]
    LEFT_PAREN,         // (
    RIGHT_PAREN,        // )
    SEMICOLON,          // ;
    COLON,              // :
    COMMA,              // ,
    DOT,                // .
    HASH,               // # (含义依赖状态)
    AT,                 // @
    EQUALS,             // =
    ARROW,              // ->
    SLASH,              // /
    AS,                 // as (关键字)
    
    // ===== CSS 特定 =====
    CSS_PROPERTY,       // CSS 属性名（仅在 CSS 上下文）
    CSS_VALUE,          // CSS 值（仅在 CSS 属性值上下文）
    CSS_UNIT,           // CSS 单位（px, em, % 等）
    
    // ===== JS 特定 =====
    SCRIPT_CONTENT,     // 整块脚本内容
    
    // ===== CHTL-JS 特定 =====
    DOUBLE_LEFT_BRACE,  // {{
    DOUBLE_RIGHT_BRACE, // }}
    AMPERSAND,          // &
    
    // ===== 特殊 =====
    WHITESPACE,         // 空白符
    NEWLINE,            // 换行符
    COMMENT,            // 注释
    EOF_TOKEN,          // 文件结束
    
    // ===== 错误 =====
    UNKNOWN,            // 未知 token
    ERROR               // 错误 token
};

/**
 * Token 结构
 */
struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
    
    // 额外的元数据（可选）
    struct Metadata {
        bool isHtmlTag = false;      // 是否是 HTML 标签
        bool isCssProperty = false;  // 是否是 CSS 属性
        bool isTemplateParam = false; // 是否是模板参数
        std::string contextHint;      // 上下文提示（用于调试）
    } metadata;
    
    Token() : type(TokenType::UNKNOWN), line(1), column(1) {}
    
    Token(TokenType t, const std::string& v, int l, int c)
        : type(t), value(v), line(l), column(c) {}
    
    bool is(TokenType t) const { return type == t; }
    bool isOneOf(std::initializer_list<TokenType> types) const {
        for (auto t : types) {
            if (type == t) return true;
        }
        return false;
    }
    
    bool isKeyword() const {
        return isOneOf({
            TokenType::STYLE, TokenType::SCRIPT, TokenType::TEXT,
            TokenType::INHERIT, TokenType::DELETE, TokenType::INSERT
        });
    }
    
    bool isDeclaration() const {
        return isOneOf({
            TokenType::TEMPLATE, TokenType::CUSTOM, TokenType::IMPORT,
            TokenType::CONFIGURATION, TokenType::ORIGIN, TokenType::EXPORT,
            TokenType::INFO
        });
    }
    
    bool isReference() const {
        return isOneOf({
            TokenType::AT_ELEMENT, TokenType::AT_STYLE, TokenType::AT_VAR,
            TokenType::AT_HTML, TokenType::AT_JAVASCRIPT, TokenType::AT_CHTL,
            TokenType::AT_CJMOD
        });
    }
    
    std::string toString() const;
};

/**
 * 获取 Token 类型名称（用于调试）
 */
const char* getTokenTypeName(TokenType type);

} // namespace chtl::v2