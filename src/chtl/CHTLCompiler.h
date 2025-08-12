#ifndef CHTL_COMPILER_CHTL_COMPILER_H
#define CHTL_COMPILER_CHTL_COMPILER_H

#include "../compiler/Compiler.h"
#include <string>
#include <memory>

namespace chtl {

// CHTL编译器类
class CHTLCompiler : public Compiler {
public:
    CHTLCompiler();
    ~CHTLCompiler() = default;

    // 编译CHTL代码
    bool compile(const std::string& sourceCode);
    
    // 获取编译后的HTML
    std::string getHTML() const { return htmlOutput_; }
    
    // 获取编译后的CSS
    std::string getCSS() const { return cssOutput_; }
    
    // 获取编译后的JavaScript
    std::string getJavaScript() const { return jsOutput_; }

private:
    std::string htmlOutput_;
    std::string cssOutput_;
    std::string jsOutput_;
    
    // 解析CHTL语法树
    void parseCHTL(const std::string& sourceCode);
    
    // 生成HTML输出
    void generateHTML();
    
    // 生成CSS输出
    void generateCSS();
    
    // 生成JavaScript输出
    void generateJavaScript();
    
    // 处理模板
    void processTemplates();
    
    // 处理自定义元素
    void processCustomElements();
    
    // 处理样式组
    void processStyleGroups();
    
    // 处理变量组
    void processVariableGroups();
    
    // 处理命名空间
    void processNamespaces();
    
    // 处理导入
    void processImports();
    
    // 处理约束
    void processConstraints();
};

} // namespace chtl

#endif // CHTL_COMPILER_CHTL_COMPILER_H