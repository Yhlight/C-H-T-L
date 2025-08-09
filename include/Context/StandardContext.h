#ifndef CHTL_CONTEXT_STANDARD_CONTEXT_H
#define CHTL_CONTEXT_STANDARD_CONTEXT_H

#include "Context/ChtlContext.h"

namespace chtl {

/**
 * @brief StandardContext - 标准CHTL上下文
 * 
 * 这是BasicContext的标准实现，基于ChtlContext。
 * 提供了CHTL编译器需要的所有上下文管理功能。
 */
class StandardContext : public ChtlContext {
public:
    // 使用ChtlContext的构造函数
    using ChtlContext::ChtlContext;
    
    virtual ~StandardContext() = default;
};

} // namespace chtl

#endif // CHTL_CONTEXT_STANDARD_CONTEXT_H