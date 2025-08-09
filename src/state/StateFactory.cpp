#include "state/StateFactory.h"
#include "state/ChtlState.h"
#include "state/CssState.h"
#include "state/JsState.h"
#include "state/ChtlJsState.h"

namespace chtl {

std::shared_ptr<BasicState> StateFactory::createState(StateType type, Lexer* lexer) {
    switch (type) {
        case StateType::CHTL:
            return std::make_shared<ChtlState>(lexer);
        case StateType::CSS:
            return std::make_shared<CssState>(lexer);
        case StateType::JS:
            return std::make_shared<JsState>(lexer);
        case StateType::CHTL_JS:
            return std::make_shared<ChtlJsState>(lexer);
        default:
            return nullptr;
    }
}

std::shared_ptr<BasicState> StateFactory::createInitialState(Lexer* lexer) {
    return createState(StateType::CHTL, lexer);
}

} // namespace chtl