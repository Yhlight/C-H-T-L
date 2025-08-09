#pragma once

#include <string>
#include <vector>
#include "Node.h"

namespace CHTL
{
    enum class ImportKind
    {
        Html,
        Style,
        JavaScript,
        CustomStyle,
        CustomElement,
        CustomVar,
        TemplateStyle,
        TemplateElement,
        TemplateVar,
        Chtl,
        Wildcard
    };

    class ImportNode : public Node
    {
    public:
        ImportNode() = default;
        ImportNode(ImportKind kind, std::string path)
            : kind_(kind), path_(std::move(path)) {}

        ImportKind kind() const noexcept { return kind_; }
        void setKind(ImportKind k) noexcept { kind_ = k; }

        const std::string& path() const noexcept { return path_; }
        void setPath(std::string p) { path_ = std::move(p); }

        const std::string& alias() const noexcept { return alias_; }
        void setAlias(std::string a) { alias_ = std::move(a); }

        std::vector<std::string>& names() { return names_; }
        const std::vector<std::string>& names() const { return names_; }

        const std::string& fromNamespace() const noexcept { return fromNamespace_; }
        void setFromNamespace(std::string ns) { fromNamespace_ = std::move(ns); }

    private:
        ImportKind kind_ { ImportKind::Html };
        std::string path_ {};
        std::string alias_ {};
        std::vector<std::string> names_ {}; // 指定导入的名称列表（自定义/模板）
        std::string fromNamespace_ {};       // 使用 from 指定的命名空间
    };
}