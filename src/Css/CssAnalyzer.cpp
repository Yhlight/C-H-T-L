#include "Css/CssAnalyzer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace chtl {
namespace css {

CssAnalyzer::CssAnalyzer() {
}

CssAnalysisResult CssAnalyzer::analyze(const std::string& css) {
    // 清空之前的结果
    result_ = CssAnalysisResult();
    
    // 基础语法验证
    if (!validateSyntax(css)) {
        result_.hasErrors = true;
        return result_;
    }
    
    // 提取CSS块
    result_.blocks = extractor_.extractBlocks(css);
    
    // 分析每个块
    for (const auto& block : result_.blocks) {
        analyzeBlock(block);
    }
    
    // 检测现代特性
    detectModernFeatures(css);
    
    // 统计信息
    result_.ruleCount = result_.blocks.size();
    result_.customPropertyCount = result_.customProperties.size();
    
    return result_;
}

void CssAnalyzer::detectModernFeatures(const std::string& css) {
    // CSS Variables
    if (css.find("--") != std::string::npos || css.find("var(") != std::string::npos) {
        result_.modernFeatures.cssVariables = true;
    }
    
    // Grid Layout
    if (css.find("display: grid") != std::string::npos || 
        css.find("display:grid") != std::string::npos ||
        css.find("grid-template") != std::string::npos) {
        result_.modernFeatures.cssGrid = true;
    }
    
    // Flexbox
    if (css.find("display: flex") != std::string::npos || 
        css.find("display:flex") != std::string::npos ||
        css.find("flex-") != std::string::npos) {
        result_.modernFeatures.cssFlexbox = true;
    }
    
    // Container Queries
    if (css.find("@container") != std::string::npos) {
        result_.modernFeatures.containerQueries = true;
    }
    
    // Cascade Layers
    if (css.find("@layer") != std::string::npos) {
        result_.modernFeatures.cascadeLayers = true;
    }
    
    // :has() selector
    if (css.find(":has(") != std::string::npos) {
        result_.modernFeatures.hasOperator = true;
    }
    
    // :where() and :is()
    if (css.find(":where(") != std::string::npos || css.find(":is(") != std::string::npos) {
        result_.modernFeatures.whereIsOperator = true;
    }
    
    // Logical Properties
    std::vector<std::string> logicalProps = {
        "margin-inline", "margin-block", "padding-inline", "padding-block",
        "inset", "inset-inline", "inset-block"
    };
    for (const auto& prop : logicalProps) {
        if (css.find(prop) != std::string::npos) {
            result_.modernFeatures.logicalProperties = true;
            break;
        }
    }
    
    // aspect-ratio
    if (css.find("aspect-ratio") != std::string::npos) {
        result_.modernFeatures.aspectRatio = true;
    }
    
    // color() function
    if (css.find("color(") != std::string::npos) {
        result_.modernFeatures.colorFunction = true;
    }
    
    // subgrid
    if (css.find("subgrid") != std::string::npos) {
        result_.modernFeatures.subgrid = true;
    }
}

bool CssAnalyzer::validateSyntax(const std::string& css) {
    // 基础括号平衡检查
    int braceCount = 0;
    int parenCount = 0;
    int bracketCount = 0;
    bool inString = false;
    char stringChar = '\0';
    
    for (size_t i = 0; i < css.length(); ++i) {
        char c = css[i];
        
        // 处理字符串
        if ((c == '"' || c == '\'') && (i == 0 || css[i-1] != '\\')) {
            if (!inString) {
                inString = true;
                stringChar = c;
            } else if (c == stringChar) {
                inString = false;
            }
            continue;
        }
        
        if (inString) continue;
        
        // 处理注释
        if (c == '/' && i + 1 < css.length() && css[i+1] == '*') {
            size_t endComment = css.find("*/", i + 2);
            if (endComment == std::string::npos) {
                result_.errors.push_back("Unclosed comment");
                return false;
            }
            i = endComment + 1;
            continue;
        }
        
        // 计数括号
        switch (c) {
            case '{': braceCount++; break;
            case '}': braceCount--; break;
            case '(': parenCount++; break;
            case ')': parenCount--; break;
            case '[': bracketCount++; break;
            case ']': bracketCount--; break;
        }
        
        // 检查负数
        if (braceCount < 0 || parenCount < 0 || bracketCount < 0) {
            result_.errors.push_back("Unmatched closing bracket at position " + std::to_string(i));
            return false;
        }
    }
    
    // 检查最终平衡
    if (braceCount != 0) {
        result_.errors.push_back("Unmatched braces");
        return false;
    }
    if (parenCount != 0) {
        result_.errors.push_back("Unmatched parentheses");
        return false;
    }
    if (bracketCount != 0) {
        result_.errors.push_back("Unmatched brackets");
        return false;
    }
    
    return true;
}

void CssAnalyzer::analyzeBlock(std::shared_ptr<CssBlock> block) {
    if (!block) return;
    
    // 提取选择器信息
    if (block->type == CssBlockType::RULE_SET) {
        extractSelectorsFromBlock(block);
        extractProperties(block);
    } else if (block->type == CssBlockType::AT_RULE) {
        analyzeAtRule(block);
    }
    
    // 递归分析嵌套块
    for (const auto& nested : block->nestedBlocks) {
        analyzeBlock(nested);
    }
}

void CssAnalyzer::extractSelectorsFromBlock(std::shared_ptr<CssBlock> block) {
    if (block->selector.empty()) return;
    
    // 添加到选择器列表
    result_.selectors.push_back(block->selector);
    
    // 提取类名和ID
    extractClassesAndIds(block->selector);
}

void CssAnalyzer::extractClassesAndIds(const std::string& selector) {
    // 提取类名 (.class-name)
    std::regex classRegex(R"(\.([a-zA-Z0-9_-]+))");
    std::smatch match;
    std::string::const_iterator searchStart(selector.cbegin());
    
    while (std::regex_search(searchStart, selector.cend(), match, classRegex)) {
        result_.classNames.push_back(match[1]);
        searchStart = match.suffix().first;
    }
    
    // 提取ID (#id-name)
    std::regex idRegex(R"(#([a-zA-Z0-9_-]+))");
    searchStart = selector.cbegin();
    
    while (std::regex_search(searchStart, selector.cend(), match, idRegex)) {
        result_.idNames.push_back(match[1]);
        searchStart = match.suffix().first;
    }
}

CssAnalysisResult CssAnalyzer::analyzeFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        result_.hasErrors = true;
        result_.errors.push_back("Failed to open file: " + filepath);
        return result_;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return analyze(buffer.str());
}

void CssAnalyzer::extractProperties(std::shared_ptr<CssBlock> block) {
    // TODO: 实现属性提取
}

void CssAnalyzer::analyzeAtRule(std::shared_ptr<CssBlock> block) {
    // TODO: 实现@规则分析
}

std::unordered_map<std::string, std::string> CssAnalyzer::extractCssVariables(const std::string& css) {
    std::unordered_map<std::string, std::string> variables;
    // TODO: 实现CSS变量提取
    return variables;
}

CssModernFeatures CssAnalyzer::detectModernFeatures(const std::string& css) const {
    CssModernFeatures features;
    // 使用非const版本的实现
    const_cast<CssAnalyzer*>(this)->detectModernFeatures(css);
    return const_cast<CssAnalyzer*>(this)->result_.modernFeatures;
}

} // namespace css
} // namespace chtl