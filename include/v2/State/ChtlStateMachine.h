#pragma once

#include "ChtlParseState.h"
#include "v2/Context/ParseContext.h"
#include <memory>
#include <vector>
#include <functional>

namespace chtl::v2 {

// 前向声明
class Token;
class ChtlLexer;

/**
 * 状态转换规则
 */
struct StateTransition {
    using ConditionFunc = std::function<bool(const Token&, const ParseContext&)>;
    using ActionFunc = std::function<void(ParseContext&)>;
    
    ConditionFunc condition;    // 转换条件
    ChtlParseState nextState;   // 目标状态
    ActionFunc action;          // 转换时的动作（可选）
};

/**
 * CHTL 状态机
 * 负责管理解析状态和状态转换
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
    ChtlParseState getCurrentState() const;
    
    /**
     * 处理 Token 并可能触发状态转换
     * @return 是否成功处理
     */
    bool processToken(const Token& token);
    
    /**
     * 强制转换到指定状态
     */
    void transitionTo(ChtlParseState newState);
    
    /**
     * 推入新的状态（保存当前状态）
     */
    void pushState(ChtlParseState newState);
    
    /**
     * 弹出状态（恢复之前的状态）
     */
    void popState();
    
    /**
     * 获取当前上下文
     */
    ParseContext& getCurrentContext();
    const ParseContext& getCurrentContext() const;
    
    /**
     * 设置词法分析器（用于状态相关的 token 识别）
     */
    void setLexer(ChtlLexer* lexer);
    
    /**
     * 注册状态进入/退出回调
     */
    using StateCallback = std::function<void(ChtlParseState, ParseContext&)>;
    void onStateEnter(ChtlParseState state, StateCallback callback);
    void onStateExit(ChtlParseState state, StateCallback callback);
    
    /**
     * 重置状态机
     */
    void reset();
    
    /**
     * 获取状态栈深度（用于调试）
     */
    size_t getStateStackDepth() const { return stateStack_.size(); }
    
    /**
     * 检查是否在特定状态或其子状态中
     */
    bool isInState(ChtlParseState state) const;
    bool isInStyleContext() const;
    bool isInScriptContext() const;
    bool isInTemplateContext() const;
    
private:
    /**
     * 注册所有状态转换规则
     */
    void registerTransitions();
    
    /**
     * 注册特定状态的转换规则
     */
    void registerTopLevelTransitions();
    void registerElementContentTransitions();
    void registerStyleBlockTransitions();
    void registerTemplateDeclarationTransitions();
    // ... 其他状态的转换规则
    
    /**
     * 执行状态转换
     */
    void performTransition(ChtlParseState newState);
    
    /**
     * 查找适用的转换规则
     */
    const StateTransition* findTransition(const Token& token) const;
    
private:
    // 状态栈
    std::vector<ChtlParseState> stateStack_;
    
    // 上下文栈
    std::vector<ParseContext> contextStack_;
    
    // 状态转换规则表
    std::unordered_map<ChtlParseState, std::vector<StateTransition>> transitions_;
    
    // 状态回调
    std::unordered_map<ChtlParseState, StateCallback> enterCallbacks_;
    std::unordered_map<ChtlParseState, StateCallback> exitCallbacks_;
    
    // 关联的词法分析器
    ChtlLexer* lexer_;
};

} // namespace chtl::v2