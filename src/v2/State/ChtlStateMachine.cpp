#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/Token.h"
#include "v2/Lexer/ChtlLexer.h"
#include <iostream>
#include <stdexcept>

namespace chtl::v2 {

ChtlStateMachine::ChtlStateMachine() : lexer_(nullptr) {
    // 初始状态
    stateStack_.push_back(ChtlParseState::TOP_LEVEL);
    contextStack_.emplace_back(ChtlParseState::TOP_LEVEL);
}

ChtlStateMachine::~ChtlStateMachine() = default;

void ChtlStateMachine::initialize() {
    // 注册所有状态转换规则
    registerTransitions();
    
    // 重置到初始状态
    reset();
}

ChtlParseState ChtlStateMachine::getCurrentState() const {
    if (stateStack_.empty()) {
        throw std::runtime_error("State stack is empty");
    }
    return stateStack_.back();
}

bool ChtlStateMachine::processToken(const Token& token) {
    // 查找适用的转换规则
    const StateTransition* transition = findTransition(token);
    
    if (transition) {
        // 执行转换动作
        if (transition->action) {
            transition->action(getCurrentContext());
        }
        
        // 执行状态转换
        if (transition->nextState != getCurrentState()) {
            performTransition(transition->nextState);
        }
        
        return true;
    }
    
    // 没有找到转换规则，可能是错误
    return false;
}

void ChtlStateMachine::transitionTo(ChtlParseState newState) {
    performTransition(newState);
}

void ChtlStateMachine::pushState(ChtlParseState newState) {
    // 保存当前状态
    stateStack_.push_back(newState);
    
    // 创建新的上下文
    contextStack_.emplace_back(newState);
    
    // 通知词法分析器状态改变
    if (lexer_) {
        lexer_->setCurrentState(newState);
    }
    
    // 执行进入回调
    auto it = enterCallbacks_.find(newState);
    if (it != enterCallbacks_.end()) {
        it->second(newState, getCurrentContext());
    }
    
    std::cerr << "[StateMachine] Push state: " << getStateName(newState) 
              << " (depth: " << stateStack_.size() << ")\n";
}

void ChtlStateMachine::popState() {
    if (stateStack_.size() <= 1) {
        throw std::runtime_error("Cannot pop the last state");
    }
    
    ChtlParseState oldState = getCurrentState();
    
    // 执行退出回调
    auto it = exitCallbacks_.find(oldState);
    if (it != exitCallbacks_.end()) {
        it->second(oldState, getCurrentContext());
    }
    
    // 弹出状态和上下文
    stateStack_.pop_back();
    contextStack_.pop_back();
    
    // 通知词法分析器状态改变
    if (lexer_) {
        lexer_->setCurrentState(getCurrentState());
    }
    
    std::cerr << "[StateMachine] Pop state: " << getStateName(oldState) 
              << " -> " << getStateName(getCurrentState()) 
              << " (depth: " << stateStack_.size() << ")\n";
}

ParseContext& ChtlStateMachine::getCurrentContext() {
    if (contextStack_.empty()) {
        throw std::runtime_error("Context stack is empty");
    }
    return contextStack_.back();
}

const ParseContext& ChtlStateMachine::getCurrentContext() const {
    if (contextStack_.empty()) {
        throw std::runtime_error("Context stack is empty");
    }
    return contextStack_.back();
}

void ChtlStateMachine::setLexer(ChtlLexer* lexer) {
    lexer_ = lexer;
    if (lexer_) {
        lexer_->setCurrentState(getCurrentState());
    }
}

void ChtlStateMachine::onStateEnter(ChtlParseState state, StateCallback callback) {
    enterCallbacks_[state] = callback;
}

void ChtlStateMachine::onStateExit(ChtlParseState state, StateCallback callback) {
    exitCallbacks_[state] = callback;
}

void ChtlStateMachine::reset() {
    stateStack_.clear();
    contextStack_.clear();
    
    // 回到初始状态
    stateStack_.push_back(ChtlParseState::TOP_LEVEL);
    contextStack_.emplace_back(ChtlParseState::TOP_LEVEL);
    
    if (lexer_) {
        lexer_->setCurrentState(ChtlParseState::TOP_LEVEL);
    }
}

bool ChtlStateMachine::isInState(ChtlParseState state) const {
    for (const auto& s : stateStack_) {
        if (s == state) return true;
    }
    return false;
}

bool ChtlStateMachine::isInStyleContext() const {
    ChtlParseState current = getCurrentState();
    return current == ChtlParseState::STYLE_BLOCK ||
           current == ChtlParseState::STYLE_SELECTOR ||
           current == ChtlParseState::STYLE_PROPERTY_NAME ||
           current == ChtlParseState::STYLE_PROPERTY_VALUE ||
           current == ChtlParseState::STYLE_TEXT_CONTENT;
}

bool ChtlStateMachine::isInScriptContext() const {
    ChtlParseState current = getCurrentState();
    return current == ChtlParseState::SCRIPT_BLOCK ||
           current == ChtlParseState::SCRIPT_CONTENT;
}

bool ChtlStateMachine::isInTemplateContext() const {
    return isInState(ChtlParseState::TEMPLATE_DECLARATION) ||
           isInState(ChtlParseState::CUSTOM_DECLARATION);
}

void ChtlStateMachine::performTransition(ChtlParseState newState) {
    ChtlParseState oldState = getCurrentState();
    
    // 执行退出回调
    auto exitIt = exitCallbacks_.find(oldState);
    if (exitIt != exitCallbacks_.end()) {
        exitIt->second(oldState, getCurrentContext());
    }
    
    // 更新状态
    stateStack_.back() = newState;
    getCurrentContext().setState(newState);
    
    // 通知词法分析器
    if (lexer_) {
        lexer_->setCurrentState(newState);
    }
    
    // 执行进入回调
    auto enterIt = enterCallbacks_.find(newState);
    if (enterIt != enterCallbacks_.end()) {
        enterIt->second(newState, getCurrentContext());
    }
    
    std::cerr << "[StateMachine] Transition: " << getStateName(oldState) 
              << " -> " << getStateName(newState) << "\n";
}

const StateTransition* ChtlStateMachine::findTransition(const Token& token) const {
    ChtlParseState currentState = getCurrentState();
    
    auto it = transitions_.find(currentState);
    if (it == transitions_.end()) {
        return nullptr;
    }
    
    // 遍历当前状态的所有转换规则
    for (const auto& transition : it->second) {
        if (transition.condition(token, getCurrentContext())) {
            return &transition;
        }
    }
    
    return nullptr;
}

} // namespace chtl::v2