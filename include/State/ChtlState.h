#ifndef CHTL_CHTL_STATE_H
#define CHTL_CHTL_STATE_H

#include "State/BasicState.h"
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
        WHITESPACE,         // 空白符
        IN_TEXT_BLOCK,      // 在text块内
        CSS_PROPERTY_NAME,  // CSS属性名
        CSS_PROPERTY_VALUE, // CSS属性值
        CSS_COLOR_VALUE     // CSS颜色值 (#开头)
    };
    
    SubState subState_;
    std::string buffer_;
    int startLine_;
    int startColumn_;
    bool inStyleBlock_;     // 是否在style块内
    bool inScriptBlock_;    // 是否在script块内
    int braceDepth_;        // 大括号深度
    bool inTextBlock_;      // 是否在text块内
    bool inCssProperty_;    // 是否在CSS属性中
    
public:
    ChtlState(BasicLexer* lexer);
    
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
    void emitToken(TokenType type);
    void emitToken(TokenType type, const std::string& value);
    
    // 各种子状态的处理方法
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
    std::shared_ptr<BasicState> handleWhitespace(char ch);
    std::shared_ptr<BasicState> handleTextBlock(char ch);
    std::shared_ptr<BasicState> handleCssPropertyName(char ch);
    std::shared_ptr<BasicState> handleCssPropertyValue(char ch);
    std::shared_ptr<BasicState> handleCssColorValue(char ch);
    
    // 辅助判断方法
    bool isIdentifierStart(char ch);
    bool isIdentifierPart(char ch);
    bool isIdentifierContinue(char ch);
    bool isDigit(char ch);
    bool isWhitespace(char ch);
    bool isOperatorChar(char ch);
    bool isHexDigit(char ch);
    
    // Token类型判断
    TokenType determineIdentifierType();
    TokenType determineOperatorType();
    TokenType determineNumberType();
    TokenType determineAtPrefixType();
    
    // 完成当前token
    void completeToken();
    void emitTokenAndReset(TokenType type);
    
    // 状态转换
    std::shared_ptr<BasicState> transitionToState(StateType newStateType);
};

} // namespace chtl

#endif // CHTL_CHTL_STATE_H