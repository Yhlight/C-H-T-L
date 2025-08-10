#include "Js/JsAnalyzer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace chtl {

class JsAnalyzer::Impl {
public:
    JsAnalysisResult result;
    
    void reset() {
        result = JsAnalysisResult();
    }
};

JsAnalyzer::JsAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

JsAnalyzer::~JsAnalyzer() = default;

JsAnalysisResult JsAnalyzer::analyze(const std::string& js) {
    impl_->reset();
    
    // 简单实现：提取基本信息
    extractFunctions(js);
    extractClasses(js);
    extractVariables(js);
    extractImports(js);
    extractExports(js);
    detectModernFeatures(js);
    
    return impl_->result;
}

std::unordered_set<std::string> JsAnalyzer::extractFunctions(const std::string& js) {
    std::unordered_set<std::string> functions;
    
    // 简单实现：查找function关键字
    size_t pos = 0;
    while ((pos = js.find("function", pos)) != std::string::npos) {
        pos += 8; // 跳过"function"
        
        // 跳过空白
        while (pos < js.length() && std::isspace(js[pos])) {
            pos++;
        }
        
        // 提取函数名
        if (pos < js.length() && (std::isalpha(js[pos]) || js[pos] == '_')) {
            size_t start = pos;
            while (pos < js.length() && 
                   (std::isalnum(js[pos]) || js[pos] == '_')) {
                pos++;
            }
            std::string funcName = js.substr(start, pos - start);
            functions.insert(funcName);
            impl_->result.functions.insert(funcName);
        }
    }
    
    return functions;
}

std::unordered_set<std::string> JsAnalyzer::extractClasses(const std::string& js) {
    std::unordered_set<std::string> classes;
    
    // 简单实现：查找class关键字
    size_t pos = 0;
    while ((pos = js.find("class", pos)) != std::string::npos) {
        // 确保是独立的class关键字
        if (pos > 0 && (std::isalnum(js[pos - 1]) || js[pos - 1] == '_')) {
            pos++;
            continue;
        }
        
        pos += 5; // 跳过"class"
        
        // 跳过空白
        while (pos < js.length() && std::isspace(js[pos])) {
            pos++;
        }
        
        // 提取类名
        if (pos < js.length() && (std::isalpha(js[pos]) || js[pos] == '_')) {
            size_t start = pos;
            while (pos < js.length() && 
                   (std::isalnum(js[pos]) || js[pos] == '_')) {
                pos++;
            }
            std::string className = js.substr(start, pos - start);
            classes.insert(className);
            impl_->result.classes.insert(className);
        }
    }
    
    return classes;
}

std::unordered_set<std::string> JsAnalyzer::extractVariables(const std::string& js) {
    std::unordered_set<std::string> variables;
    
    // 简单实现：查找var, let, const
    std::vector<std::string> keywords = {"var", "let", "const"};
    
    for (const auto& keyword : keywords) {
        size_t pos = 0;
        while ((pos = js.find(keyword, pos)) != std::string::npos) {
            // 确保是独立的关键字
            if (pos > 0 && (std::isalnum(js[pos - 1]) || js[pos - 1] == '_')) {
                pos++;
                continue;
            }
            
            pos += keyword.length();
            
            // 跳过空白
            while (pos < js.length() && std::isspace(js[pos])) {
                pos++;
            }
            
            // 提取变量名
            if (pos < js.length() && (std::isalpha(js[pos]) || js[pos] == '_')) {
                size_t start = pos;
                while (pos < js.length() && 
                       (std::isalnum(js[pos]) || js[pos] == '_')) {
                    pos++;
                }
                std::string varName = js.substr(start, pos - start);
                variables.insert(varName);
                impl_->result.variables.insert(varName);
            }
        }
    }
    
    return variables;
}

std::unordered_set<std::string> JsAnalyzer::extractImports(const std::string& js) {
    std::unordered_set<std::string> imports;
    
    // 简单实现：查找import语句
    size_t pos = 0;
    while ((pos = js.find("import", pos)) != std::string::npos) {
        // 确保是独立的import关键字
        if (pos > 0 && (std::isalnum(js[pos - 1]) || js[pos - 1] == '_')) {
            pos++;
            continue;
        }
        
        // 查找from
        size_t fromPos = js.find("from", pos);
        if (fromPos != std::string::npos) {
            // 查找模块名
            size_t quotePos = js.find_first_of("'\"", fromPos);
            if (quotePos != std::string::npos) {
                char quote = js[quotePos];
                size_t endQuote = js.find(quote, quotePos + 1);
                if (endQuote != std::string::npos) {
                    std::string module = js.substr(quotePos + 1, endQuote - quotePos - 1);
                    imports.insert(module);
                    impl_->result.imports.insert(module);
                }
            }
        }
        
        pos += 6;
    }
    
    return imports;
}

std::unordered_set<std::string> JsAnalyzer::extractExports(const std::string& js) {
    std::unordered_set<std::string> exports;
    
    // 简单实现：查找export语句
    size_t pos = 0;
    while ((pos = js.find("export", pos)) != std::string::npos) {
        // 确保是独立的export关键字
        if (pos > 0 && (std::isalnum(js[pos - 1]) || js[pos - 1] == '_')) {
            pos++;
            continue;
        }
        
        pos += 6;
        exports.insert("export");
        impl_->result.exports.insert("export");
    }
    
    return exports;
}

void JsAnalyzer::detectModernFeatures(const std::string& js) {
    // 箭头函数
    if (js.find("=>") != std::string::npos) {
        impl_->result.hasArrowFunctions = true;
    }
    
    // 类
    if (js.find("class") != std::string::npos) {
        impl_->result.hasClasses = true;
    }
    
    // 模板字符串
    if (js.find("`") != std::string::npos) {
        impl_->result.hasTemplateStrings = true;
    }
    
    // let/const
    if (js.find("let") != std::string::npos || js.find("const") != std::string::npos) {
        impl_->result.hasLetConst = true;
    }
    
    // 模块
    if (js.find("import") != std::string::npos || js.find("export") != std::string::npos) {
        impl_->result.hasModules = true;
    }
    
    // async/await
    if (js.find("async") != std::string::npos || js.find("await") != std::string::npos) {
        impl_->result.hasAsyncAwait = true;
    }
    
    // 可选链
    if (js.find("?.") != std::string::npos) {
        impl_->result.hasOptionalChaining = true;
    }
    
    // 空值合并
    if (js.find("??") != std::string::npos) {
        impl_->result.hasNullishCoalescing = true;
    }
}

} // namespace chtl