#include "lexer/ChtlLexer.h"

namespace chtl {

ChtlLexer::ChtlLexer()
    : BasicLexer(),
      allowUnquotedLiterals_(true),
      colonEqualsEquivalence_(true) {
}

std::shared_ptr<BasicState> ChtlLexer::createInitialState() {
    return StateFactory::createInitialState(this);
}

std::shared_ptr<BasicContext> ChtlLexer::createInitialContext() {
    return std::make_shared<ChtlContext>();
}

} // namespace chtl