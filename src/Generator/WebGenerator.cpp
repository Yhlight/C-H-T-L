#include "Generator/Generator.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Custom.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Reference.h"
#include "Node/Operate.h"
#include <sstream>
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
    // 检查是否是引用
    if (custom->getDefinitionType() == Custom::DefinitionType::REFERENCE) {
        // 查找组件定义并展开
        processCustomComponent(custom);
    } else {
        // 这是组件定义，存储起来
        componentMap_[custom->getName()] = custom->toString();
        
        // 如果有render内容，访问它
        if (!custom->getChildren().empty()) {
            for (const auto& child : custom->getChildren()) {
                if (child->getType() == NodeType::OPERATE) {
                    auto operate = std::static_pointer_cast<Operate>(child);
                    if (operate->getChildren().size() > 0 && 
                        operate->getChildren()[0]->toString() == "render") {
                        // 这是render块，不直接生成代码
                        continue;
                    }
                }
            }
        }
    }
}

void WebGenerator::processCustomComponent(const std::shared_ptr<Custom>& custom) {
    const std::string& componentName = custom->getName();
    
    // 查找组件定义
    auto it = componentMap_.find(componentName);
    if (it == componentMap_.end()) {
        // 未找到组件定义
        result_.warnings.push_back("Component not found: " + componentName);
        htmlCollector_.append("<!-- Component not found: " + componentName + " -->");
        return;
    }
    
    // 获取属性
    std::unordered_map<std::string, std::string> props;
    for (const auto& child : custom->getChildren()) {
        if (child->getType() == NodeType::OPERATE) {
            auto operate = std::static_pointer_cast<Operate>(child);
            if (operate->getChildren().size() >= 2) {
                std::string key = operate->getChildren()[0]->toString();
                std::string value = operate->getChildren()[1]->toString();
                props[key] = value;
            }
        }
    }
    
    // 展开组件
    expandComponent(componentName, props, custom->getChildren());
}

void WebGenerator::expandComponent(const std::string& componentName,
                                   const std::unordered_map<std::string, std::string>& props,
                                   const std::vector<std::shared_ptr<Node>>& children) {
    // 简化实现：直接输出div包装
    htmlCollector_.append("<div class=\"chtl-component-" + componentName + "\"");
    
    // 添加data属性保存props
    for (const auto& [key, value] : props) {
        htmlCollector_.append(" data-" + key + "=\"" + escape(value) + "\"");
    }
    
    htmlCollector_.append(">");
    
    // 处理子节点（slot内容）
    for (const auto& child : children) {
        // 跳过属性节点
        if (child->getType() != NodeType::OPERATE) {
            visit(child);
        }
    }
    
    htmlCollector_.append("</div>");
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