#ifndef JS_COMPILER_H
#define JS_COMPILER_H

#include <string>
#include <memory>
#include "ASTNode.h"
#include <antlr4-runtime.h>

namespace CHTL {

// 前向声明ANTLR生成的类
class JavaScriptLexer;
class JavaScriptParser;
class JavaScriptVisitor;

// JavaScript编译器
class JSCompiler {
public:
    JSCompiler();
    ~JSCompiler();
    
    // 编译JavaScript代码并返回AST
    std::shared_ptr<ASTNode> compile(const std::string& code);
    
    // 解析JavaScript文件
    std::shared_ptr<ASTNode> parseFile(const std::string& filePath);
    
    // 验证JavaScript代码
    bool validate(const std::string& code);
    
    // 获取错误信息
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    // 清除错误
    void clearErrors() { errors_.clear(); warnings_.clear(); }
    
private:
    // ANTLR访问者实现
    class JSVisitorImpl;
    std::unique_ptr<JSVisitorImpl> visitor_;
    
    // 错误收集
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 错误监听器
    class ErrorListener;
    std::unique_ptr<ErrorListener> errorListener_;
};

} // namespace CHTL

#endif // JS_COMPILER_H