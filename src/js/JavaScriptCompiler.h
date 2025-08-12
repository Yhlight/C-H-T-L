#ifndef CHTL_COMPILER_JAVASCRIPT_COMPILER_H
#define CHTL_COMPILER_JAVASCRIPT_COMPILER_H

#include "../compiler/Compiler.h"
#include <string>
#include <vector>

namespace chtl {

// JavaScript编译器类
class JavaScriptCompiler : public Compiler {
public:
    JavaScriptCompiler();
    ~JavaScriptCompiler() = default;

    // 编译JavaScript代码
    bool compile(const std::string& sourceCode);
    
    // 获取编译后的JavaScript
    std::string getJavaScript() const { return jsOutput_; }
    
    // 验证JavaScript语法
    bool validate(const std::string& sourceCode);
    
    // 压缩JavaScript
    std::string minify(const std::string& sourceCode);
    
    // 转换ES6+语法
    std::string transpile(const std::string& sourceCode);

private:
    std::string jsOutput_;
    
    // 解析JavaScript语法树
    void parseJavaScript(const std::string& sourceCode);
    
    // 生成JavaScript输出
    void generateJavaScript();
    
    // 处理变量声明
    void processVariableDeclarations();
    
    // 处理函数声明
    void processFunctionDeclarations();
    
    // 处理类声明
    void processClassDeclarations();
    
    // 处理导入导出
    void processImportsExports();
    
    // 处理箭头函数
    void processArrowFunctions();
    
    // 处理模板字符串
    void processTemplateStrings();
    
    // 处理解构赋值
    void processDestructuring();
    
    // 处理展开运算符
    void processSpreadOperator();
    
    // 验证语法
    bool validateSyntax(const std::string& sourceCode);
    
    // 检查未定义的变量
    bool checkUndefinedVariables();
    
    // 检查未使用的变量
    bool checkUnusedVariables();
};

} // namespace chtl

#endif // CHTL_COMPILER_JAVASCRIPT_COMPILER_H