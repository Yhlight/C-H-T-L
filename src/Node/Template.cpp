#include "Node/Template.h"
#include <sstream>

namespace chtl {

std::string Template::getParameter(const std::string& name) const {
    auto it = parameters_.find(name);
    return it != parameters_.end() ? it->second : "";
}

std::shared_ptr<Node> Template::clone(bool deep) const {
    auto cloned = std::make_shared<Template>(templateType_, templateName_);
    cloned->parameters_ = parameters_;
    cloned->inheritFrom_ = inheritFrom_;
    cloned->isExplicitInherit_ = isExplicitInherit_;
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Template::toString() const {
    std::stringstream ss;
    ss << "[Template] ";
    
    switch (templateType_) {
        case TemplateType::STYLE:
            ss << "@Style ";
            break;
        case TemplateType::ELEMENT:
            ss << "@Element ";
            break;
        case TemplateType::VAR:
            ss << "@Var ";
            break;
    }
    
    ss << templateName_;
    
    // 输出参数
    if (!parameters_.empty()) {
        ss << "(";
        bool first = true;
        for (const auto& [name, value] : parameters_) {
            if (!first) ss << ", ";
            ss << name << ": " << value;
            first = false;
        }
        ss << ")";
    }
    
    // 输出继承
    if (!inheritFrom_.empty()) {
        ss << " : ";
        for (size_t i = 0; i < inheritFrom_.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << inheritFrom_[i];
        }
    }
    
    ss << "\n{";
    
    // 输出子节点内容
    for (const auto& child : children_) {
        ss << "\n  " << child->toString();
    }
    
    ss << "\n}";
    
    return ss.str();
}

void Template::accept(Visitor* visitor) {
    // 基础Visitor不支持Template，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl