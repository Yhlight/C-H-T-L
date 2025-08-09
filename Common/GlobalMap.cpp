#include "GlobalMap.h"

#include <algorithm>

namespace CHTL
{
    namespace
    {
        // 使用函数静态局部变量确保单一定义与惰性初始化
        const std::map<std::string, TokenType>& getKeywordToTokenTypeMap()
        {
            static const std::map<std::string, TokenType> mapInstance = {
                {"text", TokenType::KeywordText},
                {"style", TokenType::KeywordStyle},
                {"inherit", TokenType::KeywordInherit},
                {"delete", TokenType::KeywordDelete},
                {"insert", TokenType::KeywordInsert},
                {"after", TokenType::KeywordAfter},
                {"before", TokenType::KeywordBefore},
                {"replace", TokenType::KeywordReplace},
                {"at top", TokenType::KeywordAtTop},
                {"at bottom", TokenType::KeywordAtBottom},
                {"from", TokenType::KeywordFrom},
                {"as", TokenType::KeywordAs},
                {"except", TokenType::KeywordExcept},

                // 名称组
                {"@Style", TokenType::KeywordStyle}, // 用于模板/自定义标识
                {"@Element", TokenType::Identifier}, // 作为类型标识，保持为标识符或另设类型
                {"@Var", TokenType::Identifier},
                {"[Template]", TokenType::KeywordTemplate},
                {"[Custom]", TokenType::KeywordCustom},
                {"[Origin]", TokenType::KeywordOrigin},
                {"[Import]", TokenType::KeywordImport},
                {"[Namespace]", TokenType::KeywordNamespace},
                {"[Configuration]", TokenType::KeywordConfiguration},
            };
            return mapInstance;
        }

        const std::map<TokenType, std::string>& getTokenTypeToKeywordMap()
        {
            static const std::map<TokenType, std::string> mapInstance = {
                {TokenType::KeywordText, "text"},
                {TokenType::KeywordStyle, "style"},
                {TokenType::KeywordTemplate, "[Template]"},
                {TokenType::KeywordCustom, "[Custom]"},
                {TokenType::KeywordOrigin, "[Origin]"},
                {TokenType::KeywordImport, "[Import]"},
                {TokenType::KeywordNamespace, "[Namespace]"},
                {TokenType::KeywordConfiguration, "[Configuration]"},
                {TokenType::KeywordInherit, "inherit"},
                {TokenType::KeywordDelete, "delete"},
                {TokenType::KeywordInsert, "insert"},
                {TokenType::KeywordAfter, "after"},
                {TokenType::KeywordBefore, "before"},
                {TokenType::KeywordReplace, "replace"},
                {TokenType::KeywordAtTop, "at top"},
                {TokenType::KeywordAtBottom, "at bottom"},
                {TokenType::KeywordFrom, "from"},
                {TokenType::KeywordAs, "as"},
                {TokenType::KeywordExcept, "except"},
            };
            return mapInstance;
        }
    }

    const std::map<std::string, TokenType>& GlobalMap::keywordToTokenType()
    {
        return getKeywordToTokenTypeMap();
    }

    const std::map<TokenType, std::string>& GlobalMap::tokenTypeToKeyword()
    {
        return getTokenTypeToKeywordMap();
    }

    std::optional<TokenType> GlobalMap::findTokenTypeByKeyword(const std::string& keyword)
    {
        const auto& m = getKeywordToTokenTypeMap();
        auto it = m.find(keyword);
        if (it == m.end())
            return std::nullopt;
        return it->second;
    }

    std::optional<std::string> GlobalMap::findKeywordByTokenType(TokenType type)
    {
        const auto& m = getTokenTypeToKeywordMap();
        auto it = m.find(type);
        if (it == m.end())
            return std::nullopt;
        return it->second;
    }
}