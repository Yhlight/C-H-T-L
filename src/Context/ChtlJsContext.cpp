#include "Context/ChtlJsContext.h"

namespace chtl {

ChtlJsContext::ChtlJsContext() : BasicContext(ContextType::CHTL_JS) {
    // 初始化CHTL-JS特有功能
}

void ChtlJsContext::enterScope(ScopeType scopeType, const std::string& scopeName) {
    BasicContext::enterScope(scopeType, scopeName);
    // CHTL-JS特有的作用域处理
}

void ChtlJsContext::exitScope() {
    BasicContext::exitScope();
    // CHTL-JS特有的作用域清理
}

void ChtlJsContext::reset() {
    BasicContext::reset();
    selectors_.clear();
    methods_.clear();
    animations_.clear();
    eventBindings_.clear();
}

bool ChtlJsContext::validate() {
    // 验证CHTL-JS上下文
    return true;
}

// 选择器管理
void ChtlJsContext::registerSelector(const std::string& selector, size_t location) {
    selectors_[selector] = location;
}

bool ChtlJsContext::hasSelector(const std::string& selector) const {
    return selectors_.find(selector) != selectors_.end();
}

std::optional<size_t> ChtlJsContext::getSelectorLocation(const std::string& selector) const {
    auto it = selectors_.find(selector);
    if (it != selectors_.end()) {
        return it->second;
    }
    return std::nullopt;
}

// 方法管理
void ChtlJsContext::registerMethod(const std::string& method, const MethodInfo& info) {
    methods_[method] = info;
}

bool ChtlJsContext::hasMethod(const std::string& method) const {
    return methods_.find(method) != methods_.end();
}

std::optional<MethodInfo> ChtlJsContext::getMethodInfo(const std::string& method) const {
    auto it = methods_.find(method);
    if (it != methods_.end()) {
        return it->second;
    }
    return std::nullopt;
}

// 动画管理
void ChtlJsContext::registerAnimation(const std::string& name, const AnimationInfo& info) {
    animations_[name] = info;
}

bool ChtlJsContext::hasAnimation(const std::string& name) const {
    return animations_.find(name) != animations_.end();
}

// 事件绑定管理
void ChtlJsContext::addEventBinding(const EventBinding& binding) {
    eventBindings_.push_back(binding);
}

std::vector<EventBinding> ChtlJsContext::getEventBindings() const {
    return eventBindings_;
}

// 获取所有注册的信息
std::vector<std::string> ChtlJsContext::getAllSelectors() const {
    std::vector<std::string> result;
    for (const auto& [selector, _] : selectors_) {
        result.push_back(selector);
    }
    return result;
}

std::vector<std::string> ChtlJsContext::getAllMethods() const {
    std::vector<std::string> result;
    for (const auto& [method, _] : methods_) {
        result.push_back(method);
    }
    return result;
}

std::vector<std::string> ChtlJsContext::getAllAnimations() const {
    std::vector<std::string> result;
    for (const auto& [name, _] : animations_) {
        result.push_back(name);
    }
    return result;
}

} // namespace chtl