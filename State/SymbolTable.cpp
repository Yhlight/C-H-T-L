#include "SymbolTable.h"
#include <iostream>
#include <sstream>

namespace CHTL {

SymbolTable::SymbolTable() {
    // 创建全局作用域
    globalScope_ = std::make_shared<Scope>("global", Scope::ScopeType::GLOBAL, nullptr);
    currentScope_ = globalScope_.get();
    scopeStack_.push(currentScope_);
}

void SymbolTable::enterScope(const std::string& name, Scope::ScopeType type) {
    auto newScope = std::make_shared<Scope>(name, type, currentScope_);
    currentScope_->addChild(newScope);
    currentScope_ = newScope.get();
    scopeStack_.push(currentScope_);
}

void SymbolTable::exitScope() {
    if (scopeStack_.size() > 1) {
        scopeStack_.pop();
        currentScope_ = scopeStack_.top();
    }
}

bool SymbolTable::defineSymbol(SymbolPtr symbol) {
    if (!symbol) {
        return false;
    }
    
    // 设置命名空间
    if (!currentNamespace_.empty()) {
        symbol->setAttribute("namespace", currentNamespace_);
    }
    
    return currentScope_->define(symbol);
}

SymbolPtr SymbolTable::lookupSymbol(const std::string& name) const {
    return currentScope_->lookup(name);
}

SymbolPtr SymbolTable::lookupSymbolInNamespace(const std::string& name, const std::string& ns) const {
    // 构建完整限定名
    std::string qualifiedName = ns.empty() ? name : ns + "::" + name;
    
    // 从全局作用域开始查找
    return lookupSymbolRecursive(globalScope_.get(), qualifiedName);
}

SymbolPtr SymbolTable::lookupSymbolRecursive(Scope* scope, const std::string& qualifiedName) const {
    if (!scope) {
        return nullptr;
    }
    
    // 在当前作用域查找
    auto symbol = scope->lookupLocal(qualifiedName);
    if (symbol) {
        return symbol;
    }
    
    // 在子作用域递归查找
    for (const auto& child : scope->getChildren()) {
        symbol = lookupSymbolRecursive(child.get(), qualifiedName);
        if (symbol) {
            return symbol;
        }
    }
    
    return nullptr;
}

void SymbolTable::enterNamespace(const std::string& ns) {
    namespaceStack_.push(currentNamespace_);
    currentNamespace_ = ns;
}

void SymbolTable::exitNamespace() {
    if (!namespaceStack_.empty()) {
        currentNamespace_ = namespaceStack_.top();
        namespaceStack_.pop();
    } else {
        currentNamespace_.clear();
    }
}

void SymbolTable::addImport(const std::string& path, const std::string& alias) {
    imports_[path] = alias;
}

bool SymbolTable::hasImport(const std::string& path) const {
    return imports_.find(path) != imports_.end();
}

std::string SymbolTable::getImportAlias(const std::string& path) const {
    auto it = imports_.find(path);
    if (it != imports_.end()) {
        return it->second;
    }
    return "";
}

std::vector<SymbolPtr> SymbolTable::getAllSymbols() const {
    std::vector<SymbolPtr> symbols;
    collectSymbols(globalScope_.get(), symbols);
    return symbols;
}

std::vector<SymbolPtr> SymbolTable::getSymbolsByType(SymbolType type) const {
    std::vector<SymbolPtr> result;
    auto allSymbols = getAllSymbols();
    
    for (const auto& symbol : allSymbols) {
        if (symbol->getType() == type) {
            result.push_back(symbol);
        }
    }
    
    return result;
}

void SymbolTable::collectSymbols(Scope* scope, std::vector<SymbolPtr>& symbols) const {
    if (!scope) {
        return;
    }
    
    // 收集当前作用域的符号
    for (const auto& [name, symbol] : scope->getSymbols()) {
        symbols.push_back(symbol);
    }
    
    // 递归收集子作用域的符号
    for (const auto& child : scope->getChildren()) {
        collectSymbols(child.get(), symbols);
    }
}

void SymbolTable::addError(const std::string& error, int line, int column) {
    std::stringstream ss;
    if (line > 0) {
        ss << "[" << line << ":" << column << "] ";
    }
    ss << error;
    errors_.push_back(ss.str());
}

void SymbolTable::clear() {
    globalScope_ = std::make_shared<Scope>("global", Scope::ScopeType::GLOBAL, nullptr);
    currentScope_ = globalScope_.get();
    
    // 清空栈
    while (!scopeStack_.empty()) {
        scopeStack_.pop();
    }
    scopeStack_.push(currentScope_);
    
    while (!namespaceStack_.empty()) {
        namespaceStack_.pop();
    }
    
    currentNamespace_.clear();
    imports_.clear();
    errors_.clear();
}

void SymbolTable::printSymbolTable() const {
    std::cout << "=== Symbol Table ===" << std::endl;
    printScope(globalScope_.get(), 0);
    
    if (!imports_.empty()) {
        std::cout << "\n=== Imports ===" << std::endl;
        for (const auto& [path, alias] : imports_) {
            std::cout << "  " << path;
            if (!alias.empty()) {
                std::cout << " as " << alias;
            }
            std::cout << std::endl;
        }
    }
    
    if (!errors_.empty()) {
        std::cout << "\n=== Errors ===" << std::endl;
        for (const auto& error : errors_) {
            std::cout << "  " << error << std::endl;
        }
    }
}

void SymbolTable::printScope(Scope* scope, int indent) const {
    if (!scope) {
        return;
    }
    
    // 打印缩进
    std::string indentStr(indent * 2, ' ');
    
    // 打印作用域信息
    std::cout << indentStr << scope->toString() << std::endl;
    
    // 打印符号
    for (const auto& [name, symbol] : scope->getSymbols()) {
        std::cout << indentStr << "  " << symbol->toString() << std::endl;
    }
    
    // 递归打印子作用域
    for (const auto& child : scope->getChildren()) {
        printScope(child.get(), indent + 1);
    }
}

} // namespace CHTL