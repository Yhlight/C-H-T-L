#ifndef CHTL_JS_ANALYZER_H
#define CHTL_JS_ANALYZER_H

#include "ChtlJsTypes.h"
#include "ChtlJsTokenizer.h"
#include <string>
#include <memory>
#include <regex>

namespace chtl {
namespace chtl_js {

/**
 * CHTL-JS分析器
 * 分析CHTL特有的JavaScript扩展语法
 */
class ChtlJsAnalyzer {
private:
    ChtlJsTokenizer tokenizer_;
    ChtlJsTransformResult result_;
    
    // 分析方法
    void analyzeSelectors(const std::string& code);
    void analyzeChtlMethods(const std::string& code);
    void analyzeAnimations(const std::string& code);
    
    // 选择器分析
    SelectorInfo parseSelector(const std::string& selector);
    SelectorType detectSelectorType(const std::string& selector);
    std::string extractIndex(const std::string& selector, int& index);
    
    // CHTL方法分析
    ChtlMethodInfo parseListenCall(const std::string& code, size_t startPos);
    ChtlMethodInfo parseDelegateCall(const std::string& code, size_t startPos);
    AnimationInfo parseAnimateCall(const std::string& code, size_t startPos);
    
    // 工具方法
    std::string extractObjectLiteral(const std::string& code, size_t startPos);
    std::unordered_map<std::string, std::string> parseEventHandlers(const std::string& objLiteral);
    bool isChtlSyntax(const std::string& code, size_t pos);
    
public:
    ChtlJsAnalyzer();
    
    /**
     * 分析CHTL-JS代码
     * @param chtlJs CHTL-JS代码字符串
     * @return 转换结果
     */
    ChtlJsTransformResult analyze(const std::string& chtlJs);
    
    /**
     * 分析CHTL-JS文件
     * @param filepath CHTL-JS文件路径
     * @return 转换结果
     */
    ChtlJsTransformResult analyzeFile(const std::string& filepath);
    
    /**
     * 检测代码中是否包含CHTL扩展语法
     * @param code JavaScript代码
     * @return 是否包含CHTL语法
     */
    bool containsChtlSyntax(const std::string& code);
    
    /**
     * 提取所有CHTL选择器
     * @param code JavaScript代码
     * @return 选择器信息列表
     */
    std::vector<SelectorInfo> extractSelectors(const std::string& code);
    
    /**
     * 验证CHTL-JS语法
     * @param code CHTL-JS代码
     * @return 是否有语法错误
     */
    bool validateSyntax(const std::string& code);
    
    /**
     * 获取CHTL运行时代码
     * @return CHTL运行时支持函数的JavaScript代码
     */
    static std::string getChtlRuntimeCode();
    
    /**
     * 获取最后的分析结果
     */
    const ChtlJsTransformResult& getLastResult() const { return result_; }
};

} // namespace chtl_js
} // namespace chtl

#endif // CHTL_JS_ANALYZER_H