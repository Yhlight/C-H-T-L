#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <optional>

#include "Token.h"

namespace CHTL
{
    class GlobalMap
    {
    public:
        // TokenType <-> string
        static const std::map<std::string, TokenType>& keywordToTokenType();
        static const std::map<TokenType, std::string>& tokenTypeToKeyword();

        // 查找函数
        static std::optional<TokenType> findTokenTypeByKeyword(const std::string& keyword);
        static std::optional<std::string> findKeywordByTokenType(TokenType type);

    private:
        // 不允许实例化
        GlobalMap() = delete;
    };
}