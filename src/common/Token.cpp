#include "common/Token.h"
#include "common/GlobalMap.h"

namespace chtl {

std::string Token::getTypeString() const {
    return GlobalMap::tokenTypeToString(type_);
}

} // namespace chtl