#ifndef CHTL_CSS_ANALYZER_H
#define CHTL_CSS_ANALYZER_H

#include "CssTypes.h"
#include "CssBlockExtractor.h"
#include <string>
#include <memory>

namespace chtl {
namespace css {

/**
 * CSS静态分析器
 * 用于分析CSS代码，提取结构信息，支持CHTL特殊语法
 */
class CssAnalyzer {
private:
    CssBlockExtractor extractor_;
    CssAnalysisResult result_;
    
    // 分析方法
    void analyzeBlock(std::shared_ptr<CssBlock> block);
    void extractSelectorsFromBlock(std::shared_ptr<CssBlock> block);
    void extractClassesAndIds(const std::string& selector);
    void extractCustomPropertiesFromContent(const std::string& content);
    
    // CHTL特殊语法处理
    bool isChtlSpecialSyntax(const std::string& text);
    void processChtlSyntax(const std::string& text);
    
public:
    CssAnalyzer();
    
    /**
     * 分析CSS代码
     * @param css CSS代码字符串
     * @return 分析结果
     */
    CssAnalysisResult analyze(const std::string& css);
    
    /**
     * 分析CSS文件
     * @param filepath CSS文件路径
     * @return 分析结果
     */
    CssAnalysisResult analyzeFile(const std::string& filepath);
    
    /**
     * 检查CSS中是否包含CHTL特殊语法
     * @param css CSS代码
     * @return 是否包含CHTL语法
     */
    bool containsChtlSyntax(const std::string& css);
    
    /**
     * 提取CSS中的CHTL变量引用
     * 例如：background: Colors(primary);
     * @param css CSS代码
     * @return CHTL变量引用列表
     */
    std::vector<std::string> extractChtlVariableReferences(const std::string& css);
    
    /**
     * 提取CSS中的CHTL样式引用
     * 例如：@Style ButtonStyle;
     * @param css CSS代码
     * @return CHTL样式引用列表
     */
    std::vector<std::string> extractChtlStyleReferences(const std::string& css);
    
    /**
     * 验证CSS语法（基础验证）
     * @param css CSS代码
     * @return 是否有语法错误
     */
    bool validateBasicSyntax(const std::string& css);
    
    /**
     * 获取最后的分析结果
     */
    const CssAnalysisResult& getLastResult() const { return result_; }
};

} // namespace css
} // namespace chtl

#endif // CHTL_CSS_ANALYZER_H