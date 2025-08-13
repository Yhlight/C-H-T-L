#ifndef CHTL_COMPILER_COMPILER_H
#define CHTL_COMPILER_COMPILER_H

#include <string>

namespace chtl {

// 编译器基类
class Compiler {
public:
    Compiler() = default;
    virtual ~Compiler() = default;

    // 编译代码的虚函数
    virtual bool compile(const std::string& sourceCode) = 0;
    
    // 验证代码的虚函数
    virtual bool validate(const std::string& sourceCode) = 0;
    
    // 获取编译状态
    bool isCompiled() const { return compiled_; }
    
    // 获取错误信息
    std::string getErrorMessage() const { return errorMessage_; }
    
    // 清除错误信息
    void clearError() { errorMessage_.clear(); }

protected:
    bool compiled_ = false;
    std::string errorMessage_;
    
    // 设置错误信息
    void setError(const std::string& message) {
        errorMessage_ = message;
        compiled_ = false;
    }
    
    // 设置编译成功
    void setCompiled() {
        compiled_ = true;
        errorMessage_.clear();
    }
};

} // namespace chtl

#endif // CHTL_COMPILER_COMPILER_H