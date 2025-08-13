#include "CHTLJSContext.h"
#include "CHTLContext.h"
#include <iostream>
#include <regex>

namespace chtl {

// CHTLJSScope 实现
void CHTLJSScope::addSymbol(const std::string& name, const CHTLJSSymbol& symbol) {
    symbols[name] = symbol;
}

CHTLJSSymbol* CHTLJSScope::findSymbol(const std::string& name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return &it->second;
    }
    
    // 在父作用域中查找
    if (parent) {
        return parent->findSymbol(name);
    }
    
    return nullptr;
}

const CHTLJSSymbol* CHTLJSScope::findSymbol(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return &it->second;
    }
    
    // 在父作用域中查找
    if (parent) {
        return parent->findSymbol(name);
    }
    
    return nullptr;
}

// CHTLJSContext 实现
CHTLJSContext::CHTLJSContext(std::shared_ptr<CHTLContext> base)
    : baseContext(base), stateMachine(std::make_unique<CHTLJSStateMachine>()) {
    // 创建全局作用域
    globalScope = std::make_shared<CHTLJSScope>("global");
    currentScope = globalScope;
}

void CHTLJSContext::enterScope(const std::string& name) {
    auto newScope = std::make_shared<CHTLJSScope>(name, currentScope);
    scopeStack.push(currentScope);
    currentScope = newScope;
}

void CHTLJSContext::exitScope() {
    if (!scopeStack.empty()) {
        currentScope = scopeStack.top();
        scopeStack.pop();
    }
}

void CHTLJSContext::addVariable(const std::string& name, const std::string& value, bool isUnquoted) {
    CHTLJSSymbol symbol;
    symbol.type = CHTLJSSymbol::Variable;
    symbol.name = name;
    symbol.value = value;
    symbol.scope = currentScope->getName();
    symbol.isUnquoted = isUnquoted;
    
    // 如果是无修饰字面量，处理它
    if (isUnquoted && config.allowUnquotedLiterals) {
        symbol.quotedValue = processUnquotedLiteral(value);
    }
    
    currentScope->addSymbol(name, symbol);
}

void CHTLJSContext::addFunction(const std::string& name, const std::string& params) {
    CHTLJSSymbol symbol;
    symbol.type = CHTLJSSymbol::Function;
    symbol.name = name;
    symbol.value = params;
    symbol.scope = currentScope->getName();
    
    currentScope->addSymbol(name, symbol);
}

void CHTLJSContext::addSelector(const std::string& selector) {
    CHTLJSSymbol symbol;
    symbol.type = CHTLJSSymbol::Selector;
    symbol.name = selector;
    symbol.value = selector;
    symbol.scope = currentScope->getName();
    
    currentScope->addSymbol(selector, symbol);
}

void CHTLJSContext::addMethod(const std::string& object, const std::string& method) {
    CHTLJSSymbol symbol;
    symbol.type = CHTLJSSymbol::Method;
    symbol.name = object + "." + method;
    symbol.value = method;
    symbol.scope = currentScope->getName();
    
    currentScope->addSymbol(symbol.name, symbol);
}

void CHTLJSContext::addAnimation(const std::string& name, const std::string& config) {
    animations[name] = config;
    
    CHTLJSSymbol symbol;
    symbol.type = CHTLJSSymbol::Animation;
    symbol.name = name;
    symbol.value = config;
    symbol.scope = currentScope->getName();
    
    currentScope->addSymbol(name, symbol);
}

bool CHTLJSContext::isUnquotedLiteralAllowed() const {
    if (!config.allowUnquotedLiterals) {
        return false;
    }
    
    return stateMachine->canUseUnquotedLiteral();
}

bool CHTLJSContext::validateUnquotedLiteral(const std::string& value) const {
    if (!config.validateUnquoted) {
        return true;
    }
    
    return stateMachine->isValidUnquotedLiteral(value);
}

std::string CHTLJSContext::processUnquotedLiteral(const std::string& value) {
    // 首先验证
    if (!validateUnquotedLiteral(value)) {
        reportWarning("Invalid unquoted literal: " + value);
        if (!config.autoQuoteUnquoted) {
            return value;
        }
    }
    
    // 如果需要自动加引号
    if (config.autoQuoteUnquoted) {
        std::string quoted = CHTLJSStateMachineHelper::quoteUnquotedLiteral(value);
        registerUnquotedLiteral(value, quoted);
        return quoted;
    }
    
    return value;
}

void CHTLJSContext::registerUnquotedLiteral(const std::string& original, const std::string& quoted) {
    unquotedLiterals[original] = quoted;
}

void CHTLJSContext::addDOMReference(const std::string& selector, const std::string& jsCode) {
    domReferences[selector] = jsCode;
}

std::string CHTLJSContext::getDOMReference(const std::string& selector) const {
    auto it = domReferences.find(selector);
    if (it != domReferences.end()) {
        return it->second;
    }
    return "";
}

void CHTLJSContext::addEventBinding(const std::string& selector, const std::string& event) {
    eventBindings.push_back({selector, event});
}

void CHTLJSContext::reportError(const std::string& error) {
    if (baseContext) {
        baseContext->reportError("[CHTL JS] " + error);
    } else {
        std::cerr << "[CHTL JS Error] " << error << std::endl;
    }
}

void CHTLJSContext::reportWarning(const std::string& warning) {
    if (baseContext) {
        // baseContext可能没有reportWarning，使用reportError
        baseContext->reportError("[CHTL JS Warning] " + warning);
    } else {
        std::cerr << "[CHTL JS Warning] " << warning << std::endl;
    }
}

void CHTLJSContext::reset() {
    stateMachine->reset();
    currentScope = globalScope;
    while (!scopeStack.empty()) {
        scopeStack.pop();
    }
    domReferences.clear();
    eventBindings.clear();
    animations.clear();
    unquotedLiterals.clear();
}

void CHTLJSContext::dumpSymbols() const {
    std::cout << "=== CHTL JS Symbols ===" << std::endl;
    
    std::function<void(std::shared_ptr<CHTLJSScope>, int)> dumpScope = 
        [&](std::shared_ptr<CHTLJSScope> scope, int indent) {
            std::string indentStr(indent * 2, ' ');
            std::cout << indentStr << "Scope: " << scope->getName() << std::endl;
            
            // 这里需要访问scope的symbols，但是是private的
            // 实际实现中需要添加getter或者friend函数
        };
    
    dumpScope(globalScope, 0);
}

void CHTLJSContext::dumpUnquotedLiterals() const {
    std::cout << "=== Unquoted Literals ===" << std::endl;
    for (const auto& [original, quoted] : unquotedLiterals) {
        std::cout << original << " -> " << quoted << std::endl;
    }
}

// CHTLJSContextHelper 实现
namespace CHTLJSContextHelper {

bool needsQuotes(const std::string& value) {
    // 检查是否需要引号
    // 1. 如果是数字，不需要引号
    std::regex numberRegex(R"(^\d+(\.\d+)?$)");
    if (std::regex_match(value, numberRegex)) {
        return false;
    }
    
    // 2. 如果是布尔值或null，不需要引号
    if (value == "true" || value == "false" || value == "null" || value == "undefined") {
        return false;
    }
    
    // 3. 如果是有效的标识符，在某些上下文中不需要引号
    if (isValidIdentifier(value)) {
        // 需要根据上下文判断
        return false;
    }
    
    // 4. 其他情况需要引号
    return true;
}

std::string smartQuote(const std::string& value) {
    if (!needsQuotes(value)) {
        return value;
    }
    
    // 如果包含单引号，使用双引号
    if (value.find('\'') != std::string::npos) {
        return "\"" + value + "\"";
    }
    
    // 否则使用单引号
    return "'" + value + "'";
}

bool isValidIdentifier(const std::string& identifier) {
    if (identifier.empty()) {
        return false;
    }
    
    // 必须以字母或下划线开头
    if (!std::isalpha(identifier[0]) && identifier[0] != '_') {
        return false;
    }
    
    // 后续字符可以是字母、数字或下划线
    for (size_t i = 1; i < identifier.length(); ++i) {
        if (!std::isalnum(identifier[i]) && identifier[i] != '_') {
            return false;
        }
    }
    
    return true;
}

std::string extractSelectorType(const std::string& selector) {
    if (selector.empty()) {
        return "unknown";
    }
    
    if (selector[0] == '.') {
        return "class";
    } else if (selector[0] == '#') {
        return "id";
    } else if (selector.find('[') != std::string::npos) {
        return "indexed";
    } else if (selector.find(' ') != std::string::npos) {
        return "descendant";
    } else {
        return "tag";
    }
}

} // namespace CHTLJSContextHelper

} // namespace chtl