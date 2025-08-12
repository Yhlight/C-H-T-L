#pragma once

#include <string>
#include <vector>
#include <memory>

namespace chtl::v2::js {

/**
 * JS 分析结果
 */
struct JsAnalysisResult {
    bool valid = true;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // JS 结构信息
    struct Variable {
        std::string name;
        std::string type;  // var, let, const
        int line;
    };
    std::vector<Variable> variables;
    
    struct Function {
        std::string name;
        bool isAsync;
        bool isArrow;
        int line;
    };
    std::vector<Function> functions;
    
    // 导入/导出
    std::vector<std::string> imports;
    std::vector<std::string> exports;
};

/**
 * 原生 JS 分析器
 * 只处理标准 JavaScript 语法，不处理 CHTL-JS 扩展
 */
class NativeJsAnalyzer {
public:
    NativeJsAnalyzer();
    ~NativeJsAnalyzer();
    
    /**
     * 分析 JavaScript 代码
     * @param js 标准 JavaScript 代码
     * @return 分析结果
     */
    JsAnalysisResult analyze(const std::string& js);
    
    /**
     * 设置选项
     */
    void setOption(const std::string& name, bool value);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace chtl::v2::js