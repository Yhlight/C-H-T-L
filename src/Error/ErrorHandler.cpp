#include "Error/ErrorHandler.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

namespace chtl {

// ANSI颜色代码
namespace Color {
    const char* Reset = "\033[0m";
    const char* Red = "\033[31m";
    const char* Yellow = "\033[33m";
    const char* Blue = "\033[34m";
    const char* Cyan = "\033[36m";
    const char* White = "\033[37m";
    const char* Bold = "\033[1m";
    const char* Dim = "\033[2m";
}

// ErrorDetail 实现
ErrorDetail::ErrorDetail(ErrorType type, 
                        const std::string& message,
                        const ErrorContext& context)
    : type_(type)
    , message_(message)
    , context_(context) {
    // 设置默认严重程度
    ErrorCategory category = getErrorCategory(type);
    switch (category) {
        case ErrorCategory::LEXICAL:
        case ErrorCategory::SYNTACTIC:
        case ErrorCategory::SEMANTIC:
        case ErrorCategory::TYPE:
            severity_ = ErrorSeverity::ERROR;
            break;
        case ErrorCategory::MODULE:
        case ErrorCategory::GENERATOR:
            severity_ = ErrorSeverity::WARNING;
            break;
        case ErrorCategory::RUNTIME:
        case ErrorCategory::SYSTEM:
            severity_ = ErrorSeverity::FATAL;
            break;
        default:
            severity_ = ErrorSeverity::ERROR;
    }
}

std::string ErrorDetail::format(bool useColor) const {
    std::stringstream ss;
    
    // 错误级别颜色
    const char* severityColor = "";
    if (useColor) {
        switch (severity_) {
            case ErrorSeverity::INFO: severityColor = Color::Cyan; break;
            case ErrorSeverity::WARNING: severityColor = Color::Yellow; break;
            case ErrorSeverity::ERROR: severityColor = Color::Red; break;
            case ErrorSeverity::FATAL: severityColor = Color::Red; break;
        }
    }
    
    // 错误头部
    ss << severityColor << Color::Bold 
       << errorSeverityToString(severity_) 
       << Color::Reset;
    
    if (!code_.empty()) {
        ss << " [" << code_ << "]";
    }
    
    ss << ": " << message_ << "\n";
    
    // 文件位置
    if (!context_.fileName.empty()) {
        ss << Color::Dim << " --> " << Color::Reset
           << context_.fileName << ":" 
           << context_.line << ":" 
           << context_.column << "\n";
    }
    
    // 代码上下文
    if (!context_.sourceCode.empty()) {
        ss << "\n";
        
        // 显示错误行
        ss << std::setw(4) << context_.line << " | " 
           << context_.sourceCode << "\n";
        
        // 错误指示器
        ss << "     | ";
        for (int i = 0; i < context_.column - 1; ++i) {
            ss << " ";
        }
        ss << severityColor << "^";
        
        // 如果有多个字符，画下划线
        if (!message_.empty()) {
            int errorLength = std::min(10, static_cast<int>(context_.sourceCode.length() - context_.column + 1));
            for (int i = 1; i < errorLength; ++i) {
                ss << "~";
            }
        }
        ss << Color::Reset << "\n";
    }
    
    // 修复建议
    if (!fixes_.empty()) {
        ss << "\n" << Color::Cyan << "Suggestions:" << Color::Reset << "\n";
        for (size_t i = 0; i < fixes_.size(); ++i) {
            ss << "  " << (i + 1) << ". " << fixes_[i].description;
            if (!fixes_[i].replacement.empty()) {
                ss << "\n     Replace with: " << Color::Bold 
                   << fixes_[i].replacement << Color::Reset;
            }
            ss << "\n";
        }
    }
    
    return ss.str();
}

std::string ErrorDetail::formatJson() const {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"type\": \"" << errorTypeToString(type_) << "\",\n";
    ss << "  \"severity\": \"" << errorSeverityToString(severity_) << "\",\n";
    ss << "  \"message\": \"" << message_ << "\",\n";
    ss << "  \"code\": \"" << code_ << "\",\n";
    ss << "  \"location\": {\n";
    ss << "    \"file\": \"" << context_.fileName << "\",\n";
    ss << "    \"line\": " << context_.line << ",\n";
    ss << "    \"column\": " << context_.column << "\n";
    ss << "  }";
    
    if (!fixes_.empty()) {
        ss << ",\n  \"fixes\": [\n";
        for (size_t i = 0; i < fixes_.size(); ++i) {
            if (i > 0) ss << ",\n";
            ss << "    {\n";
            ss << "      \"description\": \"" << fixes_[i].description << "\",\n";
            ss << "      \"replacement\": \"" << fixes_[i].replacement << "\"\n";
            ss << "    }";
        }
        ss << "\n  ]";
    }
    
    ss << "\n}";
    return ss.str();
}

// ErrorHandler 实现
ErrorHandler::ErrorHandler() {
}

void ErrorHandler::reportError(ErrorType type,
                              const std::string& message,
                              const ErrorContext& context) {
    if (errors_.size() >= maxErrors_) {
        return;  // 达到错误上限
    }
    
    ErrorDetail error(type, message, context);
    error.setCode(getErrorCode(type));
    
    // 生成修复建议
    auto fixes = generateFixes(type, context);
    for (const auto& fix : fixes) {
        error.addFix(fix);
    }
    
    // 检查是否被抑制
    if (isErrorSuppressed(error.getCode())) {
        return;
    }
    
    if (batchMode_) {
        batchErrors_.push_back(error);
    } else {
        errors_.push_back(error);
        if (errorCallback_) {
            errorCallback_(error);
        }
    }
}

void ErrorHandler::reportWarning(const std::string& message,
                                const ErrorContext& context) {
    if (warnings_.size() >= maxWarnings_) {
        return;
    }
    
    ErrorDetail warning(ErrorType::SEMANTIC_UNUSED_VARIABLE, message, context);
    warning.setSeverity(ErrorSeverity::WARNING);
    
    if (batchMode_) {
        batchWarnings_.push_back(warning);
    } else {
        warnings_.push_back(warning);
        if (warningCallback_) {
            warningCallback_(warning);
        }
    }
}

void ErrorHandler::reportInfo(const std::string& message,
                             const ErrorContext& context) {
    ErrorDetail info(ErrorType::SEMANTIC_UNUSED_VARIABLE, message, context);
    info.setSeverity(ErrorSeverity::INFO);
    infos_.push_back(info);
}

void ErrorHandler::beginBatch() {
    batchMode_ = true;
    batchErrors_.clear();
    batchWarnings_.clear();
}

void ErrorHandler::endBatch() {
    if (!batchMode_) return;
    
    // 合并批量错误
    errors_.insert(errors_.end(), batchErrors_.begin(), batchErrors_.end());
    warnings_.insert(warnings_.end(), batchWarnings_.begin(), batchWarnings_.end());
    
    // 触发回调
    if (errorCallback_) {
        for (const auto& error : batchErrors_) {
            errorCallback_(error);
        }
    }
    
    if (warningCallback_) {
        for (const auto& warning : batchWarnings_) {
            warningCallback_(warning);
        }
    }
    
    batchMode_ = false;
    batchErrors_.clear();
    batchWarnings_.clear();
}

bool ErrorHandler::hasErrors() const {
    return !errors_.empty() || (batchMode_ && !batchErrors_.empty());
}

bool ErrorHandler::hasWarnings() const {
    return !warnings_.empty() || (batchMode_ && !batchWarnings_.empty());
}

size_t ErrorHandler::getErrorCount() const {
    return errors_.size() + (batchMode_ ? batchErrors_.size() : 0);
}

size_t ErrorHandler::getWarningCount() const {
    return warnings_.size() + (batchMode_ ? batchWarnings_.size() : 0);
}

void ErrorHandler::clearErrors() {
    errors_.clear();
    batchErrors_.clear();
}

void ErrorHandler::clearWarnings() {
    warnings_.clear();
    batchWarnings_.clear();
}

void ErrorHandler::clearAll() {
    clearErrors();
    clearWarnings();
    infos_.clear();
}

void ErrorHandler::suppressError(const std::string& code) {
    suppressedErrors_[code] = true;
}

void ErrorHandler::unsuppressError(const std::string& code) {
    suppressedErrors_.erase(code);
}

bool ErrorHandler::isErrorSuppressed(const std::string& code) const {
    return suppressedErrors_.find(code) != suppressedErrors_.end();
}

std::string ErrorHandler::formatAllErrors(bool useColor) const {
    std::stringstream ss;
    
    // 错误
    for (const auto& error : errors_) {
        ss << error.format(useColor) << "\n";
    }
    
    // 警告
    for (const auto& warning : warnings_) {
        ss << warning.format(useColor) << "\n";
    }
    
    return ss.str();
}

std::string ErrorHandler::formatSummary() const {
    std::stringstream ss;
    
    size_t errorCount = getErrorCount();
    size_t warningCount = getWarningCount();
    
    if (errorCount == 0 && warningCount == 0) {
        ss << Color::Cyan << "✓ No errors or warnings" << Color::Reset;
    } else {
        if (errorCount > 0) {
            ss << Color::Red << "✗ " << errorCount << " error" 
               << (errorCount > 1 ? "s" : "") << Color::Reset;
        }
        
        if (warningCount > 0) {
            if (errorCount > 0) ss << ", ";
            ss << Color::Yellow << warningCount << " warning"
               << (warningCount > 1 ? "s" : "") << Color::Reset;
        }
    }
    
    return ss.str();
}

void ErrorHandler::pushRecoveryPoint() {
    recoveryPoints_.push_back({errors_.size(), warnings_.size()});
}

void ErrorHandler::popRecoveryPoint() {
    if (!recoveryPoints_.empty()) {
        recoveryPoints_.pop_back();
    }
}

void ErrorHandler::recoverToLastPoint() {
    if (recoveryPoints_.empty()) return;
    
    const auto& point = recoveryPoints_.back();
    errors_.resize(point.errorCount);
    warnings_.resize(point.warningCount);
    recoveryPoints_.pop_back();
}

std::string ErrorHandler::getErrorCode(ErrorType type) const {
    std::stringstream ss;
    ss << "CHTL" << std::setfill('0') << std::setw(4) << static_cast<int>(type);
    return ss.str();
}

ErrorSeverity ErrorHandler::getDefaultSeverity(ErrorType type) const {
    ErrorCategory category = getErrorCategory(type);
    switch (category) {
        case ErrorCategory::LEXICAL:
        case ErrorCategory::SYNTACTIC:
            return ErrorSeverity::ERROR;
        case ErrorCategory::SEMANTIC:
        case ErrorCategory::TYPE:
            return ErrorSeverity::ERROR;
        case ErrorCategory::MODULE:
            return ErrorSeverity::WARNING;
        case ErrorCategory::RUNTIME:
        case ErrorCategory::SYSTEM:
            return ErrorSeverity::FATAL;
        default:
            return ErrorSeverity::ERROR;
    }
}

std::vector<ErrorFix> ErrorHandler::generateFixes(ErrorType type, const ErrorContext& context) const {
    std::vector<ErrorFix> fixes;
    
    switch (type) {
        case ErrorType::LEXER_UNTERMINATED_STRING:
            fixes.push_back({
                "Add closing quote",
                "\"",
                context.line,
                static_cast<int>(context.sourceCode.length()),
                context.line,
                static_cast<int>(context.sourceCode.length())
            });
            break;
            
        case ErrorType::PARSER_UNCLOSED_BLOCK:
            fixes.push_back({
                "Add closing brace",
                "}",
                context.line,
                static_cast<int>(context.sourceCode.length()),
                context.line,
                static_cast<int>(context.sourceCode.length())
            });
            break;
            
        case ErrorType::PARSER_EXPECTED_TOKEN:
            // 生成通用的token添加建议
            fixes.push_back({
                "Add expected token",
                "<token>",
                context.line,
                context.column,
                context.line,
                context.column
            });
            break;
            
        default:
            break;
    }
    
    return fixes;
}

// GlobalErrorHandler 实现
std::unique_ptr<ErrorHandler> GlobalErrorHandler::instance_;

ErrorHandler& GlobalErrorHandler::getInstance() {
    if (!instance_) {
        instance_ = std::make_unique<ErrorHandler>();
    }
    return *instance_;
}

// ErrorRecoveryGuard 实现
ErrorRecoveryGuard::ErrorRecoveryGuard(ErrorHandler& handler)
    : handler_(handler) {
    handler_.pushRecoveryPoint();
}

ErrorRecoveryGuard::~ErrorRecoveryGuard() {
    if (!committed_) {
        handler_.recoverToLastPoint();
    }
}

void ErrorRecoveryGuard::commit() {
    handler_.popRecoveryPoint();
    committed_ = true;
}

// 错误类型字符串转换
const char* errorTypeToString(ErrorType type) {
    switch (type) {
        case ErrorType::LEXER_UNKNOWN_CHARACTER: return "LEXER_UNKNOWN_CHARACTER";
        case ErrorType::LEXER_UNTERMINATED_STRING: return "LEXER_UNTERMINATED_STRING";
        case ErrorType::LEXER_UNTERMINATED_COMMENT: return "LEXER_UNTERMINATED_COMMENT";
        case ErrorType::LEXER_INVALID_NUMBER: return "LEXER_INVALID_NUMBER";
        case ErrorType::LEXER_INVALID_ESCAPE_SEQUENCE: return "LEXER_INVALID_ESCAPE_SEQUENCE";
        case ErrorType::LEXER_UNEXPECTED_CHARACTER: return "LEXER_UNEXPECTED_CHARACTER";
        
        case ErrorType::PARSER_UNEXPECTED_TOKEN: return "PARSER_UNEXPECTED_TOKEN";
        case ErrorType::PARSER_EXPECTED_TOKEN: return "PARSER_EXPECTED_TOKEN";
        case ErrorType::PARSER_UNCLOSED_BLOCK: return "PARSER_UNCLOSED_BLOCK";
        case ErrorType::PARSER_INVALID_SYNTAX: return "PARSER_INVALID_SYNTAX";
        case ErrorType::PARSER_DUPLICATE_ATTRIBUTE: return "PARSER_DUPLICATE_ATTRIBUTE";
        case ErrorType::PARSER_MISSING_REQUIRED_ATTRIBUTE: return "PARSER_MISSING_REQUIRED_ATTRIBUTE";
        case ErrorType::PARSER_INVALID_IMPORT: return "PARSER_INVALID_IMPORT";
        case ErrorType::PARSER_INVALID_EXPORT: return "PARSER_INVALID_EXPORT";
        case ErrorType::PARSER_INVALID_IDENTIFIER: return "PARSER_INVALID_IDENTIFIER";
        case ErrorType::PARSER_UNEXPECTED_EOF: return "PARSER_UNEXPECTED_EOF";
        
        // ... 其他类型
        default: return "UNKNOWN_ERROR";
    }
}

const char* errorSeverityToString(ErrorSeverity severity) {
    switch (severity) {
        case ErrorSeverity::INFO: return "INFO";
        case ErrorSeverity::WARNING: return "WARNING";
        case ErrorSeverity::ERROR: return "ERROR";
        case ErrorSeverity::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

const char* errorCategoryToString(ErrorCategory category) {
    switch (category) {
        case ErrorCategory::LEXICAL: return "Lexical";
        case ErrorCategory::SYNTACTIC: return "Syntactic";
        case ErrorCategory::SEMANTIC: return "Semantic";
        case ErrorCategory::TYPE: return "Type";
        case ErrorCategory::MODULE: return "Module";
        case ErrorCategory::RUNTIME: return "Runtime";
        case ErrorCategory::GENERATOR: return "Generator";
        case ErrorCategory::CONFIG: return "Configuration";
        case ErrorCategory::SYSTEM: return "System";
        default: return "Unknown";
    }
}

} // namespace chtl