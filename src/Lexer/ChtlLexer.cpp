#include "Lexer/ChtlLexer.h"

namespace chtl {

ChtlLexer::ChtlLexer()
    : BasicLexer(),
      allowUnquotedLiterals_(true),
      colonEqualsEquivalence_(true) {
}

std::shared_ptr<BasicState> ChtlLexer::createInitialState() {
    // 使用工厂方法创建初始状态
    return StateFactory::createInitialState(this);
}

std::shared_ptr<BasicContext> ChtlLexer::createInitialContext() {
    // 使用工厂方法创建初始上下文
    return ContextFactory::createInitialContext();
}

} // namespace chtl