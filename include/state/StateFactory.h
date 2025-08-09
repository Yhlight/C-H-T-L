#ifndef CHTL_STATE_FACTORY_H
#define CHTL_STATE_FACTORY_H

#include <memory>
#include "state/BasicState.h"

namespace chtl {

// 前向声明
class BasicLexer;

// 状态工厂类
class StateFactory {
public:
    // 创建指定类型的状态
    static std::shared_ptr<BasicState> createState(StateType type, BasicLexer* lexer);
    
    // 创建初始状态（CHTL状态）
    static std::shared_ptr<BasicState> createInitialState(BasicLexer* lexer);
};

} // namespace chtl

#endif // CHTL_STATE_FACTORY_H