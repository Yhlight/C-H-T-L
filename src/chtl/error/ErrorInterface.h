#ifndef CHTL_ERROR_INTERFACE_H
#define CHTL_ERROR_INTERFACE_H

#include <string>
#include <memory>
#include <functional>
#include <exception>

namespace chtl {
namespace error {

// 错误级别
enum class ErrorLevel {
    Debug = 0,
    Info = 1,
    Warning = 2,
    Error = 3,
    Fatal = 4
};

// 错误类别
enum class ErrorCategory {
    Syntax,      // 语法错误
    Semantic,    // 语义错误
    Type,        // 类型错误
    Reference,   // 引用错误
    Import,      // 导入错误
    Runtime,     // 运行时错误
    Internal,    // 内部错误
    IO,          // I/O错误
    Config,      // 配置错误
    Unknown      // 未知错误
};

// 源代码位置
struct SourceLocation {
    std::string filename;
    int line = 0;
    int column = 0;
    int offset = 0;
    
    std::string toString() const;
};

// 错误信息
struct ErrorInfo {
    ErrorLevel level = ErrorLevel::Error;
    ErrorCategory category = ErrorCategory::Unknown;
    std::string code;          // 错误代码，如 CHTL001
    std::string message;       // 错误消息
    std::string detail;        // 详细信息
    SourceLocation location;   // 错误位置
    
    // 构造函数
    ErrorInfo() = default;
    ErrorInfo(ErrorLevel lvl, ErrorCategory cat, const std::string& msg)
        : level(lvl), category(cat), message(msg) {}
};

// 错误处理器接口
class IErrorHandler {
public:
    virtual ~IErrorHandler() = default;
    
    // 处理错误
    virtual void handle(const ErrorInfo& error) = 0;
    
    // 设置错误过滤级别
    virtual void setMinLevel(ErrorLevel level) = 0;
    
    // 获取错误数量
    virtual size_t getErrorCount() const = 0;
    virtual size_t getWarningCount() const = 0;
    
    // 检查是否有错误
    virtual bool hasErrors() const = 0;
    virtual bool hasWarnings() const = 0;
    
    // 清除错误
    virtual void clear() = 0;
};

// 错误报告器接口
class IErrorReporter {
public:
    virtual ~IErrorReporter() = default;
    
    // 报告错误
    virtual void report(const ErrorInfo& error) = 0;
    
    // 便捷方法
    virtual void debug(const std::string& message, const SourceLocation& loc = {}) = 0;
    virtual void info(const std::string& message, const SourceLocation& loc = {}) = 0;
    virtual void warning(const std::string& message, const SourceLocation& loc = {}) = 0;
    virtual void error(const std::string& message, const SourceLocation& loc = {}) = 0;
    virtual void fatal(const std::string& message, const SourceLocation& loc = {}) = 0;
};

// 基础异常类
class CHTLException : public std::exception {
public:
    explicit CHTLException(const ErrorInfo& info) : errorInfo(info) {}
    
    const char* what() const noexcept override {
        return errorInfo.message.c_str();
    }
    
    const ErrorInfo& getErrorInfo() const { return errorInfo; }
    
protected:
    ErrorInfo errorInfo;
};

// 具体异常类型
class SyntaxError : public CHTLException {
public:
    SyntaxError(const std::string& message, const SourceLocation& loc)
        : CHTLException({ErrorLevel::Error, ErrorCategory::Syntax, message}) {
        errorInfo.location = loc;
    }
};

class SemanticError : public CHTLException {
public:
    SemanticError(const std::string& message, const SourceLocation& loc)
        : CHTLException({ErrorLevel::Error, ErrorCategory::Semantic, message}) {
        errorInfo.location = loc;
    }
};

class TypeError : public CHTLException {
public:
    TypeError(const std::string& message, const SourceLocation& loc)
        : CHTLException({ErrorLevel::Error, ErrorCategory::Type, message}) {
        errorInfo.location = loc;
    }
};

// 全局错误管理器
class ErrorManager {
public:
    static ErrorManager& getInstance();
    
    // 设置错误处理器
    void setHandler(std::shared_ptr<IErrorHandler> handler);
    
    // 获取错误报告器
    std::shared_ptr<IErrorReporter> getReporter();
    
    // 设置是否抛出异常
    void setThrowOnError(bool throwOnError) { throwOnError_ = throwOnError; }
    
private:
    ErrorManager() = default;
    std::shared_ptr<IErrorHandler> handler_;
    std::shared_ptr<IErrorReporter> reporter_;
    bool throwOnError_ = false;
};

// 便捷宏
#define CHTL_ERROR(msg, loc) \
    chtl::error::ErrorManager::getInstance().getReporter()->error(msg, loc)

#define CHTL_WARNING(msg, loc) \
    chtl::error::ErrorManager::getInstance().getReporter()->warning(msg, loc)

#define CHTL_THROW_IF(condition, ExceptionType, msg, loc) \
    if (condition) throw ExceptionType(msg, loc)

} // namespace error
} // namespace chtl

#endif // CHTL_ERROR_INTERFACE_H