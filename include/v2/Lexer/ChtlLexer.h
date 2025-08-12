#pragma once

#include "Token.h"
#include "v2/State/ChtlParseState.h"
#include <string>
#include <memory>
#include <queue>

namespace chtl::v2 {

// 前向声明
class ChtlStateMachine;

/**
 * CHTL 词法分析器
 * 状态感知的词法分析器，Token 类型依赖当前解析状态
 */
class ChtlLexer {
public:
    explicit ChtlLexer(const std::string& input);
    ~ChtlLexer();
    
    /**
     * 设置关联的状态机
     */
    void setStateMachine(ChtlStateMachine* stateMachine) {
        stateMachine_ = stateMachine;
    }
    
    /**
     * 获取下一个 Token
     * Token 类型会根据当前状态确定
     */
    Token nextToken();
    
    /**
     * 查看下一个 Token（不消费）
     */
    Token peekToken();
    
    /**
     * 查看指定位置的 Token（不消费）
     */
    Token peekToken(size_t ahead);
    
    /**
     * 检查是否到达输入结尾
     */
    bool isAtEnd() const;
    
    /**
     * 获取当前位置信息
     */
    int getCurrentLine() const { return line_; }
    int getCurrentColumn() const { return column_; }
    
    /**
     * 重置词法分析器
     */
    void reset();
    
    /**
     * 设置当前状态（由状态机调用）
     * 这会影响 Token 类型的判定
     */
    void setCurrentState(ChtlParseState state);
    
private:
    /**
     * 扫描下一个 Token
     */
    Token scanToken();
    
    /**
     * 根据当前状态扫描 Token
     */
    Token scanInTopLevel();
    Token scanInElementContent();
    Token scanInStyleBlock();
    Token scanInStylePropertyValue();
    Token scanInScriptBlock();
    Token scanInTextBlock();
    Token scanInExpression();
    // ... 其他状态的扫描方法
    
    /**
     * 辅助方法
     */
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);
    bool matchSequence(const std::string& seq);
    
    /**
     * 扫描特定类型的 Token
     */
    Token scanIdentifier();
    Token scanString();
    Token scanNumber();
    Token scanOperator();
    Token scanWhitespace();
    Token scanComment();
    
    /**
     * 在 CSS 上下文中扫描
     */
    Token scanCssPropertyName();
    Token scanCssPropertyValue();
    Token scanCssSelector();
    
    /**
     * 确定标识符的具体类型
     */
    TokenType determineIdentifierType(const std::string& text);
    
    /**
     * 检查是否是特定类型的标识符
     */
    bool isHtmlTag(const std::string& text) const;
    bool isCssProperty(const std::string& text) const;
    bool isKeyword(const std::string& text) const;
    
    /**
     * 创建 Token
     */
    Token makeToken(TokenType type, const std::string& value);
    Token makeToken(TokenType type);
    Token makeError(const std::string& message);
    
private:
    // 输入和位置跟踪
    std::string input_;
    size_t current_ = 0;
    size_t start_ = 0;
    int line_ = 1;
    int column_ = 1;
    int tokenStartLine_ = 1;
    int tokenStartColumn_ = 1;
    
    // 状态相关
    ChtlStateMachine* stateMachine_ = nullptr;
    ChtlParseState currentState_ = ChtlParseState::TOP_LEVEL;
    
    // Token 缓冲（用于 peek）
    std::queue<Token> tokenBuffer_;
    
    // 静态数据
    static const std::unordered_set<std::string> HTML_TAGS;
    static const std::unordered_set<std::string> CSS_PROPERTIES;
    static const std::unordered_map<std::string, TokenType> KEYWORDS;
};

} // namespace chtl::v2