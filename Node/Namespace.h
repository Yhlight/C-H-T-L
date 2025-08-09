#pragma once

#include <string>
#include "Node.h"

namespace CHTL
{
    class NamespaceNode : public Node
    {
    public:
        NamespaceNode() = default;
        explicit NamespaceNode(std::string name) : name_(std::move(name)) {}

        const std::string& name() const noexcept { return name_; }
        void setName(std::string n) { name_ = std::move(n); }

    private:
        std::string name_ {};
    };
}