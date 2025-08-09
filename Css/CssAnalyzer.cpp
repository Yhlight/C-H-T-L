#include "CssAnalyzer.h"

#include <cctype>

namespace CHTL
{
    namespace
    {
        bool isIdentChar(char c)
        {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-' || c == ':';
        }
    }

    CssFindings CssAnalyzer::analyze(std::string_view css) const
    {
        CssFindings out;
        const std::size_t n = css.size();

        // 扫描选择器中的 .class 与 #id（在花括号前）
        for (std::size_t i = 0; i < n; ++i)
        {
            char c = css[i];
            if (c == '.' || c == '#')
            {
                std::size_t j = i + 1;
                std::string name;
                while (j < n && isIdentChar(css[j]))
                {
                    name.push_back(css[j]);
                    ++j;
                }
                if (!name.empty())
                {
                    if (c == '.')
                    {
                        if (out.classSelectors.insert(name).second)
                            out.all.push_back({ CssSymbolKind::ClassSelector, name });
                    }
                    else
                    {
                        if (out.idSelectors.insert(name).second)
                            out.all.push_back({ CssSymbolKind::IdSelector, name });
                    }
                }
                i = j;
            }
        }

        // 扫描属性名（形如 key: value; 的 key）
        for (std::size_t i = 0; i < n; )
        {
            // 跳过空白与分隔
            while (i < n && std::isspace(static_cast<unsigned char>(css[i]))) ++i;
            std::size_t start = i;
            while (i < n && isIdentChar(css[i])) ++i;
            if (i > start)
            {
                // 跳过空白
                std::size_t k = i;
                while (k < n && std::isspace(static_cast<unsigned char>(css[k]))) ++k;
                if (k < n && css[k] == ':')
                {
                    std::string prop(css.substr(start, i - start));
                    if (!prop.empty())
                    {
                        if (out.propertyNames.insert(prop).second)
                            out.all.push_back({ CssSymbolKind::PropertyName, prop });
                    }
                    i = k + 1; // 跳过冒号
                    continue;
                }
            }
            ++i;
        }

        return out;
    }
}