#include "Segment.h"
#include <sstream>

namespace CHTL {

std::string Segment::toString() const {
    std::stringstream ss;
    ss << "Segment[";
    
    // 语言类型
    switch (type_) {
        case LanguageType::CHTL:
            ss << "type=CHTL";
            break;
        case LanguageType::CSS:
            ss << "type=CSS";
            break;
        case LanguageType::JAVASCRIPT:
            ss << "type=JS";
            break;
        case LanguageType::CHTL_JAVASCRIPT:
            ss << "type=CHTL_JS";
            break;
        case LanguageType::HTML:
            ss << "type=HTML";
            break;
        default:
            ss << "type=UNKNOWN";
            break;
    }
    
    // 位置信息
    ss << ", location=(" << startLine_ << ":" << startColumn_ 
       << "-" << endLine_ << ":" << endColumn_ << ")";
    
    // 内容长度
    ss << ", length=" << content_.length();
    
    // 上下文
    if (!context_.empty()) {
        ss << ", context=" << context_;
    }
    
    // 所属元素
    if (!ownerElement_.empty()) {
        ss << ", owner=" << ownerElement_;
    }
    
    // 父段
    if (parent_) {
        ss << ", hasParent=true";
    }
    
    ss << "]";
    return ss.str();
}

} // namespace CHTL