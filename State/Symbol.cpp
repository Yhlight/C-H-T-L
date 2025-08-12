#include "SymbolTable.h"
#include <sstream>

namespace CHTL {

Symbol::Symbol(const std::string& name, SymbolType type)
    : name_(name), type_(type) {
}

void Symbol::setAttribute(const std::string& key, const std::string& value) {
    attributes_[key] = value;
}

std::string Symbol::getAttribute(const std::string& key) const {
    auto it = attributes_.find(key);
    if (it != attributes_.end()) {
        return it->second;
    }
    return "";
}

bool Symbol::hasAttribute(const std::string& key) const {
    return attributes_.find(key) != attributes_.end();
}

std::string Symbol::toString() const {
    std::stringstream ss;
    ss << "Symbol[name=" << name_;
    ss << ", type=";
    
    switch (type_) {
        case SymbolType::VARIABLE:
            ss << "VARIABLE";
            break;
        case SymbolType::TEMPLATE_STYLE:
            ss << "TEMPLATE_STYLE";
            break;
        case SymbolType::TEMPLATE_ELEMENT:
            ss << "TEMPLATE_ELEMENT";
            break;
        case SymbolType::TEMPLATE_VAR:
            ss << "TEMPLATE_VAR";
            break;
        case SymbolType::CUSTOM_STYLE:
            ss << "CUSTOM_STYLE";
            break;
        case SymbolType::CUSTOM_ELEMENT:
            ss << "CUSTOM_ELEMENT";
            break;
        case SymbolType::CUSTOM_VAR:
            ss << "CUSTOM_VAR";
            break;
        case SymbolType::NAMESPACE:
            ss << "NAMESPACE";
            break;
        case SymbolType::IMPORT:
            ss << "IMPORT";
            break;
        case SymbolType::CONFIG:
            ss << "CONFIG";
            break;
        default:
            ss << "UNKNOWN";
            break;
    }
    
    if (!value_.empty()) {
        ss << ", value=\"" << value_ << "\"";
    }
    
    if (scope_) {
        ss << ", scope=" << scope_->getName();
    }
    
    if (line_ > 0) {
        ss << ", location=" << line_ << ":" << column_;
    }
    
    ss << "]";
    return ss.str();
}

} // namespace CHTL