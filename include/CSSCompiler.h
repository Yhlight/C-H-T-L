#ifndef CSS_COMPILER_H
#define CSS_COMPILER_H

#include <string>
#include <memory>
#include "ASTNode.h"
#include <antlr4-runtime.h>

namespace CHTL {

// 前向声明ANTLR生成的类
class CSSLexer;
class CSSParser;
class CSSVisitor;

// CSS编译器
class CSSCompiler {
public:
    CSSCompiler();
    ~CSSCompiler();
    
    // 编译CSS代码并返回AST
    std::shared_ptr<ASTNode> compile(const std::string& code);
    
    // 解析CSS文件
    std::shared_ptr<ASTNode> parseFile(const std::string& filePath);
    
    // 验证CSS代码
    bool validate(const std::string& code);
    
    // 获取错误信息
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    // 清除错误
    void clearErrors() { errors_.clear(); warnings_.clear(); }
    
private:
    // ANTLR访问者实现
    class CSSVisitorImpl;
    std::unique_ptr<CSSVisitorImpl> visitor_;
    
    // 错误收集
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 错误监听器
    class ErrorListener;
    std::unique_ptr<ErrorListener> errorListener_;
};

} // namespace CHTL

#endif // CSS_COMPILER_H