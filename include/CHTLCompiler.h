#ifndef CHTL_COMPILER_H
#define CHTL_COMPILER_H

#include <string>
#include <memory>
#include "ASTNode.h"
#include "SymbolTable.h"

// ANTLR4 运行时头文件
#include <antlr4-runtime.h>

namespace CHTL {

// 前向声明ANTLR生成的类
class CHTLLexer;
class CHTLParser;
class CHTLVisitor;

// CHTL编译器
class CHTLCompiler {
public:
    CHTLCompiler(SymbolTable* symbolTable);
    ~CHTLCompiler();
    
    // 编译CHTL代码并返回AST
    std::shared_ptr<ASTNode> compile(const std::string& code);
    
    // 解析CHTL文件
    std::shared_ptr<ASTNode> parseFile(const std::string& filePath);
    
    // 获取错误信息
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    // 清除错误
    void clearErrors() { errors_.clear(); warnings_.clear(); }
    
private:
    // ANTLR访问者实现
    class CHTLVisitorImpl;
    std::unique_ptr<CHTLVisitorImpl> visitor_;
    
    // 符号表引用
    SymbolTable* symbolTable_;
    
    // 错误收集
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 错误监听器
    class ErrorListener;
    std::unique_ptr<ErrorListener> errorListener_;
};

} // namespace CHTL

#endif // CHTL_COMPILER_H