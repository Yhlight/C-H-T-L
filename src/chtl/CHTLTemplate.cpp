#include "CHTLTemplate.h"
#include "CHTLGenerator.h"
#include <regex>
#include <algorithm>
#include <sstream>

namespace chtl {

// QualifiedNameResolver 实现
bool QualifiedNameResolver::parse(const std::string& fullName) {
    // 清空之前的解析结果
    prefix.clear();
    type.clear();
    name.clear();
    
    // 解析模式
    // 1. 完全限定名: [Template] @Element Box
    // 2. 部分限定名: @Element Box  
    // 3. 简单名称: Box
    
    std::regex fullQualifiedRegex(R"(\[(Template|Custom)\]\s+(@Style|@Element|@Var)\s+(\w+))");
    std::regex partialQualifiedRegex(R"((@Style|@Element|@Var)\s+(\w+))");
    std::regex simpleNameRegex(R"((\w+))");
    
    std::smatch match;
    
    if (std::regex_match(fullName, match, fullQualifiedRegex)) {
        prefix = match[1];
        type = match[2];
        name = match[3];
        nameType = QualifiedNameType::FULL;
        return true;
    } else if (std::regex_match(fullName, match, partialQualifiedRegex)) {
        type = match[1];
        name = match[2];
        nameType = QualifiedNameType::PARTIAL;
        return true;
    } else if (std::regex_match(fullName, match, simpleNameRegex)) {
        name = match[1];
        nameType = QualifiedNameType::SIMPLE;
        return true;
    }
    
    return false;
}

std::string QualifiedNameResolver::buildFullName() const {
    if (prefix.empty() || type.empty()) {
        return name;
    }
    return "[" + prefix + "] " + type + " " + name;
}

std::string QualifiedNameResolver::buildPartialName() const {
    if (type.empty()) {
        return name;
    }
    return type + " " + name;
}

bool QualifiedNameResolver::matches(const std::string& otherName) const {
    QualifiedNameResolver other;
    if (!other.parse(otherName)) {
        return false;
    }
    
    // 名称必须匹配
    if (name != other.name) {
        return false;
    }
    
    // 如果都有类型，类型必须匹配
    if (!type.empty() && !other.type.empty() && type != other.type) {
        return false;
    }
    
    // 如果都有前缀，前缀必须匹配
    if (!prefix.empty() && !other.prefix.empty() && prefix != other.prefix) {
        return false;
    }
    
    return true;
}

bool QualifiedNameResolver::matchesType(TemplateType templateType) const {
    if (type.empty()) {
        return true;  // 没有指定类型，匹配任意类型
    }
    
    switch (templateType) {
        case TemplateType::STYLE:
            return type == "@Style";
        case TemplateType::ELEMENT:
            return type == "@Element";
        case TemplateType::VAR:
            return type == "@Var";
    }
    
    return false;
}

// StyleTemplate 实现
void StyleTemplate::addStyle(const std::string& property, const std::string& value) {
    styles.push_back({property, value});
}

void StyleTemplate::inheritFrom(const std::string& templateName, bool isExplicit) {
    inheritedTemplates.push_back(templateName);
    if (isExplicit) {
        hasExplicitInherit = true;
    }
}

std::vector<std::pair<std::string, std::string>> StyleTemplate::getAllStyles(
    const std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templateMap) const {
    
    std::vector<std::pair<std::string, std::string>> allStyles;
    std::unordered_map<std::string, std::string> mergedStyles;
    
    // 首先添加继承的样式
    for (const auto& inheritedName : inheritedTemplates) {
        auto it = templateMap.find(inheritedName);
        if (it != templateMap.end()) {
            auto inheritedStyles = it->second->getAllStyles(templateMap);
            for (const auto& [prop, val] : inheritedStyles) {
                mergedStyles[prop] = val;
            }
        }
    }
    
    // 然后添加自己的样式（覆盖继承的）
    for (const auto& [prop, val] : styles) {
        mergedStyles[prop] = val;
    }
    
    // 转换为vector
    for (const auto& [prop, val] : mergedStyles) {
        allStyles.push_back({prop, val});
    }
    
    return allStyles;
}

void StyleTemplate::applyToElement(CHTLGenerator& generator) const {
    // 应用所有样式属性
    for (const auto& [property, value] : styles) {
        generator.generateInlineStyle(property, value);
    }
}

bool StyleTemplate::hasCircularInheritance(const std::string& checkName,
    const std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templateMap) const {
    
    if (name == checkName) {
        return true;
    }
    
    for (const auto& inheritedName : inheritedTemplates) {
        auto it = templateMap.find(inheritedName);
        if (it != templateMap.end()) {
            if (it->second->hasCircularInheritance(checkName, templateMap)) {
                return true;
            }
        }
    }
    
    return false;
}

// ElementTemplate 实现
void ElementTemplate::addElement(std::shared_ptr<ElementNode> element) {
    elements.push_back(element);
}

void ElementTemplate::inheritFrom(const std::string& templateName) {
    inheritedTemplates.push_back(templateName);
}

void ElementTemplate::expand(CHTLGenerator& generator) const {
    // 展开所有元素
    for (const auto& element : elements) {
        generator.generateElement(element->name, element->attributes);
        
        // 处理样式块
        if (element->hasStyleBlock && element->inlineStyles) {
            generator.beginStyleBlock();
            element->inlineStyles->applyToElement(generator);
            generator.endStyleBlock();
        }
        
        // 处理文本内容
        if (!element->textContent.empty()) {
            generator.beginTextBlock();
            generator.generateTextNode(element->textContent);
            generator.endTextBlock();
        }
        
        // 递归处理子元素
        // TODO: 实现子元素处理
        
        generator.closeElement();
    }
}

std::vector<std::shared_ptr<ElementTemplate::ElementNode>> ElementTemplate::getAllElements(
    const std::unordered_map<std::string, std::shared_ptr<ElementTemplate>>& templateMap) const {
    
    std::vector<std::shared_ptr<ElementNode>> allElements;
    
    // 首先添加继承的元素
    for (const auto& inheritedName : inheritedTemplates) {
        auto it = templateMap.find(inheritedName);
        if (it != templateMap.end()) {
            auto inheritedElements = it->second->getAllElements(templateMap);
            allElements.insert(allElements.end(), inheritedElements.begin(), inheritedElements.end());
        }
    }
    
    // 然后添加自己的元素
    allElements.insert(allElements.end(), elements.begin(), elements.end());
    
    return allElements;
}

// VarTemplate 实现
void VarTemplate::addVariable(const std::string& varName, const std::string& value) {
    variables[varName] = value;
}

void VarTemplate::inheritFrom(const std::string& templateName) {
    inheritedTemplates.push_back(templateName);
}

std::optional<std::string> VarTemplate::getVariable(const std::string& varName) const {
    auto it = variables.find(varName);
    if (it != variables.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::unordered_map<std::string, std::string> VarTemplate::getAllVariables(
    const std::unordered_map<std::string, std::shared_ptr<VarTemplate>>& templateMap) const {
    
    std::unordered_map<std::string, std::string> allVars;
    
    // 首先添加继承的变量
    for (const auto& inheritedName : inheritedTemplates) {
        auto it = templateMap.find(inheritedName);
        if (it != templateMap.end()) {
            auto inheritedVars = it->second->getAllVariables(templateMap);
            for (const auto& [var, val] : inheritedVars) {
                allVars[var] = val;
            }
        }
    }
    
    // 然后添加自己的变量（覆盖继承的）
    for (const auto& [var, val] : variables) {
        allVars[var] = val;
    }
    
    return allVars;
}

std::string VarTemplate::replaceVariables(const std::string& text) const {
    std::string result = text;
    
    // 查找并替换所有变量引用
    for (const auto& [varName, value] : variables) {
        std::string pattern = name + "(" + varName + ")";
        size_t pos = 0;
        while ((pos = result.find(pattern, pos)) != std::string::npos) {
            result.replace(pos, pattern.length(), value);
            pos += value.length();
        }
    }
    
    return result;
}

// TemplateManager 实现
bool TemplateManager::registerStyleTemplate(const std::string& name, std::shared_ptr<StyleTemplate> tmpl) {
    if (currentState != TemplateState::DEFINITION) {
        context->reportError("Cannot register template outside of definition state");
        return false;
    }
    
    styleTemplates[name] = tmpl;
    
    // 注册全缀名别名
    QualifiedNameResolver resolver;
    resolver.parse(name);
    
    registerAlias(resolver.buildPartialName(), name);
    registerAlias(resolver.buildFullName(), name);
    
    return true;
}

bool TemplateManager::registerElementTemplate(const std::string& name, std::shared_ptr<ElementTemplate> tmpl) {
    if (currentState != TemplateState::DEFINITION) {
        context->reportError("Cannot register template outside of definition state");
        return false;
    }
    
    elementTemplates[name] = tmpl;
    
    // 注册全缀名别名
    QualifiedNameResolver resolver;
    resolver.parse(name);
    
    registerAlias(resolver.buildPartialName(), name);
    registerAlias(resolver.buildFullName(), name);
    
    return true;
}

bool TemplateManager::registerVarTemplate(const std::string& name, std::shared_ptr<VarTemplate> tmpl) {
    if (currentState != TemplateState::DEFINITION) {
        context->reportError("Cannot register template outside of definition state");
        return false;
    }
    
    varTemplates[name] = tmpl;
    
    // 注册全缀名别名
    QualifiedNameResolver resolver;
    resolver.parse(name);
    
    registerAlias(resolver.buildPartialName(), name);
    registerAlias(resolver.buildFullName(), name);
    
    return true;
}

std::shared_ptr<StyleTemplate> TemplateManager::findStyleTemplate(const std::string& name) const {
    // 首先尝试直接查找
    auto it = styleTemplates.find(name);
    if (it != styleTemplates.end()) {
        return it->second;
    }
    
    // 尝试解析别名
    std::string resolved = resolveAlias(name);
    if (resolved != name) {
        it = styleTemplates.find(resolved);
        if (it != styleTemplates.end()) {
            return it->second;
        }
    }
    
    // 尝试全缀名匹配
    QualifiedNameResolver resolver;
    if (resolver.parse(name)) {
        for (const auto& [tmplName, tmpl] : styleTemplates) {
            QualifiedNameResolver tmplResolver;
            if (tmplResolver.parse(tmplName) && resolver.matches(tmplName)) {
                return tmpl;
            }
        }
    }
    
    return nullptr;
}

std::shared_ptr<ElementTemplate> TemplateManager::findElementTemplate(const std::string& name) const {
    // 类似findStyleTemplate的实现
    auto it = elementTemplates.find(name);
    if (it != elementTemplates.end()) {
        return it->second;
    }
    
    std::string resolved = resolveAlias(name);
    if (resolved != name) {
        it = elementTemplates.find(resolved);
        if (it != elementTemplates.end()) {
            return it->second;
        }
    }
    
    QualifiedNameResolver resolver;
    if (resolver.parse(name)) {
        for (const auto& [tmplName, tmpl] : elementTemplates) {
            QualifiedNameResolver tmplResolver;
            if (tmplResolver.parse(tmplName) && resolver.matches(tmplName)) {
                return tmpl;
            }
        }
    }
    
    return nullptr;
}

std::shared_ptr<VarTemplate> TemplateManager::findVarTemplate(const std::string& name) const {
    // 类似findStyleTemplate的实现
    auto it = varTemplates.find(name);
    if (it != varTemplates.end()) {
        return it->second;
    }
    
    std::string resolved = resolveAlias(name);
    if (resolved != name) {
        it = varTemplates.find(resolved);
        if (it != varTemplates.end()) {
            return it->second;
        }
    }
    
    QualifiedNameResolver resolver;
    if (resolver.parse(name)) {
        for (const auto& [tmplName, tmpl] : varTemplates) {
            QualifiedNameResolver tmplResolver;
            if (tmplResolver.parse(tmplName) && resolver.matches(tmplName)) {
                return tmpl;
            }
        }
    }
    
    return nullptr;
}

bool TemplateManager::useStyleTemplate(const std::string& name, CHTLGenerator& generator) {
    if (currentState != TemplateState::USE) {
        context->reportError("Cannot use template outside of use state");
        return false;
    }
    
    auto tmpl = findStyleTemplate(name);
    if (!tmpl) {
        context->reportError("Style template not found: " + name);
        return false;
    }
    
    // 获取所有样式（包括继承的）
    auto allStyles = tmpl->getAllStyles(styleTemplates);
    
    // 应用到当前元素
    for (const auto& [property, value] : allStyles) {
        generator.generateInlineStyle(property, value);
    }
    
    return true;
}

bool TemplateManager::useElementTemplate(const std::string& name, CHTLGenerator& generator) {
    if (currentState != TemplateState::USE) {
        context->reportError("Cannot use template outside of use state");
        return false;
    }
    
    auto tmpl = findElementTemplate(name);
    if (!tmpl) {
        context->reportError("Element template not found: " + name);
        return false;
    }
    
    // 展开模板
    tmpl->expand(generator);
    
    return true;
}

std::string TemplateManager::useVarTemplate(const std::string& templateName, const std::string& varName) {
    auto tmpl = findVarTemplate(templateName);
    if (!tmpl) {
        context->reportError("Var template not found: " + templateName);
        return "";
    }
    
    auto allVars = tmpl->getAllVariables(varTemplates);
    auto it = allVars.find(varName);
    if (it != allVars.end()) {
        return it->second;
    }
    
    context->reportError("Variable not found: " + varName + " in template " + templateName);
    return "";
}

void TemplateManager::registerAlias(const std::string& alias, const std::string& fullName) {
    if (!alias.empty() && alias != fullName) {
        nameAliases[alias] = fullName;
    }
}

std::string TemplateManager::resolveAlias(const std::string& name) const {
    auto it = nameAliases.find(name);
    if (it != nameAliases.end()) {
        return it->second;
    }
    return name;
}

// TemplateUseProcessor 实现
bool TemplateUseProcessor::processTemplateUse(const std::string& statement) {
    UseStatement use = parseUseStatement(statement);
    
    if (use.type == "@Style") {
        return manager.useStyleTemplate(use.name, generator);
    } else if (use.type == "@Element") {
        return manager.useElementTemplate(use.name, generator);
    } else if (use.type == "@Var") {
        // 变量组通常不直接使用，而是通过变量引用
        return false;
    }
    
    return false;
}

std::string TemplateUseProcessor::processVariableReference(const std::string& reference) {
    auto varRef = TemplateHelper::parseVarReference(reference);
    if (!varRef.isValid) {
        return reference;
    }
    
    return manager.useVarTemplate(varRef.templateName, varRef.varName);
}

TemplateUseProcessor::UseStatement TemplateUseProcessor::parseUseStatement(const std::string& statement) {
    UseStatement result;
    
    // 解析使用语句
    // 格式1: @Style TemplateName;
    // 格式2: [Template] @Style TemplateName;
    
    std::regex useRegex1(R"((@Style|@Element|@Var)\s+(\w+)\s*;?)");
    std::regex useRegex2(R"(\[(Template|Custom)\]\s+(@Style|@Element|@Var)\s+(\w+)\s*;?)");
    
    std::smatch match;
    
    if (std::regex_match(statement, match, useRegex2)) {
        result.prefix = match[1];
        result.type = match[2];
        result.name = match[3];
        result.hasPrefix = true;
    } else if (std::regex_match(statement, match, useRegex1)) {
        result.type = match[1];
        result.name = match[2];
        result.hasPrefix = false;
    }
    
    return result;
}

// TemplateHelper 实现
namespace TemplateHelper {

TemplateType parseTemplateType(const std::string& typeStr) {
    if (typeStr == "@Style") {
        return TemplateType::STYLE;
    } else if (typeStr == "@Element") {
        return TemplateType::ELEMENT;
    } else if (typeStr == "@Var") {
        return TemplateType::VAR;
    }
    
    throw std::invalid_argument("Invalid template type: " + typeStr);
}

std::string templateTypeToString(TemplateType type) {
    switch (type) {
        case TemplateType::STYLE:
            return "@Style";
        case TemplateType::ELEMENT:
            return "@Element";
        case TemplateType::VAR:
            return "@Var";
    }
    return "";
}

bool isValidTemplateName(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    
    // 模板名必须以字母或下划线开头
    if (!std::isalpha(name[0]) && name[0] != '_') {
        return false;
    }
    
    // 其余字符可以是字母、数字或下划线
    for (size_t i = 1; i < name.length(); ++i) {
        if (!std::isalnum(name[i]) && name[i] != '_') {
            return false;
        }
    }
    
    return true;
}

VarReference parseVarReference(const std::string& reference) {
    VarReference result;
    result.isValid = false;
    
    // 解析格式: TemplateName(varName)
    std::regex varRefRegex(R"((\w+)\((\w+)\))");
    std::smatch match;
    
    if (std::regex_match(reference, match, varRefRegex)) {
        result.templateName = match[1];
        result.varName = match[2];
        result.isValid = true;
    }
    
    return result;
}

} // namespace TemplateHelper

} // namespace chtl