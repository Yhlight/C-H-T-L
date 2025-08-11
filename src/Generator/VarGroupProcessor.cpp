#include "Generator/VarGroupProcessor.h"
#include "Node/Element.h"
#include <regex>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace chtl {

VarGroupProcessor::VarGroupProcessor() {}

VarGroupProcessor::~VarGroupProcessor() {}

void VarGroupProcessor::registerVarGroup(const std::shared_ptr<Custom>& custom) {
    if (!custom || custom->getCustomType() != Custom::CustomType::VAR) {
        return;
    }
    
    VarGroup group = parseVarGroup(custom);
    group.name = custom->getCustomName();
    
    // 处理继承
    auto children = custom->getChildren();
    for (const auto& child : children) {
        if (child->getType() == NodeType::ELEMENT) {
            auto elem = std::static_pointer_cast<Element>(child);
            if (elem->getTagName() == "inherit") {
                auto attrs = elem->getAttributes();
                if (attrs.find("name") != attrs.end()) {
                    inheritance_[group.name] = std::get<std::string>(attrs.at("name"));
                }
            }
        }
    }
    
    applyInheritance(group);
    varGroups_[group.name] = group;
}

void VarGroupProcessor::registerTemplateVarGroup(const std::shared_ptr<Template>& tmpl) {
    if (!tmpl || tmpl->getTemplateType() != Template::TemplateType::VAR) {
        return;
    }
    
    VarGroup group = parseVarGroup(tmpl);
    group.name = tmpl->getTemplateName();
    group.allowDynamic = true;  // 模板变量组允许动态变量
    
    varGroups_[group.name] = group;
}

VarGroupProcessor::VarGroup VarGroupProcessor::parseVarGroup(const std::shared_ptr<Node>& node) {
    VarGroup group;
    
    auto children = node->getChildren();
    for (const auto& child : children) {
        if (child->getType() == NodeType::ELEMENT) {
            auto elem = std::static_pointer_cast<Element>(child);
            std::string varName = elem->getTagName();
            
            // 跳过特殊元素
            if (varName == "inherit" || varName == "reference" || varName == "_except") {
                continue;
            }
            
            VarValue varValue;
            
            // 获取属性
            auto attrs = elem->getAttributes();
            
            // 获取类型
            if (attrs.find("type") != attrs.end()) {
                varValue.type = std::get<std::string>(attrs.at("type"));
            } else {
                // 自动推断类型
                varValue.type = "string";
            }
            
            // 获取值
            if (attrs.find("value") != attrs.end()) {
                varValue.value = std::get<std::string>(attrs.at("value"));
            } else if (!elem->getChildren().empty()) {
                // 从子节点文本获取值
                for (const auto& textChild : elem->getChildren()) {
                    if (textChild->getType() == NodeType::TEXT) {
                        varValue.value = textChild->getTagName();
                        break;
                    }
                }
            }
            
            // 获取默认值
            if (attrs.find("default") != attrs.end()) {
                group.defaults[varName] = std::get<std::string>(attrs.at("default"));
            }
            
            group.variables[varName] = varValue;
        }
    }
    
    return group;
}

std::string VarGroupProcessor::processVarCall(const std::string& varGroupName,
                                             const std::unordered_map<std::string, std::string>& args) {
    auto it = varGroups_.find(varGroupName);
    if (it == varGroups_.end()) {
        return "/* Var group '" + varGroupName + "' not found */";
    }
    
    const VarGroup& group = it->second;
    std::stringstream result;
    
    // 处理每个参数
    for (const auto& [argName, argValue] : args) {
        auto varIt = group.variables.find(argName);
        
        if (varIt != group.variables.end()) {
            // 找到变量
            const VarValue& var = varIt->second;
            
            if (var.isComputed && var.computeFunc) {
                // 计算变量
                result << var.computeFunc() << " ";
            } else {
                // 使用提供的值或默认值
                std::string value = argValue.empty() ? var.value : argValue;
                
                // 验证值
                if (validateVarValue(var.type, value)) {
                    result << value << " ";
                } else {
                    result << "/* Invalid value for " << argName << " */ ";
                }
            }
        } else if (group.allowDynamic) {
            // 动态变量
            result << argValue << " ";
        } else {
            // 变量不存在
            result << "/* Variable '" << argName << "' not found in " << varGroupName << " */ ";
        }
    }
    
    return result.str();
}

std::string VarGroupProcessor::getVarValue(const std::string& varGroupName,
                                          const std::string& varName,
                                          const std::string& fallback) {
    // 检查全局覆盖
    std::string key = varGroupName + "." + varName;
    auto overrideIt = globalOverrides_.find(key);
    if (overrideIt != globalOverrides_.end()) {
        return overrideIt->second;
    }
    
    // 查找变量组
    auto groupIt = varGroups_.find(varGroupName);
    if (groupIt == varGroups_.end()) {
        return fallback;
    }
    
    const VarGroup& group = groupIt->second;
    
    // 查找变量
    auto varIt = group.variables.find(varName);
    if (varIt == group.variables.end()) {
        // 检查默认值
        auto defaultIt = group.defaults.find(varName);
        if (defaultIt != group.defaults.end()) {
            return defaultIt->second;
        }
        return fallback;
    }
    
    const VarValue& var = varIt->second;
    
    if (var.isComputed && var.computeFunc) {
        return var.computeFunc();
    }
    
    return var.value.empty() ? fallback : var.value;
}

std::string VarGroupProcessor::processCSSVariables(const std::string& css) {
    std::string result = css;
    
    // 处理函数调用形式：VarGroupName(varName)
    std::regex funcCallRegex(R"((\w+)\s*\(\s*(\w+)(?:\s*=\s*([^)]+))?\s*\))");
    
    result = std::regex_replace(result, funcCallRegex,
        [this](const std::smatch& match) -> std::string {
            std::string groupName = match[1];
            std::string varName = match[2];
            std::string overrideValue = match[3];
            
            if (!hasVarGroup(groupName)) {
                // 不是变量组，保持原样
                return match[0];
            }
            
            if (!overrideValue.empty()) {
                // 有覆盖值
                std::unordered_map<std::string, std::string> args;
                args[varName] = overrideValue;
                return processVarCall(groupName, args);
            } else {
                // 使用默认值
                return getVarValue(groupName, varName, match[0]);
            }
        });
    
    // 处理 CSS 变量形式：var(--chtl-groupName-varName)
    std::regex cssVarRegex(R"(var\(--chtl-(\w+)-(\w+)(?:,\s*([^)]+))?\))");
    
    result = std::regex_replace(result, cssVarRegex,
        [this](const std::smatch& match) -> std::string {
            std::string groupName = match[1];
            std::string varName = match[2];
            std::string fallback = match[3];
            
            return getVarValue(groupName, varName, fallback.empty() ? match[0] : fallback);
        });
    
    return result;
}

void VarGroupProcessor::registerComputedVar(const std::string& varGroupName,
                                           const std::string& varName,
                                           std::function<std::string()> computeFunc) {
    auto it = varGroups_.find(varGroupName);
    if (it != varGroups_.end()) {
        VarValue var;
        var.isComputed = true;
        var.computeFunc = computeFunc;
        it->second.variables[varName] = var;
    }
}

std::string VarGroupProcessor::generateCSSVarDeclarations(const std::string& varGroupName,
                                                         const std::string& prefix) {
    auto it = varGroups_.find(varGroupName);
    if (it == varGroups_.end()) {
        return "";
    }
    
    const VarGroup& group = it->second;
    std::stringstream css;
    
    css << ":root {\n";
    
    for (const auto& [varName, varValue] : group.variables) {
        std::string cssVarName = prefix + varGroupName + "-" + varName;
        std::string value;
        
        if (varValue.isComputed && varValue.computeFunc) {
            value = varValue.computeFunc();
        } else {
            value = varValue.value;
        }
        
        if (!value.empty()) {
            css << "  " << cssVarName << ": " << value << ";\n";
        }
    }
    
    css << "}\n";
    
    return css.str();
}

bool VarGroupProcessor::validateVarValue(const std::string& type, const std::string& value) {
    if (type == "color") {
        // 验证颜色值
        std::regex colorRegex(R"(^(#[0-9a-fA-F]{3,8}|rgb\(|rgba\(|hsl\(|hsla\(|[a-zA-Z]+).*$)");
        return std::regex_match(value, colorRegex);
    } else if (type == "size" || type == "length") {
        // 验证尺寸值
        std::regex sizeRegex(R"(^-?\d*\.?\d+(px|em|rem|%|vh|vw|vmin|vmax|ch|ex|cm|mm|in|pt|pc)?$)");
        return std::regex_match(value, sizeRegex);
    } else if (type == "number") {
        // 验证数字
        std::regex numberRegex(R"(^-?\d*\.?\d+$)");
        return std::regex_match(value, numberRegex);
    } else if (type == "url") {
        // 验证URL
        return value.find("url(") == 0 || value.find("http") == 0 || value.find("/") == 0;
    }
    
    // 默认接受所有字符串值
    return true;
}

std::vector<std::string> VarGroupProcessor::getVarGroupNames() const {
    std::vector<std::string> names;
    for (const auto& [name, _] : varGroups_) {
        names.push_back(name);
    }
    return names;
}

bool VarGroupProcessor::hasVarGroup(const std::string& name) const {
    return varGroups_.find(name) != varGroups_.end();
}

std::string VarGroupProcessor::exportVarGroup(const std::string& varGroupName) const {
    auto it = varGroups_.find(varGroupName);
    if (it == varGroups_.end()) {
        return "";
    }
    
    const VarGroup& group = it->second;
    std::stringstream export_str;
    
    export_str << "[Template] @Var " << varGroupName << " {\n";
    
    for (const auto& [varName, varValue] : group.variables) {
        export_str << "  " << varName;
        
        if (!varValue.type.empty() && varValue.type != "string") {
            export_str << " type=\"" << varValue.type << "\"";
        }
        
        if (!varValue.value.empty()) {
            export_str << " {\n    " << varValue.value << "\n  }\n";
        } else {
            export_str << " {}\n";
        }
    }
    
    export_str << "}\n";
    
    return export_str.str();
}

void VarGroupProcessor::applyInheritance(VarGroup& group) {
    auto inheritIt = inheritance_.find(group.name);
    if (inheritIt == inheritance_.end()) {
        return;
    }
    
    // 查找父变量组
    auto parentIt = varGroups_.find(inheritIt->second);
    if (parentIt == varGroups_.end()) {
        return;
    }
    
    const VarGroup& parent = parentIt->second;
    
    // 继承变量（不覆盖已存在的）
    for (const auto& [varName, varValue] : parent.variables) {
        if (group.variables.find(varName) == group.variables.end()) {
            group.variables[varName] = varValue;
        }
    }
    
    // 继承默认值
    for (const auto& [varName, defaultValue] : parent.defaults) {
        if (group.defaults.find(varName) == group.defaults.end()) {
            group.defaults[varName] = defaultValue;
        }
    }
    
    // 继承动态变量设置
    if (!group.allowDynamic) {
        group.allowDynamic = parent.allowDynamic;
    }
}

std::pair<std::string, std::unordered_map<std::string, std::string>>
VarGroupProcessor::parseFunctionCall(const std::string& expr) {
    std::string groupName;
    std::unordered_map<std::string, std::string> args;
    
    // 解析函数调用：GroupName(arg1=val1, arg2=val2)
    size_t parenPos = expr.find('(');
    if (parenPos == std::string::npos) {
        return {expr, args};
    }
    
    groupName = expr.substr(0, parenPos);
    
    // 去除空格
    groupName.erase(std::remove_if(groupName.begin(), groupName.end(), ::isspace), groupName.end());
    
    // 解析参数
    size_t closeParenPos = expr.rfind(')');
    if (closeParenPos != std::string::npos && closeParenPos > parenPos) {
        std::string argsStr = expr.substr(parenPos + 1, closeParenPos - parenPos - 1);
        
        // 分割参数
        std::istringstream argStream(argsStr);
        std::string arg;
        
        while (std::getline(argStream, arg, ',')) {
            size_t eqPos = arg.find('=');
            if (eqPos != std::string::npos) {
                std::string key = arg.substr(0, eqPos);
                std::string value = arg.substr(eqPos + 1);
                
                // 去除空格
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                args[key] = value;
            }
        }
    }
    
    return {groupName, args};
}

std::string VarGroupProcessor::evaluateExpression(const std::string& expr,
                                                 const std::unordered_map<std::string, std::string>& context) {
    // 简单的表达式求值（支持基本运算）
    std::string result = expr;
    
    // 替换变量
    for (const auto& [key, value] : context) {
        std::regex varRegex("\\b" + key + "\\b");
        result = std::regex_replace(result, varRegex, value);
    }
    
    // TODO: 实现更复杂的表达式求值
    
    return result;
}

std::string VarGroupProcessor::convertValue(const std::string& value,
                                           const std::string& fromType,
                                           const std::string& toType) {
    if (fromType == toType) {
        return value;
    }
    
    // 实现一些基本的类型转换
    if (fromType == "number" && toType == "size") {
        return value + "px";
    }
    
    if (fromType == "color" && toType == "string") {
        return value;
    }
    
    // TODO: 实现更多类型转换
    
    return value;
}

} // namespace chtl