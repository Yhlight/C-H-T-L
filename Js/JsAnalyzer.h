#ifndef CHTL_JS_ANALYZER_H
#define CHTL_JS_ANALYZER_H

#include "JsTypes.h"
#include <string>
#include <memory>

namespace chtl {
namespace js {

/**
 * JavaScript静态分析器
 * 用于分析JavaScript代码，提取结构信息，识别CHTL扩展语法
 */
class JsAnalyzer {
private:
    JsAnalysisResult result_;
    
    // 分析辅助方法
    void analyzeBlock(std::shared_ptr<JsBlock> block);
    void extractIdentifiers(const std::string& code);
    void detectES6Features(const std::string& code);
    void detectChtlExtensions(const std::string& code);
    
    // 基础验证
    bool checkBracketBalance(const std::string& code);
    bool checkBasicSyntax(const std::string& code);
    
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
     * 提取所有函数声明
     * @param js JavaScript代码
     * @return 函数声明列表
     */
    std::vector<std::string> extractFunctions(const std::string& js);
    
    /**
     * 提取所有类声明
     * @param js JavaScript代码
     * @return 类声明列表
     */
    std::vector<std::string> extractClasses(const std::string& js);
    
    /**
     * 提取所有import语句
     * @param js JavaScript代码
     * @return import语句列表
     */
    std::vector<std::string> extractImports(const std::string& js);
    
    /**
     * 提取所有export语句
     * @param js JavaScript代码
     * @return export语句列表
     */
    std::vector<std::string> extractExports(const std::string& js);
    
    /**
     * 检测是否使用了ES6+特性
     * @param js JavaScript代码
     * @return 是否使用ES6+
     */
    bool usesES6Features(const std::string& js);
    
    /**
     * 检测是否包含CHTL扩展语法
     * @param js JavaScript代码
     * @return 是否包含CHTL扩展
     */
    bool containsChtlExtensions(const std::string& js);
    
    /**
     * 提取CHTL特殊引用
     * 例如：$chtl.querySelector(), {{variable}}等
     * @param js JavaScript代码
     * @return CHTL引用列表
     */
    std::vector<std::string> extractChtlReferences(const std::string& js);
    
    /**
     * 验证JavaScript基础语法
     * @param js JavaScript代码
     * @return 是否有语法错误
     */
    bool validateBasicSyntax(const std::string& js);
    
    /**
     * 获取代码统计信息
     * @param js JavaScript代码
     * @return 统计信息结构
     */
    struct CodeStats {
        size_t lineCount;
        size_t functionCount;
        size_t classCount;
        size_t commentLineCount;
        size_t emptyLineCount;
    };
    CodeStats getCodeStatistics(const std::string& js);
    
    /**
     * 获取最后的分析结果
     */
    const JsAnalysisResult& getLastResult() const { return result_; }
};

} // namespace js
} // namespace chtl

#endif // CHTL_JS_ANALYZER_H