#ifndef CHTL_CHTLJS_STATE_H
#define CHTL_CHTLJS_STATE_H

#include "State/BasicState.h"
#include <memory>

namespace chtl {

class ChtlJsLexer;

/**
 * CHTL-JS状态
 * 处理CHTL扩展的JavaScript语法
 */
class ChtlJsState : public BasicState {
public:
    explicit ChtlJsState(BasicLexer* lexer);
    virtual ~ChtlJsState() = default;
    
    // 实现BasicState纯虚函数
    std::shared_ptr<BasicState> handleChar(char ch) override;
    bool accepts(char ch) const override;
    void reset() override;
    
    // CHTL-JS特有状态
    bool isInChtlSequence() const { return inChtlSequence_; }
    void setInChtlSequence(bool value) { inChtlSequence_ = value; }
    
    bool isInSelectorMode() const { return inSelectorMode_; }
    void setInSelectorMode(bool value) { inSelectorMode_ = value; }
    
    bool isInMethodCall() const { return inMethodCall_; }
    void setInMethodCall(bool value) { inMethodCall_ = value; }
    
private:
    bool inChtlSequence_;
    bool inSelectorMode_;
    bool inMethodCall_;
};

} // namespace chtl

#endif // CHTL_CHTLJS_STATE_H