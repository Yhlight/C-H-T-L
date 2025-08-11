#include "Generator/Generator.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Custom.h"
#include "Node/Operate.h"
#include "Node/Template.h"
// #include "Node/Reference.h" // Not implemented yet
#include "Node/Origin.h" // Added for Origin node
#include "Runtime/ChtlJsRuntime.h"
#include <regex>
#include <algorithm>
#include <set>
#include <variant>
#include <tuple>


namespace chtl {

GeneratorResult WebGenerator::generate(const std::shared_ptr<Node>& ast) {
    // 调用基类生成方法
    Generator::generate(ast);
    
    // 生成完整的HTML文档
    generateHTMLDocument();
    
    // 注入运行时代码
    injectRuntimeCode();
    
    return result_;
}

std::string WebGenerator::generateHTMLDocument() {
    // 如果已经有html标签，不需要包装
    if (result_.html.find("<html") != std::string::npos) {
        return result_.html;
    }
    
    std::stringstream doc;
    
    // DOCTYPE
    doc << "<!DOCTYPE html>\n";
    doc << "<html lang=\"zh-CN\">\n";
    doc << "<head>\n";
    doc << "  <meta charset=\"UTF-8\">\n";
    doc << "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    doc << "  <title>CHTL Generated Page</title>\n";
    
    // 内联或外部样式
    if (!result_.css.empty()) {
        if (options_.inlineStyles) {
            doc << "  <style>\n";
            doc << result_.css;
            doc << "  </style>\n";
        } else {
            // 生成外部CSS文件引用
            // TODO: Handle external styles
            // result_.externalStyles.push_back("styles.css");
            doc << "  <link rel=\"stylesheet\" href=\"styles.css\">\n";
        }
    }
    
    doc << "</head>\n";
    doc << "<body>\n";
    
    // 主体内容
    doc << result_.html;
    
    // 脚本
    if (!result_.js.empty()) {
        if (options_.inlineScripts) {
            doc << "  <script>\n";
            doc << result_.js;
            doc << "  </script>\n";
        } else {
            // 生成外部JS文件引用
            // TODO: Handle external scripts
            // result_.externalScripts.push_back("app.js");
            doc << "  <script src=\"app.js\"></script>\n";
        }
    }
    
    doc << "</body>\n";
    doc << "</html>\n";
    
    result_.html = doc.str();
    return result_.html;
}

void WebGenerator::injectRuntimeCode() {
    // 获取CHTL运行时代码
    std::string runtimeCode = jsRuntime_->generateRuntimeCode();
    
    if (!runtimeCode.empty()) {
        // 在用户代码之前注入运行时
        result_.js = runtimeCode + "\n" + result_.js;
    }
}

void WebGenerator::visit(const std::shared_ptr<Node>& node) {
    if (!node) return;
    
    // 检查父节点的约束
    auto parent = node->getParent();
    if (parent && !checkConstraints(node, parent.get())) {
        // 约束违反，跳过此节点
        result_.warnings.push_back("Constraint violation: " + node->toString() + " not allowed in parent");
        return;
    }
    
    // 调用基类的visit方法
    Generator::visit(node);
}

bool WebGenerator::checkConstraints(const std::shared_ptr<Node>& node, Node* parent) {
    if (!parent) return true;
    
    const auto& constraints = parent->getConstraints();
    if (constraints.empty()) return true;
    
    for (const auto& constraint : constraints) {
        if (matchesConstraint(node, constraint)) {
            // except表示"禁止"，所以匹配就是违反
            return false;
        }
    }
    
    return true;
}

bool WebGenerator::matchesConstraint(const std::shared_ptr<Node>& node, const std::string& constraint) {
    // HTML元素约束
    if (constraint == "@Html") {
        return node->getType() == NodeType::ELEMENT;
    }
    
    // [Custom]类型约束
    if (constraint == "[Custom]") {
        return node->getType() == NodeType::CUSTOM;
    }
    
    // [Template]类型约束
    if (constraint == "[Template]") {
        return node->getType() == NodeType::TEMPLATE;
    }
    
    // 具体类型约束，如 "[Template] @Var"
    if (constraint.find("[Template] @") == 0) {
        if (auto tmpl = std::dynamic_pointer_cast<Template>(node)) {
            std::string typeStr = constraint.substr(12); // 跳过 "[Template] @"
            if (typeStr == "Style" && tmpl->getTemplateType() == Template::TemplateType::STYLE) return true;
            if (typeStr == "Element" && tmpl->getTemplateType() == Template::TemplateType::ELEMENT) return true;
            if (typeStr == "Var" && tmpl->getTemplateType() == Template::TemplateType::VAR) return true;
        }
        return false;
    }
    
    // 具体类型约束，如 "[Custom] @Element Box"
    if (constraint.find("[Custom] @") == 0) {
        if (auto custom = std::dynamic_pointer_cast<Custom>(node)) {
            size_t atPos = constraint.find('@');
            size_t spacePos = constraint.find(' ', atPos);
            if (spacePos != std::string::npos) {
                // 有具体名称
                std::string name = constraint.substr(spacePos + 1);
                return custom->getCustomName() == name;
            } else {
                // 只有类型
                std::string typeStr = constraint.substr(atPos + 1);
                if (typeStr == "Style" && custom->getCustomType() == Custom::CustomType::STYLE) return true;
                if (typeStr == "Element" && custom->getCustomType() == Custom::CustomType::ELEMENT) return true;
                if (typeStr == "Var" && custom->getCustomType() == Custom::CustomType::VAR) return true;
            }
        }
        return false;
    }
    
    // 具体元素名约束（如 "span", "div"）
    if (node->getType() == NodeType::ELEMENT) {
        auto element = std::static_pointer_cast<Element>(node);
        return element->getTagName() == constraint;
    }
    
    // 引用约束（如 "@Element Box"）
    // TODO: Implement when REFERENCE node type is added
    /*
    if (node->getType() == NodeType::REFERENCE) {
        auto attrs = node->getAttributes();
        if (attrs.find("name") != attrs.end()) {
            // 需要从variant中提取字符串
            if (std::holds_alternative<std::string>(attrs.at("name"))) {
                std::string refName = std::get<std::string>(attrs.at("name"));
                return constraint.find(refName) != std::string::npos;
            }
        }
    }
    */
    
    return false;
}

void WebGenerator::visitElement(const std::shared_ptr<Element>& element) {
    const std::string& tag = element->getTagName();
    


    // 特殊处理引用节点
    if (tag == "reference") {

        processReference(element);
        return;
    }
    
        // 特殊处理文档根节点
    if (tag == "document") {
        // 只处理子节点，不生成 document 标签
        for (const auto& child : element->getChildren()) {
            visit(child);
        }
        return;
    }
    
    // 特殊处理 delete 节点（不生成 HTML）
    if (tag == "delete") {
        return;  // delete 节点不应该生成任何输出
    }
    
    // 生成开始标签
    htmlCollector_.append("<" + tag);
    
    // 添加ID（如果有局部脚本需要）
    std::string elementId;
    bool hasLocalScript = false;
    
    // 检查是否有局部script子节点
    for (const auto& child : element->getChildren()) {
        if (child->getType() == NodeType::SCRIPT) {
            auto script = std::static_pointer_cast<Script>(child);
            if (script->getScriptType() == Script::ScriptType::INLINE && script->isScoped()) {
                hasLocalScript = true;
                break;
            }
        }
    }
    
    // 处理属性
    auto attributes = element->getAttributes();
    
    if (hasLocalScript && attributes.find("id") == attributes.end()) {
        // 需要ID但没有，生成一个
        elementId = generateUniqueId("element");
        htmlCollector_.append(" id=\"" + elementId + "\"");
    } else if (attributes.find("id") != attributes.end()) {
        if (std::holds_alternative<std::string>(attributes.at("id"))) {
            elementId = std::get<std::string>(attributes.at("id"));
        }
    }
    
    // 输出所有属性
    for (const auto& [key, value] : attributes) {
        // 处理特殊属性
        if (key == "class") {
            // 处理类名数组
            std::string classValue;
            if (std::holds_alternative<std::string>(value)) {
                classValue = std::get<std::string>(value);
            }
            if (!currentScope_.empty() && options_.scopeStyles) {
                classValue = currentScope_ + " " + classValue;
            }
            htmlCollector_.append(" class=\"" + escape(classValue) + "\"");
        } else if (key == "style") {
            // 处理内联样式对象
            if (std::holds_alternative<std::string>(value)) {
                htmlCollector_.append(" style=\"" + escape(std::get<std::string>(value)) + "\"");
            }
        } else {
            // 普通属性
            if (std::holds_alternative<std::string>(value)) {
                htmlCollector_.append(" " + key + "=\"" + escape(std::get<std::string>(value)) + "\"");
            } else if (std::holds_alternative<int>(value)) {
                htmlCollector_.append(" " + key + "=\"" + std::to_string(std::get<int>(value)) + "\"");
            } else if (std::holds_alternative<double>(value)) {
                htmlCollector_.append(" " + key + "=\"" + std::to_string(std::get<double>(value)) + "\"");
            } else if (std::holds_alternative<bool>(value)) {
                htmlCollector_.append(" " + key + "=\"" + (std::get<bool>(value) ? "true" : "false") + "\"");
            }
        }
    }
    
    // 自闭合标签
    std::set<std::string> selfClosing = {
        "area", "base", "br", "col", "embed", "hr", "img", 
        "input", "link", "meta", "param", "source", "track", "wbr"
    };
    
    if (selfClosing.count(tag) > 0) {
        htmlCollector_.append(" />");
        return;
    }
    
    htmlCollector_.append(">");
    
    // 处理子节点
    for (const auto& child : element->getChildren()) {
        if (child->getType() == NodeType::SCRIPT) {
            auto script = std::static_pointer_cast<Script>(child);
            if (script->getScriptType() == Script::ScriptType::INLINE && script->isScoped()) {
                // 设置作用域ID
                script->setScope(elementId);
            }
        }
        visit(child);
    }
    
    // 结束标签
    htmlCollector_.append("</" + tag + ">");
}

void WebGenerator::visitCustom(const std::shared_ptr<Custom>& custom) {
    // Custom 节点通常是定义，不应该直接生成内容
    // 但如果是从引用克隆的实例，需要生成其子节点
    
    // 检查是否有名称 - 有名称的是定义
    if (!custom->getCustomName().empty()) {
        // 这是一个定义，不生成内容
        return;
    }
    
    // 没有名称，可能是克隆的实例，生成其子节点内容
    for (const auto& child : custom->getChildren()) {
        visit(child);
    }
}

std::shared_ptr<Node> WebGenerator::findComponentDefinition(const std::string& name, Custom::CustomType type) {
    std::string key;
    switch (type) {
        case Custom::CustomType::STYLE:
            key = "@Style " + name;
            break;
        case Custom::CustomType::ELEMENT:
            key = "@Element " + name;
            break;
        case Custom::CustomType::VAR:
            key = "@Var " + name;
            break;
    }
    
    // 先在Custom定义中查找
    auto it = customDefinitions_.find(key);
    if (it != customDefinitions_.end()) {
        return it->second;
    }
    
    // 再在Template定义中查找
    auto it2 = templateDefinitions_.find(key);
    if (it2 != templateDefinitions_.end()) {
        return it2->second;
    }
    
    return nullptr;
}

void WebGenerator::processCustomComponent(const std::shared_ptr<Custom>& instance, 
                                          const std::shared_ptr<Node>& definition) {
    // 克隆定义以避免修改原始定义
    auto workingCopy = definition->clone();
    
    // 应用实例特有的修改（删除、插入等）
    applyInstanceModifications(workingCopy, instance);
    
    // 生成最终内容
    if (instance->getCustomType() == Custom::CustomType::ELEMENT) {
        // 对于元素类型，遍历生成子节点
        for (const auto& child : workingCopy->getChildren()) {
            visit(child);
        }
    } else if (instance->getCustomType() == Custom::CustomType::STYLE) {
        // 对于样式类型，处理样式内容
        visitStyle(std::static_pointer_cast<Style>(workingCopy));
    }
}

void WebGenerator::applyInstanceModifications(std::shared_ptr<Node> target, 
                                              const std::shared_ptr<Custom>& instance) {
    // 收集删除目标
    std::set<std::string> deleteTargets;
    std::vector<std::shared_ptr<Node>> insertOperations;
    
    for (const auto& child : instance->getChildren()) {
        if (child->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(child);
            if (element->getTagName() == "delete") {
                // 提取删除目标
                auto attrs = element->getAttributes();
                if (attrs.find("target") != attrs.end() && 
                    std::holds_alternative<std::string>(attrs.at("target"))) {
                    deleteTargets.insert(std::get<std::string>(attrs.at("target")));
                }
            }
        } else if (child->getType() == NodeType::OPERATE) {
            auto op = std::static_pointer_cast<Operate>(child);
            if (op->getOperation() == Operate::OperationType::INSERT) {
                insertOperations.push_back(op);
            }
        }
    }
    
    // 执行删除操作
    for (const auto& deleteTarget : deleteTargets) {
        deleteFromNode(target, deleteTarget);
    }
    
    // 执行插入操作
    for (const auto& insertOp : insertOperations) {
        auto operate = std::static_pointer_cast<Operate>(insertOp);
        executeInsertOperation(target, operate);
    }
}

// 查找插入/删除目标节点
std::vector<std::shared_ptr<Node>>::iterator 
WebGenerator::findTargetNode(std::vector<std::shared_ptr<Node>>& children, 
                            const std::string& target, int& currentIndex) {
    // 解析目标字符串（复用 deleteFromNode 中的逻辑）
    bool isReference = false;
    bool isCustom = false;
    std::string refType;
    std::string refName;
    std::string tagName;
    int targetIndex = -1;
    
    size_t pos = 0;
    
    // 检查 [Custom] 或 [Template]
    if (target.find("[Custom]") == 0 || target.find("[Template]") == 0) {
        isCustom = true;
        pos = target.find(']') + 1;
        while (pos < target.length() && target[pos] == ' ') pos++;
    }
    
    // 检查 Custom 或 Template 关键字
    if (target.find("Custom ", pos) == pos) {
        isCustom = true;
        pos += 7;
    } else if (target.find("Template ", pos) == pos) {
        isCustom = true;
        pos += 9;
    }
    
    // 检查 @Element, @Style, @Var
    if (target.find("@Element ", pos) == pos) {
        isReference = true;
        refType = "@Element";
        pos += 9;
    } else if (target.find("@Style ", pos) == pos) {
        isReference = true;
        refType = "@Style";
        pos += 7;
    } else if (target.find("@Var ", pos) == pos) {
        isReference = true;
        refType = "@Var";
        pos += 5;
    }
    
    // 获取名称部分
    size_t bracketPos = target.find('[', pos);
    if (bracketPos == std::string::npos) {
        if (isReference) {
            refName = target.substr(pos);
        } else {
            tagName = target.substr(pos);
        }
    } else {
        if (isReference) {
            refName = target.substr(pos, bracketPos - pos);
        } else {
            tagName = target.substr(pos, bracketPos - pos);
        }
        
        size_t closeBracket = target.find(']', bracketPos);
        if (closeBracket != std::string::npos) {
            std::string indexStr = target.substr(bracketPos + 1, closeBracket - bracketPos - 1);
            try {
                targetIndex = std::stoi(indexStr);
            } catch (const std::exception&) {
                // 索引解析失败
            }
        }
    }
    
    // 查找目标节点
    currentIndex = 0;
    for (auto it = children.begin(); it != children.end(); ++it) {
        bool isMatch = false;
        
        if (isReference || isCustom) {
            if ((*it)->getType() == NodeType::ELEMENT) {
                auto element = std::static_pointer_cast<Element>(*it);
                if (element->getTagName() == "reference") {
                    auto attrs = element->getAttributes();
                    if (attrs.find("type") != attrs.end() && 
                        attrs.find("name") != attrs.end()) {
                        auto type = std::get<std::string>(attrs.at("type"));
                        auto name = std::get<std::string>(attrs.at("name"));
                        
                        if (type == refType && name == refName) {
                            isMatch = true;
                        }
                    }
                }
            } else if (isCustom && (*it)->getType() == NodeType::CUSTOM) {
                auto custom = std::static_pointer_cast<Custom>(*it);
                if (custom->getCustomName() == refName) {
                    isMatch = true;
                }
            }
        } else {
            if ((*it)->getType() == NodeType::ELEMENT) {
                auto element = std::static_pointer_cast<Element>(*it);
                if (element->getTagName() == tagName) {
                    isMatch = true;
                }
            }
        }
        
        if (isMatch) {
            if (targetIndex == -1 || currentIndex == targetIndex) {
                return it;
            }
            currentIndex++;
        }
    }
    
    return children.end();
}

void WebGenerator::executeInsertOperation(std::shared_ptr<Node> target, 
                                          const std::shared_ptr<Operate>& insertOp) {
    auto position = insertOp->getPosition();
    auto insertTarget = insertOp->getTarget();
    
    // 递归查找所有子节点
    std::function<void(std::shared_ptr<Node>)> processNode = [&](std::shared_ptr<Node> node) {
        auto& children = node->getChildren();
        
        switch (position) {
            default:
                // Handle all cases to avoid warning
            case Operate::Position::AT_TOP:
                // 插入到开头 - 只在根节点执行
                if (node == target) {
                    for (auto it = insertOp->getChildren().rbegin(); 
                         it != insertOp->getChildren().rend(); ++it) {
                        children.insert(children.begin(), (*it)->clone());
                    }
                }
                break;
                
            case Operate::Position::AT_BOTTOM:
                // 插入到末尾 - 只在根节点执行
                if (node == target) {
                    for (const auto& child : insertOp->getChildren()) {
                        children.push_back(child->clone());
                    }
                }
                break;
                
            case Operate::Position::BEFORE:
            case Operate::Position::AFTER:
            case Operate::Position::REPLACE:
                {
                    // 使用新的 findTargetNode 方法查找目标
                    int currentIndex = 0;
                    auto targetIt = findTargetNode(const_cast<std::vector<std::shared_ptr<Node>>&>(children), 
                                                  insertTarget, currentIndex);
                    
                    if (targetIt != children.end()) {
                    if (position == Operate::Position::BEFORE) {
                        // 在目标前插入
                        for (const auto& child : insertOp->getChildren()) {
                            targetIt = children.insert(targetIt, child->clone());
                            ++targetIt;
                        }
                    } else if (position == Operate::Position::AFTER) {
                        // 在目标后插入
                        ++targetIt;
                        for (const auto& child : insertOp->getChildren()) {
                            targetIt = children.insert(targetIt, child->clone());
                            ++targetIt;
                        }
                    } else if (position == Operate::Position::REPLACE) {
                        // 替换目标
                        targetIt = children.erase(targetIt);
                        for (const auto& child : insertOp->getChildren()) {
                            targetIt = children.insert(targetIt, child->clone());
                            ++targetIt;
                        }
                    }
                    return;  // 找到并处理了，退出
                }
            }
            break;
        }
        
        // 递归处理子节点
        for (auto& child : children) {
            processNode(child);
        }
    };
    
    // 开始递归处理
    processNode(target);
}

void WebGenerator::visitStyle(const std::shared_ptr<Style>& style) {
    // 检查是否是局部样式
    bool isScoped = false;
    auto parent = style->getParent();
    if (parent && parent->getType() == NodeType::ELEMENT) {
        isScoped = true;
        
        // 为父元素生成作用域类
        if (currentScope_.empty()) {
            currentScope_ = generateUniqueId("scope");
        }
    }
    
    std::string css = style->getCssContent();
    
    // 处理变量组引用
    css = processVarReferences(css);
    
    // 处理嵌套规则
    if (css.find("&") != std::string::npos && isScoped) {
        // 替换 & 为父选择器
        std::string parentSelector = "." + currentScope_;
        size_t pos = 0;
        while ((pos = css.find("&", pos)) != std::string::npos) {
            css.replace(pos, 1, parentSelector);
            pos += parentSelector.length();
        }
    }
    
    // 添加作用域
    if (options_.scopeStyles && isScoped) {
        css = scopeSelector(css, currentScope_);
    }
    
    cssCollector_.appendLine(css);
}

std::string WebGenerator::processVarReferences(const std::string& css) {
    std::string result = css;
    
    // 查找所有的变量组引用，格式如：VarName(propertyName)
    std::regex varRegex(R"((\w+)\((\w+)(?:\s*=\s*([^)]+))?\))");
    std::smatch match;
    std::string::const_iterator searchStart(css.cbegin());
    
    std::vector<std::tuple<size_t, size_t, std::string>> replacements;
    
    while (std::regex_search(searchStart, css.cend(), match, varRegex)) {
        std::string varGroupName = match[1];
        std::string propertyName = match[2];
        std::string overrideValue = match[3]; // 可能为空
        
        size_t startPos = match.position() + (searchStart - css.cbegin());
        size_t length = match.length();
        
        std::string replacementValue;
        
        if (!overrideValue.empty()) {
            // 使用特例化的值
            replacementValue = overrideValue;
        } else {
            // 查找变量组定义
            replacementValue = findVarValue(varGroupName, propertyName);
        }
        
        if (!replacementValue.empty()) {
            replacements.push_back({startPos, length, replacementValue});
        }
        
        searchStart = match.suffix().first;
    }
    
    // 从后向前替换，避免位置偏移
    for (auto it = replacements.rbegin(); it != replacements.rend(); ++it) {
        result.replace(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
    }
    
    return result;
}

std::string WebGenerator::findVarValue(const std::string& varGroupName, const std::string& propertyName) {
    // 先在Custom定义中查找
    std::string key = "@Var " + varGroupName;
    auto customIt = customDefinitions_.find(key);
    if (customIt != customDefinitions_.end()) {
        auto custom = std::static_pointer_cast<Custom>(customIt->second);
        auto props = custom->getProperties();
        if (props.find(propertyName) != props.end()) {
            return props.at(propertyName);
        }
    }
    
    // 再在Template定义中查找
    auto templateIt = templateDefinitions_.find(key);
    if (templateIt != templateDefinitions_.end()) {
        auto tmpl = std::static_pointer_cast<Template>(templateIt->second);
        auto params = tmpl->getParameters();
        if (params.find(propertyName) != params.end()) {
            return params.at(propertyName);
        }
    }
    
    // 未找到，返回原始引用
    result_.warnings.push_back("Variable not found: " + varGroupName + "(" + propertyName + ")");
    return varGroupName + "(" + propertyName + ")";
}

// 处理样式中的@Var引用
void WebGenerator::processStyleContent(const std::shared_ptr<Style>& style) {
    std::string content = style->getCssContent();
    
    // 查找@Var引用
    std::regex varRefRegex(R"(@Var\s+(\w+)\s*;)");
    std::smatch match;
    std::string::const_iterator searchStart(content.cbegin());
    
    while (std::regex_search(searchStart, content.cend(), match, varRefRegex)) {
        std::string varName = match[1];
        
        // 查找变量组定义并展开所有属性
        std::string replacement = expandVarGroup(varName);
        
        size_t startPos = match.position() + (searchStart - content.cbegin());
        content.replace(startPos, match.length(), replacement);
        
        searchStart = content.cbegin() + startPos + replacement.length();
    }
    
    style->setContent(content);
}

std::string WebGenerator::expandVarGroup(const std::string& varGroupName) {
    std::stringstream ss;
    
    // 查找变量组定义
    std::string key = "@Var " + varGroupName;
    
    // 先在Custom定义中查找
    auto customIt = customDefinitions_.find(key);
    if (customIt != customDefinitions_.end()) {
        auto custom = std::static_pointer_cast<Custom>(customIt->second);
        for (const auto& [prop, value] : custom->getProperties()) {
            ss << prop << ": " << value << ";\n";
        }
        return ss.str();
    }
    
    // 再在Template定义中查找
    auto templateIt = templateDefinitions_.find(key);
    if (templateIt != templateDefinitions_.end()) {
        auto tmpl = std::static_pointer_cast<Template>(templateIt->second);
        for (const auto& [prop, value] : tmpl->getParameters()) {
            ss << prop << ": " << value << ";\n";
        }
        return ss.str();
    }
    
    result_.warnings.push_back("Variable group not found: " + varGroupName);
    return "/* @Var " + varGroupName + " not found */";
}

void WebGenerator::visitScript(const std::shared_ptr<Script>& script) {
    if (script->getScriptType() == Script::ScriptType::INLINE && script->isScoped()) {
        // 局部脚本
        std::string elementId = script->getScope();
        if (elementId.empty()) {
            // 如果没有作用域，尝试从父节点获取
            auto parent = script->getParent();
            if (parent && parent->getType() == NodeType::ELEMENT) {
                auto element = std::static_pointer_cast<Element>(parent);
                auto attrs = element->getAttributes();
                if (attrs.find("id") != attrs.end()) {
                    if (std::holds_alternative<std::string>(attrs.at("id"))) {
                        elementId = std::get<std::string>(attrs.at("id"));
                    }
                } else {
                    elementId = generateUniqueId("element");
                }
            }
        }
        
        // 收集局部脚本
        jsRuntime_->collectLocalScript(script->getContent(), elementId);
    } else {
        // 全局脚本
        std::string wrappedCode = script->generateWrappedCode();
        if (!wrappedCode.empty()) {
            jsCollector_.appendLine(wrappedCode);
        }
    }
}

void WebGenerator::visitComment(const std::shared_ptr<Comment>& comment) {
    // 生成器识别的注释会被输出到HTML中
    std::string content = comment->getContent();
    
    // 去除开头的 "--"（如果有的话）
    if (content.substr(0, 2) == "--") {
        content = content.substr(2);
    }
    
    // 去除首尾空格
    content = trim(content);
    
    // 生成HTML注释
    htmlCollector_.append("<!-- ");
    htmlCollector_.append(escape(content));
    htmlCollector_.append(" -->");
}

void WebGenerator::visitOrigin(const std::shared_ptr<Origin>& origin) {
    std::string content = origin->getContent();
    std::string name = origin->getOriginName();
    
    // 如果有名称，存储以供后续引用
    if (!name.empty()) {
        std::string key = generateOriginKey(origin->getOriginType(), name);
        originDefinitions_[key] = origin;
        
        // 如果是内联形式（有分号），不生成内容
        if (origin->isInline()) {
            return;
        }
    }
    
    // 根据类型生成相应的内容
    switch (origin->getOriginType()) {
        case Origin::OriginType::HTML:
            htmlCollector_.appendLine(content);
            break;
            
        case Origin::OriginType::STYLE:
            cssCollector_.appendLine(content);
            break;
            
        case Origin::OriginType::JAVASCRIPT:
            jsCollector_.appendLine(content);
            break;
    }
}

// TODO: Implement when Reference node type is added
/*
void WebGenerator::visitReference(const std::shared_ptr<Reference>& ref) {
    // 检查是否是原始嵌入的引用
    std::string refType = ref->getReferenceType();
    std::string refName = ref->getReferenceName();
    
    if (refType == "@Html" || refType == "@Style" || refType == "@JavaScript") {
        // 查找原始嵌入定义
        auto origin = findOriginDefinition(refType, refName);
        if (origin) {
            // 生成原始内容
            switch (origin->getOriginType()) {
                case Origin::OriginType::HTML:
                    htmlCollector_.appendLine(origin->getContent());
                    break;
                    
                case Origin::OriginType::STYLE:
                    cssCollector_.appendLine(origin->getContent());
                    break;
                    
                case Origin::OriginType::JAVASCRIPT:
                    jsCollector_.appendLine(origin->getContent());
                    break;
            }
        } else {
            result_.warnings.push_back("Origin not found: " + refType + " " + refName);
        }
    } else {
        // 处理其他类型的引用（样式、元素、变量等）
        Generator::visit(ref);
    }
}
*/

std::string WebGenerator::generateOriginKey(Origin::OriginType type, const std::string& name) {
    switch (type) {
        case Origin::OriginType::HTML:
            return "@Html " + name;
        case Origin::OriginType::STYLE:
            return "@Style " + name;
        case Origin::OriginType::JAVASCRIPT:
            return "@JavaScript " + name;
        default:
            return name;
    }
}

std::shared_ptr<Origin> WebGenerator::findOriginDefinition(const std::string& type, const std::string& name) {
    std::string key;
    
    if (type == "@Html") {
        key = "@Html " + name;
    } else if (type == "@Style") {
        key = "@Style " + name;
    } else if (type == "@JavaScript") {
        key = "@JavaScript " + name;
    } else {
        return nullptr;
    }
    
    auto it = originDefinitions_.find(key);
    if (it != originDefinitions_.end()) {
        return it->second;
    }
    
    return nullptr;
}

void WebGenerator::visitImport(const std::shared_ptr<Import>& import) {
    // 处理导入
    if (import->isNamespaceImport()) {
        // 从命名空间导入
        std::string namespaceName = import->getTargetNamespace();
        std::string alias = import->getAlias();
        
        if (configManager_->isDebugMode()) {
            result_.warnings.push_back("Import from namespace: " + namespaceName + 
                                       (alias.empty() ? "" : " as " + alias));
        }
        
        // TODO: 实际的命名空间导入逻辑需要模块系统支持
    } else {
        // 从文件导入
        std::string filePath = import->getFilePath();
        std::string alias = import->getAlias();
        
        if (configManager_->isDebugMode()) {
            result_.warnings.push_back("Import from file: " + filePath + 
                                       (alias.empty() ? "" : " as " + alias));
        }
        
        // TODO: 实际的文件导入逻辑需要模块系统支持
    }
}

void WebGenerator::visitExport(const std::shared_ptr<Export>& export_) {
    // 处理导出
    std::string fromNamespace = export_->getFromNamespace();
    
    if (configManager_->isDebugMode()) {
        if (!fromNamespace.empty()) {
            result_.warnings.push_back("Export from namespace: " + fromNamespace);
        }
        
        for (const auto& item : export_->getExportItems()) {
            std::string typeStr;
            switch (item.type) {
                case Export::ExportType::ELEMENT: typeStr = "@Element"; break;
                case Export::ExportType::STYLE: typeStr = "@Style"; break;
                case Export::ExportType::VAR: typeStr = "@Var"; break;
                case Export::ExportType::NAMESPACE: typeStr = "namespace"; break;
                case Export::ExportType::ALL: typeStr = "*"; break;
            }
            
            std::string exportInfo = "Export: " + typeStr + " " + item.name;
            if (!item.alias.empty()) {
                exportInfo += " as " + item.alias;
            }
            result_.warnings.push_back(exportInfo);
        }
    }
    
    // TODO: 实际的导出逻辑需要模块系统支持
}

// 辅助函数：去除首尾空格
std::string WebGenerator::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// 应用引用修改
void WebGenerator::applyReferenceModifications(std::shared_ptr<Node> target,
                                             const std::shared_ptr<Element>& refNode) {
    // 应用引用节点中的子节点作为修改
    for (const auto& child : refNode->getChildren()) {
        if (child->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(child);
            
            // 特殊处理 delete 元素
            if (element->getTagName() == "delete") {
                // 提取删除目标
                auto attrs = element->getAttributes();
                if (attrs.find("target") != attrs.end() && 
                    std::holds_alternative<std::string>(attrs.at("target"))) {
                    std::string deleteTarget = std::get<std::string>(attrs.at("target"));
                    deleteFromNode(target, deleteTarget);
                }
            } else {
                // 查找目标中对应的元素并合并属性和子节点
                mergeElement(target, element);
            }
        } else if (child->getType() == NodeType::OPERATE) {
            auto op = std::static_pointer_cast<Operate>(child);
            if (op->getOperationType() == Operate::OperationType::DELETE) {
                // 执行删除操作
                executeDeleteOperation(target, op);
            } else if (op->getOperationType() == Operate::OperationType::INSERT) {
                // 执行插入操作
                executeInsertOperation(target, op);
            }
        }
        // 其他类型的子节点直接添加
        else {
            target->addChild(child->clone(true));
        }
    }
}

// 执行删除操作
void WebGenerator::executeDeleteOperation(std::shared_ptr<Node> target,
                                        const std::shared_ptr<Operate>& deleteOp) {
    // 获取要删除的目标
    const std::string& deleteTarget = deleteOp->getTarget();
    
    // 递归删除
    deleteFromNode(target, deleteTarget);
}

// 从节点中删除指定项
void WebGenerator::deleteFromNode(std::shared_ptr<Node> node, const std::string& target) {
    // 获取子节点的可修改引用
    auto& children = const_cast<std::vector<std::shared_ptr<Node>>&>(node->getChildren());
    
    // 解析目标字符串
    // 支持格式：
    // - tagname[index]
    // - @Element Name[index]
    // - Custom @Element Name[index]
    // - [Custom] @Element Name[index]
    
    // 检查是否是引用或组件删除
    bool isReference = false;
    bool isCustom = false;
    std::string refType;
    std::string refName;
    std::string tagName;
    int targetIndex = -1;
    
    // 解析目标字符串
    size_t pos = 0;
    
    // 检查 [Custom] 或 [Template]
    if (target.find("[Custom]") == 0 || target.find("[Template]") == 0) {
        isCustom = true;
        pos = target.find(']') + 1;
        while (pos < target.length() && target[pos] == ' ') pos++;
    }
    
    // 检查 Custom 或 Template 关键字
    if (target.find("Custom ", pos) == pos) {
        isCustom = true;
        pos += 7;
    } else if (target.find("Template ", pos) == pos) {
        isCustom = true;
        pos += 9;
    }
    
    // 检查 @Element, @Style, @Var
    if (target.find("@Element ", pos) == pos) {
        isReference = true;
        refType = "@Element";
        pos += 9;
    } else if (target.find("@Style ", pos) == pos) {
        isReference = true;
        refType = "@Style";
        pos += 7;
    } else if (target.find("@Var ", pos) == pos) {
        isReference = true;
        refType = "@Var";
        pos += 5;
    }
    
    // 获取名称部分
    size_t bracketPos = target.find('[', pos);
    if (bracketPos == std::string::npos) {
        // 没有索引
        if (isReference) {
            refName = target.substr(pos);
        } else {
            tagName = target.substr(pos);
        }
    } else {
        // 有索引
        if (isReference) {
            refName = target.substr(pos, bracketPos - pos);
        } else {
            tagName = target.substr(pos, bracketPos - pos);
        }
        
        size_t closeBracket = target.find(']', bracketPos);
        if (closeBracket != std::string::npos) {
            std::string indexStr = target.substr(bracketPos + 1, closeBracket - bracketPos - 1);
            try {
                targetIndex = std::stoi(indexStr);
            } catch (const std::exception&) {
                // 索引解析失败
            }
        }
    }
    
    // 执行删除
    if (isReference || isCustom) {
        // 删除引用或自定义组件
        int currentIndex = 0;
        auto it = children.begin();
        while (it != children.end()) {
            bool shouldDelete = false;
            
            if ((*it)->getType() == NodeType::ELEMENT) {
                auto element = std::static_pointer_cast<Element>(*it);
                if (element->getTagName() == "reference") {
                    // 检查引用是否匹配
                    auto attrs = element->getAttributes();
                    if (attrs.find("type") != attrs.end() && 
                        attrs.find("name") != attrs.end()) {
                        auto type = std::get<std::string>(attrs.at("type"));
                        auto name = std::get<std::string>(attrs.at("name"));
                        
                        if (type == refType && name == refName) {
                            if (targetIndex == -1 || currentIndex == targetIndex) {
                                shouldDelete = true;
                            }
                            currentIndex++;
                        }
                    }
                }
            } else if (isCustom && (*it)->getType() == NodeType::CUSTOM) {
                auto custom = std::static_pointer_cast<Custom>(*it);
                if (custom->getCustomName() == refName) {
                    if (targetIndex == -1 || currentIndex == targetIndex) {
                        shouldDelete = true;
                    }
                    currentIndex++;
                }
            }
            
            if (shouldDelete) {
                it = children.erase(it);
                if (targetIndex != -1) break;  // 只删除一个
            } else {
                ++it;
            }
        }
    } else {
        // 删除普通元素
        if (targetIndex != -1) {
            // 索引删除
            int currentIndex = 0;
            auto it = children.begin();
            while (it != children.end()) {
                if ((*it)->getType() == NodeType::ELEMENT) {
                    auto element = std::static_pointer_cast<Element>(*it);
                    if (element->getTagName() == tagName) {
                        if (currentIndex == targetIndex) {
                            it = children.erase(it);
                            break;
                        }
                        currentIndex++;
                    }
                }
                ++it;
            }
        } else {
            // 删除所有匹配的
            children.erase(
                std::remove_if(children.begin(), children.end(),
                    [&tagName](const std::shared_ptr<Node>& child) {
                        if (child->getType() == NodeType::ELEMENT) {
                            auto element = std::static_pointer_cast<Element>(child);
                            return element->getTagName() == tagName;
                        }
                        return false;
                    }),
                children.end()
            );
        }
    }
    
    // 递归处理子节点
    for (auto& child : children) {
        deleteFromNode(child, target);
    }
}

// 合并元素
void WebGenerator::mergeElement(std::shared_ptr<Node> target, 
                               const std::shared_ptr<Element>& source) {
    // 在目标中查找同名元素
    if (target->getType() == NodeType::ELEMENT) {
        auto targetElement = std::static_pointer_cast<Element>(target);
        if (targetElement->getTagName() == source->getTagName()) {
            // 合并属性
            for (const auto& [key, value] : source->getAttributes()) {
                targetElement->setAttribute(key, value);
            }
            // 合并子节点
            for (const auto& child : source->getChildren()) {
                targetElement->addChild(child->clone(true));
            }
            return;
        }
    }
    
    // 递归查找子节点
    for (auto& child : target->getChildren()) {
        mergeElement(child, source);
    }
}

// 处理引用节点
void WebGenerator::processReference(const std::shared_ptr<Element>& refNode) {

    auto attributes = refNode->getAttributes();
    
    // 获取引用信息
    std::string type = attributes.find("type") != attributes.end() && 
        std::holds_alternative<std::string>(attributes.at("type")) 
        ? std::get<std::string>(attributes.at("type")) : "";
    std::string name = attributes.find("name") != attributes.end() && 
        std::holds_alternative<std::string>(attributes.at("name")) 
        ? std::get<std::string>(attributes.at("name")) : "";
    std::string kind = attributes.find("kind") != attributes.end() && 
        std::holds_alternative<std::string>(attributes.at("kind"))
        ? std::get<std::string>(attributes.at("kind")) : "";
    

    

    

    
    // 构建查找键
    std::string key = type + " " + name;

    
    // 根据 kind 属性决定查找 Template 还是 Custom
    std::shared_ptr<Node> definition = nullptr;
    
    if (kind == "Template") {
        // 明确查找 Template
        auto it = templateDefinitions_.find(key);
        if (it != templateDefinitions_.end()) {
            definition = it->second;
        }
    } else if (kind == "Custom") {
        // 明确查找 Custom
        auto it = customDefinitions_.find(key);
        if (it != customDefinitions_.end()) {
            definition = it->second;
        }
    } else {
        // 没有指定 kind，按优先级查找：先 Custom 后 Template
        auto customIt = customDefinitions_.find(key);
        if (customIt != customDefinitions_.end()) {
            definition = customIt->second;

        } else {
            auto templateIt = templateDefinitions_.find(key);
            if (templateIt != templateDefinitions_.end()) {
                definition = templateIt->second;

            }
        }
    }
    
    if (!definition) {
        // 未找到定义，生成警告注释

        htmlCollector_.append("<!-- Warning: Component '" + name + 
            (kind.empty() ? "" : " [" + kind + "]") + "' not found -->");
        return;
    }
    

    
        // 处理组件实例（对于元素引用）
    if (type == "@Element") {
        // 克隆定义
        auto cloned = definition->clone(true);
        
        // 应用实例修改（如果有特例化内容）
        if (!refNode->getChildren().empty()) {

            applyReferenceModifications(cloned, refNode);
        }
        
        // 直接生成克隆定义的子节点
        // 跳过 Custom/Template 节点本身，直接访问其内容
        for (const auto& child : cloned->getChildren()) {
            visit(child);
        }
    } else if (type == "@Style") {
        // 样式引用直接访问
        visit(definition);
    }
}

} // namespace chtl