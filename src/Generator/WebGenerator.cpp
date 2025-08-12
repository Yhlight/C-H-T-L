#include "Generator/Generator.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Template.h"
#include "Node/Custom.h"
#include "Node/Origin.h"
#include "Node/Import.h"
#include "Node/Export.h"
#include "Node/Config.h"
#include "Node/Namespace.h"
#include "Node/Operate.h"
#include "Node/Delete.h"
#include "Node/Info.h"
#include "Scanner/ChtlScanner.h"
#include "Loader/ImportResolver.h"
#include "CJmod/CJmodProcessor.h"
#include "Runtime/ChtlJsRuntime.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <set>
#include <variant>


namespace chtl {

GeneratorResult WebGenerator::generate(const std::shared_ptr<Node>& ast) {
    // 在调用基类方法之前重置运行时
    jsRuntime_->reset();
    
    // 调用基类生成方法
    Generator::generate(ast);
    
    // 生成完整的HTML文档
    generateHTMLDocument();
    
    // 注入运行时代码
    injectRuntimeCode();
    
    // 注入 CJmod 运行时（如果有）
    if (currentContext_ && currentContext_->hasCJmodImports()) {
        injectCJmodRuntime();
    }
    
    return result_;
}

std::string WebGenerator::generateHTMLDocument() {
    // 获取当前的 HTML 内容
    std::string bodyContent = htmlCollector_.getCode();
    
    // 检查是否已经有完整的 HTML 文档结构（包含 DOCTYPE）
    if (bodyContent.find("<!DOCTYPE") != std::string::npos) {
        result_.html = bodyContent;
        return result_.html;
    }
    
    // 提取 head 和 body 内容
    std::string headContent;
    std::string mainContent;
    
    // 查找 head 标签内容
    size_t headStart = bodyContent.find("<head>");
    size_t headEnd = bodyContent.find("</head>");
    if (headStart != std::string::npos && headEnd != std::string::npos) {
        headStart += 6; // 跳过 "<head>"
        headContent = bodyContent.substr(headStart, headEnd - headStart);
        
        // 移除 head 部分（包括标签）
        bodyContent.erase(headStart - 6, headEnd - headStart + 13); // 包括 "</head>"
    }
    
    // 如果有 <html> 标签，提取其内容
    size_t htmlStart = bodyContent.find("<html>");
    size_t htmlEnd = bodyContent.find("</html>");
    if (htmlStart != std::string::npos && htmlEnd != std::string::npos) {
        htmlStart += 6; // 跳过 "<html>"
        mainContent = bodyContent.substr(htmlStart, htmlEnd - htmlStart);
    } else {
        mainContent = bodyContent;
    }
    
    std::stringstream doc;
    
    // DOCTYPE
    doc << "<!DOCTYPE html>\n";
    doc << "<html lang=\"zh-CN\">\n";
    doc << "<head>\n";
    doc << "  <meta charset=\"UTF-8\">\n";
    doc << "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    
    // 如果有提取的 head 内容，使用它；否则使用默认标题
    if (!headContent.empty()) {
        doc << headContent;
    } else {
        doc << "  <title>CHTL Generated Page</title>\n";
    }
    
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
    
    // 主体内容 - 使用 htmlCollector 的内容
    doc << mainContent;
    
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
    
    // 更新 result_.html
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
    if (!element) return;
    
    std::string tag = element->getTagName();
    
    // 特殊处理引用节点
    if (tag == "reference") {
        try {
            processReference(element);
        } catch (const std::exception& e) {
            addError("Error processing reference: " + std::string(e.what()));
        }
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
    
    // 特殊处理 html、head 和 body 标签
    // 这些标签的结构由 generateHTMLDocument 处理
    if (tag == "html") {
        // 只处理子节点
        for (const auto& child : element->getChildren()) {
            visit(child);
        }
        return;
    }
    
    if (tag == "head") {
        // head 的内容已经在 generateHTMLDocument 中处理
        // 但我们需要处理其中的 style 节点
        for (const auto& child : element->getChildren()) {
            if (child->getType() == NodeType::STYLE) {
                visit(child);
            }
            // title 等其他内容已经被提取
        }
        return;
    }
    
    if (tag == "body") {
        // 只处理子节点，不生成 body 标签本身
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
            // 修正判断逻辑：元素内的脚本就是局部脚本
            // 不需要检查 ScriptType 和 isScoped，因为我们已经在 visitScript 中处理了
            hasLocalScript = true;
            break;
        }
    }
    
    // 检查是否有style子节点
    std::string inlineStyles;
    for (const auto& child : element->getChildren()) {
        if (child->getType() == NodeType::STYLE) {
            auto styleNode = std::static_pointer_cast<Style>(child);
            std::string css = styleNode->getCssContent();
            if (!css.empty()) {
                            // 处理变量组引用
            css = processVarReferences(css);
            if (!inlineStyles.empty() && inlineStyles.back() != ';') {
                inlineStyles += "; ";
            }
            inlineStyles += css;
            }
            
            // 处理样式节点的子节点（全局样式如.class, #id, &:hover）
            for (const auto& styleChild : styleNode->getChildren()) {
                if (styleChild->getType() == NodeType::STYLE) {
                    auto globalStyle = std::static_pointer_cast<Style>(styleChild);
                    if (globalStyle->isGlobal()) {
                        // 收集全局样式
                        std::string selector = globalStyle->getSelector();
                        std::string content = globalStyle->getCssContent();
                        if (!selector.empty() && !content.empty()) {
                            // 处理变量组引用
                            content = processVarReferences(content);
                            cssCollector_.appendLine(selector + " {");
                            cssCollector_.appendLine(content);
                            cssCollector_.appendLine("}");
                        }
                    }
                } else if (styleChild->getType() == NodeType::ELEMENT) {
                    // 可能是引用节点，需要处理
                    visit(styleChild);
                }
            }
        }
    }
    
    // 处理属性
    // 如果有内联样式，添加或合并到 style 属性
    if (!inlineStyles.empty()) {
        auto existingStyle = element->getAttribute("style");
        if (std::holds_alternative<std::string>(existingStyle)) {
            std::string styleStr = std::get<std::string>(existingStyle);
            if (!styleStr.empty() && styleStr.back() != ';') {
                styleStr += "; ";
            }
            element->setAttribute("style", styleStr + inlineStyles);
        } else {
            element->setAttribute("style", inlineStyles);
        }
    }
    
    // 首先检查元素是否已经有ID
    auto idAttr = element->getAttribute("id");
    if (std::holds_alternative<std::string>(idAttr)) {
        elementId = std::get<std::string>(idAttr);
    } else if (hasLocalScript) {
        // 只有在没有ID且有局部脚本时才生成ID
        elementId = generateUniqueId("element");
        element->setAttribute("id", elementId);
    }
    
    // 输出所有属性
    const auto& attributes = element->getAttributes();
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
        } else if (key == "id") {
            // 确保 ID 被输出
            if (std::holds_alternative<std::string>(value)) {
                htmlCollector_.append(" id=\"" + escape(std::get<std::string>(value)) + "\"");
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
        if (child->getType() == NodeType::STYLE) {
            // Style 已经在前面处理过了，跳过
            continue;
        }
        visit(child);
    }
    
    // 结束标签
    htmlCollector_.append("</" + tag + ">");
}

void WebGenerator::visitCustom(const std::shared_ptr<Custom>& custom) {
    // Custom 定义在基类的 collectDefinitions 中已处理
    // 只需要处理没有名称的实例（从引用克隆的）
    
    if (!custom->getCustomName().empty()) {
        // 有名称的是定义，不生成内容
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
    // 检查是否是局部样式（在元素内的样式，但不包括 head 元素）
    auto parent = style->getParent();
    if (parent && parent->getType() == NodeType::ELEMENT) {
        auto element = std::static_pointer_cast<Element>(parent);
        // 如果父元素是 head，这是全局样式
        if (element->getTagName() != "head") {
            // 局部样式应该作为父元素的 style 属性，而不是全局 CSS
            // 不需要处理，因为我们将在 visitElement 中处理
            return;
        }
    }
    

    // 全局样式处理
    std::string css = style->getCssContent();
    
    // 处理变量组引用
    css = processVarReferences(css);
    
    // 全局样式不需要作用域处理
    cssCollector_.appendLine(css);
}

std::string WebGenerator::processVarReferences(const std::string& css) {
    std::string result = css;
    
    // 首先收集所有已知的变量组名称
    std::set<std::string> knownVarGroups;
    
    // 从 Custom 定义中收集
    for (const auto& [key, node] : customDefinitions_) {
        if (key.find("@Var ") == 0) {
            knownVarGroups.insert(key.substr(5)); // 移除 "@Var " 前缀
        }
    }
    
    // 从 Template 定义中收集
    for (const auto& [key, node] : templateDefinitions_) {
        if (key.find("@Var ") == 0) {
            knownVarGroups.insert(key.substr(5)); // 移除 "@Var " 前缀
        }
    }
    
    // 查找所有的变量组引用，格式如：VarName(propertyName) 或 VarName ( propertyName )
    std::regex varRegex(R"((\w+)\s*\(\s*(\w+)(?:\s*=\s*([^)]+))?\s*\))");
    std::smatch match;
    std::string::const_iterator searchStart(css.cbegin());
    
    std::vector<std::tuple<size_t, size_t, std::string>> replacements;
    
    while (std::regex_search(searchStart, css.cend(), match, varRegex)) {
        std::string varGroupName = match[1];
        std::string propertyName = match[2];
        std::string overrideValue = match[3]; // 可能为空
        
        // 只处理已知的变量组
        if (knownVarGroups.find(varGroupName) != knownVarGroups.end()) {
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
    addWarning("Variable not found: " + varGroupName + "(" + propertyName + ")");
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

void WebGenerator::visitComment(const std::shared_ptr<Comment>& comment) {
    // 根据上下文生成不同格式的注释
    std::string content = comment->getContent();
    
    // 判断当前上下文
    auto parent = comment->getParent();
    if (parent) {
        if (parent->getType() == NodeType::SCRIPT) {
            // JavaScript 注释
            jsCollector_.appendLine("// " + content);
        } else if (parent->getType() == NodeType::STYLE) {
            // CSS 注释
            cssCollector_.appendLine("/* " + content + " */");
        } else {
            // HTML 注释
            htmlCollector_.append("<!-- " + content + " -->");
        }
    } else {
        // 默认为 HTML 注释
        htmlCollector_.append("<!-- " + content + " -->");
    }
}

void WebGenerator::visitTemplate(const std::shared_ptr<Template>& /*tmpl*/) {
    // 模板定义已经在基类的 collectDefinitions 中处理
    // 不需要生成任何输出
}

void WebGenerator::visitScript(const std::shared_ptr<Script>& script) {
    // 判断是否为局部脚本：脚本的父节点是元素节点（且不是 body 或 html）
    auto parent = script->getParent();
    bool isLocalScript = false;
    
    if (parent && parent->getType() == NodeType::ELEMENT) {
        auto element = std::static_pointer_cast<Element>(parent);
        std::string tagName = element->getTagName();
        // body 和 html 内的脚本被认为是全局脚本
        if (tagName != "body" && tagName != "html" && tagName != "head") {
            isLocalScript = true;
        }
    }
    
    if (isLocalScript) {
        // 局部脚本 - 收集元素信息
        auto element = std::static_pointer_cast<Element>(parent);
        ChtlJsRuntime::ElementInfo elementInfo;
        
        // 获取元素的属性
        auto attrs = element->getAttributes();
        
        // 获取 ID
        if (attrs.find("id") != attrs.end()) {
            if (std::holds_alternative<std::string>(attrs.at("id"))) {
                elementInfo.id = std::get<std::string>(attrs.at("id"));
            }
        }
        
        // 获取 class
        if (attrs.find("class") != attrs.end()) {
            if (std::holds_alternative<std::string>(attrs.at("class"))) {
                elementInfo.className = std::get<std::string>(attrs.at("class"));
            }
        }
        
        // 检查是否有局部样式块
        for (const auto& child : element->getChildren()) {
            if (child->getType() == NodeType::STYLE) {
                auto styleNode = std::static_pointer_cast<Style>(child);
                if (!styleNode->isGlobal()) {
                    elementInfo.hasLocalStyle = true;
                    // TODO: 解析局部样式块中的选择器
                    // 这里需要更复杂的CSS解析逻辑
                    break;
                }
            }
        }
        
        // 如果没有任何标识符，生成一个ID
        if (elementInfo.id.empty() && elementInfo.className.empty()) {
            elementInfo.id = generateUniqueId("element");
            // 将ID添加到元素上，确保HTML输出时也有这个ID
            element->setAttribute("id", elementInfo.id);
        }
        
        // 收集局部脚本
        try {
            // 先处理变量替换
            std::string processedScript = processVarReferences(script->getContent());
            jsRuntime_->collectLocalScript(processedScript, elementInfo);
        } catch (const std::exception& e) {
            addError("Error collecting local script: " + std::string(e.what()));
        }
    } else {
        // 全局脚本
        std::string scriptContent = script->getContent();
        // 先处理变量替换
        scriptContent = processVarReferences(scriptContent);
        
        // 创建一个临时的脚本节点来生成包装代码
        auto tempScript = std::make_shared<Script>();
        tempScript->setContent(scriptContent);
        tempScript->setScriptType(script->getScriptType());
        tempScript->setScope(script->getScope());
        
        std::string wrappedCode = tempScript->generateWrappedCode();
        if (!wrappedCode.empty()) {
            // 应用 CJmod 处理
            if (currentContext_ && currentContext_->hasCJmodImports()) {
                wrappedCode = processJavaScriptWithCJmod(wrappedCode);
            }
            jsCollector_.appendLine(wrappedCode);
        }
    }
}

void WebGenerator::visitScriptWithCJmod(const std::shared_ptr<Script>& script, bool isLocal) {
    if (!script) return;
    
    std::string scriptContent = script->getContent();
    
    // 使用 ChtlScanner 进行精确切割
    ChtlScanner scanner;
    auto segments = scanner.scan(scriptContent, SegmentType::JS);
    
    // 处理每个片段
    std::string processedContent;
    for (const auto& segment : segments) {
        if (segment.type == SegmentType::CHTL_JS) {
            // 使用新的 CJmod 系统处理 CHTL-JS
            auto& processor = cjmod::CJmodProcessor::getInstance();
            std::string processed = processor.processScript(segment.content);
            processedContent += processed;
        } else {
            // 纯 JavaScript 代码保持不变
            processedContent += segment.content;
        }
    }
    
    // 处理后的脚本内容
    if (isLocal) {
        // 局部脚本已经在 visitScript 中处理
    } else {
        // 全局脚本
        jsCollector_.appendLine(processedContent);
    }
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
    // 使用 ImportResolver 解析路径
    ImportResolver resolver;
    
    auto result = resolver.resolve(import->getFilePath(), import->getType(), ".");
    
    if (!result.success) {
        addError("Failed to resolve import: " + import->getFilePath());
        return;
    }
    
    // 处理导入
    if (import->getType() == Import::ImportType::CJMOD) {
        // CJmod 模块
        // 初始化 CJmod 系统
        cjmod::integration::initialize();
        
        // 处理导入
        cjmod::integration::processImport(import->getName(), result.resolvedPath);
        
        // 记录活跃模块
        activeCJmodModules_.insert(import->getName());
        return;
    }
    
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
                // 对于普通元素，直接添加到目标
                target->addChild(element->clone(true));
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
            // 合并属性 - 直接设置到目标元素
            const auto& sourceAttrs = source->getAttributes();
            for (const auto& [key, value] : sourceAttrs) {
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
        
        // 处理 slot 替换
        processSlots(cloned, refNode);
        
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

// 处理 slot 元素替换
void WebGenerator::processSlots(std::shared_ptr<Node> templateNode, 
                               const std::shared_ptr<Element>& refNode) {
    // 递归查找并替换所有 slot 元素
    auto& children = const_cast<std::vector<std::shared_ptr<Node>>&>(templateNode->getChildren());
    
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        
        if (child->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(child);
            
            if (element->getTagName() == "slot") {
                // 替换 slot 为引用节点的内容
                children.erase(children.begin() + i);
                
                // 插入引用节点的所有子节点
                for (const auto& refChild : refNode->getChildren()) {
                    // 跳过引用节点中的操作节点
                    if (refChild->getType() != NodeType::OPERATE) {
                        children.insert(children.begin() + i, refChild->clone(true));
                        ++i;
                    }
                }
                --i; // 调整索引
            } else {
                // 递归处理子节点
                processSlots(element, refNode);
            }
        }
    }
}

std::string WebGenerator::processJavaScriptWithCJmod(const std::string& jsCode) {
    if (activeCJmodModules_.empty()) {
        return jsCode;
    }
    
    // 使用 CJmod 处理器处理 JavaScript 代码
    auto& processor = cjmod::CJmodProcessor::getInstance();
    std::vector<std::string> modules(activeCJmodModules_.begin(), activeCJmodModules_.end());
    return processor.processScript(jsCode, modules);
}

void WebGenerator::injectCJmodRuntime() {
    if (activeCJmodModules_.empty()) {
        return;
    }
    
    // 生成 CJmod 运行时代码
    auto& processor = cjmod::CJmodProcessor::getInstance();
    std::vector<std::string> modules(activeCJmodModules_.begin(), activeCJmodModules_.end());
    std::string runtime = processor.getRuntimeCode(modules);
    
    if (!runtime.empty()) {
        // 在用户代码之前注入 CJmod 运行时
        result_.js = runtime + "\n\n" + result_.js;
    }
}

} // namespace chtl