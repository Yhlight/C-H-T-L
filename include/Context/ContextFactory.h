#ifndef CHTL_CONTEXT_FACTORY_H
#define CHTL_CONTEXT_FACTORY_H

#include <memory>
#include <stack>
#include <utility>
#include "Context/BasicContext.h"

namespace chtl {

// 前向声明
class ChtlContext;
class CssContext;
class JsContext;
// class ChtlJsContext; // TODO: 完整实现后再启用

// 上下文工厂类 - 提供上下文管理
class ContextFactory {
private:
    // 上下文栈 - 存储类型和上下文对
    std::stack<std::pair<ContextType, std::shared_ptr<BasicContext>>> contextStack_;
    
public:
    // 创建指定类型的上下文
    std::shared_ptr<BasicContext> createContext(ContextType type);
    
    // 上下文栈管理
    void pushMarker(ContextType type, std::shared_ptr<BasicContext> context);
    void popMarker();
    
    // 获取当前上下文
    std::shared_ptr<BasicContext> getCurrentContext() const;
    ContextType getCurrentType() const;
    
    // 上下文切换
    void switchContext(ContextType newType);
    void restoreContext();
    
    // 重置工厂
    void reset();
    
    // 类型转换辅助方法
    std::shared_ptr<ChtlContext> asChtlContext() const;
    std::shared_ptr<CssContext> asCssContext() const;
    std::shared_ptr<JsContext> asJsContext() const;
    // std::shared_ptr<ChtlJsContext> asChtlJsContext() const; // TODO: 完整实现后再启用
    std::shared_ptr<void> asChtlJsContext() const; // 临时返回void
    
    // 上下文检查
    bool isInContext(ContextType type) const;
    size_t getStackDepth() const;
    
    // 错误传播
    void propagateError(const std::string& error);
    void propagateWarning(const std::string& warning);
};

} // namespace chtl

#endif // CHTL_CONTEXT_FACTORY_H