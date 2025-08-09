#ifndef CHTL_BASIC_LEXER_H
#define CHTL_BASIC_LEXER_H

#include <string>
#include <memory>
#include <queue>
#include <istream>
#include <fstream>
#include "Common/Token.h"
#include "State/BasicState.h"
#include "Context/BasicContext.h"
#include "State/StateFactory.h"
#include "Context/ContextFactory.h"

namespace chtl {

// 词法分析器基类
class BasicLexer {
protected:
    // 输入流
    std::unique_ptr<std::istream> inputStream_;
    std::string filename_;
    
    // 当前位置
    int currentLine_;
    int currentColumn_;
    int currentPosition_;  // 在文件中的字节位置
    
    // 字符缓冲
    static const int BUFFER_SIZE = 4096;
    char buffer_[BUFFER_SIZE];
    int bufferPos_;
    int bufferSize_;
    
    // Token队列
    std::queue<Token> tokenQueue_;
    
    // 当前状态
    std::shared_ptr<BasicState> currentState_;
    
    // 上下文
    std::shared_ptr<BasicContext> context_;
    
    // 错误处理
    bool hasError_;
    std::string lastError_;
    
public:
    // 构造函数
    BasicLexer();
    virtual ~BasicLexer();
    
    // 初始化
    virtual bool initialize(const std::string& filename);
    virtual bool initialize(std::unique_ptr<std::istream> stream, const std::string& sourceName = "<stream>");
    
    // 获取下一个Token
    virtual Token getNextToken();
    virtual Token peekNextToken();
    virtual bool hasMoreTokens();
    
    // 批量获取Token
    virtual std::vector<Token> getAllTokens();
    
    // 状态管理
    void setState(std::shared_ptr<BasicState> state);
    std::shared_ptr<BasicState> getState() const { return currentState_; }
    
    // 上下文管理
    void setContext(std::shared_ptr<BasicContext> context) { context_ = context; }
    std::shared_ptr<BasicContext> getContext() const { return context_; }
    
    // 位置信息
    int getCurrentLine() const { return currentLine_; }
    int getCurrentColumn() const { return currentColumn_; }
    int getCurrentPosition() const { return currentPosition_; }
    const std::string& getFilename() const { return filename_; }
    
    // 错误处理
    bool hasError() const { return hasError_; }
    const std::string& getLastError() const { return lastError_; }
    void clearError() { hasError_ = false; lastError_.clear(); }
    
    // Token管理（供State使用）
    void emitToken(const Token& token);
    void emitToken(TokenType type, const std::string& value);
    void emitToken(TokenType type, const std::string& value, int line, int column);
    
protected:
    // 读取字符
    virtual char getNextChar();
    virtual char peekChar();
    virtual void ungetChar();
    virtual bool isEOF() const;
    
    // 缓冲区管理
    virtual bool fillBuffer();
    
    // 错误报告
    virtual void reportError(const std::string& message);
    virtual void reportError(const std::string& message, int line, int column);
    
    // 创建初始状态和上下文的方法
    virtual std::shared_ptr<BasicState> createInitialState();
    virtual std::shared_ptr<BasicContext> createInitialContext();
    
    // 辅助方法
    void updatePosition(char ch);
    void skipWhitespace();
    std::string readUntil(const std::string& delimiters);
    std::string readWhile(const std::string& allowedChars);
    
    // 自动化状态和上下文管理
    void autoTransitionState(const std::string& trigger);
    void autoMarkContext(const std::string& token);
    
private:
    // 内部辅助方法
    void processChar(char ch);
    void finalizeTokens();
};

} // namespace chtl

#endif // CHTL_BASIC_LEXER_H