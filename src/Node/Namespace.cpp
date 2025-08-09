#include "Node/Namespace.h"
#include <sstream>

namespace chtl {

std::string Namespace::getFullPath() const {
    std::stringstream ss;
    for (size_t i = 0; i < namespacePath_.size(); ++i) {
        if (i > 0) ss << "::";
        ss << namespacePath_[i];
    }
    if (!namespacePath_.empty() && !namespaceName_.empty()) {
        ss << "::";
    }
    ss << namespaceName_;
    return ss.str();
}

std::shared_ptr<Node> Namespace::clone(bool deep) const {
    auto cloned = std::make_shared<Namespace>(namespaceName_);
    cloned->namespacePath_ = namespacePath_;
    cloned->isExport_ = isExport_;
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Namespace::toString() const {
    std::stringstream ss;
    
    if (isExport_) {
        ss << "export ";
    }
    
    ss << "[Namespace] " << namespaceName_;
    ss << "\n{";
    
    // 输出子节点内容
    for (const auto& child : children_) {
        std::string childStr = child->toString();
        
        // 为每行添加缩进
        std::istringstream iss(childStr);
        std::string line;
        while (std::getline(iss, line)) {
            ss << "\n  " << line;
        }
    }
    
    ss << "\n}";
    
    return ss.str();
}

void Namespace::accept(Visitor* visitor) {
    // 基础Visitor不支持Namespace，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl