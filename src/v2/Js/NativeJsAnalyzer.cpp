#include "v2/Js/NativeJsAnalyzer.h"
#include <regex>
#include <sstream>

namespace chtl::v2::js {

class NativeJsAnalyzer::Impl {
public:
    JsAnalysisResult analyze(const std::string& js) {
        JsAnalysisResult result;
        
        if (js.empty()) {
            return result;
        }
        
        // 简单的 JS 语法检查
        checkSyntax(js, result);
        
        // 提取结构信息
        extractStructure(js, result);
        
        return result;
    }
    
    void setOption(const std::string& name, bool value) {
        if (name == "strict") {
            strict_ = value;
        } else if (name == "esModules") {
            esModules_ = value;
        }
    }
    
private:
    void checkSyntax(const std::string& js, JsAnalysisResult& result) {
        // 基本的括号匹配
        int parenDepth = 0;
        int braceDepth = 0;
        int bracketDepth = 0;
        
        bool inString = false;
        bool inComment = false;
        char stringChar = 0;
        
        for (size_t i = 0; i < js.length(); ++i) {
            char ch = js[i];
            char next = (i + 1 < js.length()) ? js[i + 1] : 0;
            
            // 处理注释
            if (!inString && !inComment && ch == '/' && next == '/') {
                // 单行注释，跳到行尾
                while (i < js.length() && js[i] != '\n') i++;
                continue;
            }
            
            if (!inString && !inComment && ch == '/' && next == '*') {
                inComment = true;
                i++; // 跳过 *
                continue;
            }
            
            if (inComment && ch == '*' && next == '/') {
                inComment = false;
                i++; // 跳过 /
                continue;
            }
            
            if (inComment) continue;
            
            // 处理字符串
            if (!inString && (ch == '"' || ch == '\'' || ch == '`')) {
                inString = true;
                stringChar = ch;
            } else if (inString && ch == stringChar && js[i-1] != '\\') {
                inString = false;
            }
            
            if (inString) continue;
            
            // 检查括号匹配
            switch (ch) {
                case '(': parenDepth++; break;
                case ')': 
                    parenDepth--; 
                    if (parenDepth < 0) {
                        result.errors.push_back("Unmatched ')' at position " + 
                                              std::to_string(i));
                        result.valid = false;
                    }
                    break;
                case '{': braceDepth++; break;
                case '}': 
                    braceDepth--; 
                    if (braceDepth < 0) {
                        result.errors.push_back("Unmatched '}' at position " + 
                                              std::to_string(i));
                        result.valid = false;
                    }
                    break;
                case '[': bracketDepth++; break;
                case ']': 
                    bracketDepth--; 
                    if (bracketDepth < 0) {
                        result.errors.push_back("Unmatched ']' at position " + 
                                              std::to_string(i));
                        result.valid = false;
                    }
                    break;
            }
        }
        
        // 检查最终深度
        if (parenDepth != 0) {
            result.errors.push_back("Unclosed parentheses");
            result.valid = false;
        }
        if (braceDepth != 0) {
            result.errors.push_back("Unclosed braces");
            result.valid = false;
        }
        if (bracketDepth != 0) {
            result.errors.push_back("Unclosed brackets");
            result.valid = false;
        }
    }
    
    void extractStructure(const std::string& js, JsAnalysisResult& result) {
        // 提取变量声明
        extractVariables(js, result);
        
        // 提取函数声明
        extractFunctions(js, result);
        
        // 提取导入导出
        if (esModules_) {
            extractImportsExports(js, result);
        }
    }
    
    void extractVariables(const std::string& js, JsAnalysisResult& result) {
        // 匹配 var/let/const 声明
        std::regex varRegex(R"(\b(var|let|const)\s+([a-zA-Z_$][a-zA-Z0-9_$]*))");
        std::sregex_iterator it(js.begin(), js.end(), varRegex);
        std::sregex_iterator end;
        
        int lineNum = 1;
        for (; it != end; ++it) {
            JsAnalysisResult::Variable var;
            var.type = (*it)[1];
            var.name = (*it)[2];
            var.line = lineNum; // 简化的行号计算
            
            result.variables.push_back(var);
        }
    }
    
    void extractFunctions(const std::string& js, JsAnalysisResult& result) {
        // 匹配函数声明
        std::regex funcRegex(R"(\b(async\s+)?function\s+([a-zA-Z_$][a-zA-Z0-9_$]*))");
        std::sregex_iterator it(js.begin(), js.end(), funcRegex);
        std::sregex_iterator end;
        
        for (; it != end; ++it) {
            JsAnalysisResult::Function func;
            func.isAsync = !(*it)[1].str().empty();
            func.name = (*it)[2];
            func.isArrow = false;
            func.line = 1; // 简化的行号
            
            result.functions.push_back(func);
        }
        
        // 匹配箭头函数
        std::regex arrowRegex(R"(\b(const|let|var)\s+([a-zA-Z_$][a-zA-Z0-9_$]*)\s*=\s*(async\s*)?\([^)]*\)\s*=>)");
        it = std::sregex_iterator(js.begin(), js.end(), arrowRegex);
        
        for (; it != end; ++it) {
            JsAnalysisResult::Function func;
            func.name = (*it)[2];
            func.isAsync = !(*it)[3].str().empty();
            func.isArrow = true;
            func.line = 1; // 简化的行号
            
            result.functions.push_back(func);
        }
    }
    
    void extractImportsExports(const std::string& js, JsAnalysisResult& result) {
        // 匹配 import 语句
        std::regex importRegex(R"(import\s+.*?\s+from\s+['"](.*?)['"])");
        std::sregex_iterator it(js.begin(), js.end(), importRegex);
        std::sregex_iterator end;
        
        for (; it != end; ++it) {
            result.imports.push_back((*it)[1]);
        }
        
        // 匹配 export 语句
        std::regex exportRegex(R"(export\s+(default\s+)?(?:function|class|const|let|var)\s+([a-zA-Z_$][a-zA-Z0-9_$]*))");
        it = std::sregex_iterator(js.begin(), js.end(), exportRegex);
        
        for (; it != end; ++it) {
            result.exports.push_back((*it)[2]);
        }
    }
    
    bool strict_ = false;
    bool esModules_ = true;
};

NativeJsAnalyzer::NativeJsAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

NativeJsAnalyzer::~NativeJsAnalyzer() = default;

JsAnalysisResult NativeJsAnalyzer::analyze(const std::string& js) {
    return impl_->analyze(js);
}

void NativeJsAnalyzer::setOption(const std::string& name, bool value) {
    impl_->setOption(name, value);
}

} // namespace chtl::v2::js