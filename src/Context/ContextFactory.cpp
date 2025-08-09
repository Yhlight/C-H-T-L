#include "Context/ContextFactory.h"
#include "Context/ChtlContext.h"
#include "Context/CssContext.h"
#include "Context/JsContext.h"
#include "ChtlJs/ChtlJsContext.h"

namespace chtl {

std::shared_ptr<BasicContext> ContextFactory::createContext(ContextType type) {
    switch (type) {
        case ContextType::CHTL:
            return std::make_shared<ChtlContext>();
        case ContextType::CSS:
            return std::make_shared<CssContext>();
        case ContextType::JS:
            return std::make_shared<JsContext>();
        case ContextType::CHTL_JS:
            return std::make_shared<chtl_js::ChtlJsContext>();
        case ContextType::CONFIG:
            // 配置上下文使用CHTL上下文
            return std::make_shared<ChtlContext>();
        default:
            return nullptr;
    }
}

void ContextFactory::pushMarker(ContextType type, std::shared_ptr<BasicContext> context) {
    if (!context) return;
    
    contextStack_.push({type, context});
    
    // 为不同的上下文类型设置标记
    switch (type) {
        case ContextType::CHTL:
            context->enterScope(ScopeType::NAMESPACE, "chtl");
            break;
        case ContextType::CSS:
            context->enterScope(ScopeType::BLOCK, "style");
            break;
        case ContextType::JS:
            context->enterScope(ScopeType::GLOBAL, "script");
            break;
        case ContextType::CHTL_JS:
            context->enterScope(ScopeType::GLOBAL, "chtl-js");
            break;
        case ContextType::CONFIG:
            context->enterScope(ScopeType::BLOCK, "config");
            break;
    }
}

void ContextFactory::popMarker() {
    if (contextStack_.empty()) return;
    
    auto& [type, context] = contextStack_.top();
    
    // 退出作用域
    context->exitScope();
    
    contextStack_.pop();
}

std::shared_ptr<BasicContext> ContextFactory::getCurrentContext() const {
    if (contextStack_.empty()) return nullptr;
    return contextStack_.top().second;
}

ContextType ContextFactory::getCurrentType() const {
    if (contextStack_.empty()) return ContextType::CHTL;
    return contextStack_.top().first;
}

void ContextFactory::switchContext(ContextType newType) {
    // 保存当前上下文状态
    if (!contextStack_.empty()) {
        auto currentContext = getCurrentContext();
        if (currentContext) {
            // 可以在这里保存特定状态
        }
    }
    
    // 创建并切换到新上下文
    auto newContext = createContext(newType);
    pushMarker(newType, newContext);
}

void ContextFactory::restoreContext() {
    if (contextStack_.size() > 1) {
        popMarker();
    }
}

void ContextFactory::reset() {
    while (!contextStack_.empty()) {
        popMarker();
    }
}

std::shared_ptr<ChtlContext> ContextFactory::asChtlContext() const {
    auto context = getCurrentContext();
    if (context && getCurrentType() == ContextType::CHTL) {
        return std::dynamic_pointer_cast<ChtlContext>(context);
    }
    return nullptr;
}

std::shared_ptr<CssContext> ContextFactory::asCssContext() const {
    auto context = getCurrentContext();
    if (context && getCurrentType() == ContextType::CSS) {
        return std::dynamic_pointer_cast<CssContext>(context);
    }
    return nullptr;
}

std::shared_ptr<JsContext> ContextFactory::asJsContext() const {
    auto context = getCurrentContext();
    if (context && getCurrentType() == ContextType::JS) {
        return std::dynamic_pointer_cast<JsContext>(context);
    }
    return nullptr;
}

std::shared_ptr<chtl_js::ChtlJsContext> ContextFactory::asChtlJsContext() const {
    auto context = getCurrentContext();
    if (context && getCurrentType() == ContextType::CHTL_JS) {
        return std::dynamic_pointer_cast<chtl_js::ChtlJsContext>(context);
    }
    return nullptr;
}

bool ContextFactory::isInContext(ContextType type) const {
    // 遍历栈检查是否在指定类型的上下文中
    std::stack<std::pair<ContextType, std::shared_ptr<BasicContext>>> tempStack = contextStack_;
    while (!tempStack.empty()) {
        if (tempStack.top().first == type) {
            return true;
        }
        tempStack.pop();
    }
    return false;
}

size_t ContextFactory::getStackDepth() const {
    return contextStack_.size();
}

void ContextFactory::propagateError(const std::string& error) {
    // 向所有上下文传播错误
    std::stack<std::pair<ContextType, std::shared_ptr<BasicContext>>> tempStack = contextStack_;
    while (!tempStack.empty()) {
        auto& context = tempStack.top().second;
        if (context) {
            context->addError(error);
        }
        tempStack.pop();
    }
}

void ContextFactory::propagateWarning(const std::string& warning) {
    // 向所有上下文传播警告
    std::stack<std::pair<ContextType, std::shared_ptr<BasicContext>>> tempStack = contextStack_;
    while (!tempStack.empty()) {
        auto& context = tempStack.top().second;
        if (context) {
            context->addWarning(warning);
        }
        tempStack.pop();
    }
}

} // namespace chtl