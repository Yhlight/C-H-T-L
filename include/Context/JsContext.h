#ifndef CHTL_JS_CONTEXT_H
#define CHTL_JS_CONTEXT_H

#include "Context/BasicContext.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

namespace chtl {

// JavaScript上下文 - 管理JS解析过程中的信息
class JsContext : public BasicContext {
public:
    // 函数信息
    struct FunctionInfo {
        std::string name;
        bool isAsync;
        bool isGenerator;
        int line;
        int column;
    };
    
    // 类信息
    struct ClassInfo {
        std::string name;
        int line;
        int column;
    };
    
    // 变量信息
    struct VariableInfo {
        std::string name;
        std::string type;
        bool isConst;
        int line;
        int column;
    };
    
    // 导入信息
    struct ImportInfo {
        std::string module;
        std::string alias;
        int line;
        int column;
    };
    
    // 导出信息
    struct ExportInfo {
        std::string name;
        bool isDefault;
        int line;
        int column;
    };
    
    JsContext();
    virtual ~JsContext() = default;
    
    // BasicContext接口实现
    void enterScope(ScopeType scopeType, const std::string& scopeName = "") override;
    void exitScope() override;
    void reset() override;
    bool validate() override { return true; } // Placeholder implementation
    
    // JS符号管理
    void addFunction(const std::string& name, bool isAsync = false, bool isGenerator = false);
    void addClass(const std::string& name);
    void addVariable(const std::string& name, const std::string& type = "var", bool isConst = false);
    
    bool hasFunction(const std::string& name) const;
    bool hasClass(const std::string& name) const;
    bool hasVariable(const std::string& name) const;
    
    // 模块管理
    void addImport(const std::string& module, const std::string& alias = "");
    void addExport(const std::string& name, bool isDefault = false);
    
    std::vector<ImportInfo> getImports() const;
    std::vector<ExportInfo> getExports() const;
    
    // 特性管理
    void setStrictMode(bool strict);
    bool isStrictMode() const;
    
    void setInAsyncFunction(bool async);
    bool isInAsyncFunction() const;
    
    void setInGeneratorFunction(bool generator);
    bool isInGeneratorFunction() const;
    
    // 作用域查询
    bool isInFunctionScope() const;
    bool isInBlockScope() const;
    int getFunctionDepth() const;
    int getBlockDepth() const;
    
    // 变量提升
    void addHoistedVar(const std::string& name);
    bool isHoistedVar(const std::string& name) const;
    
    // 获取符号信息
    const FunctionInfo* getFunctionInfo(const std::string& name) const;
    const ClassInfo* getClassInfo(const std::string& name) const;
    const VariableInfo* getVariableInfo(const std::string& name) const;
    
private:
    // 符号表
    std::map<std::string, FunctionInfo> functions_;
    std::map<std::string, ClassInfo> classes_;  
    std::map<std::string, VariableInfo> variables_;
    std::vector<ImportInfo> imports_;
    std::vector<ExportInfo> exports_;
    
    // 特定符号集合
    std::set<std::string> asyncFunctions_;
    std::set<std::string> generatorFunctions_;
    std::set<std::string> hoistedVars_;
    
    // 状态标志
    bool inStrictMode_;
    bool inAsyncFunction_;
    bool inGeneratorFunction_;
    int currentFunctionDepth_;
    int currentBlockDepth_;
};

} // namespace chtl

#endif // CHTL_JS_CONTEXT_H