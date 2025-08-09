#ifndef CHTL_STATE_STANDARD_STATE_H
#define CHTL_STATE_STANDARD_STATE_H

#include "State/ChtlState.h"

namespace chtl {

/**
 * @brief StandardState - 标准CHTL状态机
 * 
 * 这是BasicState的标准实现，基于ChtlState。
 * 提供了处理CHTL语法的完整状态机功能。
 */
class StandardState : public ChtlState {
public:
    // 使用ChtlState的构造函数
    using ChtlState::ChtlState;
    
    virtual ~StandardState() = default;
};

} // namespace chtl

#endif // CHTL_STATE_STANDARD_STATE_H