#include "SymbolTable.h"
#include <algorithm>

namespace CHTL {

// Symbol实现
Symbol::Symbol(const std::string& name, SymbolType type) 
    : name_(name), type_(type) {}

// Scope实现
Scope::Scope(const std::string& name, Scope* parent) 
    : name_(name), parent_(parent) {}

bool Scope::addSymbol(std::shared_ptr<Symbol> symbol) {
    if (!symbol) return false;
    
    // 检查是否已存在同名同类型的符号
    auto range = symbols_.equal_range(symbol->getName());
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second->getType() == symbol->getType()) {
            return false; // 已存在
        }
    }
    
    symbols_.emplace(symbol->getName(), symbol);
    return true;
}

std::shared_ptr<Symbol> Scope::findSymbol(const std::string& name, SymbolType type) const {
    // 先在当前作用域查找
    auto symbol = findSymbolInScope(name, type);
    if (symbol) return symbol;
    
    // 递归在父作用域查找
    if (parent_) {
        return parent_->findSymbol(name, type);
    }
    
    return nullptr;
}

std::shared_ptr<Symbol> Scope::findSymbolInScope(const std::string& name, SymbolType type) const {
    auto range = symbols_.equal_range(name);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second->getType() == type) {
            return it->second;
        }
    }
    return nullptr;
}

Scope* Scope::createChildScope(const std::string& name) {
    children_.push_back(std::make_unique<Scope>(name, this));
    return children_.back().get();
}

// SymbolTable实现
SymbolTable::SymbolTable() {
    rootScope_ = std::make_unique<Scope>("global");
    currentScope_ = rootScope_.get();
}

void SymbolTable::enterScope(const std::string& name) {
    currentScope_ = currentScope_->createChildScope(name);
}

void SymbolTable::exitScope() {
    if (currentScope_ && currentScope_->getParent()) {
        currentScope_ = currentScope_->getParent();
    }
}

bool SymbolTable::defineSymbol(const std::string& name, SymbolType type) {
    auto symbol = std::make_shared<Symbol>(name, type);
    return defineSymbol(symbol);
}

bool SymbolTable::defineSymbol(std::shared_ptr<Symbol> symbol) {
    if (!symbol || !currentScope_) return false;
    
    // 如果在命名空间中，设置命名空间
    if (!namespaceStack_.empty()) {
        std::string fullNamespace;
        for (const auto& ns : namespaceStack_) {
            if (!fullNamespace.empty()) fullNamespace += ".";
            fullNamespace += ns;
        }
        symbol->setNamespace(fullNamespace);
    }
    
    return currentScope_->addSymbol(symbol);
}

std::shared_ptr<Symbol> SymbolTable::lookupSymbol(const std::string& name, SymbolType type) const {
    if (!currentScope_) return nullptr;
    
    // 如果名称包含命名空间（如 space.room.Box）
    size_t dotPos = name.find('.');
    if (dotPos != std::string::npos) {
        // TODO: 实现命名空间查找
    }
    
    return currentScope_->findSymbol(name, type);
}

bool SymbolTable::defineNamespace(const std::string& name) {
    auto symbol = std::make_shared<Symbol>(name, SymbolType::NAMESPACE);
    return defineSymbol(symbol);
}

bool SymbolTable::enterNamespace(const std::string& name) {
    namespaceStack_.push_back(name);
    enterScope("namespace:" + name);
    return true;
}

void SymbolTable::exitNamespace() {
    if (!namespaceStack_.empty()) {
        namespaceStack_.pop_back();
        exitScope();
    }
}

std::string SymbolTable::getCurrentNamespace() const {
    std::string result;
    for (const auto& ns : namespaceStack_) {
        if (!result.empty()) result += ".";
        result += ns;
    }
    return result;
}

void SymbolTable::addImport(const std::string& path, const std::string& alias) {
    imports_.push_back({path, alias});
}

std::vector<std::string> SymbolTable::getImports() const {
    std::vector<std::string> result;
    for (const auto& import : imports_) {
        result.push_back(import.first);
    }
    return result;
}

void SymbolTable::setConfiguration(const std::string& key, const std::string& value) {
    configurations_[key] = value;
}

std::string SymbolTable::getConfiguration(const std::string& key) const {
    auto it = configurations_.find(key);
    return (it != configurations_.end()) ? it->second : "";
}

bool SymbolTable::validateSymbolUsage(const std::string& name, SymbolType type) const {
    auto symbol = lookupSymbol(name, type);
    if (!symbol) {
        undefinedSymbols_.push_back(name);
        return false;
    }
    return true;
}

std::vector<std::string> SymbolTable::getUndefinedSymbols() const {
    // 去重
    std::vector<std::string> result = undefinedSymbols_;
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

} // namespace CHTL