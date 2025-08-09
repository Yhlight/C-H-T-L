#include "Context/CssContext.h"
#include <algorithm>
#include <regex>

namespace chtl {

CssContext::CssContext() : BasicContext(ContextType::CSS, "CssContext") {
    // 初始化CSS特定的状态
    currentBlock_ = BlockType::NONE;
    ruleCount_ = 0;
    declarationCount_ = 0;
}

// 上下文管理
void CssContext::enterScope(ScopeType scopeType, const std::string& scopeName) {
    // 调用基类方法
    BasicContext::enterScope(scopeType, scopeName);
    
    // CSS特定的作用域处理
    if (scopeType == ScopeType::BLOCK) {
        selectorStack_.push(scopeName);
    }
}

void CssContext::exitScope() {
    // CSS特定的作用域处理
    if (!selectorStack_.empty() && getCurrentScope()->type == ScopeType::BLOCK) {
        selectorStack_.pop();
    }
    
    // 调用基类方法
    BasicContext::exitScope();
}

void CssContext::reset() {
    BasicContext::reset();
    
    // 重置CSS特定状态
    currentBlock_ = BlockType::NONE;
    currentSelector_.clear();
    while (!selectorStack_.empty()) {
        selectorStack_.pop();
    }
    selectors_.clear();
    classNames_.clear();
    idNames_.clear();
    customProperties_.clear();
    mediaQueries_.clear();
    imports_.clear();
    ruleCount_ = 0;
    declarationCount_ = 0;
}

// CSS选择器管理
void CssContext::addSelector(const std::string& selector) {
    selectors_.insert(selector);
    currentSelector_ = selector;
    ruleCount_++;
}

void CssContext::addClass(const std::string& className) {
    classNames_.insert(className);
}

void CssContext::addId(const std::string& idName) {
    idNames_.insert(idName);
}

bool CssContext::hasSelector(const std::string& selector) const {
    return selectors_.find(selector) != selectors_.end();
}

bool CssContext::hasClass(const std::string& className) const {
    return classNames_.find(className) != classNames_.end();
}

bool CssContext::hasId(const std::string& idName) const {
    return idNames_.find(idName) != idNames_.end();
}

// CSS属性管理
void CssContext::addProperty(const std::string& property, const std::string& value) {
    if (!currentSelector_.empty()) {
        properties_[currentSelector_][property] = value;
        declarationCount_++;
    }
}

void CssContext::addCustomProperty(const std::string& name, const std::string& value) {
    customProperties_[name] = value;
}

std::string CssContext::getProperty(const std::string& selector, const std::string& property) const {
    auto selectorIt = properties_.find(selector);
    if (selectorIt != properties_.end()) {
        auto propIt = selectorIt->second.find(property);
        if (propIt != selectorIt->second.end()) {
            return propIt->second;
        }
    }
    return "";
}

std::string CssContext::getCustomProperty(const std::string& name) const {
    auto it = customProperties_.find(name);
    if (it != customProperties_.end()) {
        return it->second;
    }
    return "";
}

// CSS特性管理
void CssContext::addMediaQuery(const std::string& query) {
    mediaQueries_.insert(query);
}

void CssContext::addImport(const std::string& importPath) {
    imports_.push_back(importPath);
}

void CssContext::setCurrentBlock(BlockType type) {
    currentBlock_ = type;
}

CssContext::BlockType CssContext::getCurrentBlock() const {
    return currentBlock_;
}

// 获取收集的信息
std::set<std::string> CssContext::getSelectors() const {
    return selectors_;
}

std::set<std::string> CssContext::getClassNames() const {
    return classNames_;
}

std::set<std::string> CssContext::getIdNames() const {
    return idNames_;
}

std::vector<std::string> CssContext::getImports() const {
    return imports_;
}

std::set<std::string> CssContext::getMediaQueries() const {
    return mediaQueries_;
}

// 其他已有方法
std::vector<std::string> CssContext::getAllSelectors() const {
    return std::vector<std::string>(selectors_.begin(), selectors_.end());
}

bool CssContext::hasProperty(const std::string& property) const {
    for (const auto& [selector, props] : properties_) {
        if (props.find(property) != props.end()) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> CssContext::getPropertyValues(const std::string& property) const {
    std::vector<std::string> values;
    for (const auto& [selector, props] : properties_) {
        auto it = props.find(property);
        if (it != props.end()) {
            values.push_back(it->second);
        }
    }
    return values;
}

void CssContext::addKeyframe(const std::string& name) {
    // TODO: 实现关键帧管理
}

bool CssContext::isValidSelector(const std::string& selector) const {
    // 简单的CSS选择器验证
    if (selector.empty()) return false;
    return true;
}

bool CssContext::isValidProperty(const std::string& property) const {
    // 简单的CSS属性名验证
    if (property.empty()) return false;
    return true;
}

bool CssContext::isValidValue(const std::string& property, const std::string& value) const {
    // 简单的值验证
    if (value.empty()) return false;
    (void)property;  // 避免未使用参数警告
    return true;
}

} // namespace chtl