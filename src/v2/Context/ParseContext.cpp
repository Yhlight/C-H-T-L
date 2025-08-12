#include "v2/Context/ParseContext.h"
#include <sstream>
#include <stdexcept>

namespace chtl::v2 {

// ===== ParseContext 实现 =====

ParseContext::ParseContext(ChtlParseState state) 
    : state_(state)
    , currentNode_(nullptr)
    , currentScope_(std::make_shared<Scope>("global")) {
    scopeStack_.push_back(currentScope_);
}

ParseContext::~ParseContext() = default;

void ParseContext::enterScope(const std::string& name) {
    auto newScope = std::make_shared<Scope>(name, currentScope_);
    scopeStack_.push_back(newScope);
    currentScope_ = newScope;
}

void ParseContext::exitScope() {
    if (scopeStack_.size() <= 1) {
        throw std::runtime_error("Cannot exit global scope");
    }
    
    scopeStack_.pop_back();
    currentScope_ = scopeStack_.back();
}

void ParseContext::defineVariable(const std::string& name, const std::string& value) {
    currentScope_->define(name, value);
}

bool ParseContext::hasVariable(const std::string& name) const {
    return currentScope_->has(name);
}

std::string ParseContext::getVariable(const std::string& name) const {
    return currentScope_->get(name);
}

void ParseContext::defineParameter(const std::string& name) {
    currentScope_->defineParameter(name);
    templateData_.parameters.push_back(name);
}

bool ParseContext::isParameter(const std::string& name) const {
    return currentScope_->isParameter(name);
}

std::string ParseContext::toString() const {
    std::stringstream ss;
    ss << "ParseContext {\n";
    ss << "  state: " << getStateName(state_) << "\n";
    ss << "  location: " << currentLine_ << ":" << currentColumn_ << "\n";
    ss << "  scope: " << currentScope_->getName() << "\n";
    
    if (!templateData_.templateName.empty()) {
        ss << "  template: " << templateData_.templateName;
        if (!templateData_.parameters.empty()) {
            ss << "(";
            for (size_t i = 0; i < templateData_.parameters.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << templateData_.parameters[i];
            }
            ss << ")";
        }
        ss << "\n";
    }
    
    if (!elementData_.tagName.empty()) {
        ss << "  element: " << elementData_.tagName;
        if (!elementData_.id.empty()) {
            ss << "#" << elementData_.id;
        }
        for (const auto& cls : elementData_.classes) {
            ss << "." << cls;
        }
        ss << "\n";
    }
    
    if (!cssData_.currentSelector.empty()) {
        ss << "  css selector: " << cssData_.currentSelector << "\n";
    }
    if (!cssData_.currentPropertyName.empty()) {
        ss << "  css property: " << cssData_.currentPropertyName;
        if (!cssData_.currentPropertyValue.empty()) {
            ss << ": " << cssData_.currentPropertyValue;
        }
        ss << "\n";
    }
    
    ss << "}";
    return ss.str();
}

// ===== Scope 实现 =====

Scope::Scope(const std::string& name, std::shared_ptr<Scope> parent)
    : name_(name), parent_(parent) {}

void Scope::define(const std::string& name, const std::string& value) {
    variables_[name] = value;
}

bool Scope::has(const std::string& name) const {
    // 先在当前作用域查找
    if (variables_.find(name) != variables_.end()) {
        return true;
    }
    
    // 检查是否是参数
    for (const auto& param : parameters_) {
        if (param == name) {
            return true;
        }
    }
    
    // 在父作用域查找
    if (parent_) {
        return parent_->has(name);
    }
    
    return false;
}

std::string Scope::get(const std::string& name) const {
    // 先在当前作用域查找
    auto it = variables_.find(name);
    if (it != variables_.end()) {
        return it->second;
    }
    
    // 检查是否是参数（参数值需要在运行时提供）
    for (const auto& param : parameters_) {
        if (param == name) {
            return "{" + name + "}";  // 返回占位符
        }
    }
    
    // 在父作用域查找
    if (parent_) {
        return parent_->get(name);
    }
    
    throw std::runtime_error("Variable not found: " + name);
}

void Scope::defineParameter(const std::string& name) {
    parameters_.push_back(name);
}

bool Scope::isParameter(const std::string& name) const {
    for (const auto& param : parameters_) {
        if (param == name) {
            return true;
        }
    }
    
    // 也检查父作用域
    if (parent_) {
        return parent_->isParameter(name);
    }
    
    return false;
}

} // namespace chtl::v2