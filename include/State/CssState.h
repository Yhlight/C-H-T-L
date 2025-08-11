#ifndef CHTL_CSS_STATE_H
#define CHTL_CSS_STATE_H

#include "State/BasicState.h"
#include <string>
#include <stack>

namespace chtl {

// CSS状态机（用于处理style块内的CSS代码）
class CssState : public BasicState {
public:
    enum class State {
        CSS_NORMAL,
        CSS_STRING,
        CSS_COMMENT,
        CSS_AT_RULE,
        CSS_SELECTOR,
        CSS_PROPERTY_NAME,
        CSS_PROPERTY_VALUE,
        CSS_URL,
        CSS_FUNCTION,
        CSS_VARIABLE,
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
    
    bool inAtRule_;
    bool inSelector_;
    bool inPropertyName_;
    bool inPropertyValue_;
    
    std::string buffer_;
    std::string currentBuffer_;  // 添加缺失的成员
    std::string currentSelector_;
    std::string currentProperty_;
    std::string currentAtRule_;

public:
    CssState(BasicLexer* lexer);
    
    // BasicState接口实现
    std::shared_ptr<BasicState> handleChar(char ch) override;
    bool accepts(char ch) const override;
    void reset() override;
    
    // 辅助方法
    void processChar(char c);
    bool isInStringLiteral() const;
    bool isInComment() const;
    bool isInPreprocessor() const { return false; }
    std::string getStateName() const;
    
    // CSS特定功能
    bool isInSelector() const { return inSelector_; }
    bool isInPropertyName() const { return inPropertyName_; }
    bool isInPropertyValue() const { return inPropertyValue_; }
    bool isInAtRule() const { return inAtRule_; }
    
    State getCurrentState() const { return currentState_; }
    std::string getCurrentSelector() const { return currentSelector_; }
    std::string getCurrentProperty() const { return currentProperty_; }
    
protected:
    void transitionTo(State newState);
    
private:
    void handleNormalState(char c);
    void handleStringState(char c);
    void handleCommentState(char c);
    void handleAtRuleState(char c);
    void handleSelectorState(char c);
    void handlePropertyNameState(char c);
    void handlePropertyValueState(char c);
    void handleUrlState(char c);
    void handleFunctionState(char c);
    void handleVariableState(char c);
    
    bool isEscaped() const;
    bool checkSequence(const std::string& sequence) const;
    bool isIdentifierBefore() const;
    bool isIdentifierStart(char c) const;
    bool isIdentifierPart(char c) const;
};

} // namespace chtl

#endif // CHTL_CSS_STATE_H