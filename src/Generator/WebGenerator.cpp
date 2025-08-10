#include "Generator/Generator.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Custom.h"
#include "Node/Operate.h"
#include "Runtime/ChtlJsRuntime.h"
#include <regex>
#include <algorithm>
#include <set>

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

void WebGenerator::generateHTMLDocument() {
    // 如果已经有html标签，不需要包装
    if (result_.html.find("<html") != std::string::npos) {
        return;
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
            result_.externalStyles.push_back("styles.css");
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
            result_.externalScripts.push_back("app.js");
            doc << "  <script src=\"app.js\"></script>\n";
        }
    }
    
    doc << "</body>\n";
    doc << "</html>\n";
    
    result_.html = doc.str();
}

void WebGenerator::injectRuntimeCode() {
    // 获取CHTL运行时代码
    std::string runtimeCode = jsRuntime_->generateRuntimeCode();
    
    if (!runtimeCode.empty()) {
        // 在用户代码之前注入运行时
        result_.js = runtimeCode + "\n" + result_.js;
    }
}

void WebGenerator::visitElement(const std::shared_ptr<Element>& element) {
    const std::string& tag = element->getTag();
    
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
        elementId = attributes.at("id");
    }
    
    // 输出所有属性
    for (const auto& [key, value] : attributes) {
        // 处理特殊属性
        if (key == "class") {
            // 处理类名数组
            std::string classValue = value;
            if (!currentScope_.empty() && options_.scopeStyles) {
                classValue = currentScope_ + " " + classValue;
            }
            htmlCollector_.append(" class=\"" + escape(classValue) + "\"");
        } else if (key == "style") {
            // 处理内联样式对象
            htmlCollector_.append(" style=\"" + escape(value) + "\"");
        } else {
            // 普通属性
            htmlCollector_.append(" " + key + "=\"" + escape(value) + "\"");
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
    // 获取自定义组件名称
    std::string componentName = custom->getCustomName();
    if (componentName.empty()) {
        // 尝试从属性获取
        auto attrs = custom->getAttributes();
        if (attrs.find("name") != attrs.end()) {
            componentName = attrs.at("name");
        }
    }
    
    // 查找组件定义
    auto componentDef = findComponentDefinition(componentName, custom->getCustomType());
    if (!componentDef) {
        result_.warnings.push_back("Component not found: " + componentName);
        htmlCollector_.append("<!-- Component not found: " + componentName + " -->");
        return;
    }
    
    // 处理组件实例
    processCustomComponent(custom, componentDef);
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
        if (child->getType() == NodeType::DELETE) {
            auto attrs = child->getAttributes();
            if (attrs.find("target") != attrs.end()) {
                deleteTargets.insert(attrs.at("target"));
            }
        } else if (child->getType() == NodeType::OPERATE) {
            auto op = std::static_pointer_cast<Operate>(child);
            if (op->getOperation() == Operate::OperationType::INSERT) {
                insertOperations.push_back(op);
            }
        }
    }
    
    // 执行删除操作
    if (!deleteTargets.empty()) {
        auto& children = target->getChildren();
        children.erase(
            std::remove_if(children.begin(), children.end(),
                [&deleteTargets](const std::shared_ptr<Node>& node) {
                    if (node->getType() == NodeType::ELEMENT) {
                        auto elem = std::static_pointer_cast<Element>(node);
                        // 检查标签名
                        if (deleteTargets.find(elem->getTagName()) != deleteTargets.end()) {
                            return true;
                        }
                        // 检查是否是引用（如 @Element Name）
                        if (node->getType() == NodeType::REFERENCE) {
                            auto attrs = node->getAttributes();
                            if (attrs.find("name") != attrs.end() &&
                                deleteTargets.find(attrs.at("name")) != deleteTargets.end()) {
                                return true;
                            }
                        }
                    }
                    return false;
                }),
            children.end()
        );
    }
    
    // 执行插入操作
    for (const auto& insertOp : insertOperations) {
        auto operate = std::static_pointer_cast<Operate>(insertOp);
        executeInsertOperation(target, operate);
    }
}

void WebGenerator::executeInsertOperation(std::shared_ptr<Node> target, 
                                          const std::shared_ptr<Operate>& insertOp) {
    auto position = insertOp->getPosition();
    auto insertTarget = insertOp->getTarget();
    auto& children = target->getChildren();
    
    switch (position) {
        case Operate::Position::AT_TOP:
            // 插入到开头
            for (auto it = insertOp->getChildren().rbegin(); 
                 it != insertOp->getChildren().rend(); ++it) {
                children.insert(children.begin(), (*it)->clone());
            }
            break;
            
        case Operate::Position::AT_BOTTOM:
            // 插入到末尾
            for (const auto& child : insertOp->getChildren()) {
                children.push_back(child->clone());
            }
            break;
            
        case Operate::Position::BEFORE:
        case Operate::Position::AFTER:
        case Operate::Position::REPLACE:
            {
                // 查找目标元素
                auto targetIt = std::find_if(children.begin(), children.end(),
                    [&insertTarget](const std::shared_ptr<Node>& node) {
                        if (node->getType() == NodeType::ELEMENT) {
                            auto elem = std::static_pointer_cast<Element>(node);
                            // 检查是否匹配 "tag[index]" 格式
                            size_t bracketPos = insertTarget.find('[');
                            if (bracketPos != std::string::npos) {
                                std::string tag = insertTarget.substr(0, bracketPos);
                                std::string indexStr = insertTarget.substr(bracketPos + 1, 
                                    insertTarget.find(']') - bracketPos - 1);
                                int targetIndex = std::stoi(indexStr);
                                
                                // 计算当前元素的索引
                                int currentIndex = 0;
                                for (auto it = elem->getParent()->getChildren().begin();
                                     it != elem->getParent()->getChildren().end(); ++it) {
                                    if ((*it)->getType() == NodeType::ELEMENT &&
                                        std::static_pointer_cast<Element>(*it)->getTagName() == tag) {
                                        if (*it == node && currentIndex == targetIndex) {
                                            return true;
                                        }
                                        currentIndex++;
                                    }
                                }
                            } else {
                                // 简单标签匹配
                                return elem->getTagName() == insertTarget;
                            }
                        }
                        return false;
                    });
                
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
                }
            }
            break;
    }
}

void WebGenerator::visitStyle(const std::shared_ptr<Style>& style) {
    // 检查是否是局部样式
    bool isScoped = false;
    Node* parent = style->getParent();
    if (parent && parent->getType() == NodeType::ELEMENT) {
        isScoped = true;
        
        // 为父元素生成作用域类
        if (currentScope_.empty()) {
            currentScope_ = generateUniqueId("scope");
        }
    }
    
    std::string css = style->getContent();
    
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

void WebGenerator::visitScript(const std::shared_ptr<Script>& script) {
    if (script->getScriptType() == Script::ScriptType::INLINE && script->isScoped()) {
        // 局部脚本
        std::string elementId = script->getScope();
        if (elementId.empty()) {
            // 如果没有作用域，尝试从父节点获取
            Node* parent = script->getParent();
            if (parent && parent->getType() == NodeType::ELEMENT) {
                auto element = static_cast<Element*>(parent);
                auto attrs = element->getAttributes();
                if (attrs.find("id") != attrs.end()) {
                    elementId = attrs.at("id");
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

} // namespace chtl