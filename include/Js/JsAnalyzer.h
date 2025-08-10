#ifndef CHTL_JS_ANALYZER_H
#define CHTL_JS_ANALYZER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>

namespace chtl {

// JavaScript分析结果
struct JsAnalysisResult {
    // 提取的信息
    std::unordered_set<std::string> functions;
    std::unordered_set<std::string> classes;
    std::unordered_set<std::string> variables;
    std::unordered_set<std::string> imports;
    std::unordered_set<std::string> exports;
    std::unordered_set<std::string> identifiers;
    
    // ES6+特性检测
    bool hasArrowFunctions = false;
    bool hasClasses = false;
    bool hasTemplateStrings = false;
    bool hasDestructuring = false;
    bool hasLetConst = false;
    bool hasModules = false;
    bool hasAsyncAwait = false;
    bool hasOptionalChaining = false;
    bool hasNullishCoalescing = false;
    bool hasBigInt = false;
    bool hasDynamicImport = false;
    bool hasTopLevelAwait = false;
    bool hasPrivateFields = false;
    bool hasStaticBlocks = false;
    bool hasErrorCause = false;
    bool hasArrayAt = false;
    bool hasDecorators = false;
    
    // 错误和警告
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

// JavaScript静态分析器
class JsAnalyzer {
public:
    JsAnalyzer();
    ~JsAnalyzer();
    
    // 分析JavaScript代码
    JsAnalysisResult analyze(const std::string& js);
    
    // 提取各种信息
    std::unordered_set<std::string> extractFunctions(const std::string& js);
    std::unordered_set<std::string> extractClasses(const std::string& js);
    std::unordered_set<std::string> extractVariables(const std::string& js);
    std::unordered_set<std::string> extractImports(const std::string& js);
    std::unordered_set<std::string> extractExports(const std::string& js);
    
    // 检测ES6+特性
    void detectModernFeatures(const std::string& js);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace chtl

#endif // CHTL_JS_ANALYZER_H