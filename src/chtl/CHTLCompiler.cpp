#include "CHTLCompiler.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <stack>

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
        reset();
        
        // 解析CHTL代码
        parseCHTL(sourceCode);
        
        // 处理模板
        processTemplates();
        
        // 处理自定义元素
        processCustomElements();
        
        // 处理样式组
        processStyleGroups();
        
        // 处理变量组
        processVariableGroups();
        
        // 处理命名空间
        processNamespaces();
        
        // 处理导入
        processImports();
        
        // 处理约束
        processConstraints();
        
        // 生成输出
        generateHTML();
        generateCSS();
        generateJavaScript();
        
        setSuccess(true);
        return true;
        
    } catch (const std::exception& e) {
        setError("CHTL编译失败: " + std::string(e.what()));
        return false;
    }
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
        "header", "footer", "nav", "main", "form", "table", "ul", "ol", "li", "blockquote",
        "pre", "code", "figure", "figcaption", "details", "summary"
    };
    
    // 行内元素
    inlineElements_ = {
        "span", "a", "strong", "em", "b", "i", "u", "mark", "small", "del", "ins",
        "sub", "sup", "code", "kbd", "samp", "var", "time", "abbr", "cite", "q"
    };
}

void CHTLCompiler::parseCHTL(const std::string& sourceCode) {
    // 简单的词法分析器，按行解析
    std::istringstream iss(sourceCode);
    std::string line;
    
    while (std::getline(iss, line)) {
        currentLineNumber_++;
        parseLine(line, currentLineNumber_);
    }
    
    // 处理未闭合的元素
    processUnclosedElements();
}

void CHTLCompiler::parseLine(const std::string& line, size_t lineNumber) {
    std::string trimmed = trim(line);
    if (trimmed.empty() || isComment(trimmed)) {
        return;
    }
    
    // 状态机处理
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
    } else if (line.find("[Custom]") == 0) {
        currentState_ = CompilerState::CUSTOM;
        parseCustom(line);
    } else if (line.find("[Import]") == 0) {
        parseImport(line);
    } else if (line.find("[Namespace]") == 0) {
        parseNamespace(line);
    } else if (line.find("[Configuration]") == 0) {
        parseConfiguration(line);
    } else if (line.find("[Origin]") == 0) {
        parseOrigin(line);
    } else {
        // 检查是否是HTML元素
        std::string elementName = extractElementName(line);
        if (!elementName.empty()) {
            currentState_ = CompilerState::ELEMENT;
            startElement(elementName, line);
        }
    }
}

void CHTLCompiler::handleElementState(const std::string& line, size_t lineNumber) {
    if (line.find('{') != std::string::npos) {
        // 开始元素内容
        currentState_ = CompilerState::CONTENT;
        openElement();
    } else if (line.find(':') != std::string::npos || line.find('=') != std::string::npos) {
        // 属性定义
        currentState_ = CompilerState::ATTRIBUTES;
        parseAttribute(line);
    } else if (line.find(';') != std::string::npos) {
        // 自闭合元素
        closeElement();
        currentState_ = CompilerState::INITIAL;
    }
}

void CHTLCompiler::handleAttributesState(const std::string& line, size_t lineNumber) {
    if (line.find('{') != std::string::npos) {
        // 开始元素内容
        currentState_ = CompilerState::CONTENT;
        openElement();
    } else if (line.find(':') != std::string::npos || line.find('=') != std::string::npos) {
        // 继续解析属性
        parseAttribute(line);
    }
}

void CHTLCompiler::handleContentState(const std::string& line, size_t lineNumber) {
    if (line.find('}') != std::string::npos) {
        // 结束元素内容
        closeElement();
        currentState_ = CompilerState::INITIAL;
    } else if (line.find("text") == 0) {
        // 文本块
        currentState_ = CompilerState::TEXT_BLOCK;
        startTextBlock();
    } else if (line.find("style") == 0) {
        // 样式块
        currentState_ = CompilerState::STYLE_BLOCK;
        startStyleBlock();
    } else if (line.find("script") == 0) {
        // 脚本块
        currentState_ = CompilerState::SCRIPT_BLOCK;
        startScriptBlock();
    } else if (line.find('@') == 0) {
        // 模板使用
        parseTemplateUsage(line);
    } else {
        // 嵌套元素
        std::string elementName = extractElementName(line);
        if (!elementName.empty()) {
            startElement(elementName, line);
        }
    }
}

void CHTLCompiler::handleStyleBlockState(const std::string& line, size_t lineNumber) {
    if (line.find('}') != std::string::npos) {
        // 结束样式块
        endStyleBlock();
        currentState_ = CompilerState::CONTENT;
    } else {
        // 解析CSS规则
        parseCSSRule(line);
    }
}

void CHTLCompiler::handleTextBlockState(const std::string& line, size_t lineNumber) {
    if (line.find('}') != std::string::npos) {
        // 结束文本块
        endTextBlock();
        currentState_ = CompilerState::CONTENT;
    } else {
        // 添加文本内容
        addTextContent(line);
    }
}

void CHTLCompiler::handleScriptBlockState(const std::string& line, size_t lineNumber) {
    if (line.find('}') != std::string::npos) {
        // 结束脚本块
        endScriptBlock();
        currentState_ = CompilerState::CONTENT;
    } else {
        // 添加脚本内容
        addScriptContent(line);
    }
}

void CHTLCompiler::handleTemplateState(const std::string& line, size_t lineNumber) {
    if (line.find('}') != std::string::npos) {
        // 结束模板定义
        endTemplate();
        currentState_ = CompilerState::INITIAL;
    } else {
        // 继续解析模板内容
        parseTemplateContent(line);
    }
}

void CHTLCompiler::handleCustomState(const std::string& line, size_t lineNumber) {
    if (line.find('}') != std::string::npos) {
        // 结束自定义定义
        endCustom();
        currentState_ = CompilerState::INITIAL;
    } else {
        // 继续解析自定义内容
        parseCustomContent(line);
    }
}

void CHTLCompiler::startElement(const std::string& elementName, const std::string& line) {
    ElementContext context;
    context.elementName = elementName;
    context.lineNumber = currentLineNumber_;
    context.hasAttributes = line.find(':') != std::string::npos || line.find('=') != std::string::npos;
    
    contextStack_.push(context);
    
    // 生成HTML开始标签
    std::string htmlTag = "<" + elementName;
    if (context.hasAttributes) {
        htmlTag += ">";
    } else {
        htmlTag += ">";
    }
    
    htmlOutput_ += htmlTag + "\n";
}

void CHTLCompiler::openElement() {
    // 元素开始，不需要额外处理
}

void CHTLCompiler::closeElement() {
    if (!contextStack_.empty()) {
        ElementContext context = contextStack_.top();
        contextStack_.pop();
        
        // 生成HTML结束标签
        if (!isSingleTagElement(context.elementName)) {
            htmlOutput_ += "</" + context.elementName + ">\n";
        }
    }
}

void CHTLCompiler::startTextBlock() {
    // 开始文本块，不需要额外处理
}

void CHTLCompiler::endTextBlock() {
    // 文本块结束，内容已经在addTextContent中添加
}

void CHTLCompiler::startStyleBlock() {
    // 开始样式块
    currentStyleBlock_ = "";
}

void CHTLCompiler::endStyleBlock() {
    // 处理样式块内容，包括上下文推导
    processStyleBlockWithContext();
}

void CHTLCompiler::startScriptBlock() {
    // 开始脚本块
    currentScriptBlock_ = "";
}

void CHTLCompiler::endScriptBlock() {
    // 脚本块结束，内容已经在addScriptContent中添加
    jsOutput_ += currentScriptBlock_ + "\n";
}

void CHTLCompiler::parseAttribute(const std::string& line) {
    // 解析属性 line: "id: box;" 或 "id = box;"
    std::regex attrPattern(R"((\w+)\s*[:=]\s*([^;]+);?)");
    std::smatch match;
    
    if (std::regex_search(line, match, attrPattern)) {
        std::string attrName = match[1].str();
        std::string attrValue = trim(match[2].str());
        
        // 移除引号
        if ((attrValue.front() == '"' && attrValue.back() == '"') ||
            (attrValue.front() == '\'' && attrValue.back() == '\'')) {
            attrValue = attrValue.substr(1, attrValue.length() - 2);
        }
        
        // 添加到当前元素的属性
        if (!contextStack_.empty()) {
            ElementContext& context = contextStack_.top();
            context.attributes[attrName] = attrValue;
            
            // 更新HTML标签
            updateHTMLElementAttributes(context);
        }
    }
}

void CHTLCompiler::parseCSSRule(const std::string& line) {
    // 解析CSS规则，支持上下文推导
    if (line.find('.') == 0 || line.find('#') == 0 || line.find('&') == 0) {
        // 选择器规则
        currentCSSRule_ = line;
    } else if (line.find(':') != std::string::npos && line.find(';') != std::string::npos) {
        // CSS属性
        if (!currentCSSRule_.empty()) {
            currentCSSRule_ += "\n" + line;
        }
    }
}

void CHTLCompiler::addTextContent(const std::string& line) {
    std::string trimmed = trim(line);
    if (!trimmed.empty()) {
        htmlOutput_ += trimmed + "\n";
    }
}

void CHTLCompiler::addScriptContent(const std::string& line) {
    currentScriptBlock_ += line + "\n";
}

void CHTLCompiler::processStyleBlockWithContext() {
    // 处理样式块，包括上下文推导
    if (currentCSSRule_.empty()) {
        return;
    }
    
    // 解析选择器
    std::vector<std::string> selectors = parseSelectors(currentCSSRule_);
    
    // 为每个选择器生成CSS
    for (const auto& selector : selectors) {
        std::string processedSelector = processSelectorWithContext(selector);
        std::string cssProperties = extractCSSProperties(currentCSSRule_);
        
        cssOutput_ += processedSelector + " {\n";
        cssOutput_ += cssProperties + "\n";
        cssOutput_ += "}\n\n";
    }
    
    // 清空当前CSS规则
    currentCSSRule_.clear();
}

std::vector<std::string> CHTLCompiler::parseSelectors(const std::string& cssRule) {
    std::vector<std::string> selectors;
    
    // 简单的选择器解析
    std::istringstream iss(cssRule);
    std::string line;
    
    while (std::getline(iss, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty()) continue;
        
        if (trimmed.find('.') == 0 || trimmed.find('#') == 0 || trimmed.find('&') == 0) {
            selectors.push_back(trimmed);
        }
    }
    
    return selectors;
}

std::string CHTLCompiler::processSelectorWithContext(const std::string& selector) {
    // 处理上下文推导
    if (selector.find('&') == 0) {
        // 上下文推导：& 表示当前元素的类名或ID
        std::string contextSelector = getCurrentElementSelector();
        if (!contextSelector.empty()) {
            return contextSelector + selector.substr(1);
        }
    }
    
    return selector;
}

std::string CHTLCompiler::getCurrentElementSelector() {
    // 获取当前元素的CSS选择器
    if (!contextStack_.empty()) {
        const ElementContext& context = contextStack_.top();
        
        // 优先使用ID，其次使用类名
        auto idIt = context.attributes.find("id");
        if (idIt != context.attributes.end()) {
            return "#" + idIt->second;
        }
        
        auto classIt = context.attributes.find("class");
        if (classIt != context.attributes.end()) {
            return "." + classIt->second;
        }
        
        // 如果没有ID或类名，生成一个唯一的类名
        std::string generatedClass = "chtl-" + context.elementName + "-" + std::to_string(context.lineNumber);
        return "." + generatedClass;
    }
    
    return "";
}

std::string CHTLCompiler::extractCSSProperties(const std::string& cssRule) {
    std::string properties;
    std::istringstream iss(cssRule);
    std::string line;
    
    while (std::getline(iss, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty()) continue;
        
        if (trimmed.find(':') != std::string::npos && trimmed.find(';') != std::string::npos) {
            properties += "  " + trimmed + "\n";
        }
    }
    
    return properties;
}

void CHTLCompiler::updateHTMLElementAttributes(const ElementContext& context) {
    // 更新HTML元素的属性
    // 这里需要重新生成HTML标签，简化处理
}

void CHTLCompiler::parseTemplate(const std::string& line) {
    // 解析模板定义
    std::regex templatePattern(R"(\[Template\]\s*@(\w+)\s+(\w+))");
    std::smatch match;
    
    if (std::regex_search(line, match, templatePattern)) {
        std::string templateType = match[1].str();
        std::string templateName = match[2].str();
        
        // 存储模板信息
        TemplateInfo templateInfo;
        templateInfo.type = templateType;
        templateInfo.name = templateName;
        templates_[templateName] = templateInfo;
    }
}

void CHTLCompiler::parseCustom(const std::string& line) {
    // 解析自定义定义
    std::regex customPattern(R"(\[Custom\]\s*@(\w+)\s+(\w+))");
    std::smatch match;
    
    if (std::regex_search(line, match, customPattern)) {
        std::string customType = match[1].str();
        std::string customName = match[2].str();
        
        // 存储自定义信息
        CustomInfo customInfo;
        customInfo.type = customType;
        customInfo.name = customName;
        customs_[customName] = customInfo;
    }
}

void CHTLCompiler::parseImport(const std::string& line) {
    // 解析导入语句
    // 简化实现
}

void CHTLCompiler::parseNamespace(const std::string& line) {
    // 解析命名空间
    // 简化实现
}

void CHTLCompiler::parseConfiguration(const std::string& line) {
    // 解析配置
    // 简化实现
}

void CHTLCompiler::parseOrigin(const std::string& line) {
    // 解析原始嵌入
    // 简化实现
}

void CHTLCompiler::parseTemplateUsage(const std::string& line) {
    // 解析模板使用
    // 简化实现
}

void CHTLCompiler::parseTemplateContent(const std::string& line) {
    // 解析模板内容
    // 简化实现
}

void CHTLCompiler::parseCustomContent(const std::string& line) {
    // 解析自定义内容
    // 简化实现
}

void CHTLCompiler::endTemplate() {
    // 结束模板定义
    // 简化实现
}

void CHTLCompiler::endCustom() {
    // 结束自定义定义
    // 简化实现
}

void CHTLCompiler::processUnclosedElements() {
    // 处理未闭合的元素
    while (!contextStack_.empty()) {
        closeElement();
    }
}

std::string CHTLCompiler::extractElementName(const std::string& line) {
    std::string trimmed = trim(line);
    
    // 检查是否是HTML元素
    for (const auto& element : getAllHTMLElements()) {
        if (trimmed.find(element) == 0) {
            return element;
        }
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
    return std::find(singleTagElements_.begin(), singleTagElements_.end(), elementName) != singleTagElements_.end();
}

bool CHTLCompiler::isComment(const std::string& line) {
    std::string trimmed = trim(line);
    return trimmed.find("//") == 0 || trimmed.find("/**/") == 0;
}

std::string CHTLCompiler::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

void CHTLCompiler::reset() {
    htmlOutput_.clear();
    cssOutput_.clear();
    jsOutput_.clear();
    currentState_ = CompilerState::INITIAL;
    
    while (!contextStack_.empty()) {
        contextStack_.pop();
    }
    contextStack_.push(ElementContext());
    
    templates_.clear();
    customs_.clear();
    
    currentCSSRule_.clear();
    currentStyleBlock_.clear();
    currentScriptBlock_.clear();
    
    setSuccess(false);
    setError("");
}

void CHTLCompiler::processTemplates() {
    // 处理模板
    // 简化实现
}

void CHTLCompiler::processCustomElements() {
    // 处理自定义元素
    // 简化实现
}

void CHTLCompiler::processStyleGroups() {
    // 处理样式组
    // 简化实现
}

void CHTLCompiler::processVariableGroups() {
    // 处理变量组
    // 简化实现
}

void CHTLCompiler::processNamespaces() {
    // 处理命名空间
    // 简化实现
}

void CHTLCompiler::processImports() {
    // 处理导入
    // 简化实现
}

void CHTLCompiler::processConstraints() {
    // 处理约束
    // 简化实现
}

void CHTLCompiler::generateHTML() {
    // HTML已经在解析过程中生成
}

void CHTLCompiler::generateCSS() {
    // CSS已经在解析过程中生成
}

void CHTLCompiler::generateJavaScript() {
    // JavaScript已经在解析过程中生成
}

} // namespace chtl