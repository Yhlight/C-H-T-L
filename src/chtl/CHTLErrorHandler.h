#ifndef CHTL_ERROR_HANDLER_H
#define CHTL_ERROR_HANDLER_H

#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <functional>
#include <unordered_map>
#include <sstream>

namespace chtl {

// 错误级别
enum class ErrorLevel {
    Info,      // 信息
    Warning,   // 警告
    Error,     // 错误
    Fatal      // 致命错误
};

// 错误类型
enum class ErrorType {
    SyntaxError,       // 语法错误
    SemanticError,     // 语义错误
    TypeError,         // 类型错误
    ReferenceError,    // 引用错误
    ImportError,       // 导入错误
    CompileError,      // 编译错误
    RuntimeError,      // 运行时错误
    InternalError,     // 内部错误
    ConfigError,       // 配置错误
    IOError,           // I/O错误
    Unknown            // 未知错误
};

// 源代码位置
struct SourceLocation {
    std::string filename;
    int line;        // 1-based
    int column;      // 1-based
    int offset;      // 0-based字符偏移
    
    SourceLocation() : line(0), column(0), offset(0) {}
    SourceLocation(const std::string& file, int l, int c, int o = 0)
        : filename(file), line(l), column(c), offset(o) {}
    
    std::string toString() const;
};

// 错误信息
struct ErrorInfo {
    ErrorLevel level;
    ErrorType type;
    std::string message;
    std::string details;
    SourceLocation location;
    std::string errorCode;  // 如 CHTL001
    std::vector<std::string> suggestions;  // 修复建议
    
    ErrorInfo() : level(ErrorLevel::Error), type(ErrorType::Unknown) {}
};

// 错误上下文
struct ErrorContext {
    std::string sourceCode;         // 源代码片段
    int contextLinesBefore = 2;     // 显示错误前几行
    int contextLinesAfter = 2;      // 显示错误后几行
    bool showLineNumbers = true;    // 显示行号
    bool useColors = true;          // 使用颜色
};

// CHTL异常基类
class CHTLException : public std::exception {
public:
    CHTLException(const ErrorInfo& info) : errorInfo(info) {}
    
    const char* what() const noexcept override {
        if (cachedWhat.empty()) {
            cachedWhat = formatError();
        }
        return cachedWhat.c_str();
    }
    
    const ErrorInfo& getErrorInfo() const { return errorInfo; }
    
protected:
    ErrorInfo errorInfo;
    mutable std::string cachedWhat;
    
    virtual std::string formatError() const;
};

// 具体异常类
class SyntaxException : public CHTLException {
public:
    SyntaxException(const std::string& message, const SourceLocation& loc);
};

class SemanticException : public CHTLException {
public:
    SemanticException(const std::string& message, const SourceLocation& loc);
};

class TypeError : public CHTLException {
public:
    TypeError(const std::string& expected, const std::string& actual, 
             const SourceLocation& loc);
};

class ImportException : public CHTLException {
public:
    ImportException(const std::string& module, const std::string& reason,
                   const SourceLocation& loc);
};

// 错误收集器
class ErrorCollector {
public:
    using ErrorHandler = std::function<void(const ErrorInfo&)>;
    
    ErrorCollector();
    
    // 添加错误
    void addError(const ErrorInfo& error);
    void addError(ErrorLevel level, ErrorType type, const std::string& message,
                 const SourceLocation& location = SourceLocation());
    
    // 便捷方法
    void info(const std::string& message, const SourceLocation& loc = {});
    void warning(const std::string& message, const SourceLocation& loc = {});
    void error(const std::string& message, const SourceLocation& loc = {});
    void fatal(const std::string& message, const SourceLocation& loc = {});
    
    // 错误查询
    bool hasErrors() const;
    bool hasFatalErrors() const;
    bool hasWarnings() const;
    
    size_t getErrorCount() const;
    size_t getWarningCount() const;
    
    const std::vector<ErrorInfo>& getErrors() const { return errors; }
    std::vector<ErrorInfo> getErrorsByLevel(ErrorLevel level) const;
    std::vector<ErrorInfo> getErrorsByType(ErrorType type) const;
    
    // 清除错误
    void clear();
    
    // 设置错误处理器
    void setErrorHandler(ErrorHandler handler);
    
    // 错误限制
    void setMaxErrors(size_t max) { maxErrors = max; }
    bool isErrorLimitReached() const;
    
private:
    std::vector<ErrorInfo> errors;
    ErrorHandler errorHandler;
    size_t maxErrors = 100;
    
    void handleError(const ErrorInfo& error);
};

// 错误格式化器
class ErrorFormatter {
public:
    ErrorFormatter();
    
    // 格式化单个错误
    std::string format(const ErrorInfo& error, const ErrorContext& context = {});
    
    // 格式化错误列表
    std::string formatList(const std::vector<ErrorInfo>& errors, 
                          const ErrorContext& context = {});
    
    // 设置格式选项
    void setUseColors(bool use) { useColors = use; }
    void setShowSuggestions(bool show) { showSuggestions = show; }
    void setShowErrorCodes(bool show) { showErrorCodes = show; }
    
private:
    bool useColors = true;
    bool showSuggestions = true;
    bool showErrorCodes = true;
    
    // ANSI颜色代码
    struct Colors {
        static const char* reset;
        static const char* red;
        static const char* yellow;
        static const char* blue;
        static const char* green;
        static const char* bold;
        static const char* dim;
    };
    
    std::string formatLocation(const SourceLocation& loc);
    std::string formatCodeSnippet(const ErrorInfo& error, const ErrorContext& context);
    std::string highlightError(const std::string& line, int column, int length);
    std::string getLevelColor(ErrorLevel level);
    std::string getLevelString(ErrorLevel level);
};

// 错误恢复策略
class ErrorRecovery {
public:
    // 恢复点
    struct RecoveryPoint {
        std::string name;
        std::function<void()> recover;
    };
    
    // 注册恢复点
    void addRecoveryPoint(const std::string& name, std::function<void()> recover);
    
    // 尝试恢复
    bool tryRecover(const std::string& errorType);
    
    // 执行恢复策略
    void executeRecovery(const std::string& strategy);
    
private:
    std::unordered_map<std::string, std::vector<RecoveryPoint>> recoveryStrategies;
};

// 全局错误处理器
class GlobalErrorHandler {
public:
    static GlobalErrorHandler& getInstance();
    
    // 设置全局错误收集器
    void setErrorCollector(std::shared_ptr<ErrorCollector> collector);
    std::shared_ptr<ErrorCollector> getErrorCollector();
    
    // 报告错误
    void reportError(const ErrorInfo& error);
    void reportException(const CHTLException& e);
    
    // 设置未捕获异常处理器
    void setUncaughtExceptionHandler(std::function<void(const std::exception&)> handler);
    
    // 错误统计
    struct ErrorStats {
        size_t totalErrors = 0;
        size_t totalWarnings = 0;
        std::unordered_map<ErrorType, size_t> errorsByType;
        std::unordered_map<std::string, size_t> errorsByFile;
    };
    
    ErrorStats getStats() const { return stats; }
    
private:
    GlobalErrorHandler() = default;
    
    std::shared_ptr<ErrorCollector> errorCollector;
    std::function<void(const std::exception&)> uncaughtHandler;
    ErrorStats stats;
    
    void updateStats(const ErrorInfo& error);
};

// 错误生成辅助函数
namespace ErrorHelpers {
    // 生成错误代码
    std::string generateErrorCode(ErrorType type, int number);
    
    // 获取相似标识符（用于拼写错误建议）
    std::vector<std::string> findSimilarIdentifiers(const std::string& identifier,
                                                   const std::vector<std::string>& candidates);
    
    // 生成修复建议
    std::vector<std::string> generateSuggestions(ErrorType type, 
                                                const std::string& context);
    
    // 获取文件片段
    std::string getFileSnippet(const std::string& filename, 
                              int startLine, int endLine);
}

// 断言宏
#define CHTL_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            throw chtl::CHTLException({ \
                chtl::ErrorLevel::Fatal, \
                chtl::ErrorType::InternalError, \
                std::string("Assertion failed: ") + (message), \
                #condition, \
                chtl::SourceLocation(__FILE__, __LINE__, 0), \
                "CHTL_ASSERT", \
                {} \
            }); \
        } \
    } while(0)

} // namespace chtl

#endif // CHTL_ERROR_HANDLER_H