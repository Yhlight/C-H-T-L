#include "node/Import.h"
#include <sstream>

namespace chtl {

std::string Import::getAlias(const std::string& item) const {
    auto it = aliases_.find(item);
    return it != aliases_.end() ? it->second : "";
}

std::shared_ptr<Node> Import::clone(bool deep) const {
    (void)deep; // Import节点通常不包含子节点
    auto cloned = std::make_shared<Import>(filePath_);
    cloned->importItems_ = importItems_;
    cloned->aliases_ = aliases_;
    cloned->isNamespaceImport_ = isNamespaceImport_;
    cloned->targetNamespace_ = targetNamespace_;
    return cloned;
}

std::string Import::toString() const {
    std::stringstream ss;
    ss << "[Import]";
    
    if (!filePath_.empty()) {
        ss << " \"" << filePath_ << "\"";
    }
    
    // 如果是命名空间导入
    if (isNamespaceImport_ && !targetNamespace_.empty()) {
        ss << " as " << targetNamespace_;
    } else if (!importItems_.empty()) {
        // 具体导入项
        if (isImportAll()) {
            ss << " *";
        } else {
            ss << "\n{";
            for (const auto& item : importItems_) {
                ss << "\n  from " << item;
                
                auto alias = getAlias(item);
                if (!alias.empty()) {
                    ss << " as " << alias;
                }
                ss << ";";
            }
            ss << "\n}";
        }
    }
    
    // 如果只有路径，简单格式
    if (importItems_.empty() && !isNamespaceImport_) {
        ss << ";";
    }
    
    return ss.str();
}

void Import::accept(Visitor* visitor) {
    // 基础Visitor不支持Import，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl