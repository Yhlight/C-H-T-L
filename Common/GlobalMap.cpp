#include "GlobalMap.h"

namespace CHTL {

GlobalMap& GlobalMap::getInstance() {
    static GlobalMap instance;
    return instance;
}

void GlobalMap::initialize() {
    if (initialized_) return;
    
    initializeKeywords();
    initializeHTMLTags();
    initializeCSSProperties();
    initializeVoidElements();
    initializeDefaultConfigs();
    
    initialized_ = true;
}

void GlobalMap::initializeKeywords() {
    // CHTL关键字
    keywordMap_["text"] = TokenType::TEXT;
    keywordMap_["style"] = TokenType::STYLE;
    keywordMap_["script"] = TokenType::SCRIPT;
    keywordMap_["Template"] = TokenType::TEMPLATE;
    keywordMap_["Custom"] = TokenType::CUSTOM;
    keywordMap_["Origin"] = TokenType::ORIGIN;
    keywordMap_["Import"] = TokenType::IMPORT;
    keywordMap_["Namespace"] = TokenType::NAMESPACE;
    keywordMap_["Configuration"] = TokenType::CONFIGURATION;
    keywordMap_["Name"] = TokenType::NAME;
    keywordMap_["Info"] = TokenType::INFO;
    keywordMap_["Export"] = TokenType::EXPORT;
    
    // 修饰符
    keywordMap_["inherit"] = TokenType::INHERIT;
    keywordMap_["delete"] = TokenType::DELETE;
    keywordMap_["insert"] = TokenType::INSERT;
    keywordMap_["except"] = TokenType::EXCEPT;
    keywordMap_["from"] = TokenType::FROM;
    keywordMap_["as"] = TokenType::AS;
    
    // 位置关键字
    keywordMap_["after"] = TokenType::AFTER;
    keywordMap_["before"] = TokenType::BEFORE;
    keywordMap_["replace"] = TokenType::REPLACE;
    keywordMap_["at"] = TokenType::AT_TOP;  // 需要特殊处理 "at top" 和 "at bottom"
    
    // JavaScript关键字
    keywordMap_["var"] = TokenType::VAR;
    keywordMap_["let"] = TokenType::LET;
    keywordMap_["const"] = TokenType::CONST;
    keywordMap_["function"] = TokenType::FUNCTION;
    keywordMap_["class"] = TokenType::CLASS;
    keywordMap_["if"] = TokenType::IF;
    keywordMap_["else"] = TokenType::ELSE;
    keywordMap_["for"] = TokenType::FOR;
    keywordMap_["while"] = TokenType::WHILE;
    keywordMap_["do"] = TokenType::DO;
    keywordMap_["return"] = TokenType::RETURN;
    keywordMap_["break"] = TokenType::BREAK;
    keywordMap_["continue"] = TokenType::CONTINUE;
    keywordMap_["switch"] = TokenType::SWITCH;
    keywordMap_["case"] = TokenType::CASE;
    keywordMap_["default"] = TokenType::DEFAULT;
    keywordMap_["try"] = TokenType::TRY;
    keywordMap_["catch"] = TokenType::CATCH;
    keywordMap_["finally"] = TokenType::FINALLY;
    keywordMap_["throw"] = TokenType::THROW;
    keywordMap_["new"] = TokenType::NEW;
    keywordMap_["this"] = TokenType::THIS;
    keywordMap_["super"] = TokenType::SUPER;
    keywordMap_["async"] = TokenType::ASYNC;
    keywordMap_["await"] = TokenType::AWAIT;
    keywordMap_["yield"] = TokenType::YIELD;
    
    // CHTL JS扩展关键字
    keywordMap_["listen"] = TokenType::LISTEN;
    keywordMap_["delegate"] = TokenType::DELEGATE;
    keywordMap_["animate"] = TokenType::ANIMATE;
    keywordMap_["target"] = TokenType::TARGET;
    keywordMap_["duration"] = TokenType::DURATION;
    keywordMap_["easing"] = TokenType::EASING;
    keywordMap_["begin"] = TokenType::BEGIN;
    keywordMap_["end"] = TokenType::END;
    keywordMap_["when"] = TokenType::WHEN;
    keywordMap_["loop"] = TokenType::LOOP;
    keywordMap_["delay"] = TokenType::DELAY;
    keywordMap_["callback"] = TokenType::CALLBACK;
    
    // 初始化反向映射
    for (const auto& pair : keywordMap_) {
        tokenNameMap_[pair.second] = pair.first;
    }
}

void GlobalMap::initializeHTMLTags() {
    // 常用HTML5标签
    const std::vector<std::string> htmlTags = {
        // 文档结构
        "html", "head", "body", "title", "meta", "link", "style", "script", "base",
        
        // 内容分区
        "header", "nav", "main", "aside", "footer", "section", "article", "address",
        
        // 文本内容
        "h1", "h2", "h3", "h4", "h5", "h6", "p", "div", "span", "blockquote", "pre",
        "hr", "ul", "ol", "li", "dl", "dt", "dd", "figure", "figcaption",
        
        // 内联文本语义
        "a", "em", "strong", "small", "s", "cite", "q", "dfn", "abbr", "ruby", "rt",
        "rp", "data", "time", "code", "var", "samp", "kbd", "sub", "sup", "i", "b",
        "u", "mark", "bdi", "bdo", "wbr",
        
        // 图片和多媒体
        "img", "iframe", "embed", "object", "param", "video", "audio", "source",
        "track", "map", "area", "canvas", "svg", "math",
        
        // 表格
        "table", "caption", "colgroup", "col", "tbody", "thead", "tfoot", "tr",
        "td", "th",
        
        // 表单
        "form", "label", "input", "button", "select", "datalist", "optgroup",
        "option", "textarea", "output", "progress", "meter", "fieldset", "legend",
        
        // 交互元素
        "details", "summary", "dialog", "menu",
        
        // 其他
        "template", "slot", "picture"
    };
    
    for (const auto& tag : htmlTags) {
        htmlTags_[tag] = true;
    }
}

void GlobalMap::initializeCSSProperties() {
    // 常用CSS属性
    const std::vector<std::string> cssProperties = {
        // 布局
        "display", "position", "top", "right", "bottom", "left", "float", "clear",
        "z-index", "overflow", "overflow-x", "overflow-y", "visibility",
        
        // 盒模型
        "width", "height", "min-width", "min-height", "max-width", "max-height",
        "margin", "margin-top", "margin-right", "margin-bottom", "margin-left",
        "padding", "padding-top", "padding-right", "padding-bottom", "padding-left",
        "border", "border-width", "border-style", "border-color", "border-radius",
        
        // 背景
        "background", "background-color", "background-image", "background-repeat",
        "background-position", "background-size", "background-clip", "background-origin",
        
        // 文本
        "color", "font", "font-family", "font-size", "font-weight", "font-style",
        "line-height", "text-align", "text-decoration", "text-transform", "text-indent",
        "letter-spacing", "word-spacing", "white-space", "text-overflow",
        
        // Flexbox
        "flex", "flex-direction", "flex-wrap", "flex-flow", "justify-content",
        "align-items", "align-content", "align-self", "order", "flex-grow",
        "flex-shrink", "flex-basis", "gap", "row-gap", "column-gap",
        
        // Grid
        "grid", "grid-template", "grid-template-columns", "grid-template-rows",
        "grid-template-areas", "grid-column", "grid-row", "grid-area",
        
        // 变换和动画
        "transform", "transform-origin", "transition", "transition-property",
        "transition-duration", "transition-timing-function", "transition-delay",
        "animation", "animation-name", "animation-duration", "animation-timing-function",
        
        // 其他
        "opacity", "cursor", "user-select", "pointer-events", "box-shadow", "filter"
    };
    
    for (const auto& prop : cssProperties) {
        cssProperties_[prop] = true;
    }
}

void GlobalMap::initializeVoidElements() {
    // HTML void元素（自闭合标签）
    const std::vector<std::string> voidElements = {
        "area", "base", "br", "col", "embed", "hr", "img", "input",
        "link", "meta", "param", "source", "track", "wbr"
    };
    
    for (const auto& elem : voidElements) {
        voidElements_[elem] = true;
    }
}

void GlobalMap::initializeDefaultConfigs() {
    // CHTL默认配置
    defaultConfigs_["INDEX_INITIAL_COUNT"] = "0";
    defaultConfigs_["DISABLE_NAME_GROUP"] = "false";
    defaultConfigs_["DEBUG_MODE"] = "false";
    defaultConfigs_["OPTION_COUNT"] = "3";
}

TokenType GlobalMap::getTokenType(const std::string& keyword) const {
    auto it = keywordMap_.find(keyword);
    if (it != keywordMap_.end()) {
        return it->second;
    }
    return TokenType::UNKNOWN;
}

std::string GlobalMap::getTokenName(TokenType type) const {
    auto it = tokenNameMap_.find(type);
    if (it != tokenNameMap_.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

bool GlobalMap::isKeyword(const std::string& word) const {
    return keywordMap_.find(word) != keywordMap_.end();
}

bool GlobalMap::isHTMLTag(const std::string& tag) const {
    return htmlTags_.find(tag) != htmlTags_.end();
}

bool GlobalMap::isCSSProperty(const std::string& property) const {
    return cssProperties_.find(property) != cssProperties_.end();
}

bool GlobalMap::isVoidElement(const std::string& tag) const {
    return voidElements_.find(tag) != voidElements_.end();
}

std::string GlobalMap::getDefaultConfig(const std::string& key) const {
    auto it = defaultConfigs_.find(key);
    if (it != defaultConfigs_.end()) {
        return it->second;
    }
    return "";
}

void GlobalMap::registerCustomKeyword(const std::string& name, const std::vector<std::string>& values) {
    customKeywords_[name] = values;
}

std::vector<std::string> GlobalMap::getCustomKeyword(const std::string& name) const {
    auto it = customKeywords_.find(name);
    if (it != customKeywords_.end()) {
        return it->second;
    }
    return {};
}

} // namespace CHTL