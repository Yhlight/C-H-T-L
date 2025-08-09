#include "common/GlobalMap.h"
#include <iostream>
#include <algorithm>

namespace chtl {

// 静态成员初始化
std::unique_ptr<GlobalMap> GlobalMap::instance = nullptr;

GlobalMap::GlobalMap() {
    // 构造函数中调用初始化
    initialize();
}

GlobalMap& GlobalMap::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<GlobalMap>(new GlobalMap());
    }
    return *instance;
}

void GlobalMap::initialize() {
    initializeKeywords();
    initializeSpecialMarkers();
    initializeAtPrefixes();
    initializeHtmlTags();
    initializeCssProperties();
    initializeJsReservedWords();
}

void GlobalMap::initializeKeywords() {
    // CHTL关键字
    keywordMap["text"] = TokenType::TEXT;
    keywordMap["style"] = TokenType::STYLE;
    keywordMap["inherit"] = TokenType::INHERIT;
    keywordMap["delete"] = TokenType::DELETE_KW;
    keywordMap["insert"] = TokenType::INSERT;
    keywordMap["after"] = TokenType::AFTER;
    keywordMap["before"] = TokenType::BEFORE;
    keywordMap["replace"] = TokenType::REPLACE;
    keywordMap["at"] = TokenType::AT;
    keywordMap["top"] = TokenType::TOP;
    keywordMap["bottom"] = TokenType::BOTTOM;
    keywordMap["from"] = TokenType::FROM;
    keywordMap["as"] = TokenType::AS;
    keywordMap["except"] = TokenType::EXCEPT;
}

void GlobalMap::initializeSpecialMarkers() {
    // 特殊标记
    specialMarkerMap["[Custom]"] = TokenType::CUSTOM;
    specialMarkerMap["[Template]"] = TokenType::TEMPLATE;
    specialMarkerMap["[Origin]"] = TokenType::ORIGIN;
    specialMarkerMap["[Import]"] = TokenType::IMPORT;
    specialMarkerMap["[Namespace]"] = TokenType::NAMESPACE_KW;
    specialMarkerMap["[Configuration]"] = TokenType::CONFIGURATION;
    specialMarkerMap["[Name]"] = TokenType::NAME;
    specialMarkerMap["[Info]"] = TokenType::INFO;
    specialMarkerMap["[Export]"] = TokenType::EXPORT_KW;
}

void GlobalMap::initializeAtPrefixes() {
    // AT前缀
    atPrefixMap["@Style"] = TokenType::AT_STYLE;
    atPrefixMap["@style"] = TokenType::AT_STYLE;  // 支持小写变体
    atPrefixMap["@Element"] = TokenType::AT_ELEMENT;
    atPrefixMap["@element"] = TokenType::AT_ELEMENT;
    atPrefixMap["@Var"] = TokenType::AT_VAR;
    atPrefixMap["@var"] = TokenType::AT_VAR;
    atPrefixMap["@Html"] = TokenType::AT_HTML;
    atPrefixMap["@html"] = TokenType::AT_HTML;
    atPrefixMap["@JavaScript"] = TokenType::AT_JAVASCRIPT;
    atPrefixMap["@javascript"] = TokenType::AT_JAVASCRIPT;
    atPrefixMap["@Javascript"] = TokenType::AT_JAVASCRIPT;
    atPrefixMap["@JS"] = TokenType::AT_JAVASCRIPT;
    atPrefixMap["@js"] = TokenType::AT_JAVASCRIPT;
    atPrefixMap["@Chtl"] = TokenType::AT_CHTL;
    atPrefixMap["@chtl"] = TokenType::AT_CHTL;
    atPrefixMap["@CHTL"] = TokenType::AT_CHTL;
}

void GlobalMap::initializeHtmlTags() {
    // HTML5标签
    const std::vector<std::string> tags = {
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
    
    for (const auto& tag : tags) {
        htmlTags.insert(tag);
    }
    
    // HTML单标签（自闭合标签）
    const std::vector<std::string> singleTags = {
        "area", "base", "br", "col", "embed", "hr", "img", "input",
        "link", "meta", "param", "source", "track", "wbr"
    };
    
    for (const auto& tag : singleTags) {
        htmlSingleTags.insert(tag);
    }
}

void GlobalMap::initializeCssProperties() {
    // 常用CSS属性
    const std::vector<std::string> properties = {
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
    
    for (const auto& prop : properties) {
        cssProperties.insert(prop);
    }
}

void GlobalMap::initializeJsReservedWords() {
    // JavaScript保留字
    const std::vector<std::string> reserved = {
        "break", "case", "catch", "class", "const", "continue", "debugger",
        "default", "delete", "do", "else", "export", "extends", "finally",
        "for", "function", "if", "import", "in", "instanceof", "new",
        "return", "super", "switch", "this", "throw", "try", "typeof",
        "var", "void", "while", "with", "yield", "let", "static",
        "enum", "implements", "interface", "package", "private", "protected",
        "public", "await", "async"
    };
    
    for (const auto& word : reserved) {
        jsReservedWords.insert(word);
    }
}

TokenType GlobalMap::getKeywordType(const std::string& keyword) const {
    auto it = keywordMap.find(keyword);
    if (it != keywordMap.end()) {
        return it->second;
    }
    
    // 检查配置别名
    for (const auto& [key, aliases] : configKeywordAliases) {
        if (std::find(aliases.begin(), aliases.end(), keyword) != aliases.end()) {
            auto keyIt = keywordMap.find(key);
            if (keyIt != keywordMap.end()) {
                return keyIt->second;
            }
        }
    }
    
    return TokenType::UNKNOWN;
}

TokenType GlobalMap::getSpecialMarkerType(const std::string& marker) const {
    auto it = specialMarkerMap.find(marker);
    return (it != specialMarkerMap.end()) ? it->second : TokenType::UNKNOWN;
}

TokenType GlobalMap::getAtPrefixType(const std::string& prefix) const {
    auto it = atPrefixMap.find(prefix);
    return (it != atPrefixMap.end()) ? it->second : TokenType::UNKNOWN;
}

bool GlobalMap::isHtmlTag(const std::string& tag) const {
    return htmlTags.find(tag) != htmlTags.end();
}

bool GlobalMap::isHtmlSingleTag(const std::string& tag) const {
    return htmlSingleTags.find(tag) != htmlSingleTags.end();
}

bool GlobalMap::isCssProperty(const std::string& property) const {
    return cssProperties.find(property) != cssProperties.end();
}

bool GlobalMap::isJsReservedWord(const std::string& word) const {
    return jsReservedWords.find(word) != jsReservedWords.end();
}

void GlobalMap::addKeywordAlias(const std::string& keyword, const std::string& alias) {
    configKeywordAliases[keyword].push_back(alias);
}

void GlobalMap::setKeywordAliases(const std::string& keyword, const std::vector<std::string>& aliases) {
    configKeywordAliases[keyword] = aliases;
}

std::vector<std::string> GlobalMap::getKeywordAliases(const std::string& keyword) const {
    auto it = configKeywordAliases.find(keyword);
    return (it != configKeywordAliases.end()) ? it->second : std::vector<std::string>();
}

void GlobalMap::printKeywords() const {
    std::cout << "=== CHTL Keywords ===" << std::endl;
    for (const auto& [keyword, type] : keywordMap) {
        std::cout << keyword << " -> " << tokenTypeToString(type) << std::endl;
    }
}

void GlobalMap::printHtmlTags() const {
    std::cout << "=== HTML Tags ===" << std::endl;
    for (const auto& tag : htmlTags) {
        std::cout << tag;
        if (htmlSingleTags.find(tag) != htmlSingleTags.end()) {
            std::cout << " (self-closing)";
        }
        std::cout << std::endl;
    }
}

} // namespace chtl