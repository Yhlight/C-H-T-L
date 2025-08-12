#include "v2/Css/NativeCssAnalyzer.h"
#include <regex>
#include <sstream>

namespace chtl::v2::css {

class NativeCssAnalyzer::Impl {
public:
    CssAnalysisResult analyze(const std::string& css) {
        CssAnalysisResult result;
        
        if (css.empty()) {
            return result;
        }
        
        // 简单的 CSS 解析
        parseRules(css, result);
        
        return result;
    }
    
    void setOption(const std::string& name, bool value) {
        if (name == "strict") {
            strict_ = value;
        }
    }
    
private:
    void parseRules(const std::string& css, CssAnalysisResult& result) {
        // 移除注释
        std::string cleanCss = removeComments(css);
        
        // 查找 @规则
        findAtRules(cleanCss, result);
        
        // 查找普通规则
        findStyleRules(cleanCss, result);
    }
    
    std::string removeComments(const std::string& css) {
        std::string result = css;
        
        // 移除 /* */ 注释
        std::regex blockComment("/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/");
        result = std::regex_replace(result, blockComment, "");
        
        return result;
    }
    
    void findAtRules(const std::string& css, CssAnalysisResult& result) {
        // 简单匹配 @规则
        std::regex atRule("@[a-zA-Z-]+[^{;]*[{;]");
        std::sregex_iterator it(css.begin(), css.end(), atRule);
        std::sregex_iterator end;
        
        for (; it != end; ++it) {
            result.atRules.push_back(it->str());
        }
    }
    
    void findStyleRules(const std::string& css, CssAnalysisResult& result) {
        // 简单的规则解析
        size_t pos = 0;
        while (pos < css.length()) {
            // 查找选择器
            size_t bracePos = css.find('{', pos);
            if (bracePos == std::string::npos) break;
            
            // 提取选择器
            std::string selector = css.substr(pos, bracePos - pos);
            selector = trim(selector);
            
            // 跳过 @规则
            if (selector.empty() || selector[0] == '@') {
                pos = css.find('}', bracePos);
                if (pos != std::string::npos) pos++;
                continue;
            }
            
            // 查找规则体结束
            size_t endBrace = findMatchingBrace(css, bracePos);
            if (endBrace == std::string::npos) {
                result.errors.push_back("Unmatched brace at position " + 
                                      std::to_string(bracePos));
                break;
            }
            
            // 提取属性
            std::string body = css.substr(bracePos + 1, endBrace - bracePos - 1);
            
            CssAnalysisResult::Rule rule;
            rule.selector = selector;
            parseProperties(body, rule.properties);
            
            result.rules.push_back(rule);
            
            pos = endBrace + 1;
        }
    }
    
    void parseProperties(const std::string& body, 
                        std::vector<std::pair<std::string, std::string>>& properties) {
        std::istringstream stream(body);
        std::string property;
        
        while (std::getline(stream, property, ';')) {
            property = trim(property);
            if (property.empty()) continue;
            
            size_t colonPos = property.find(':');
            if (colonPos != std::string::npos) {
                std::string name = trim(property.substr(0, colonPos));
                std::string value = trim(property.substr(colonPos + 1));
                
                if (!name.empty() && !value.empty()) {
                    properties.push_back({name, value});
                }
            }
        }
    }
    
    size_t findMatchingBrace(const std::string& str, size_t start) {
        int depth = 1;
        for (size_t i = start + 1; i < str.length(); ++i) {
            if (str[i] == '{') depth++;
            else if (str[i] == '}') {
                depth--;
                if (depth == 0) return i;
            }
        }
        return std::string::npos;
    }
    
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }
    
    bool strict_ = false;
};

NativeCssAnalyzer::NativeCssAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

NativeCssAnalyzer::~NativeCssAnalyzer() = default;

CssAnalysisResult NativeCssAnalyzer::analyze(const std::string& css) {
    return impl_->analyze(css);
}

void NativeCssAnalyzer::setOption(const std::string& name, bool value) {
    impl_->setOption(name, value);
}

} // namespace chtl::v2::css