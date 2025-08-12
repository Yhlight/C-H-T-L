#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/Token.h"
#include "v2/Lexer/ChtlLexer.h"
#include <iostream>
#include <stdexcept>

namespace chtl::v2 {

ChtlStateMachine::ChtlStateMachine() 
    : currentState_(ChtlParseState::INITIAL)
    , currentSubState_(ChtlSubState::NONE)
    , parseContext_()
    , lexer_(nullptr) {
    // 初始上下文为全局
    contextStack_.push_back(ChtlContext::GLOBAL);
    stateStack_.push_back({ChtlParseState::INITIAL, ChtlSubState::NONE});
}

ChtlStateMachine::~ChtlStateMachine() = default;

void ChtlStateMachine::initialize() {
    // 注册所有状态转换规则
    registerTransitions();
    
    // 重置到初始状态
    reset();
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
        if (transition->nextState != currentState_ || 
            transition->nextSubState != currentSubState_) {
            performTransition(transition->nextState, transition->nextSubState);
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

void ChtlStateMachine::enterState(ChtlParseState newState, ChtlSubState newSubState) {
    // 保存当前状态到栈
    stateStack_.push_back({currentState_, currentSubState_});
    
    // 执行状态转换
    performTransition(newState, newSubState);
}

void ChtlStateMachine::exitState() {
    if (stateStack_.size() <= 1) {
        // 不能退出初始状态
        std::cerr << "Warning: Cannot exit initial state\n";
        return;
    }
    
    // 恢复之前的状态
    stateStack_.pop_back();
    const StateInfo& prevState = stateStack_.back();
    performTransition(prevState.state, prevState.subState);
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
    stateStack_.push_back({ChtlParseState::INITIAL, ChtlSubState::NONE});
    parseContext_.reset();
    
    if (lexer_) {
        lexer_->setCurrentState(currentState_);
    }
}

void ChtlStateMachine::switchSubState(ChtlSubState newSubState) {
    currentSubState_ = newSubState;
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

void ChtlStateMachine::performTransition(ChtlParseState newState, ChtlSubState newSubState) {
    ChtlParseState oldState = currentState_;
    ChtlSubState oldSubState = currentSubState_;
    
    currentState_ = newState;
    currentSubState_ = newSubState;
    
    // 通知词法分析器状态变化
    if (lexer_) {
        lexer_->setCurrentState(newState);
    }
    
    std::cout << "[State Transition] " 
              << getStateName(oldState) << "/" << getSubStateName(oldSubState)
              << " -> " 
              << getStateName(newState) << "/" << getSubStateName(newSubState) 
              << "\n";
}

const StateTransition* ChtlStateMachine::findTransition(const Token& token) const {
    // 构建状态键
    StateKey key{currentState_, currentSubState_};
    
    // 查找当前状态的转换规则
    auto it = transitions_.find(key);
    if (it == transitions_.end()) {
        // 如果没有找到特定子状态的规则，尝试查找 NONE 子状态的规则
        key.second = ChtlSubState::NONE;
        it = transitions_.find(key);
        if (it == transitions_.end()) {
            return nullptr;
        }
    }
    
    // 在规则列表中查找匹配的转换
    const auto& rules = it->second;
    for (const auto& rule : rules) {
        if (rule.condition(token, getCurrentContext(), currentSubState_)) {
            return &rule;
        }
    }
    
    return nullptr;
}

void ChtlStateMachine::addTransition(ChtlParseState fromState, ChtlSubState fromSubState,
                                    StateTransition::ConditionFunc condition,
                                    ChtlParseState toState, ChtlSubState toSubState,
                                    StateTransition::ActionFunc action) {
    StateKey key{fromState, fromSubState};
    StateTransition transition;
    transition.condition = condition;
    transition.nextState = toState;
    transition.nextSubState = toSubState;
    transition.action = action;
    transitions_[key].push_back(transition);
}

} // namespace chtl::v2