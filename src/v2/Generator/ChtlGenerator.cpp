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
    std::string localStyle = node->getLocalStyle();
    if (localStyle.empty()) return;
    
    // 解析局部样式内容
    std::string inlineStyles;
    std::string globalStyles;
    std::vector<std::string> autoClasses;
    std::string autoId;
    
    // 简单的解析器状态
    enum State { NORMAL, IN_SELECTOR, IN_BLOCK };
    State state = NORMAL;
    std::string currentSelector;
    std::string currentBlock;
    int braceDepth = 0;
    
    for (size_t i = 0; i < localStyle.length(); ++i) {
        char ch = localStyle[i];
        
        if (state == NORMAL) {
            if (ch == '.' || ch == '#' || ch == '&') {
                // 开始选择器
                state = IN_SELECTOR;
                currentSelector = ch;
            } else if (ch == '{') {
                // 直接的属性块（内联样式）
                size_t endBrace = findMatchingBrace(localStyle, i);
                if (endBrace != std::string::npos) {
                    inlineStyles = localStyle.substr(i + 1, endBrace - i - 1);
                    i = endBrace;
                }
            } else if (!std::isspace(ch)) {
                // 可能是直接的属性（内联样式）
                size_t propEnd = localStyle.find_first_of(";}", i);
                if (propEnd != std::string::npos) {
                    std::string prop = localStyle.substr(i, propEnd - i + 1);
                    if (prop.find(':') != std::string::npos) {
                        inlineStyles += prop;
                        if (localStyle[propEnd] != '}') {
                            inlineStyles += " ";
                        }
                        i = propEnd;
                    }
                }
            }
        } else if (state == IN_SELECTOR) {
            if (ch == '{') {
                // 选择器结束，开始块
                state = IN_BLOCK;
                braceDepth = 1;
                currentBlock = "";
            } else {
                currentSelector += ch;
            }
        } else if (state == IN_BLOCK) {
            if (ch == '{') {
                braceDepth++;
            } else if (ch == '}') {
                braceDepth--;
                if (braceDepth == 0) {
                    // 块结束，处理选择器和内容
                    processSelector(currentSelector, currentBlock, node, 
                                  autoClasses, autoId, globalStyles);
                    state = NORMAL;
                    currentSelector.clear();
                    currentBlock.clear();
                    continue;
                }
            }
            currentBlock += ch;
        }
    }
    
    // 应用内联样式
    if (!inlineStyles.empty()) {
        // 清理样式字符串
        inlineStyles = trim(inlineStyles);
        // 添加到元素的 style 属性
        const_cast<Element*>(node)->setAttribute("style", inlineStyles);
    }
    
    // 应用自动类名
    for (const auto& className : autoClasses) {
        const_cast<Element*>(node)->addClass(className);
    }
    
    // 应用自动 ID
    if (!autoId.empty()) {
        const_cast<Element*>(node)->setId(autoId);
    }
    
    // 添加全局样式
    if (!globalStyles.empty()) {
        cssCollector_.appendLine(globalStyles);
    }
}

void ChtlGenerator::processSelector(const std::string& selector, 
                                   const std::string& content,
                                   Element* node,
                                   std::vector<std::string>& autoClasses,
                                   std::string& autoId,
                                   std::string& globalStyles) {
    std::string trimmedSelector = trim(selector);
    std::string trimmedContent = trim(content);
    
    if (trimmedSelector.empty() || trimmedContent.empty()) return;
    
    // 处理类选择器
    if (trimmedSelector[0] == '.') {
        std::string className = trimmedSelector.substr(1);
        // 去除可能的伪类部分
        size_t colonPos = className.find(':');
        if (colonPos != std::string::npos) {
            className = className.substr(0, colonPos);
        }
        
        if (!className.empty()) {
            // 添加到自动类名列表
            if (std::find(autoClasses.begin(), autoClasses.end(), className) == autoClasses.end()) {
                autoClasses.push_back(className);
            }
        }
        
        // 添加到全局样式
        globalStyles += trimmedSelector + " {\n" + trimmedContent + "\n}\n";
    }
    // 处理 ID 选择器
    else if (trimmedSelector[0] == '#') {
        std::string id = trimmedSelector.substr(1);
        // 去除可能的伪类部分
        size_t colonPos = id.find(':');
        if (colonPos != std::string::npos) {
            id = id.substr(0, colonPos);
        }
        
        if (!id.empty() && autoId.empty()) {
            autoId = id;
        }
        
        // 添加到全局样式
        globalStyles += trimmedSelector + " {\n" + trimmedContent + "\n}\n";
    }
    // 处理 & 选择器
    else if (trimmedSelector[0] == '&') {
        // 需要知道元素的类名或 ID
        std::string replacement;
        
        // 优先使用类名
        if (!autoClasses.empty()) {
            replacement = "." + autoClasses[0];
        } else if (!node->getClasses().empty()) {
            replacement = "." + node->getClasses()[0];
        } else if (!autoId.empty()) {
            replacement = "#" + autoId;
        } else if (!node->getId().empty()) {
            replacement = "#" + node->getId();
        }
        
        if (!replacement.empty()) {
            // 替换 & 为实际的选择器
            std::string actualSelector = replacement + trimmedSelector.substr(1);
            globalStyles += actualSelector + " {\n" + trimmedContent + "\n}\n";
        }
    }
}

size_t ChtlGenerator::findMatchingBrace(const std::string& str, size_t start) {
    int depth = 1;
    for (size_t i = start + 1; i < str.length(); ++i) {
        if (str[i] == '{') depth++;
        else if (str[i] == '}') {
            depth--;
            if (depth == 0) return i;
        }
    }
    return std::string::npos;
}

std::string ChtlGenerator::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
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