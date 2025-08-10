#ifndef CHTL_STANDARD_CONTEXT_H
#define CHTL_STANDARD_CONTEXT_H

#include "Context/ChtlContext.h"
#include "Context/NamespaceManager.h"
#include "Utils/ConstraintValidator.h"
#include <memory>

namespace chtl {

// StandardContext - CHTL标准上下文的具体实现
// 这是ChtlContext的别名，用于更清晰的命名
class StandardContext : public ChtlContext {
private:
    std::shared_ptr<NamespaceManager> namespaceManager_;
    std::shared_ptr<ConstraintValidator> constraintValidator_;
    
public:
    StandardContext();
    
    // 命名空间管理
    std::shared_ptr<NamespaceManager> getNamespaceManager() { return namespaceManager_; }
    
    // 约束验证
    std::shared_ptr<ConstraintValidator> getConstraintValidator() { return constraintValidator_; }
    
    // 验证约束
    bool validateConstraints(std::shared_ptr<Node> ast);
    
    // 可以在这里添加StandardContext特有的方法
};

} // namespace chtl

#endif // CHTL_STANDARD_CONTEXT_H