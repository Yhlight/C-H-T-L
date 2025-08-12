#ifndef CHTL_LOCAL_STYLE_VALIDATOR_H
#define CHTL_LOCAL_STYLE_VALIDATOR_H

#include <string>
#include <vector>
#include <unordered_set>

namespace chtl {

// 局部样式块验证器
class LocalStyleValidator {
private:
    // 禁止的 CSS 特性
    static const std::unordered_set<std::string> forbiddenFeatures_;
    
    // 禁止的 @ 规则
    static const std::unordered_set<std::string> forbiddenAtRules_;
    
    // 允许的简单属性
    static const std::unordered_set<std::string> allowedProperties_;
    
public:
    // 验证结果
    struct ValidationResult {
        bool isValid;
        std::vector<std::string> errors;
        std::vector<std::string> warnings;
    };
    
    // 验证 CSS 规则
    static ValidationResult validateRule(const std::string& selector, const std::string& declarations);
    
    // 验证选择器
    static bool isValidLocalSelector(const std::string& selector);
    
    // 验证属性
    static bool isAllowedProperty(const std::string& property);
    
    // 检查是否包含禁止的特性
    static bool containsForbiddenFeature(const std::string& css);
    
    // 提取需要移到全局的样式
    struct ExtractedStyle {
        std::string selector;
        std::string declarations;
        bool isClassRule;    // 是否是类规则
        bool isIdRule;       // 是否是ID规则
        bool isPseudoRule;   // 是否是伪类/伪元素规则
    };
    
    static std::vector<ExtractedStyle> extractGlobalStyles(const std::string& cssContent);
    
private:
    // 解析 CSS 声明
    static std::vector<std::pair<std::string, std::string>> parseDeclarations(const std::string& declarations);
    
    // 规范化属性名
    static std::string normalizeProperty(const std::string& property);
    
    // 检查选择器类型
    static bool isClassSelector(const std::string& selector);
    static bool isIdSelector(const std::string& selector);
    static bool isPseudoSelector(const std::string& selector);
    static bool isInlineStyle(const std::string& selector);
};

// 静态成员初始化
const std::unordered_set<std::string> LocalStyleValidator::forbiddenFeatures_ = {
    "@media", "@keyframes", "@font-face", "@import", "@supports",
    "@page", "@namespace", "@document", "@viewport", "@counter-style"
};

const std::unordered_set<std::string> LocalStyleValidator::forbiddenAtRules_ = {
    "media", "keyframes", "font-face", "import", "supports",
    "page", "namespace", "document", "viewport", "counter-style"
};

// 局部样式块只允许基本的样式属性
const std::unordered_set<std::string> LocalStyleValidator::allowedProperties_ = {
    // 布局
    "display", "position", "top", "right", "bottom", "left",
    "width", "height", "min-width", "min-height", "max-width", "max-height",
    "margin", "margin-top", "margin-right", "margin-bottom", "margin-left",
    "padding", "padding-top", "padding-right", "padding-bottom", "padding-left",
    
    // 文本
    "color", "font-size", "font-family", "font-weight", "font-style",
    "text-align", "text-decoration", "line-height", "letter-spacing",
    
    // 背景和边框
    "background", "background-color", "background-image", "background-position",
    "background-repeat", "background-size",
    "border", "border-width", "border-style", "border-color",
    "border-radius", "box-shadow",
    
    // 其他常用
    "opacity", "visibility", "overflow", "cursor", "z-index",
    
    // Flexbox（基础）
    "flex", "flex-direction", "justify-content", "align-items",
    
    // 简单过渡（但不允许动画）
    "transition", "transition-duration", "transition-property"
};

} // namespace chtl

#endif // CHTL_LOCAL_STYLE_VALIDATOR_H