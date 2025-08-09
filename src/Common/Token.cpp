#include "Common/Token.h"
#include "Common/GlobalMap.h"

namespace chtl {

std::string Token::getTypeString() const {
    return GlobalMap::tokenTypeToString(type_);
}

} // namespace chtl