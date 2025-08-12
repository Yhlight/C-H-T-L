#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace chtl::v2::css {

/**
 * CSS 分析结果
 */
struct CssAnalysisResult {
    bool valid = true;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;

    // 属性出现次数统计
    std::map<std::string, int> properties;

    // 规则数量统计
    int ruleCount = 0;

    // 特性检测
    struct Features {
        bool hasMediaQueries = false;
        bool hasAnimations  = false;
        bool hasSupports    = false;
        bool hasImports     = false;
    } features;

    // 唯一选择器集合
    std::vector<std::string> selectors;
};

/**
 * 原生 CSS 分析器
 * 只处理标准 CSS 语法，不处理 CHTL 特有语法
 */
class NativeCssAnalyzer {
public:
    NativeCssAnalyzer();
    ~NativeCssAnalyzer();
    
    /**
     * 分析 CSS 代码
     * @param css 标准 CSS 代码
     * @return 分析结果
     */
    CssAnalysisResult analyze(const std::string& css);
    
    /**
     * 设置选项
     */
    void setOption(const std::string& name, bool value);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace chtl::v2::css