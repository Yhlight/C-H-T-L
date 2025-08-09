#pragma once

#include <string>
#include "Node.h"

namespace CHTL
{
    enum class OriginKind
    {
        Html,
        Style,
        JavaScript
    };

    class OriginNode : public Node
    {
    public:
        OriginNode() = default;
        explicit OriginNode(OriginKind kind) : kind_(kind) {}
        OriginNode(OriginKind kind, std::string name, std::string raw)
            : kind_(kind), name_(std::move(name)), rawContent_(std::move(raw)) {}

        OriginKind kind() const noexcept { return kind_; }
        void setKind(OriginKind k) noexcept { kind_ = k; }

        const std::string& name() const noexcept { return name_; }
        void setName(std::string n) { name_ = std::move(n); }

        const std::string& raw() const noexcept { return rawContent_; }
        void setRaw(std::string r) { rawContent_ = std::move(r); }

    private:
        OriginKind kind_ { OriginKind::Html };
        std::string name_ {};
        std::string rawContent_ {};
    };
}