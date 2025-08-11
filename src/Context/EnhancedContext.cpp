#include "Context/EnhancedContext.h"
#include "Node/Node.h"
#include <iostream>
#include <sstream>

namespace chtl {

// ComponentTemplate 实现
std::unique_ptr<Node> ComponentTemplate::instantiate() const {
    // TODO: 实现深拷贝逻辑
    // 这里需要一个 Node 的克隆方法
    return nullptr;
}

EnhancedContext::EnhancedContext() : StandardContext() {
    // 初始化为全局作用域
    scopeStack_.push(Scope::GLOBAL);
}

// 作用域管理
void EnhancedContext::pushScope(Scope scope) {
    scopeStack_.push(scope);
}

void EnhancedContext::popScope() {
    if (scopeStack_.size() > 1) {  // 保留全局作用域
        scopeStack_.pop();
    }
}

Scope EnhancedContext::getCurrentScope() const {
    return scopeStack_.empty() ? Scope::GLOBAL : scopeStack_.top();
}

bool EnhancedContext::isInScope(Scope scope) const {
    std::stack<Scope> temp = scopeStack_;
    while (!temp.empty()) {
        if (temp.top() == scope) return true;
        temp.pop();
    }
    return false;
}

// 元素上下文管理
void EnhancedContext::pushElement(const ElementContext& ctx) {
    elementStack_.push(ctx);
}

void EnhancedContext::popElement() {
    if (!elementStack_.empty()) {
        elementStack_.pop();
    }
}

ElementContext* EnhancedContext::getCurrentElement() {
    return elementStack_.empty() ? nullptr : &elementStack_.top();
}

// 模板注册
void EnhancedContext::registerComponent(const std::string& name, ComponentTemplate&& tmpl) {
    if (components_.find(name) != components_.end()) {
        addWarning("Component '" + name + "' is already defined, overwriting");
    }
    components_[name] = std::move(tmpl);
}

void EnhancedContext::registerStyle(const std::string& name, StyleTemplate&& tmpl) {
    if (styles_.find(name) != styles_.end()) {
        addWarning("Style '" + name + "' is already defined, overwriting");
    }
    styles_[name] = std::move(tmpl);
}

void EnhancedContext::registerVariable(const std::string& name, VariableGroup&& vars) {
    if (variables_.find(name) != variables_.end()) {
        addWarning("Variable group '" + name + "' is already defined, overwriting");
    }
    variables_[name] = std::move(vars);
}

// 命名空间模板注册
void EnhancedContext::registerNamespacedComponent(const std::string& ns, const std::string& name, ComponentTemplate&& tmpl) {
    nsComponents_[ns][name] = std::move(tmpl);
}

void EnhancedContext::registerNamespacedStyle(const std::string& ns, const std::string& name, StyleTemplate&& tmpl) {
    nsStyles_[ns][name] = std::move(tmpl);
}

void EnhancedContext::registerNamespacedVariable(const std::string& ns, const std::string& name, VariableGroup&& vars) {
    nsVariables_[ns][name] = std::move(vars);
}

// 模板查找
ComponentTemplate* EnhancedContext::findComponent(const std::string& name) {
    // 先在当前命名空间查找
    if (!currentNamespace_.empty()) {
        auto nsIt = nsComponents_.find(currentNamespace_);
        if (nsIt != nsComponents_.end()) {
            auto it = nsIt->second.find(name);
            if (it != nsIt->second.end()) {
                return &it->second;
            }
        }
    }
    
    // 再在全局查找
    auto it = components_.find(name);
    return it != components_.end() ? &it->second : nullptr;
}

StyleTemplate* EnhancedContext::findStyle(const std::string& name) {
    // 先在当前命名空间查找
    if (!currentNamespace_.empty()) {
        auto nsIt = nsStyles_.find(currentNamespace_);
        if (nsIt != nsStyles_.end()) {
            auto it = nsIt->second.find(name);
            if (it != nsIt->second.end()) {
                return &it->second;
            }
        }
    }
    
    // 再在全局查找
    auto it = styles_.find(name);
    return it != styles_.end() ? &it->second : nullptr;
}

VariableGroup* EnhancedContext::findVariable(const std::string& name) {
    // 先在当前命名空间查找
    if (!currentNamespace_.empty()) {
        auto nsIt = nsVariables_.find(currentNamespace_);
        if (nsIt != nsVariables_.end()) {
            auto it = nsIt->second.find(name);
            if (it != nsIt->second.end()) {
                return &it->second;
            }
        }
    }
    
    // 再在全局查找
    auto it = variables_.find(name);
    return it != variables_.end() ? &it->second : nullptr;
}

// 带命名空间的查找
ComponentTemplate* EnhancedContext::findComponent(const std::string& ns, const std::string& name) {
    auto nsIt = nsComponents_.find(ns);
    if (nsIt != nsComponents_.end()) {
        auto it = nsIt->second.find(name);
        if (it != nsIt->second.end()) {
            return &it->second;
        }
    }
    return nullptr;
}

StyleTemplate* EnhancedContext::findStyle(const std::string& ns, const std::string& name) {
    auto nsIt = nsStyles_.find(ns);
    if (nsIt != nsStyles_.end()) {
        auto it = nsIt->second.find(name);
        if (it != nsIt->second.end()) {
            return &it->second;
        }
    }
    return nullptr;
}

VariableGroup* EnhancedContext::findVariable(const std::string& ns, const std::string& name) {
    auto nsIt = nsVariables_.find(ns);
    if (nsIt != nsVariables_.end()) {
        auto it = nsIt->second.find(name);
        if (it != nsIt->second.end()) {
            return &it->second;
        }
    }
    return nullptr;
}

// 变量值查找
std::optional<std::string> EnhancedContext::getVariableValue(const std::string& groupName, const std::string& key) {
    auto* group = findVariable(groupName);
    if (group) {
        return group->getValue(key);
    }
    return std::nullopt;
}

std::optional<std::string> EnhancedContext::getVariableValue(const std::string& ns, const std::string& groupName, const std::string& key) {
    auto* group = findVariable(ns, groupName);
    if (group) {
        return group->getValue(key);
    }
    return std::nullopt;
}

// & 符号推导
std::string EnhancedContext::resolveAmpersand() const {
    if (elementStack_.empty()) {
        const_cast<EnhancedContext*>(this)->addError("Cannot use '&' outside of an element context");
        return "";
    }
    
    const ElementContext& ctx = elementStack_.top();
    
    // 优先使用类名
    if (!ctx.classes.empty()) {
        return "." + ctx.classes[0];
    }
    
    // 其次使用 ID
    if (!ctx.id.empty()) {
        return "#" + ctx.id;
    }
    
    // 最后使用标签名
    if (!ctx.tagName.empty()) {
        return ctx.tagName;
    }
    
    const_cast<EnhancedContext*>(this)->addError("Cannot resolve '&' - no class, id, or tag name available");
    return "";
}

// 命名空间管理
void EnhancedContext::enterNamespace(const std::string& name) {
    currentNamespace_ = name;
    pushScope(Scope::NAMESPACE_BLOCK);
}

void EnhancedContext::exitNamespace() {
    currentNamespace_.clear();
    popScope();
}

// 验证方法
bool EnhancedContext::isValidComponentName(const std::string& name) const {
    // 组件名应该以大写字母开头
    return !name.empty() && std::isupper(name[0]);
}

bool EnhancedContext::isValidStyleName(const std::string& name) const {
    // 样式名应该以大写字母开头
    return !name.empty() && std::isupper(name[0]);
}

bool EnhancedContext::isValidVariableName(const std::string& name) const {
    // 变量组名应该以大写字母开头
    return !name.empty() && std::isupper(name[0]);
}

// 错误报告增强
void EnhancedContext::reportUndefinedComponent(const std::string& name) {
    std::stringstream ss;
    ss << "Component '" << name << "' is not defined";
    
    // 提供建议
    if (!components_.empty()) {
        ss << ". Available components: ";
        bool first = true;
        for (const auto& [compName, _] : components_) {
            if (!first) ss << ", ";
            ss << compName;
            first = false;
        }
    }
    
    addError(ss.str());
}

void EnhancedContext::reportUndefinedStyle(const std::string& name) {
    std::stringstream ss;
    ss << "Style '" << name << "' is not defined";
    
    // 提供建议
    if (!styles_.empty()) {
        ss << ". Available styles: ";
        bool first = true;
        for (const auto& [styleName, _] : styles_) {
            if (!first) ss << ", ";
            ss << styleName;
            first = false;
        }
    }
    
    addError(ss.str());
}

void EnhancedContext::reportUndefinedVariable(const std::string& group, const std::string& key) {
    std::stringstream ss;
    ss << "Variable '" << group << "(" << key << ")' is not defined";
    
    auto* varGroup = findVariable(group);
    if (varGroup) {
        ss << ". Available keys in '" << group << "': ";
        bool first = true;
        for (const auto& [k, _] : varGroup->values) {
            if (!first) ss << ", ";
            ss << k;
            first = false;
        }
    } else {
        ss << ". Variable group '" << group << "' not found";
    }
    
    addError(ss.str());
}

// 调试支持
void EnhancedContext::dumpTemplates() const {
    std::cout << "=== Registered Templates ===" << std::endl;
    
    std::cout << "\nComponents:" << std::endl;
    for (const auto& [name, _] : components_) {
        std::cout << "  - " << name << std::endl;
    }
    
    std::cout << "\nStyles:" << std::endl;
    for (const auto& [name, _] : styles_) {
        std::cout << "  - " << name << std::endl;
    }
    
    std::cout << "\nVariable Groups:" << std::endl;
    for (const auto& [name, group] : variables_) {
        std::cout << "  - " << name << ": ";
        for (const auto& [key, value] : group.values) {
            std::cout << key << "=" << value << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n==========================" << std::endl;
}

} // namespace chtl