#include "State/ChtlJsState.h"
#include "Lexer/BasicLexer.h"

namespace chtl {

ChtlJsState::ChtlJsState(BasicLexer* lexer)
    : BasicState(lexer, StateType::JS),
      inChtlSequence_(false),
      inSelectorMode_(false),
      inMethodCall_(false) {
}

std::shared_ptr<BasicState> ChtlJsState::handleChar(char ch) {
    // CHTL-JS字符处理逻辑
    // 这里简单返回自身，实际实现需要处理状态转换
    return shared_from_this();
}

bool ChtlJsState::accepts(char ch) const {
    // 接受所有字符
    return true;
}

void ChtlJsState::reset() {
    inChtlSequence_ = false;
    inSelectorMode_ = false;
    inMethodCall_ = false;
}

} // namespace chtl