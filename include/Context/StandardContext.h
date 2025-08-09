#ifndef CHTL_STANDARD_CONTEXT_H
#define CHTL_STANDARD_CONTEXT_H

#include "Context/ChtlContext.h"

namespace chtl {

// StandardContext - CHTL标准上下文的具体实现
// 这是ChtlContext的别名，用于更清晰的命名
class StandardContext : public ChtlContext {
public:
    StandardContext() : ChtlContext() {}
    
    // 可以在这里添加StandardContext特有的方法
};

} // namespace chtl

#endif // CHTL_STANDARD_CONTEXT_H