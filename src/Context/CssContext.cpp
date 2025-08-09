#include "Context/CssContext.h"
#include <algorithm>
#include <regex>

namespace chtl {

CssContext::CssContext() 
    : BasicContext(ContextType::CSS, "CssContext"),
      ruleCount_(0),
      declarationCount_(0) {
}

void CssContext::enterScope() {
    // CSS通常不需要嵌套作用域，但可以用于处理嵌套规则
    BasicContext::enterScope();
}

void CssContext::exitScope() {
    BasicContext::exitScope();
}

void CssContext::reset() {
    BasicContext::reset();
    
    selectors_.clear();
    classNames_.clear();
    idNames_.clear();
    properties_.clear();
    variables_.clear();
    mediaQueries_.clear();
    keyframes_.clear();
    imports_.clear();
    currentSelector_.clear();
    currentProperty_.clear();
    currentAtRule_.clear();
    ruleCount_ = 0;
    declarationCount_ = 0;
}

void CssContext::addSelector(const std::string& selector) {
    selectors_.insert(selector);
    
    // 提取类名和ID
    std::regex classRegex(R"(\.([a-zA-Z0-9_-]+))");
    std::regex idRegex(R"(#([a-zA-Z0-9_-]+))");
    
    std::smatch match;
    std::string::const_iterator searchStart(selector.cbegin());
    
    // 提取所有类名
    while (std::regex_search(searchStart, selector.cend(), match, classRegex)) {
        addClass(match[1]);
        searchStart = match.suffix().first;
    }
    
    // 提取所有ID
    searchStart = selector.cbegin();
    while (std::regex_search(searchStart, selector.cend(), match, idRegex)) {
        addId(match[1]);
        searchStart = match.suffix().first;
    }
}

void CssContext::addClass(const std::string& className) {
    classNames_.insert(className);
}

void CssContext::addId(const std::string& id) {
    idNames_.insert(id);
}

bool CssContext::hasSelector(const std::string& selector) const {
    return selectors_.find(selector) != selectors_.end();
}

std::vector<std::string> CssContext::getAllSelectors() const {
    return std::vector<std::string>(selectors_.begin(), selectors_.end());
}

void CssContext::addProperty(const std::string& property, const std::string& value) {
    properties_[property].push_back(value);
    declarationCount_++;
}

void CssContext::addVariable(const std::string& name, const std::string& value) {
    variables_[name] = value;
}

bool CssContext::hasProperty(const std::string& property) const {
    return properties_.find(property) != properties_.end();
}

std::vector<std::string> CssContext::getPropertyValues(const std::string& property) const {
    auto it = properties_.find(property);
    if (it != properties_.end()) {
        return it->second;
    }
    return {};
}

void CssContext::addMediaQuery(const std::string& query) {
    mediaQueries_.push_back(query);
}

void CssContext::addKeyframe(const std::string& name) {
    keyframes_.push_back(name);
}

void CssContext::addImport(const std::string& url) {
    imports_.push_back(url);
}

bool CssContext::isValidSelector(const std::string& selector) const {
    // 简单的CSS选择器验证
    if (selector.empty()) return false;
    
    // 检查是否包含无效字符
    static const std::regex invalidChars(R"([^\w\s\-_#.\[\]:,>+~*='"()|$^])");
    if (std::regex_search(selector, invalidChars)) {
        return false;
    }
    
    // 更复杂的验证可以在这里添加
    return true;
}

bool CssContext::isValidProperty(const std::string& property) const {
    // 简单的CSS属性名验证
    if (property.empty()) return false;
    
    // CSS属性名通常是小写字母和连字符
    static const std::regex propertyPattern(R"(^[a-z\-]+$)");
    return std::regex_match(property, propertyPattern);
}

bool CssContext::isValidValue(const std::string& property, const std::string& value) const {
    // 简单的值验证
    if (value.empty()) return false;
    
    // 这里可以根据不同的属性添加特定的验证逻辑
    // 例如：color属性应该是有效的颜色值
    // 暂时只做基本验证
    
    (void)property;  // 避免未使用参数警告
    return true;
}

} // namespace chtl