#ifndef CHTL_ENHANCED_CONTEXT_H
#define CHTL_ENHANCED_CONTEXT_H

#include "Context/Context.h"
#include "Error/ErrorHandler.h"
#include <memory>
#include <string>
#include <vector>

namespace chtl {

// 增强的上下文，集成错误处理
class EnhancedContext : public Context {
public:
    EnhancedContext();
    virtual ~EnhancedContext() = default;
    
    // Context接口实现
    void addError(const std::string& error) override;
    void addWarning(const std::string& warning) override;
    void addInfo(const std::string& info) override;
    
    bool hasErrors() const override;
    bool hasWarnings() const override;
    
    const std::vector<std::string>& getErrors() const override;
    const std::vector<std::string>& getWarnings() const override;
    const std::vector<std::string>& getInfos() const override;
    
    void clearErrors() override;
    void clearWarnings() override;
    void clearAll() override;
    
    // 增强的错误报告方法
    void reportError(ErrorType type,
                    const std::string& message,
                    int line = -1,
                    int column = -1);
    
    void reportWarning(const std::string& message,
                      int line = -1,
                      int column = -1);
    
    void reportInfo(const std::string& message,
                   int line = -1,
                   int column = -1);
    
    // 设置源文件信息
    void setSourceFile(const std::string& fileName) { fileName_ = fileName; }
    void setSourceCode(const std::string& sourceCode) { sourceCode_ = sourceCode; }
    
    // 获取错误处理器
    ErrorHandler& getErrorHandler() { return errorHandler_; }
    const ErrorHandler& getErrorHandler() const { return errorHandler_; }
    
    // 格式化错误输出
    std::string formatErrors(bool useColor = true) const;
    std::string formatSummary() const;
    
    // 错误恢复
    void pushRecoveryPoint() { errorHandler_.pushRecoveryPoint(); }
    void popRecoveryPoint() { errorHandler_.popRecoveryPoint(); }
    void recoverToLastPoint() { errorHandler_.recoverToLastPoint(); }
    
    // 批处理模式
    void beginBatch() { errorHandler_.beginBatch(); }
    void endBatch() { errorHandler_.endBatch(); }
    
    // 获取当前位置的上下文行
    std::string getContextLines(int line, int contextSize = 2) const;
    
private:
    ErrorHandler errorHandler_;
    std::string fileName_;
    std::string sourceCode_;
    std::vector<std::string> sourceLines_;
    
    // 缓存的字符串列表（为了兼容基类接口）
    mutable std::vector<std::string> errorStrings_;
    mutable std::vector<std::string> warningStrings_;
    mutable std::vector<std::string> infoStrings_;
    mutable bool stringsNeedUpdate_ = true;
    
    // 更新字符串缓存
    void updateStringCache() const;
    
    // 构建错误上下文
    ErrorContext buildErrorContext(int line, int column) const;
};

// 创建增强上下文的工厂函数
std::shared_ptr<EnhancedContext> createEnhancedContext();

} // namespace chtl

#endif // CHTL_ENHANCED_CONTEXT_H