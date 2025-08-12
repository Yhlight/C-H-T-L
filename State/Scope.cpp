#include "SymbolTable.h"
#include <sstream>

namespace CHTL {

Scope::Scope(const std::string& name, ScopeType type, Scope* parent)
    : name_(name), type_(type), parent_(parent) {
}

void Scope::addChild(ScopePtr child) {
    if (child) {
        children_.push_back(child);
    }
}

bool Scope::define(SymbolPtr symbol) {
    if (!symbol || symbol->getName().empty()) {
        return false;
    }
    
    // 检查是否已经定义
    if (symbols_.find(symbol->getName()) != symbols_.end()) {
        return false;
    }
    
    symbols_[symbol->getName()] = symbol;
    symbol->setScope(this);
    return true;
}

SymbolPtr Scope::lookup(const std::string& name) const {
    // 首先在当前作用域查找
    auto symbol = lookupLocal(name);
    if (symbol) {
        return symbol;
    }
    
    // 在父作用域递归查找
    if (parent_) {
        return parent_->lookup(name);
    }
    
    return nullptr;
}

SymbolPtr Scope::lookupLocal(const std::string& name) const {
    auto it = symbols_.find(name);
    if (it != symbols_.end()) {
        return it->second;
    }
    return nullptr;
}

std::string Scope::getQualifiedName() const {
    if (!parent_ || parent_->type_ == ScopeType::GLOBAL) {
        return name_;
    }
    
    std::string parentName = parent_->getQualifiedName();
    if (parentName.empty()) {
        return name_;
    }
    
    return parentName + "::" + name_;
}

std::string Scope::toString() const {
    std::stringstream ss;
    ss << "Scope[name=" << name_;
    ss << ", type=";
    
    switch (type_) {
        case ScopeType::GLOBAL:
            ss << "GLOBAL";
            break;
        case ScopeType::NAMESPACE:
            ss << "NAMESPACE";
            break;
        case ScopeType::TEMPLATE:
            ss << "TEMPLATE";
            break;
        case ScopeType::CUSTOM:
            ss << "CUSTOM";
            break;
        case ScopeType::ELEMENT:
            ss << "ELEMENT";
            break;
        case ScopeType::BLOCK:
            ss << "BLOCK";
            break;
    }
    
    ss << ", symbols=" << symbols_.size();
    ss << ", children=" << children_.size();
    
    if (!namespace_.empty()) {
        ss << ", namespace=" << namespace_;
    }
    
    if (parent_) {
        ss << ", parent=" << parent_->name_;
    }
    
    ss << "]";
    return ss.str();
}

} // namespace CHTL