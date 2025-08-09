#include "state/StateFactory.h"
#include "state/ChtlState.h"
#include "state/CssState.h"
#include "state/JsState.h"
#include "state/ChtlJsState.h"
#include <algorithm>
#include <vector>

namespace chtl {

// 静态成员定义
thread_local std::stack<std::shared_ptr<BasicState>> StateFactory::stateStack_;

// 状态转换表定义
const std::vector<StateTransition> StateFactory::transitions_ = {
    // CHTL -> CSS (style块)
    {StateType::CHTL, "style{", StateType::CSS, true},
    {StateType::CSS, "}", StateType::CHTL, false},
    
    // CHTL -> JS (script块)
    {StateType::CHTL, "script{", StateType::JS, true},
    {StateType::JS, "}", StateType::CHTL, false},
    
    // CHTL -> CHTL_JS (CHTL增强的JS)
    {StateType::CHTL, "{{", StateType::CHTL_JS, true},
    {StateType::CHTL_JS, "}}", StateType::CHTL, false},
    
    // 嵌套style块
    {StateType::CSS, "style{", StateType::CSS, true},
    
    // Origin块
    {StateType::CHTL, "@Html{", StateType::ORIGIN, true},
    {StateType::CHTL, "@Style{", StateType::ORIGIN, true},
    {StateType::CHTL, "@JavaScript{", StateType::ORIGIN, true},
    {StateType::ORIGIN, "}", StateType::CHTL, false}
};

// 状态创建器映射
const std::unordered_map<StateType, StateFactory::StateCreator> StateFactory::stateCreators_ = {
    {StateType::CHTL, [](BasicLexer* lexer) { return std::make_shared<ChtlState>(lexer); }},
    {StateType::CSS, [](BasicLexer* lexer) { return std::make_shared<CssState>(lexer); }},
    {StateType::JS, [](BasicLexer* lexer) { return std::make_shared<JsState>(lexer); }},
    {StateType::CHTL_JS, [](BasicLexer* lexer) { return std::make_shared<ChtlJsState>(lexer); }},
    {StateType::ORIGIN, [](BasicLexer* lexer) { return std::make_shared<ChtlState>(lexer); }}, // 暂时使用ChtlState
    {StateType::STRING, [](BasicLexer* lexer) { return std::make_shared<ChtlState>(lexer); }}, // 暂时使用ChtlState
    {StateType::COMMENT, [](BasicLexer* lexer) { return std::make_shared<ChtlState>(lexer); }} // 暂时使用ChtlState
};

std::shared_ptr<BasicState> StateFactory::createState(StateType type, BasicLexer* lexer) {
    auto it = stateCreators_.find(type);
    if (it != stateCreators_.end()) {
        return it->second(lexer);
    }
    // 默认返回CHTL状态
    return std::make_shared<ChtlState>(lexer);
}

std::shared_ptr<BasicState> StateFactory::createInitialState(BasicLexer* lexer) {
    clearStateStack(); // 确保状态栈是空的
    return createState(StateType::CHTL, lexer);
}

std::shared_ptr<BasicState> StateFactory::autoTransition(
    BasicLexer* lexer,
    const std::shared_ptr<BasicState>& currentState,
    const std::string& trigger
) {
    if (!currentState) {
        return nullptr;
    }
    
    StateType currentType = currentState->getType();
    const StateTransition* transition = findTransition(currentType, trigger);
    
    if (!transition) {
        return nullptr; // 没有匹配的转换规则
    }
    
    // 处理状态栈
    if (transition->pushToStack) {
        pushState(currentState);
    } else if (!transition->pushToStack && hasStateInStack()) {
        // 如果是返回转换，从栈中弹出状态
        auto previousState = popState();
        if (previousState) {
            return previousState;
        }
    }
    
    // 创建新状态
    return createState(transition->toState, lexer);
}

void StateFactory::pushState(const std::shared_ptr<BasicState>& state) {
    if (state) {
        stateStack_.push(state);
    }
}

std::shared_ptr<BasicState> StateFactory::popState() {
    if (!stateStack_.empty()) {
        auto state = stateStack_.top();
        stateStack_.pop();
        return state;
    }
    return nullptr;
}

bool StateFactory::hasStateInStack() {
    return !stateStack_.empty();
}

void StateFactory::clearStateStack() {
    while (!stateStack_.empty()) {
        stateStack_.pop();
    }
}

void StateFactory::registerTransition(const StateTransition& transition) {
    // 这里应该使用非const的transitions_，但为了保持简单，暂时不实现
    // 实际项目中可能需要一个可修改的转换表
    (void)transition;
}

bool StateFactory::canTransition(StateType from, const std::string& trigger) {
    return findTransition(from, trigger) != nullptr;
}

StateType StateFactory::getTransitionTarget(StateType from, const std::string& trigger) {
    const StateTransition* transition = findTransition(from, trigger);
    if (transition) {
        return transition->toState;
    }
    return from; // 没有转换，返回原状态
}

const StateTransition* StateFactory::findTransition(StateType from, const std::string& trigger) {
    auto it = std::find_if(transitions_.begin(), transitions_.end(),
        [from, &trigger](const StateTransition& t) {
            return t.fromState == from && t.trigger == trigger;
        });
    
    return (it != transitions_.end()) ? &(*it) : nullptr;
}

} // namespace chtl