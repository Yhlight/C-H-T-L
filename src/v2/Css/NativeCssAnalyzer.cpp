#include "v2/Css/NativeCssAnalyzer.h"
#include "v2/Css/CssParser.h"
#include <iostream>
#include <set>

namespace chtl::v2::css {

class NativeCssAnalyzer::Impl {
public:
    CssAnalysisResult analyze(const std::string& css) {
        CssAnalysisResult result;
        result.valid = true;
        
        try {
            // 使用新的 CSS 解析器
            CssParser parser(css);
            auto parseResult = parser.parse();
            
            if (!parseResult.errors.empty()) {
                result.valid = false;
                result.errors = parseResult.errors;
            }
            
            result.warnings = parseResult.warnings;
            
            // 分析样式表
            if (parseResult.stylesheet) {
                analyzeStylesheet(*parseResult.stylesheet, result);
            }
            
        } catch (const std::exception& e) {
            result.valid = false;
            result.errors.push_back("CSS parse error: " + std::string(e.what()));
        }
        
        return result;
    }
    
private:
    void analyzeStylesheet(const CssStylesheet& stylesheet, CssAnalysisResult& result) {
        // 收集选择器
        std::set<std::string> uniqueSelectors;
        
        for (const auto& rule : stylesheet.rules) {
            if (rule->type == RuleType::STYLE_RULE) {
                // 收集选择器
                for (const auto& selector : rule->selectors) {
                    std::string selectorStr = selector->toString();
                    uniqueSelectors.insert(selectorStr);
                }
                
                // 收集属性
                for (const auto& decl : rule->declarations) {
                    result.properties[decl.property]++;
                    
                    // 检查供应商前缀
                    if (decl.property.starts_with("-webkit-") ||
                        decl.property.starts_with("-moz-") ||
                        decl.property.starts_with("-ms-") ||
                        decl.property.starts_with("-o-")) {
                        result.warnings.push_back("Vendor prefix used: " + decl.property);
                    }
                }
                
                // 统计规则
                result.ruleCount++;
                
            } else if (rule->type == RuleType::MEDIA_RULE) {
                result.features.hasMediaQueries = true;
                // 递归分析嵌套规则
                for (const auto& nestedRule : rule->nestedRules) {
                    if (nestedRule->type == RuleType::STYLE_RULE) {
                        result.ruleCount++;
                    }
                }
                
            } else if (rule->type == RuleType::KEYFRAMES_RULE) {
                result.features.hasAnimations = true;
                
            } else if (rule->type == RuleType::SUPPORTS_RULE) {
                result.features.hasSupports = true;
                
            } else if (rule->type == RuleType::IMPORT_RULE) {
                result.features.hasImports = true;
            }
        }
        
        // 转换选择器集合为向量
        result.selectors.assign(uniqueSelectors.begin(), uniqueSelectors.end());
        
        // 检查复杂度
        checkComplexity(stylesheet, result);
        
        // 检查最佳实践
        checkBestPractices(stylesheet, result);
    }
    
    void checkComplexity(const CssStylesheet& stylesheet, CssAnalysisResult& result) {
        int maxSelectorComplexity = 0;
        int totalComplexity = 0;
        int selectorCount = 0;
        
        for (const auto& rule : stylesheet.rules) {
            if (rule->type == RuleType::STYLE_RULE) {
                for (const auto& selector : rule->selectors) {
                    int complexity = calculateSelectorComplexity(*selector);
                    maxSelectorComplexity = std::max(maxSelectorComplexity, complexity);
                    totalComplexity += complexity;
                    selectorCount++;
                }
            }
        }
        
        if (maxSelectorComplexity > 4) {
            result.warnings.push_back("Complex selector detected (complexity: " + 
                                    std::to_string(maxSelectorComplexity) + ")");
        }
        
        if (selectorCount > 0) {
            double avgComplexity = static_cast<double>(totalComplexity) / selectorCount;
            if (avgComplexity > 2.5) {
                result.warnings.push_back("High average selector complexity: " + 
                                        std::to_string(avgComplexity));
            }
        }
    }
    
    int calculateSelectorComplexity(const CssSelector& selector) {
        int complexity = 1;
        const CssSelector* current = &selector;
        
        while (current) {
            // 伪类和伪元素增加复杂度
            if (current->type == SelectorType::PSEUDO_CLASS ||
                current->type == SelectorType::PSEUDO_ELEMENT) {
                complexity++;
            }
            
            // 属性选择器增加复杂度
            if (current->type == SelectorType::ATTRIBUTE) {
                complexity++;
            }
            
            // 组合器增加复杂度
            if (current->combinator != CombinatorType::NONE) {
                complexity++;
            }
            
            current = current->next.get();
        }
        
        return complexity;
    }
    
    void checkBestPractices(const CssStylesheet& stylesheet, CssAnalysisResult& result) {
        // 检查是否使用了 ID 选择器
        bool hasIdSelectors = false;
        bool hasUniversalSelectors = false;
        bool hasImportantDeclarations = false;
        
        for (const auto& rule : stylesheet.rules) {
            if (rule->type == RuleType::STYLE_RULE) {
                for (const auto& selector : rule->selectors) {
                    if (hasIdSelector(*selector)) {
                        hasIdSelectors = true;
                    }
                    if (hasUniversalSelector(*selector)) {
                        hasUniversalSelectors = true;
                    }
                }
                
                for (const auto& decl : rule->declarations) {
                    if (decl.important) {
                        hasImportantDeclarations = true;
                    }
                }
            }
        }
        
        if (hasIdSelectors) {
            result.warnings.push_back("ID selectors found - consider using classes for better reusability");
        }
        
        if (hasUniversalSelectors) {
            result.warnings.push_back("Universal selector (*) found - may impact performance");
        }
        
        if (hasImportantDeclarations) {
            result.warnings.push_back("!important declarations found - consider specificity instead");
        }
        
        // 检查重复的声明
        checkDuplicateDeclarations(stylesheet, result);
    }
    
    bool hasIdSelector(const CssSelector& selector) {
        const CssSelector* current = &selector;
        while (current) {
            if (current->type == SelectorType::ID) {
                return true;
            }
            current = current->next.get();
        }
        return false;
    }
    
    bool hasUniversalSelector(const CssSelector& selector) {
        const CssSelector* current = &selector;
        while (current) {
            if (current->type == SelectorType::UNIVERSAL) {
                return true;
            }
            current = current->next.get();
        }
        return false;
    }
    
    void checkDuplicateDeclarations(const CssStylesheet& stylesheet, CssAnalysisResult& result) {
        std::map<std::string, std::set<std::string>> selectorProperties;
        
        for (const auto& rule : stylesheet.rules) {
            if (rule->type == RuleType::STYLE_RULE) {
                for (const auto& selector : rule->selectors) {
                    std::string selectorStr = selector->toString();
                    auto& props = selectorProperties[selectorStr];
                    
                    for (const auto& decl : rule->declarations) {
                        if (props.count(decl.property) > 0) {
                            result.warnings.push_back("Duplicate property '" + decl.property + 
                                                    "' in selector '" + selectorStr + "'");
                        }
                        props.insert(decl.property);
                    }
                }
            }
        }
    }
};

NativeCssAnalyzer::NativeCssAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

NativeCssAnalyzer::~NativeCssAnalyzer() = default;

CssAnalysisResult NativeCssAnalyzer::analyze(const std::string& css) {
    return impl_->analyze(css);
}

} // namespace chtl::v2::css