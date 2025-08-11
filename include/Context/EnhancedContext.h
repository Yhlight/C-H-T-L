#ifndef CHTL_ENHANCED_CONTEXT_H
#define CHTL_ENHANCED_CONTEXT_H

#include "Context/BasicContext.h"
#include "Context/ChtlContext.h"
#include "Error/ErrorHandler.h"
#include <memory>
#include <string>
#include <vector>

namespace chtl {

// 增强的上下文，集成错误处理
class EnhancedContext : public ChtlContext {
public:
    EnhancedContext();
    virtual ~EnhancedContext() = default;
    
    // 增强的错误处理接口
    void addError(const std::string& error);
    void addWarning(const std::string& warning);
    void addInfo(const std::string& info);
    
    bool hasErrors() const;
    bool hasWarnings() const;
    
    const std::vector<std::string>& getErrors() const;
    const std::vector<std::string>& getWarnings() const;
    const std::vector<std::string>& getInfos() const;
    
    void clearErrors();
    void clearWarnings();
    void clearAll();
    
    // 详细错误报告
    void reportError(const ErrorDetail& error);
    void reportWarning(const ErrorDetail& warning);
    
    // 设置源文件信息
    void setSourceFile(const std::string& fileName) { fileName_ = fileName; }
    void setSourceCode(const std::string& sourceCode);
    const std::string& getSourceFile() const { return fileName_; }
    
    // 错误恢复
    void pushRecoveryPoint() { errorHandler_->pushRecoveryPoint(); }
    void popRecoveryPoint() { errorHandler_->popRecoveryPoint(); }
    
    // 获取错误处理器
    ErrorHandler* getErrorHandler() { return errorHandler_.get(); }
    const ErrorHandler* getErrorHandler() const { return errorHandler_.get(); }
    
    // 格式化错误输出
    std::string formatErrors(bool useColor = true) const;
    std::string formatWarnings(bool useColor = true) const;
    std::string formatSummary() const;
    
    // 获取上下文行
    std::string getContextLines(int line, int contextSize = 2) const;
    
private:
    std::unique_ptr<ErrorHandler> errorHandler_;
    std::string fileName_;
    std::string sourceCode_;
    mutable std::vector<std::string> sourceLines_;  // 源码行缓存
    
    // 兼容旧接口的错误列表
    mutable std::vector<std::string> errors_;
    mutable std::vector<std::string> warnings_;
    mutable std::vector<std::string> infos_;
    
    // 更新字符串缓存
    void updateStringCaches() const;
    
    // 获取源码行
    std::string getSourceLine(int line) const;
    std::vector<std::string> getSourceLines(int startLine, int endLine) const;
    
    // 构建错误上下文
    ErrorContext buildErrorContext(int line, int column) const;
};

// 创建增强上下文的工厂函数
std::shared_ptr<EnhancedContext> createEnhancedContext();

} // namespace chtl

#endif // CHTL_ENHANCED_CONTEXT_H