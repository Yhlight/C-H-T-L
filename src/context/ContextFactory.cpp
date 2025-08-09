#include "context/ContextFactory.h"
#include "context/ChtlContext.h"
#include "context/CssContext.h"
#include "context/JsContext.h"
#include "context/ChtlJsContext.h"
#include <algorithm>

namespace chtl {

// 静态成员定义
thread_local std::stack<std::shared_ptr<BasicContext>> ContextFactory::contextStack_;
thread_local std::shared_ptr<BasicContext> ContextFactory::currentContext_;

// 上下文转换表定义
const std::vector<ContextTransition> ContextFactory::transitions_ = {
    // CHTL -> CSS (进入style块)
    {ContextType::CHTL, "style{", ContextType::CSS, false, true},
    {ContextType::CSS, "}", ContextType::CHTL, false, false},
    
    // CHTL -> JS (进入script块)
    {ContextType::CHTL, "script{", ContextType::JS, false, true},
    {ContextType::JS, "}", ContextType::CHTL, false, false},
    
    // CHTL -> CHTL_JS (增强JS语法)
    {ContextType::CHTL, "{{", ContextType::CHTL_JS, true, true},
    {ContextType::CHTL_JS, "}}", ContextType::CHTL, false, false},
    
    // 模板和自定义元素上下文
    {ContextType::CHTL, "[Template]", ContextType::TEMPLATE, true, true},
    {ContextType::TEMPLATE, "}", ContextType::CHTL, false, false},
    
    {ContextType::CHTL, "[Custom]", ContextType::CUSTOM, true, true},
    {ContextType::CUSTOM, "}", ContextType::CHTL, false, false},
    
    // 命名空间上下文
    {ContextType::CHTL, "[Namespace]", ContextType::NAMESPACE, true, true},
    {ContextType::NAMESPACE, "}", ContextType::CHTL, false, false}
};

// 上下文标记规则定义
const std::vector<ContextMarker> ContextFactory::markers_ = {
    // 模板标记
    {"[Template]", ContextType::TEMPLATE, ScopeType::TEMPLATE, 
        [](std::shared_ptr<BasicContext>& ctx, const std::string& token) {
            (void)token;
            if (auto chtlCtx = std::dynamic_pointer_cast<ChtlContext>(ctx)) {
                chtlCtx->enterScope(ScopeType::TEMPLATE, "template");
            }
        }
    },
    
    // 自定义元素标记
    {"[Custom]", ContextType::CUSTOM, ScopeType::CUSTOM,
        [](std::shared_ptr<BasicContext>& ctx, const std::string& token) {
            (void)token;
            if (auto chtlCtx = std::dynamic_pointer_cast<ChtlContext>(ctx)) {
                chtlCtx->enterScope(ScopeType::CUSTOM, "custom");
            }
        }
    },
    
    // 命名空间标记
    {"[Namespace]", ContextType::NAMESPACE, ScopeType::NAMESPACE,
        [](std::shared_ptr<BasicContext>& ctx, const std::string& token) {
            (void)token;
            if (auto chtlCtx = std::dynamic_pointer_cast<ChtlContext>(ctx)) {
                chtlCtx->enterScope(ScopeType::NAMESPACE, "namespace");
            }
        }
    },
    
    // 配置标记
    {"[Configuration]", ContextType::CHTL, ScopeType::GLOBAL,
        [](std::shared_ptr<BasicContext>& ctx, const std::string& token) {
            (void)token;
            ctx->setConfig("in_configuration", "true");
        }
    },
    
    // 导入标记
    {"[Import]", ContextType::CHTL, ScopeType::GLOBAL,
        [](std::shared_ptr<BasicContext>& ctx, const std::string& token) {
            (void)token;
            ctx->setConfig("in_import", "true");
        }
    }
};

// 上下文创建器映射
const std::unordered_map<ContextType, ContextFactory::ContextCreator> ContextFactory::contextCreators_ = {
    {ContextType::CHTL, []() { return std::make_shared<ChtlContext>(); }},
    {ContextType::CSS, []() { return std::make_shared<CssContext>(); }},
    {ContextType::JS, []() { return std::make_shared<JsContext>(); }},
    {ContextType::CHTL_JS, []() { return std::make_shared<ChtlJsContext>(); }},
    {ContextType::TEMPLATE, []() { return std::make_shared<ChtlContext>(); }}, // 使用ChtlContext
    {ContextType::CUSTOM, []() { return std::make_shared<ChtlContext>(); }},   // 使用ChtlContext
    {ContextType::NAMESPACE, []() { return std::make_shared<ChtlContext>(); }} // 使用ChtlContext
};

std::shared_ptr<BasicContext> ContextFactory::createContext(ContextType type) {
    auto it = contextCreators_.find(type);
    if (it != contextCreators_.end()) {
        auto context = it->second();
        context->setConfig("context_type", std::to_string(static_cast<int>(type)));
        return context;
    }
    // 默认返回CHTL上下文
    return std::make_shared<ChtlContext>();
}

std::shared_ptr<BasicContext> ContextFactory::createInitialContext() {
    clearContextStack();
    currentContext_ = createContext(ContextType::CHTL);
    return currentContext_;
}

std::shared_ptr<BasicContext> ContextFactory::autoTransition(
    const std::string& trigger,
    const std::shared_ptr<BasicContext>& context
) {
    auto ctx = context ? context : currentContext_;
    if (!ctx) {
        return nullptr;
    }
    
    ContextType currentType = ctx->getType();
    const ContextTransition* transition = findTransition(currentType, trigger);
    
    if (!transition) {
        return nullptr; // 没有匹配的转换规则
    }
    
    // 创建新上下文
    auto newContext = createContext(transition->toContext);
    
    // 处理符号表继承
    if (transition->inheritSymbols) {
        inheritSymbols(ctx, newContext);
    }
    
    // 创建新作用域
    if (transition->createNewScope) {
        ScopeType scopeType = ScopeType::BLOCK;
        switch (transition->toContext) {
            case ContextType::TEMPLATE:
                scopeType = ScopeType::TEMPLATE;
                break;
            case ContextType::CUSTOM:
                scopeType = ScopeType::CUSTOM;
                break;
            case ContextType::NAMESPACE:
                scopeType = ScopeType::NAMESPACE;
                break;
            case ContextType::CSS:
                scopeType = ScopeType::STYLE;
                break;
            case ContextType::JS:
            case ContextType::CHTL_JS:
                scopeType = ScopeType::SCRIPT;
                break;
            default:
                break;
        }
        newContext->enterScope(scopeType, trigger);
    }
    
    // 更新当前上下文
    pushContext(ctx);
    currentContext_ = newContext;
    
    return newContext;
}

bool ContextFactory::autoMark(
    const std::string& token,
    std::shared_ptr<BasicContext>& context
) {
    if (!context) {
        return false;
    }
    
    const ContextMarker* marker = findMarker(token);
    if (!marker) {
        return false;
    }
    
    // 执行标记回调
    if (marker->onEnter) {
        marker->onEnter(context, token);
    }
    
    // 如果需要切换上下文类型
    if (marker->contextType != context->getType()) {
        auto newContext = createContext(marker->contextType);
        inheritSymbols(context, newContext);
        context = newContext;
        currentContext_ = newContext;
    }
    
    return true;
}

void ContextFactory::pushContext(const std::shared_ptr<BasicContext>& context) {
    if (context) {
        contextStack_.push(context);
    }
}

std::shared_ptr<BasicContext> ContextFactory::popContext() {
    if (!contextStack_.empty()) {
        auto context = contextStack_.top();
        contextStack_.pop();
        currentContext_ = context;
        return context;
    }
    return nullptr;
}

bool ContextFactory::hasContextInStack() {
    return !contextStack_.empty();
}

void ContextFactory::clearContextStack() {
    while (!contextStack_.empty()) {
        contextStack_.pop();
    }
    currentContext_ = nullptr;
}

void ContextFactory::registerTransition(const ContextTransition& transition) {
    // 暂时不实现动态注册
    (void)transition;
}

void ContextFactory::registerMarker(const ContextMarker& marker) {
    // 暂时不实现动态注册
    (void)marker;
}

bool ContextFactory::canTransition(ContextType from, const std::string& trigger) {
    return findTransition(from, trigger) != nullptr;
}

ContextType ContextFactory::getTransitionTarget(ContextType from, const std::string& trigger) {
    const ContextTransition* transition = findTransition(from, trigger);
    if (transition) {
        return transition->toContext;
    }
    return from;
}

void ContextFactory::inheritSymbols(
    const std::shared_ptr<BasicContext>& from,
    std::shared_ptr<BasicContext>& to
) {
    if (!from || !to) {
        return;
    }
    
    // 复制全局符号表
    const auto& symbols = from->getGlobalSymbols();
    for (const auto& [name, info] : symbols) {
        to->addSymbol(name, info);
    }
    
    // 复制配置
    const auto& config = from->getConfiguration();
    for (const auto& [key, value] : config) {
        to->setConfig(key, value);
    }
}

void ContextFactory::mergeContexts(
    const std::shared_ptr<BasicContext>& source,
    std::shared_ptr<BasicContext>& target
) {
    if (!source || !target) {
        return;
    }
    
    // 合并符号表
    inheritSymbols(source, target);
    
    // 合并错误和警告
    for (const auto& error : source->getErrors()) {
        target->addError(error);
    }
    
    for (const auto& warning : source->getWarnings()) {
        target->addWarning(warning);
    }
}

const ContextTransition* ContextFactory::findTransition(ContextType from, const std::string& trigger) {
    auto it = std::find_if(transitions_.begin(), transitions_.end(),
        [from, &trigger](const ContextTransition& t) {
            return t.fromContext == from && t.trigger == trigger;
        });
    
    return (it != transitions_.end()) ? &(*it) : nullptr;
}

const ContextMarker* ContextFactory::findMarker(const std::string& token) {
    auto it = std::find_if(markers_.begin(), markers_.end(),
        [&token](const ContextMarker& m) {
            return m.pattern == token;
        });
    
    return (it != markers_.end()) ? &(*it) : nullptr;
}

} // namespace chtl