#ifndef CHTL_CONTEXT_FACTORY_H
#define CHTL_CONTEXT_FACTORY_H

#include <memory>
#include <unordered_map>
#include <stack>
#include <string>
#include <functional>
#include "Context/BasicContext.h"

namespace chtl {

// 上下文切换规则
struct ContextTransition {
    ContextType fromContext;
    std::string trigger;     // 触发条件
    ContextType toContext;
    bool inheritSymbols;     // 是否继承符号表
    bool createNewScope;     // 是否创建新作用域
};

// 上下文标记规则
struct ContextMarker {
    std::string pattern;     // 匹配模式（如 "[Template]", "[Custom]" 等）
    ContextType contextType; // 对应的上下文类型
    ScopeType scopeType;    // 创建的作用域类型
    std::function<void(std::shared_ptr<BasicContext>&, const std::string&)> onEnter; // 进入时的回调
};

// 上下文工厂类 - 提供自动化上下文管理
class ContextFactory {
private:
    // 上下文栈
    static thread_local std::stack<std::shared_ptr<BasicContext>> contextStack_;
    
    // 当前活动上下文
    static thread_local std::shared_ptr<BasicContext> currentContext_;
    
    // 上下文转换表
    static const std::vector<ContextTransition> transitions_;
    
    // 上下文标记规则
    static const std::vector<ContextMarker> markers_;
    
    // 上下文创建器映射
    using ContextCreator = std::function<std::shared_ptr<BasicContext>()>;
    static const std::unordered_map<ContextType, ContextCreator> contextCreators_;
    
public:
    // 创建指定类型的上下文
    static std::shared_ptr<BasicContext> createContext(ContextType type);
    
    // 创建初始上下文
    static std::shared_ptr<BasicContext> createInitialContext();
    
    // 自动化上下文切换
    static std::shared_ptr<BasicContext> autoTransition(
        const std::string& trigger,
        const std::shared_ptr<BasicContext>& currentContext = nullptr
    );
    
    // 自动化上下文标记
    static bool autoMark(
        const std::string& token,
        std::shared_ptr<BasicContext>& context
    );
    
    // 上下文栈管理
    static void pushContext(const std::shared_ptr<BasicContext>& context);
    static std::shared_ptr<BasicContext> popContext();
    static bool hasContextInStack();
    static void clearContextStack();
    
    // 获取当前活动上下文
    static std::shared_ptr<BasicContext> getCurrentContext() { return currentContext_; }
    static void setCurrentContext(const std::shared_ptr<BasicContext>& context) { currentContext_ = context; }
    
    // 获取上下文栈深度
    static size_t getStackDepth() { return contextStack_.size(); }
    
    // 注册自定义转换和标记规则
    static void registerTransition(const ContextTransition& transition);
    static void registerMarker(const ContextMarker& marker);
    
    // 检查是否可以转换
    static bool canTransition(ContextType from, const std::string& trigger);
    
    // 获取转换目标上下文
    static ContextType getTransitionTarget(ContextType from, const std::string& trigger);
    
    // 符号表继承
    static void inheritSymbols(
        const std::shared_ptr<BasicContext>& from,
        std::shared_ptr<BasicContext>& to
    );
    
    // 上下文合并
    static void mergeContexts(
        const std::shared_ptr<BasicContext>& source,
        std::shared_ptr<BasicContext>& target
    );
    
private:
    // 初始化上下文创建器
    static void initializeCreators();
    
    // 查找匹配的转换规则
    static const ContextTransition* findTransition(ContextType from, const std::string& trigger);
    
    // 查找匹配的标记规则
    static const ContextMarker* findMarker(const std::string& token);
};

} // namespace chtl

#endif // CHTL_CONTEXT_FACTORY_H