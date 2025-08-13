#include "CHTLConstraint.h"
#include "CHTLGenerator.h"
#include "CHTLNamespace.h"
#include <regex>
#include <sstream>
#include <algorithm>

namespace chtl {

// ConstraintTarget 实现
void ConstraintTarget::updateFullName() {
    if (qualifier.empty()) {
        fullName = name;
    } else {
        fullName = qualifier + " " + name;
    }
}

bool ConstraintTarget::matches(const ConstraintTarget& other) const {
    // 类型必须匹配
    if (type != other.type) {
        return false;
    }
    
    // 对于ALL类型，只需要类型匹配
    if (type == ConstraintTargetType::HTML_ALL ||
        type == ConstraintTargetType::CUSTOM_ALL ||
        type == ConstraintTargetType::TEMPLATE_ALL) {
        return true;
    }
    
    // 对于精确约束，名称必须匹配
    return name == other.name;
}

// ConstraintRule 实现
void ConstraintRule::addTarget(const ConstraintTarget& target) {
    targets.push_back(target);
}

bool ConstraintRule::isViolated(const ConstraintTarget& target) const {
    for (const auto& constraintTarget : targets) {
        if (constraintTarget.matches(target)) {
            return true;
        }
    }
    return false;
}

bool ConstraintRule::isViolated(const std::string& elementOrType) const {
    // 创建临时目标进行检查
    ConstraintTarget target;
    
    // 判断是HTML元素还是类型约束
    if (elementOrType == "@Html") {
        target.type = ConstraintTargetType::HTML_ALL;
    } else if (elementOrType == "[Custom]") {
        target.type = ConstraintTargetType::CUSTOM_ALL;
    } else if (elementOrType == "[Template]") {
        target.type = ConstraintTargetType::TEMPLATE_ALL;
    } else {
        // 假设是HTML元素
        target.type = ConstraintTargetType::HTML_ELEMENT;
        target.name = elementOrType;
    }
    
    return isViolated(target);
}

std::string ConstraintRule::getViolationMessage(const ConstraintTarget& target) const {
    std::stringstream ss;
    ss << "Constraint violation: ";
    
    if (isGlobal) {
        ss << "Global constraint in namespace '" << scope << "' ";
    } else {
        ss << "Constraint in element '" << scope << "' ";
    }
    
    ss << "prohibits use of ";
    
    switch (target.type) {
        case ConstraintTargetType::HTML_ELEMENT:
            ss << "HTML element '" << target.name << "'";
            break;
        case ConstraintTargetType::HTML_ALL:
            ss << "any HTML elements (@Html)";
            break;
        case ConstraintTargetType::CUSTOM_ALL:
            ss << "any custom definitions ([Custom])";
            break;
        case ConstraintTargetType::TEMPLATE_ALL:
            ss << "any templates ([Template])";
            break;
        default:
            ss << target.fullName;
    }
    
    if (!sourceFile.empty()) {
        ss << " (defined at " << sourceFile << ":" << lineNumber << ")";
    }
    
    return ss.str();
}

// ConstraintManager 实现
ConstraintManager::ConstraintManager(std::shared_ptr<CHTLContext> ctx) : context(ctx) {
    // 初始化根作用域
    constraintStack.push_back(std::vector<std::shared_ptr<ConstraintRule>>());
}

void ConstraintManager::addConstraint(std::shared_ptr<ConstraintRule> rule, const std::string& scope) {
    if (rule->isGlobalConstraint()) {
        addNamespaceConstraint(scope, rule);
    } else {
        addElementConstraint(scope, rule);
    }
}

void ConstraintManager::addElementConstraint(const std::string& elementPath, 
                                            std::shared_ptr<ConstraintRule> rule) {
    elementConstraints[elementPath].push_back(rule);
    
    // 添加到当前作用域
    if (!constraintStack.empty()) {
        constraintStack.back().push_back(rule);
    }
}

void ConstraintManager::addNamespaceConstraint(const std::string& namespacePath, 
                                              std::shared_ptr<ConstraintRule> rule) {
    namespaceConstraints[namespacePath].push_back(rule);
}

bool ConstraintManager::checkConstraint(const ConstraintTarget& target, 
                                       const std::string& currentScope) const {
    // 检查当前元素的约束
    auto elemIt = elementConstraints.find(currentScope);
    if (elemIt != elementConstraints.end()) {
        for (const auto& rule : elemIt->second) {
            if (rule->isViolated(target)) {
                context->reportError(rule->getViolationMessage(target));
                return false;
            }
        }
    }
    
    // 检查所有父元素的约束
    for (const auto& rules : constraintStack) {
        for (const auto& rule : rules) {
            if (rule->isViolated(target)) {
                context->reportError(rule->getViolationMessage(target));
                return false;
            }
        }
    }
    
    // 检查命名空间约束
    if (namespaceManager) {
        auto currentNs = namespaceManager->getCurrentNamespace();
        while (currentNs) {
            auto nsIt = namespaceConstraints.find(currentNs->getFullPath());
            if (nsIt != namespaceConstraints.end()) {
                for (const auto& rule : nsIt->second) {
                    if (rule->isViolated(target)) {
                        context->reportError(rule->getViolationMessage(target));
                        return false;
                    }
                }
            }
            currentNs = currentNs->getParent();
        }
    }
    
    return true;
}

bool ConstraintManager::checkConstraint(const std::string& elementOrType, 
                                       const std::string& currentScope) const {
    ConstraintTarget target;
    
    // 解析目标
    if (elementOrType.find("[Custom]") == 0) {
        target.type = ConstraintTargetType::CUSTOM_ALL;
        target.qualifier = "[Custom]";
    } else if (elementOrType.find("[Template]") == 0) {
        target.type = ConstraintTargetType::TEMPLATE_ALL;
        target.qualifier = "[Template]";
    } else if (elementOrType == "@Html") {
        target.type = ConstraintTargetType::HTML_ALL;
    } else {
        target.type = ConstraintTargetType::HTML_ELEMENT;
        target.name = elementOrType;
    }
    
    return checkConstraint(target, currentScope);
}

void ConstraintManager::enterScope(const std::string& scopeName) {
    // 继承父作用域的约束
    std::vector<std::shared_ptr<ConstraintRule>> newScope;
    if (!constraintStack.empty()) {
        newScope = constraintStack.back();
    }
    
    // 添加新作用域特定的约束
    auto it = elementConstraints.find(scopeName);
    if (it != elementConstraints.end()) {
        newScope.insert(newScope.end(), it->second.begin(), it->second.end());
    }
    
    constraintStack.push_back(newScope);
}

void ConstraintManager::exitScope() {
    if (constraintStack.size() > 1) {
        constraintStack.pop_back();
    }
}

std::vector<std::shared_ptr<ConstraintRule>> ConstraintManager::getCurrentConstraints() const {
    if (!constraintStack.empty()) {
        return constraintStack.back();
    }
    return {};
}

std::vector<std::string> ConstraintManager::getViolations(const ConstraintTarget& target, 
                                                         const std::string& currentScope) const {
    std::vector<std::string> violations;
    
    // 收集所有违反的约束信息
    auto rules = getCurrentConstraints();
    for (const auto& rule : rules) {
        if (rule->isViolated(target)) {
            violations.push_back(rule->getViolationMessage(target));
        }
    }
    
    return violations;
}

void ConstraintManager::clear() {
    elementConstraints.clear();
    namespaceConstraints.clear();
    constraintStack.clear();
    constraintStack.push_back(std::vector<std::shared_ptr<ConstraintRule>>());
}

// ConstraintProcessor 实现
void ConstraintProcessor::processExceptStatement(const std::string& statement, 
                                                const std::string& currentScope) {
    auto decl = parseExceptDeclaration(statement);
    
    if (!decl.isValid) {
        return;
    }
    
    // 创建约束规则
    auto rule = std::make_shared<ConstraintRule>(decl.type, currentScope);
    
    // 添加所有目标
    for (const auto& target : decl.targets) {
        rule->addTarget(target);
    }
    
    // 添加到管理器
    manager.addConstraint(rule, currentScope);
}

ConstraintProcessor::ExceptDeclaration ConstraintProcessor::parseExceptDeclaration(
    const std::string& declaration) {
    ExceptDeclaration decl;
    decl.isValid = false;
    
    // 提取except后的内容
    std::regex exceptRegex(R"(except\s+(.+)\s*;)");
    std::smatch match;
    
    if (!std::regex_match(declaration, match, exceptRegex)) {
        return decl;
    }
    
    std::string targetsStr = match[1];
    
    // 分割多个目标
    auto targetStrs = ConstraintHelper::splitExceptTargets(targetsStr);
    
    // 解析每个目标
    bool hasTypeConstraint = false;
    bool hasPreciseConstraint = false;
    
    for (const auto& targetStr : targetStrs) {
        auto target = parseConstraintTarget(targetStr);
        decl.targets.push_back(target);
        
        if (target.type == ConstraintTargetType::HTML_ALL ||
            target.type == ConstraintTargetType::CUSTOM_ALL ||
            target.type == ConstraintTargetType::TEMPLATE_ALL) {
            hasTypeConstraint = true;
        } else {
            hasPreciseConstraint = true;
        }
    }
    
    // 确定约束类型
    if (hasTypeConstraint && !hasPreciseConstraint) {
        decl.type = ConstraintType::TYPE;
    } else {
        decl.type = ConstraintType::PRECISE;
    }
    
    decl.isValid = !decl.targets.empty();
    return decl;
}

ConstraintTarget ConstraintProcessor::parseConstraintTarget(const std::string& targetStr) {
    ConstraintTarget target;
    
    // 去除空格
    std::string trimmed = targetStr;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);
    
    // 检查类型约束
    if (trimmed == "@Html") {
        target.type = ConstraintTargetType::HTML_ALL;
    } else if (trimmed == "[Custom]") {
        target.type = ConstraintTargetType::CUSTOM_ALL;
        target.qualifier = "[Custom]";
    } else if (trimmed == "[Template]") {
        target.type = ConstraintTargetType::TEMPLATE_ALL;
        target.qualifier = "[Template]";
    } else if (trimmed.find("[Custom] @Element") == 0) {
        target.type = ConstraintTargetType::CUSTOM_ELEMENT;
        target.qualifier = "[Custom]";
        target.name = trimmed.substr(17); // 跳过"[Custom] @Element "
        target.name.erase(0, target.name.find_first_not_of(" "));
    } else if (trimmed.find("[Custom] @Style") == 0) {
        target.type = ConstraintTargetType::CUSTOM_STYLE;
        target.qualifier = "[Custom]";
        target.name = trimmed.substr(15);
        target.name.erase(0, target.name.find_first_not_of(" "));
    } else if (trimmed.find("[Custom] @Var") == 0) {
        target.type = ConstraintTargetType::CUSTOM_VAR;
        target.qualifier = "[Custom]";
        target.name = trimmed.substr(13);
        target.name.erase(0, target.name.find_first_not_of(" "));
    } else if (trimmed.find("[Template] @Element") == 0) {
        target.type = ConstraintTargetType::TEMPLATE_ELEMENT;
        target.qualifier = "[Template]";
        target.name = trimmed.substr(19);
        target.name.erase(0, target.name.find_first_not_of(" "));
    } else if (trimmed.find("[Template] @Style") == 0) {
        target.type = ConstraintTargetType::TEMPLATE_STYLE;
        target.qualifier = "[Template]";
        target.name = trimmed.substr(17);
        target.name.erase(0, target.name.find_first_not_of(" "));
    } else if (trimmed.find("[Template] @Var") == 0) {
        target.type = ConstraintTargetType::TEMPLATE_VAR;
        target.qualifier = "[Template]";
        target.name = trimmed.substr(15);
        target.name.erase(0, target.name.find_first_not_of(" "));
    } else {
        // 默认为HTML元素
        target.type = ConstraintTargetType::HTML_ELEMENT;
        target.name = trimmed;
    }
    
    target.updateFullName();
    return target;
}

bool ConstraintProcessor::validateUsage(const std::string& usage, const std::string& currentScope) {
    auto target = parseConstraintTarget(usage);
    return manager.checkConstraint(target, currentScope);
}

// ConstraintChecker 实现
bool ConstraintChecker::canUseHtmlElement(const std::string& elementName) const {
    ConstraintTarget target(ConstraintTargetType::HTML_ELEMENT, elementName);
    return manager.checkConstraint(target, currentElementPath);
}

bool ConstraintChecker::canUseCustom(const std::string& customType, const std::string& customName) const {
    ConstraintTarget target;
    target.qualifier = "[Custom]";
    target.name = customName;
    
    if (customType == "@Element") {
        target.type = ConstraintTargetType::CUSTOM_ELEMENT;
    } else if (customType == "@Style") {
        target.type = ConstraintTargetType::CUSTOM_STYLE;
    } else if (customType == "@Var") {
        target.type = ConstraintTargetType::CUSTOM_VAR;
    }
    
    target.updateFullName();
    return manager.checkConstraint(target, currentElementPath);
}

bool ConstraintChecker::canUseTemplate(const std::string& templateType, const std::string& templateName) const {
    ConstraintTarget target;
    target.qualifier = "[Template]";
    target.name = templateName;
    
    if (templateType == "@Element") {
        target.type = ConstraintTargetType::TEMPLATE_ELEMENT;
    } else if (templateType == "@Style") {
        target.type = ConstraintTargetType::TEMPLATE_STYLE;
    } else if (templateType == "@Var") {
        target.type = ConstraintTargetType::TEMPLATE_VAR;
    }
    
    target.updateFullName();
    return manager.checkConstraint(target, currentElementPath);
}

bool ConstraintChecker::canDefineCustom(const std::string& customType) const {
    ConstraintTarget target(ConstraintTargetType::CUSTOM_ALL);
    return manager.checkConstraint(target, currentNamespace);
}

bool ConstraintChecker::canDefineTemplate(const std::string& templateType) const {
    ConstraintTarget target(ConstraintTargetType::TEMPLATE_ALL);
    return manager.checkConstraint(target, currentNamespace);
}

std::string ConstraintChecker::getConstraintError(const ConstraintTarget& target) const {
    auto violations = manager.getViolations(target, currentElementPath);
    if (!violations.empty()) {
        return violations[0];
    }
    return "";
}

// ConstraintHelper 实现
namespace ConstraintHelper {

ConstraintTargetType parseTargetType(const std::string& typeStr) {
    if (typeStr == "@Html") return ConstraintTargetType::HTML_ALL;
    if (typeStr == "[Custom]") return ConstraintTargetType::CUSTOM_ALL;
    if (typeStr == "[Template]") return ConstraintTargetType::TEMPLATE_ALL;
    
    // 其他情况根据上下文判断
    return ConstraintTargetType::HTML_ELEMENT;
}

bool isTypeConstraint(const std::string& constraint) {
    return constraint == "@Html" || 
           constraint == "[Custom]" || 
           constraint == "[Template]" ||
           constraint.find("[Template] @Var") != std::string::npos ||
           constraint.find("[Template] @Style") != std::string::npos ||
           constraint.find("[Template] @Element") != std::string::npos;
}

bool isPreciseConstraint(const std::string& constraint) {
    return !isTypeConstraint(constraint);
}

std::string normalizeTarget(const std::string& target) {
    std::string normalized = target;
    
    // 去除多余空格
    normalized.erase(0, normalized.find_first_not_of(" \t"));
    normalized.erase(normalized.find_last_not_of(" \t") + 1);
    
    // 规范化空格
    std::regex multiSpace("\\s+");
    normalized = std::regex_replace(normalized, multiSpace, " ");
    
    return normalized;
}

std::vector<std::string> splitExceptTargets(const std::string& exceptClause) {
    std::vector<std::string> targets;
    std::stringstream ss(exceptClause);
    std::string target;
    
    // 处理可能包含空格的目标（如[Custom] @Element Box）
    std::string currentTarget;
    bool inBrackets = false;
    
    while (ss >> target) {
        if (target[0] == '[') {
            inBrackets = true;
            currentTarget = target;
        } else if (inBrackets) {
            currentTarget += " " + target;
            if (target.find(';') != std::string::npos || 
                ss.peek() == ',' || ss.peek() == EOF) {
                // 去除末尾的逗号或分号
                if (currentTarget.back() == ',' || currentTarget.back() == ';') {
                    currentTarget.pop_back();
                }
                targets.push_back(normalizeTarget(currentTarget));
                inBrackets = false;
                currentTarget.clear();
                
                // 跳过逗号
                if (ss.peek() == ',') {
                    ss.get();
                }
            }
        } else {
            // 简单目标
            if (target.back() == ',') {
                target.pop_back();
            }
            targets.push_back(normalizeTarget(target));
        }
    }
    
    // 处理最后一个目标
    if (!currentTarget.empty()) {
        targets.push_back(normalizeTarget(currentTarget));
    }
    
    return targets;
}

std::string buildElementPath(const std::vector<std::string>& elements) {
    std::string path;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) {
            path += "/";
        }
        path += elements[i];
    }
    return path;
}

std::string constraintTypeToString(ConstraintType type) {
    switch (type) {
        case ConstraintType::PRECISE: return "Precise";
        case ConstraintType::TYPE: return "Type";
        case ConstraintType::GLOBAL: return "Global";
        default: return "Unknown";
    }
}

std::string targetTypeToString(ConstraintTargetType type) {
    switch (type) {
        case ConstraintTargetType::HTML_ELEMENT: return "HTML Element";
        case ConstraintTargetType::HTML_ALL: return "All HTML Elements";
        case ConstraintTargetType::CUSTOM_ELEMENT: return "Custom Element";
        case ConstraintTargetType::CUSTOM_STYLE: return "Custom Style";
        case ConstraintTargetType::CUSTOM_VAR: return "Custom Variable";
        case ConstraintTargetType::CUSTOM_ALL: return "All Custom";
        case ConstraintTargetType::TEMPLATE_ELEMENT: return "Template Element";
        case ConstraintTargetType::TEMPLATE_STYLE: return "Template Style";
        case ConstraintTargetType::TEMPLATE_VAR: return "Template Variable";
        case ConstraintTargetType::TEMPLATE_ALL: return "All Templates";
        default: return "Unknown";
    }
}

} // namespace ConstraintHelper

} // namespace chtl