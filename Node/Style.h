#pragma once

#include <string>
#include <map>
#include <vector>
#include "Node.h"

namespace CHTL
{
    enum class StyleScope
    {
        Local,
        Global
    };

    class StyleBase : public Node
    {
    public:
        virtual ~StyleBase() = default;
        virtual StyleScope scope() const noexcept = 0;
    };

    class LocalStyle : public StyleBase
    {
    public:
        StyleScope scope() const noexcept override { return StyleScope::Local; }

        // 内联样式属性
        std::map<std::string, std::string>& inlineProperties() { return inlineProperties_; }
        const std::map<std::string, std::string>& inlineProperties() const { return inlineProperties_; }

        // 选择器（类、id、伪类、伪元素），用于自动加入全局样式块
        std::vector<std::string>& selectors() { return selectors_; }
        const std::vector<std::string>& selectors() const { return selectors_; }

    private:
        std::map<std::string, std::string> inlineProperties_ {};
        std::vector<std::string> selectors_ {};
    };

    class GlobalStyle : public StyleBase
    {
    public:
        StyleScope scope() const noexcept override { return StyleScope::Global; }
        // 简化处理：保存原始 CSS 文本，后续可结构化
        const std::string& cssText() const noexcept { return cssText_; }
        void setCssText(std::string s) { cssText_ = std::move(s); }
    private:
        std::string cssText_ {};
    };
}