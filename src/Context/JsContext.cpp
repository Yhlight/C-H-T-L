#include "Context/JsContext.h"
#include <algorithm>
#include <regex>

namespace chtl {

JsContext::JsContext() 
    : BasicContext(ContextType::JS, "JsContext"),
      currentScopeLevel_(0),
      functionCount_(0),
      classCount_(0),
      variableCount_(0) {
}

void JsContext::enterScope() {
    BasicContext::enterScope();
    currentScopeLevel_++;
}

void JsContext::exitScope() {
    BasicContext::exitScope();
    
    // 清理当前作用域的变量
    auto it = variables_.begin();
    while (it != variables_.end()) {
        auto& varList = it->second;
        varList.erase(
            std::remove_if(varList.begin(), varList.end(),
                [this](const VariableInfo& var) {
                    return var.scopeLevel == currentScopeLevel_;
                }),
            varList.end()
        );
        
        if (varList.empty()) {
            it = variables_.erase(it);
        } else {
            ++it;
        }
    }
    
    currentScopeLevel_--;
}

void JsContext::reset() {
    BasicContext::reset();
    
    functions_.clear();
    classes_.clear();
    variables_.clear();
    imports_.clear();
    exports_.clear();
    dependencies_.clear();
    identifiers_.clear();
    currentFunction_.clear();
    currentClass_.clear();
    currentScopeLevel_ = 0;
    functionCount_ = 0;
    classCount_ = 0;
    variableCount_ = 0;
}

void JsContext::addFunction(const std::string& name, const std::vector<std::string>& params,
                           bool isAsync, bool isGenerator, bool isArrow) {
    FunctionInfo info;
    info.name = name;
    info.parameters = params;
    info.isAsync = isAsync;
    info.isGenerator = isGenerator;
    info.isArrow = isArrow;
    info.line = getCurrentLine();
    
    functions_[name].push_back(info);
    addIdentifier(name);
    functionCount_++;
}

bool JsContext::hasFunction(const std::string& name) const {
    return functions_.find(name) != functions_.end();
}

std::vector<JsContext::FunctionInfo> JsContext::getFunctions(const std::string& name) const {
    auto it = functions_.find(name);
    if (it != functions_.end()) {
        return it->second;
    }
    return {};
}

void JsContext::addClass(const std::string& name, const std::string& superClass) {
    ClassInfo info;
    info.name = name;
    info.superClass = superClass;
    info.line = getCurrentLine();
    
    classes_[name] = info;
    addIdentifier(name);
    classCount_++;
}

void JsContext::addMethod(const std::string& className, const std::string& methodName) {
    auto it = classes_.find(className);
    if (it != classes_.end()) {
        it->second.methods.push_back(methodName);
    }
}

void JsContext::addField(const std::string& className, const std::string& fieldName) {
    auto it = classes_.find(className);
    if (it != classes_.end()) {
        it->second.fields.push_back(fieldName);
    }
}

bool JsContext::hasClass(const std::string& name) const {
    return classes_.find(name) != classes_.end();
}

void JsContext::addVariable(const std::string& name, VariableInfo::Type type) {
    VariableInfo info;
    info.name = name;
    info.type = type;
    info.scopeLevel = currentScopeLevel_;
    info.line = getCurrentLine();
    
    variables_[name].push_back(info);
    addIdentifier(name);
    variableCount_++;
}

bool JsContext::hasVariable(const std::string& name) const {
    return variables_.find(name) != variables_.end();
}

bool JsContext::isConstant(const std::string& name) const {
    auto it = variables_.find(name);
    if (it != variables_.end() && !it->second.empty()) {
        // 返回最近声明的变量是否是const
        return it->second.back().type == VariableInfo::CONST;
    }
    return false;
}

void JsContext::addImport(const std::string& import) {
    imports_.push_back(import);
    
    // 提取依赖
    std::regex fromRegex(R"(from\s+['"](.*?)['"])");
    std::smatch match;
    if (std::regex_search(import, match, fromRegex)) {
        addDependency(match[1]);
    }
}

void JsContext::addExport(const std::string& exp) {
    exports_.push_back(exp);
}

void JsContext::addDependency(const std::string& dep) {
    dependencies_.insert(dep);
}

void JsContext::addIdentifier(const std::string& id) {
    identifiers_.insert(id);
}

bool JsContext::hasIdentifier(const std::string& id) const {
    return identifiers_.find(id) != identifiers_.end();
}

std::vector<std::string> JsContext::getAllIdentifiers() const {
    return std::vector<std::string>(identifiers_.begin(), identifiers_.end());
}

bool JsContext::isValidIdentifier(const std::string& id) const {
    if (id.empty()) return false;
    
    // JavaScript标识符规则
    static const std::regex identifierPattern(R"(^[a-zA-Z_$][a-zA-Z0-9_$]*$)");
    return std::regex_match(id, identifierPattern) && !isReservedWord(id);
}

bool JsContext::isReservedWord(const std::string& word) const {
    static const std::unordered_set<std::string> reservedWords = {
        "break", "case", "catch", "class", "const", "continue", "debugger",
        "default", "delete", "do", "else", "export", "extends", "finally",
        "for", "function", "if", "import", "in", "instanceof", "new",
        "return", "super", "switch", "this", "throw", "try", "typeof",
        "var", "void", "while", "with", "yield", "let", "static",
        "enum", "implements", "interface", "package", "private", "protected",
        "public", "await", "async", "of", "as", "from", "get", "set"
    };
    
    return reservedWords.find(word) != reservedWords.end();
}

bool JsContext::checkVariableRedeclaration(const std::string& name) const {
    auto it = variables_.find(name);
    if (it == variables_.end()) return false;
    
    // 检查同一作用域内的重复声明
    const auto& varList = it->second;
    int count = 0;
    for (const auto& var : varList) {
        if (var.scopeLevel == currentScopeLevel_) {
            count++;
            if (count > 1 && (var.type == VariableInfo::LET || var.type == VariableInfo::CONST)) {
                return true;  // let和const不允许重复声明
            }
        }
    }
    
    return false;
}

} // namespace chtl