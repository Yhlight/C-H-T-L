#include "Node/Export.h"
// #include "Visitor/Visitor.h" // Not implemented yet
#include <sstream>

namespace chtl {

std::shared_ptr<Node> Export::clone(bool deep) const {
    auto cloned = std::make_shared<Export>();
    
    // 复制导出项
    cloned->exportItems_ = exportItems_;
    cloned->fromNamespace_ = fromNamespace_;
    
    // 复制基类属性
    cloned->setTagName(getTagName());
    // Export nodes don't have attributes like Element nodes
    
    // Export节点通常没有子节点
    if (deep) {
        for (const auto& child : getChildren()) {
            cloned->addChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Export::toString() const {
    std::stringstream ss;
    ss << "[Export]";
    
    if (!fromNamespace_.empty()) {
        ss << " from " << fromNamespace_;
    }
    
    if (!exportItems_.empty()) {
        ss << " {";
        bool first = true;
        for (const auto& item : exportItems_) {
            if (!first) ss << ", ";
            
            switch (item.type) {
                case ExportType::ELEMENT: ss << "@Element "; break;
                case ExportType::STYLE: ss << "@Style "; break;
                case ExportType::VAR: ss << "@Var "; break;
                case ExportType::NAMESPACE: ss << "namespace "; break;
                case ExportType::ALL: ss << "*"; break;
            }
            
            if (item.type != ExportType::ALL) {
                ss << item.name;
                if (!item.alias.empty()) {
                    ss << " as " << item.alias;
                }
            }
            
            first = false;
        }
        ss << "}";
    }
    
    return ss.str();
}

void Export::accept(Visitor* visitor) {
    (void)visitor; // Suppress unused parameter warning
    // TODO: Implement when Visitor class is added
    // visitor->visit(this);
}

} // namespace chtl