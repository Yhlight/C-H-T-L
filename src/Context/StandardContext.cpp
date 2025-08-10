#include "Context/StandardContext.h"

namespace chtl {

StandardContext::StandardContext() : ChtlContext() {
    namespaceManager_ = std::make_shared<NamespaceManager>();
}

} // namespace chtl