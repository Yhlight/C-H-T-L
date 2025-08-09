#ifndef CHTL_STANDARD_STATE_H
#define CHTL_STANDARD_STATE_H

#include "State/ChtlState.h"

namespace chtl {

// StandardState - CHTL标准状态机的具体实现
// 这是ChtlState的别名，用于更清晰的命名
class StandardState : public ChtlState {
public:
    StandardState(BasicLexer* lexer) : ChtlState(lexer) {}
    
    // 可以在这里添加StandardState特有的方法
};

} // namespace chtl

#endif // CHTL_STANDARD_STATE_H