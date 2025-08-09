#include "context/BasicContext.h"
#include <iostream>
#include <sstream>

namespace chtl {

BasicContext::BasicContext(ContextType type, const std::string& name)
    : type_(type), name_(name) {
    // 创建全局作用域
    currentScope_ = std::make_shared<ScopeInfo>(ScopeType::GLOBAL, "global");
    scopeStack_.push(currentScope_);
}

void BasicContext::enterScope(ScopeType scopeType, const std::string& scopeName) {
    auto newScope = std::make_shared<ScopeInfo>(scopeType, scopeName);
    newScope->parent = currentScope_;
    currentScope_ = newScope;
    scopeStack_.push(currentScope_);
}

void BasicContext::exitScope() {
    if (scopeStack_.size() > 1) {  // 保留全局作用域
        scopeStack_.pop();
        if (!scopeStack_.empty()) {
            currentScope_ = scopeStack_.top();
        }
    }
}

bool BasicContext::isInScope(ScopeType scopeType) const {
    auto scope = currentScope_;
    while (scope) {
        if (scope->type == scopeType) {
            return true;
        }
        scope = scope->parent;
    }
    return false;
}

bool BasicContext::addSymbol(const std::string& name, const SymbolInfo& info) {
    if (!currentScope_) {
        return false;
    }
    
    // 检查当前作用域是否已存在
    if (currentScope_->symbols.find(name) != currentScope_->symbols.end()) {
        addWarning(formatWarning("Symbol '" + name + "' already exists in current scope", 
                               info.line, info.column));
        return false;
    }
    
    currentScope_->symbols[name] = info;
    return true;
}

bool BasicContext::hasSymbol(const std::string& name) const {
    if (!currentScope_) {
        return false;
    }
    return currentScope_->symbols.find(name) != currentScope_->symbols.end();
}

SymbolInfo* BasicContext::getSymbol(const std::string& name) {
    if (!currentScope_) {
        return nullptr;
    }
    
    auto it = currentScope_->symbols.find(name);
    if (it != currentScope_->symbols.end()) {
        return &it->second;
    }
    return nullptr;
}

const SymbolInfo* BasicContext::getSymbol(const std::string& name) const {
    if (!currentScope_) {
        return nullptr;
    }
    
    auto it = currentScope_->symbols.find(name);
    if (it != currentScope_->symbols.end()) {
        return &it->second;
    }
    return nullptr;
}

bool BasicContext::removeSymbol(const std::string& name) {
    if (!currentScope_) {
        return false;
    }
    
    auto it = currentScope_->symbols.find(name);
    if (it != currentScope_->symbols.end()) {
        currentScope_->symbols.erase(it);
        return true;
    }
    return false;
}

SymbolInfo* BasicContext::lookupSymbol(const std::string& name) {
    auto scope = currentScope_;
    while (scope) {
        auto it = scope->symbols.find(name);
        if (it != scope->symbols.end()) {
            return &it->second;
        }
        scope = scope->parent;
    }
    
    // 检查全局符号表
    auto it = globalSymbols_.find(name);
    if (it != globalSymbols_.end()) {
        return &it->second;
    }
    
    return nullptr;
}

const SymbolInfo* BasicContext::lookupSymbol(const std::string& name) const {
    auto scope = currentScope_;
    while (scope) {
        auto it = scope->symbols.find(name);
        if (it != scope->symbols.end()) {
            return &it->second;
        }
        scope = scope->parent;
    }
    
    // 检查全局符号表
    auto it = globalSymbols_.find(name);
    if (it != globalSymbols_.end()) {
        return &it->second;
    }
    
    return nullptr;
}

std::string BasicContext::getConfig(const std::string& key, const std::string& defaultValue) const {
    auto it = config_.find(key);
    if (it != config_.end()) {
        return it->second;
    }
    return defaultValue;
}

void BasicContext::reset() {
    // 清空作用域栈，重新创建全局作用域
    while (!scopeStack_.empty()) {
        scopeStack_.pop();
    }
    
    currentScope_ = std::make_shared<ScopeInfo>(ScopeType::GLOBAL, "global");
    scopeStack_.push(currentScope_);
    
    // 清空其他数据
    globalSymbols_.clear();
    errors_.clear();
    warnings_.clear();
    config_.clear();
}

void BasicContext::printDebugInfo() const {
    std::cout << "=== Context Debug Info ===" << std::endl;
    std::cout << "Type: " << static_cast<int>(type_) << std::endl;
    std::cout << "Name: " << name_ << std::endl;
    
    // 打印作用域信息
    std::cout << "\nScope Stack (size: " << scopeStack_.size() << "):" << std::endl;
    auto tempStack = scopeStack_;
    int level = 0;
    while (!tempStack.empty()) {
        auto scope = tempStack.top();
        tempStack.pop();
        std::cout << "  Level " << level++ << ": " << scope->name 
                  << " (type: " << static_cast<int>(scope->type) << ")" << std::endl;
    }
    
    // 打印当前作用域的符号
    if (currentScope_) {
        std::cout << "\nCurrent Scope Symbols:" << std::endl;
        for (const auto& [name, info] : currentScope_->symbols) {
            std::cout << "  " << name << " (type: " << static_cast<int>(info.type) 
                      << ", line: " << info.line << ")" << std::endl;
        }
    }
    
    // 打印全局符号
    std::cout << "\nGlobal Symbols:" << std::endl;
    for (const auto& [name, info] : globalSymbols_) {
        std::cout << "  " << name << " (type: " << static_cast<int>(info.type) 
                  << ", line: " << info.line << ")" << std::endl;
    }
    
    // 打印错误和警告
    if (!errors_.empty()) {
        std::cout << "\nErrors:" << std::endl;
        for (const auto& error : errors_) {
            std::cout << "  " << error << std::endl;
        }
    }
    
    if (!warnings_.empty()) {
        std::cout << "\nWarnings:" << std::endl;
        for (const auto& warning : warnings_) {
            std::cout << "  " << warning << std::endl;
        }
    }
    
    // 打印配置
    if (!config_.empty()) {
        std::cout << "\nConfiguration:" << std::endl;
        for (const auto& [key, value] : config_) {
            std::cout << "  " << key << " = " << value << std::endl;
        }
    }
}

std::string BasicContext::formatError(const std::string& message, int line, int column) const {
    std::stringstream ss;
    ss << "Error at " << line << ":" << column << " - " << message;
    return ss.str();
}

std::string BasicContext::formatWarning(const std::string& message, int line, int column) const {
    std::stringstream ss;
    ss << "Warning at " << line << ":" << column << " - " << message;
    return ss.str();
}

} // namespace chtl