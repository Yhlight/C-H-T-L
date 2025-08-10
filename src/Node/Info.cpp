#include "Node/Info.h"
#include "Visitor/Visitor.h"
#include <sstream>

namespace chtl {

std::shared_ptr<Node> Info::clone(bool deep) const {
    auto cloned = std::make_shared<Info>();
    
    // 复制所有属性
    cloned->properties_ = properties_;
    
    // 复制基类属性
    cloned->setTagName(getTagName());
    for (const auto& [key, value] : getAttributes()) {
        cloned->setAttribute(key, value);
    }
    
    // Info节点通常没有子节点
    if (deep) {
        for (const auto& child : getChildren()) {
            cloned->addChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Info::toString() const {
    std::stringstream ss;
    ss << "[Info]";
    
    if (!properties_.empty()) {
        ss << " {";
        bool first = true;
        for (const auto& [key, value] : properties_) {
            if (!first) ss << ", ";
            ss << key << ": \"" << value << "\"";
            first = false;
        }
        ss << "}";
    }
    
    return ss.str();
}

void Info::accept(Visitor* visitor) {
    visitor->visit(this);
}

} // namespace chtl