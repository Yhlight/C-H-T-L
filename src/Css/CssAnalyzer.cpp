#include "Css/CssAnalyzer.h"
#include <sstream>
#include <regex>
#include <cctype>

namespace chtl {

// 私有实现类
class CssAnalyzer::Impl {
public:
    CssAnalysisResult result;
    
    void reset() {
        result = CssAnalysisResult();
    }
    
    // 使用改进的解析方法（暂时不使用状态机）
    void analyzeCss(const std::string& css) {
        // 当前的 CSS 结构状态
        enum class ParseState {
            SELECTOR,
            PROPERTY_NAME,
            PROPERTY_VALUE,
            AT_RULE,
            COMMENT,
            STRING
        };
        
        ParseState state = ParseState::SELECTOR;
        std::string currentSelector;
        std::string currentProperty;
        std::string currentValue;
        std::string currentAtRule;
        char stringDelimiter = '\0';
        bool escaped = false;
        
        for (size_t i = 0; i < css.length(); ++i) {
            char ch = css[i];
            // char prevCh = (i > 0) ? css[i-1] : '\0';
            char nextCh = (i + 1 < css.length()) ? css[i+1] : '\0';
            
            // 处理转义
            if (escaped) {
                escaped = false;
                continue;
            }
            if (ch == '\\') {
                escaped = true;
                continue;
            }
            
            // 处理注释
            if (state != ParseState::COMMENT && state != ParseState::STRING) {
                if (ch == '/' && nextCh == '*') {
                    state = ParseState::COMMENT;
                    i++; // 跳过 *
                    continue;
                }
            }
            
            if (state == ParseState::COMMENT) {
                if (ch == '*' && nextCh == '/') {
                    state = ParseState::SELECTOR; // 回到选择器状态
                    i++; // 跳过 /
                }
                continue;
            }
            
            // 处理字符串
            if (state == ParseState::STRING) {
                if (ch == stringDelimiter) {
                    stringDelimiter = '\0';
                    state = ParseState::PROPERTY_VALUE; // 假设字符串在属性值中
                }
                currentValue += ch;
                continue;
            }
            
            // 根据状态处理
            switch (state) {
                case ParseState::SELECTOR:
                    if (ch == '"' || ch == '\'') {
                        stringDelimiter = ch;
                        state = ParseState::STRING;
                        currentSelector += ch;
                    } else if (ch == '{') {
                        // 选择器结束
                        std::string trimmedSelector = trim(currentSelector);
                        if (!trimmedSelector.empty()) {
                            result.selectors.insert(trimmedSelector);
                            extractClassAndId(trimmedSelector);
                        }
                        currentSelector.clear();
                        state = ParseState::PROPERTY_NAME;
                    } else if (ch == '@') {
                        // @ 规则
                        currentAtRule = "@";
                        state = ParseState::AT_RULE;
                    } else {
                        currentSelector += ch;
                    }
                    break;
                    
                case ParseState::AT_RULE:
                    if (std::isalpha(ch) || ch == '-') {
                        currentAtRule += ch;
                    } else {
                        // @ 规则名称结束
                        if (ch == '{' || ch == ';' || std::isspace(ch)) {
                            // 收集 @ 规则内容
                            std::string ruleContent;
                            size_t j = i;
                            
                            // 跳过空白
                            while (j < css.length() && std::isspace(css[j])) j++;
                            
                            // 收集到 ; 或 {
                            while (j < css.length() && css[j] != ';' && css[j] != '{') {
                                ruleContent += css[j];
                                j++;
                            }
                            
                            if (currentAtRule == "@import") {
                                result.imports.insert(trim(ruleContent));
                            } else if (currentAtRule == "@media") {
                                result.mediaQueries.insert(trim(ruleContent));
                            }
                            
                            i = j;
                            if (css[j] == '{') {
                                state = ParseState::SELECTOR;
                            } else {
                                state = ParseState::SELECTOR;
                            }
                            currentAtRule.clear();
                        }
                    }
                    break;
                    
                case ParseState::PROPERTY_NAME:
                    if (ch == ':') {
                        currentProperty = trim(currentProperty);
                        state = ParseState::PROPERTY_VALUE;
                    } else if (ch == '}') {
                        // 规则块结束
                        currentProperty.clear();
                        state = ParseState::SELECTOR;
                    } else if (!std::isspace(ch)) {
                        currentProperty += ch;
                    }
                    break;
                    
                case ParseState::PROPERTY_VALUE:
                    if (ch == '"' || ch == '\'') {
                        stringDelimiter = ch;
                        state = ParseState::STRING;
                        currentValue += ch;
                    } else if (ch == ';' || ch == '}') {
                        // 属性结束
                        std::string trimmedValue = trim(currentValue);
                        if (!currentProperty.empty() && !trimmedValue.empty()) {
                            // 检查自定义属性
                            if (currentProperty.substr(0, 2) == "--") {
                                result.customProperties.insert(currentProperty);
                            }
                        }
                        currentProperty.clear();
                        currentValue.clear();
                        
                        if (ch == '}') {
                            state = ParseState::SELECTOR;
                        } else {
                            state = ParseState::PROPERTY_NAME;
                        }
                    } else {
                        currentValue += ch;
                    }
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    void extractClassAndId(const std::string& selector) {
        // 提取类名 (.className)
        std::regex classRegex(R"(\.([a-zA-Z_][\w-]*))");
        std::smatch match;
        std::string::const_iterator searchStart(selector.cbegin());
        
        while (std::regex_search(searchStart, selector.cend(), match, classRegex)) {
            result.classNames.insert(match[1].str());
            searchStart = match.suffix().first;
        }
        
        // 提取 ID (#id)
        std::regex idRegex(R"(#([a-zA-Z_][\w-]*))");
        searchStart = selector.cbegin();
        
        while (std::regex_search(searchStart, selector.cend(), match, idRegex)) {
            result.ids.insert(match[1].str());
            searchStart = match.suffix().first;
        }
    }
    
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }
};

CssAnalyzer::CssAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

CssAnalyzer::~CssAnalyzer() = default;

CssAnalysisResult CssAnalyzer::analyze(const std::string& css) {
    impl_->reset();
    
    // 使用改进的解析方法
    impl_->analyzeCss(css);
    
    return impl_->result;
}

// 保留原有的提取方法接口
std::unordered_set<std::string> CssAnalyzer::extractSelectors(const std::string& css) {
    analyze(css);
    return impl_->result.selectors;
}

std::unordered_set<std::string> CssAnalyzer::extractClassNames(const std::string& css) {
    analyze(css);
    return impl_->result.classNames;
}

std::unordered_set<std::string> CssAnalyzer::extractIds(const std::string& css) {
    analyze(css);
    return impl_->result.ids;
}

std::unordered_set<std::string> CssAnalyzer::extractCustomProperties(const std::string& css) {
    analyze(css);
    return impl_->result.customProperties;
}

std::unordered_set<std::string> CssAnalyzer::extractMediaQueries(const std::string& css) {
    analyze(css);
    return impl_->result.mediaQueries;
}

std::unordered_set<std::string> CssAnalyzer::extractImports(const std::string& css) {
    analyze(css);
    return impl_->result.imports;
}

bool CssAnalyzer::validateSelector(const std::string& selector) {
    // 基本验证
    return !selector.empty() && selector.find_first_not_of(" \t\n\r") != std::string::npos;
}

bool CssAnalyzer::validateProperty(const std::string& property) {
    // 基本验证
    static const std::unordered_set<std::string> validProperties = {
        "color", "background", "background-color", "border", "border-radius",
        "margin", "padding", "width", "height", "display", "position",
        "font-size", "font-family", "text-align", "line-height",
        // ... 添加更多标准属性
    };
    
    // 自定义属性总是有效的
    if (property.substr(0, 2) == "--") return true;
    
    return validProperties.find(property) != validProperties.end();
}

bool CssAnalyzer::validateValue(const std::string& property, const std::string& value) {
    // 基本验证
    return !property.empty() && !value.empty();
}

} // namespace chtl