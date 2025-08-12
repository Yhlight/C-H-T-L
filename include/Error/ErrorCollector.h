#ifndef CHTL_ERROR_COLLECTOR_H
#define CHTL_ERROR_COLLECTOR_H

#include "Error/ErrorHandler.h"
#include <memory>
#include <mutex>

namespace chtl {

// 线程安全的错误收集器
class ErrorCollector {
public:
    static ErrorCollector& getInstance() {
        static ErrorCollector instance;
        return instance;
    }
    
    // 设置错误处理器
    void setErrorHandler(std::shared_ptr<ErrorHandler> handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        errorHandler_ = handler;
    }
    
    // 报告错误（线程安全）
    void reportError(ErrorType type,
                    const std::string& message,
                    const ErrorContext& context) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (errorHandler_) {
            errorHandler_->reportError(type, message, context);
        }
    }
    
    void reportWarning(const std::string& message,
                      const ErrorContext& context) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (errorHandler_) {
            errorHandler_->reportWarning(message, context);
        }
    }
    
    // 便捷方法
    void syntaxError(const std::string& message, int line, int column) {
        ErrorContext ctx;
        ctx.line = line;
        ctx.column = column;
        reportError(ErrorType::SYNTAX_ERROR, message, ctx);
    }
    
    void semanticError(const std::string& message, int line, int column) {
        ErrorContext ctx;
        ctx.line = line;
        ctx.column = column;
        reportError(ErrorType::SEMANTIC_ERROR, message, ctx);
    }
    
    void runtimeError(const std::string& message) {
        ErrorContext ctx;
        reportError(ErrorType::RUNTIME_ERROR, message, ctx);
    }
    
    // 获取错误计数
    size_t getErrorCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return errorHandler_ ? errorHandler_->getErrors().size() : 0;
    }
    
    bool hasErrors() const {
        return getErrorCount() > 0;
    }
    
    // 清除错误
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (errorHandler_) {
            errorHandler_->clearErrors();
        }
    }
    
private:
    ErrorCollector() = default;
    ~ErrorCollector() = default;
    
    ErrorCollector(const ErrorCollector&) = delete;
    ErrorCollector& operator=(const ErrorCollector&) = delete;
    
    mutable std::mutex mutex_;
    std::shared_ptr<ErrorHandler> errorHandler_;
};

// 便捷宏
#define CHTL_SYNTAX_ERROR(msg, line, col) \
    chtl::ErrorCollector::getInstance().syntaxError(msg, line, col)

#define CHTL_SEMANTIC_ERROR(msg, line, col) \
    chtl::ErrorCollector::getInstance().semanticError(msg, line, col)

#define CHTL_RUNTIME_ERROR(msg) \
    chtl::ErrorCollector::getInstance().runtimeError(msg)

} // namespace chtl

#endif // CHTL_ERROR_COLLECTOR_H