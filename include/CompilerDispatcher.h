#ifndef COMPILER_DISPATCHER_H
#define COMPILER_DISPATCHER_H

#include <string>
#include <memory>
#include <vector>
#include "Scanner.h"
#include "ASTNode.h"

namespace CHTL {

// 前向声明
class CHTLCompiler;
class CSSCompiler;
class JSCompiler;
class CHTLJSCompiler;
class SymbolTable;

// 编译结果
struct CompilationResult {
    bool success;
    std::string html;
    std::string css;
    std::string javascript;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

// 编译器调度器
class CompilerDispatcher {
public:
    CompilerDispatcher();
    ~CompilerDispatcher();
    
    // 编译CHTL文件
    CompilationResult compile(const std::string& chtlContent);
    
    // 编译单个文件并返回AST
    std::shared_ptr<ASTNode> compileFile(const std::string& filePath);
    
    // 设置配置
    void setConfiguration(const std::string& key, const std::string& value);
    
    // 获取符号表
    SymbolTable* getSymbolTable() const { return symbolTable_.get(); }
    
private:
    // 处理代码片段
    std::shared_ptr<ASTNode> processFragment(const CodeFragment& fragment);
    
    // 合并编译结果
    void mergeResults(CompilationResult& result, 
                     const std::shared_ptr<ASTNode>& ast);
    
    // 验证和优化
    bool validate(const std::vector<std::shared_ptr<ASTNode>>& asts);
    void optimize(std::vector<std::shared_ptr<ASTNode>>& asts);
    
    // 错误处理
    void addError(const std::string& error);
    void addWarning(const std::string& warning);
    
private:
    std::unique_ptr<Scanner> scanner_;
    std::unique_ptr<CHTLCompiler> chtlCompiler_;
    std::unique_ptr<CSSCompiler> cssCompiler_;
    std::unique_ptr<JSCompiler> jsCompiler_;
    std::unique_ptr<CHTLJSCompiler> chtljsCompiler_;
    std::unique_ptr<SymbolTable> symbolTable_;
    
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
};

} // namespace CHTL

#endif // COMPILER_DISPATCHER_H