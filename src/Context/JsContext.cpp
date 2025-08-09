#include "Context/JsContext.h"
#include <algorithm>
#include <regex>

namespace chtl {

JsContext::JsContext() : BasicContext(ContextType::JS, "JsContext") {
    // 初始化JS特定的状态
    inStrictMode_ = false;
    inAsyncFunction_ = false;
    inGeneratorFunction_ = false;
    currentFunctionDepth_ = 0;
    currentBlockDepth_ = 0;
}

// 上下文管理
void JsContext::enterScope(ScopeType scopeType, const std::string& scopeName) {
    // 调用基类方法
    BasicContext::enterScope(scopeType, scopeName);
    
    // JS特定的作用域处理
    if (scopeType == ScopeType::FUNCTION) {
        currentFunctionDepth_++;
    } else if (scopeType == ScopeType::BLOCK) {
        currentBlockDepth_++;
    }
}

void JsContext::exitScope() {
    // JS特定的作用域处理
    auto scope = getCurrentScope();
    if (scope) {
        if (scope->type == ScopeType::FUNCTION) {
            currentFunctionDepth_--;
        } else if (scope->type == ScopeType::BLOCK) {
            currentBlockDepth_--;
        }
    }
    
    // 调用基类方法
    BasicContext::exitScope();
}

void JsContext::reset() {
    BasicContext::reset();
    
    // 重置JS特定状态
    functions_.clear();
    classes_.clear();
    variables_.clear();
    imports_.clear();
    exports_.clear();
    asyncFunctions_.clear();
    generatorFunctions_.clear();
    hoistedVars_.clear();
    inStrictMode_ = false;
    inAsyncFunction_ = false;
    inGeneratorFunction_ = false;
    currentFunctionDepth_ = 0;
    currentBlockDepth_ = 0;
}

// JS符号管理
void JsContext::addFunction(const std::string& name, bool isAsync, bool isGenerator) {
    FunctionInfo info;
    info.name = name;
    info.isAsync = isAsync;
    info.isGenerator = isGenerator;
    info.line = 0; // TODO: Get from lexer/parser
    info.column = 0; // TODO: Get from lexer/parser
    
    functions_[name] = info;
    
    if (isAsync) {
        asyncFunctions_.insert(name);
    }
    if (isGenerator) {
        generatorFunctions_.insert(name);
    }
}

void JsContext::addClass(const std::string& name) {
    ClassInfo info;
    info.name = name;
    info.line = 0; // TODO: Get from lexer/parser
    info.column = 0; // TODO: Get from lexer/parser
    
    classes_[name] = info;
}

void JsContext::addVariable(const std::string& name, const std::string& type, bool isConst) {
    VariableInfo info;
    info.name = name;
    info.type = type;
    info.isConst = isConst;
    info.line = 0; // TODO: Get from lexer/parser
    info.column = 0; // TODO: Get from lexer/parser
    
    variables_[name] = info;
}

bool JsContext::hasFunction(const std::string& name) const {
    return functions_.find(name) != functions_.end();
}

bool JsContext::hasClass(const std::string& name) const {
    return classes_.find(name) != classes_.end();
}

bool JsContext::hasVariable(const std::string& name) const {
    return variables_.find(name) != variables_.end();
}

// 模块管理
void JsContext::addImport(const std::string& module, const std::string& alias) {
    ImportInfo info;
    info.module = module;
    info.alias = alias;
    info.line = 0; // TODO: Get from lexer/parser
    info.column = 0; // TODO: Get from lexer/parser
    
    imports_.push_back(info);
}

void JsContext::addExport(const std::string& name, bool isDefault) {
    ExportInfo info;
    info.name = name;
    info.isDefault = isDefault;
    info.line = 0; // TODO: Get from lexer/parser
    info.column = 0; // TODO: Get from lexer/parser
    
    exports_.push_back(info);
}

std::vector<JsContext::ImportInfo> JsContext::getImports() const {
    return imports_;
}

std::vector<JsContext::ExportInfo> JsContext::getExports() const {
    return exports_;
}

// 特性管理
void JsContext::setStrictMode(bool strict) {
    inStrictMode_ = strict;
}

bool JsContext::isStrictMode() const {
    return inStrictMode_;
}

void JsContext::setInAsyncFunction(bool async) {
    inAsyncFunction_ = async;
}

bool JsContext::isInAsyncFunction() const {
    return inAsyncFunction_;
}

void JsContext::setInGeneratorFunction(bool generator) {
    inGeneratorFunction_ = generator;
}

bool JsContext::isInGeneratorFunction() const {
    return inGeneratorFunction_;
}

// 作用域查询
bool JsContext::isInFunctionScope() const {
    return currentFunctionDepth_ > 0;
}

bool JsContext::isInBlockScope() const {
    return currentBlockDepth_ > 0;
}

int JsContext::getFunctionDepth() const {
    return currentFunctionDepth_;
}

int JsContext::getBlockDepth() const {
    return currentBlockDepth_;
}

// 变量提升
void JsContext::addHoistedVar(const std::string& name) {
    hoistedVars_.insert(name);
}

bool JsContext::isHoistedVar(const std::string& name) const {
    return hoistedVars_.find(name) != hoistedVars_.end();
}

// 获取符号信息
const JsContext::FunctionInfo* JsContext::getFunctionInfo(const std::string& name) const {
    auto it = functions_.find(name);
    if (it != functions_.end()) {
        return &it->second;
    }
    return nullptr;
}

const JsContext::ClassInfo* JsContext::getClassInfo(const std::string& name) const {
    auto it = classes_.find(name);
    if (it != classes_.end()) {
        return &it->second;
    }
    return nullptr;
}

const JsContext::VariableInfo* JsContext::getVariableInfo(const std::string& name) const {
    auto it = variables_.find(name);
    if (it != variables_.end()) {
        return &it->second;
    }
    return nullptr;
}

} // namespace chtl