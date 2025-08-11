#ifndef CHTL_JS_STATE_H
#define CHTL_JS_STATE_H

#include "State/BasicState.h"
#include <string>
#include <stack>

namespace chtl {

// JavaScript状态机（用于处理script块内的JavaScript代码）
class JsState : public BasicState {
public:
    enum class State {
        JS_NORMAL,
        JS_STRING_SINGLE,    // 单引号字符串
        JS_STRING_DOUBLE,    // 双引号字符串
        JS_TEMPLATE_LITERAL, // 模板字符串
        JS_COMMENT_SINGLE,   // 单行注释
        JS_COMMENT_MULTI,    // 多行注释
        JS_REGEX,            // 正则表达式
        JS_NUMBER,           // 数字
        JS_IDENTIFIER,       // 标识符
        JS_OPERATOR,         // 操作符
        ERROR
    };

private:
    State currentState_;
    State previousState_;
    std::stack<State> stateStack_;
    
    char stringDelimiter_;
    int braceDepth_;
    int parenDepth_;
    int bracketDepth_;
    int templateDepth_;      // 模板字符串嵌套深度
    
    bool inExpression_;      // 是否在表达式中
    bool afterOperator_;     // 是否在操作符后（用于区分正则和除法）
    
    std::string buffer_;
    std::string currentIdentifier_;
    std::string lastToken_;

public:
    JsState(BasicLexer* lexer);
    
    // BasicState接口实现
    std::shared_ptr<BasicState> handleChar(char ch) override;
    bool accepts(char ch) const override;
    void reset() override;
    
    // 辅助方法
    void processChar(char c);
    bool isInStringLiteral() const;
    bool isInComment() const;
    bool isInTemplateLiteral() const { return currentState_ == State::JS_TEMPLATE_LITERAL; }
    bool isInRegex() const { return currentState_ == State::JS_REGEX; }
    std::string getStateName() const;
    
    // JS特定功能
    State getCurrentState() const { return currentState_; }
    int getBraceDepth() const { return braceDepth_; }
    bool isInExpression() const { return inExpression_; }
    
protected:
    void transitionTo(State newState);
    
private:
    void handleNormalState(char c);
    void handleStringState(char c);
    void handleTemplateState(char c);
    void handleCommentState(char c);
    void handleRegexState(char c);
    void handleNumberState(char c);
    void handleIdentifierState(char c);
    void handleOperatorState(char c);
    
    bool isEscaped() const;
    bool checkSequence(const std::string& sequence) const;
    bool isIdentifierStart(char c) const;
    bool isIdentifierPart(char c) const;
    bool isDigit(char c) const;
    bool isOperatorChar(char c) const;
    bool shouldStartRegex() const;  // 判断/是否开始正则表达式
};

} // namespace chtl

#endif // CHTL_JS_STATE_H