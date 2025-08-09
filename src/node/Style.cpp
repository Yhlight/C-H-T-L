#include "node/Style.h"
#include <sstream>

namespace chtl {

std::string Style::getRule(const std::string& property) const {
    auto it = rules_.find(property);
    return it != rules_.end() ? it->second : "";
}

std::shared_ptr<Node> Style::clone(bool deep) const {
    auto cloned = std::make_shared<Style>(scope_);
    cloned->cssContent_ = cssContent_;
    cloned->rules_ = rules_;
    cloned->selectors_ = selectors_;
    cloned->isScoped_ = isScoped_;
    cloned->parentElement_ = parentElement_;
    
    if (deep) {
        for (const auto& child : children_) {
            cloned->appendChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Style::toString() const {
    std::stringstream ss;
    
    if (scope_ == StyleScope::GLOBAL) {
        ss << "style";
        if (isScoped_) {
            ss << " scoped";
        }
        ss << "\n{";
    } else {
        // 局部样式，缩进显示
        ss << "style\n  {";
    }
    
    // 如果有原始CSS内容，直接输出
    if (!cssContent_.empty()) {
        std::istringstream iss(cssContent_);
        std::string line;
        while (std::getline(iss, line)) {
            ss << "\n  ";
            if (scope_ == StyleScope::LOCAL) {
                ss << "  "; // 额外缩进
            }
            ss << line;
        }
    } else {
        // 输出选择器和规则
        if (!selectors_.empty() && !rules_.empty()) {
            for (const auto& selector : selectors_) {
                ss << "\n  ";
                if (scope_ == StyleScope::LOCAL) {
                    ss << "  ";
                }
                ss << selector << " {";
                
                for (const auto& [property, value] : rules_) {
                    ss << "\n    ";
                    if (scope_ == StyleScope::LOCAL) {
                        ss << "  ";
                    }
                    ss << property << ": " << value << ";";
                }
                
                ss << "\n  ";
                if (scope_ == StyleScope::LOCAL) {
                    ss << "  ";
                }
                ss << "}";
            }
        } else if (!rules_.empty()) {
            // 内联样式规则
            for (const auto& [property, value] : rules_) {
                ss << "\n  ";
                if (scope_ == StyleScope::LOCAL) {
                    ss << "  ";
                }
                ss << property << ": " << value << ";";
            }
        }
    }
    
    // 输出子节点（通常style节点不应该有子节点）
    for (const auto& child : children_) {
        ss << "\n  ";
        if (scope_ == StyleScope::LOCAL) {
            ss << "  ";
        }
        ss << child->toString();
    }
    
    ss << "\n";
    if (scope_ == StyleScope::LOCAL) {
        ss << "  ";
    }
    ss << "}";
    
    return ss.str();
}

void Style::accept(Visitor* visitor) {
    // 基础Visitor不支持Style，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl