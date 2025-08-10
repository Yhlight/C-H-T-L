#include "Generator/Generator.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Import.h"
#include "Node/Export.h"
#include "Node/Config.h"
#include "Node/Namespace.h"
#include <algorithm>
#include <regex>

namespace chtl {

// CodeCollector 实现
void Generator::CodeCollector::append(const std::string& code) {
    stream_ << code;
}

void Generator::CodeCollector::appendLine(const std::string& code) {
    if (!code.empty()) {
        for (int i = 0; i < indentLevel_; ++i) {
            stream_ << "  ";
        }
        stream_ << code;
    }
    stream_ << "\n";
}

// Generator 实现
Generator::Generator(const GeneratorOptions& options) 
    : options_(options), jsRuntime_(std::make_unique<ChtlJsRuntime>()) {
}

GeneratorResult Generator::generate(const std::shared_ptr<Node>& ast) {
    // 清空之前的结果
    result_ = GeneratorResult();
    htmlCollector_.clear();
    cssCollector_.clear();
    jsCollector_.clear();
    componentMap_.clear();
    styleMap_.clear();
    scopeStack_.clear();
    jsRuntime_->reset();
    
    // 访问AST
    visit(ast);
    
    // 收集结果
    result_.html = htmlCollector_.getCode();
    result_.css = cssCollector_.getCode();
    result_.js = jsCollector_.getCode();
    
    return result_;
}

void Generator::visit(const std::shared_ptr<Node>& node) {
    if (!node) return;
    
    switch (node->getType()) {
        case NodeType::ELEMENT:
            visitElement(std::static_pointer_cast<Element>(node));
            break;
        case NodeType::TEXT:
            visitText(std::static_pointer_cast<Text>(node));
            break;
        case NodeType::CUSTOM:
            visitCustom(std::static_pointer_cast<Custom>(node));
            break;
        case NodeType::TEMPLATE:
            visitTemplate(std::static_pointer_cast<Template>(node));
            break;
        case NodeType::STYLE:
            visitStyle(std::static_pointer_cast<Style>(node));
            break;
        case NodeType::SCRIPT:
            visitScript(std::static_pointer_cast<Script>(node));
            break;
        case NodeType::IMPORT:
            visitImport(std::static_pointer_cast<Import>(node));
            break;
        case NodeType::EXPORT:
            visitExport(std::static_pointer_cast<Export>(node));
            break;
        case NodeType::CONFIG:
            visitConfig(std::static_pointer_cast<Config>(node));
            break;
        case NodeType::NAMESPACE:
            visitNamespace(std::static_pointer_cast<Namespace>(node));
            break;
        default:
            // 处理其他节点类型
            for (const auto& child : node->getChildren()) {
                visit(child);
            }
            break;
    }
}

void Generator::visitElement(const std::shared_ptr<Element>& element) {
    // 基础实现，子类会覆盖
    htmlCollector_.append("<" + element->getTag());
    
    // 属性
    for (const auto& [key, value] : element->getAttributes()) {
        htmlCollector_.append(" " + key + "=\"" + escape(value) + "\"");
    }
    
    htmlCollector_.append(">");
    
    // 子节点
    for (const auto& child : element->getChildren()) {
        visit(child);
    }
    
    htmlCollector_.append("</" + element->getTag() + ">");
}

void Generator::visitText(const std::shared_ptr<Text>& text) {
    htmlCollector_.append(escape(text->getContent()));
}

void Generator::visitCustom(const std::shared_ptr<Custom>& custom) {
    // 基础实现，子类会覆盖
    result_.warnings.push_back("Custom component not implemented: " + custom->getName());
}

void Generator::visitTemplate(const std::shared_ptr<Template>& tmpl) {
    // 模板定义，存储供后续使用
    componentMap_[tmpl->getName()] = tmpl->toString();
}

void Generator::visitStyle(const std::shared_ptr<Style>& style) {
    std::string css = style->getContent();
    
    // 添加作用域
    if (options_.scopeStyles && !currentScope_.empty()) {
        css = scopeSelector(css, currentScope_);
    }
    
    cssCollector_.appendLine(css);
}

void Generator::visitScript(const std::shared_ptr<Script>& script) {
    if (script->getScriptType() == Script::ScriptType::INLINE && script->isScoped()) {
        // 局部脚本由运行时处理
        std::string elementId = script->getScope();
        if (elementId.empty()) {
            elementId = generateUniqueId("element");
        }
        jsRuntime_->collectLocalScript(script->getContent(), elementId);
    } else {
        // 全局脚本
        jsCollector_.appendLine(script->generateWrappedCode());
    }
}

void Generator::visitImport(const std::shared_ptr<Import>& import) {
    // 处理导入，可能需要加载外部模块
    result_.warnings.push_back("Import handling not fully implemented: " + import->getSource());
}

void Generator::visitExport(const std::shared_ptr<Export>& exp) {
    // 处理导出
    for (const auto& item : exp->getExportedItems()) {
        // 记录导出项
    }
}

void Generator::visitConfig(const std::shared_ptr<Config>& config) {
    // 处理配置
    for (const auto& [key, value] : config->getConfigItems()) {
        if (key == "title") {
            // 设置页面标题等
        }
    }
}

void Generator::visitNamespace(const std::shared_ptr<Namespace>& ns) {
    // 处理命名空间
    std::string oldScope = currentScope_;
    currentScope_ = ns->getName();
    scopeStack_.push_back(currentScope_);
    
    for (const auto& child : ns->getChildren()) {
        visit(child);
    }
    
    scopeStack_.pop_back();
    currentScope_ = oldScope;
}

// 工具方法
std::string Generator::indent(int level) const {
    return std::string(level * 2, ' ');
}

std::string Generator::escape(const std::string& str) const {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += c; break;
        }
    }
    return result;
}

std::string Generator::generateUniqueId(const std::string& prefix) const {
    return prefix + "-" + std::to_string(++uniqueIdCounter_);
}

std::string Generator::scopeSelector(const std::string& css, const std::string& scope) const {
    // 简单的作用域实现，为每个选择器添加作用域类
    std::regex selectorRegex(R"(([^{]+)\{)");
    std::string scopedCss = css;
    
    scopedCss = std::regex_replace(scopedCss, selectorRegex, 
        [&scope](const std::smatch& match) {
            std::string selector = match[1].str();
            // 去除前后空白
            selector.erase(0, selector.find_first_not_of(" \t\n\r"));
            selector.erase(selector.find_last_not_of(" \t\n\r") + 1);
            
            // 添加作用域
            if (selector.find("@") == 0 || selector.find(":root") == 0) {
                // 不处理@规则和:root
                return match[0].str();
            }
            
            return "." + scope + " " + selector + "{";
        });
    
    return scopedCss;
}

// 工厂函数
std::unique_ptr<Generator> createGenerator(const std::string& platform, 
                                          const GeneratorOptions& options) {
    if (platform == "web") {
        return std::make_unique<WebGenerator>(options);
    } else if (platform == "react") {
        return std::make_unique<ReactGenerator>(options);
    } else if (platform == "vue") {
        return std::make_unique<VueGenerator>(options);
    } else {
        return std::make_unique<WebGenerator>(options); // 默认使用Web生成器
    }
}

} // namespace chtl