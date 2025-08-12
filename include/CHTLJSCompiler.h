#ifndef CHTL_JS_COMPILER_H
#define CHTL_JS_COMPILER_H

#include <string>
#include <memory>
#include <unordered_map>
#include "ASTNode.h"
#include <antlr4-runtime.h>

namespace CHTL {

// 前向声明ANTLR生成的类
class CHTLJavaScriptLexer;
class CHTLJavaScriptParser;
class CHTLJavaScriptVisitor;

// CHTL JavaScript编译器
class CHTLJSCompiler {
public:
    CHTLJSCompiler();
    ~CHTLJSCompiler();
    
    // 编译CHTL扩展的JavaScript代码并返回AST
    std::shared_ptr<ASTNode> compile(const std::string& code);
    
    // 转换CHTL JS语法为标准JS
    std::string transform(const std::string& chtlJsCode);
    
    // 设置上下文信息（用于解析选择器）
    void setContext(const std::unordered_map<std::string, std::string>& contextInfo);
    
    // 获取错误信息
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    // 清除错误
    void clearErrors() { errors_.clear(); warnings_.clear(); }
    
private:
    // ANTLR访问者实现
    class CHTLJSVisitorImpl;
    std::unique_ptr<CHTLJSVisitorImpl> visitor_;
    
    // 上下文信息（如当前元素的类名、ID等）
    std::unordered_map<std::string, std::string> contextInfo_;
    
    // 错误收集
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 错误监听器
    class ErrorListener;
    std::unique_ptr<ErrorListener> errorListener_;
    
    // CHTL JS语法转换辅助函数
    std::string transformSelector(const std::string& selector);
    std::string transformListen(const std::string& listenCall);
    std::string transformDelegate(const std::string& delegateCall);
    std::string transformAnimate(const std::string& animateCall);
    std::string generateSelectorFunction(const std::string& selector);
};

} // namespace CHTL

#endif // CHTL_JS_COMPILER_H