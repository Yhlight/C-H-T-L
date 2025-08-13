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
    
    // 初始化状态转换表
    initializeStateTransitions();
    
    // 初始化上下文推导规则
    initializeContextRules();
    
    // 初始化状态机
    currentState_ = CompilerState::INITIAL;
    
    // 创建根上下文
    auto rootContext = createContext(ContextType::ROOT, "root");
    pushContext(rootContext);
}

bool CHTLCompiler::compile(const std::string& sourceCode) {
    try {
        // 重置状态
        reset();
        
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

void CHTLCompiler::initializeStateTransitions() {
    // 初始化状态转换表
    // 从初始状态到根状态
    stateTransitions_.emplace_back(
        CompilerState::INITIAL, "start", CompilerState::ROOT,
        [this](const std::string&) { /* 初始化根上下文 */ }
    );
    
    // 从根状态到元素声明状态
    stateTransitions_.emplace_back(
        CompilerState::ROOT, "element", CompilerState::ELEMENT_DECL,
        [this](const std::string& line) { processElement(line); }
    );
    
    // 从元素声明状态到元素打开状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_DECL, "{", CompilerState::ELEMENT_OPEN,
        [this](const std::string&) { /* 打开元素 */ }
    );
    
    // 从元素打开状态到属性列表状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_OPEN, "attribute", CompilerState::ATTRIBUTE_LIST,
        [this](const std::string& line) { processAttribute(line); }
    );
    
    // 从元素打开状态到样式块状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_OPEN, "style", CompilerState::STYLE_BLOCK,
        [this](const std::string& line) { processStyleBlock(line); }
    );
    
    // 从元素打开状态到文本块状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_OPEN, "text", CompilerState::TEXT_BLOCK,
        [this](const std::string& line) { processTextBlock(line); }
    );
    
    // 从元素打开状态到脚本块状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_OPEN, "script", CompilerState::SCRIPT_BLOCK,
        [this](const std::string& line) { processScriptBlock(line); }
    );
    
    // 从各种块状态回到元素内容状态
    stateTransitions_.emplace_back(
        CompilerState::STYLE_BLOCK, "}", CompilerState::ELEMENT_CONTENT,
        [this](const std::string&) { /* 结束样式块 */ }
    );
    
    stateTransitions_.emplace_back(
        CompilerState::TEXT_BLOCK, "}", CompilerState::ELEMENT_CONTENT,
        [this](const std::string&) { /* 结束文本块 */ }
    );
    
    stateTransitions_.emplace_back(
        CompilerState::SCRIPT_BLOCK, "}", CompilerState::ELEMENT_CONTENT,
        [this](const std::string&) { /* 结束脚本块 */ }
    );
    
    // 从元素内容状态到元素关闭状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_CONTENT, "}", CompilerState::ELEMENT_CLOSE,
        [this](const std::string&) { /* 关闭元素 */ }
    );
    
    // 从元素关闭状态回到根状态
    stateTransitions_.emplace_back(
        CompilerState::ELEMENT_CLOSE, "end", CompilerState::ROOT,
        [this](const std::string&) { /* 回到根状态 */ }
    );
}

void CHTLCompiler::initializeContextRules() {
    // 初始化上下文推导规则
    
    // 规则1: & 上下文推导 - 最高优先级
    contextRules_.emplace_back(
        "&",
        [](const CompilerContext& context, const std::string& input) -> std::string {
            if (input == "&") {
                return "." + context.generatedClasses.back();
            }
            if (input.find("&") == 0) {
                return "." + context.generatedClasses.back() + input.substr(1);
            }
            return input;
        },
        100
    );
    
    // 规则2: 类选择器自动生成
    contextRules_.emplace_back(
        "\\.[a-zA-Z_][a-zA-Z0-9_]*",
        [](const CompilerContext& context, const std::string& input) -> std::string {
            if (input.front() == '.') {
                std::string className = input.substr(1);
                // 自动为元素添加类名
                return input;
            }
            return input;
        },
        90
    );
    
    // 规则3: ID选择器自动生成
    contextRules_.emplace_back(
        "#[a-zA-Z_][a-zA-Z0-9_]*",
        [](const CompilerContext& context, const std::string& input) -> std::string {
            if (input.front() == '#') {
                std::string idName = input.substr(1);
                // 自动为元素添加ID
                return input;
            }
            return input;
        },
        90
    );
    
    // 规则4: 嵌套选择器
    contextRules_.emplace_back(
        "\\s+[.#][a-zA-Z_][a-zA-Z0-9_]*",
        [](const CompilerContext& context, const std::string& input) -> std::string {
            // 处理嵌套选择器
            return input;
        },
        80
    );
    
    // 按优先级排序
    std::sort(contextRules_.begin(), contextRules_.end(), 
              [](const ContextRule& a, const ContextRule& b) {
                  return a.priority > b.priority;
              });
}

void CHTLCompiler::parseCHTL(const std::string& sourceCode) {
    std::istringstream iss(sourceCode);
    std::string line;
    size_t lineNumber = 0;
    
    // 启动状态机
    transitionState("start");
    
    while (std::getline(iss, line)) {
        lineNumber++;
        currentLineNumber_ = lineNumber;
        parseLine(line, lineNumber);
    }
    
    // 结束状态机
    transitionState("end");
}

void CHTLCompiler::parseLine(const std::string& line, size_t lineNumber) {
    std::string trimmed = trim(line);
    
    // 跳过空行和注释
    if (trimmed.empty() || isComment(trimmed)) {
        return;
    }
    
    // 调试信息 - 将状态转换为字符串
    std::string stateStr;
    switch (currentState_) {
        case CompilerState::INITIAL: stateStr = "INITIAL"; break;
        case CompilerState::ROOT: stateStr = "ROOT"; break;
        case CompilerState::ELEMENT_DECL: stateStr = "ELEMENT_DECL"; break;
        case CompilerState::ELEMENT_OPEN: stateStr = "ELEMENT_OPEN"; break;
        case CompilerState::ELEMENT_CONTENT: stateStr = "ELEMENT_CONTENT"; break;
        case CompilerState::ELEMENT_CLOSE: stateStr = "ELEMENT_CLOSE"; break;
        case CompilerState::ATTRIBUTE_LIST: stateStr = "ATTRIBUTE_LIST"; break;
        case CompilerState::ATTRIBUTE_PAIR: stateStr = "ATTRIBUTE_PAIR"; break;
        case CompilerState::STYLE_BLOCK: stateStr = "STYLE_BLOCK"; break;
        case CompilerState::STYLE_RULE: stateStr = "STYLE_RULE"; break;
        case CompilerState::STYLE_PROPERTY: stateStr = "STYLE_PROPERTY"; break;
        case CompilerState::TEXT_BLOCK: stateStr = "TEXT_BLOCK"; break;
        case CompilerState::SCRIPT_BLOCK: stateStr = "SCRIPT_BLOCK"; break;
        case CompilerState::TEMPLATE_DECL: stateStr = "TEMPLATE_DECL"; break;
        case CompilerState::TEMPLATE_CONTENT: stateStr = "TEMPLATE_CONTENT"; break;
        case CompilerState::CUSTOM_DECL: stateStr = "CUSTOM_DECL"; break;
        case CompilerState::CUSTOM_CONTENT: stateStr = "CUSTOM_CONTENT"; break;
        case CompilerState::IMPORT_DECL: stateStr = "IMPORT_DECL"; break;
        case CompilerState::NAMESPACE_DECL: stateStr = "NAMESPACE_DECL"; break;
        case CompilerState::CONFIG_DECL: stateStr = "CONFIG_DECL"; break;
        case CompilerState::ORIGIN_BLOCK: stateStr = "ORIGIN_BLOCK"; break;
        case CompilerState::COMMENT_BLOCK: stateStr = "COMMENT_BLOCK"; break;
        default: stateStr = "UNKNOWN"; break;
    }
    
    std::cout << "Line " << lineNumber << " [" << stateStr << "]: " << trimmed << std::endl;
    
    // 更新当前上下文
    updateContext(trimmed);
    
    // 处理状态
    handleState(trimmed, lineNumber);
}

bool CHTLCompiler::transitionState(const std::string& trigger) {
    // 查找匹配的状态转换
    for (const auto& transition : stateTransitions_) {
        if (transition.from == currentState_ && transition.trigger == trigger) {
            // 执行转换动作
            if (transition.action) {
                transition.action(trigger);
            }
            
            // 更新状态
            currentState_ = transition.to;
            return true;
        }
    }
    
    return false;
}

void CHTLCompiler::executeStateAction(const std::string& trigger) {
    // 执行状态动作
    for (const auto& transition : stateTransitions_) {
        if (transition.from == currentState_ && transition.trigger == trigger) {
            if (transition.action) {
                transition.action(trigger);
            }
            break;
        }
    }
}

void CHTLCompiler::handleState(const std::string& line, size_t lineNumber) {
    // 基于当前状态和上下文处理行
    switch (currentState_) {
        case CompilerState::ROOT:
            if (line.find("element") == 0) {
                std::cout << "  -> Transitioning to ELEMENT_DECL" << std::endl;
                currentState_ = CompilerState::ELEMENT_DECL;
                // 立即处理元素
                processElement(line);
            }
            break;
            
        case CompilerState::ELEMENT_DECL:
            if (line.find("{") != std::string::npos) {
                std::cout << "  -> Transitioning to ELEMENT_OPEN" << std::endl;
                currentState_ = CompilerState::ELEMENT_OPEN;
            } else if (line.find("element") == 0) {
                // 嵌套元素
                std::cout << "  -> Nested element, creating new context" << std::endl;
                processElement(line);
            }
            break;
            
        case CompilerState::ELEMENT_OPEN:
            if (line.find("class:") != std::string::npos || line.find("class=") != std::string::npos) {
                std::cout << "  -> Processing attribute" << std::endl;
                processAttribute(line);
            } else if (line.find("style:") == 0 || line.find("style=") == 0) {
                std::cout << "  -> Transitioning to STYLE_BLOCK" << std::endl;
                currentState_ = CompilerState::STYLE_BLOCK;
            } else if (line.find("text:") == 0 || line.find("text=") == 0) {
                std::cout << "  -> Transitioning to TEXT_BLOCK" << std::endl;
                currentState_ = CompilerState::TEXT_BLOCK;
            } else if (line.find("script:") == 0 || line.find("script=") == 0) {
                std::cout << "  -> Transitioning to SCRIPT_BLOCK" << std::endl;
                currentState_ = CompilerState::SCRIPT_BLOCK;
            } else if (line.find("element") == 0) {
                // 嵌套元素 - 应该创建新的元素上下文
                std::cout << "  -> Nested element, creating new context" << std::endl;
                currentState_ = CompilerState::ELEMENT_DECL;
                processElement(line);
            } else if (line.find("}") != std::string::npos) {
                // 检查是否是当前元素的结束
                std::cout << "  -> Element content ended, transitioning to ELEMENT_CONTENT" << std::endl;
                currentState_ = CompilerState::ELEMENT_CONTENT;
            }
            break;
            
        case CompilerState::STYLE_BLOCK:
            if (line.find("}") != std::string::npos) {
                std::cout << "  -> Ending style block, back to ELEMENT_OPEN" << std::endl;
                currentState_ = CompilerState::ELEMENT_OPEN;
            } else {
                processStyleBlock(line);
            }
            break;
            
        case CompilerState::TEXT_BLOCK:
            if (line.find("}") != std::string::npos) {
                std::cout << "  -> Ending text block, back to ELEMENT_OPEN" << std::endl;
                currentState_ = CompilerState::ELEMENT_OPEN;
            } else {
                processTextBlock(line);
            }
            break;
            
        case CompilerState::SCRIPT_BLOCK:
            if (line.find("}") != std::string::npos) {
                std::cout << "  -> Ending script block, back to ELEMENT_OPEN" << std::endl;
                currentState_ = CompilerState::ELEMENT_OPEN;
            } else {
                processScriptBlock(line);
            }
            break;
            
        case CompilerState::ELEMENT_CONTENT:
            if (line.find("}") != std::string::npos) {
                std::cout << "  -> Closing element" << std::endl;
                closeElement(); // 调用closeElement方法
                currentState_ = CompilerState::ELEMENT_CLOSE;
            } else if (line.find("element") == 0) {
                std::cout << "  -> Nested element in content" << std::endl;
                currentState_ = CompilerState::ELEMENT_DECL;
                processElement(line);
            } else if (line.find("class:") != std::string::npos || line.find("class=") != std::string::npos) {
                std::cout << "  -> Processing attribute in content" << std::endl;
                processAttribute(line);
            } else if (line.find("style:") == 0 || line.find("style=") == 0) {
                std::cout << "  -> Style block in content" << std::endl;
                currentState_ = CompilerState::STYLE_BLOCK;
            } else if (line.find("text:") == 0 || line.find("text=") == 0) {
                std::cout << "  -> Text block in content" << std::endl;
                currentState_ = CompilerState::TEXT_BLOCK;
            } else if (line.find("script:") == 0 || line.find("script=") == 0) {
                std::cout << "  -> Script block in content" << std::endl;
                currentState_ = CompilerState::SCRIPT_BLOCK;
            }
            break;
            
        case CompilerState::ELEMENT_CLOSE:
            std::cout << "  -> Element closed, back to ROOT" << std::endl;
            currentState_ = CompilerState::ROOT;
            break;
            
        default:
            std::cout << "  -> Unknown state: " << static_cast<int>(currentState_) << std::endl;
            break;
    }
}

std::shared_ptr<CompilerContext> CHTLCompiler::createContext(ContextType type, const std::string& name) {
    auto context = std::make_shared<CompilerContext>();
    context->type = type;
    context->name = name;
    context->lineNumber = currentLineNumber_;
    context->depth = contextStack_.size();
    
    // 生成唯一标识符
    std::string uniqueId = context->generateUniqueId();
    context->generatedIds.push_back(uniqueId);
    
    // 注册上下文
    contextRegistry_[uniqueId] = context;
    
    return context;
}

void CHTLCompiler::pushContext(std::shared_ptr<CompilerContext> context) {
    if (!contextStack_.empty()) {
        auto parent = contextStack_.top();
        context->parentSelector = parent->getFullSelector();
        context->depth = parent->depth + 1;
    }
    
    contextStack_.push(context);
}

std::shared_ptr<CompilerContext> CHTLCompiler::popContext() {
    if (contextStack_.empty()) {
        return nullptr;
    }
    
    auto context = contextStack_.top();
    contextStack_.pop();
    return context;
}

std::shared_ptr<CompilerContext> CHTLCompiler::getCurrentContext() {
    if (contextStack_.empty()) {
        return nullptr;
    }
    return contextStack_.top();
}

void CHTLCompiler::updateContext(const std::string& line) {
    auto context = getCurrentContext();
    if (!context) return;
    
    // 更新上下文内容
    context->content.push_back(line);
    
    // 检查是否是文本内容
    if (line.find("text:") == 0 || line.find("text=") == 0) {
        // 提取文本内容
        std::regex textPattern(R"(text\s*[:=]\s*["']?([^"']+)["']?)");
        std::smatch match;
        if (std::regex_search(line, match, textPattern)) {
            std::string textContent = match[1];
            // 将文本内容添加到当前上下文的HTML输出
            htmlOutput_ += textContent + "\n";
        }
    }
}

std::string CHTLCompiler::deriveContext(const std::string& input) {
    return applyContextRules(input);
}

std::string CHTLCompiler::applyContextRules(const std::string& input) {
    std::string result = input;
    
    for (const auto& rule : contextRules_) {
        std::regex pattern(rule.pattern);
        if (std::regex_search(result, pattern)) {
            auto context = getCurrentContext();
            if (context) {
                result = rule.transform(*context, result);
            }
        }
    }
    
    return result;
}

std::string CHTLCompiler::generateSelector(const std::shared_ptr<CompilerContext>& context) {
    if (!context) return "";
    
    std::string selector;
    
    // 优先使用ID
    if (!context->generatedIds.empty()) {
        selector = "#" + context->generatedIds.back();
    }
    // 其次使用类名
    else if (!context->generatedClasses.empty()) {
        selector = "." + context->generatedClasses.back();
    }
    // 最后使用元素名
    else {
        selector = context->name;
    }
    
    return selector;
}

void CHTLCompiler::processElement(const std::string& line) {
    std::string elementName = extractElementName(line);
    if (elementName.empty()) return;
    
    // 创建元素上下文
    auto elementContext = createContext(ContextType::ELEMENT, elementName);
    elementContext->currentSelector = elementName;
    
    // 生成类名
    std::string className = "chtl-" + elementName + "-" + std::to_string(elementContext->depth);
    elementContext->generatedClasses.push_back(className);
    
    pushContext(elementContext);
    
    // 生成HTML开始标签
    htmlOutput_ += "<" + elementName;
    htmlOutput_ += " class=\"" + className + "\"";
    
    if (isSingleTagElement(elementName)) {
        htmlOutput_ += " />\n";
    } else {
        htmlOutput_ += ">\n";
    }
}

void CHTLCompiler::processAttribute(const std::string& line) {
    auto context = getCurrentContext();
    if (!context) return;
    
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
        
        context->attributes[attrName] = attrValue;
        
        // 更新HTML标签 - 重新生成整个开始标签
        updateHTMLElement(context);
    }
}

void CHTLCompiler::updateHTMLElement(const std::shared_ptr<CompilerContext>& context) {
    if (!context) return;
    
    // 重新生成HTML开始标签，包含所有属性
    std::string elementName = context->name;
    std::string className = context->generatedClasses.empty() ? "" : context->generatedClasses.back();
    
    // 构建属性字符串
    std::string attributesStr = " class=\"" + className + "\"";
    for (const auto& attr : context->attributes) {
        attributesStr += " " + attr.first + "=\"" + attr.second + "\"";
    }
    
    // 更新HTML输出 - 这里需要更复杂的逻辑来替换现有的标签
    // 暂时简化处理，在实际实现中需要更精确的标签替换
    // 现在先不实现复杂的标签替换，保持简单
}

void CHTLCompiler::closeElement() {
    if (contextStack_.empty()) return;
    
    auto context = contextStack_.top();
    std::string elementName = context->name;
    
    // 检查是否是单标签元素
    if (!isSingleTagElement(elementName)) {
        htmlOutput_ += "</" + elementName + ">\n";
    }
    
    contextStack_.pop();
}

void CHTLCompiler::processStyleBlock(const std::string& line) {
    if (line.find("}") != std::string::npos) {
        // 结束样式块
        return;
    }
    
    // 处理样式内容
    if (line.find(":") != std::string::npos) {
        // 解析CSS属性
        std::regex cssPattern(R"((\w+)\s*:\s*([^;]+);?)");
        std::smatch match;
        if (std::regex_search(line, match, cssPattern)) {
            std::string property = match[1];
            std::string value = trim(match[2]);
            currentStyleBlock_ += "  " + property + ": " + value + ";\n";
        }
    }
}

void CHTLCompiler::processTextBlock(const std::string& line) {
    if (line.find("}") != std::string::npos) {
        // 结束文本块
        return;
    }
    
    // 处理文本块内容
    if (line.find("text:") == 0 || line.find("text=") == 0) {
        // 提取文本内容
        std::regex textPattern(R"(text\s*[:=]\s*["']?([^"']+)["']?)");
        std::smatch match;
        if (std::regex_search(line, match, textPattern)) {
            std::string textContent = match[1];
            // 将文本内容添加到HTML输出
            htmlOutput_ += textContent + "\n";
        }
    } else {
        // 直接添加文本内容
        htmlOutput_ += line + "\n";
    }
}

void CHTLCompiler::processScriptBlock(const std::string& line) {
    if (line.find("}") != std::string::npos) {
        // 结束脚本块
        return;
    }
    
    currentScriptBlock_ += line + "\n";
}

void CHTLCompiler::processTemplate(const std::string& line) {
    // 处理模板定义
    // 这里可以添加模板处理逻辑
}

void CHTLCompiler::processCustom(const std::string& line) {
    // 处理自定义定义
    // 这里可以添加自定义处理逻辑
}

void CHTLCompiler::processImport(const std::string& line) {
    // 处理导入语句
    // 这里可以添加导入处理逻辑
}

void CHTLCompiler::processNamespace(const std::string& line) {
    // 处理命名空间
    // 这里可以添加命名空间处理逻辑
}

void CHTLCompiler::processConfiguration(const std::string& line) {
    // 处理配置
    // 这里可以添加配置处理逻辑
}

void CHTLCompiler::processOrigin(const std::string& line) {
    // 处理原始嵌入
    // 这里可以添加原始嵌入处理逻辑
}

void CHTLCompiler::generateHTML() {
    // HTML已经在解析过程中生成
}

void CHTLCompiler::generateCSS() {
    // 生成CSS输出
    if (!currentStyleBlock_.empty()) {
        cssOutput_ += "/* 自动生成的CSS */\n";
        cssOutput_ += currentStyleBlock_;
    }
}

void CHTLCompiler::generateJavaScript() {
    // 生成JavaScript输出
    if (!currentScriptBlock_.empty()) {
        jsOutput_ += "// 自动生成的JavaScript\n";
        jsOutput_ += currentScriptBlock_;
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

void CHTLCompiler::reset() {
    currentState_ = CompilerState::INITIAL;
    currentLineNumber_ = 0;
    htmlOutput_.clear();
    cssOutput_.clear();
    jsOutput_.clear();
    
    while (!contextStack_.empty()) {
        contextStack_.pop();
    }
    
    contextRegistry_.clear();
    templates_.clear();
    customs_.clear();
    
    currentStyleBlock_.clear();
    currentScriptBlock_.clear();
    
    // 重新创建根上下文
    auto rootContext = createContext(ContextType::ROOT, "root");
    pushContext(rootContext);
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

std::string CHTLCompiler::extractElementName(const std::string& line) {
    // 提取元素名称
    std::regex elementPattern(R"((\w+)\s*\{)");
    std::smatch match;
    
    if (std::regex_search(line, match, elementPattern)) {
        return match[1];
    }
    
    return "";
}

bool CHTLCompiler::isSingleTagElement(const std::string& elementName) {
    return singleTagElements_.find(elementName) != singleTagElements_.end();
}

std::vector<std::string> CHTLCompiler::getAllHTMLElements() {
    std::vector<std::string> allElements;
    
    allElements.insert(allElements.end(), singleTagElements_.begin(), singleTagElements_.end());
    allElements.insert(allElements.end(), blockElements_.begin(), blockElements_.end());
    allElements.insert(allElements.end(), inlineElements_.begin(), inlineElements_.end());
    
    return allElements;
}

} // namespace chtl