#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

namespace chtl::v2::js {

/**
 * JavaScript 语法结构类型
 */
enum class JsNodeType {
    PROGRAM,
    FUNCTION_DECLARATION,
    VARIABLE_DECLARATION,
    CLASS_DECLARATION,
    IMPORT_DECLARATION,
    EXPORT_DECLARATION,
    IF_STATEMENT,
    FOR_STATEMENT,
    WHILE_STATEMENT,
    RETURN_STATEMENT,
    EXPRESSION_STATEMENT,
    BLOCK_STATEMENT,
    IDENTIFIER,
    LITERAL,
    CALL_EXPRESSION,
    MEMBER_EXPRESSION,
    ASSIGNMENT,
    BINARY_EXPRESSION,
    UNARY_EXPRESSION,
    UNKNOWN
};

/**
 * JavaScript 变量/函数信息
 */
struct JsSymbol {
    std::string name;
    JsNodeType type;
    std::string scope;
    int lineNumber;
    bool isConst;
    bool isLet;
    bool isVar;
    bool isFunction;
    bool isClass;
    bool isImported;
    bool isExported;
};

/**
 * JavaScript 依赖信息
 */
struct JsDependency {
    std::string source;        // import 来源
    std::vector<std::string> imports;  // 导入的符号
    bool isDefault;           // 是否默认导入
    bool isNamespace;         // 是否命名空间导入
    int lineNumber;
};

/**
 * JavaScript 分析结果
 */
struct JsAnalysisResult {
    bool success;
    std::vector<JsSymbol> symbols;         // 定义的符号
    std::vector<JsDependency> dependencies; // 依赖
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 使用的全局变量
    std::unordered_set<std::string> globalVariables;
    
    // 统计信息
    struct Stats {
        int totalFunctions;
        int totalClasses;
        int totalVariables;
        int totalImports;
        int totalExports;
        bool isModule;         // 是否是 ES6 模块
        bool hasStrictMode;    // 是否有 "use strict"
    } stats;
};

/**
 * 原生 JavaScript 静态分析器
 * 只负责分析标准 JavaScript，不处理 CHTL-JS 特有语法
 */
class NativeJsAnalyzer {
public:
    NativeJsAnalyzer();
    ~NativeJsAnalyzer();
    
    /**
     * 分析 JavaScript 代码
     * @param js JavaScript 源代码
     * @return 分析结果
     */
    JsAnalysisResult analyze(const std::string& js);
    
    /**
     * 验证 JavaScript 语法
     * @param js JavaScript 源代码
     * @return 是否有效
     */
    bool validate(const std::string& js);
    
    /**
     * 提取所有符号（变量、函数、类）
     */
    std::vector<JsSymbol> extractSymbols(const std::string& js);
    
    /**
     * 提取所有依赖
     */
    std::vector<JsDependency> extractDependencies(const std::string& js);
    
    /**
     * 检查是否使用了特定的全局变量
     */
    bool usesGlobal(const std::string& js, const std::string& globalName);
    
    /**
     * 获取代码的复杂度
     */
    int calculateComplexity(const std::string& js);
    
    /**
     * 设置 ECMAScript 版本
     */
    void setEcmaVersion(int version);
    
    /**
     * 设置是否允许 JSX
     */
    void setAllowJsx(bool allow);
    
    /**
     * 设置分析选项
     */
    void setOption(const std::string& name, bool value);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace chtl::v2::js