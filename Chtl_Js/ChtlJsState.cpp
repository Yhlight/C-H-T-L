#include "State/ChtlJsState.h"
#include <algorithm>

namespace chtl {
namespace chtl_js {

ChtlJsState::ChtlJsState()
    : currentState_(State::JS_NORMAL),
      previousState_(State::JS_NORMAL),
      braceCount_(0),
      expectingSecondBrace_(false),
      parenDepth_(0),
      objectDepth_(0),
      stringDelimiter_('\0'),
      templateDepth_(0) {
}

void ChtlJsState::reset() {
    currentState_ = State::JS_NORMAL;
    previousState_ = State::JS_NORMAL;
    while (!stateStack_.empty()) {
        stateStack_.pop();
    }
    braceCount_ = 0;
    expectingSecondBrace_ = false;
    currentSelector_.clear();
    currentMethod_.clear();
    parenDepth_ = 0;
    objectDepth_ = 0;
    stringDelimiter_ = '\0';
    templateDepth_ = 0;
}

void ChtlJsState::processChar(char c) {
    switch (currentState_) {
        case State::JS_NORMAL:
            handleNormalState(c);
            break;
        case State::JS_STRING:
            handleStringState(c);
            break;
        case State::JS_TEMPLATE_LITERAL:
            handleTemplateState(c);
            break;
        case State::JS_COMMENT_SINGLE:
        case State::JS_COMMENT_MULTI:
            handleCommentState(c);
            break;
        case State::CHTL_SELECTOR_START:
        case State::CHTL_SELECTOR:
        case State::CHTL_SELECTOR_END:
            handleSelectorState(c);
            break;
        case State::CHTL_ARROW:
            handleArrowState(c);
            break;
        case State::CHTL_METHOD_CALL:
        case State::CHTL_LISTEN_OBJECT:
        case State::CHTL_DELEGATE_OBJECT:
            handleMethodCallState(c);
            break;
        case State::CHTL_ANIMATE_CALL:
        case State::CHTL_ANIMATE_CONFIG:
        case State::CHTL_ANIMATE_KEYFRAME:
            handleAnimateState(c);
            break;
        case State::ERROR:
            // 错误状态，等待恢复
            break;
        default:
            break;
    }
}

bool ChtlJsState::isInStringLiteral() const {
    return currentState_ == State::JS_STRING || 
           currentState_ == State::JS_TEMPLATE_LITERAL;
}

bool ChtlJsState::isInComment() const {
    return currentState_ == State::JS_COMMENT_SINGLE || 
           currentState_ == State::JS_COMMENT_MULTI;
}

std::string ChtlJsState::getStateName() const {
    switch (currentState_) {
        case State::JS_NORMAL: return "JS_NORMAL";
        case State::JS_STRING: return "JS_STRING";
        case State::JS_TEMPLATE_LITERAL: return "JS_TEMPLATE_LITERAL";
        case State::JS_COMMENT_SINGLE: return "JS_COMMENT_SINGLE";
        case State::JS_COMMENT_MULTI: return "JS_COMMENT_MULTI";
        case State::JS_REGEX: return "JS_REGEX";
        case State::CHTL_SELECTOR_START: return "CHTL_SELECTOR_START";
        case State::CHTL_SELECTOR: return "CHTL_SELECTOR";
        case State::CHTL_SELECTOR_END: return "CHTL_SELECTOR_END";
        case State::CHTL_ARROW: return "CHTL_ARROW";
        case State::CHTL_METHOD_CALL: return "CHTL_METHOD_CALL";
        case State::CHTL_ANIMATE_CALL: return "CHTL_ANIMATE_CALL";
        case State::CHTL_LISTEN_OBJECT: return "CHTL_LISTEN_OBJECT";
        case State::CHTL_DELEGATE_OBJECT: return "CHTL_DELEGATE_OBJECT";
        case State::CHTL_ANIMATE_CONFIG: return "CHTL_ANIMATE_CONFIG";
        case State::CHTL_ANIMATE_KEYFRAME: return "CHTL_ANIMATE_KEYFRAME";
        case State::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

bool ChtlJsState::isInChtlSelector() const {
    return currentState_ == State::CHTL_SELECTOR_START ||
           currentState_ == State::CHTL_SELECTOR ||
           currentState_ == State::CHTL_SELECTOR_END;
}

bool ChtlJsState::isInChtlMethod() const {
    return currentState_ == State::CHTL_METHOD_CALL ||
           currentState_ == State::CHTL_LISTEN_OBJECT ||
           currentState_ == State::CHTL_DELEGATE_OBJECT;
}

bool ChtlJsState::isInAnimateConfig() const {
    return currentState_ == State::CHTL_ANIMATE_CALL ||
           currentState_ == State::CHTL_ANIMATE_CONFIG ||
           currentState_ == State::CHTL_ANIMATE_KEYFRAME;
}

void ChtlJsState::transitionTo(State newState) {
    previousState_ = currentState_;
    currentState_ = newState;
}

void ChtlJsState::pushState(State newState) {
    stateStack_.push(currentState_);
    currentState_ = newState;
}

void ChtlJsState::popState() {
    if (!stateStack_.empty()) {
        currentState_ = stateStack_.top();
        stateStack_.pop();
    }
}

void ChtlJsState::handleNormalState(char c) {
    // 检查字符串开始
    if (c == '"' || c == '\'') {
        stringDelimiter_ = c;
        transitionTo(State::JS_STRING);
        return;
    }
    
    // 检查模板字符串
    if (c == '`') {
        templateDepth_++;
        transitionTo(State::JS_TEMPLATE_LITERAL);
        return;
    }
    
    // 检查注释
    static char lastChar = '\0';
    if (lastChar == '/' && c == '/') {
        transitionTo(State::JS_COMMENT_SINGLE);
        return;
    }
    if (lastChar == '/' && c == '*') {
        transitionTo(State::JS_COMMENT_MULTI);
        return;
    }
    
    // 检查CHTL选择器开始 {{
    if (c == '{') {
        if (expectingSecondBrace_) {
            expectingSecondBrace_ = false;
            transitionTo(State::CHTL_SELECTOR);
            currentSelector_.clear();
            return;
        } else {
            expectingSecondBrace_ = true;
        }
    } else if (expectingSecondBrace_) {
        expectingSecondBrace_ = false;
        // 普通的 { ，增加对象深度
        objectDepth_++;
    }
    
    // 检查CHTL箭头操作符 ->
    if (lastChar == '-' && c == '>') {
        transitionTo(State::CHTL_ARROW);
        return;
    }
    
    lastChar = c;
}

void ChtlJsState::handleStringState(char c) {
    static bool escaped = false;
    
    if (escaped) {
        escaped = false;
        return;
    }
    
    if (c == '\\') {
        escaped = true;
        return;
    }
    
    if (c == stringDelimiter_) {
        stringDelimiter_ = '\0';
        transitionTo(State::JS_NORMAL);
    }
}

void ChtlJsState::handleTemplateState(char c) {
    static bool escaped = false;
    
    if (escaped) {
        escaped = false;
        return;
    }
    
    if (c == '\\') {
        escaped = true;
        return;
    }
    
    if (c == '`') {
        templateDepth_--;
        if (templateDepth_ == 0) {
            transitionTo(State::JS_NORMAL);
        }
    } else if (c == '$' && !escaped) {
        // 可能是模板插值 ${...}
        // 需要额外处理
    }
}

void ChtlJsState::handleCommentState(char c) {
    if (currentState_ == State::JS_COMMENT_SINGLE) {
        if (c == '\n') {
            transitionTo(State::JS_NORMAL);
        }
    } else if (currentState_ == State::JS_COMMENT_MULTI) {
        static char lastChar = '\0';
        if (lastChar == '*' && c == '/') {
            transitionTo(State::JS_NORMAL);
        }
        lastChar = c;
    }
}

void ChtlJsState::handleSelectorState(char c) {
    if (currentState_ == State::CHTL_SELECTOR) {
        if (c == '}') {
            braceCount_++;
            if (braceCount_ == 1) {
                transitionTo(State::CHTL_SELECTOR_END);
            }
        } else {
            currentSelector_ += c;
        }
    } else if (currentState_ == State::CHTL_SELECTOR_END) {
        if (c == '}') {
            braceCount_ = 0;
            transitionTo(State::JS_NORMAL);
        } else {
            // 错误：期待第二个 }
            transitionTo(State::ERROR);
        }
    }
}

void ChtlJsState::handleArrowState(char c) {
    // -> 后面应该跟着方法名
    if (isWhitespace(c)) {
        return; // 跳过空白
    }
    
    if (isIdentifierStart(c)) {
        currentMethod_.clear();
        currentMethod_ += c;
        transitionTo(State::CHTL_METHOD_CALL);
    } else {
        // 不是CHTL方法调用，回到正常状态
        transitionTo(State::JS_NORMAL);
    }
}

void ChtlJsState::handleMethodCallState(char c) {
    if (isIdentifierPart(c)) {
        currentMethod_ += c;
    } else if (c == '(') {
        // 检查是否是CHTL方法
        if (currentMethod_ == "listen") {
            pushState(State::CHTL_LISTEN_OBJECT);
            parenDepth_ = 1;
        } else if (currentMethod_ == "delegate") {
            pushState(State::CHTL_DELEGATE_OBJECT);
            parenDepth_ = 1;
        } else {
            // 普通方法调用
            transitionTo(State::JS_NORMAL);
        }
    } else {
        transitionTo(State::JS_NORMAL);
    }
}

void ChtlJsState::handleAnimateState(char c) {
    // 处理animate()调用的复杂状态
    if (c == '(') {
        parenDepth_++;
    } else if (c == ')') {
        parenDepth_--;
        if (parenDepth_ == 0) {
            popState();
        }
    } else if (c == '{') {
        objectDepth_++;
    } else if (c == '}') {
        objectDepth_--;
        if (objectDepth_ == 0 && currentState_ == State::CHTL_ANIMATE_CONFIG) {
            popState();
        }
    }
}

bool ChtlJsState::isIdentifierStart(char c) const {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           c == '_' || 
           c == '$';
}

bool ChtlJsState::isIdentifierPart(char c) const {
    return isIdentifierStart(c) || (c >= '0' && c <= '9');
}

bool ChtlJsState::isWhitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

} // namespace chtl_js
} // namespace chtl