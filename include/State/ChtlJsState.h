#ifndef CHTL_CHTL_JS_STATE_H
#define CHTL_CHTL_JS_STATE_H

#include "State/BasicState.h"
#include <memory>

namespace chtl {

// CHTL-JS状态 - 跟踪CHTL-JS特定的语法状态
class ChtlJsState : public BasicState {
private:
    // CHTL-JS特定状态
    bool inChtlSelector_;      // 在 {{ }} 选择器中
    bool inChtlMethod_;        // 在 -> 方法调用中
    bool inTemplateString_;    // 在模板字符串中
    int selectorDepth_;        // 选择器嵌套深度
    int parenDepth_;          // 括号深度
    
public:
    ChtlJsState(BasicLexer* lexer)
        : BasicState(StateType::JS, "ChtlJsState", lexer),
          inChtlSelector_(false),
          inChtlMethod_(false),
          inTemplateString_(false),
          selectorDepth_(0),
          parenDepth_(0) {}
    
    // 状态查询
    bool isInChtlSelector() const { return inChtlSelector_; }
    bool isInChtlMethod() const { return inChtlMethod_; }
    bool isInTemplateString() const { return inTemplateString_; }
    bool isInSelectorMode() const { return inChtlSelector_; } // 兼容旧接口
    
    // 实现基类方法
    std::shared_ptr<BasicState> handleChar(char c) override;
    bool accepts(char c) const override;
    void reset() override;
    
    // CHTL-JS特定方法
    void enterChtlSelector() { inChtlSelector_ = true; selectorDepth_++; }
    void exitChtlSelector() { 
        selectorDepth_--;
        if (selectorDepth_ <= 0) {
            inChtlSelector_ = false;
            selectorDepth_ = 0;
        }
    }
    void enterChtlMethod() { inChtlMethod_ = true; }
    void exitChtlMethod() { inChtlMethod_ = false; }
    void enterTemplateString() { inTemplateString_ = true; }
    void exitTemplateString() { inTemplateString_ = false; }
};

} // namespace chtl

#endif // CHTL_CHTL_JS_STATE_H