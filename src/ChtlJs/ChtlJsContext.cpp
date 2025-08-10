#include "Context/ChtlJsContext.h"
#include <algorithm>
#include <sstream>

namespace chtl {

ChtlJsContext::ChtlJsContext() 
    : BasicContext(ContextType::CHTL_JS, "ChtlJsContext"),
      totalSelectors_(0),
      totalChtlMethods_(0),
      totalAnimations_(0) {
    initializeMethodTransforms();
    initializeRuntimeFunctions();
}

void ChtlJsContext::enterScope(ScopeType scopeType, const std::string& scopeName) {
    BasicContext::enterScope(scopeType, scopeName);
    // CHTL-JS特定的作用域处理
}

void ChtlJsContext::exitScope() {
    BasicContext::exitScope();
    // CHTL-JS特定的作用域清理
}

void ChtlJsContext::reset() {
    BasicContext::reset();
    
    selectors_.clear();
    cachedSelectors_.clear();
    listenCalls_.clear();
    delegateCalls_.clear();
    animations_.clear();
    selectorVariables_.clear();
    requiredRuntimeFunctions_.clear();
    
    totalSelectors_ = 0;
    totalChtlMethods_ = 0;
    totalAnimations_ = 0;
}

void ChtlJsContext::registerSelector(const std::string& selector, size_t location) {
    auto it = selectors_.find(selector);
    if (it != selectors_.end()) {
        it->second.usageCount++;
        it->second.locations.push_back(location);
    } else {
        SelectorInfo info;
        info.selector = selector;
        info.type = analyzeSelectorType(selector);
        info.usageCount = 1;
        info.locations.push_back(location);
        selectors_[selector] = info;
    }
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
    
    // 生成新的变量名
    std::string varName = generateSelectorVariable(selector);
    selectorVariables_[selector] = varName;
    
    // 如果频繁使用，标记为需要缓存
    if (shouldCacheSelector(selector)) {
        cachedSelectors_.insert(selector);
    }
    
    return varName;
}

const ChtlJsContext::SelectorInfo* ChtlJsContext::getSelectorInfo(const std::string& selector) const {
    auto it = selectors_.find(selector);
    return it != selectors_.end() ? &it->second : nullptr;
}

std::vector<std::string> ChtlJsContext::getAllSelectors() const {
    std::vector<std::string> result;
    for (const auto& pair : selectors_) {
        result.push_back(pair.first);
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
    
    requireRuntimeFunction("$chtl_addListener");
}

void ChtlJsContext::registerDelegateCall(const std::string& parentSelector,
                                       const std::vector<std::string>& childSelectors,
                                       const std::unordered_map<std::string, std::string>& events,
                                       size_t location) {
    ChtlMethodInfo info;
    info.methodName = "delegate";
    info.targetSelector = parentSelector;
    info.parameters = events;
    info.location = location;
    
    // 存储子选择器信息
    std::stringstream ss;
    for (size_t i = 0; i < childSelectors.size(); ++i) {
        if (i > 0) ss << ",";
        ss << childSelectors[i];
    }
    info.parameters["_targets"] = ss.str();
    
    delegateCalls_.push_back(info);
    totalChtlMethods_++;
    
    requireRuntimeFunction("$chtl_delegateEvent");
}

void ChtlJsContext::registerAnimation(const AnimationInfo& animation) {
    animations_.push_back(animation);
    totalAnimations_++;
    
    requireRuntimeFunction("$chtl_animate");
}

std::string ChtlJsContext::transformSelector(const std::string& selector) {
    // 注册选择器
    registerSelector(selector, 0);
    
    // 决定是使用缓存变量还是直接查询
    if (shouldCacheSelector(selector)) {
        return getSelectorVariable(selector);
    } else {
        requireRuntimeFunction("$chtl_querySelector");
        return "$chtl_querySelector('" + selector + "')";
    }
}

std::string ChtlJsContext::transformMethod(const std::string& method, const std::string& target) {
    auto it = methodTransforms_.find(method);
    if (it != methodTransforms_.end()) {
        return it->second + "(" + target + ")";
    }
    return target + "." + method;
}

void ChtlJsContext::requireRuntimeFunction(const std::string& functionName) {
    requiredRuntimeFunctions_.insert(functionName);
}

std::vector<std::string> ChtlJsContext::getRequiredRuntimeFunctions() const {
    return std::vector<std::string>(requiredRuntimeFunctions_.begin(), 
                                  requiredRuntimeFunctions_.end());
}

bool ChtlJsContext::shouldCacheSelector(const std::string& selector) const {
    auto it = selectors_.find(selector);
    if (it != selectors_.end()) {
        // 使用次数超过2次就缓存
        return it->second.usageCount > 2;
    }
    return false;
}

std::vector<std::string> ChtlJsContext::getFrequentlyUsedSelectors(int threshold) const {
    std::vector<std::string> result;
    for (const auto& pair : selectors_) {
        if (pair.second.usageCount >= threshold) {
            result.push_back(pair.first);
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
    // 验证动画配置
    if (animation.duration <= 0) {
        return false;
    }
    
    // 验证关键帧时间点
    for (const auto& keyframe : animation.keyframes) {
        if (keyframe.first < 0.0 || keyframe.first > 1.0) {
            return false;
        }
    }
    
    return true;
}

void ChtlJsContext::reportSelectorError(const std::string& selector, const std::string& error) {
    addError("Selector error: " + selector + " - " + error);
}

void ChtlJsContext::reportMethodError(const std::string& method, const std::string& error) {
    addError("Method error: " + method + " - " + error);
}

void ChtlJsContext::reportAnimationError(const std::string& error) {
    addError("Animation error: " + error);
}

std::string ChtlJsContext::analyzeSelectorType(const std::string& selector) const {
    if (selector.empty()) return "invalid";
    
    if (selector[0] == '#') return "id";
    if (selector[0] == '.') return "class";
    if (selector.find(' ') != std::string::npos) return "mixed";
    if (selector.find('[') != std::string::npos && 
        selector.find(']') != std::string::npos) return "indexed";
    
    return "tag";
}

std::string ChtlJsContext::generateSelectorVariable(const std::string& selector) {
    // 生成基于选择器的变量名
    std::string varName = "$chtl_";
    
    if (selector[0] == '#') {
        varName += "id_" + selector.substr(1);
    } else if (selector[0] == '.') {
        varName += "class_" + selector.substr(1);
    } else {
        varName += "tag_" + selector;
    }
    
    // 清理非法字符
    std::replace(varName.begin(), varName.end(), ' ', '_');
    std::replace(varName.begin(), varName.end(), '-', '_');
    std::replace(varName.begin(), varName.end(), '[', '_');
    std::replace(varName.begin(), varName.end(), ']', '_');
    
    return varName;
}

bool ChtlJsContext::isValidCssSelector(const std::string& selector) const {
    if (selector.empty()) return false;
    
    // 基本验证
    // TODO: 实现更完整的CSS选择器验证
    return true;
}

bool ChtlJsContext::isValidEventName(const std::string& event) const {
    // 常见的DOM事件
    static const std::unordered_set<std::string> validEvents = {
        "click", "dblclick", "mousedown", "mouseup", "mousemove",
        "mouseenter", "mouseleave", "mouseover", "mouseout",
        "keydown", "keyup", "keypress",
        "focus", "blur", "change", "input", "submit",
        "load", "unload", "resize", "scroll",
        "touchstart", "touchend", "touchmove"
    };
    
    return validEvents.find(event) != validEvents.end();
}

void ChtlJsContext::initializeMethodTransforms() {
    // CHTL方法到运行时函数的映射
    methodTransforms_["listen"] = "$chtl_addListener";
    methodTransforms_["delegate"] = "$chtl_delegateEvent";
}

void ChtlJsContext::initializeRuntimeFunctions() {
    // 基础运行时函数
    // 这些会根据实际使用情况动态添加
}

bool ChtlJsContext::validate() {
    // ChtlJsContext 继承自 BasicContext，不实现额外的验证
    // 具体的验证逻辑应该在使用时通过其他上下文类完成
    return true;
}

} // namespace chtl