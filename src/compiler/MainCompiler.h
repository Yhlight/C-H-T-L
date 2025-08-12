#ifndef CHTL_COMPILER_MAIN_COMPILER_H
#define CHTL_COMPILER_MAIN_COMPILER_H

#include "Compiler.h"
#include "../scanner/CodeScanner.h"
#include "../chtl/CHTLCompiler.h"
#include "../css/CSSCompiler.h"
#include "../js/JavaScriptCompiler.h"
#include "../chtljs/CHTLJSCompiler.h"
#include <memory>
#include <string>
#include <vector>

namespace chtl {

// 主编译器类 - 协调4个独立编译器
class MainCompiler : public Compiler {
public:
    MainCompiler();
    ~MainCompiler() = default;

    // 编译完整的CHTL文件
    bool compile(const std::string& sourceCode);
    
    // 获取编译结果
    std::string getHTML() const { return htmlOutput_; }
    std::string getCSS() const { return cssOutput_; }
    std::string getJavaScript() const { return jsOutput_; }
    
    // 获取编译统计信息
    std::map<std::string, int> getStats() const;
    
    // 获取警告信息
    std::vector<std::string> getWarnings() const;
    
    // 获取错误信息
    std::string getError() const;
    
    // 设置编译选项
    void setOptions(const std::map<std::string, std::string>& options);

private:
    std::unique_ptr<CodeScanner> scanner_;
    std::unique_ptr<CHTLCompiler> chtlCompiler_;
    std::unique_ptr<CSSCompiler> cssCompiler_;
    std::unique_ptr<JavaScriptCompiler> jsCompiler_;
    std::unique_ptr<CHTLJSCompiler> chtljsCompiler_;
    
    std::string htmlOutput_;
    std::string cssOutput_;
    std::string jsOutput_;
    
    std::map<std::string, std::string> options_;
    
    // 扫描并分类代码块
    std::vector<CodeBlock> scanCodeBlocks(const std::string& sourceCode);
    
    // 分发代码块到相应的编译器
    void dispatchCodeBlocks(const std::vector<CodeBlock>& codeBlocks);
    
    // 编译CHTL代码块
    bool compileCHTLBlock(const CodeBlock& block);
    
    // 编译CSS代码块
    bool compileCSSBlock(const CodeBlock& block);
    
    // 编译JavaScript代码块
    bool compileJSBlock(const CodeBlock& block);
    
    // 编译CHTL JS代码块
    bool compileCHTLJSBlock(const CodeBlock& block);
    
    // 合并编译结果
    void mergeCompilationResults();
    
    // 验证编译结果
    bool validateCompilationResults();
    
    // 生成最终输出
    void generateFinalOutput();
    
    // 处理编译器间的依赖关系
    void resolveDependencies();
    
    // 优化输出
    void optimizeOutput();
    
    // 收集统计信息
    void collectStatistics();
    
    // 处理编译错误
    void handleCompilationError(const std::string& error, const CodeBlock& block);
    
    // 处理编译警告
    void handleCompilationWarning(const std::string& warning, const CodeBlock& block);
};

} // namespace chtl

#endif // CHTL_COMPILER_MAIN_COMPILER_H