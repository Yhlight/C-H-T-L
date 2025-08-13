#include "CSSCompiler.h"
#include <iostream>
#include <regex>
#include <sstream>

namespace chtl {

CSSCompiler::CSSCompiler() : cssOutput_("") {
    // 初始化CSS编译器
}

bool CSSCompiler::compile(const std::string& sourceCode) {
    try {
        // 解析CSS语法树
        parseCSS(sourceCode);
        
        // 处理各种CSS特性
        processSelectors();
        processProperties();
        processMediaQueries();
        processAnimations();
        processVariables();
        processNesting();
        
        // 生成CSS输出
        generateCSS();
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "CSS编译错误: " << e.what() << std::endl;
        return false;
    }
}

bool CSSCompiler::validate(const std::string& sourceCode) {
    try {
        // 基本的CSS语法验证
        std::regex cssRulePattern(R"(([^{}]+)\s*\{[^{}]*\})");
        std::sregex_iterator iter(sourceCode.begin(), sourceCode.end(), cssRulePattern);
        std::sregex_iterator end;
        
        while (iter != end) {
            std::string rule = (*iter)[0];
            std::string selector = (*iter)[1];
            
            if (!validateSelector(selector)) {
                return false;
            }
            
            ++iter;
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "CSS验证错误: " << e.what() << std::endl;
        return false;
    }
}

std::string CSSCompiler::minify(const std::string& sourceCode) {
    std::string minified = sourceCode;
    
    // 移除注释
    std::regex commentPattern(R"(\/\*[^*]*\*+(?:[^/*][^*]*\*+)*\/)");
    minified = std::regex_replace(minified, commentPattern, "");
    
    // 移除多余的空白字符
    std::regex whitespacePattern(R"(\s+)");
    minified = std::regex_replace(minified, whitespacePattern, " ");
    
    // 移除规则前后的空白
    minified = std::regex_replace(minified, std::regex(R"(\s*\{\s*)"), "{");
    minified = std::regex_replace(minified, std::regex(R"(\s*\}\s*)"), "}");
    minified = std::regex_replace(minified, std::regex(R"(\s*:\s*)"), ":");
    minified = std::regex_replace(minified, std::regex(R"(\s*;\s*)"), ";");
    
    return minified;
}

std::string CSSCompiler::addPrefixes(const std::string& sourceCode) {
    std::string prefixed = sourceCode;
    
    // 添加浏览器前缀
    std::vector<std::pair<std::string, std::vector<std::string>>> prefixMap = {
        {"transform", {"-webkit-transform", "-moz-transform", "-ms-transform"}},
        {"transition", {"-webkit-transition", "-moz-transition", "-o-transition"}},
        {"animation", {"-webkit-animation", "-moz-animation", "-o-animation"}},
        {"border-radius", {"-webkit-border-radius", "-moz-border-radius"}},
        {"box-shadow", {"-webkit-box-shadow", "-moz-box-shadow"}},
        {"flex", {"-webkit-box", "-moz-box", "-ms-flexbox"}},
        {"flex-direction", {"-webkit-box-orient", "-webkit-box-direction", "-moz-box-orient", "-moz-box-direction"}}
    };
    
    for (const auto& [property, prefixes] : prefixMap) {
        std::regex propertyPattern(property + R"(\s*:\s*[^;]+;)");
        std::string replacement;
        
        for (const auto& prefix : prefixes) {
            replacement += prefix + ":" + std::string("$&") + ";\n";
        }
        replacement += property + ":" + std::string("$&") + ";";
        
        prefixed = std::regex_replace(prefixed, propertyPattern, replacement);
    }
    
    return prefixed;
}

void CSSCompiler::parseCSS(const std::string& sourceCode) {
    // 使用ANTLR4生成的词法分析器解析CSS
    // 这里将集成生成的CSSLexer
    std::cout << "解析CSS代码..." << std::endl;
}

void CSSCompiler::generateCSS() {
    // 生成最终的CSS输出
    std::cout << "生成CSS输出..." << std::endl;
}

void CSSCompiler::processSelectors() {
    // 处理CSS选择器
    std::cout << "处理CSS选择器..." << std::endl;
}

void CSSCompiler::processProperties() {
    // 处理CSS属性
    std::cout << "处理CSS属性..." << std::endl;
}

void CSSCompiler::processMediaQueries() {
    // 处理媒体查询
    std::cout << "处理媒体查询..." << std::endl;
}

void CSSCompiler::processAnimations() {
    // 处理CSS动画
    std::cout << "处理CSS动画..." << std::endl;
}

void CSSCompiler::processVariables() {
    // 处理CSS变量
    std::cout << "处理CSS变量..." << std::endl;
}

void CSSCompiler::processNesting() {
    // 处理CSS嵌套
    std::cout << "处理CSS嵌套..." << std::endl;
}

bool CSSCompiler::validateSelector(const std::string& selector) {
    // 验证CSS选择器语法
    if (selector.empty()) {
        return false;
    }
    
    // 基本的选择器验证规则
    std::regex validSelectorPattern(R"(^[.#]?[a-zA-Z][a-zA-Z0-9_-]*(\.[a-zA-Z][a-zA-Z0-9_-]*)*(#[a-zA-Z][a-zA-Z0-9_-]*)?(\[[^\]]*\])*(\:[a-zA-Z-]+)?(\:\:[a-zA-Z-]+)?$)");
    
    return std::regex_match(selector, validSelectorPattern);
}

bool CSSCompiler::validatePropertyValue(const std::string& property, const std::string& value) {
    // 验证CSS属性值
    if (value.empty()) {
        return false;
    }
    
    // 这里可以添加更详细的属性值验证逻辑
    return true;
}

} // namespace chtl