#include "Js/JsAnalyzer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace chtl {
namespace js {

JsAnalyzer::JsAnalyzer() {
}

JsAnalysisResult JsAnalyzer::analyze(const std::string& js) {
    // 清空之前的结果
    result_ = JsAnalysisResult();
    
    // 基础语法验证
    if (!validateSyntax(js)) {
        result_.hasErrors = true;
        return result_;
    }
    
    // 检测现代特性
    detectModernFeatures(js);
    
    // 提取各种信息
    result_.functions = extractFunctions(js);
    result_.classes = extractClasses(js);
    extractIdentifiers(js);
    extractDependencies(js);
    
    // 计算复杂度
    calculateComplexity(js);
    
    // 统计信息
    auto stats = getStatistics(js);
    result_.functionCount = stats.functionCount;
    result_.classCount = stats.classCount;
    result_.lineCount = stats.totalLines;
    
    return result_;
}

void JsAnalyzer::detectModernFeatures(const std::string& js) {
    detectES6Features(js);
    detectES2017Features(js);
    detectES2020Features(js);
    detectES2022Features(js);
    detectProposalFeatures(js);
}

void JsAnalyzer::detectES6Features(const std::string& code) {
    // Arrow functions
    if (code.find("=>") != std::string::npos) {
        result_.modernFeatures.arrowFunctions = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
    
    // Classes
    std::regex classRegex(R"(\bclass\s+\w+)");
    if (std::regex_search(code, classRegex)) {
        result_.modernFeatures.classes = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
    
    // Template literals
    if (code.find("`") != std::string::npos) {
        result_.modernFeatures.templateLiterals = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
    
    // let/const
    std::regex letConstRegex(R"(\b(let|const)\s+)");
    if (std::regex_search(code, letConstRegex)) {
        result_.modernFeatures.letConst = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
    
    // Destructuring
    std::regex destructRegex(R"(\{[^}]*\}\s*=|\[[^\]]*\]\s*=)");
    if (std::regex_search(code, destructRegex)) {
        result_.modernFeatures.destructuring = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
    
    // Rest/Spread
    if (code.find("...") != std::string::npos) {
        result_.modernFeatures.restSpread = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
    
    // Modules
    std::regex moduleRegex(R"(\b(import|export)\s+)");
    if (std::regex_search(code, moduleRegex)) {
        result_.modernFeatures.modules = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES6);
    }
}

void JsAnalyzer::detectES2017Features(const std::string& code) {
    // Async/Await
    std::regex asyncRegex(R"(\basync\s+(function|\(|[a-zA-Z_$]))");
    std::regex awaitRegex(R"(\bawait\s+)");
    if (std::regex_search(code, asyncRegex) || std::regex_search(code, awaitRegex)) {
        result_.modernFeatures.asyncAwait = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2017);
    }
}

void JsAnalyzer::detectES2020Features(const std::string& code) {
    // Optional chaining
    if (code.find("?.") != std::string::npos) {
        result_.modernFeatures.optionalChaining = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2020);
    }
    
    // Nullish coalescing
    if (code.find("??") != std::string::npos) {
        result_.modernFeatures.nullishCoalescing = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2020);
    }
    
    // BigInt
    std::regex bigIntRegex(R"(\d+n\b)");
    if (std::regex_search(code, bigIntRegex)) {
        result_.modernFeatures.bigInt = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2020);
    }
    
    // Dynamic import
    std::regex dynamicImportRegex(R"(import\s*\()");
    if (std::regex_search(code, dynamicImportRegex)) {
        result_.modernFeatures.dynamicImport = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2020);
    }
}

void JsAnalyzer::detectES2022Features(const std::string& code) {
    // Top-level await
    std::regex topLevelAwaitRegex(R"(^[^{]*\bawait\s+)", std::regex::multiline);
    if (std::regex_search(code, topLevelAwaitRegex)) {
        result_.modernFeatures.topLevelAwait = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2022);
    }
    
    // Private fields
    std::regex privateFieldRegex(R"(#[a-zA-Z_$][a-zA-Z0-9_$]*)");
    if (std::regex_search(code, privateFieldRegex)) {
        result_.modernFeatures.privateFields = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2022);
    }
    
    // Static blocks
    std::regex staticBlockRegex(R"(static\s*\{)");
    if (std::regex_search(code, staticBlockRegex)) {
        result_.modernFeatures.staticBlocks = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2022);
    }
    
    // Error cause
    std::regex errorCauseRegex(R"(new\s+Error\s*\([^)]*,\s*\{\s*cause\s*:)");
    if (std::regex_search(code, errorCauseRegex)) {
        result_.modernFeatures.errorCause = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2022);
    }
    
    // Array.at()
    std::regex arrayAtRegex(R"(\.at\s*\()");
    if (std::regex_search(code, arrayAtRegex)) {
        result_.modernFeatures.arrayAt = true;
        result_.modernFeatures.highestVersionUsed = std::max(result_.modernFeatures.highestVersionUsed, EsVersion::ES2022);
    }
}

void JsAnalyzer::detectProposalFeatures(const std::string& code) {
    // Decorators
    std::regex decoratorRegex(R"(@[a-zA-Z_$][a-zA-Z0-9_$]*\s*(class|\([^)]*\)\s*{))");
    if (std::regex_search(code, decoratorRegex)) {
        result_.modernFeatures.decorators = true;
        result_.modernFeatures.highestVersionUsed = EsVersion::ESNEXT;
    }
}

bool JsAnalyzer::validateSyntax(const std::string& js) {
    // 基础括号平衡检查
    int braceCount = 0;
    int parenCount = 0;
    int bracketCount = 0;
    bool inString = false;
    bool inTemplate = false;
    char stringChar = '\0';
    
    for (size_t i = 0; i < js.length(); ++i) {
        char c = js[i];
        
        // 处理字符串
        if ((c == '"' || c == '\'') && (i == 0 || js[i-1] != '\\') && !inTemplate) {
            if (!inString) {
                inString = true;
                stringChar = c;
            } else if (c == stringChar) {
                inString = false;
            }
            continue;
        }
        
        // 处理模板字符串
        if (c == '`' && (i == 0 || js[i-1] != '\\')) {
            inTemplate = !inTemplate;
            continue;
        }
        
        if (inString || inTemplate) continue;
        
        // 处理注释
        if (c == '/' && i + 1 < js.length()) {
            if (js[i+1] == '/') {
                // 单行注释
                size_t endLine = js.find('\n', i);
                if (endLine == std::string::npos) {
                    i = js.length();
                } else {
                    i = endLine;
                }
                continue;
            } else if (js[i+1] == '*') {
                // 多行注释
                size_t endComment = js.find("*/", i + 2);
                if (endComment == std::string::npos) {
                    result_.errors.push_back("Unclosed comment");
                    return false;
                }
                i = endComment + 1;
                continue;
            }
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

std::vector<std::string> JsAnalyzer::extractFunctions(const std::string& js) {
    std::vector<std::string> functions;
    
    // 函数声明
    std::regex funcDeclRegex(R"(function\s+([a-zA-Z_$][a-zA-Z0-9_$]*)\s*\()");
    std::smatch match;
    std::string::const_iterator searchStart(js.cbegin());
    
    while (std::regex_search(searchStart, js.cend(), match, funcDeclRegex)) {
        functions.push_back(match[1]);
        searchStart = match.suffix().first;
    }
    
    // 箭头函数（带名称的）
    std::regex arrowFuncRegex(R"((?:const|let|var)\s+([a-zA-Z_$][a-zA-Z0-9_$]*)\s*=\s*(?:\([^)]*\)|[a-zA-Z_$][a-zA-Z0-9_$]*)\s*=>)");
    searchStart = js.cbegin();
    
    while (std::regex_search(searchStart, js.cend(), match, arrowFuncRegex)) {
        functions.push_back(match[1]);
        searchStart = match.suffix().first;
    }
    
    // 方法定义（ES6类方法）
    std::regex methodRegex(R"(([a-zA-Z_$][a-zA-Z0-9_$]*)\s*\([^)]*\)\s*\{)");
    searchStart = js.cbegin();
    
    // 需要更复杂的逻辑来区分方法和函数调用
    
    return functions;
}

std::vector<std::string> JsAnalyzer::extractClasses(const std::string& js) {
    std::vector<std::string> classes;
    
    std::regex classRegex(R"(class\s+([a-zA-Z_$][a-zA-Z0-9_$]*))");
    std::smatch match;
    std::string::const_iterator searchStart(js.cbegin());
    
    while (std::regex_search(searchStart, js.cend(), match, classRegex)) {
        classes.push_back(match[1]);
        searchStart = match.suffix().first;
    }
    
    return classes;
}

JsAnalysisResult JsAnalyzer::analyzeFile(const std::string& filepath) {
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

JsAnalyzer::CodeStatistics JsAnalyzer::getStatistics(const std::string& js) {
    CodeStatistics stats{};
    
    std::istringstream stream(js);
    std::string line;
    
    while (std::getline(stream, line)) {
        stats.totalLines++;
        
        // 去除首尾空格
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) {
            stats.blankLines++;
        } else if (line.find("//") == 0 || (line.find("/*") == 0 && line.find("*/") != std::string::npos)) {
            stats.commentLines++;
        } else {
            stats.codeLines++;
        }
    }
    
    stats.functionCount = extractFunctions(js).size();
    stats.classCount = extractClasses(js).size();
    
    return stats;
}

void JsAnalyzer::extractIdentifiers(const std::string& code) {
    // 简单的标识符提取
    std::regex identifierRegex(R"(\b([a-zA-Z_$][a-zA-Z0-9_$]*)\b)");
    std::smatch match;
    std::string::const_iterator searchStart(code.cbegin());
    
    while (std::regex_search(searchStart, code.cend(), match, identifierRegex)) {
        result_.identifiers.insert(match[1]);
        searchStart = match.suffix().first;
    }
}

void JsAnalyzer::extractDependencies(const std::string& code) {
    // 提取import语句中的依赖
    std::regex importRegex(R"(import\s+.*?\s+from\s+['"](.*?)['"])");
    std::smatch match;
    std::string::const_iterator searchStart(code.cbegin());
    
    while (std::regex_search(searchStart, code.cend(), match, importRegex)) {
        result_.dependencies.insert(match[1]);
        searchStart = match.suffix().first;
    }
    
    // 提取require语句中的依赖
    std::regex requireRegex(R"(require\s*\(\s*['"](.*?)['"]\s*\))");
    searchStart = code.cbegin();
    
    while (std::regex_search(searchStart, code.cend(), match, requireRegex)) {
        result_.dependencies.insert(match[1]);
        searchStart = match.suffix().first;
    }
}

void JsAnalyzer::calculateComplexity(const std::string& code) {
    // 简单的圈复杂度计算
    result_.cyclomaticComplexity = 1; // 基础复杂度
    
    // 条件语句增加复杂度
    std::vector<std::string> complexityKeywords = {
        "\\bif\\b", "\\belse\\s+if\\b", "\\bfor\\b", "\\bwhile\\b", 
        "\\bdo\\b", "\\bcase\\b", "\\bcatch\\b", "\\?", "&&", "\\|\\|"
    };
    
    for (const auto& keyword : complexityKeywords) {
        std::regex keywordRegex(keyword);
        std::smatch match;
        std::string::const_iterator searchStart(code.cbegin());
        
        while (std::regex_search(searchStart, code.cend(), match, keywordRegex)) {
            result_.cyclomaticComplexity++;
            searchStart = match.suffix().first;
        }
    }
}

} // namespace js
} // namespace chtl