#include "Lexer/ChtlJsLexer.h"
#include <cctype>

namespace chtl {

ChtlJsLexer::ChtlJsLexer() 
    : BasicLexer(),
      inChtlSequence_(false) {
}

void ChtlJsLexer::initialize(std::shared_ptr<ChtlJsState> state, 
                            std::shared_ptr<ChtlJsContext> context) {
    if (state) {
        chtlJsState_ = state;
    } else {
        chtlJsState_ = std::make_shared<ChtlJsState>(this);
    }
    
    if (context) {
        chtlJsContext_ = context;
    } else {
        chtlJsContext_ = std::make_shared<ChtlJsContext>();
    }
    
    // 设置初始上下文
    context_ = chtlJsContext_;
}

Token ChtlJsLexer::getNextToken() {
    if (!chtlJsState_ || !chtlJsContext_) {
        initialize();
    }
    
    skipWhitespace();
    
    if (position_ >= input_.size()) {
        return Token(TokenType::EOF_TOKEN, "", currentLine_, currentColumn_);
    }
    
    // 检查CHTL-JS特殊语法
    if (checkChtlSequence("{{")) {
        return recognizeChtlSelector();
    }
    
    if (checkChtlSequence("->")) {
        return recognizeChtlArrow();
    }
    
    // 处理标准JavaScript
    return recognizeToken();
}

Token ChtlJsLexer::peekNextToken() {
    size_t savedPos = position_;
    int savedLine = currentLine_;
    int savedCol = currentColumn_;
    
    Token token = getNextToken();
    
    position_ = savedPos;
    currentLine_ = savedLine;
    currentColumn_ = savedCol;
    
    return token;
}

void ChtlJsLexer::reset() {
    // 重置状态
    currentLine_ = 1;
    currentColumn_ = 1;
    position_ = 0;
    
    tokenBuffer_.clear();
    inChtlSequence_ = false;
    if (chtlJsState_) {
        chtlJsState_->reset();
    }
    if (chtlJsContext_) {
        chtlJsContext_->reset();
    }
}

bool ChtlJsLexer::isInChtlMode() const {
    return inChtlSequence_ || 
           (chtlJsState_ && chtlJsState_->isInChtlSelector());
}

Token ChtlJsLexer::recognizeToken() {
    char ch = peekChar();
    
    // 标识符
    if (std::isalpha(ch) || ch == '_' || ch == '$') {
        return recognizeJsIdentifier();
    }
    
    // 数字
    if (std::isdigit(ch)) {
        return recognizeJsNumber();
    }
    
    // 字符串
    if (ch == '"' || ch == '\'' || ch == '`') {
        return recognizeJsString();
    }
    
    // 操作符和标点
    return recognizeJsOperator();
}

Token ChtlJsLexer::recognizeChtlSelector() {
    // 跳过 {{
    advanceChar();
    advanceChar();
    
    std::string selector;
    int braceCount = 0;
    
    while (position_ < input_.size()) {
        if (peekChar() == '}' && peekChar(1) == '}' && braceCount == 0) {
            // 找到结束的 }}
            advanceChar();
            advanceChar();
            break;
        }
        
        if (currentChar() == '{') braceCount++;
        else if (currentChar() == '}') braceCount--;
        
        selector += currentChar();
        advanceChar();
    }
    
    // 注册选择器到上下文
    chtlJsContext_->registerSelector(selector, position_);
    
    return createSelectorToken(selector);
}

Token ChtlJsLexer::recognizeChtlArrow() {
    // 跳过 ->
    advanceChar();
    advanceChar();
    
    // 识别方法名
    std::string method = readWhile([](char c) {
        return std::isalnum(c) || c == '_';
    });
    
    return createMethodToken(method);
}

Token ChtlJsLexer::recognizeChtlMethod() {
    std::string method = readWhile([](char c) {
        return std::isalnum(c) || c == '_';
    });
    
    return Token(TokenType::IDENTIFIER, method, currentLine_, currentColumn_);
}

Token ChtlJsLexer::recognizeJsIdentifier() {
    std::string identifier = readWhile([](char c) {
        return std::isalnum(c) || c == '_' || c == '$';
    });
    
    // 检查是否是关键字
    TokenType type = getKeywordType(identifier);
    if (type != TokenType::IDENTIFIER) {
        return Token(type, identifier, currentLine_, currentColumn_);
    }
    
    // 检查是否是CHTL-JS特殊方法
    if (identifier == "animate" || identifier == "listen" || identifier == "delegate") {
        return Token(TokenType::IDENTIFIER, identifier, currentLine_, currentColumn_);
    }
    
    return Token(TokenType::IDENTIFIER, identifier, currentLine_, currentColumn_);
}

Token ChtlJsLexer::recognizeJsNumber() {
    std::string number = readWhile([](char c) {
        return std::isdigit(c) || c == '.' || c == 'e' || c == 'E' || 
               c == 'x' || c == 'X' || c == '_' || c == 'n';
    });
    
    return Token(TokenType::NUMBER, number, currentLine_, currentColumn_);
}

Token ChtlJsLexer::recognizeJsString() {
    char quote = currentChar();
    advanceChar();
    
    std::string str;
    bool escaped = false;
    
    while (position_ < input_.size() && (escaped || currentChar() != quote)) {
        if (escaped) {
            str += currentChar();
            escaped = false;
        } else if (currentChar() == '\\') {
            str += currentChar();
            escaped = true;
        } else {
            str += currentChar();
        }
        advanceChar();
    }
    
    if (position_ < input_.size()) {
        advanceChar(); // 跳过结束引号
    }
    
    TokenType type = (quote == '`') ? TokenType::TEMPLATE_LITERAL : TokenType::STRING_LITERAL;
    return Token(type, str, currentLine_, currentColumn_);
}

Token ChtlJsLexer::recognizeJsOperator() {
    char ch = currentChar();
    std::string op(1, ch);
    advanceChar();
    
    // 检查双字符操作符
    if (position_ < input_.size()) {
        char next = currentChar();
        std::string doubleOp = op + next;
        
        if (doubleOp == "==" || doubleOp == "!=" || doubleOp == "<=" || 
            doubleOp == ">=" || doubleOp == "&&" || doubleOp == "||" ||
            doubleOp == "++" || doubleOp == "--" || doubleOp == "+=" ||
            doubleOp == "-=" || doubleOp == "*=" || doubleOp == "/=" ||
            doubleOp == "<<" || doubleOp == ">>" || doubleOp == "??" ||
            doubleOp == "?." || doubleOp == "**") {
            advanceChar();
            op = doubleOp;
        }
        
        // 检查三字符操作符
        if (position_ < input_.size() && op == "==" && currentChar() == '=') {
            advanceChar();
            op = "===";
        } else if (position_ < input_.size() && op == "!=" && currentChar() == '=') {
            advanceChar();
            op = "!==";
        } else if (position_ < input_.size() && op == ">>" && currentChar() == '>') {
            advanceChar();
            op = ">>>";
        }
    }
    
    return Token(getOperatorType(op), op, currentLine_, currentColumn_);
}

Token ChtlJsLexer::createChtlToken(TokenType type, const std::string& value) {
    return Token(type, value, currentLine_, currentColumn_);
}

Token ChtlJsLexer::createSelectorToken(const std::string& selector) {
    return Token(TokenType::CHTL_SELECTOR, selector, currentLine_, currentColumn_);
}

Token ChtlJsLexer::createMethodToken(const std::string& method) {
    return Token(TokenType::CHTL_METHOD, method, currentLine_, currentColumn_);
}

bool ChtlJsLexer::checkChtlSequence(const std::string& sequence) {
    if (position_ + sequence.length() > input_.size()) {
        return false;
    }
    
    for (size_t i = 0; i < sequence.length(); ++i) {
        if (input_[position_ + i] != sequence[i]) {
            return false;
        }
    }
    
    return true;
}

void ChtlJsLexer::skipWhitespace() {
    while (position_ < input_.size() && isWhitespace(currentChar())) {
        advanceChar();
    }
}

bool ChtlJsLexer::isAlphaNumeric(char ch) const {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9') ||
           ch == '_' || ch == '$';
}

bool ChtlJsLexer::isWhitespace(char ch) const {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

void ChtlJsLexer::advanceChar() {
    if (position_ < input_.length()) {
        if (input_[position_] == '\n') {
            currentLine_++;
            currentColumn_ = 1;
        } else {
            currentColumn_++;
        }
        position_++;
    }
}

char ChtlJsLexer::currentChar() const {
    if (position_ >= input_.length()) {
        return '\0';
    }
    return input_[position_];
}

char ChtlJsLexer::peekChar(int offset) const {
    size_t pos = position_ + offset;
    if (pos >= input_.length()) {
        return '\0';
    }
    return input_[pos];
}

std::string ChtlJsLexer::readWhile(std::function<bool(char)> predicate) {
    std::string result;
    
    while (position_ < input_.length() && predicate(currentChar())) {
        result += currentChar();
        advanceChar();
    }
    
    return result;
}

TokenType ChtlJsLexer::getKeywordType(const std::string& word) {
    static std::unordered_map<std::string, TokenType> keywords = {
        {"var", TokenType::VAR},
        {"let", TokenType::LET},
        {"const", TokenType::CONST},
        {"function", TokenType::FUNCTION},
        {"class", TokenType::CLASS},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"for", TokenType::FOR},
        {"while", TokenType::WHILE},
        {"return", TokenType::RETURN},
        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"null", TokenType::NULL_LITERAL},
        {"undefined", TokenType::UNDEFINED},
        {"new", TokenType::NEW},
        {"this", TokenType::THIS},
        {"async", TokenType::ASYNC},
        {"await", TokenType::AWAIT},
        {"import", TokenType::IMPORT},
        {"export", TokenType::EXPORT_KW},
        {"from", TokenType::FROM}
    };
    
    auto it = keywords.find(word);
    return (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
}

TokenType ChtlJsLexer::getOperatorType(const std::string& op) {
    // 所有操作符都返回OPERATOR类型
    return TokenType::OPERATOR;
}

} // namespace chtl