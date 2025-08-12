#ifndef CHTL_COMPILER_CSS_COMPILER_H
#define CHTL_COMPILER_CSS_COMPILER_H

#include <string>
#include <memory>
#include <vector>

namespace chtl {

// 前向声明
class BasicLexer;
class CssContext;
class CssState;

// CSS 编译结果
struct CssCompileResult {
    std::string css;           // 编译后的 CSS
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    bool success = true;
};

// CSS 编译器 - CHTL 的四个编译器之一
class CssCompiler {
private:
    std::unique_ptr<BasicLexer> lexer_;
    std::shared_ptr<CssContext> context_;
    std::shared_ptr<CssState> state_;
    
    // 编译选项
    bool minify_ = false;
    bool preserveComments_ = true;
    bool validateProperties_ = true;
    
public:
    CssCompiler();
    ~CssCompiler();
    
    // 编译 CSS 代码
    CssCompileResult compile(const std::string& css);
    
    // 设置选项
    void setMinify(bool minify) { minify_ = minify; }
    void setPreserveComments(bool preserve) { preserveComments_ = preserve; }
    void setValidateProperties(bool validate) { validateProperties_ = validate; }
    
    // 获取上下文（用于调试或高级用途）
    std::shared_ptr<CssContext> getContext() const { return context_; }
    
private:
    // 初始化编译器
    void initialize();
    
    // 处理 CSS 内容
    std::string processCss(const std::string& css);
    
    // 验证 CSS
    bool validateCss(const std::string& css);
    
    // 压缩 CSS
    std::string minifyCss(const std::string& css);
    
    // 错误处理
    void addError(const std::string& message);
    void addWarning(const std::string& message);
    
    CssCompileResult result_;
};

} // namespace chtl

#endif // CHTL_COMPILER_CSS_COMPILER_H