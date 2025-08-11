#include "Node/Origin.h"
#include <sstream>

namespace chtl {

std::string Origin::getTypeString() const {
    switch (originType_) {
        case OriginType::HTML:
            return "@Html";
        case OriginType::STYLE:
            return "@Style";
        case OriginType::JAVASCRIPT:
            return "@JavaScript";
        default:
            return "@Unknown";
    }
}

std::shared_ptr<Node> Origin::clone(bool deep) const {
    (void)deep; // Origin节点通常不包含子节点
    auto cloned = std::make_shared<Origin>(originType_, originName_);
    cloned->content_ = content_;
    cloned->isInline_ = isInline_;
    return cloned;
}

std::string Origin::toString() const {
    std::stringstream ss;
    
    ss << "[Origin] " << getTypeString();
    
    // 添加名称（如果有）
    if (!originName_.empty()) {
        ss << " " << originName_;
    }
    
    if (isInline_) {
        // 内联形式
        ss << ";";
    } else {
        // 块形式
        ss << "\n{";
        
        if (!content_.empty()) {
            // 将内容按行分割并缩进
            std::istringstream iss(content_);
            std::string line;
            while (std::getline(iss, line)) {
                ss << "\n  " << line;
            }
        }
        
        ss << "\n}";
    }
    
    return ss.str();
}

void Origin::accept(Visitor* visitor) {
    // 基础Visitor不支持Origin，需要使用ExtendedVisitor
    (void)visitor;
}

} // namespace chtl