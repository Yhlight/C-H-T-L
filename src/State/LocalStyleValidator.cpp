#include "State/LocalStyleValidator.h"
#include <algorithm>
#include <regex>
#include <sstream>

namespace chtl {

LocalStyleValidator::ValidationResult LocalStyleValidator::validateRule(
    const std::string& selector, 
    const std::string& declarations) {
    
    ValidationResult result;
    result.isValid = true;
    
    // 检查选择器
    if (!isValidLocalSelector(selector)) {
        result.isValid = false;
        result.errors.push_back("Invalid selector in local style block: " + selector);
    }
    
    // 检查是否包含禁止的特性
    if (containsForbiddenFeature(declarations)) {
        result.isValid = false;
        result.errors.push_back("Forbidden CSS features detected in local style block");
    }
    
    // 解析并验证每个属性
    auto props = parseDeclarations(declarations);
    for (const auto& [property, value] : props) {
        std::string normalizedProp = normalizeProperty(property);
        
        // 检查是否是动画相关属性
        if (normalizedProp == "animation" || normalizedProp.find("animation-") == 0) {
            result.isValid = false;
            result.errors.push_back("Animation properties are not allowed in local style blocks: " + property);
            continue;
        }
        
        // 检查是否是 CSS 变量定义
        if (normalizedProp.find("--") == 0) {
            result.isValid = false;
            result.errors.push_back("CSS custom properties are not allowed in local style blocks: " + property);
            continue;
        }
        
        // 对于内联样式，检查是否是允许的属性
        if (isInlineStyle(selector) && !isAllowedProperty(normalizedProp)) {
            result.warnings.push_back("Property '" + property + "' may not work as expected in inline styles");
        }
    }
    
    return result;
}

bool LocalStyleValidator::isValidLocalSelector(const std::string& selector) {
    // 去除空格
    std::string trimmed = selector;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);
    
    // 空选择器表示内联样式
    if (trimmed.empty()) {
        return true;
    }
    
    // 类选择器 (.className)
    if (isClassSelector(trimmed)) {
        return true;
    }
    
    // ID 选择器 (#id)
    if (isIdSelector(trimmed)) {
        return true;
    }
    
    // 伪类/伪元素选择器 (&:hover, &::before)
    if (isPseudoSelector(trimmed)) {
        return true;
    }
    
    // 不允许其他复杂选择器
    return false;
}

bool LocalStyleValidator::isAllowedProperty(const std::string& property) {
    std::string normalized = normalizeProperty(property);
    return allowedProperties_.find(normalized) != allowedProperties_.end();
}

bool LocalStyleValidator::containsForbiddenFeature(const std::string& css) {
    for (const auto& feature : forbiddenFeatures_) {
        if (css.find(feature) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::vector<LocalStyleValidator::ExtractedStyle> LocalStyleValidator::extractGlobalStyles(
    const std::string& cssContent) {
    
    std::vector<ExtractedStyle> extracted;
    
    // 简单的 CSS 解析（实际应该用更健壮的解析器）
    std::regex ruleRegex(R"(([^{]+)\{([^}]+)\})");
    std::smatch match;
    std::string content = cssContent;
    
    while (std::regex_search(content, match, ruleRegex)) {
        std::string selector = match[1];
        std::string declarations = match[2];
        
        // 去除空格
        selector.erase(0, selector.find_first_not_of(" \t\n\r"));
        selector.erase(selector.find_last_not_of(" \t\n\r") + 1);
        
        ExtractedStyle style;
        style.selector = selector;
        style.declarations = declarations;
        style.isClassRule = isClassSelector(selector);
        style.isIdRule = isIdSelector(selector);
        style.isPseudoRule = isPseudoSelector(selector);
        
        // 只提取非内联样式
        if (!selector.empty()) {
            extracted.push_back(style);
        }
        
        content = match.suffix();
    }
    
    return extracted;
}

std::vector<std::pair<std::string, std::string>> LocalStyleValidator::parseDeclarations(
    const std::string& declarations) {
    
    std::vector<std::pair<std::string, std::string>> result;
    std::regex propRegex(R"(([^:]+):([^;]+);?)");
    std::smatch match;
    std::string content = declarations;
    
    while (std::regex_search(content, match, propRegex)) {
        std::string property = match[1];
        std::string value = match[2];
        
        // 去除空格
        property.erase(0, property.find_first_not_of(" \t\n\r"));
        property.erase(property.find_last_not_of(" \t\n\r") + 1);
        value.erase(0, value.find_first_not_of(" \t\n\r"));
        value.erase(value.find_last_not_of(" \t\n\r") + 1);
        
        result.push_back({property, value});
        content = match.suffix();
    }
    
    return result;
}

std::string LocalStyleValidator::normalizeProperty(const std::string& property) {
    std::string normalized = property;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}

bool LocalStyleValidator::isClassSelector(const std::string& selector) {
    return !selector.empty() && selector[0] == '.';
}

bool LocalStyleValidator::isIdSelector(const std::string& selector) {
    return !selector.empty() && selector[0] == '#';
}

bool LocalStyleValidator::isPseudoSelector(const std::string& selector) {
    return selector.find("&:") == 0 || selector.find("&::") == 0;
}

bool LocalStyleValidator::isInlineStyle(const std::string& selector) {
    return selector.empty();
}

} // namespace chtl