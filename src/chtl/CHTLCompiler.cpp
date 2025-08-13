#include "CHTLCompiler.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <stack>
#include <queue>

namespace chtl {

CHTLCompiler::CHTLCompiler() {
    // 初始化HTML元素映射
    initializeHTMLElements();
    
    // 初始化状态机
    currentState_ = CompilerState::INITIAL;
    
    // 初始化上下文栈
    contextStack_.push(ElementContext());
}

bool CHTLCompiler::compile(const std::string& sourceCode) {
    try {
        // 重置状态
        currentState_ = CompilerState::INITIAL;
        currentLineNumber_ = 0;
        htmlOutput_.clear();
        cssOutput_.clear();
        jsOutput_.clear();
        
        // 初始化HTML元素支持
        initializeHTMLElements();
        
        // 解析CHTL代码
        parseCHTL(sourceCode);
        
        // 后处理
        processTemplates();
        processCustomElements();
        processStyleGroups();
        processVariableGroups();
        processNamespaces();
        processImports();
        processConstraints();
        
        // 生成输出
        generateHTML();
        generateCSS();
        generateJavaScript();
        
        setCompiled();
        return true;
        
    } catch (const std::exception& e) {
        setError("CHTL编译失败: " + std::string(e.what()));
        return false;
    }
}

bool CHTLCompiler::validate(const std::string& sourceCode) {
    try {
        // 基本的CHTL语法验证
        std::istringstream iss(sourceCode);
        std::string line;
        size_t lineNumber = 0;
        
        while (std::getline(iss, line)) {
            lineNumber++;
            std::string trimmed = trim(line);
            
            if (trimmed.empty() || isComment(trimmed)) {
                continue;
            }
            
            // 验证基本的CHTL语法结构
            if (!validateCHTLLine(trimmed)) {
                setError("第" + std::to_string(lineNumber) + "行语法错误: " + trimmed);
                return false;
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        setError("CHTL验证失败: " + std::string(e.what()));
        return false;
    }
}

bool CHTLCompiler::validateCHTLLine(const std::string& line) {
    // 基本的CHTL语法验证
    if (line.empty()) {
        return true;
    }
    
    // 检查是否是有效的CHTL语法
    // 这里可以添加更详细的语法验证逻辑
    
    return true;
}

void CHTLCompiler::initializeHTMLElements() {
    // 单标签元素
    singleTagElements_ = {
        "img", "input", "br", "hr", "meta", "link", "area", "base", "col", "embed",
        "keygen", "param", "source", "track", "wbr"
    };
    
    // 块级元素
    blockElements_ = {
        "div", "p", "h1", "h2", "h3", "h4", "h5", "h6", "section", "article", "aside",
        "nav", "header", "footer", "main", "form", "table", "ul", "ol", "li", "dl", "dt", "dd",
        "blockquote", "pre", "address", "fieldset", "legend", "figure", "figcaption"
    };
    
    // 行内元素
    inlineElements_ = {
        "span", "a", "strong", "em", "b", "i", "u", "s", "mark", "small", "sub", "sup",
        "code", "kbd", "samp", "var", "cite", "abbr", "acronym", "dfn", "time", "q",
        "del", "ins", "ruby", "rt", "rp", "bdi", "bdo", "wbr"
    };
}

void CHTLCompiler::parseCHTL(const std::string& sourceCode) {
    std::istringstream iss(sourceCode);
    std::string line;
    size_t lineNumber = 0;
    
    while (std::getline(iss, line)) {
        lineNumber++;
        currentLineNumber_ = lineNumber;
        parseLine(line, lineNumber);
    }
    
    // 处理未关闭的元素
    processUnclosedElements();
}

void CHTLCompiler::parseLine(const std::string& line, size_t lineNumber) {
    std::string trimmed = trim(line);
    
    // 跳过空行和注释
    if (trimmed.empty() || isComment(trimmed)) {
        return;
    }
    
    // 根据当前状态处理行
    switch (currentState_) {
        case CompilerState::INITIAL:
            handleInitialState(trimmed, lineNumber);
            break;
        case CompilerState::ELEMENT:
            handleElementState(trimmed, lineNumber);
            break;
        case CompilerState::ATTRIBUTES:
            handleAttributesState(trimmed, lineNumber);
            break;
        case CompilerState::CONTENT:
            handleContentState(trimmed, lineNumber);
            break;
        case CompilerState::STYLE_BLOCK:
            handleStyleBlockState(trimmed, lineNumber);
            break;
        case CompilerState::TEXT_BLOCK:
            handleTextBlockState(trimmed, lineNumber);
            break;
        case CompilerState::SCRIPT_BLOCK:
            handleScriptBlockState(trimmed, lineNumber);
            break;
        case CompilerState::TEMPLATE:
            handleTemplateState(trimmed, lineNumber);
            break;
        case CompilerState::CUSTOM:
            handleCustomState(trimmed, lineNumber);
            break;
    }
}

void CHTLCompiler::handleInitialState(const std::string& line, size_t lineNumber) {
    // 检查是否是特殊指令
    if (line.find("[Template]") == 0) {
        currentState_ = CompilerState::TEMPLATE;
        parseTemplate(line);
        return;
    }
    
    if (line.find("[Custom]") == 0) {
        currentState_ = CompilerState::CUSTOM;
        parseCustom(line);
        return;
    }
    
    if (line.find("[Import]") == 0) {
        parseImport(line);
        return;
    }
    
    if (line.find("[Namespace]") == 0) {
        parseNamespace(line);
        return;
    }
    
    if (line.find("[Configuration]") == 0) {
        parseConfiguration(line);
        return;
    }
    
    if (line.find("[Origin]") == 0) {
        parseOrigin(line);
        return;
    }
    
    // 检查是否是元素开始
    if (line.find("{") != std::string::npos) {
        std::string elementName = extractElementName(line);
        if (!elementName.empty()) {
            startElement(elementName, line);
            currentState_ = CompilerState::ELEMENT;
        }
    }
}

void CHTLCompiler::handleElementState(const std::string& line, size_t lineNumber) {
    // 检查是否是属性
    if (line.find(":") != std::string::npos || line.find("=") != std::string::npos) {
        parseAttribute(line);
        return;
    }
    
    // 检查是否是样式块开始
    if (line.find("style") == 0 && line.find("{") != std::string::npos) {
        startStyleBlock();
        currentState_ = CompilerState::STYLE_BLOCK;
        return;
    }
    
    // 检查是否是文本块开始
    if (line.find("text") == 0 && line.find("{") != std::string::npos) {
        startTextBlock();
        currentState_ = CompilerState::TEXT_BLOCK;
        return;
    }
    
    // 检查是否是脚本块开始
    if (line.find("script") == 0 && line.find("{") != std::string::npos) {
        startScriptBlock();
        currentState_ = CompilerState::SCRIPT_BLOCK;
        return;
    }
    
    // 检查是否是元素结束
    if (line.find("}") != std::string::npos) {
        closeElement();
        if (contextStack_.size() <= 1) {
            currentState_ = CompilerState::INITIAL;
        }
        return;
    }
    
    // 检查是否是新的元素开始
    if (line.find("{") != std::string::npos) {
        std::string elementName = extractElementName(line);
        if (!elementName.empty()) {
            startElement(elementName, line);
        }
    }
}

void CHTLCompiler::handleStyleBlockState(const std::string& line, size_t lineNumber) {
    if (line.find("}") != std::string::npos) {
        endStyleBlock();
        currentState_ = CompilerState::ELEMENT;
        return;
    }
    
    parseCSSRule(line);
}

void CHTLCompiler::handleTextBlockState(const std::string& line, size_t lineNumber) {
    if (line.find("}") != std::string::npos) {
        endTextBlock();
        currentState_ = CompilerState::ELEMENT;
        return;
    }
    
    addTextContent(line);
}

void CHTLCompiler::handleScriptBlockState(const std::string& line, size_t lineNumber) {
    if (line.find("}") != std::string::npos) {
        endScriptBlock();
        currentState_ = CompilerState::ELEMENT;
        return;
    }
    
    addScriptContent(line);
}

void CHTLCompiler::handleTemplateState(const std::string& line, size_t lineNumber) {
    if (line.find("}") != std::string::npos) {
        endTemplate();
        currentState_ = CompilerState::INITIAL;
        return;
    }
    
    parseTemplateContent(line);
}

void CHTLCompiler::handleCustomState(const std::string& line, size_t lineNumber) {
    if (line.find("}") != std::string::npos) {
        endCustom();
        currentState_ = CompilerState::INITIAL;
        return;
    }
    
    parseCustomContent(line);
}

void CHTLCompiler::handleAttributesState(const std::string& line, size_t lineNumber) {
    // 处理属性状态
    if (line.find("}") != std::string::npos) {
        currentState_ = CompilerState::ELEMENT;
        return;
    }
    
    parseAttribute(line);
}

void CHTLCompiler::handleContentState(const std::string& line, size_t lineNumber) {
    // 处理内容状态
    if (line.find("}") != std::string::npos) {
        currentState_ = CompilerState::ELEMENT;
        return;
    }
    
    // 处理内容
    if (!contextStack_.empty()) {
        ElementContext& context = contextStack_.top();
        // 这里可以添加内容处理逻辑
    }
}

void CHTLCompiler::startElement(const std::string& elementName, const std::string& line) {
    ElementContext context;
    context.elementName = elementName;
    context.lineNumber = currentLineNumber_;
    
    // 生成唯一的类名和ID
    static size_t elementCounter = 0;
    elementCounter++;
    context.generatedClass = "chtl-element-" + std::to_string(elementCounter);
    
    contextStack_.push(context);
    
    // 开始HTML元素
    openElement();
}

void CHTLCompiler::openElement() {
    if (contextStack_.empty()) return;
    
    ElementContext& context = contextStack_.top();
    std::string elementName = context.elementName;
    
    // 生成HTML开始标签
    htmlOutput_ += "<" + elementName;
    
    // 添加属性
    if (!context.attributes.empty()) {
        for (const auto& attr : context.attributes) {
            htmlOutput_ += " " + attr.first + "=\"" + attr.second + "\"";
        }
    }
    
    // 添加生成的类名
    htmlOutput_ += " class=\"" + context.generatedClass + "\"";
    
    // 检查是否是单标签元素
    if (isSingleTagElement(elementName)) {
        htmlOutput_ += " />\n";
    } else {
        htmlOutput_ += ">\n";
    }
}

void CHTLCompiler::closeElement() {
    if (contextStack_.empty()) return;
    
    ElementContext& context = contextStack_.top();
    std::string elementName = context.elementName;
    
    // 检查是否是单标签元素
    if (!isSingleTagElement(elementName)) {
        htmlOutput_ += "</" + elementName + ">\n";
    }
    
    contextStack_.pop();
}

void CHTLCompiler::startTextBlock() {
    // 开始文本块
    currentStyleBlock_.clear();
}

void CHTLCompiler::endTextBlock() {
    // 结束文本块，将文本内容添加到HTML输出
    if (!contextStack_.empty()) {
        ElementContext& context = contextStack_.top();
        htmlOutput_ += currentStyleBlock_;
    }
    currentStyleBlock_.clear();
}

void CHTLCompiler::addTextContent(const std::string& line) {
    // 添加文本内容
    currentStyleBlock_ += line + "\n";
}

void CHTLCompiler::startStyleBlock() {
    // 开始样式块
    currentStyleBlock_.clear();
}

void CHTLCompiler::endStyleBlock() {
    // 结束样式块，处理样式内容
    processStyleBlockWithContext();
    currentStyleBlock_.clear();
}

void CHTLCompiler::parseCSSRule(const std::string& line) {
    // 解析CSS规则
    currentStyleBlock_ += line + "\n";
}

void CHTLCompiler::processStyleBlockWithContext() {
    if (contextStack_.empty()) return;
    
    ElementContext& context = contextStack_.top();
    
    // 处理样式块，支持上下文推导
    std::vector<std::string> selectors = parseSelectors(currentStyleBlock_);
    
    for (const std::string& selector : selectors) {
        std::string processedSelector = processSelectorWithContext(selector);
        std::string cssProperties = extractCSSProperties(currentStyleBlock_);
        
        // 生成CSS规则
        cssOutput_ += processedSelector + " {\n";
        cssOutput_ += cssProperties + "\n";
        cssOutput_ += "}\n\n";
    }
}

void CHTLCompiler::startScriptBlock() {
    // 开始脚本块
    currentScriptBlock_.clear();
}

void CHTLCompiler::endScriptBlock() {
    // 结束脚本块，将脚本内容添加到JavaScript输出
    jsOutput_ += currentScriptBlock_;
    currentScriptBlock_.clear();
}

void CHTLCompiler::addScriptContent(const std::string& line) {
    // 添加脚本内容
    currentScriptBlock_ += line + "\n";
}

void CHTLCompiler::parseAttribute(const std::string& line) {
    if (contextStack_.empty()) return;
    
    ElementContext& context = contextStack_.top();
    
    // 解析属性，支持 : 和 = 等价
    std::regex attrPattern(R"((\w+)\s*[:=]\s*([^;]+);?)");
    std::smatch match;
    
    if (std::regex_search(line, match, attrPattern)) {
        std::string attrName = match[1];
        std::string attrValue = trim(match[2]);
        
        // 移除引号
        if ((attrValue.front() == '"' && attrValue.back() == '"') ||
            (attrValue.front() == '\'' && attrValue.back() == '\'')) {
            attrValue = attrValue.substr(1, attrValue.length() - 2);
        }
        
        context.attributes[attrName] = attrValue;
        context.hasAttributes = true;
    }
}

void CHTLCompiler::parseTemplate(const std::string& line) {
    // 解析模板定义
    std::regex templatePattern(R"(\[Template\]\s*@(\w+)\s+(\w+))");
    std::smatch match;
    
    if (std::regex_search(line, match, templatePattern)) {
        TemplateInfo info;
        info.type = match[1];
        info.name = match[2];
        templates_[info.name] = info;
    }
}

void CHTLCompiler::parseTemplateContent(const std::string& line) {
    // 解析模板内容
    if (!templates_.empty()) {
        auto& lastTemplate = templates_.rbegin()->second;
        lastTemplate.content += line + "\n";
    }
}

void CHTLCompiler::endTemplate() {
    // 结束模板定义
    // 这里可以添加模板处理逻辑
}

void CHTLCompiler::parseCustom(const std::string& line) {
    // 解析自定义定义
    std::regex customPattern(R"(\[Custom\]\s*@(\w+)\s+(\w+))");
    std::smatch match;
    
    if (std::regex_search(line, match, customPattern)) {
        CustomInfo info;
        info.type = match[1];
        info.name = match[2];
        customs_[info.name] = info;
    }
}

void CHTLCompiler::parseCustomContent(const std::string& line) {
    // 解析自定义内容
    if (!customs_.empty()) {
        auto& lastCustom = customs_.rbegin()->second;
        lastCustom.content += line + "\n";
    }
}

void CHTLCompiler::endCustom() {
    // 结束自定义定义
    // 这里可以添加自定义处理逻辑
}

void CHTLCompiler::parseImport(const std::string& line) {
    // 解析导入语句
    // 这里可以添加导入处理逻辑
}

void CHTLCompiler::parseNamespace(const std::string& line) {
    // 解析命名空间
    // 这里可以添加命名空间处理逻辑
}

void CHTLCompiler::parseConfiguration(const std::string& line) {
    // 解析配置
    // 这里可以添加配置处理逻辑
}

void CHTLCompiler::parseOrigin(const std::string& line) {
    // 解析原始嵌入
    // 这里可以添加原始嵌入处理逻辑
}

std::vector<std::string> CHTLCompiler::parseSelectors(const std::string& cssRule) {
    std::vector<std::string> selectors;
    
    // 简单的选择器解析
    std::regex selectorPattern(R"(([.#]?\w+))");
    std::sregex_iterator iter(cssRule.begin(), cssRule.end(), selectorPattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        selectors.push_back(iter->str());
    }
    
    return selectors;
}

std::string CHTLCompiler::processSelectorWithContext(const std::string& selector) {
    if (contextStack_.empty()) return selector;
    
    ElementContext& context = contextStack_.top();
    
    // 处理上下文推导
    if (selector == "&") {
        return "." + context.generatedClass;
    }
    
    if (selector.find("&") == 0) {
        return "." + context.generatedClass + selector.substr(1);
    }
    
    return selector;
}

std::string CHTLCompiler::extractCSSProperties(const std::string& cssRule) {
    // 提取CSS属性
    std::string properties;
    
    // 简单的属性提取
    std::regex propertyPattern(R"((\w+)\s*:\s*([^;]+);?)");
    std::sregex_iterator iter(cssRule.begin(), cssRule.end(), propertyPattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        properties += "  " + iter->str(1) + ": " + iter->str(2) + ";\n";
    }
    
    return properties;
}

std::string CHTLCompiler::getCurrentElementSelector() {
    if (contextStack_.empty()) return "";
    
    ElementContext& context = contextStack_.top();
    return "." + context.generatedClass;
}

std::string CHTLCompiler::extractElementName(const std::string& line) {
    // 提取元素名称
    std::regex elementPattern(R"((\w+)\s*\{)");
    std::smatch match;
    
    if (std::regex_search(line, match, elementPattern)) {
        return match[1];
    }
    
    return "";
}

std::vector<std::string> CHTLCompiler::getAllHTMLElements() {
    std::vector<std::string> allElements;
    
    allElements.insert(allElements.end(), singleTagElements_.begin(), singleTagElements_.end());
    allElements.insert(allElements.end(), blockElements_.begin(), blockElements_.end());
    allElements.insert(allElements.end(), inlineElements_.begin(), inlineElements_.end());
    
    return allElements;
}

bool CHTLCompiler::isSingleTagElement(const std::string& elementName) {
    return singleTagElements_.find(elementName) != singleTagElements_.end();
}

void CHTLCompiler::processUnclosedElements() {
    // 处理未关闭的元素
    while (contextStack_.size() > 1) {
        closeElement();
    }
}

void CHTLCompiler::processTemplates() {
    // 处理模板
    // 这里可以添加模板处理逻辑
}

void CHTLCompiler::processCustomElements() {
    // 处理自定义元素
    // 这里可以添加自定义元素处理逻辑
}

void CHTLCompiler::processStyleGroups() {
    // 处理样式组
    // 这里可以添加样式组处理逻辑
}

void CHTLCompiler::processVariableGroups() {
    // 处理变量组
    // 这里可以添加变量组处理逻辑
}

void CHTLCompiler::processNamespaces() {
    // 处理命名空间
    // 这里可以添加命名空间处理逻辑
}

void CHTLCompiler::processImports() {
    // 处理导入
    // 这里可以添加导入处理逻辑
}

void CHTLCompiler::processConstraints() {
    // 处理约束
    // 这里可以添加约束处理逻辑
}

void CHTLCompiler::generateHTML() {
    // 生成HTML输出
    // HTML已经在解析过程中生成
}

void CHTLCompiler::generateCSS() {
    // 生成CSS输出
    // CSS已经在解析过程中生成
}

void CHTLCompiler::generateJavaScript() {
    // 生成JavaScript输出
    // JavaScript已经在解析过程中生成
}

void CHTLCompiler::reset() {
    currentState_ = CompilerState::INITIAL;
    currentLineNumber_ = 0;
    htmlOutput_.clear();
    cssOutput_.clear();
    jsOutput_.clear();
    
    while (!contextStack_.empty()) {
        contextStack_.pop();
    }
    
    contextStack_.push(ElementContext());
    
    templates_.clear();
    customs_.clear();
    
    currentCSSRule_.clear();
    currentStyleBlock_.clear();
    currentScriptBlock_.clear();
}

std::string CHTLCompiler::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool CHTLCompiler::isComment(const std::string& line) {
    std::string trimmed = trim(line);
    return trimmed.find("//") == 0 || 
           (trimmed.find("/*") == 0 && trimmed.find("*/") != std::string::npos);
}

} // namespace chtl