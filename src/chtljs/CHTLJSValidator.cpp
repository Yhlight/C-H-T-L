#include "CHTLJSStateMachine.h"
#include <regex>
#include <sstream>
#include <algorithm>

namespace chtljs {

// 验证事件名称的正则表达式
static const std::regex eventNameRegex("^(click|dblclick|mousedown|mouseup|mousemove|mouseenter|mouseleave|"
                                      "keydown|keyup|keypress|focus|blur|change|input|submit|load|unload|"
                                      "resize|scroll|touchstart|touchend|touchmove)$");

// 验证CSS属性名的正则表达式
static const std::regex cssPropertyRegex("^[a-z]+(-[a-z]+)*$");

// 验证选择器的正则表达式
static const std::regex classSelectorRegex("^\\.[a-zA-Z_-][a-zA-Z0-9_-]*$");
static const std::regex idSelectorRegex("^#[a-zA-Z_-][a-zA-Z0-9_-]*$");
static const std::regex elementSelectorRegex("^[a-zA-Z]+[a-zA-Z0-9]*$");
static const std::regex indexedSelectorRegex("^(.+)\\[([0-9]+)\\]$");

// CHTLSelectorValidator 实现
bool CHTLSelectorValidator::validate() {
    if (selector.empty()) {
        errorMessage = "Selector cannot be empty";
        isValid = false;
        return false;
    }
    
    // 移除可能的空格
    std::string trimmedSelector = selector;
    trimmedSelector.erase(0, trimmedSelector.find_first_not_of(" \t"));
    trimmedSelector.erase(trimmedSelector.find_last_not_of(" \t") + 1);
    
    // 检查是否是复合选择器（包含空格）
    if (trimmedSelector.find(' ') != std::string::npos) {
        // 复合选择器验证
        std::istringstream iss(trimmedSelector);
        std::string part;
        while (iss >> part) {
            if (!isClassSelector() && !isIdSelector() && !isElementSelector()) {
                errorMessage = "Invalid selector part: " + part;
                isValid = false;
                return false;
            }
        }
        return true;
    }
    
    // 检查是否有索引
    std::smatch match;
    if (std::regex_match(trimmedSelector, match, indexedSelectorRegex)) {
        std::string baseSelector = match[1];
        // 递归验证基础选择器
        CHTLSelectorValidator baseValidator(baseSelector);
        if (!baseValidator.validate()) {
            errorMessage = baseValidator.getError();
            isValid = false;
            return false;
        }
    }
    
    // 单一选择器验证
    if (!isClassSelector() && !isIdSelector() && !isElementSelector()) {
        errorMessage = "Invalid selector format: " + selector;
        isValid = false;
        return false;
    }
    
    return true;
}

bool CHTLSelectorValidator::isClassSelector() const {
    return std::regex_match(selector, classSelectorRegex);
}

bool CHTLSelectorValidator::isIdSelector() const {
    return std::regex_match(selector, idSelectorRegex);
}

bool CHTLSelectorValidator::isElementSelector() const {
    return std::regex_match(selector, elementSelectorRegex);
}

bool CHTLSelectorValidator::hasIndex() const {
    return selector.find('[') != std::string::npos && selector.find(']') != std::string::npos;
}

int CHTLSelectorValidator::getIndex() const {
    std::smatch match;
    if (std::regex_match(selector, match, indexedSelectorRegex)) {
        return std::stoi(match[2]);
    }
    return -1;
}

std::string CHTLSelectorValidator::getBaseSelector() const {
    std::smatch match;
    if (std::regex_match(selector, match, indexedSelectorRegex)) {
        return match[1];
    }
    return selector;
}

// EventConfigValidator 实现
bool EventConfigValidator::validateListenConfig(const std::string& config) {
    // 简化的配置解析，实际应该使用更复杂的解析器
    // 期望格式: { event1: handler1, event2: handler2, ... }
    
    if (config.empty() || config.front() != '{' || config.back() != '}') {
        errorMessage = "Invalid config format";
        isValid = false;
        return false;
    }
    
    // 提取事件对
    std::string content = config.substr(1, config.length() - 2);
    std::istringstream iss(content);
    std::string line;
    
    while (std::getline(iss, line, ',')) {
        // 查找冒号
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) {
            errorMessage = "Invalid event binding format";
            isValid = false;
            return false;
        }
        
        std::string eventName = line.substr(0, colonPos);
        // 移除空格和引号
        eventName.erase(std::remove_if(eventName.begin(), eventName.end(), 
                                     [](char c) { return std::isspace(c) || c == '"' || c == '\''; }), 
                       eventName.end());
        
        if (!hasEvent(eventName)) {
            if (!std::regex_match(eventName, eventNameRegex)) {
                errorMessage = "Invalid event name: " + eventName;
                isValid = false;
                return false;
            }
        }
        
        events[eventName] = line.substr(colonPos + 1);
    }
    
    return true;
}

bool EventConfigValidator::validateDelegateConfig(const std::string& config) {
    // Delegate配置需要额外的target属性
    // 期望格式: { target: selector, event1: handler1, ... }
    
    if (!validateListenConfig(config)) {
        return false;
    }
    
    if (events.find("target") == events.end()) {
        errorMessage = "Delegate config must include 'target' property";
        isValid = false;
        return false;
    }
    
    return true;
}

bool EventConfigValidator::hasEvent(const std::string& eventName) const {
    return events.find(eventName) != events.end();
}

// AnimateConfigValidator 实现
bool AnimateConfigValidator::validate(const std::string& configStr) {
    // 简化的动画配置解析
    // 期望格式: { duration: 1000, easing: "ease-in-out", begin: {...}, end: {...}, ... }
    
    if (configStr.empty() || configStr.front() != '{' || configStr.back() != '}') {
        errorMessage = "Invalid animate config format";
        isValid = false;
        return false;
    }
    
    // 解析配置属性
    std::string content = configStr.substr(1, configStr.length() - 2);
    
    // 查找duration
    size_t durationPos = content.find("duration:");
    if (durationPos != std::string::npos) {
        size_t endPos = content.find(',', durationPos);
        std::string durationStr = content.substr(durationPos + 9, endPos - durationPos - 9);
        try {
            config.duration = std::stoi(durationStr);
        } catch (...) {
            errorMessage = "Invalid duration value";
            isValid = false;
            return false;
        }
    }
    
    // 查找easing
    size_t easingPos = content.find("easing:");
    if (easingPos != std::string::npos) {
        size_t startQuote = content.find_first_of("\"'", easingPos);
        size_t endQuote = content.find_first_of("\"'", startQuote + 1);
        if (startQuote != std::string::npos && endQuote != std::string::npos) {
            config.easing = content.substr(startQuote + 1, endQuote - startQuote - 1);
        }
    }
    
    // 查找loop
    size_t loopPos = content.find("loop:");
    if (loopPos != std::string::npos) {
        size_t endPos = content.find_first_of(",}", loopPos);
        std::string loopStr = content.substr(loopPos + 5, endPos - loopPos - 5);
        try {
            config.loop = std::stoi(loopStr);
        } catch (...) {
            errorMessage = "Invalid loop value";
            isValid = false;
            return false;
        }
    }
    
    // 验证必需的属性
    if (config.duration <= 0) {
        errorMessage = "Duration must be greater than 0";
        isValid = false;
        return false;
    }
    
    return true;
}

// CHTLJSStateMachine 的验证方法实现
bool CHTLJSStateMachine::validateCHTLSelector(const std::string& selector) {
    CHTLSelectorValidator validator(selector);
    return validator.validate();
}

bool CHTLJSStateMachine::validateListenConfig(const std::string& config) {
    EventConfigValidator validator;
    return validator.validateListenConfig(config);
}

bool CHTLJSStateMachine::validateDelegateConfig(const std::string& config) {
    EventConfigValidator validator;
    return validator.validateDelegateConfig(config);
}

bool CHTLJSStateMachine::validateAnimateConfig(const std::string& config) {
    AnimateConfigValidator validator;
    return validator.validate(config);
}

// CHTLJSHelper 命名空间实现
namespace CHTLJSHelper {

DOMReferenceType parseSelector(const std::string& selector) {
    if (selector.empty()) {
        return DOMReferenceType::ELEMENT_SELECTOR;
    }
    
    if (selector[0] == '.') {
        return DOMReferenceType::CLASS_SELECTOR;
    } else if (selector[0] == '#') {
        return DOMReferenceType::ID_SELECTOR;
    } else if (selector.find(' ') != std::string::npos) {
        return DOMReferenceType::COMPLEX_SELECTOR;
    } else if (selector.find('[') != std::string::npos) {
        return DOMReferenceType::INDEXED_SELECTOR;
    }
    
    return DOMReferenceType::ELEMENT_SELECTOR;
}

std::string extractSelectorBase(const std::string& selector) {
    size_t bracketPos = selector.find('[');
    if (bracketPos != std::string::npos) {
        return selector.substr(0, bracketPos);
    }
    return selector;
}

std::optional<int> extractSelectorIndex(const std::string& selector) {
    std::smatch match;
    if (std::regex_match(selector, match, indexedSelectorRegex)) {
        return std::stoi(match[2]);
    }
    return std::nullopt;
}

bool isValidJavaScriptIdentifier(const std::string& identifier) {
    if (identifier.empty()) {
        return false;
    }
    
    // 首字符必须是字母、下划线或$
    if (!std::isalpha(identifier[0]) && identifier[0] != '_' && identifier[0] != '$') {
        return false;
    }
    
    // 其余字符可以是字母、数字、下划线或$
    for (size_t i = 1; i < identifier.length(); ++i) {
        if (!std::isalnum(identifier[i]) && identifier[i] != '_' && identifier[i] != '$') {
            return false;
        }
    }
    
    // 检查是否是保留字
    static const std::unordered_set<std::string> reservedWords = {
        "break", "case", "catch", "class", "const", "continue", "debugger",
        "default", "delete", "do", "else", "export", "extends", "finally",
        "for", "function", "if", "import", "in", "instanceof", "new",
        "return", "super", "switch", "this", "throw", "try", "typeof",
        "var", "void", "while", "with", "yield", "let", "static",
        "await", "async"
    };
    
    return reservedWords.find(identifier) == reservedWords.end();
}

bool isValidEventName(const std::string& eventName) {
    return std::regex_match(eventName, eventNameRegex);
}

std::string generateUniqueId(const std::string& prefix) {
    static int counter = 0;
    return prefix + "_" + std::to_string(++counter);
}

} // namespace CHTLJSHelper

} // namespace chtljs