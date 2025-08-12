#include "v2/Lexer/ChtlLexer.h"
#include "v2/State/ChtlStateMachine.h"
#include <cctype>
#include <iostream>

namespace chtl::v2 {

// 静态数据定义
const std::unordered_set<std::string> ChtlLexer::HTML_TAGS = {
    "div", "span", "p", "a", "img", "h1", "h2", "h3", "h4", "h5", "h6",
    "ul", "ol", "li", "table", "tr", "td", "th", "form", "input", "button",
    "header", "footer", "nav", "main", "section", "article", "aside",
    "body", "head", "html", "meta", "link", "script", "style", "title"
};

const std::unordered_set<std::string> ChtlLexer::CSS_PROPERTIES = {
    "color", "background", "margin", "padding", "border", "width", "height",
    "display", "position", "top", "left", "right", "bottom", "font-size",
    "font-family", "text-align", "overflow", "z-index", "opacity"
};

const std::unordered_map<std::string, TokenType> ChtlLexer::KEYWORDS = {
    {"style", TokenType::STYLE},
    {"script", TokenType::SCRIPT},
    {"text", TokenType::TEXT},
    {"inherit", TokenType::INHERIT},
    {"delete", TokenType::DELETE},
    {"insert", TokenType::INSERT},
    {"Template", TokenType::TEMPLATE},
    {"Custom", TokenType::CUSTOM},
    {"Import", TokenType::IMPORT},
    {"Configuration", TokenType::CONFIGURATION},
    {"Origin", TokenType::ORIGIN},
    {"Export", TokenType::EXPORT},
    {"Info", TokenType::INFO},
    {"as", TokenType::AS}
};

ChtlLexer::ChtlLexer(const std::string& input) 
    : input_(input)
    , current_(0)
    , start_(0)
    , line_(1)
    , column_(1)
    , tokenStartLine_(1)
    , tokenStartColumn_(1)
    , stateMachine_(nullptr)
    , currentState_(ChtlParseState::INITIAL) {
}

ChtlLexer::~ChtlLexer() = default;

Token ChtlLexer::nextToken() {
    // 如果有缓冲的 token，先返回
    if (!tokenBuffer_.empty()) {
        Token token = tokenBuffer_.front();
        tokenBuffer_.pop();
        return token;
    }
    
    return scanToken();
}

Token ChtlLexer::peekToken() {
    if (tokenBuffer_.empty()) {
        tokenBuffer_.push(scanToken());
    }
    return tokenBuffer_.front();
}

Token ChtlLexer::peekToken(size_t ahead) {
    while (tokenBuffer_.size() <= ahead) {
        tokenBuffer_.push(scanToken());
    }
    
    // 创建临时队列来访问第 N 个元素
    std::queue<Token> temp;
    Token result;
    
    for (size_t i = 0; i <= ahead; ++i) {
        Token t = tokenBuffer_.front();
        tokenBuffer_.pop();
        temp.push(t);
        if (i == ahead) result = t;
    }
    
    // 恢复队列
    while (!temp.empty()) {
        tokenBuffer_.push(temp.front());
        temp.pop();
    }
    
    return result;
}

bool ChtlLexer::isAtEnd() const {
    return current_ >= input_.length();
}

void ChtlLexer::reset() {
    current_ = 0;
    start_ = 0;
    line_ = 1;
    column_ = 1;
    tokenStartLine_ = 1;
    tokenStartColumn_ = 1;
    while (!tokenBuffer_.empty()) {
        tokenBuffer_.pop();
    }
}

void ChtlLexer::setCurrentState(ChtlParseState state) {
    currentState_ = state;
}

Token ChtlLexer::scanToken() {
    // 跳过空白符
    skipWhitespace();
    
    if (isAtEnd()) {
        return makeToken(TokenType::EOF_TOKEN);
    }
    
    start_ = current_;
    tokenStartLine_ = line_;
    tokenStartColumn_ = column_;
    
    // 根据当前状态选择扫描方法
    switch (currentState_) {
        case ChtlParseState::INITIAL:
            return scanInTopLevel();
            
        case ChtlParseState::ELEMENT:
        case ChtlParseState::ELEMENT_CONTENT:
            return scanInElementContent();
            
        case ChtlParseState::STYLE:
        case ChtlParseState::STYLE_CONTENT:
            return scanInStyleContent();
            
        case ChtlParseState::SCRIPT:
        case ChtlParseState::SCRIPT_CONTENT:
            return scanInScriptContent();
            
        case ChtlParseState::TEXT:
        case ChtlParseState::TEXT_CONTENT:
            return scanInTextContent();
            
        default:
            return scanInTopLevel();
    }
}

Token ChtlLexer::scanInTopLevel() {
    char c = advance();
    
    // 单字符 token
    switch (c) {
        case '{': return makeToken(TokenType::LEFT_BRACE);
        case '}': return makeToken(TokenType::RIGHT_BRACE);
        case '[': return makeToken(TokenType::LEFT_BRACKET);
        case ']': return makeToken(TokenType::RIGHT_BRACKET);
        case '(': return makeToken(TokenType::LEFT_PAREN);
        case ')': return makeToken(TokenType::RIGHT_PAREN);
        case ';': return makeToken(TokenType::SEMICOLON);
        case ':': return makeToken(TokenType::COLON);
        case ',': return makeToken(TokenType::COMMA);
        case '.': return makeToken(TokenType::DOT);
        case '#': return makeToken(TokenType::HASH);
        case '=': return makeToken(TokenType::EQUALS);
        case '@': {
            // 可能是 @Element, @Style 等
            if (isAlpha(peek())) {
                return scanAtReference();
            }
            return makeToken(TokenType::AT);
        }
        case '"': return scanString();
        case '/':
            if (peek() == '/') {
                return scanComment();
            }
            return makeToken(TokenType::SLASH);
    }
    
    // 标识符或关键字
    if (isAlpha(c)) {
        // 回退一个字符，因为已经 advance 了
        current_--;
        column_--;
        return scanIdentifier();
    }
    
    // 数字
    if (isDigit(c)) {
        // 回退一个字符
        current_--;
        column_--;
        return scanNumber();
    }
    
    return makeError("Unexpected character");
}

Token ChtlLexer::scanInElementContent() {
    // 在元素内容中的扫描逻辑
    // 大部分与 scanInTopLevel 相同，但有一些差异
    return scanInTopLevel();
}

Token ChtlLexer::scanInStyleContent() {
    // 在样式内容中，我们需要整块收集
    // 但仍需要识别某些特殊结构（如 text { }）
    char c = advance();
    
    if (c == '}') {
        return makeToken(TokenType::RIGHT_BRACE);
    }
    
    if (c == 't' && matchSequence("ext")) {
        return makeToken(TokenType::TEXT);
    }
    
    // 否则收集到下一个特殊字符
    while (!isAtEnd() && peek() != '{' && peek() != '}') {
        advance();
    }
    
    return makeToken(TokenType::CSS_VALUE);
}

Token ChtlLexer::scanInScriptContent() {
    // 脚本内容整块传递给 JS 分析器
    // CHTL 词法分析器不解析 JS 语法
    std::string scriptContent;
    int braceDepth = 1;
    
    while (!isAtEnd() && braceDepth > 0) {
        char c = advance();
        if (c == '{') braceDepth++;
        else if (c == '}') braceDepth--;
        
        if (braceDepth > 0) {
            scriptContent += c;
        }
    }
    
    Token token = makeToken(TokenType::SCRIPT_CONTENT, scriptContent);
    token.metadata.contextHint = "javascript";
    return token;
}

Token ChtlLexer::scanInTextContent() {
    // text 块中的内容
    char c = peek();
    
    if (c == '"') {
        advance();
        return scanString();
    }
    
    if (c == '{') {
        advance();
        return makeToken(TokenType::LEFT_BRACE);
    }
    
    if (c == '}') {
        advance();
        return makeToken(TokenType::RIGHT_BRACE);
    }
    
    // 模板参数引用
    if (isAlpha(c)) {
        return scanIdentifier();
    }
    
    return makeError("Unexpected character in text block");
}

Token ChtlLexer::scanIdentifier() {
    while (isAlpha(peek()) || isDigit(peek()) || peek() == '-' || peek() == '_') {
        advance();
    }
    
    std::string text = input_.substr(start_, current_ - start_);
    TokenType type = determineIdentifierType(text);
    return makeToken(type, text);
}

Token ChtlLexer::scanString() {
    // 已经消费了开始的 "
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line_++;
            column_ = 1;
        }
        advance();
    }
    
    if (isAtEnd()) {
        return makeError("Unterminated string");
    }
    
    // 消费结束的 "
    advance();
    
    // 去掉引号
    std::string value = input_.substr(start_ + 1, current_ - start_ - 2);
    return makeToken(TokenType::STRING, value);
}

Token ChtlLexer::scanNumber() {
    while (isDigit(peek())) {
        advance();
    }
    
    // 小数部分
    if (peek() == '.' && isDigit(peekNext())) {
        advance(); // 消费 .
        while (isDigit(peek())) {
            advance();
        }
    }
    
    return makeToken(TokenType::NUMBER);
}

Token ChtlLexer::scanComment() {
    // 已经看到了 //
    advance(); // 消费第二个 /
    
    while (peek() != '\n' && !isAtEnd()) {
        advance();
    }
    
    return makeToken(TokenType::COMMENT);
}

Token ChtlLexer::scanAtReference() {
    // @ 后面跟着标识符
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
    }
    
    std::string text = input_.substr(start_ + 1, current_ - start_ - 1);
    
    if (text == "Element") return makeToken(TokenType::AT_ELEMENT);
    if (text == "Style") return makeToken(TokenType::AT_STYLE);
    if (text == "Var") return makeToken(TokenType::AT_VAR);
    if (text == "Html") return makeToken(TokenType::AT_HTML);
    if (text == "JavaScript") return makeToken(TokenType::AT_JAVASCRIPT);
    if (text == "Chtl") return makeToken(TokenType::AT_CHTL);
    if (text == "CJMOD") return makeToken(TokenType::AT_CJMOD);
    
    return makeToken(TokenType::UNKNOWN);
}

TokenType ChtlLexer::determineIdentifierType(const std::string& text) {
    // 检查是否是关键字
    auto it = KEYWORDS.find(text);
    if (it != KEYWORDS.end()) {
        return it->second;
    }
    
    // 创建标识符 token
    Token token(TokenType::IDENTIFIER, text, tokenStartLine_, tokenStartColumn_);
    
    // 设置元数据
    token.metadata.isHtmlTag = isHtmlTag(text);
    token.metadata.isCssProperty = isCssProperty(text);
    
    return TokenType::IDENTIFIER;
}

char ChtlLexer::advance() {
    if (isAtEnd()) return '\0';
    
    char c = input_[current_++];
    column_++;
    
    if (c == '\n') {
        line_++;
        column_ = 1;
    }
    
    return c;
}

char ChtlLexer::peek() const {
    if (isAtEnd()) return '\0';
    return input_[current_];
}

char ChtlLexer::peekNext() const {
    if (current_ + 1 >= input_.length()) return '\0';
    return input_[current_ + 1];
}

bool ChtlLexer::match(char expected) {
    if (isAtEnd()) return false;
    if (input_[current_] != expected) return false;
    
    advance();
    return true;
}

bool ChtlLexer::matchSequence(const std::string& seq) {
    for (size_t i = 0; i < seq.length(); ++i) {
        if (current_ + i >= input_.length() || input_[current_ + i] != seq[i]) {
            return false;
        }
    }
    
    current_ += seq.length();
    column_ += seq.length();
    return true;
}

void ChtlLexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t') {
            advance();
        } else if (c == '\n') {
            line_++;
            column_ = 1;
            advance();
        } else {
            break;
        }
    }
}

bool ChtlLexer::isHtmlTag(const std::string& text) const {
    return HTML_TAGS.find(text) != HTML_TAGS.end();
}

bool ChtlLexer::isCssProperty(const std::string& text) const {
    return CSS_PROPERTIES.find(text) != CSS_PROPERTIES.end();
}

bool ChtlLexer::isKeyword(const std::string& text) const {
    return KEYWORDS.find(text) != KEYWORDS.end();
}

Token ChtlLexer::makeToken(TokenType type, const std::string& value) {
    std::string tokenValue = value.empty() ? 
        input_.substr(start_, current_ - start_) : value;
    
    Token token(type, tokenValue, tokenStartLine_, tokenStartColumn_);
    
    // 如果是标识符，设置元数据
    if (type == TokenType::IDENTIFIER) {
        token.metadata.isHtmlTag = isHtmlTag(tokenValue);
        token.metadata.isCssProperty = isCssProperty(tokenValue);
    }
    
    return token;
}

Token ChtlLexer::makeToken(TokenType type) {
    return makeToken(type, "");
}

Token ChtlLexer::makeError(const std::string& message) {
    Token token = makeToken(TokenType::ERROR, message);
    return token;
}

} // namespace chtl::v2