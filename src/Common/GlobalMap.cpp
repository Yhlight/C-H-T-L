#include "Common/GlobalMap.h"
#include <iostream>

namespace chtl {

// 关键字映射表定义
const std::unordered_map<std::string, TokenType> GlobalMap::KEYWORD_MAP = {
    {"text", TokenType::TEXT},
    {"style", TokenType::STYLE},
    {"script", TokenType::SCRIPT_KW},
    {"inherit", TokenType::INHERIT},
    {"delete", TokenType::DELETE_KW},
    {"insert", TokenType::INSERT},
    {"after", TokenType::AFTER},
    {"before", TokenType::BEFORE},
    {"replace", TokenType::REPLACE},
    {"at", TokenType::AT},
    {"top", TokenType::TOP},
    {"bottom", TokenType::BOTTOM},
    {"from", TokenType::FROM},
    {"as", TokenType::AS},
    {"except", TokenType::EXCEPT}
};

// 特殊标记映射表定义
const std::unordered_map<std::string, TokenType> GlobalMap::SPECIAL_MARKER_MAP = {
    {"[Custom]", TokenType::CUSTOM},
    {"[Template]", TokenType::TEMPLATE},
    {"[Origin]", TokenType::ORIGIN},
    {"[Import]", TokenType::IMPORT},
    {"[Namespace]", TokenType::NAMESPACE_KW},
    {"[Configuration]", TokenType::CONFIGURATION},
    {"[Name]", TokenType::NAME},
    {"[Info]", TokenType::INFO},
    {"[Export]", TokenType::EXPORT_KW}
};

// AT前缀映射表定义
const std::unordered_map<std::string, TokenType> GlobalMap::AT_PREFIX_MAP = {
    {"@Style", TokenType::AT_STYLE},
    {"@style", TokenType::AT_STYLE},
    {"@Element", TokenType::AT_ELEMENT},
    {"@element", TokenType::AT_ELEMENT},
    {"@Var", TokenType::AT_VAR},
    {"@var", TokenType::AT_VAR},
    {"@Html", TokenType::AT_HTML},
    {"@html", TokenType::AT_HTML},
    {"@HTML", TokenType::AT_HTML},
    {"@JavaScript", TokenType::AT_JAVASCRIPT},
    {"@javascript", TokenType::AT_JAVASCRIPT},
    {"@Javascript", TokenType::AT_JAVASCRIPT},
    {"@JS", TokenType::AT_JAVASCRIPT},
    {"@js", TokenType::AT_JAVASCRIPT},
    {"@Chtl", TokenType::AT_CHTL},
    {"@chtl", TokenType::AT_CHTL},
    {"@CHTL", TokenType::AT_CHTL}
};

// HTML标签集合定义
const std::unordered_set<std::string> GlobalMap::HTML_TAGS = {
    // 文档元素
    "html", "head", "body", "title", "meta", "link", "script", "style", "base",
    
    // 结构元素
    "div", "span", "header", "footer", "main", "section", "article", "aside",
    "nav", "details", "summary", "dialog",
    
    // 文本元素
    "h1", "h2", "h3", "h4", "h5", "h6", "p", "blockquote", "pre", "code",
    "em", "strong", "small", "mark", "del", "ins", "sub", "sup", "cite",
    "q", "dfn", "abbr", "time", "var", "samp", "kbd", "data", "bdi", "bdo",
    
    // 列表元素
    "ul", "ol", "li", "dl", "dt", "dd", "menu",
    
    // 表格元素
    "table", "caption", "thead", "tbody", "tfoot", "tr", "th", "td", "col", "colgroup",
    
    // 表单元素
    "form", "input", "textarea", "button", "select", "option", "optgroup",
    "label", "fieldset", "legend", "datalist", "output", "progress", "meter",
    
    // 媒体元素
    "img", "picture", "source", "audio", "video", "track", "map", "area",
    "canvas", "svg", "math",
    
    // 嵌入元素
    "iframe", "embed", "object", "param", "portal",
    
    // 其他元素
    "a", "address", "hr", "br", "wbr", "figure", "figcaption", "ruby", "rt",
    "rp", "template", "slot"
};

// HTML单标签集合定义
const std::unordered_set<std::string> GlobalMap::HTML_SINGLE_TAGS = {
    "area", "base", "br", "col", "embed", "hr", "img", "input",
    "link", "meta", "param", "source", "track", "wbr"
};

// CSS属性集合定义
const std::unordered_set<std::string> GlobalMap::CSS_PROPERTIES = {
    // 布局
    "display", "position", "top", "right", "bottom", "left", "float", "clear",
    "z-index", "overflow", "overflow-x", "overflow-y", "visibility",
    
    // 盒模型
    "width", "height", "max-width", "max-height", "min-width", "min-height",
    "margin", "margin-top", "margin-right", "margin-bottom", "margin-left",
    "padding", "padding-top", "padding-right", "padding-bottom", "padding-left",
    "border", "border-width", "border-style", "border-color", "border-radius",
    "box-sizing", "box-shadow",
    
    // 文本
    "color", "font", "font-family", "font-size", "font-weight", "font-style",
    "line-height", "text-align", "text-decoration", "text-transform",
    "letter-spacing", "word-spacing", "white-space", "text-shadow",
    
    // 背景
    "background", "background-color", "background-image", "background-position",
    "background-repeat", "background-size", "background-attachment",
    
    // Flexbox
    "flex", "flex-direction", "flex-wrap", "flex-flow", "justify-content",
    "align-items", "align-content", "order", "flex-grow", "flex-shrink",
    "flex-basis", "align-self",
    
    // Grid
    "grid", "grid-template", "grid-template-columns", "grid-template-rows",
    "grid-template-areas", "grid-gap", "grid-column", "grid-row",
    
    // 变换和动画
    "transform", "transition", "animation", "opacity",
    
    // 其他
    "cursor", "user-select", "pointer-events", "list-style"
};

// JavaScript保留字集合定义
const std::unordered_set<std::string> GlobalMap::JS_RESERVED_WORDS = {
    "break", "case", "catch", "class", "const", "continue", "debugger",
    "default", "delete", "do", "else", "export", "extends", "finally",
    "for", "function", "if", "import", "in", "instanceof", "new",
    "return", "super", "switch", "this", "throw", "try", "typeof",
    "var", "void", "while", "with", "yield", "let", "static",
    "enum", "implements", "interface", "package", "private", "protected",
    "public", "await", "async"
};

// TokenType到字符串的映射定义
const std::unordered_map<TokenType, std::string> GlobalMap::TOKEN_TYPE_STRINGS = {
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::STRING_LITERAL, "STRING_LITERAL"},
    {TokenType::UNQUOTED_LITERAL, "UNQUOTED_LITERAL"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::TEXT, "TEXT"},
    {TokenType::STYLE, "STYLE"},
    {TokenType::INHERIT, "INHERIT"},
    {TokenType::DELETE_KW, "DELETE"},
    {TokenType::INSERT, "INSERT"},
    {TokenType::AFTER, "AFTER"},
    {TokenType::BEFORE, "BEFORE"},
    {TokenType::REPLACE, "REPLACE"},
    {TokenType::AT, "AT"},
    {TokenType::TOP, "TOP"},
    {TokenType::BOTTOM, "BOTTOM"},
    {TokenType::FROM, "FROM"},
    {TokenType::AS, "AS"},
    {TokenType::EXCEPT, "EXCEPT"},
    {TokenType::CUSTOM, "CUSTOM"},
    {TokenType::TEMPLATE, "TEMPLATE"},
    {TokenType::ORIGIN, "ORIGIN"},
    {TokenType::IMPORT, "IMPORT"},
    {TokenType::NAMESPACE_KW, "NAMESPACE"},
    {TokenType::CONFIGURATION, "CONFIGURATION"},
    {TokenType::NAME, "NAME"},
    {TokenType::INFO, "INFO"},
    {TokenType::EXPORT_KW, "EXPORT"},
    {TokenType::AT_STYLE, "@Style"},
    {TokenType::AT_ELEMENT, "@Element"},
    {TokenType::AT_VAR, "@Var"},
    {TokenType::AT_HTML, "@Html"},
    {TokenType::AT_JAVASCRIPT, "@JavaScript"},
    {TokenType::AT_CHTL, "@Chtl"},
    {TokenType::COLON, "COLON"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::EQUALS, "EQUALS"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::DOT, "DOT"},
    {TokenType::ARROW, "ARROW"},
    {TokenType::AMPERSAND, "AMPERSAND"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACKET, "LEFT_BRACKET"},
    {TokenType::RIGHT_BRACKET, "RIGHT_BRACKET"},
    {TokenType::SINGLE_LINE_COMMENT, "SINGLE_LINE_COMMENT"},
    {TokenType::MULTI_LINE_COMMENT, "MULTI_LINE_COMMENT"},
    {TokenType::HTML_COMMENT, "HTML_COMMENT"},
    {TokenType::DOUBLE_LEFT_BRACE, "DOUBLE_LEFT_BRACE"},
    {TokenType::DOUBLE_RIGHT_BRACE, "DOUBLE_RIGHT_BRACE"},
    {TokenType::WILDCARD, "WILDCARD"},
    {TokenType::EOF_TOKEN, "EOF"},
    {TokenType::UNKNOWN, "UNKNOWN"}
};

// 查询方法实现
TokenType GlobalMap::getKeywordType(const std::string& keyword) {
    auto it = KEYWORD_MAP.find(keyword);
    return (it != KEYWORD_MAP.end()) ? it->second : TokenType::UNKNOWN;
}

TokenType GlobalMap::getSpecialMarkerType(const std::string& marker) {
    auto it = SPECIAL_MARKER_MAP.find(marker);
    return (it != SPECIAL_MARKER_MAP.end()) ? it->second : TokenType::UNKNOWN;
}

TokenType GlobalMap::getAtPrefixType(const std::string& prefix) {
    auto it = AT_PREFIX_MAP.find(prefix);
    return (it != AT_PREFIX_MAP.end()) ? it->second : TokenType::UNKNOWN;
}

bool GlobalMap::isHtmlTag(const std::string& tag) {
    return HTML_TAGS.find(tag) != HTML_TAGS.end();
}

bool GlobalMap::isHtmlSingleTag(const std::string& tag) {
    return HTML_SINGLE_TAGS.find(tag) != HTML_SINGLE_TAGS.end();
}

bool GlobalMap::isCssProperty(const std::string& property) {
    return CSS_PROPERTIES.find(property) != CSS_PROPERTIES.end();
}

bool GlobalMap::isJsReservedWord(const std::string& word) {
    return JS_RESERVED_WORDS.find(word) != JS_RESERVED_WORDS.end();
}

std::string GlobalMap::tokenTypeToString(TokenType type) {
    auto it = TOKEN_TYPE_STRINGS.find(type);
    return (it != TOKEN_TYPE_STRINGS.end()) ? it->second : "UNKNOWN";
}

// 调试方法实现
void GlobalMap::printKeywords() {
    std::cout << "=== CHTL Keywords ===" << std::endl;
    for (const auto& [keyword, type] : KEYWORD_MAP) {
        std::cout << keyword << " -> " << tokenTypeToString(type) << std::endl;
    }
}

void GlobalMap::printHtmlTags() {
    std::cout << "=== HTML Tags ===" << std::endl;
    for (const auto& tag : HTML_TAGS) {
        std::cout << tag;
        if (HTML_SINGLE_TAGS.find(tag) != HTML_SINGLE_TAGS.end()) {
            std::cout << " (self-closing)";
        }
        std::cout << std::endl;
    }
}

void GlobalMap::printTokenTypes() {
    std::cout << "=== Token Types ===" << std::endl;
    for (const auto& [type, str] : TOKEN_TYPE_STRINGS) {
        std::cout << str << std::endl;
    }
}

} // namespace chtl