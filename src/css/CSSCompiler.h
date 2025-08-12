#ifndef CHTL_COMPILER_CSS_COMPILER_H
#define CHTL_COMPILER_CSS_COMPILER_H

#include "../compiler/Compiler.h"
#include <string>
#include <vector>

namespace chtl {

// CSS编译器类
class CSSCompiler : public Compiler {
public:
    CSSCompiler();
    ~CSSCompiler() = default;

    // 编译CSS代码
    bool compile(const std::string& sourceCode);
    
    // 获取编译后的CSS
    std::string getCSS() const { return cssOutput_; }
    
    // 验证CSS语法
    bool validate(const std::string& sourceCode);
    
    // 压缩CSS
    std::string minify(const std::string& sourceCode);
    
    // 添加前缀
    std::string addPrefixes(const std::string& sourceCode);

private:
    std::string cssOutput_;
    
    // 解析CSS语法树
    void parseCSS(const std::string& sourceCode);
    
    // 生成CSS输出
    void generateCSS();
    
    // 处理选择器
    void processSelectors();
    
    // 处理属性
    void processProperties();
    
    // 处理媒体查询
    void processMediaQueries();
    
    // 处理动画
    void processAnimations();
    
    // 处理变量
    void processVariables();
    
    // 处理嵌套
    void processNesting();
    
    // 验证选择器
    bool validateSelector(const std::string& selector);
    
    // 验证属性值
    bool validatePropertyValue(const std::string& property, const std::string& value);
};

} // namespace chtl

#endif // CHTL_COMPILER_CSS_COMPILER_H