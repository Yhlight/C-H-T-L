#pragma once

#include <string>
#include <vector>

namespace chtl::v2::css {

/**
 * CSS 分析结果
 */
struct CssAnalysisResult {
    bool valid = true;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // CSS 结构信息
    struct Rule {
        std::string selector;
        std::vector<std::pair<std::string, std::string>> properties;
    };
    std::vector<Rule> rules;
    
    // @规则
    std::vector<std::string> atRules;
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