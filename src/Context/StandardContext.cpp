#include "Context/StandardContext.h"

namespace chtl {

StandardContext::StandardContext() : ChtlContext() {
    namespaceManager_ = std::make_shared<NamespaceManager>();
    // ConstraintValidator will be initialized lazily
}

bool StandardContext::validateConstraints(std::shared_ptr<Node> ast) {
    // Lazy initialization of constraint validator
    if (!constraintValidator_) {
        constraintValidator_ = std::make_shared<ConstraintValidator>(nullptr);
    }
    
    // Set context before validation
    if (constraintValidator_) {
        // Context might not be available as shared_ptr yet, so we pass nullptr
        // The validator will just not report errors to context
        return constraintValidator_->validateConstraints(ast);
    }
    
    return true;
}

} // namespace chtl