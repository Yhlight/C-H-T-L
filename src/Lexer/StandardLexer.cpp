#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Context/ContextFactory.h"
#include "State/StandardState.h"

namespace chtl {

StandardLexer::StandardLexer() : BasicLexer() {
    // 初始化默认状态和上下文
    if (!context_) {
        context_ = std::make_shared<StandardContext>();
    }
}

std::shared_ptr<BasicContext> StandardLexer::createDefaultContext() const {
    return std::make_shared<StandardContext>();
}

std::shared_ptr<BasicState> StandardLexer::createDefaultState() const {
    return std::make_shared<StandardState>(this);
}

void StandardLexer::reset() {
    BasicLexer::reset();
    // StandardLexer特定的重置逻辑
}

} // namespace chtl