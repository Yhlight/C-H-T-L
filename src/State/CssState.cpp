#include "State/CssState.h"
#include <algorithm>

namespace chtl {

CssState::CssState() 
    : BasicState(),
      currentState_(State::CSS_NORMAL),
      previousState_(State::CSS_NORMAL),
      stringDelimiter_('\0'),
      braceDepth_(0),
      parenDepth_(0),
      bracketDepth_(0),
      inAtRule_(false),
      inSelector_(true),
      inPropertyName_(false),
      inPropertyValue_(false) {
}

void CssState::reset() {
    currentState_ = State::CSS_NORMAL;
    previousState_ = State::CSS_NORMAL;
    stringDelimiter_ = '\0';
    braceDepth_ = 0;
    parenDepth_ = 0;
    bracketDepth_ = 0;
    inAtRule_ = false;
    inSelector_ = true;
    inPropertyName_ = false;
    inPropertyValue_ = false;
    currentBuffer_.clear();
}

void CssState::processChar(char c) {
    currentBuffer_ += c;
    
    switch (currentState_) {
        case State::CSS_NORMAL:
            handleNormalState(c);
            break;
        case State::CSS_STRING:
            handleStringState(c);
            break;
        case State::CSS_COMMENT:
            handleCommentState(c);
            break;
        case State::CSS_AT_RULE:
            handleAtRuleState(c);
            break;
        case State::CSS_SELECTOR:
            handleSelectorState(c);
            break;
        case State::CSS_PROPERTY_NAME:
            handlePropertyNameState(c);
            break;
        case State::CSS_PROPERTY_VALUE:
            handlePropertyValueState(c);
            break;
        case State::CSS_URL:
            handleUrlState(c);
            break;
        case State::CSS_FUNCTION:
            handleFunctionState(c);
            break;
        case State::CSS_VARIABLE:
            handleVariableState(c);
            break;
        case State::ERROR:
            // 错误状态，等待恢复
            break;
    }
}

bool CssState::isInStringLiteral() const {
    return currentState_ == State::CSS_STRING;
}

bool CssState::isInComment() const {
    return currentState_ == State::CSS_COMMENT;
}

std::string CssState::getStateName() const {
    switch (currentState_) {
        case State::CSS_NORMAL: return "CSS_NORMAL";
        case State::CSS_STRING: return "CSS_STRING";
        case State::CSS_COMMENT: return "CSS_COMMENT";
        case State::CSS_AT_RULE: return "CSS_AT_RULE";
        case State::CSS_SELECTOR: return "CSS_SELECTOR";
        case State::CSS_PROPERTY_NAME: return "CSS_PROPERTY_NAME";
        case State::CSS_PROPERTY_VALUE: return "CSS_PROPERTY_VALUE";
        case State::CSS_URL: return "CSS_URL";
        case State::CSS_FUNCTION: return "CSS_FUNCTION";
        case State::CSS_VARIABLE: return "CSS_VARIABLE";
        case State::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void CssState::transitionTo(State newState) {
    previousState_ = currentState_;
    currentState_ = newState;
}

void CssState::handleNormalState(char c) {
    if (currentBuffer_.size() >= 2) {
        const char prev = currentBuffer_[currentBuffer_.size() - 2];
        
        // 检查注释开始
        if (prev == '/' && c == '*') {
            transitionTo(State::CSS_COMMENT);
            return;
        }
    }
    
    // 处理字符串
    if (c == '"' || c == '\'') {
        stringDelimiter_ = c;
        transitionTo(State::CSS_STRING);
        return;
    }
    
    // 处理@规则
    if (c == '@') {
        inAtRule_ = true;
        transitionTo(State::CSS_AT_RULE);
        return;
    }
    
    // 处理选择器/属性切换
    if (c == '{') {
        braceDepth_++;
        inSelector_ = false;
        inPropertyName_ = true;
        transitionTo(State::CSS_PROPERTY_NAME);
        return;
    }
    
    if (c == '}') {
        braceDepth_--;
        if (braceDepth_ == 0) {
            inSelector_ = true;
            inPropertyName_ = false;
            inPropertyValue_ = false;
            transitionTo(State::CSS_SELECTOR);
        }
        return;
    }
    
    // 处理属性声明
    if (c == ':' && !inSelector_ && inPropertyName_) {
        inPropertyName_ = false;
        inPropertyValue_ = true;
        transitionTo(State::CSS_PROPERTY_VALUE);
        return;
    }
    
    if (c == ';' && inPropertyValue_) {
        inPropertyValue_ = false;
        inPropertyName_ = true;
        transitionTo(State::CSS_PROPERTY_NAME);
        return;
    }
    
    // 处理CSS变量
    if (c == '-' && currentBuffer_.size() >= 2 && 
        currentBuffer_[currentBuffer_.size() - 2] == '-') {
        transitionTo(State::CSS_VARIABLE);
        return;
    }
    
    // 处理函数
    if (c == '(' && isIdentifierBefore()) {
        parenDepth_++;
        transitionTo(State::CSS_FUNCTION);
        return;
    }
}

void CssState::handleStringState(char c) {
    if (c == stringDelimiter_ && !isEscaped()) {
        stringDelimiter_ = '\0';
        transitionTo(previousState_);
    }
}

void CssState::handleCommentState(char c) {
    if (currentBuffer_.size() >= 2) {
        const char prev = currentBuffer_[currentBuffer_.size() - 2];
        if (prev == '*' && c == '/') {
            transitionTo(State::CSS_NORMAL);
        }
    }
}

void CssState::handleAtRuleState(char c) {
    // @规则可以包含字符串
    if (c == '"' || c == '\'') {
        stringDelimiter_ = c;
        previousState_ = State::CSS_AT_RULE;
        transitionTo(State::CSS_STRING);
        return;
    }
    
    // @规则结束
    if (c == ';' || c == '{') {
        inAtRule_ = false;
        if (c == '{') {
            braceDepth_++;
            transitionTo(State::CSS_NORMAL);
        } else {
            transitionTo(State::CSS_SELECTOR);
        }
    }
}

void CssState::handleSelectorState(char c) {
    // 选择器中的字符串（属性选择器）
    if (c == '"' || c == '\'') {
        stringDelimiter_ = c;
        previousState_ = State::CSS_SELECTOR;
        transitionTo(State::CSS_STRING);
        return;
    }
    
    if (c == '[') {
        bracketDepth_++;
    } else if (c == ']') {
        bracketDepth_--;
    } else if (c == '{') {
        braceDepth_++;
        inSelector_ = false;
        inPropertyName_ = true;
        transitionTo(State::CSS_PROPERTY_NAME);
    }
}

void CssState::handlePropertyNameState(char c) {
    if (c == ':') {
        inPropertyName_ = false;
        inPropertyValue_ = true;
        transitionTo(State::CSS_PROPERTY_VALUE);
    } else if (c == '}') {
        braceDepth_--;
        if (braceDepth_ == 0) {
            inSelector_ = true;
            inPropertyName_ = false;
            transitionTo(State::CSS_SELECTOR);
        }
    }
}

void CssState::handlePropertyValueState(char c) {
    // 值中的字符串
    if (c == '"' || c == '\'') {
        stringDelimiter_ = c;
        previousState_ = State::CSS_PROPERTY_VALUE;
        transitionTo(State::CSS_STRING);
        return;
    }
    
    // URL函数
    if (checkSequence("url(")) {
        transitionTo(State::CSS_URL);
        return;
    }
    
    // 其他函数
    if (c == '(' && isIdentifierBefore()) {
        parenDepth_++;
        transitionTo(State::CSS_FUNCTION);
        return;
    }
    
    // 值结束
    if (c == ';' || c == '}') {
        inPropertyValue_ = false;
        if (c == ';') {
            inPropertyName_ = true;
            transitionTo(State::CSS_PROPERTY_NAME);
        } else {
            braceDepth_--;
            if (braceDepth_ == 0) {
                inSelector_ = true;
                transitionTo(State::CSS_SELECTOR);
            }
        }
    }
}

void CssState::handleUrlState(char c) {
    if (c == ')' && parenDepth_ == 1) {
        parenDepth_--;
        transitionTo(State::CSS_PROPERTY_VALUE);
    } else if (c == '(') {
        parenDepth_++;
    }
}

void CssState::handleFunctionState(char c) {
    if (c == ')') {
        parenDepth_--;
        if (parenDepth_ == 0) {
            transitionTo(previousState_);
        }
    } else if (c == '(') {
        parenDepth_++;
    }
}

void CssState::handleVariableState(char c) {
    if (!isIdentifierPart(c) && c != '-') {
        transitionTo(previousState_);
        processChar(c); // 重新处理当前字符
    }
}

bool CssState::isEscaped() const {
    if (currentBuffer_.size() < 2) return false;
    int backslashCount = 0;
    for (int i = currentBuffer_.size() - 2; i >= 0 && currentBuffer_[i] == '\\'; i--) {
        backslashCount++;
    }
    return backslashCount % 2 == 1;
}

bool CssState::checkSequence(const std::string& sequence) const {
    if (currentBuffer_.size() < sequence.size()) return false;
    return currentBuffer_.substr(currentBuffer_.size() - sequence.size()) == sequence;
}

bool CssState::isIdentifierBefore() const {
    if (currentBuffer_.size() < 2) return false;
    char prev = currentBuffer_[currentBuffer_.size() - 2];
    return isIdentifierPart(prev);
}

bool CssState::isIdentifierStart(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '-';
}

bool CssState::isIdentifierPart(char c) const {
    return isIdentifierStart(c) || (c >= '0' && c <= '9');
}

} // namespace chtl