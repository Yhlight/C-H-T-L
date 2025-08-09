#ifndef CHTL_CHTL_JS_STATE_H
#define CHTL_CHTL_JS_STATE_H

#include "State/BasicState.h"
#include "Common/Token.h"
#include <string>
#include <stack>

namespace chtl {

/**
 * CHTL-JS状态机
 * 处理CHTL扩展的JavaScript语法
 */
class ChtlJsState : public BasicState {
public:
    // CHTL-JS特有状态
    enum class State {
        // 基础JavaScript状态
        JS_NORMAL,
        JS_STRING,
        JS_TEMPLATE_LITERAL,
        JS_COMMENT_SINGLE,
        JS_COMMENT_MULTI,
        JS_REGEX,
        
        // CHTL扩展状态
        CHTL_SELECTOR_START,      // 遇到第一个 {
        CHTL_SELECTOR,            // {{ 内部
        CHTL_SELECTOR_END,        // 遇到第一个 }
        CHTL_ARROW,               // -> 操作符
        CHTL_METHOD_CALL,         // ->listen, ->delegate
        CHTL_ANIMATE_CALL,        // animate() 调用
        
        // 嵌套结构状态
        CHTL_LISTEN_OBJECT,       // listen({...}) 内部
        CHTL_DELEGATE_OBJECT,     // delegate({...}) 内部
        CHTL_ANIMATE_CONFIG,      // animate({...}) 配置对象
        CHTL_ANIMATE_KEYFRAME,    // when: [{...}] 关键帧
        
        // 错误状态
        ERROR
    };
    
private:
    State currentState_;
    State previousState_;
    std::stack<State> stateStack_;  // 用于处理嵌套结构
    
    // 选择器解析状态
    int braceCount_;                 // 跟踪花括号深度
    bool expectingSecondBrace_;      // 是否期待第二个 {
    std::string currentSelector_;    // 当前正在解析的选择器
    
    // 方法调用状态
    std::string currentMethod_;      // 当前CHTL方法名
    int parenDepth_;                // 圆括号深度
    int objectDepth_;               // 对象字面量深度
    
    // 字符串和模板状态
    char stringDelimiter_;          // 当前字符串分隔符
    int templateDepth_;             // 模板字符串嵌套深度
    
public:
    ChtlJsState(BasicLexer* lexer);
    virtual ~ChtlJsState() = default;
    
    // 实现BasicState接口
    std::shared_ptr<BasicState> handleChar(char ch) override;
    bool accepts(char ch) const override;
    void reset() override;
    
    // 辅助方法
    void processChar(char c);
    bool isInStringLiteral() const;
    bool isInComment() const;
    bool isInPreprocessor() const { return false; }
    std::string getStateName() const;
    
    // CHTL-JS特有方法
    bool isInChtlSelector() const;
    bool isInChtlMethod() const;
    bool isInAnimateConfig() const;
    State getCurrentState() const { return currentState_; }
    
    // 选择器相关
    std::string getCurrentSelector() const { return currentSelector_; }
    void clearSelector() { currentSelector_.clear(); }
    
    // 方法调用相关
    std::string getCurrentMethod() const { return currentMethod_; }
    bool isListenCall() const { return currentMethod_ == "listen"; }
    bool isDelegateCall() const { return currentMethod_ == "delegate"; }
    
    // 状态转换
    void transitionTo(State newState);
    void pushState(State newState);
    void popState();
    
    // 辅助方法
    bool isEscaped(const std::string& buffer, size_t pos) const;
    bool checkSequence(const std::string& buffer, const std::string& sequence) const;
    
private:
    // 状态处理方法
    void handleNormalState(char c);
    void handleStringState(char c);
    void handleTemplateState(char c);
    void handleCommentState(char c);
    void handleSelectorState(char c);
    void handleArrowState(char c);
    void handleMethodCallState(char c);
    void handleAnimateState(char c);
    
    // 特征检测
    bool isStartOfSelector(char c, char next);
    bool isEndOfSelector(char c, char next);
    bool isArrowOperator(char c, char next);
    bool isChtlMethodStart(const std::string& identifier);
    bool isAnimateCall(const std::string& identifier);
    
    // 字符分类
    bool isIdentifierStart(char c) const;
    bool isIdentifierPart(char c) const;
    bool isWhitespace(char c) const;
};

} // namespace chtl

#endif // CHTL_CHTL_JS_STATE_H