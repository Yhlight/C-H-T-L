#include "Context/ChtlJsContext.h"
#include <regex>

namespace chtl {

ChtlJsContext::ChtlJsContext() : BasicContext(ContextType::CHTL_JS, "ChtlJs") {
    totalSelectors_ = 0;
    totalChtlMethods_ = 0;
    totalAnimations_ = 0;
    initializeMethodTransforms();
    initializeRuntimeFunctions();
}

void ChtlJsContext::enterScope(ScopeType scopeType, const std::string& scopeName) {
    BasicContext::enterScope(scopeType, scopeName);
}

void ChtlJsContext::exitScope() {
    BasicContext::exitScope();
}

void ChtlJsContext::reset() {
    BasicContext::reset();
    selectors_.clear();
    cachedSelectors_.clear();
    listenCalls_.clear();
    delegateCalls_.clear();
    animations_.clear();
    selectorVariables_.clear();
    methodTransforms_.clear();
    requiredRuntimeFunctions_.clear();
    totalSelectors_ = 0;
    totalChtlMethods_ = 0;
    totalAnimations_ = 0;
}

bool ChtlJsContext::validate() {
    return BasicContext::validate();
}

void ChtlJsContext::registerSelector(const std::string& selector, size_t location) {
    auto& info = selectors_[selector];
    info.selector = selector;
    info.type = analyzeSelectorType(selector);
    info.locations.push_back(location);
    info.usageCount++;
    totalSelectors_++;
}

bool ChtlJsContext::hasSelector(const std::string& selector) const {
    return selectors_.find(selector) != selectors_.end();
}

std::string ChtlJsContext::getSelectorVariable(const std::string& selector) {
    auto it = selectorVariables_.find(selector);
    if (it != selectorVariables_.end()) {
        return it->second;
    }
    
    std::string varName = generateSelectorVariable(selector);
    selectorVariables_[selector] = varName;
    return varName;
}

const ChtlJsContext::SelectorInfo* ChtlJsContext::getSelectorInfo(const std::string& selector) const {
    auto it = selectors_.find(selector);
    if (it != selectors_.end()) {
        return &it->second;
    }
    return nullptr;
}

std::vector<std::string> ChtlJsContext::getAllSelectors() const {
    std::vector<std::string> result;
    for (const auto& [selector, info] : selectors_) {
        result.push_back(selector);
    }
    return result;
}

void ChtlJsContext::registerListenCall(const std::string& selector,
                                      const std::unordered_map<std::string, std::string>& events,
                                      size_t location) {
    ChtlMethodInfo info;
    info.methodName = "listen";
    info.targetSelector = selector;
    info.parameters = events;
    info.location = location;
    listenCalls_.push_back(info);
    totalChtlMethods_++;
    requireRuntimeFunction("listen");
}

void ChtlJsContext::registerDelegateCall(const std::string& parentSelector,
                                        const std::vector<std::string>& childSelectors,
                                        const std::unordered_map<std::string, std::string>& events,
                                        size_t location) {
    ChtlMethodInfo info;
    info.methodName = "delegate";
    info.targetSelector = parentSelector;
    // 存储子选择器作为参数
    for (size_t i = 0; i < childSelectors.size(); ++i) {
        info.parameters["child_" + std::to_string(i)] = childSelectors[i];
    }
    // 合并事件
    for (const auto& [event, handler] : events) {
        info.parameters[event] = handler;
    }
    info.location = location;
    delegateCalls_.push_back(info);
    totalChtlMethods_++;
    requireRuntimeFunction("delegate");
}

void ChtlJsContext::registerAnimation(const AnimationInfo& animation) {
    animations_.push_back(animation);
    totalAnimations_++;
    requireRuntimeFunction("animate");
}

std::string ChtlJsContext::transformSelector(const std::string& selector) {
    // 基本选择器转换逻辑
    if (selector.empty()) return "";
    
    if (selector[0] == '#') {
        return "document.getElementById('" + selector.substr(1) + "')";
    } else if (selector[0] == '.') {
        return "document.getElementsByClassName('" + selector.substr(1) + "')[0]";
    } else {
        return "document.getElementsByTagName('" + selector + "')[0]";
    }
}

std::string ChtlJsContext::transformMethod(const std::string& method, const std::string& target) {
    auto it = methodTransforms_.find(method);
    if (it != methodTransforms_.end()) {
        return target + "." + it->second;
    }
    return target + "." + method;
}

void ChtlJsContext::requireRuntimeFunction(const std::string& functionName) {
    requiredRuntimeFunctions_.insert(functionName);
}

std::vector<std::string> ChtlJsContext::getRequiredRuntimeFunctions() const {
    return std::vector<std::string>(requiredRuntimeFunctions_.begin(), requiredRuntimeFunctions_.end());
}

bool ChtlJsContext::shouldCacheSelector(const std::string& selector) const {
    auto it = selectors_.find(selector);
    if (it != selectors_.end()) {
        return it->second.usageCount > 1;
    }
    return false;
}

std::vector<std::string> ChtlJsContext::getFrequentlyUsedSelectors(int threshold) const {
    std::vector<std::string> result;
    for (const auto& [selector, info] : selectors_) {
        if (info.usageCount >= threshold) {
            result.push_back(selector);
        }
    }
    return result;
}

bool ChtlJsContext::validateSelector(const std::string& selector) const {
    return isValidCssSelector(selector);
}

bool ChtlJsContext::validateEventName(const std::string& event) const {
    return isValidEventName(event);
}

bool ChtlJsContext::validateAnimationConfig(const AnimationInfo& animation) const {
    // 基本验证
    return animation.duration > 0 && !animation.id.empty();
}

void ChtlJsContext::reportSelectorError(const std::string& selector, const std::string& error) {
    addError("Selector error for '" + selector + "': " + error);
}

void ChtlJsContext::reportMethodError(const std::string& method, const std::string& error) {
    addError("Method error for '" + method + "': " + error);
}

void ChtlJsContext::reportAnimationError(const std::string& error) {
    addError("Animation error: " + error);
}

std::string ChtlJsContext::analyzeSelectorType(const std::string& selector) const {
    if (selector.empty()) return "unknown";
    
    if (selector[0] == '#') return "id";
    if (selector[0] == '.') return "class";
    if (selector.find(' ') != std::string::npos ||
        selector.find('>') != std::string::npos ||
        selector.find('+') != std::string::npos ||
        selector.find('~') != std::string::npos) {
        return "mixed";
    }
    return "tag";
}

std::string ChtlJsContext::generateSelectorVariable(const std::string& selector) {
    static int counter = 0;
    std::string base = "sel";
    
    // 根据选择器类型生成变量名
    if (selector[0] == '#') {
        base = selector.substr(1);
    } else if (selector[0] == '.') {
        base = selector.substr(1) + "El";
    } else {
        base = selector + "El";
    }
    
    // 清理非法字符
    std::string cleanName;
    for (char c : base) {
        if (std::isalnum(c)) {
            cleanName += c;
        }
    }
    
    if (cleanName.empty()) {
        cleanName = "el" + std::to_string(counter++);
    }
    
    return cleanName;
}

bool ChtlJsContext::isValidCssSelector(const std::string& selector) const {
    if (selector.empty()) return false;
    
    // 基本验证
    try {
        // 简单的CSS选择器验证
        std::regex selectorRegex(R"(^[#.]?[a-zA-Z][\w-]*(\s*[>+~]\s*[#.]?[a-zA-Z][\w-]*)*$)");
        return std::regex_match(selector, selectorRegex);
    } catch (...) {
        return false;
    }
}

bool ChtlJsContext::isValidEventName(const std::string& event) const {
    static const std::unordered_set<std::string> validEvents = {
        "click", "dblclick", "mouseenter", "mouseleave", "mouseover", "mouseout",
        "mousemove", "mousedown", "mouseup", "keydown", "keyup", "keypress",
        "focus", "blur", "change", "input", "submit", "load", "unload",
        "resize", "scroll", "touchstart", "touchend", "touchmove"
    };
    
    return validEvents.find(event) != validEvents.end();
}

void ChtlJsContext::initializeMethodTransforms() {
    methodTransforms_["listen"] = "addEventListener";
    methodTransforms_["animate"] = "animate";
    methodTransforms_["delegate"] = "delegate";
}

void ChtlJsContext::initializeRuntimeFunctions() {
    // 运行时函数将在需要时添加
}

} // namespace chtl