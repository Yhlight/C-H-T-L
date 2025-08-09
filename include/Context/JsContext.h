#ifndef CHTL_JS_CONTEXT_H
#define CHTL_JS_CONTEXT_H

#include "Context/BasicContext.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace chtl {

// JavaScript上下文 - 管理JS解析过程中的信息
class JsContext : public BasicContext {
private:
    // 函数信息
    struct FunctionInfo {
        std::string name;
        std::vector<std::string> parameters;
        bool isAsync;
        bool isGenerator;
        bool isArrow;
        int line;
    };
    
    // 类信息
    struct ClassInfo {
        std::string name;
        std::string superClass;
        std::vector<std::string> methods;
        std::vector<std::string> fields;
        int line;
    };
    
    // 变量信息
    struct VariableInfo {
        std::string name;
        enum Type { VAR, LET, CONST } type;
        int scopeLevel;
        int line;
    };
    
    // 符号表
    std::unordered_map<std::string, std::vector<FunctionInfo>> functions_;
    std::unordered_map<std::string, ClassInfo> classes_;
    std::unordered_map<std::string, std::vector<VariableInfo>> variables_;
    
    // 导入导出信息
    std::vector<std::string> imports_;
    std::vector<std::string> exports_;
    std::unordered_set<std::string> dependencies_;
    
    // 当前解析状态
    std::string currentFunction_;
    std::string currentClass_;
    int currentScopeLevel_;
    
    // 标识符集合
    std::unordered_set<std::string> identifiers_;
    
    // 统计信息
    int functionCount_;
    int classCount_;
    int variableCount_;

public:
    JsContext();
    virtual ~JsContext() = default;
    
    // BasicContext接口实现
    void enterScope() override;
    void exitScope() override;
    void reset() override;
    
    // 函数管理
    void addFunction(const std::string& name, const std::vector<std::string>& params,
                     bool isAsync = false, bool isGenerator = false, bool isArrow = false);
    bool hasFunction(const std::string& name) const;
    std::vector<FunctionInfo> getFunctions(const std::string& name) const;
    
    // 类管理
    void addClass(const std::string& name, const std::string& superClass = "");
    void addMethod(const std::string& className, const std::string& methodName);
    void addField(const std::string& className, const std::string& fieldName);
    bool hasClass(const std::string& name) const;
    
    // 变量管理
    void addVariable(const std::string& name, VariableInfo::Type type);
    bool hasVariable(const std::string& name) const;
    bool isConstant(const std::string& name) const;
    
    // 导入导出管理
    void addImport(const std::string& import);
    void addExport(const std::string& exp);
    void addDependency(const std::string& dep);
    
    // 标识符管理
    void addIdentifier(const std::string& id);
    bool hasIdentifier(const std::string& id) const;
    std::vector<std::string> getAllIdentifiers() const;
    
    // 当前状态管理
    void setCurrentFunction(const std::string& func) { currentFunction_ = func; }
    void setCurrentClass(const std::string& cls) { currentClass_ = cls; }
    
    std::string getCurrentFunction() const { return currentFunction_; }
    std::string getCurrentClass() const { return currentClass_; }
    int getCurrentScopeLevel() const { return currentScopeLevel_; }
    
    // 统计信息
    int getFunctionCount() const { return functionCount_; }
    int getClassCount() const { return classCount_; }
    int getVariableCount() const { return variableCount_; }
    
    // JS验证
    bool isValidIdentifier(const std::string& id) const;
    bool isReservedWord(const std::string& word) const;
    bool checkVariableRedeclaration(const std::string& name) const;
};

} // namespace chtl

#endif // CHTL_JS_CONTEXT_H