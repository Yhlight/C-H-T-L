#include "Lexer/StandardLexer.h"
#include "State/StateFactory.h"
#include "Context/ContextFactory.h"

namespace chtl {

StandardLexer::StandardLexer() : BasicLexer() {
    // 构造函数，基类已经完成了大部分初始化工作
}

std::shared_ptr<BasicState> StandardLexer::createInitialState() {
    // 创建CHTL状态作为标准状态
    return StateFactory::createState(StateType::CHTL, this);
}

std::shared_ptr<BasicContext> StandardLexer::createInitialContext() {
    // 创建CHTL上下文作为标准上下文
    return ContextFactory::createContext(ContextType::CHTL);
}

} // namespace chtl