#ifndef CHTL_ERROR_HANDLER_H
#define CHTL_ERROR_HANDLER_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Error/ErrorTypes.h"

namespace chtl {

// 错误上下文
struct ErrorContext {
    std::string fileName;
    int line;
    int column;
    std::string sourceCode;
    std::string contextLines;  // 错误前后的代码行
};

// 错误修复建议
struct ErrorFix {
    std::string description;
    std::string replacement;
    int startLine;
    int startColumn;
    int endLine;
    int endColumn;
};

// 错误详情
class ErrorDetail {
public:
    ErrorDetail() = default;  // 默认构造函数
    ErrorDetail(ErrorType type, 
                const std::string& message,
                const ErrorContext& context);
    
    ErrorType getType() const { return type_; }
    const std::string& getMessage() const { return message_; }
    const ErrorContext& getContext() const { return context_; }
    ErrorSeverity getSeverity() const { return severity_; }
    const std::string& getCode() const { return code_; }
    const std::vector<ErrorFix>& getFixes() const { return fixes_; }
    
    void setSeverity(ErrorSeverity severity) { severity_ = severity; }
    void setCode(const std::string& code) { code_ = code; }
    void addFix(const ErrorFix& fix) { fixes_.push_back(fix); }
    
    // 格式化错误信息
    std::string format(bool useColor = true) const;
    std::string formatJson() const;
    
private:
    ErrorType type_;
    std::string message_;
    ErrorContext context_;
    ErrorSeverity severity_;
    std::string code_;  // 错误代码 (如 CHTL001)
    std::vector<ErrorFix> fixes_;
};

// 错误处理器
class ErrorHandler {
public:
    using ErrorCallback = std::function<void(const ErrorDetail&)>;
    
    ErrorHandler();
    ~ErrorHandler() = default;
    
    // 报告错误
    void reportError(ErrorType type,
                    const std::string& message,
                    const ErrorContext& context);
    
    void reportWarning(const std::string& message,
                      const ErrorContext& context);
    
    void reportInfo(const std::string& message,
                   const ErrorContext& context);
    
    // 批量错误处理
    void beginBatch();
    void endBatch();
    bool isInBatch() const { return batchMode_; }
    
    // 错误查询
    bool hasErrors() const;
    bool hasWarnings() const;
    size_t getErrorCount() const;
    size_t getWarningCount() const;
    const std::vector<ErrorDetail>& getErrors() const { return errors_; }
    const std::vector<ErrorDetail>& getWarnings() const { return warnings_; }
    
    // 清除错误
    void clearErrors();
    void clearWarnings();
    void clearAll();
    
    // 错误回调
    void setErrorCallback(ErrorCallback callback) { errorCallback_ = callback; }
    void setWarningCallback(ErrorCallback callback) { warningCallback_ = callback; }
    
    // 错误抑制
    void suppressError(const std::string& code);
    void unsuppressError(const std::string& code);
    bool isErrorSuppressed(const std::string& code) const;
    
    // 错误限制
    void setMaxErrors(size_t max) { maxErrors_ = max; }
    void setMaxWarnings(size_t max) { maxWarnings_ = max; }
    
    // 格式化输出
    std::string formatAllErrors(bool useColor = true) const;
    std::string formatSummary() const;
    
    // 错误恢复
    void pushRecoveryPoint();
    void popRecoveryPoint();
    void recoverToLastPoint();
    
private:
    std::vector<ErrorDetail> errors_;
    std::vector<ErrorDetail> warnings_;
    std::vector<ErrorDetail> infos_;
    
    bool batchMode_ = false;
    std::vector<ErrorDetail> batchErrors_;
    std::vector<ErrorDetail> batchWarnings_;
    
    ErrorCallback errorCallback_;
    ErrorCallback warningCallback_;
    
    std::unordered_map<std::string, bool> suppressedErrors_;
    size_t maxErrors_ = 100;
    size_t maxWarnings_ = 100;
    
    // 错误恢复点
    struct RecoveryPoint {
        size_t errorCount;
        size_t warningCount;
    };
    std::vector<RecoveryPoint> recoveryPoints_;
    
    // 辅助方法
    std::string getErrorCode(ErrorType type) const;
    ErrorSeverity getDefaultSeverity(ErrorType type) const;
    std::vector<ErrorFix> generateFixes(ErrorType type, const ErrorContext& context) const;
};

// 全局错误处理器
class GlobalErrorHandler {
public:
    static ErrorHandler& getInstance();
    
private:
    GlobalErrorHandler() = default;
    static std::unique_ptr<ErrorHandler> instance_;
};

// 错误报告宏
#define REPORT_ERROR(type, message, context) \
    GlobalErrorHandler::getInstance().reportError(type, message, context)

#define REPORT_WARNING(message, context) \
    GlobalErrorHandler::getInstance().reportWarning(message, context)

#define REPORT_INFO(message, context) \
    GlobalErrorHandler::getInstance().reportInfo(message, context)

// 错误恢复助手
class ErrorRecoveryGuard {
public:
    explicit ErrorRecoveryGuard(ErrorHandler& handler);
    ~ErrorRecoveryGuard();
    
    void commit();
    
private:
    ErrorHandler& handler_;
    bool committed_ = false;
};

} // namespace chtl

#endif // CHTL_ERROR_HANDLER_H