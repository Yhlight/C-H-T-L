#include "Predefine/Registry.h"
#include <algorithm>

namespace chtl {

// 单例实现
Registry& Registry::getInstance() {
    static Registry instance;
    return instance;
}

Registry::Registry() {
    // 构造时可以初始化默认值
}

// 注册方法实现
void Registry::registerElement(const ElementInfo& info) {
    elements_[info.name] = info;
    elementsByCategory_[info.category].insert(info.name);
}

void Registry::registerStyle(const StyleInfo& info) {
    styles_[info.name] = info;
    stylesByCategory_[info.category].insert(info.name);
}

void Registry::registerVar(const VarInfo& info) {
    vars_[info.name] = info;
    varsByType_[info.type].insert(info.name);
}

void Registry::registerFunction(const FunctionInfo& info) {
    functions_[info.name] = info;
}

// 批量注册
void Registry::registerElements(const std::vector<ElementInfo>& elements) {
    for (const auto& element : elements) {
        registerElement(element);
    }
}

void Registry::registerStyles(const std::vector<StyleInfo>& styles) {
    for (const auto& style : styles) {
        registerStyle(style);
    }
}

void Registry::registerVars(const std::vector<VarInfo>& vars) {
    for (const auto& var : vars) {
        registerVar(var);
    }
}

void Registry::registerFunctions(const std::vector<FunctionInfo>& functions) {
    for (const auto& function : functions) {
        registerFunction(function);
    }
}

// 查询方法
bool Registry::hasElement(const std::string& name) const {
    return elements_.find(name) != elements_.end();
}

bool Registry::hasStyle(const std::string& name) const {
    return styles_.find(name) != styles_.end();
}

bool Registry::hasVar(const std::string& name) const {
    return vars_.find(name) != vars_.end();
}

bool Registry::hasFunction(const std::string& name) const {
    return functions_.find(name) != functions_.end();
}

// 获取信息
const Registry::ElementInfo* Registry::getElement(const std::string& name) const {
    auto it = elements_.find(name);
    return it != elements_.end() ? &it->second : nullptr;
}

const Registry::StyleInfo* Registry::getStyle(const std::string& name) const {
    auto it = styles_.find(name);
    return it != styles_.end() ? &it->second : nullptr;
}

const Registry::VarInfo* Registry::getVar(const std::string& name) const {
    auto it = vars_.find(name);
    return it != vars_.end() ? &it->second : nullptr;
}

const Registry::FunctionInfo* Registry::getFunction(const std::string& name) const {
    auto it = functions_.find(name);
    return it != functions_.end() ? &it->second : nullptr;
}

// 获取列表
std::vector<std::string> Registry::getAllElements() const {
    std::vector<std::string> result;
    result.reserve(elements_.size());
    for (const auto& [name, info] : elements_) {
        result.push_back(name);
    }
    return result;
}

std::vector<std::string> Registry::getElementsByCategory(const std::string& category) const {
    std::vector<std::string> result;
    auto it = elementsByCategory_.find(category);
    if (it != elementsByCategory_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::vector<std::string> Registry::getAllStyles() const {
    std::vector<std::string> result;
    result.reserve(styles_.size());
    for (const auto& [name, info] : styles_) {
        result.push_back(name);
    }
    return result;
}

std::vector<std::string> Registry::getStylesByCategory(const std::string& category) const {
    std::vector<std::string> result;
    auto it = stylesByCategory_.find(category);
    if (it != stylesByCategory_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::vector<std::string> Registry::getAllVars() const {
    std::vector<std::string> result;
    result.reserve(vars_.size());
    for (const auto& [name, info] : vars_) {
        result.push_back(name);
    }
    return result;
}

std::vector<std::string> Registry::getVarsByType(const std::string& type) const {
    std::vector<std::string> result;
    auto it = varsByType_.find(type);
    if (it != varsByType_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::vector<std::string> Registry::getAllFunctions() const {
    std::vector<std::string> result;
    result.reserve(functions_.size());
    for (const auto& [name, info] : functions_) {
        result.push_back(name);
    }
    return result;
}

// 属性验证
bool Registry::isValidAttribute(const std::string& element, const std::string& attribute) const {
    auto elemInfo = getElement(element);
    if (!elemInfo) return false;
    
    // 检查是否在允许的属性列表中
    const auto& allowed = elemInfo->allowedAttributes;
    return std::find(allowed.begin(), allowed.end(), attribute) != allowed.end();
}

bool Registry::isRequiredAttribute(const std::string& element, const std::string& attribute) const {
    auto elemInfo = getElement(element);
    if (!elemInfo) return false;
    
    const auto& required = elemInfo->requiredAttributes;
    return std::find(required.begin(), required.end(), attribute) != required.end();
}

std::vector<std::string> Registry::getMissingRequiredAttributes(
    const std::string& element, 
    const std::vector<std::string>& providedAttributes) const {
    
    std::vector<std::string> missing;
    auto elemInfo = getElement(element);
    if (!elemInfo) return missing;
    
    for (const auto& required : elemInfo->requiredAttributes) {
        if (std::find(providedAttributes.begin(), providedAttributes.end(), required) == providedAttributes.end()) {
            missing.push_back(required);
        }
    }
    
    return missing;
}

// 清理方法
void Registry::clear() {
    clearElements();
    clearStyles();
    clearVars();
    clearFunctions();
}

void Registry::clearElements() {
    elements_.clear();
    elementsByCategory_.clear();
}

void Registry::clearStyles() {
    styles_.clear();
    stylesByCategory_.clear();
}

void Registry::clearVars() {
    vars_.clear();
    varsByType_.clear();
}

void Registry::clearFunctions() {
    functions_.clear();
}

// 初始化默认值
void Registry::initializeDefaults() {
    // 注册HTML元素
    registerElements({
        // 结构元素
        {"div", "structure", {"class", "id", "style"}, {}, false, false, "Generic container"},
        {"span", "structure", {"class", "id", "style"}, {}, false, false, "Inline container"},
        {"p", "structure", {"class", "id", "style"}, {}, false, false, "Paragraph"},
        {"section", "structure", {"class", "id", "style"}, {}, false, false, "Document section"},
        {"article", "structure", {"class", "id", "style"}, {}, false, false, "Article content"},
        {"header", "structure", {"class", "id", "style"}, {}, false, false, "Header section"},
        {"footer", "structure", {"class", "id", "style"}, {}, false, false, "Footer section"},
        {"nav", "structure", {"class", "id", "style"}, {}, false, false, "Navigation section"},
        {"main", "structure", {"class", "id", "style"}, {}, false, false, "Main content"},
        {"aside", "structure", {"class", "id", "style"}, {}, false, false, "Sidebar content"},
        
        // 表单元素
        {"form", "form", {"action", "method", "class", "id"}, {}, false, false, "Form container"},
        {"input", "form", {"type", "name", "value", "placeholder", "required", "class", "id"}, {}, true, false, "Input field"},
        {"button", "form", {"type", "name", "value", "class", "id"}, {}, false, false, "Button element"},
        {"select", "form", {"name", "multiple", "required", "class", "id"}, {}, false, false, "Select dropdown"},
        {"option", "form", {"value", "selected"}, {}, false, false, "Select option"},
        {"textarea", "form", {"name", "rows", "cols", "placeholder", "required", "class", "id"}, {}, false, false, "Text area"},
        {"label", "form", {"for", "class", "id"}, {}, false, false, "Form label"},
        
        // 媒体元素
        {"img", "media", {"src", "alt", "width", "height", "class", "id"}, {"src", "alt"}, true, false, "Image"},
        {"video", "media", {"src", "controls", "autoplay", "loop", "muted", "width", "height", "class", "id"}, {}, false, false, "Video player"},
        {"audio", "media", {"src", "controls", "autoplay", "loop", "muted", "class", "id"}, {}, false, false, "Audio player"},
        
        // 语义元素
        {"h1", "semantic", {"class", "id", "style"}, {}, false, false, "Heading 1"},
        {"h2", "semantic", {"class", "id", "style"}, {}, false, false, "Heading 2"},
        {"h3", "semantic", {"class", "id", "style"}, {}, false, false, "Heading 3"},
        {"h4", "semantic", {"class", "id", "style"}, {}, false, false, "Heading 4"},
        {"h5", "semantic", {"class", "id", "style"}, {}, false, false, "Heading 5"},
        {"h6", "semantic", {"class", "id", "style"}, {}, false, false, "Heading 6"},
        {"a", "semantic", {"href", "target", "rel", "class", "id"}, {"href"}, false, false, "Hyperlink"},
        {"ul", "semantic", {"class", "id", "style"}, {}, false, false, "Unordered list"},
        {"ol", "semantic", {"class", "id", "style"}, {}, false, false, "Ordered list"},
        {"li", "semantic", {"class", "id", "style"}, {}, false, false, "List item"},
        {"table", "semantic", {"class", "id", "style"}, {}, false, false, "Table"},
        {"tr", "semantic", {"class", "id", "style"}, {}, false, false, "Table row"},
        {"td", "semantic", {"colspan", "rowspan", "class", "id"}, {}, false, false, "Table cell"},
        {"th", "semantic", {"colspan", "rowspan", "class", "id"}, {}, false, false, "Table header"}
    });
    
    // 注册预定义样式
    registerStyles({
        // 布局样式
        {"flex", "layout", {"display", "flex-direction", "justify-content", "align-items", "flex-wrap"}, "Flexbox layout"},
        {"grid", "layout", {"display", "grid-template-columns", "grid-template-rows", "gap"}, "Grid layout"},
        {"container", "layout", {"max-width", "margin", "padding"}, "Container wrapper"},
        
        // 排版样式
        {"text-center", "typography", {"text-align"}, "Center text alignment"},
        {"text-left", "typography", {"text-align"}, "Left text alignment"},
        {"text-right", "typography", {"text-align"}, "Right text alignment"},
        {"bold", "typography", {"font-weight"}, "Bold text"},
        {"italic", "typography", {"font-style"}, "Italic text"},
        
        // 颜色样式
        {"primary", "color", {"color", "background-color"}, "Primary color scheme"},
        {"secondary", "color", {"color", "background-color"}, "Secondary color scheme"},
        {"success", "color", {"color", "background-color"}, "Success color scheme"},
        {"warning", "color", {"color", "background-color"}, "Warning color scheme"},
        {"danger", "color", {"color", "background-color"}, "Danger color scheme"},
        
        // 动画样式
        {"fade-in", "animation", {"animation", "opacity"}, "Fade in animation"},
        {"slide-in", "animation", {"animation", "transform"}, "Slide in animation"},
        {"bounce", "animation", {"animation"}, "Bounce animation"}
    });
    
    // 注册预定义变量
    registerVars({
        // 颜色变量
        {"primary-color", "color", "#007bff", "Primary theme color"},
        {"secondary-color", "color", "#6c757d", "Secondary theme color"},
        {"success-color", "color", "#28a745", "Success state color"},
        {"warning-color", "color", "#ffc107", "Warning state color"},
        {"danger-color", "color", "#dc3545", "Danger state color"},
        
        // 尺寸变量
        {"base-font-size", "size", "16px", "Base font size"},
        {"h1-size", "size", "2.5rem", "H1 heading size"},
        {"h2-size", "size", "2rem", "H2 heading size"},
        {"h3-size", "size", "1.75rem", "H3 heading size"},
        
        // 间距变量
        {"spacing-xs", "spacing", "0.25rem", "Extra small spacing"},
        {"spacing-sm", "spacing", "0.5rem", "Small spacing"},
        {"spacing-md", "spacing", "1rem", "Medium spacing"},
        {"spacing-lg", "spacing", "1.5rem", "Large spacing"},
        {"spacing-xl", "spacing", "3rem", "Extra large spacing"},
        
        // 断点变量
        {"breakpoint-sm", "breakpoint", "576px", "Small device breakpoint"},
        {"breakpoint-md", "breakpoint", "768px", "Medium device breakpoint"},
        {"breakpoint-lg", "breakpoint", "992px", "Large device breakpoint"},
        {"breakpoint-xl", "breakpoint", "1200px", "Extra large device breakpoint"}
    });
    
    // 注册预定义函数
    registerFunctions({
        {"rgba", {"color", "alpha"}, "color", "Create RGBA color"},
        {"calc", {"expression"}, "value", "Calculate CSS value"},
        {"var", {"name", "fallback"}, "value", "Get CSS variable"},
        {"min", {"values..."}, "value", "Get minimum value"},
        {"max", {"values..."}, "value", "Get maximum value"},
        {"clamp", {"min", "preferred", "max"}, "value", "Clamp value between min and max"}
    });
}

} // namespace chtl