#pragma once

#include <string>
#include <vector>
#include <memory>

namespace chtl::v2::css {

/**
 * CSS 规则类型
 */
enum class CssRuleType {
    STYLE_RULE,      // 普通样式规则
    AT_IMPORT,       // @import
    AT_MEDIA,        // @media
    AT_KEYFRAMES,    // @keyframes
    AT_FONT_FACE,    // @font-face
    AT_SUPPORTS,     // @supports
    AT_PAGE,         // @page
    AT_NAMESPACE,    // @namespace
    UNKNOWN
};

/**
 * CSS 选择器
 */
struct CssSelector {
    std::string raw;           // 原始选择器文本
    std::string normalized;    // 规范化的选择器
    int specificity;          // 特异性值
};

/**
 * CSS 属性
 */
struct CssProperty {
    std::string name;         // 属性名
    std::string value;        // 属性值
    bool isImportant;        // 是否有 !important
    int lineNumber;          // 行号
};

/**
 * CSS 规则
 */
struct CssRule {
    CssRuleType type;
    std::vector<CssSelector> selectors;
    std::vector<CssProperty> properties;
    std::string atRuleContent;  // @规则的内容
    int startLine;
    int endLine;
};

/**
 * CSS 分析结果
 */
struct CssAnalysisResult {
    bool success;
    std::vector<CssRule> rules;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 统计信息
    struct Stats {
        int totalRules;
        int totalSelectors;
        int totalProperties;
        int totalAtRules;
    } stats;
};

/**
 * 原生 CSS 静态分析器
 * 只负责分析标准 CSS，不处理 CHTL 特有语法
 */
class NativeCssAnalyzer {
public:
    NativeCssAnalyzer();
    ~NativeCssAnalyzer();
    
    /**
     * 分析 CSS 代码
     * @param css CSS 源代码
     * @return 分析结果
     */
    CssAnalysisResult analyze(const std::string& css);
    
    /**
     * 验证 CSS 语法
     * @param css CSS 源代码
     * @return 是否有效
     */
    bool validate(const std::string& css);
    
    /**
     * 提取所有选择器
     */
    std::vector<CssSelector> extractSelectors(const std::string& css);
    
    /**
     * 提取所有属性
     */
    std::vector<CssProperty> extractProperties(const std::string& css);
    
    /**
     * 计算选择器特异性
     */
    static int calculateSpecificity(const std::string& selector);
    
    /**
     * 规范化选择器
     */
    static std::string normalizeSelector(const std::string& selector);
    
    /**
     * 设置选项
     */
    void setOption(const std::string& name, bool value);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace chtl::v2::css