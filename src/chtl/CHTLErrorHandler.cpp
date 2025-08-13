#include "CHTLErrorHandler.h"
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cmath>

namespace chtl {

// 颜色常量定义
const char* ErrorFormatter::Colors::reset = "\033[0m";
const char* ErrorFormatter::Colors::red = "\033[31m";
const char* ErrorFormatter::Colors::yellow = "\033[33m";
const char* ErrorFormatter::Colors::blue = "\033[34m";
const char* ErrorFormatter::Colors::green = "\033[32m";
const char* ErrorFormatter::Colors::bold = "\033[1m";
const char* ErrorFormatter::Colors::dim = "\033[2m";

// SourceLocation 实现
std::string SourceLocation::toString() const {
    std::stringstream ss;
    if (!filename.empty()) {
        ss << filename;
        if (line > 0) {
            ss << ":" << line;
            if (column > 0) {
                ss << ":" << column;
            }
        }
    }
    return ss.str();
}

// CHTLException 实现
std::string CHTLException::formatError() const {
    ErrorFormatter formatter;
    return formatter.format(errorInfo);
}

// 具体异常类实现
SyntaxException::SyntaxException(const std::string& message, const SourceLocation& loc) 
    : CHTLException({
        ErrorLevel::Error,
        ErrorType::SyntaxError,
        message,
        "",
        loc,
        ErrorHelpers::generateErrorCode(ErrorType::SyntaxError, 1),
        {}
    }) {}

SemanticException::SemanticException(const std::string& message, const SourceLocation& loc)
    : CHTLException({
        ErrorLevel::Error,
        ErrorType::SemanticError,
        message,
        "",
        loc,
        ErrorHelpers::generateErrorCode(ErrorType::SemanticError, 1),
        {}
    }) {}

TypeError::TypeError(const std::string& expected, const std::string& actual, 
                   const SourceLocation& loc)
    : CHTLException({
        ErrorLevel::Error,
        ErrorType::TypeError,
        "Type mismatch: expected '" + expected + "', got '" + actual + "'",
        "",
        loc,
        ErrorHelpers::generateErrorCode(ErrorType::TypeError, 1),
        {"Check the type of the expression", "Ensure type compatibility"}
    }) {}

ImportException::ImportException(const std::string& module, const std::string& reason,
                               const SourceLocation& loc)
    : CHTLException({
        ErrorLevel::Error,
        ErrorType::ImportError,
        "Cannot import module '" + module + "': " + reason,
        "",
        loc,
        ErrorHelpers::generateErrorCode(ErrorType::ImportError, 1),
        {"Check if the module exists", "Verify the module path"}
    }) {}

// ErrorCollector 实现
ErrorCollector::ErrorCollector() {}

void ErrorCollector::addError(const ErrorInfo& error) {
    if (isErrorLimitReached()) {
        return;
    }
    
    errors.push_back(error);
    handleError(error);
}

void ErrorCollector::addError(ErrorLevel level, ErrorType type, const std::string& message,
                            const SourceLocation& location) {
    ErrorInfo error;
    error.level = level;
    error.type = type;
    error.message = message;
    error.location = location;
    error.errorCode = ErrorHelpers::generateErrorCode(type, errors.size() + 1);
    
    addError(error);
}

void ErrorCollector::info(const std::string& message, const SourceLocation& loc) {
    addError(ErrorLevel::Info, ErrorType::Unknown, message, loc);
}

void ErrorCollector::warning(const std::string& message, const SourceLocation& loc) {
    addError(ErrorLevel::Warning, ErrorType::Unknown, message, loc);
}

void ErrorCollector::error(const std::string& message, const SourceLocation& loc) {
    addError(ErrorLevel::Error, ErrorType::Unknown, message, loc);
}

void ErrorCollector::fatal(const std::string& message, const SourceLocation& loc) {
    addError(ErrorLevel::Fatal, ErrorType::Unknown, message, loc);
}

bool ErrorCollector::hasErrors() const {
    return std::any_of(errors.begin(), errors.end(),
                      [](const ErrorInfo& e) { 
                          return e.level == ErrorLevel::Error || 
                                 e.level == ErrorLevel::Fatal; 
                      });
}

bool ErrorCollector::hasFatalErrors() const {
    return std::any_of(errors.begin(), errors.end(),
                      [](const ErrorInfo& e) { return e.level == ErrorLevel::Fatal; });
}

bool ErrorCollector::hasWarnings() const {
    return std::any_of(errors.begin(), errors.end(),
                      [](const ErrorInfo& e) { return e.level == ErrorLevel::Warning; });
}

size_t ErrorCollector::getErrorCount() const {
    return std::count_if(errors.begin(), errors.end(),
                        [](const ErrorInfo& e) { 
                            return e.level == ErrorLevel::Error || 
                                   e.level == ErrorLevel::Fatal; 
                        });
}

size_t ErrorCollector::getWarningCount() const {
    return std::count_if(errors.begin(), errors.end(),
                        [](const ErrorInfo& e) { return e.level == ErrorLevel::Warning; });
}

std::vector<ErrorInfo> ErrorCollector::getErrorsByLevel(ErrorLevel level) const {
    std::vector<ErrorInfo> result;
    std::copy_if(errors.begin(), errors.end(), std::back_inserter(result),
                [level](const ErrorInfo& e) { return e.level == level; });
    return result;
}

std::vector<ErrorInfo> ErrorCollector::getErrorsByType(ErrorType type) const {
    std::vector<ErrorInfo> result;
    std::copy_if(errors.begin(), errors.end(), std::back_inserter(result),
                [type](const ErrorInfo& e) { return e.type == type; });
    return result;
}

void ErrorCollector::clear() {
    errors.clear();
}

void ErrorCollector::setErrorHandler(ErrorHandler handler) {
    errorHandler = handler;
}

bool ErrorCollector::isErrorLimitReached() const {
    return getErrorCount() >= maxErrors;
}

void ErrorCollector::handleError(const ErrorInfo& error) {
    if (errorHandler) {
        errorHandler(error);
    }
}

// ErrorFormatter 实现
ErrorFormatter::ErrorFormatter() {}

std::string ErrorFormatter::format(const ErrorInfo& error, const ErrorContext& context) {
    std::stringstream ss;
    
    // 错误级别和位置
    if (useColors) {
        ss << getLevelColor(error.level) << Colors::bold;
    }
    
    ss << getLevelString(error.level);
    
    if (showErrorCodes && !error.errorCode.empty()) {
        ss << "[" << error.errorCode << "]";
    }
    
    if (useColors) {
        ss << Colors::reset << Colors::bold;
    }
    
    ss << ": " << error.message;
    
    if (useColors) {
        ss << Colors::reset;
    }
    
    ss << "\n";
    
    // 位置信息
    if (!error.location.filename.empty()) {
        if (useColors) {
            ss << Colors::dim;
        }
        ss << " --> " << formatLocation(error.location) << "\n";
        if (useColors) {
            ss << Colors::reset;
        }
    }
    
    // 代码片段
    if (!context.sourceCode.empty()) {
        ss << formatCodeSnippet(error, context);
    }
    
    // 详细信息
    if (!error.details.empty()) {
        ss << "\n" << error.details << "\n";
    }
    
    // 建议
    if (showSuggestions && !error.suggestions.empty()) {
        if (useColors) {
            ss << Colors::green;
        }
        ss << "\nSuggestions:\n";
        for (const auto& suggestion : error.suggestions) {
            ss << "  • " << suggestion << "\n";
        }
        if (useColors) {
            ss << Colors::reset;
        }
    }
    
    return ss.str();
}

std::string ErrorFormatter::formatList(const std::vector<ErrorInfo>& errors,
                                     const ErrorContext& context) {
    std::stringstream ss;
    
    // 统计
    size_t errorCount = 0, warningCount = 0;
    for (const auto& error : errors) {
        if (error.level == ErrorLevel::Error || error.level == ErrorLevel::Fatal) {
            errorCount++;
        } else if (error.level == ErrorLevel::Warning) {
            warningCount++;
        }
    }
    
    // 格式化每个错误
    for (const auto& error : errors) {
        ss << format(error, context) << "\n";
    }
    
    // 总结
    if (useColors) {
        ss << Colors::bold;
    }
    
    if (errorCount > 0) {
        ss << "Found " << errorCount << " error" << (errorCount > 1 ? "s" : "");
        if (warningCount > 0) {
            ss << " and " << warningCount << " warning" << (warningCount > 1 ? "s" : "");
        }
    } else if (warningCount > 0) {
        ss << "Found " << warningCount << " warning" << (warningCount > 1 ? "s" : "");
    }
    
    if (useColors) {
        ss << Colors::reset;
    }
    
    ss << "\n";
    
    return ss.str();
}

std::string ErrorFormatter::formatLocation(const SourceLocation& loc) {
    return loc.toString();
}

std::string ErrorFormatter::formatCodeSnippet(const ErrorInfo& error, 
                                            const ErrorContext& context) {
    if (context.sourceCode.empty() || error.location.line <= 0) {
        return "";
    }
    
    std::stringstream ss;
    std::istringstream stream(context.sourceCode);
    std::string line;
    int lineNum = 1;
    
    // 计算行号宽度
    int totalLines = std::count(context.sourceCode.begin(), context.sourceCode.end(), '\n') + 1;
    int lineNumWidth = std::to_string(totalLines).length();
    
    // 定位到错误行附近
    int startLine = std::max(1, error.location.line - context.contextLinesBefore);
    int endLine = error.location.line + context.contextLinesAfter;
    
    while (std::getline(stream, line)) {
        if (lineNum >= startLine && lineNum <= endLine) {
            // 行号
            if (context.showLineNumbers) {
                if (useColors) {
                    ss << Colors::dim;
                }
                ss << std::setw(lineNumWidth) << lineNum << " | ";
                if (useColors) {
                    ss << Colors::reset;
                }
            }
            
            // 代码行
            if (lineNum == error.location.line) {
                // 高亮错误行
                ss << highlightError(line, error.location.column, 1);
            } else {
                ss << line;
            }
            ss << "\n";
            
            // 错误指示器
            if (lineNum == error.location.line && error.location.column > 0) {
                if (context.showLineNumbers) {
                    ss << std::string(lineNumWidth + 3, ' ');
                }
                
                if (useColors) {
                    ss << Colors::red << Colors::bold;
                }
                
                ss << std::string(error.location.column - 1, ' ') << "^";
                
                if (useColors) {
                    ss << Colors::reset;
                }
                ss << "\n";
            }
        }
        
        lineNum++;
        if (lineNum > endLine) {
            break;
        }
    }
    
    return ss.str();
}

std::string ErrorFormatter::highlightError(const std::string& line, int column, int length) {
    if (column <= 0 || column > line.length()) {
        return line;
    }
    
    std::stringstream ss;
    
    // 错误位置前的部分
    ss << line.substr(0, column - 1);
    
    // 错误部分
    if (useColors) {
        ss << Colors::red << Colors::bold;
    }
    
    int endPos = std::min((int)line.length(), column - 1 + length);
    ss << line.substr(column - 1, endPos - (column - 1));
    
    if (useColors) {
        ss << Colors::reset;
    }
    
    // 错误位置后的部分
    if (endPos < line.length()) {
        ss << line.substr(endPos);
    }
    
    return ss.str();
}

std::string ErrorFormatter::getLevelColor(ErrorLevel level) {
    switch (level) {
        case ErrorLevel::Info:
            return Colors::blue;
        case ErrorLevel::Warning:
            return Colors::yellow;
        case ErrorLevel::Error:
            return Colors::red;
        case ErrorLevel::Fatal:
            return std::string(Colors::red) + Colors::bold;
        default:
            return "";
    }
}

std::string ErrorFormatter::getLevelString(ErrorLevel level) {
    switch (level) {
        case ErrorLevel::Info:
            return "info";
        case ErrorLevel::Warning:
            return "warning";
        case ErrorLevel::Error:
            return "error";
        case ErrorLevel::Fatal:
            return "fatal error";
        default:
            return "unknown";
    }
}

// ErrorRecovery 实现
void ErrorRecovery::addRecoveryPoint(const std::string& name, std::function<void()> recover) {
    RecoveryPoint point{name, recover};
    recoveryStrategies[name].push_back(point);
}

bool ErrorRecovery::tryRecover(const std::string& errorType) {
    auto it = recoveryStrategies.find(errorType);
    if (it != recoveryStrategies.end() && !it->second.empty()) {
        executeRecovery(errorType);
        return true;
    }
    return false;
}

void ErrorRecovery::executeRecovery(const std::string& strategy) {
    auto it = recoveryStrategies.find(strategy);
    if (it != recoveryStrategies.end()) {
        for (const auto& point : it->second) {
            if (point.recover) {
                point.recover();
            }
        }
    }
}

// GlobalErrorHandler 实现
GlobalErrorHandler& GlobalErrorHandler::getInstance() {
    static GlobalErrorHandler instance;
    return instance;
}

void GlobalErrorHandler::setErrorCollector(std::shared_ptr<ErrorCollector> collector) {
    errorCollector = collector;
}

std::shared_ptr<ErrorCollector> GlobalErrorHandler::getErrorCollector() {
    if (!errorCollector) {
        errorCollector = std::make_shared<ErrorCollector>();
    }
    return errorCollector;
}

void GlobalErrorHandler::reportError(const ErrorInfo& error) {
    if (errorCollector) {
        errorCollector->addError(error);
    }
    updateStats(error);
}

void GlobalErrorHandler::reportException(const CHTLException& e) {
    reportError(e.getErrorInfo());
}

void GlobalErrorHandler::setUncaughtExceptionHandler(
    std::function<void(const std::exception&)> handler) {
    uncaughtHandler = handler;
}

void GlobalErrorHandler::updateStats(const ErrorInfo& error) {
    if (error.level == ErrorLevel::Error || error.level == ErrorLevel::Fatal) {
        stats.totalErrors++;
    } else if (error.level == ErrorLevel::Warning) {
        stats.totalWarnings++;
    }
    
    stats.errorsByType[error.type]++;
    
    if (!error.location.filename.empty()) {
        stats.errorsByFile[error.location.filename]++;
    }
}

// ErrorHelpers 实现
namespace ErrorHelpers {

std::string generateErrorCode(ErrorType type, int number) {
    std::string prefix;
    switch (type) {
        case ErrorType::SyntaxError:
            prefix = "SYN";
            break;
        case ErrorType::SemanticError:
            prefix = "SEM";
            break;
        case ErrorType::TypeError:
            prefix = "TYP";
            break;
        case ErrorType::ReferenceError:
            prefix = "REF";
            break;
        case ErrorType::ImportError:
            prefix = "IMP";
            break;
        case ErrorType::CompileError:
            prefix = "CMP";
            break;
        case ErrorType::RuntimeError:
            prefix = "RUN";
            break;
        case ErrorType::InternalError:
            prefix = "INT";
            break;
        case ErrorType::ConfigError:
            prefix = "CFG";
            break;
        case ErrorType::IOError:
            prefix = "IO";
            break;
        default:
            prefix = "UNK";
    }
    
    std::stringstream ss;
    ss << "CHTL" << prefix << std::setfill('0') << std::setw(3) << number;
    return ss.str();
}

std::vector<std::string> findSimilarIdentifiers(const std::string& identifier,
                                              const std::vector<std::string>& candidates) {
    std::vector<std::pair<std::string, int>> scored;
    
    // 简单的编辑距离算法
    auto editDistance = [](const std::string& s1, const std::string& s2) -> int {
        int m = s1.length();
        int n = s2.length();
        
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }
        
        return dp[m][n];
    };
    
    for (const auto& candidate : candidates) {
        int distance = editDistance(identifier, candidate);
        // 只考虑相似度较高的候选
        if (distance <= 3 && distance < identifier.length()) {
            scored.push_back({candidate, distance});
        }
    }
    
    // 按距离排序
    std::sort(scored.begin(), scored.end(),
             [](const auto& a, const auto& b) { return a.second < b.second; });
    
    std::vector<std::string> result;
    for (const auto& [name, _] : scored) {
        result.push_back(name);
        if (result.size() >= 3) {  // 最多返回3个建议
            break;
        }
    }
    
    return result;
}

std::vector<std::string> generateSuggestions(ErrorType type, const std::string& context) {
    std::vector<std::string> suggestions;
    
    switch (type) {
        case ErrorType::SyntaxError:
            suggestions.push_back("Check for missing semicolons or brackets");
            suggestions.push_back("Verify keyword spelling");
            break;
            
        case ErrorType::TypeError:
            suggestions.push_back("Ensure type compatibility");
            suggestions.push_back("Check function parameter types");
            break;
            
        case ErrorType::ImportError:
            suggestions.push_back("Verify the module path");
            suggestions.push_back("Check if the module is installed");
            suggestions.push_back("Ensure the module exports the required items");
            break;
            
        default:
            suggestions.push_back("Review the CHTL documentation");
    }
    
    return suggestions;
}

std::string getFileSnippet(const std::string& filename, int startLine, int endLine) {
    std::ifstream file(filename);
    if (!file) {
        return "";
    }
    
    std::stringstream result;
    std::string line;
    int lineNum = 1;
    
    while (std::getline(file, line) && lineNum <= endLine) {
        if (lineNum >= startLine) {
            result << line << "\n";
        }
        lineNum++;
    }
    
    return result.str();
}

} // namespace ErrorHelpers

} // namespace chtl