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
        state_ = state;
    } else {
        chtlJsState_ = std::make_shared<ChtlJsState>(this);
        state_ = chtlJsState_;
    }
    
    if (context) {
        chtlJsContext_ = context;
        context_ = context;
    } else {
        chtlJsContext_ = std::make_shared<ChtlJsContext>();
        context_ = chtlJsContext_;
    }
}

Token ChtlJsLexer::getNextToken() {
    if (!chtlJsState_ || !chtlJsContext_) {
        initialize();
    }
    
    skipWhitespace();
    
    if (position_ >= input_.size()) {
        return Token(TokenType::END_OF_FILE, "", line_, column_);
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
    int savedLine = line_;
    int savedCol = column_;
    
    Token token = getNextToken();
    
    position_ = savedPos;
    line_ = savedLine;
    column_ = savedCol;
    
    return token;
}

void ChtlJsLexer::reset() {
    BasicLexer::reset();
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
    advance();
    advance();
    
    std::string selector;
    int braceCount = 0;
    
    while (position_ < input_.size()) {
        if (peekChar() == '}' && peekChar(1) == '}' && braceCount == 0) {
            // 找到结束的 }}
            advance();
            advance();
            break;
        }
        
        if (peekChar() == '{') braceCount++;
        else if (peekChar() == '}') braceCount--;
        
        selector += currentChar();
        advance();
    }
    
    // 注册选择器到上下文
    chtlJsContext_->registerSelector(selector, position_);
    
    return createSelectorToken(selector);
}

Token ChtlJsLexer::recognizeChtlArrow() {
    // 跳过 ->
    advance();
    advance();
    
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
    
    return Token(TokenType::IDENTIFIER, method, line_, column_);
}

Token ChtlJsLexer::recognizeJsIdentifier() {
    std::string identifier = readWhile([](char c) {
        return std::isalnum(c) || c == '_' || c == '$';
    });
    
    // 检查是否是关键字
    TokenType type = getKeywordType(identifier);
    if (type != TokenType::IDENTIFIER) {
        return Token(type, identifier, line_, column_);
    }
    
    // 检查是否是CHTL-JS特殊方法
    if (identifier == "animate" || identifier == "listen" || identifier == "delegate") {
        return Token(TokenType::IDENTIFIER, identifier, line_, column_);
    }
    
    return Token(TokenType::IDENTIFIER, identifier, line_, column_);
}

Token ChtlJsLexer::recognizeJsNumber() {
    std::string number = readWhile([](char c) {
        return std::isdigit(c) || c == '.' || c == 'e' || c == 'E' || 
               c == 'x' || c == 'X' || c == '_' || c == 'n';
    });
    
    return Token(TokenType::NUMBER, number, line_, column_);
}

Token ChtlJsLexer::recognizeJsString() {
    char quote = currentChar();
    advance();
    
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
        advance();
    }
    
    if (position_ < input_.size()) {
        advance(); // 跳过结束引号
    }
    
    TokenType type = (quote == '`') ? TokenType::TEMPLATE_LITERAL : TokenType::STRING;
    return Token(type, str, line_, column_);
}

Token ChtlJsLexer::recognizeJsOperator() {
    char ch = currentChar();
    std::string op(1, ch);
    advance();
    
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
            advance();
            op = doubleOp;
        }
        
        // 检查三字符操作符
        if (position_ < input_.size() && op == "==" && currentChar() == '=') {
            advance();
            op = "===";
        } else if (position_ < input_.size() && op == "!=" && currentChar() == '=') {
            advance();
            op = "!==";
        } else if (position_ < input_.size() && op == ">>" && currentChar() == '>') {
            advance();
            op = ">>>";
        }
    }
    
    return Token(getOperatorType(op), op, line_, column_);
}

Token ChtlJsLexer::createChtlToken(TokenType type, const std::string& value) {
    return Token(type, value, line_, column_);
}

Token ChtlJsLexer::createSelectorToken(const std::string& selector) {
    return Token(TokenType::CHTL_SELECTOR, selector, line_, column_);
}

Token ChtlJsLexer::createMethodToken(const std::string& method) {
    return Token(TokenType::CHTL_METHOD, method, line_, column_);
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
    while (position_ < input_.size() && std::isspace(currentChar())) {
        if (currentChar() == '\n') {
            line_++;
            column_ = 1;
        } else {
            column_++;
        }
        position_++;
    }
}

char ChtlJsLexer::peekChar(int offset) {
    size_t pos = position_ + offset;
    if (pos >= input_.size()) {
        return '\0';
    }
    return input_[pos];
}

std::string ChtlJsLexer::readUntil(const std::string& delimiter) {
    std::string result;
    
    while (position_ < input_.size()) {
        if (checkChtlSequence(delimiter)) {
            break;
        }
        result += currentChar();
        advance();
    }
    
    return result;
}

std::string ChtlJsLexer::readWhile(std::function<bool(char)> predicate) {
    std::string result;
    
    while (position_ < input_.size() && predicate(currentChar())) {
        result += currentChar();
        advance();
    }
    
    return result;
}

} // namespace chtl