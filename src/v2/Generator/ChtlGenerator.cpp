#include "v2/Generator/ChtlGenerator.h"
#include "v2/ChtlJs/ChtlJsCompiler.h"
#include <iostream>
#include <regex>

namespace chtl::v2 {

ChtlGenerator::ChtlGenerator() = default;
ChtlGenerator::~ChtlGenerator() = default;

GenerateResult ChtlGenerator::generate(std::shared_ptr<Node> ast) {
    // 重置状态
    result_ = GenerateResult();
    htmlCollector_.clear();
    cssCollector_.clear();
    jsCollector_.clear();
    templates_.clear();
    currentParams_.clear();
    uniqueIdCounter_ = 0;
    
    try {
        // 第一遍：收集模板定义
        collectTemplates(ast.get());
        
        // 第二遍：生成代码
        ast->accept(*this);
        
        // 收集结果
        result_.html = htmlCollector_.getCode();
        result_.css = cssCollector_.getCode();
        result_.javascript = jsCollector_.getCode();
        
        // 生成文件映射
        if (!options_.inlineStyles && !result_.css.empty()) {
            result_.files[options_.cssFileName] = result_.css;
        }
        if (!options_.inlineScripts && !result_.javascript.empty()) {
            result_.files[options_.jsFileName] = result_.javascript;
        }
        
        result_.success = result_.errors.empty();
    } catch (const std::exception& e) {
        addError(std::string("Generation error: ") + e.what());
        result_.success = false;
    }
    
    return result_;
}

void ChtlGenerator::setOptions(const GeneratorOptions& options) {
    options_ = options;
}

void ChtlGenerator::visitDocument(Document* node) {
    // Document 只是根节点，直接处理子节点
    for (auto& child : node->getChildren()) {
        child->accept(*this);
    }
}

void ChtlGenerator::visitElement(Element* node) {
    // 处理局部样式
    if (!node->getLocalStyle().empty()) {
        processLocalStyle(node);
    }
    
    // 生成开始标签
    generateElementStart(node);
    
    // 处理子节点
    htmlCollector_.indent();
    for (auto& child : node->getChildren()) {
        child->accept(*this);
    }
    htmlCollector_.dedent();
    
    // 生成结束标签
    generateElementEnd(node);
}

void ChtlGenerator::visitText(Text* node) {
    htmlCollector_.appendIndent();
    
    std::string content = node->getContent();
    
    // 处理模板参数引用
    if (inTemplate_ && content.size() > 2 && 
        content.front() == '{' && content.back() == '}') {
        // 这是一个参数引用
        std::string paramName = content.substr(1, content.size() - 2);
        auto it = currentParams_.find(paramName);
        if (it != currentParams_.end()) {
            content = it->second;
        } else {
            addWarning("Unknown template parameter: " + paramName);
        }
    }
    
    // HTML 转义
    std::string escaped;
    for (char c : content) {
        switch (c) {
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '&': escaped += "&amp;"; break;
            case '"': escaped += "&quot;"; break;
            default: escaped += c;
        }
    }
    
    htmlCollector_.appendLine(escaped);
}

void ChtlGenerator::visitStyle(Style* node) {
    if (node->isGlobal()) {
        // 全局样式直接添加到 CSS 收集器
        cssCollector_.appendLine(node->getCssContent());
    }
    // 局部样式已经在 Element 中处理
}

void ChtlGenerator::visitScript(Script* node) {
    std::string content = node->getJsContent();
    
    if (node->hasChtlJs()) {
        // 使用 CHTL-JS 编译器处理
        chtljs::ChtlJsCompiler chtlJsCompiler;
        
        // 准备上下文
        std::map<std::string, std::string> context;
        // TODO: 从当前上下文提取元素信息
        
        auto chtlJsResult = chtlJsCompiler.compile(content, context);
        
        if (chtlJsResult.success) {
            content = chtlJsResult.javascript;
            
            // 添加运行时依赖
            if (!chtlJsResult.dependencies.empty()) {
                // 确保运行时库被包含
                if (jsCollector_.getCode().find("window.chtl") == std::string::npos) {
                    // 在最开始添加运行时库
                    std::string runtime = chtljs::ChtlJsRuntime::generateFullRuntime();
                    std::string currentJs = jsCollector_.getCode();
                    jsCollector_.clear();
                    jsCollector_.appendLine(runtime);
                    jsCollector_.append(currentJs);
                }
            }
        } else {
            for (const auto& error : chtlJsResult.errors) {
                addError("CHTL-JS: " + error);
            }
        }
        
        for (const auto& warning : chtlJsResult.warnings) {
            addWarning("CHTL-JS: " + warning);
        }
    }
    
    if (node->isGlobal()) {
        // 全局脚本
        jsCollector_.appendLine(content);
    } else {
        // 局部脚本，内联到 HTML
        htmlCollector_.appendIndent();
        htmlCollector_.appendLine("<script>");
        htmlCollector_.indent();
        htmlCollector_.appendIndent();
        htmlCollector_.appendLine(content);
        htmlCollector_.dedent();
        htmlCollector_.appendIndent();
        htmlCollector_.appendLine("</script>");
    }
}

void ChtlGenerator::visitTemplate(Template* node) {
    // 模板定义已经在 collectTemplates 中处理
    // 这里不生成任何代码
}

void ChtlGenerator::visitReference(Reference* node) {
    if (node->getReferenceType() == "@Element" || 
        node->getReferenceType() == "AT_ELEMENT") {
        expandTemplateReference(node);
    } else {
        addWarning("Unsupported reference type: " + node->getReferenceType());
    }
}

void ChtlGenerator::generateElementStart(Element* node) {
    htmlCollector_.appendIndent();
    htmlCollector_.append("<" + node->getTag());
    
    // ID
    if (!node->getId().empty()) {
        htmlCollector_.append(" id=\"" + node->getId() + "\"");
    }
    
    // 类名
    if (!node->getClasses().empty()) {
        htmlCollector_.append(" class=\"");
        bool first = true;
        for (const auto& cls : node->getClasses()) {
            if (!first) htmlCollector_.append(" ");
            htmlCollector_.append(cls);
            first = false;
        }
        htmlCollector_.append("\"");
    }
    
    // 其他属性
    generateAttributes(node);
    
    htmlCollector_.appendLine(">");
}

void ChtlGenerator::generateElementEnd(Element* node) {
    htmlCollector_.appendIndent();
    htmlCollector_.appendLine("</" + node->getTag() + ">");
}

void ChtlGenerator::generateAttributes(Element* node) {
    for (const auto& [name, value] : node->getAttributes()) {
        htmlCollector_.append(" " + name);
        if (!value.empty()) {
            htmlCollector_.append("=\"" + value + "\"");
        }
    }
}

void ChtlGenerator::processLocalStyle(Element* node) {
    // 生成唯一类名
    std::string uniqueClass = generateUniqueClass();
    
    // 添加类名到元素
    const_cast<Element*>(node)->addClass(uniqueClass);
    
    // 生成 CSS 规则
    std::string css = "." + uniqueClass + " {\n";
    css += node->getLocalStyle();
    if (!css.empty() && css.back() != '\n') {
        css += '\n';
    }
    css += "}\n";
    
    cssCollector_.appendLine(css);
}

std::string ChtlGenerator::generateUniqueClass() {
    return "chtl-" + std::to_string(++uniqueIdCounter_);
}

void ChtlGenerator::expandTemplateReference(Reference* node) {
    // 查找模板
    auto it = templates_.find(node->getName());
    if (it == templates_.end()) {
        addError("Template not found: " + node->getName());
        return;
    }
    
    Template* templ = it->second;
    
    // 准备参数
    std::map<std::string, std::string> oldParams = currentParams_;
    currentParams_.clear();
    
    // 绑定参数
    const auto& params = templ->getParameters();
    const auto& args = node->getArguments();
    
    for (size_t i = 0; i < params.size(); ++i) {
        if (i < args.size()) {
            currentParams_[params[i].first] = args[i];
        } else if (!params[i].second.empty()) {
            // 使用默认值
            currentParams_[params[i].first] = params[i].second;
        } else {
            addWarning("Missing argument for parameter: " + params[i].first);
        }
    }
    
    // 标记进入模板
    bool oldInTemplate = inTemplate_;
    inTemplate_ = true;
    
    // 展开模板内容
    for (auto& child : templ->getChildren()) {
        child->accept(*this);
    }
    
    // 恢复状态
    inTemplate_ = oldInTemplate;
    currentParams_ = oldParams;
}

std::string ChtlGenerator::processTemplateContent(const std::string& content,
                                                 const std::map<std::string, std::string>& params) {
    std::string result = content;
    
    // 简单的参数替换
    for (const auto& [param, value] : params) {
        std::string placeholder = "{" + param + "}";
        size_t pos = 0;
        while ((pos = result.find(placeholder, pos)) != std::string::npos) {
            result.replace(pos, placeholder.length(), value);
            pos += value.length();
        }
    }
    
    return result;
}

void ChtlGenerator::collectTemplates(Node* node) {
    if (node->getType() == NodeType::TEMPLATE) {
        Template* templ = dynamic_cast<Template*>(node);
        if (templ) {
            templates_[templ->getName()] = templ;
        }
    }
    
    // 递归收集子节点的模板
    for (auto& child : node->getChildren()) {
        collectTemplates(child.get());
    }
}

void ChtlGenerator::addError(const std::string& message) {
    result_.errors.push_back(message);
}

void ChtlGenerator::addWarning(const std::string& message) {
    result_.warnings.push_back(message);
}

} // namespace chtl::v2