#ifndef CHTL_BASIC_PARSER_H
#define CHTL_BASIC_PARSER_H

#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <functional>
#include "Common/Token.h"
#include "Node/Node.h"
#include "Lexer/BasicLexer.h"
#include "Context/BasicContext.h"

namespace chtl {

// 前向声明
class BasicLexer;
class BasicContext;

// 解析器基类
class BasicParser {
public:
    // 解析器状态
    enum class ParseState {
        INITIAL,
        PARSING,
        SUCCESS,
        ERROR
    };
    
    // 错误信息
    struct ParseError {
        std::string message;
        size_t line;
        size_t column;
        std::string filename;
        
        ParseError(const std::string& msg, size_t l, size_t c, const std::string& file)
            : message(msg), line(l), column(c), filename(file) {}
    };
    
protected:
    std::shared_ptr<BasicLexer> lexer_;        // 词法分析器
    std::shared_ptr<BasicContext> context_;    // 上下文
    std::shared_ptr<Node> rootNode_;          // 根节点
    ParseState state_;                        // 解析状态
    std::vector<ParseError> errors_;          // 错误列表
    std::vector<ParseError> warnings_;        // 警告列表
    
    // 当前处理的token
    Token currentToken_;
    Token previousToken_;
    bool hasLookahead_ = false;
    
    // 节点栈（用于构建树）
    std::stack<std::shared_ptr<Node>> nodeStack_;
    
public:
    BasicParser();
    virtual ~BasicParser() = default;
    
    // 初始化
    virtual bool initialize(std::shared_ptr<BasicLexer> lexer, 
                          std::shared_ptr<BasicContext> context);
    
    // 解析方法
    virtual std::shared_ptr<Node> parse() = 0;
    virtual std::shared_ptr<Node> parseFile(const std::string& filename);
    virtual std::shared_ptr<Node> parseString(const std::string& content);
    
    // 获取结果
    std::shared_ptr<Node> getRootNode() const { return rootNode_; }
    ParseState getState() const { return state_; }
    const std::vector<ParseError>& getErrors() const { return errors_; }
    const std::vector<ParseError>& getWarnings() const { return warnings_; }
    bool hasErrors() const { return !errors_.empty(); }
    bool hasWarnings() const { return !warnings_.empty(); }
    
    // 错误处理
    void reportError(const std::string& message);
    void reportError(const std::string& message, const Token& token);
    void reportWarning(const std::string& message);
    void reportWarning(const std::string& message, const Token& token);
    void clearErrors() { errors_.clear(); }
    void clearWarnings() { warnings_.clear(); }
    
protected:
    // Token操作
    Token getNextToken();
    Token peekNextToken();
    void consumeToken();
    bool matchToken(TokenType type);
    bool expectToken(TokenType type);
    bool expectToken(TokenType type, const std::string& errorMsg);
    
    // 辅助方法
    bool isAtEnd() const;
    void synchronize();  // 错误恢复
    
    // 节点栈操作
    void pushNode(std::shared_ptr<Node> node) { nodeStack_.push(node); }
    std::shared_ptr<Node> popNode();
    std::shared_ptr<Node> peekNode() const;
    bool isNodeStackEmpty() const { return nodeStack_.empty(); }
    size_t getNodeStackSize() const { return nodeStack_.size(); }
    
    // 子类需要实现的方法
    virtual void initializeParser() {}
    virtual void finalizeParser() {}
    
    // 工具方法
    std::string getTokenDescription(TokenType type) const;
    std::string getCurrentPosition() const;
};

} // namespace chtl

#endif // CHTL_BASIC_PARSER_H