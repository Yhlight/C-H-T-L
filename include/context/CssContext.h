#ifndef CHTL_CSS_CONTEXT_H
#define CHTL_CSS_CONTEXT_H

#include "context/BasicContext.h"

namespace chtl {

// CSS上下文类（用于处理style块内的CSS代码）
class CssContext : public BasicContext {
public:
    CssContext() : BasicContext(ContextType::CSS, "CssContext") {}
    
    // TODO: 实现CSS上下文
    bool validate() override {
        // 占位实现
        return true;
    }
};

} // namespace chtl

#endif // CHTL_CSS_CONTEXT_H