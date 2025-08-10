#include "Context/EnhancedContext.h"
#include <sstream>
#include <algorithm>

namespace chtl {

EnhancedContext::EnhancedContext() {
    // 设置错误回调，自动更新字符串缓存
    errorHandler_.setErrorCallback([this](const ErrorDetail&) {
        stringsNeedUpdate_ = true;
    });
    
    errorHandler_.setWarningCallback([this](const ErrorDetail&) {
        stringsNeedUpdate_ = true;
    });
}

void EnhancedContext::addError(const std::string& error) {
    reportError(ErrorType::PARSER_INVALID_SYNTAX, error);
}

void EnhancedContext::addWarning(const std::string& warning) {
    reportWarning(warning);
}

void EnhancedContext::addInfo(const std::string& info) {
    reportInfo(info);
}

bool EnhancedContext::hasErrors() const {
    return errorHandler_.hasErrors();
}

bool EnhancedContext::hasWarnings() const {
    return errorHandler_.hasWarnings();
}

const std::vector<std::string>& EnhancedContext::getErrors() const {
    updateStringCache();
    return errorStrings_;
}

const std::vector<std::string>& EnhancedContext::getWarnings() const {
    updateStringCache();
    return warningStrings_;
}

const std::vector<std::string>& EnhancedContext::getInfos() const {
    updateStringCache();
    return infoStrings_;
}

void EnhancedContext::clearErrors() {
    errorHandler_.clearErrors();
    errorStrings_.clear();
    stringsNeedUpdate_ = true;
}

void EnhancedContext::clearWarnings() {
    errorHandler_.clearWarnings();
    warningStrings_.clear();
    stringsNeedUpdate_ = true;
}

void EnhancedContext::clearAll() {
    errorHandler_.clearAll();
    errorStrings_.clear();
    warningStrings_.clear();
    infoStrings_.clear();
    stringsNeedUpdate_ = true;
}

void EnhancedContext::reportError(ErrorType type,
                                  const std::string& message,
                                  int line,
                                  int column) {
    ErrorContext ctx = buildErrorContext(line, column);
    errorHandler_.reportError(type, message, ctx);
}

void EnhancedContext::reportWarning(const std::string& message,
                                   int line,
                                   int column) {
    ErrorContext ctx = buildErrorContext(line, column);
    errorHandler_.reportWarning(message, ctx);
}

void EnhancedContext::reportInfo(const std::string& message,
                                int line,
                                int column) {
    ErrorContext ctx = buildErrorContext(line, column);
    errorHandler_.reportInfo(message, ctx);
}

std::string EnhancedContext::formatErrors(bool useColor) const {
    return errorHandler_.formatAllErrors(useColor);
}

std::string EnhancedContext::formatSummary() const {
    return errorHandler_.formatSummary();
}

std::string EnhancedContext::getContextLines(int line, int contextSize) const {
    if (sourceLines_.empty() && !sourceCode_.empty()) {
        // 分割源代码为行
        std::stringstream ss(sourceCode_);
        std::string lineStr;
        while (std::getline(ss, lineStr)) {
            sourceLines_.push_back(lineStr);
        }
    }
    
    if (line <= 0 || line > static_cast<int>(sourceLines_.size())) {
        return "";
    }
    
    std::stringstream result;
    int startLine = std::max(1, line - contextSize);
    int endLine = std::min(static_cast<int>(sourceLines_.size()), line + contextSize);
    
    for (int i = startLine; i <= endLine; ++i) {
        result << i << " | " << sourceLines_[i - 1] << "\n";
    }
    
    return result.str();
}

void EnhancedContext::updateStringCache() const {
    if (!stringsNeedUpdate_) {
        return;
    }
    
    errorStrings_.clear();
    warningStrings_.clear();
    infoStrings_.clear();
    
    // 转换错误为字符串
    for (const auto& error : errorHandler_.getErrors()) {
        errorStrings_.push_back(error.getMessage());
    }
    
    for (const auto& warning : errorHandler_.getWarnings()) {
        warningStrings_.push_back(warning.getMessage());
    }
    
    stringsNeedUpdate_ = false;
}

ErrorContext EnhancedContext::buildErrorContext(int line, int column) const {
    ErrorContext ctx;
    ctx.fileName = fileName_;
    ctx.line = line > 0 ? line : 1;
    ctx.column = column > 0 ? column : 1;
    
    // 获取源代码行
    if (!sourceLines_.empty() && line > 0 && line <= static_cast<int>(sourceLines_.size())) {
        ctx.sourceCode = sourceLines_[line - 1];
    } else if (!sourceCode_.empty()) {
        // 如果还没有分割成行，尝试获取
        std::stringstream ss(sourceCode_);
        std::string lineStr;
        int currentLine = 1;
        while (std::getline(ss, lineStr) && currentLine <= line) {
            if (currentLine == line) {
                ctx.sourceCode = lineStr;
                break;
            }
            currentLine++;
        }
    }
    
    // 获取上下文行
    ctx.contextLines = getContextLines(line, 2);
    
    return ctx;
}

void EnhancedContext::setSourceCode(const std::string& sourceCode) {
    sourceCode_ = sourceCode;
    sourceLines_.clear();  // 清除缓存的行
    
    // 立即分割成行，以便后续使用
    std::stringstream ss(sourceCode_);
    std::string lineStr;
    while (std::getline(ss, lineStr)) {
        sourceLines_.push_back(lineStr);
    }
}

// 工厂函数
std::shared_ptr<EnhancedContext> createEnhancedContext() {
    return std::make_shared<EnhancedContext>();
}

} // namespace chtl