#ifndef CHTL_JS_ANALYZER_H
#define CHTL_JS_ANALYZER_H

#include "JsTypes.h"
#include <string>
#include <memory>
#include <regex>

namespace chtl {
namespace js {

/**
 * JavaScript静态分析器
 * 支持ES2022+现代JavaScript语法分析
 */
class JsAnalyzer {
private:
    JsAnalysisResult result_;
    
    // 现代特性检测
    void detectModernFeatures(const std::string& js);
    void detectES6Features(const std::string& code);
    void detectES2017Features(const std::string& code);
    void detectES2020Features(const std::string& code);
    void detectES2022Features(const std::string& code);
    void detectProposalFeatures(const std::string& code);
    
    // 分析辅助方法
    void analyzeBlock(std::shared_ptr<JsBlock> block);
    void extractIdentifiers(const std::string& code);
    void extractDependencies(const std::string& code);
    void calculateComplexity(const std::string& code);
    
    // 语法检测
    bool isArrowFunction(const std::string& code);
    bool isAsyncFunction(const std::string& code);
    bool isGeneratorFunction(const std::string& code);
    bool isClassDeclaration(const std::string& code);
    bool isModuleStatement(const std::string& code);
    
    // 基础验证
    bool checkBracketBalance(const std::string& code);
    bool checkBasicSyntax(const std::string& code);
    
    // 工具方法
    std::vector<std::string> extractStringLiterals(const std::string& code);
    std::vector<std::string> extractTemplateLiterals(const std::string& code);
    std::string removeComments(const std::string& code);
    
public:
    JsAnalyzer();
    
    /**
     * 分析JavaScript代码
     * @param js JavaScript代码字符串
     * @return 分析结果
     */
    JsAnalysisResult analyze(const std::string& js);
    
    /**
     * 分析JavaScript文件
     * @param filepath JavaScript文件路径
     * @return 分析结果
     */
    JsAnalysisResult analyzeFile(const std::string& filepath);
    
    /**
     * 检测代码使用的ECMAScript版本
     * @param js JavaScript代码
     * @return 最高使用的ES版本
     */
    EsVersion detectEsVersion(const std::string& js);
    
    /**
     * 提取所有函数声明（包括各种形式）
     * @param js JavaScript代码
     * @return 函数信息列表
     */
    struct FunctionInfo {
        std::string name;
        std::string type; // "function", "arrow", "async", "generator", etc.
        std::vector<std::string> parameters;
        bool isAsync;
        bool isGenerator;
        bool isArrow;
        size_t line;
    };
    std::vector<FunctionInfo> extractFunctions(const std::string& js);
    
    /**
     * 提取所有类声明
     * @param js JavaScript代码
     * @return 类信息列表
     */
    struct ClassInfo {
        std::string name;
        std::string superClass;
        std::vector<std::string> methods;
        std::vector<std::string> fields;
        std::vector<std::string> staticMembers;
        bool hasConstructor;
        size_t line;
    };
    std::vector<ClassInfo> extractClasses(const std::string& js);
    
    /**
     * 提取所有import语句
     * @param js JavaScript代码
     * @return import信息列表
     */
    struct ImportInfo {
        std::string source;
        std::vector<std::string> imports;
        bool isDefault;
        bool isNamespace;
        bool isDynamic;
        size_t line;
    };
    std::vector<ImportInfo> extractImports(const std::string& js);
    
    /**
     * 提取所有export语句
     * @param js JavaScript代码
     * @return export信息列表
     */
    struct ExportInfo {
        std::string name;
        std::string type; // "default", "named", "all"
        std::string source; // for re-exports
        size_t line;
    };
    std::vector<ExportInfo> extractExports(const std::string& js);
    
    /**
     * 检测使用的现代JavaScript特性
     * @param js JavaScript代码
     * @return 现代特性使用情况
     */
    JsModernFeatures detectModernFeatures(const std::string& js) const;
    
    /**
     * 验证JavaScript语法
     * @param js JavaScript代码
     * @return 是否有语法错误
     */
    bool validateSyntax(const std::string& js);
    
    /**
     * 获取代码质量指标
     * @param js JavaScript代码
     * @return 代码质量报告
     */
    struct CodeQualityReport {
        size_t cyclomaticComplexity;
        size_t cognitiveComplexity;
        size_t maintainabilityIndex;
        size_t duplicatedLines;
        size_t codeSmells;
        std::vector<std::string> suggestions;
    };
    CodeQualityReport analyzeCodeQuality(const std::string& js);
    
    /**
     * 获取代码统计信息
     * @param js JavaScript代码
     * @return 统计信息
     */
    struct CodeStatistics {
        size_t totalLines;
        size_t codeLines;
        size_t commentLines;
        size_t blankLines;
        size_t functionCount;
        size_t classCount;
        size_t variableCount;
        size_t constantCount;
        size_t importCount;
        size_t exportCount;
        double averageFunctionLength;
        size_t maxFunctionLength;
    };
    CodeStatistics getStatistics(const std::string& js);
    
    /**
     * 检测潜在的安全问题
     * @param js JavaScript代码
     * @return 安全警告列表
     */
    std::vector<std::string> detectSecurityIssues(const std::string& js);
    
    /**
     * 获取依赖分析
     * @param js JavaScript代码
     * @return 依赖信息
     */
    struct DependencyInfo {
        std::unordered_set<std::string> externalDependencies;
        std::unordered_set<std::string> internalDependencies;
        std::unordered_map<std::string, std::vector<std::string>> dependencyGraph;
        bool hasCircularDependencies;
    };
    DependencyInfo analyzeDependencies(const std::string& js);
    
    /**
     * 获取最后的分析结果
     */
    const JsAnalysisResult& getLastResult() const { return result_; }
};

} // namespace js
} // namespace chtl

#endif // CHTL_JS_ANALYZER_H