#ifndef CHTL_ERROR_RECOVERY_H
#define CHTL_ERROR_RECOVERY_H

#include <string>
#include <vector>
#include <functional>
#include "Common/TokenType.h"
#include "Error/ErrorTypes.h"

namespace chtl {

// 错误恢复策略
class ErrorRecoveryStrategy {
public:
    virtual ~ErrorRecoveryStrategy() = default;
    
    // 是否可以从此错误恢复
    virtual bool canRecover(ErrorType type) const = 0;
    
    // 执行恢复
    virtual bool recover() = 0;
    
    // 获取恢复描述
    virtual std::string getDescription() const = 0;
};

// 词法错误恢复
class LexerErrorRecovery : public ErrorRecoveryStrategy {
public:
    using SkipFunction = std::function<void()>;
    
    LexerErrorRecovery(ErrorType type, SkipFunction skipFn);
    
    bool canRecover(ErrorType type) const override;
    bool recover() override;
    std::string getDescription() const override;
    
private:
    ErrorType errorType_;
    SkipFunction skipFunction_;
};

// 语法错误恢复
class ParserErrorRecovery : public ErrorRecoveryStrategy {
public:
    using SyncFunction = std::function<void(const std::vector<TokenType>&)>;
    
    ParserErrorRecovery(ErrorType type, 
                       const std::vector<TokenType>& syncTokens,
                       SyncFunction syncFn);
    
    bool canRecover(ErrorType type) const override;
    bool recover() override;
    std::string getDescription() const override;
    
    // 设置同步标记
    void setSyncTokens(const std::vector<TokenType>& tokens) {
        syncTokens_ = tokens;
    }
    
private:
    ErrorType errorType_;
    std::vector<TokenType> syncTokens_;
    SyncFunction syncFunction_;
};

// 恢复点管理器
class RecoveryPointManager {
public:
    struct RecoveryPoint {
        std::string name;
        std::function<void()> restoreFunction;
        int priority;
    };
    
    // 添加恢复点
    void addRecoveryPoint(const std::string& name,
                         std::function<void()> restoreFn,
                         int priority = 0);
    
    // 恢复到最近的恢复点
    bool recoverToNearest();
    
    // 恢复到指定恢复点
    bool recoverTo(const std::string& name);
    
    // 清除所有恢复点
    void clear();
    
    // 获取恢复点数量
    size_t getRecoveryPointCount() const { return recoveryPoints_.size(); }
    
private:
    std::vector<RecoveryPoint> recoveryPoints_;
};

// 智能错误恢复
class SmartErrorRecovery {
public:
    SmartErrorRecovery();
    ~SmartErrorRecovery() = default;
    
    // 注册恢复策略
    void registerStrategy(std::unique_ptr<ErrorRecoveryStrategy> strategy);
    
    // 尝试从错误恢复
    bool tryRecover(ErrorType type);
    
    // 获取可用的恢复策略
    std::vector<const ErrorRecoveryStrategy*> getAvailableStrategies(ErrorType type) const;
    
    // 设置最大恢复尝试次数
    void setMaxRecoveryAttempts(int max) { maxAttempts_ = max; }
    
    // 获取恢复统计
    struct RecoveryStats {
        int totalAttempts = 0;
        int successfulRecoveries = 0;
        int failedRecoveries = 0;
    };
    
    const RecoveryStats& getStats() const { return stats_; }
    void resetStats() { stats_ = RecoveryStats(); }
    
private:
    std::vector<std::unique_ptr<ErrorRecoveryStrategy>> strategies_;
    RecoveryStats stats_;
    int maxAttempts_ = 3;
    int currentAttempts_ = 0;
};

// 常用的同步标记集合
namespace SyncTokens {
    // 语句结束标记
    const std::vector<TokenType> STATEMENT_END = {
        TokenType::SEMICOLON,
        TokenType::RIGHT_BRACE,
        TokenType::NEWLINE
    };
    
    // 块结束标记
    const std::vector<TokenType> BLOCK_END = {
        TokenType::RIGHT_BRACE,
        TokenType::EOF_TOKEN
    };
    
    // 顶级声明开始标记
    const std::vector<TokenType> TOP_LEVEL = {
        TokenType::LEFT_BRACKET,  // [Custom], [Template]等
        TokenType::IMPORT,        // Import语句
        TokenType::EXPORT,        // [Export]
        TokenType::EOF_TOKEN
    };
    
    // 属性分隔符
    const std::vector<TokenType> ATTRIBUTE_SEP = {
        TokenType::COMMA,
        TokenType::RIGHT_BRACE,
        TokenType::NEWLINE
    };
}

} // namespace chtl

#endif // CHTL_ERROR_RECOVERY_H