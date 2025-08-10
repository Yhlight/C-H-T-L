#include "Context/EnhancedContext.h"
#include <sstream>
#include <fstream>

namespace chtl {

EnhancedContext::EnhancedContext() 
    : ChtlContext(),
      errorHandler_(std::make_unique<ErrorHandler>()) {
}

void EnhancedContext::addError(const std::string& error) {
    ErrorContext ctx = buildErrorContext(-1, -1);
    errorHandler_->reportError(ErrorType::GENERAL, error, ctx);
    updateStringCaches();
}

void EnhancedContext::addWarning(const std::string& warning) {
    ErrorContext ctx = buildErrorContext(-1, -1);
    errorHandler_->reportWarning(warning, ctx);
    updateStringCaches();
}

void EnhancedContext::addInfo(const std::string& info) {
    ErrorContext ctx = buildErrorContext(-1, -1);
    errorHandler_->reportInfo(info, ctx);
    updateStringCaches();
}

bool EnhancedContext::hasErrors() const {
    return errorHandler_->hasErrors();
}

bool EnhancedContext::hasWarnings() const {
    return errorHandler_->hasWarnings();
}

const std::vector<std::string>& EnhancedContext::getErrors() const {
    updateStringCaches();
    return errors_;
}

const std::vector<std::string>& EnhancedContext::getWarnings() const {
    updateStringCaches();
    return warnings_;
}

const std::vector<std::string>& EnhancedContext::getInfos() const {
    updateStringCaches();
    return infos_;
}

void EnhancedContext::clearErrors() {
    errorHandler_->clearErrors();
    errors_.clear();
}

void EnhancedContext::clearWarnings() {
    // ErrorHandler doesn't have separate clear methods, so we'll clear all
    warnings_.clear();
}

void EnhancedContext::clearAll() {
    errorHandler_->clearErrors();
    errors_.clear();
    warnings_.clear();
    infos_.clear();
}

void EnhancedContext::reportError(const ErrorDetail& error) {
    errorHandler_->reportError(error.getType(), error.getMessage(), error.getContext());
    updateStringCaches();
}

void EnhancedContext::reportWarning(const ErrorDetail& warning) {
    errorHandler_->reportWarning(warning.getMessage(), warning.getContext());
    updateStringCaches();
}

void EnhancedContext::setSourceCode(const std::string& sourceCode) {
    sourceCode_ = sourceCode;
    sourceLines_.clear();
    
    // 分割源码为行
    std::istringstream iss(sourceCode);
    std::string line;
    while (std::getline(iss, line)) {
        sourceLines_.push_back(line);
    }
}

std::string EnhancedContext::formatErrors(bool useColor) const {
    std::stringstream ss;
    const auto& errors = errorHandler_->getErrors();
    
    for (const auto& error : errors) {
        ss << error.format(useColor) << "\n";
    }
    
    return ss.str();
}

std::string EnhancedContext::formatWarnings(bool useColor) const {
    std::stringstream ss;
    const auto& errors = errorHandler_->getErrors();
    
    for (const auto& error : errors) {
        if (error.getSeverity() == ErrorSeverity::WARNING) {
            ss << error.format(useColor) << "\n";
        }
    }
    
    return ss.str();
}

std::string EnhancedContext::getContextLines(int line, int contextSize) const {
    std::stringstream ss;
    int startLine = std::max(1, line - contextSize);
    int endLine = std::min(static_cast<int>(sourceLines_.size()), line + contextSize);
    
    for (int i = startLine; i <= endLine; ++i) {
        ss << i << " | " << getSourceLine(i) << "\n";
        if (i == line) {
            ss << "   | ^~~~~ error here\n";
        }
    }
    
    return ss.str();
}

void EnhancedContext::updateStringCaches() const {
    errors_.clear();
    warnings_.clear();
    infos_.clear();
    
    const auto& allErrors = errorHandler_->getErrors();
    for (const auto& error : allErrors) {
        switch (error.getSeverity()) {
            case ErrorSeverity::ERROR:
                errors_.push_back(error.getMessage());
                break;
            case ErrorSeverity::WARNING:
                warnings_.push_back(error.getMessage());
                break;
            case ErrorSeverity::INFO:
                infos_.push_back(error.getMessage());
                break;
            case ErrorSeverity::FATAL:
                errors_.push_back(error.getMessage());
                break;
        }
    }
}

std::string EnhancedContext::getSourceLine(int line) const {
    if (line > 0 && line <= static_cast<int>(sourceLines_.size())) {
        return sourceLines_[line - 1];
    }
    return "";
}

std::vector<std::string> EnhancedContext::getSourceLines(int startLine, int endLine) const {
    std::vector<std::string> lines;
    
    if (sourceLines_.empty() && !sourceCode_.empty()) {
        // 延迟解析源码
        std::istringstream iss(sourceCode_);
        std::string line;
        while (std::getline(iss, line)) {
            sourceLines_.push_back(line);
        }
    }
    
    for (int i = startLine; i <= endLine && i <= static_cast<int>(sourceLines_.size()); ++i) {
        if (i > 0) {
            lines.push_back(sourceLines_[i - 1]);
        }
    }
    
    return lines;
}

ErrorContext EnhancedContext::buildErrorContext(int line, int column) const {
    ErrorContext context;
    context.line = line;
    context.column = column;
    context.fileName = fileName_;
    
    if (line > 0) {
        // 获取上下文行并拼接成字符串
        auto lines = getSourceLines(std::max(1, line - 2), line + 2);
        std::stringstream ss;
        int currentLine = std::max(1, line - 2);
        for (const auto& lineContent : lines) {
            ss << currentLine << " | " << lineContent << "\n";
            currentLine++;
        }
        context.contextLines = ss.str();
        
        if (line <= static_cast<int>(sourceLines_.size())) {
            context.sourceCode = sourceLines_[line - 1];
        }
    }
    
    return context;
}

} // namespace chtl