#include "Utils/ConstraintValidator.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include "Node/Namespace.h"
#include <sstream>
#include <algorithm>

namespace chtl {

ConstraintValidator::ConstraintValidator(std::shared_ptr<BasicContext> context)
    : context_(context) {
}

bool ConstraintValidator::validateConstraints(std::shared_ptr<Node> ast) {
    if (!ast) return true;
    
    clear();
    
    // 开始递归验证
    std::unordered_set<std::string> globalConstraints;
    validateRecursive(ast, "", globalConstraints);
    
    return violations_.empty();
}

bool ConstraintValidator::validateNode(std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
    if (!node || !parent) return true;
    
    // 获取父节点的约束
    auto constraints = parent->getConstraints();
    
    for (const auto& constraint : constraints) {
        if (matchesConstraint(node, constraint)) {
            // 违反了约束 - except表示"禁止"，所以匹配就是违反
            ConstraintInfo violation;
            violation.type = parseConstraintType(constraint);
            violation.value = constraint;
            violation.scope = getNodePath(parent);
            violation.isViolated = true;
            violation.violations.push_back("Node '" + node->getTagName() + 
                "' violates except constraint '" + constraint + "'");
            
            violations_.push_back(violation);
            
            // 报告错误
            if (context_) {
                context_->addError("Constraint violation: " + node->getTagName() + 
                    " is not allowed in " + parent->getTagName() + 
                    " (except constraint: '" + constraint + "')");
            }
            
            return false;
        }
    }
    
    return true;
}

void ConstraintValidator::registerConstraint(const std::string& scope, const std::string& constraint) {
    constraints_[scope].insert(constraint);
}

std::vector<ConstraintInfo> ConstraintValidator::getViolations() const {
    return violations_;
}

void ConstraintValidator::clear() {
    constraints_.clear();
    violations_.clear();
    pathStack_.clear();
    namespaceConstraintStack_.clear();
}

ConstraintType ConstraintValidator::parseConstraintType(const std::string& constraint) {
    if (constraint.find("@Html") != std::string::npos ||
        constraint.find("[Custom]") != std::string::npos ||
        constraint.find("[Template]") != std::string::npos) {
        return ConstraintType::TYPE;
    }
    
    // 如果包含具体的自定义或模板名称
    if (constraint.find("[Custom] @") != std::string::npos ||
        constraint.find("[Template] @") != std::string::npos) {
        return ConstraintType::PRECISE;
    }
    
    // 默认为精确约束（HTML元素名）
    return ConstraintType::PRECISE;
}

bool ConstraintValidator::matchesConstraint(std::shared_ptr<Node> node, const std::string& constraint) {
    ConstraintType type = parseConstraintType(constraint);
    
    switch (type) {
        case ConstraintType::PRECISE:
            return matchesPreciseConstraint(node, constraint);
        case ConstraintType::TYPE:
            return matchesTypeConstraint(node, constraint);
        default:
            return false;
    }
}

bool ConstraintValidator::matchesPreciseConstraint(std::shared_ptr<Node> node, const std::string& constraint) {
    auto parts = parseConstraintParts(constraint);
    
    // 检查HTML元素
    if (parts.category.empty() || (!parts.category.empty() && parts.category[0] != '[')) {
        // 这是一个HTML元素约束
        if (node->getType() == NodeType::ELEMENT) {
            // 对于简单的HTML元素名，直接比较
            std::string elementName = constraint;
            // 如果constraint中有空格（如来自parseConstraintParts的category），使用category
            if (!parts.category.empty() && parts.category[0] != '[') {
                elementName = parts.category;
            }
            return node->getTagName() == elementName;
        }
        return false;
    }
    
    // 检查[Custom] @Element Box这样的精确约束
    if (parts.category == "[Custom]" && node->getType() == NodeType::CUSTOM) {
        auto custom = std::static_pointer_cast<Custom>(node);
        
        // 检查类型
        if (!parts.type.empty()) {
            Custom::CustomType expectedType;
            if (parts.type == "@Element") expectedType = Custom::CustomType::ELEMENT;
            else if (parts.type == "@Style") expectedType = Custom::CustomType::STYLE;
            else if (parts.type == "@Var") expectedType = Custom::CustomType::VAR;
            else return false;
            
            if (custom->getCustomType() != expectedType) return false;
        }
        
        // 检查名称
        if (!parts.name.empty() && custom->getCustomName() != parts.name) {
            return false;
        }
        
        return true;
    }
    
    // 检查[Template]约束
    if (parts.category == "[Template]" && node->getType() == NodeType::TEMPLATE) {
        auto tmpl = std::static_pointer_cast<Template>(node);
        
        // 检查类型
        if (!parts.type.empty()) {
            Template::TemplateType expectedType;
            if (parts.type == "@Element") expectedType = Template::TemplateType::ELEMENT;
            else if (parts.type == "@Style") expectedType = Template::TemplateType::STYLE;
            else if (parts.type == "@Var") expectedType = Template::TemplateType::VAR;
            else return false;
            
            if (tmpl->getTemplateType() != expectedType) return false;
        }
        
        // 检查名称
        if (!parts.name.empty() && tmpl->getTemplateName() != parts.name) {
            return false;
        }
        
        return true;
    }
    
    return false;
}

bool ConstraintValidator::matchesTypeConstraint(std::shared_ptr<Node> node, const std::string& constraint) {
    // @Html - 禁止所有HTML元素
    if (constraint == "@Html") {
        return node->getType() == NodeType::ELEMENT && 
               node->getTagName() != "reference" &&  // 排除引用节点
               node->getTagName()[0] != '[';         // 排除特殊节点
    }
    
    // [Custom] - 禁止所有自定义元素
    if (constraint == "[Custom]") {
        return node->getType() == NodeType::CUSTOM;
    }
    
    // [Template] - 禁止所有模板
    if (constraint == "[Template]") {
        return node->getType() == NodeType::TEMPLATE;
    }
    
    // [Template] @Var等具体类型约束
    auto parts = parseConstraintParts(constraint);
    
    if (parts.category == "[Template]" && !parts.type.empty()) {
        if (node->getType() != NodeType::TEMPLATE) return false;
        
        auto tmpl = std::static_pointer_cast<Template>(node);
        Template::TemplateType expectedType;
        
        if (parts.type == "@Var") expectedType = Template::TemplateType::VAR;
        else if (parts.type == "@Style") expectedType = Template::TemplateType::STYLE;
        else if (parts.type == "@Element") expectedType = Template::TemplateType::ELEMENT;
        else return false;
        
        return tmpl->getTemplateType() == expectedType;
    }
    
    return false;
}

std::string ConstraintValidator::getNodePath(std::shared_ptr<Node> node) {
    // 简化实现，返回节点标签名
    return node->getTagName();
}

void ConstraintValidator::validateRecursive(std::shared_ptr<Node> node, 
                                          const std::string& currentPath,
                                          const std::unordered_set<std::string>& activeConstraints) {
    if (!node) return;
    
    // 构建当前路径
    std::string nodePath = currentPath.empty() ? node->getTagName() : 
                          currentPath + "/" + node->getTagName();
    pathStack_.push_back(nodePath);
    
    // 收集当前节点的约束
    std::unordered_set<std::string> currentConstraints = activeConstraints;
    for (const auto& constraint : node->getConstraints()) {
        currentConstraints.insert(constraint);
        registerConstraint(nodePath, constraint);
    }
    
    // 如果是命名空间，更新全局约束
    if (node->getType() == NodeType::NAMESPACE) {
        namespaceConstraintStack_.push_back(currentConstraints);
    }
    
    // 验证子节点
    for (const auto& child : node->getChildren()) {
        // 检查子节点是否违反当前约束
        for (const auto& constraint : currentConstraints) {

            
            if (matchesConstraint(child, constraint)) {
                ConstraintInfo violation;
                violation.type = parseConstraintType(constraint);
                violation.value = constraint;
                violation.scope = nodePath;
                violation.isViolated = true;
                violation.violations.push_back("Node '" + child->getTagName() + 
                    "' at '" + nodePath + "' violates except constraint '" + constraint + "'");
                
                violations_.push_back(violation);
                
                if (context_) {
                    context_->addError("Constraint violation in " + nodePath + ": " + 
                        child->getTagName() + " is not allowed (violates '" + constraint + "')");
                }
            }
        }
        
        // 递归验证
        validateRecursive(child, nodePath, currentConstraints);
    }
    
    // 退出命名空间时恢复约束栈
    if (node->getType() == NodeType::NAMESPACE && !namespaceConstraintStack_.empty()) {
        namespaceConstraintStack_.pop_back();
    }
    
    pathStack_.pop_back();
}

ConstraintValidator::ConstraintParts ConstraintValidator::parseConstraintParts(const std::string& constraint) {
    ConstraintParts parts;
    
    std::istringstream iss(constraint);
    std::string token;
    
    while (iss >> token) {
        if (token == "[Custom]" || token == "[Template]") {
            parts.category = token;
        } else if (token.find("@") == 0) {
            parts.type = token;
        } else if (!parts.category.empty()) {
            // 这是名称部分
            parts.name = token;
        } else {
            // 这是HTML元素名
            parts.category = token;
        }
    }
    
    return parts;
}

} // namespace chtl