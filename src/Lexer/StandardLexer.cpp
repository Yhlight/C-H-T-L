#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "State/StandardState.h"

namespace chtl {

StandardLexer::StandardLexer() : BasicLexer() {
    // 初始化默认状态和上下文
    if (!context_) {
        context_ = createInitialContext();
    }
    if (!currentState_) {
        currentState_ = createInitialState();
    }
}

std::shared_ptr<BasicContext> StandardLexer::createInitialContext() {
    return std::make_shared<StandardContext>();
}

std::shared_ptr<BasicState> StandardLexer::createInitialState() {
    return std::make_shared<StandardState>(this);
}

} // namespace chtl