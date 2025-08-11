#ifndef CHTL_BASIC_PARSER_NEW_H
#define CHTL_BASIC_PARSER_NEW_H

#include <memory>
#include <vector>
#include <string>
#include <stack>
#include "Common/Token.h"
#include "Node/Node_new.h"

namespace chtl {

// 前向声明
class BasicLexer;
class BasicContext;

// 解析状态
enum class ParseState {
    INITIAL,
    PARSING,
    COMPLETED,
    ERROR
};

// 解析错误
struct ParseError {
    std::string message;
    Token token;
    int line;
    int column;
};

// 基础解析器 - 使用 unique_ptr 管理 AST
class BasicParser {
protected:
    BasicLexer* lexer_;                      // 词法分析器（不拥有）
    BasicContext* context_;                  // 上下文（不拥有）
    std::unique_ptr<Node> rootNode_;         // 根节点（拥有整个 AST）
    ParseState state_;                       // 解析状态
    std::vector<ParseError> errors_;         // 错误列表
    
    // 当前 token
    Token currentToken_;
    Token previousToken_;
    
    // 节点栈（构建过程中的临时存储）
    std::stack<Node*> nodeStack_;            // 原始指针，不拥有
    
public:
    BasicParser() : lexer_(nullptr), context_(nullptr), 
                   state_(ParseState::INITIAL) {}
    virtual ~BasicParser() = default;
    
    // 禁用拷贝
    BasicParser(const BasicParser&) = delete;
    BasicParser& operator=(const BasicParser&) = delete;
    
    // 初始化
    virtual bool initialize(BasicLexer* lexer, BasicContext* context);
    
    // 解析方法
    virtual std::unique_ptr<Node> parse() = 0;
    virtual std::unique_ptr<Node> parseFile(const std::string& filename);
    virtual std::unique_ptr<Node> parseString(const std::string& content);
    
    // 获取结果（转移所有权）
    std::unique_ptr<Node> getRootNode() { return std::move(rootNode_); }
    
    // 获取状态
    ParseState getState() const { return state_; }
    const std::vector<ParseError>& getErrors() const { return errors_; }
    bool hasErrors() const { return !errors_.empty(); }
    
protected:
    // Token 操作
    void advance();
    Token peek(int offset = 0) const;
    bool match(TokenType type);
    bool check(TokenType type) const;
    Token consume(TokenType type, const std::string& message);
    Token getPreviousToken() const { return previousToken_; }
    
    // 错误处理
    void addError(const std::string& message);
    void addError(const std::string& message, const Token& token);
    void synchronize();
    void panic();
    void recover();
    
    // 节点创建辅助方法
    template<typename T, typename... Args>
    std::unique_ptr<T> createNode(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    // 节点栈操作（用于构建过程）
    void pushNode(Node* node) { nodeStack_.push(node); }
    Node* popNode();
    Node* peekNode() const;
    bool isNodeStackEmpty() const { return nodeStack_.empty(); }
    size_t getNodeStackSize() const { return nodeStack_.size(); }
    
    // 状态管理
    void setState(ParseState state) { state_ = state; }
    
    // 工具方法
    bool isAtEnd() const;
    void skipWhitespaceTokens();
    void skipToNextStatement();
    
    // 调试
    virtual void printDebugInfo() const;
};

} // namespace chtl

#endif // CHTL_BASIC_PARSER_NEW_H