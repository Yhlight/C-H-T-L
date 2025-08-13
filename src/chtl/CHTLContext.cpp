// CHTLContext.cpp - CHTL编译上下文实现
#include "CHTLContext.h"
#include <iostream>

namespace chtl {

CHTLContext::CHTLContext() 
    : errorHandler(std::make_shared<CHTLErrorHandler>()),
      currentMode(Mode::CHTL),
      debugMode(false),
      strictMode(false) {
    
    // 初始化默认配置
    initializeDefaultConfig();
}

CHTLContext::~CHTLContext() = default;

void CHTLContext::initializeDefaultConfig() {
    // 设置默认的CHTL配置
    config["version"] = "1.0.0";
    config["encoding"] = "utf-8";
    config["strict"] = false;
    config["optimize"] = true;
}

void CHTLContext::setVariable(const std::string& name, const std::string& value) {
    variables[name] = value;
}

std::string CHTLContext::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return "";
}

bool CHTLContext::hasVariable(const std::string& name) const {
    return variables.find(name) != variables.end();
}

void CHTLContext::removeVariable(const std::string& name) {
    variables.erase(name);
}

void CHTLContext::clearVariables() {
    variables.clear();
}

void CHTLContext::pushScope() {
    scopeStack.push(variables);
}

void CHTLContext::popScope() {
    if (!scopeStack.empty()) {
        variables = scopeStack.top();
        scopeStack.pop();
    }
}

void CHTLContext::setMode(Mode mode) {
    currentMode = mode;
}

CHTLContext::Mode CHTLContext::getMode() const {
    return currentMode;
}

void CHTLContext::setDebugMode(bool enabled) {
    debugMode = enabled;
}

bool CHTLContext::isDebugMode() const {
    return debugMode;
}

void CHTLContext::setStrictMode(bool enabled) {
    strictMode = enabled;
    config["strict"] = enabled;
}

bool CHTLContext::isStrictMode() const {
    return strictMode;
}

void CHTLContext::setConfig(const std::string& key, const std::string& value) {
    config[key] = value;
}

std::string CHTLContext::getConfig(const std::string& key) const {
    auto it = config.find(key);
    if (it != config.end()) {
        return it->second;
    }
    return "";
}

bool CHTLContext::hasConfig(const std::string& key) const {
    return config.find(key) != config.end();
}

void CHTLContext::addError(const std::string& message, int line, int column) {
    if (errorHandler) {
        errorHandler->reportError(message, "", line, column);
    }
}

void CHTLContext::addWarning(const std::string& message, int line, int column) {
    if (errorHandler) {
        errorHandler->reportWarning(message, "", line, column);
    }
}

bool CHTLContext::hasErrors() const {
    return errorHandler && errorHandler->hasErrors();
}

std::vector<CHTLError> CHTLContext::getErrors() const {
    if (errorHandler) {
        return errorHandler->getErrors();
    }
    return {};
}

void CHTLContext::clearErrors() {
    if (errorHandler) {
        errorHandler->clear();
    }
}

std::shared_ptr<CHTLErrorHandler> CHTLContext::getErrorHandler() const {
    return errorHandler;
}

void CHTLContext::reset() {
    clearVariables();
    clearErrors();
    currentMode = Mode::CHTL;
    debugMode = false;
    strictMode = false;
    initializeDefaultConfig();
    
    // 清空作用域栈
    while (!scopeStack.empty()) {
        scopeStack.pop();
    }
}

} // namespace chtl