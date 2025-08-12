#pragma once

#include "ChtlParseState.h"
#include "v2/Context/ParseContext.h"
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

namespace chtl::v2 {

// 前向声明
class Token;
class ChtlLexer;

/**
 * 状态转换规则
 */
struct StateTransition {
    using ConditionFunc = std::function<bool(const Token&, ChtlContext, ChtlSubState)>;
    using ActionFunc = std::function<void(ParseContext&)>;
    
    ConditionFunc condition;    // 转换条件（包含上下文和子状态）
    ChtlParseState nextState;   // 目标状态
    ChtlSubState nextSubState;  // 目标子状态
    ActionFunc action;          // 转换时的动作（可选）
};

/**
 * CHTL 状态机（简化版）
 * 基于全局/局部上下文的状态管理，支持子状态
 */
class ChtlStateMachine {
public:
    ChtlStateMachine();
    ~ChtlStateMachine();
    
    /**
     * 初始化状态机
     */
    void initialize();
    
    /**
     * 获取当前状态
     */
    ChtlParseState getCurrentState() const { return currentState_; }
    
    /**
     * 获取当前子状态
     */
    ChtlSubState getCurrentSubState() const { return currentSubState_; }
    
    /**
     * 获取当前上下文（全局/局部）
     */
    ChtlContext getCurrentContext() const;
    
    /**
     * 处理 Token 并可能触发状态转换
     * @return 是否成功处理
     */
    bool processToken(const Token& token);
    
    /**
     * 进入新状态
     */
    void enterState(ChtlParseState newState, ChtlSubState subState = ChtlSubState::NONE);
    
    /**
     * 切换子状态
     */
    void switchSubState(ChtlSubState newSubState);
    
    /**
     * 退出当前状态
     */
    void exitState();
    
    /**
     * 进入局部上下文（如进入元素内部）
     */
    void enterLocalContext();
    
    /**
     * 退出局部上下文（返回全局或上层）
     */
    void exitLocalContext();
    
    /**
     * 获取当前解析上下文
     */
    ParseContext& getParseContext() { return parseContext_; }
    const ParseContext& getParseContext() const { return parseContext_; }
    
    /**
     * 设置词法分析器（用于状态相关的 token 识别）
     */
    void setLexer(ChtlLexer* lexer) { lexer_ = lexer; }
    
    /**
     * 重置状态机
     */
    void reset();
    
    /**
     * 调试信息
     */
    void printState() const;
    
private:
    /**
     * 注册状态转换规则
     */
    void registerTransitions();
    void registerInitialTransitions();
    void registerElementTransitions();
    void registerElementSubStateTransitions();
    void registerStyleTransitions();
    void registerStyleSubStateTransitions();
    void registerScriptTransitions();
    void registerScriptSubStateTransitions();
    void registerDeclarationTransitions();
    void registerReferenceTransitions();
    
    /**
     * 执行状态转换
     */
    void performTransition(ChtlParseState newState, ChtlSubState newSubState);
    
    /**
     * 添加状态转换规则的辅助方法
     */
    void addTransition(ChtlParseState fromState, ChtlSubState fromSubState,
                      StateTransition::ConditionFunc condition,
                      ChtlParseState toState, ChtlSubState toSubState,
                      StateTransition::ActionFunc action = nullptr);
    
    /**
     * 查找适用的状态转换
     */
    const StateTransition* findTransition(const Token& token) const;
    
private:
    // 当前状态
    ChtlParseState currentState_;
    ChtlSubState currentSubState_;
    
    // 上下文栈（支持嵌套）
    std::vector<ChtlContext> contextStack_;
    
    // 解析上下文
    ParseContext parseContext_;
    
    // 状态转换规则表（按状态和子状态组织）
    using StateKey = std::pair<ChtlParseState, ChtlSubState>;
    std::map<StateKey, std::vector<StateTransition>> transitions_;
    
    // 关联的词法分析器
    ChtlLexer* lexer_;
    
    // 状态栈（用于返回）
    struct StateInfo {
        ChtlParseState state;
        ChtlSubState subState;
    };
    std::vector<StateInfo> stateStack_;
};

} // namespace chtl::v2