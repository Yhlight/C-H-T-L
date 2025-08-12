#include "v2/Context/ParseContext.h"
#include <sstream>
#include <stdexcept>

namespace chtl::v2 {

// ===== ParseContext 实现 =====

ParseContext::ParseContext() 
    : state_(ChtlParseState::INITIAL)
    , context_(ChtlContext::GLOBAL)
    , currentNode_(nullptr) {
}

ParseContext::~ParseContext() = default;

void ParseContext::reset() {
    state_ = ChtlParseState::INITIAL;
    context_ = ChtlContext::GLOBAL;
    currentNode_ = nullptr;
    currentLine_ = 1;
    currentColumn_ = 1;
    elementData_ = ElementData();
    declarationData_ = DeclarationData();
    
    // 清空内容缓冲
    cssContent_.clear();
    jsContent_.clear();
    textContent_.clear();
}

void ParseContext::resetElementData() {
    elementData_ = ElementData();
}

void ParseContext::resetDeclarationData() {
    declarationData_ = DeclarationData();
}

void ParseContext::resetContent() {
    cssContent_.clear();
    jsContent_.clear();
    textContent_.clear();
}

std::string ParseContext::toString() const {
    // TODO: 实现 toString
    return "ParseContext[state=" + std::string(getStateName(state_)) + "]";
}

} // namespace chtl::v2