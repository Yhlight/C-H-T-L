#include "State/JsState.h"
#include <algorithm>
#include <cctype>

namespace chtl {

JsState::JsState(BasicLexer* lexer) 
    : BasicState(StateType::JS, "JsState", lexer),
      currentState_(State::JS_NORMAL),
      previousState_(State::JS_NORMAL),
      stringDelimiter_('\0'),
      braceDepth_(0),
      parenDepth_(0),
      bracketDepth_(0),
      templateDepth_(0),
      inExpression_(false),
      afterOperator_(false) {
}

void JsState::reset() {
    currentState_ = State::JS_NORMAL;
    previousState_ = State::JS_NORMAL;
    while (!stateStack_.empty()) {
        stateStack_.pop();
    }
    stringDelimiter_ = '\0';
    braceDepth_ = 0;
    parenDepth_ = 0;
    bracketDepth_ = 0;
    templateDepth_ = 0;
    inExpression_ = false;
    afterOperator_ = false;
    buffer_.clear();
    currentIdentifier_.clear();
    lastToken_.clear();
}

std::shared_ptr<BasicState> JsState::handleChar(char ch) {
    processChar(ch);
    // JS状态机通常不切换到其他状态
    return nullptr;
}

bool JsState::accepts(char ch) const {
    (void)ch;  // 避免未使用参数警告
    // JS状态接受所有字符
    return true;
}

void JsState::processChar(char c) {
    buffer_ += c;
    
    switch (currentState_) {
        case State::JS_NORMAL:
            handleNormalState(c);
            break;
        case State::JS_STRING_SINGLE:
        case State::JS_STRING_DOUBLE:
            handleStringState(c);
            break;
        case State::JS_TEMPLATE_LITERAL:
            handleTemplateState(c);
            break;
        case State::JS_COMMENT_SINGLE:
        case State::JS_COMMENT_MULTI:
            handleCommentState(c);
            break;
        case State::JS_REGEX:
            handleRegexState(c);
            break;
        case State::JS_NUMBER:
            handleNumberState(c);
            break;
        case State::JS_IDENTIFIER:
            handleIdentifierState(c);
            break;
        case State::JS_OPERATOR:
            handleOperatorState(c);
            break;
        case State::ERROR:
            // 错误状态，不处理
            break;
    }
}

bool JsState::isInStringLiteral() const {
    return currentState_ == State::JS_STRING_SINGLE ||
           currentState_ == State::JS_STRING_DOUBLE ||
           currentState_ == State::JS_TEMPLATE_LITERAL;
}

bool JsState::isInComment() const {
    return currentState_ == State::JS_COMMENT_SINGLE ||
           currentState_ == State::JS_COMMENT_MULTI;
}

std::string JsState::getStateName() const {
    switch (currentState_) {
        case State::JS_NORMAL: return "JS_NORMAL";
        case State::JS_STRING_SINGLE: return "JS_STRING_SINGLE";
        case State::JS_STRING_DOUBLE: return "JS_STRING_DOUBLE";
        case State::JS_TEMPLATE_LITERAL: return "JS_TEMPLATE_LITERAL";
        case State::JS_COMMENT_SINGLE: return "JS_COMMENT_SINGLE";
        case State::JS_COMMENT_MULTI: return "JS_COMMENT_MULTI";
        case State::JS_REGEX: return "JS_REGEX";
        case State::JS_NUMBER: return "JS_NUMBER";
        case State::JS_IDENTIFIER: return "JS_IDENTIFIER";
        case State::JS_OPERATOR: return "JS_OPERATOR";
        case State::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void JsState::transitionTo(State newState) {
    previousState_ = currentState_;
    currentState_ = newState;
}

void JsState::handleNormalState(char c) {
    // 检查字符串开始
    if (c == '\'' || c == '"') {
        stringDelimiter_ = c;
        transitionTo(c == '\'' ? State::JS_STRING_SINGLE : State::JS_STRING_DOUBLE);
        return;
    }
    
    // 检查模板字符串
    if (c == '`') {
        transitionTo(State::JS_TEMPLATE_LITERAL);
        return;
    }
    
    // 检查注释
    if (c == '/') {
        if (buffer_.size() >= 2) {
            char prev = buffer_[buffer_.size() - 2];
            if (prev == '/') {
                transitionTo(State::JS_COMMENT_SINGLE);
                return;
            } else if (prev == '*' && buffer_.size() >= 3 && buffer_[buffer_.size() - 3] == '/') {
                transitionTo(State::JS_COMMENT_MULTI);
                return;
            }
        }
        
        // 可能是正则表达式
        if (shouldStartRegex()) {
            transitionTo(State::JS_REGEX);
            return;
        }
    }
    
    // 检查数字
    if (isDigit(c)) {
        transitionTo(State::JS_NUMBER);
        return;
    }
    
    // 检查标识符
    if (isIdentifierStart(c)) {
        currentIdentifier_ = std::string(1, c);
        transitionTo(State::JS_IDENTIFIER);
        return;
    }
    
    // 检查操作符
    if (isOperatorChar(c)) {
        afterOperator_ = true;
        transitionTo(State::JS_OPERATOR);
        return;
    }
    
    // 更新深度计数
    switch (c) {
        case '{': braceDepth_++; break;
        case '}': braceDepth_--; break;
        case '(': parenDepth_++; afterOperator_ = false; break;
        case ')': parenDepth_--; afterOperator_ = false; break;
        case '[': bracketDepth_++; afterOperator_ = false; break;
        case ']': bracketDepth_--; afterOperator_ = false; break;
        case ';': afterOperator_ = false; break;
        case ',': afterOperator_ = true; break;
    }
}

void JsState::handleStringState(char c) {
    if (!isEscaped()) {
        if (c == stringDelimiter_) {
            transitionTo(State::JS_NORMAL);
            stringDelimiter_ = '\0';
        }
    }
}

void JsState::handleTemplateState(char c) {
    if (!isEscaped()) {
        if (c == '`') {
            if (templateDepth_ == 0) {
                transitionTo(State::JS_NORMAL);
            } else {
                templateDepth_--;
            }
        } else if (c == '{' && buffer_.size() >= 2 && buffer_[buffer_.size() - 2] == '$') {
            templateDepth_++;
        }
    }
}

void JsState::handleCommentState(char c) {
    if (currentState_ == State::JS_COMMENT_SINGLE) {
        if (c == '\n') {
            transitionTo(State::JS_NORMAL);
        }
    } else if (currentState_ == State::JS_COMMENT_MULTI) {
        if (c == '/' && buffer_.size() >= 2 && buffer_[buffer_.size() - 2] == '*') {
            transitionTo(State::JS_NORMAL);
        }
    }
}

void JsState::handleRegexState(char c) {
    if (!isEscaped()) {
        if (c == '/') {
            // 检查正则标志
            transitionTo(State::JS_NORMAL);
        } else if (c == '[') {
            // 进入字符类
        } else if (c == ']') {
            // 退出字符类
        }
    }
}

void JsState::handleNumberState(char c) {
    if (!isDigit(c) && c != '.' && c != 'e' && c != 'E' && 
        c != 'x' && c != 'X' && c != 'n' && c != '_') {
        transitionTo(State::JS_NORMAL);
        // 重新处理当前字符
        handleNormalState(c);
    }
}

void JsState::handleIdentifierState(char c) {
    if (isIdentifierPart(c)) {
        currentIdentifier_ += c;
    } else {
        lastToken_ = currentIdentifier_;
        transitionTo(State::JS_NORMAL);
        // 重新处理当前字符
        handleNormalState(c);
    }
}

void JsState::handleOperatorState(char c) {
    if (!isOperatorChar(c)) {
        transitionTo(State::JS_NORMAL);
        // 重新处理当前字符
        handleNormalState(c);
    }
}

bool JsState::isEscaped() const {
    if (buffer_.size() < 2) return false;
    
    int backslashCount = 0;
    for (int i = buffer_.size() - 2; i >= 0 && buffer_[i] == '\\'; i--) {
        backslashCount++;
    }
    
    return backslashCount % 2 == 1;
}

bool JsState::checkSequence(const std::string& sequence) const {
    if (buffer_.size() < sequence.size()) return false;
    return buffer_.substr(buffer_.size() - sequence.size()) == sequence;
}

bool JsState::isIdentifierStart(char c) const {
    return std::isalpha(c) || c == '_' || c == '$';
}

bool JsState::isIdentifierPart(char c) const {
    return std::isalnum(c) || c == '_' || c == '$';
}

bool JsState::isDigit(char c) const {
    return std::isdigit(c);
}

bool JsState::isOperatorChar(char c) const {
    static const std::string operators = "+-*/%=<>!&|^~?:";
    return operators.find(c) != std::string::npos;
}

bool JsState::shouldStartRegex() const {
    // 简化的正则表达式判断逻辑
    // 在这些token后，/更可能是正则表达式而不是除法
    static const std::vector<std::string> regexPrecedingTokens = {
        "return", "throw", "else", "case", "new", "void", "typeof", "delete",
        "=", "==", "===", "!=", "!==", "<", ">", "<=", ">=",
        "(", "[", "{", ",", ";", ":", "?", "+", "-", "*", "/", "%",
        "&&", "||", "!", "~", "&", "|", "^"
    };
    
    // 检查最后的token
    for (const auto& token : regexPrecedingTokens) {
        if (lastToken_ == token || checkSequence(token)) {
            return true;
        }
    }
    
    return afterOperator_;
}

} // namespace chtl