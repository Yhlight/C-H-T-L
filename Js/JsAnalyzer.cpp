#include "JsAnalyzer.h"

#include <cctype>

namespace CHTL
{
    namespace
    {
        bool isIdentStart(char c)
        {
            return std::isalpha(static_cast<unsigned char>(c)) || c == '_' || c == '$';
        }
        bool isIdentChar(char c)
        {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '$';
        }
        void scanWord(std::string_view s, std::size_t& i, std::string& out)
        {
            out.clear();
            if (i < s.size() && isIdentStart(s[i]))
            {
                out.push_back(s[i++]);
                while (i < s.size() && isIdentChar(s[i])) out.push_back(s[i++]);
            }
        }
    }

    JsFindings JsAnalyzer::analyze(std::string_view js) const
    {
        JsFindings out;
        const std::size_t n = js.size();

        for (std::size_t i = 0; i < n; ++i)
        {
            // function <name>
            if (i + 8 < n && js.compare(i, 8, "function") == 0 && std::isspace(static_cast<unsigned char>(js[i+8])))
            {
                std::size_t k = i + 8;
                while (k < n && std::isspace(static_cast<unsigned char>(js[k]))) ++k;
                std::string name;
                scanWord(js, k, name);
                if (!name.empty()) out.functionNames.insert(name);
            }

            // const/let/var <name> = (...) => 作为函数（粗略）
            if ((i + 5 < n && js.compare(i, 5, "const") == 0) ||
                (i + 3 < n && js.compare(i, 3, "let") == 0) ||
                (i + 3 < n && js.compare(i, 3, "var") == 0))
            {
                std::size_t k = i;
                while (k < n && !std::isspace(static_cast<unsigned char>(js[k]))) ++k; // 跳关键字
                while (k < n && std::isspace(static_cast<unsigned char>(js[k]))) ++k;
                std::string name;
                scanWord(js, k, name);
                while (k < n && std::isspace(static_cast<unsigned char>(js[k]))) ++k;
                if (k < n && js[k] == '=')
                {
                    if (!name.empty()) out.functionNames.insert(name);
                }
            }

            // addEventListener('click' ...)
            if (i + 16 < n && js.compare(i, 16, "addEventListener") == 0)
            {
                std::size_t k = i + 16;
                k = js.find('(', k);
                if (k != std::string_view::npos && k + 1 < n)
                {
                    ++k;
                    if (k < n && (js[k] == '\'' || js[k] == '"'))
                    {
                        char q = js[k++];
                        std::string evt;
                        while (k < n && js[k] != q) evt.push_back(js[k++]);
                        if (!evt.empty()) out.eventNames.insert(evt);
                    }
                }
            }

            // ->listen({ click: ..., mouseenter: ... })（CHTL增强）
            if (i + 9 < n && js.compare(i, 9, "->listen(") == 0)
            {
                std::size_t k = i + 9;
                k = js.find('{', k);
                if (k != std::string_view::npos)
                {
                    ++k;
                    while (k < n)
                    {
                        while (k < n && std::isspace(static_cast<unsigned char>(js[k]))) ++k;
                        std::string evt;
                        // 读取键直到冒号或非标识
                        while (k < n && (std::isalpha(static_cast<unsigned char>(js[k])) || js[k] == '-' ))
                            evt.push_back(js[k++]);
                        while (k < n && std::isspace(static_cast<unsigned char>(js[k]))) ++k;
                        if (k < n && js[k] == ':')
                        {
                            if (!evt.empty()) out.eventNames.insert(evt);
                            ++k;
                        }
                        // 跳到下一个逗号或结束
                        std::size_t nextComma = js.find_first_of("},", k);
                        if (nextComma == std::string_view::npos) break;
                        if (js[nextComma] == '}') { k = nextComma + 1; break; }
                        k = nextComma + 1;
                    }
                }
            }

            // 选择器：document.querySelector('...') / {{...}}（增强）
            if (i + 17 < n && js.compare(i, 17, "querySelector(") == 0)
            {
                std::size_t k = i + 17;
                if (k < n && (js[k] == '\'' || js[k] == '"'))
                {
                    char q = js[k++];
                    std::string sel;
                    while (k < n && js[k] != q) sel.push_back(js[k++]);
                    if (!sel.empty()) out.selectors.insert(sel);
                }
            }
            if (i + 1 < n && js[i] == '{' && js[i+1] == '{')
            {
                std::size_t k = i + 2;
                std::string sel;
                while (k + 1 < n && !(js[k] == '}' && js[k+1] == '}')) sel.push_back(js[k++]);
                if (!sel.empty()) out.selectors.insert(sel);
            }
        }

        return out;
    }
}