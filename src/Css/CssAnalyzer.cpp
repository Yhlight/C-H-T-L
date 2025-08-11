#include "Css/CssAnalyzer.h"

namespace chtl {

// 私有实现类
class CssAnalyzer::Impl {
public:
    CssAnalysisResult result;
    
    void reset() {
        result = CssAnalysisResult();
    }
};

CssAnalyzer::CssAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

CssAnalyzer::~CssAnalyzer() = default;

CssAnalysisResult CssAnalyzer::analyze(const std::string& css) {
    impl_->reset();
    
    // 简单实现：提取基本信息
    extractSelectors(css);
    extractClassNames(css);
    extractIds(css);
    extractCustomProperties(css);
    extractMediaQueries(css);
    extractImports(css);
    
    return impl_->result;
}

std::unordered_set<std::string> CssAnalyzer::extractSelectors(const std::string& css) {
    std::unordered_set<std::string> selectors;
    
    // 简单实现：查找选择器模式
    size_t pos = 0;
    while (pos < css.length()) {
        // 跳过注释和字符串
        if (css[pos] == '/' && pos + 1 < css.length() && css[pos + 1] == '*') {
            pos = css.find("*/", pos + 2);
            if (pos != std::string::npos) pos += 2;
            else break;
            continue;
        }
        
        // 查找 { 之前的选择器
        size_t bracePos = css.find('{', pos);
        if (bracePos == std::string::npos) break;
        
        // 提取选择器
        std::string selector = css.substr(pos, bracePos - pos);
        // 清理空白
        selector.erase(0, selector.find_first_not_of(" \t\n\r"));
        selector.erase(selector.find_last_not_of(" \t\n\r") + 1);
        
        if (!selector.empty()) {
            selectors.insert(selector);
            impl_->result.selectors.insert(selector);
        }
        
        // 跳到下一个 }
        pos = css.find('}', bracePos);
        if (pos != std::string::npos) pos++;
        else break;
    }
    
    return selectors;
}

std::unordered_set<std::string> CssAnalyzer::extractClassNames(const std::string& css) {
    std::unordered_set<std::string> classNames;
    
    // 查找 .className 模式
    size_t pos = 0;
    while ((pos = css.find('.', pos)) != std::string::npos) {
        pos++;
        if (pos < css.length() && (std::isalpha(css[pos]) || css[pos] == '_' || css[pos] == '-')) {
            size_t end = pos;
            while (end < css.length() && 
                   (std::isalnum(css[end]) || css[end] == '_' || css[end] == '-')) {
                end++;
            }
            std::string className = css.substr(pos, end - pos);
            classNames.insert(className);
            impl_->result.classNames.insert(className);
            pos = end;
        }
    }
    
    return classNames;
}

std::unordered_set<std::string> CssAnalyzer::extractIds(const std::string& css) {
    std::unordered_set<std::string> ids;
    
    // 查找 #id 模式
    size_t pos = 0;
    while ((pos = css.find('#', pos)) != std::string::npos) {
        pos++;
        if (pos < css.length() && (std::isalpha(css[pos]) || css[pos] == '_' || css[pos] == '-')) {
            size_t end = pos;
            while (end < css.length() && 
                   (std::isalnum(css[end]) || css[end] == '_' || css[end] == '-')) {
                end++;
            }
            std::string id = css.substr(pos, end - pos);
            ids.insert(id);
            impl_->result.ids.insert(id);
            pos = end;
        }
    }
    
    return ids;
}

std::unordered_set<std::string> CssAnalyzer::extractCustomProperties(const std::string& css) {
    std::unordered_set<std::string> customProps;
    
    // 查找 --property 模式
    size_t pos = 0;
    while ((pos = css.find("--", pos)) != std::string::npos) {
        size_t end = pos + 2;
        while (end < css.length() && 
               (std::isalnum(css[end]) || css[end] == '_' || css[end] == '-')) {
            end++;
        }
        if (end > pos + 2) {
            std::string prop = css.substr(pos, end - pos);
            customProps.insert(prop);
            impl_->result.customProperties.insert(prop);
        }
        pos = end;
    }
    
    return customProps;
}

std::unordered_set<std::string> CssAnalyzer::extractMediaQueries(const std::string& css) {
    std::unordered_set<std::string> mediaQueries;
    
    // 查找 @media 模式
    size_t pos = 0;
    while ((pos = css.find("@media", pos)) != std::string::npos) {
        size_t start = pos;
        size_t bracePos = css.find('{', pos);
        if (bracePos != std::string::npos) {
            std::string query = css.substr(start, bracePos - start);
            mediaQueries.insert(query);
            impl_->result.mediaQueries.insert(query);
            pos = bracePos;
        } else {
            pos += 6;
        }
    }
    
    return mediaQueries;
}

std::unordered_set<std::string> CssAnalyzer::extractImports(const std::string& css) {
    std::unordered_set<std::string> imports;
    
    // 查找 @import 模式
    size_t pos = 0;
    while ((pos = css.find("@import", pos)) != std::string::npos) {
        size_t end = css.find(';', pos);
        if (end != std::string::npos) {
            std::string import = css.substr(pos, end - pos + 1);
            imports.insert(import);
            impl_->result.imports.insert(import);
            pos = end;
        } else {
            pos += 7;
        }
    }
    
    return imports;
}

bool CssAnalyzer::validateSelector(const std::string& selector) {
    // 简单验证
    return !selector.empty() && selector.find_first_not_of(" \t\n\r") != std::string::npos;
}

bool CssAnalyzer::validateProperty(const std::string& property) {
    // 简单验证
    return !property.empty();
}

bool CssAnalyzer::validateValue(const std::string& property, const std::string& value) {
    // 简单验证
    return !property.empty() && !value.empty();
}

} // namespace chtl