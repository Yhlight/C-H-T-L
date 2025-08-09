#ifndef CHTL_CSS_STATE_H
#define CHTL_CSS_STATE_H

#include "State/BasicState.h"

namespace chtl {

// CSS状态机（用于处理style块内的CSS代码）
class CssState : public BasicState {
public:
    CssState(BasicLexer* lexer) : BasicState(StateType::CSS, "CssState", lexer) {}
    
    // TODO: 实现CSS状态机
    std::shared_ptr<BasicState> handleChar(char ch) override {
        // 占位实现
        (void)ch; // 避免未使用参数警告
        return nullptr;
    }
    
    bool accepts(char ch) const override {
        // 占位实现
        (void)ch; // 避免未使用参数警告
        return true;
    }
};

} // namespace chtl

#endif // CHTL_CSS_STATE_H