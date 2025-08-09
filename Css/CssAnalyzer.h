#ifndef CHTL_CSS_ANALYZER_H
#define CHTL_CSS_ANALYZER_H

#include "CssTypes.h"
#include "CssBlockExtractor.h"
#include <string>
#include <memory>
#include <regex>

namespace chtl {
namespace css {

/**
 * CSS静态分析器
 * 支持现代CSS特性，包括CSS3+、CSS Grid、CSS Variables等
 */
class CssAnalyzer {
private:
    CssBlockExtractor extractor_;
    CssAnalysisResult result_;
    
    // 现代CSS特性检测
    void detectModernFeatures(const std::string& css);
    void detectGridFeatures(const std::string& content);
    void detectFlexboxFeatures(const std::string& content);
    void detectCustomProperties(const std::string& content);
    void detectContainerQueries(const std::string& content);
    void detectCascadeLayers(const std::string& content);
    void detectNesting(const std::string& content);
    void detectLogicalProperties(const std::string& content);
    
    // 分析方法
    void analyzeBlock(std::shared_ptr<CssBlock> block);
    void extractSelectorsFromBlock(std::shared_ptr<CssBlock> block);
    void extractClassesAndIds(const std::string& selector);
    void extractProperties(std::shared_ptr<CssBlock> block);
    void analyzeAtRule(std::shared_ptr<CssBlock> block);
    
    // 验证方法
    bool validateSelector(const std::string& selector);
    bool validateProperty(const std::string& property, const std::string& value);
    bool validateColor(const std::string& color);
    bool validateUnit(const std::string& value);
    
    // 工具方法
    std::vector<std::string> tokenizeSelector(const std::string& selector);
    std::pair<std::string, std::string> parseProperty(const std::string& line);
    bool isModernProperty(const std::string& property);
    bool isExperimentalProperty(const std::string& property);
    
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
     * 检测CSS中使用的现代特性
     * @param css CSS代码
     * @return 现代特性使用情况
     */
    CssModernFeatures detectModernFeatures(const std::string& css) const;
    
    /**
     * 提取所有CSS变量定义
     * @param css CSS代码
     * @return 变量名到值的映射
     */
    std::unordered_map<std::string, std::string> extractCssVariables(const std::string& css);
    
    /**
     * 提取所有@import语句
     * @param css CSS代码
     * @return import URL列表
     */
    std::vector<std::string> extractImports(const std::string& css);
    
    /**
     * 提取所有媒体查询
     * @param css CSS代码
     * @return 媒体查询条件列表
     */
    std::vector<std::string> extractMediaQueries(const std::string& css);
    
    /**
     * 提取所有动画定义
     * @param css CSS代码
     * @return 动画名称列表
     */
    std::vector<std::string> extractKeyframes(const std::string& css);
    
    /**
     * 提取所有字体定义
     * @param css CSS代码
     * @return 字体族名称列表
     */
    std::vector<std::string> extractFontFaces(const std::string& css);
    
    /**
     * 验证CSS语法
     * @param css CSS代码
     * @return 是否有语法错误
     */
    bool validateSyntax(const std::string& css);
    
    /**
     * 检查浏览器兼容性问题
     * @param css CSS代码
     * @param targetBrowsers 目标浏览器列表
     * @return 兼容性警告列表
     */
    std::vector<std::string> checkBrowserCompatibility(
        const std::string& css, 
        const std::vector<std::string>& targetBrowsers = {}
    );
    
    /**
     * 优化建议
     * @param css CSS代码
     * @return 优化建议列表
     */
    std::vector<std::string> getOptimizationSuggestions(const std::string& css);
    
    /**
     * 获取CSS统计信息
     */
    struct CssStatistics {
        size_t totalRules;
        size_t totalSelectors;
        size_t totalDeclarations;
        size_t totalMediaQueries;
        size_t totalKeyframes;
        size_t totalCustomProperties;
        size_t fileSize;
        double averageSpecificity;
        size_t maxNestingDepth;
    };
    CssStatistics getStatistics(const std::string& css);
    
    /**
     * 获取最后的分析结果
     */
    const CssAnalysisResult& getLastResult() const { return result_; }
};

} // namespace css
} // namespace chtl

#endif // CHTL_CSS_ANALYZER_H