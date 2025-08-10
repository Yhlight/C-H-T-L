#ifndef CHTL_CSS_ANALYZER_H
#define CHTL_CSS_ANALYZER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

namespace chtl {

// CSS分析结果
struct CssAnalysisResult {
    std::unordered_set<std::string> selectors;
    std::unordered_set<std::string> classNames;
    std::unordered_set<std::string> ids;
    std::unordered_set<std::string> customProperties;
    std::unordered_set<std::string> mediaQueries;
    std::unordered_set<std::string> imports;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

// CSS静态分析器
class CssAnalyzer {
public:
    CssAnalyzer();
    ~CssAnalyzer();
    
    // 分析CSS代码
    CssAnalysisResult analyze(const std::string& css);
    
    // 提取特定信息
    std::unordered_set<std::string> extractSelectors(const std::string& css);
    std::unordered_set<std::string> extractClassNames(const std::string& css);
    std::unordered_set<std::string> extractIds(const std::string& css);
    std::unordered_set<std::string> extractCustomProperties(const std::string& css);
    std::unordered_set<std::string> extractMediaQueries(const std::string& css);
    std::unordered_set<std::string> extractImports(const std::string& css);
    
    // 验证CSS
    bool validateSelector(const std::string& selector);
    bool validateProperty(const std::string& property);
    bool validateValue(const std::string& property, const std::string& value);
    
    // 现代CSS特性支持
    bool supportsGridLayout() const { return true; }
    bool supportsFlexbox() const { return true; }
    bool supportsCustomProperties() const { return true; }
    bool supportsContainerQueries() const { return true; }
    bool supportsCascadeLayers() const { return true; }
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace chtl

#endif // CHTL_CSS_ANALYZER_H