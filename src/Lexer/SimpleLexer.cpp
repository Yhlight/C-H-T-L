#include "Lexer/SimpleLexer.h"
#include "State/StateFactory.h"
#include "Context/ContextFactory.h"

namespace chtl {

SimpleLexer::SimpleLexer()
    : BasicLexer() {
}

std::shared_ptr<BasicState> SimpleLexer::createInitialState() {
    // 创建CHTL状态作为初始状态
    return StateFactory::createState(StateType::CHTL, this);
}

std::shared_ptr<BasicContext> SimpleLexer::createInitialContext() {
    // 创建CHTL上下文
    return ContextFactory::createContext(ContextType::CHTL);
}

} // namespace chtl