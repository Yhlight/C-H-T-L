#ifndef CHTL_STATE_FACTORY_H
#define CHTL_STATE_FACTORY_H

#include <memory>
#include <unordered_map>
#include <stack>
#include <string>
#include <functional>
#include "state/BasicState.h"

namespace chtl {

// 前向声明
class BasicLexer;

// 状态转换规则
struct StateTransition {
    StateType fromState;
    std::string trigger;  // 触发条件（如 "style{", "script{", "}" 等）
    StateType toState;
    bool pushToStack;     // 是否将当前状态压栈
};

// 状态工厂类 - 提供自动化状态管理
class StateFactory {
private:
    // 状态栈，用于管理嵌套状态
    static thread_local std::stack<std::shared_ptr<BasicState>> stateStack_;
    
    // 状态转换表
    static const std::vector<StateTransition> transitions_;
    
    // 状态创建器映射
    using StateCreator = std::function<std::shared_ptr<BasicState>(BasicLexer*)>;
    static const std::unordered_map<StateType, StateCreator> stateCreators_;
    
public:
    // 创建指定类型的状态
    static std::shared_ptr<BasicState> createState(StateType type, BasicLexer* lexer);
    
    // 创建初始状态（CHTL状态）
    static std::shared_ptr<BasicState> createInitialState(BasicLexer* lexer);
    
    // 自动化状态管理
    static std::shared_ptr<BasicState> autoTransition(
        BasicLexer* lexer,
        const std::shared_ptr<BasicState>& currentState,
        const std::string& trigger
    );
    
    // 状态栈管理
    static void pushState(const std::shared_ptr<BasicState>& state);
    static std::shared_ptr<BasicState> popState();
    static bool hasStateInStack();
    static void clearStateStack();
    
    // 获取当前状态栈深度
    static size_t getStackDepth() { return stateStack_.size(); }
    
    // 注册自定义状态转换
    static void registerTransition(const StateTransition& transition);
    
    // 检查是否可以转换
    static bool canTransition(StateType from, const std::string& trigger);
    
    // 获取转换目标状态
    static StateType getTransitionTarget(StateType from, const std::string& trigger);
    
private:
    // 初始化状态创建器
    static void initializeCreators();
    
    // 查找匹配的转换规则
    static const StateTransition* findTransition(StateType from, const std::string& trigger);
};

} // namespace chtl

#endif // CHTL_STATE_FACTORY_H