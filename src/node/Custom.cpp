#include "node/Custom.h"
#include <sstream>
#include <algorithm>

namespace chtl {

std::string Custom::getProperty(const std::string& name) const {
    auto it = properties_.find(name);
    return it != properties_.end() ? it->second : "";
}

bool Custom::hasDelete(const std::string& property) const {
    return std::find(deleteList_.begin(), deleteList_.end(), property) != deleteList_.end();
}

std::shared_ptr<Node> Custom::clone(bool deep) const {
    auto cloned = std::make_shared<Custom>(customType_, customName_);
    cloned->properties_ = properties_;
    cloned->deleteList_ = deleteList_;
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Custom::toString() const {
    std::stringstream ss;
    ss << "[Custom] ";
    
    switch (customType_) {
        case CustomType::ELEMENT:
            ss << "@Element ";
            break;
        case CustomType::STYLE:
            ss << "@Style ";
            break;
        case CustomType::VAR:
            ss << "@Var ";
            break;
    }
    
    ss << customName_;
    ss << "\n{";
    
    // 输出属性
    for (const auto& [name, value] : properties_) {
        ss << "\n  " << name << ": " << value << ";";
    }
    
    // 输出删除列表
    if (!deleteList_.empty()) {
        ss << "\n  delete ";
        for (size_t i = 0; i < deleteList_.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << deleteList_[i];
        }
        ss << ";";
    }
    
    // 输出子节点
    for (const auto& child : children_) {
        ss << "\n  " << child->toString();
    }
    
    ss << "\n}";
    
    return ss.str();
}

void Custom::accept(Visitor* visitor) {
    // 基础Visitor不支持Custom，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl