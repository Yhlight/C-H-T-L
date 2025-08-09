#pragma once

#include <string>
#include "Node.h"

namespace CHTL
{
    enum class CustomKind
    {
        Style,
        Element,
        Var
    };

    class CustomBase : public Node
    {
    public:
        CustomBase() = default;
        explicit CustomBase(std::string name) : name_(std::move(name)) {}
        virtual ~CustomBase() = default;

        const std::string& name() const noexcept { return name_; }
        void setName(std::string n) { name_ = std::move(n); }

        virtual CustomKind kind() const noexcept = 0;

    private:
        std::string name_ {};
    };

    class CustomStyle : public CustomBase
    {
    public:
        using CustomBase::CustomBase;
        CustomKind kind() const noexcept override { return CustomKind::Style; }
    };

    class CustomElement : public CustomBase
    {
    public:
        using CustomBase::CustomBase;
        CustomKind kind() const noexcept override { return CustomKind::Element; }
    };

    class CustomVar : public CustomBase
    {
    public:
        using CustomBase::CustomBase;
        CustomKind kind() const noexcept override { return CustomKind::Var; }
    };
}