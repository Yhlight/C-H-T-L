#include "CHTLJSCompiler.h"
#include <iostream>
#include <regex>
#include <sstream>

namespace chtl {

CHTLJSCompiler::CHTLJSCompiler() : jsOutput_("") {
    // 初始化CHTL JS编译器
}

bool CHTLJSCompiler::compile(const std::string& sourceCode) {
    try {
        // 解析CHTL JS语法树
        parseCHTLJS(sourceCode);
        
        // 处理各种CHTL JS特性
        processCHTLSelectors();
        processListeners();
        processEventDelegation();
        processAnimations();
        
        // 生成JavaScript输出
        generateJavaScript();
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "CHTL JS编译错误: " << e.what() << std::endl;
        return false;
    }
}

bool CHTLJSCompiler::validate(const std::string& sourceCode) {
    try {
        // 基本的CHTL JS语法验证
        std::regex chtlScriptPattern(R"(script\s*\{[^{}]*\})");
        if (!std::regex_search(sourceCode, chtlScriptPattern)) {
            return false;
        }
        
        // 验证选择器语法
        std::regex selectorPattern(R"(\{\{([^}]+)\}\})");
        std::sregex_iterator iter(sourceCode.begin(), sourceCode.end(), selectorPattern);
        std::sregex_iterator end;
        
        while (iter != end) {
            std::string selector = (*iter)[1];
            if (!validateSelector(selector)) {
                return false;
            }
            ++iter;
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "CHTL JS验证错误: " << e.what() << std::endl;
        return false;
    }
}

std::string CHTLJSCompiler::transpile(const std::string& sourceCode) {
    std::string transpiled = sourceCode;
    
    // 转换CHTL选择器 - 使用简单的字符串替换
    std::regex selectorPattern(R"(\{\{([^}]+)\}\})");
    std::sregex_iterator selectorIter(transpiled.begin(), transpiled.end(), selectorPattern);
    std::sregex_iterator selectorEnd;
    
    while (selectorIter != selectorEnd) {
        std::string match = (*selectorIter)[0];
        std::string content = (*selectorIter)[1];
        std::string replacement = convertSelector(content);
        size_t pos = transpiled.find(match);
        if (pos != std::string::npos) {
            transpiled.replace(pos, match.length(), replacement);
        }
        ++selectorIter;
    }
    
    // 转换监听器语法
    std::regex listenerPattern(R"(\.listen\s*\(\s*\{([^}]+)\}\s*\))");
    std::sregex_iterator listenerIter(transpiled.begin(), transpiled.end(), listenerPattern);
    std::sregex_iterator listenerEnd;
    
    while (listenerIter != listenerEnd) {
        std::string match = (*listenerIter)[0];
        std::string content = (*listenerIter)[1];
        std::string replacement = convertListener(content);
        size_t pos = transpiled.find(match);
        if (pos != std::string::npos) {
            transpiled.replace(pos, match.length(), replacement);
        }
        ++listenerIter;
    }
    
    // 转换事件委托语法
    std::regex delegatePattern(R"(\.delegate\s*\(\s*\{([^}]+)\}\s*\))");
    std::sregex_iterator delegateIter(transpiled.begin(), transpiled.end(), delegatePattern);
    std::sregex_iterator delegateEnd;
    
    while (delegateIter != delegateEnd) {
        std::string match = (*delegateIter)[0];
        std::string content = (*delegateIter)[1];
        std::string replacement = convertEventDelegation(content);
        size_t pos = transpiled.find(match);
        if (pos != std::string::npos) {
            transpiled.replace(pos, match.length(), replacement);
        }
        ++delegateIter;
    }
    
    // 转换动画语法
    std::regex animationPattern(R"(animate\s*\(\s*\{([^}]+)\}\s*\))");
    std::sregex_iterator animationIter(transpiled.begin(), transpiled.end(), animationPattern);
    std::sregex_iterator animationEnd;
    
    while (animationIter != animationEnd) {
        std::string match = (*animationIter)[0];
        std::string content = (*animationIter)[1];
        std::string replacement = convertAnimation(content);
        size_t pos = transpiled.find(match);
        if (pos != std::string::npos) {
            transpiled.replace(pos, match.length(), replacement);
        }
        ++animationIter;
    }
    
    return transpiled;
}

void CHTLJSCompiler::parseCHTLJS(const std::string& sourceCode) {
    // 使用ANTLR4生成的词法分析器解析CHTL JS
    // 这里将集成生成的CHTLJSLexer
    std::cout << "解析CHTL JS代码..." << std::endl;
}

void CHTLJSCompiler::generateJavaScript() {
    // 生成最终的JavaScript输出
    std::cout << "生成JavaScript输出..." << std::endl;
}

void CHTLJSCompiler::processCHTLSelectors() {
    // 处理CHTL选择器
    std::cout << "处理CHTL选择器..." << std::endl;
}

void CHTLJSCompiler::processListeners() {
    // 处理监听器
    std::cout << "处理监听器..." << std::endl;
}

void CHTLJSCompiler::processEventDelegation() {
    // 处理事件委托
    std::cout << "处理事件委托..." << std::endl;
}

void CHTLJSCompiler::processAnimations() {
    // 处理动画
    std::cout << "处理动画..." << std::endl;
}

std::string CHTLJSCompiler::convertSelector(const std::string& chtlSelector) {
    // 转换CHTL选择器为标准CSS选择器
    std::string selector = chtlSelector;
    
    // 处理类选择器
    if (selector[0] == '.') {
        return "document.querySelector('" + selector + "')";
    }
    
    // 处理ID选择器
    if (selector[0] == '#') {
        return "document.getElementById('" + selector.substr(1) + "')";
    }
    
    // 处理元素选择器
    return "document.querySelector('" + selector + "')";
}

std::string CHTLJSCompiler::convertListener(const std::string& chtlListener) {
    // 转换监听器语法
    std::string listener = chtlListener;
    
    // 解析事件类型和处理器
    std::regex eventPattern(R"((\w+)\s*:\s*(\w+))");
    std::smatch match;
    
    if (std::regex_search(listener, match, eventPattern)) {
        std::string eventType = match[1];
        std::string handler = match[2];
        return generateEventBinding(eventType, handler);
    }
    
    return "addEventListener('click', " + listener + ")";
}

std::string CHTLJSCompiler::convertEventDelegation(const std::string& chtlDelegate) {
    // 转换事件委托语法
    std::string delegate = chtlDelegate;
    
    // 解析目标选择器和事件
    std::regex targetPattern(R"(target\s*:\s*([^,]+))");
    std::regex eventPattern(R"(event\s*:\s*([^,]+))");
    
    std::smatch targetMatch, eventMatch;
    std::string target, event;
    
    if (std::regex_search(delegate, targetMatch, targetPattern)) {
        target = targetMatch[1];
    }
    
    if (std::regex_search(delegate, eventMatch, eventPattern)) {
        event = eventMatch[1];
    }
    
    return "addEventListener('" + event + "', function(e) { if (e.target.matches('" + target + "')) { /* handler */ } })";
}

std::string CHTLJSCompiler::convertAnimation(const std::string& chtlAnimation) {
    // 转换动画语法
    std::map<std::string, std::string> config = parseAnimationConfig(chtlAnimation);
    
    if (config.find("duration") != config.end()) {
        std::string duration = config["duration"];
        return "setTimeout(() => { /* animation */ }, " + duration + ")";
    }
    
    return "/* animation code */";
}

std::string CHTLJSCompiler::generateDOMQuery(const std::string& selector) {
    // 生成DOM查询代码
    if (selector[0] == '#') {
        return "document.getElementById('" + selector.substr(1) + "')";
    } else if (selector[0] == '.') {
        return "document.querySelector('" + selector + "')";
    } else {
        return "document.querySelector('" + selector + "')";
    }
}

std::string CHTLJSCompiler::generateEventBinding(const std::string& eventType, const std::string& handler) {
    // 生成事件绑定代码
    return "addEventListener('" + eventType + "', " + handler + ")";
}

std::string CHTLJSCompiler::generateAnimationCode(const std::map<std::string, std::string>& animationConfig) {
    // 生成动画代码
    std::stringstream code;
    code << "const animation = {";
    
    for (const auto& [key, value] : animationConfig) {
        code << key << ": " << value << ",";
    }
    
    code << "};";
    return code.str();
}

bool CHTLJSCompiler::validateSelector(const std::string& selector) {
    // 验证选择器语法
    if (selector.empty()) {
        return false;
    }
    
    // 基本的选择器验证规则
    std::regex validSelectorPattern(R"(^[.#]?[a-zA-Z][a-zA-Z0-9_-]*(\.[a-zA-Z][a-zA-Z0-9_-]*)*(#[a-zA-Z][a-zA-Z0-9_-]*)?$)");
    
    return std::regex_match(selector, validSelectorPattern);
}

bool CHTLJSCompiler::validateEventHandler(const std::string& handler) {
    // 验证事件处理器
    if (handler.empty()) {
        return false;
    }
    
    // 检查是否是有效的JavaScript标识符
    std::regex validHandlerPattern(R"(^[a-zA-Z_$][a-zA-Z0-9_$]*$)");
    
    return std::regex_match(handler, validHandlerPattern);
}

bool CHTLJSCompiler::validateAnimationConfig(const std::map<std::string, std::string>& config) {
    // 验证动画配置
    if (config.empty()) {
        return false;
    }
    
    // 检查必需的配置项
    if (config.find("duration") == config.end()) {
        return false;
    }
    
    return true;
}

std::vector<std::string> CHTLJSCompiler::parseSelectorContent(const std::string& selector) {
    // 解析选择器内容
    std::vector<std::string> parts;
    std::stringstream ss(selector);
    std::string part;
    
    while (std::getline(ss, part, '.')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }
    
    return parts;
}

std::map<std::string, std::string> CHTLJSCompiler::parseAnimationConfig(const std::string& config) {
    // 解析动画配置
    std::map<std::string, std::string> animationConfig;
    
    std::regex configPattern(R"((\w+)\s*:\s*([^,]+))");
    std::sregex_iterator iter(config.begin(), config.end(), configPattern);
    std::sregex_iterator end;
    
    while (iter != end) {
        std::string key = (*iter)[1];
        std::string value = (*iter)[2];
        animationConfig[key] = value;
        ++iter;
    }
    
    return animationConfig;
}

} // namespace chtl