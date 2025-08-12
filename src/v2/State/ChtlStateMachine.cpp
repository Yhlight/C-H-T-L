#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/Token.h"
#include "v2/Lexer/ChtlLexer.h"
#include <iostream>
#include <stdexcept>

namespace chtl::v2 {

ChtlStateMachine::ChtlStateMachine() 
    : currentState_(ChtlParseState::INITIAL)
    , parseContext_()
    , lexer_(nullptr) {
    // 初始上下文为全局
    contextStack_.push_back(ChtlContext::GLOBAL);
    stateStack_.push_back(ChtlParseState::INITIAL);
}

ChtlStateMachine::~ChtlStateMachine() = default;

void ChtlStateMachine::initialize() {
    // 注册所有状态转换规则
    registerTransitions();
    
    // 重置到初始状态
    reset();
}

ChtlParseState ChtlStateMachine::getCurrentState() const {
    return currentState_;
}

ChtlContext ChtlStateMachine::getCurrentContext() const {
    if (contextStack_.empty()) {
        return ChtlContext::GLOBAL;
    }
    return contextStack_.back();
}

bool ChtlStateMachine::processToken(const Token& token) {
    // 查找适用的转换规则
    const StateTransition* transition = findTransition(token);
    
    if (transition) {
        // 执行转换动作
        if (transition->action) {
            transition->action(parseContext_);
        }
        
        // 执行状态转换
        if (transition->nextState != currentState_) {
            performTransition(transition->nextState);
        }
        
        return true;
    }
    
    // 没有找到转换规则，可能是错误
    std::cerr << "[StateMachine] No transition for token " 
              << token.toString() 
              << " in state " << getStateName(currentState_) 
              << " with context " << getContextName(getCurrentContext()) << "\n";
    return false;
}

void ChtlStateMachine::enterState(ChtlParseState newState) {
    stateStack_.push_back(newState);
    performTransition(newState);
    
    // 某些状态自动进入局部上下文
    if (requiresLocalContext(newState)) {
        enterLocalContext();
    }
}

void ChtlStateMachine::exitState() {
    if (stateStack_.size() <= 1) {
        throw std::runtime_error("Cannot exit initial state");
    }
    
    // 如果当前状态需要局部上下文，退出时也要退出上下文
    if (requiresLocalContext(currentState_)) {
        exitLocalContext();
    }
    
    stateStack_.pop_back();
    performTransition(stateStack_.back());
}

void ChtlStateMachine::enterLocalContext() {
    contextStack_.push_back(ChtlContext::LOCAL);
    parseContext_.setContext(ChtlContext::LOCAL);
    
    std::cerr << "[StateMachine] Enter LOCAL context (depth: " 
              << contextStack_.size() << ")\n";
}

void ChtlStateMachine::exitLocalContext() {
    if (contextStack_.size() <= 1) {
        throw std::runtime_error("Cannot exit global context");
    }
    
    contextStack_.pop_back();
    parseContext_.setContext(contextStack_.back());
    
    std::cerr << "[StateMachine] Exit to " 
              << getContextName(getCurrentContext()) 
              << " context (depth: " << contextStack_.size() << ")\n";
}

void ChtlStateMachine::reset() {
    currentState_ = ChtlParseState::INITIAL;
    contextStack_.clear();
    contextStack_.push_back(ChtlContext::GLOBAL);
    stateStack_.clear();
    stateStack_.push_back(ChtlParseState::INITIAL);
    parseContext_.reset();
    
    if (lexer_) {
        lexer_->setCurrentState(currentState_);
    }
}

void ChtlStateMachine::printState() const {
    std::cout << "=== State Machine Status ===\n";
    std::cout << "Current State: " << getStateName(currentState_) << "\n";
    std::cout << "Current Context: " << getContextName(getCurrentContext()) << "\n";
    std::cout << "Context Stack Depth: " << contextStack_.size() << "\n";
    std::cout << "State Stack Depth: " << stateStack_.size() << "\n";
    std::cout << parseContext_.toString() << "\n";
    std::cout << "========================\n";
}

void ChtlStateMachine::performTransition(ChtlParseState newState) {
    ChtlParseState oldState = currentState_;
    currentState_ = newState;
    parseContext_.setState(newState);
    
    // 通知词法分析器
    if (lexer_) {
        lexer_->setCurrentState(newState);
    }
    
    std::cerr << "[StateMachine] Transition: " 
              << getStateName(oldState) 
              << " -> " << getStateName(newState) << "\n";
}

const StateTransition* ChtlStateMachine::findTransition(const Token& token) const {
    auto it = transitions_.find(currentState_);
    if (it == transitions_.end()) {
        return nullptr;
    }
    
    // 获取当前上下文
    ChtlContext context = getCurrentContext();
    
    // 遍历当前状态的所有转换规则
    for (const auto& transition : it->second) {
        if (transition.condition(token, context)) {
            return &transition;
        }
    }
    
    return nullptr;
}

} // namespace chtl::v2