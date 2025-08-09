#ifndef CHTL_CHTL_STATE_H
#define CHTL_CHTL_STATE_H

#include "state/BasicState.h"
#include "Common/GlobalMap.h"
#include <cctype>
#include <sstream>

namespace chtl {

// CHTL主状态机
class ChtlState : public BasicState {
private:
    // 子状态枚举
    enum class SubState {
        INITIAL,            // 初始状态
        IDENTIFIER,         // 标识符
        STRING_SINGLE,      // 单引号字符串
        STRING_DOUBLE,      // 双引号字符串
        UNQUOTED_LITERAL,   // 无引号字面量
        NUMBER,             // 数字
        OPERATOR,           // 操作符
        COMMENT_SINGLE,     // 单行注释
        COMMENT_MULTI,      // 多行注释
        HTML_COMMENT,       // HTML注释
        AT_PREFIX,          // @前缀
        SPECIAL_MARKER,     // 特殊标记 [xxx]
        WHITESPACE          // 空白符
    };
    
    SubState subState_;
    std::string buffer_;
    int startLine_;
    int startColumn_;
    bool inStyleBlock_;     // 是否在style块内
    bool inScriptBlock_;    // 是否在script块内
    
public:
    ChtlState(Lexer* lexer);
    
    // 重写基类方法
    std::shared_ptr<BasicState> handleChar(char ch) override;
    void onEnter() override;
    void onExit() override;
    void onEnd() override;
    bool accepts(char ch) const override;
    std::string getCurrentValue() const override { return buffer_; }
    void reset() override;
    
    // 设置上下文
    void setInStyleBlock(bool value) { inStyleBlock_ = value; }
    void setInScriptBlock(bool value) { inScriptBlock_ = value; }
    bool isInStyleBlock() const { return inStyleBlock_; }
    bool isInScriptBlock() const { return inScriptBlock_; }
    
private:
    // 辅助方法
    bool isIdentifierStart(char ch) const;
    bool isIdentifierContinue(char ch) const;
    bool isOperatorChar(char ch) const;
    bool isWhitespace(char ch) const;
    
    // 处理不同子状态
    std::shared_ptr<BasicState> handleInitial(char ch);
    std::shared_ptr<BasicState> handleIdentifier(char ch);
    std::shared_ptr<BasicState> handleStringSingle(char ch);
    std::shared_ptr<BasicState> handleStringDouble(char ch);
    std::shared_ptr<BasicState> handleUnquotedLiteral(char ch);
    std::shared_ptr<BasicState> handleNumber(char ch);
    std::shared_ptr<BasicState> handleOperator(char ch);
    std::shared_ptr<BasicState> handleCommentSingle(char ch);
    std::shared_ptr<BasicState> handleCommentMulti(char ch);
    std::shared_ptr<BasicState> handleHtmlComment(char ch);
    std::shared_ptr<BasicState> handleAtPrefix(char ch);
    std::shared_ptr<BasicState> handleSpecialMarker(char ch);
    
    // 完成当前token
    void completeToken();
    void emitToken(TokenType type);
    void emitTokenAndReset(TokenType type);
    
    // 判断token类型
    TokenType determineIdentifierType();
    TokenType determineOperatorType();
    TokenType determineAtPrefixType();
    
    // 状态转换
    std::shared_ptr<BasicState> transitionToState(StateType newStateType);
};

} // namespace chtl

#endif // CHTL_CHTL_STATE_H