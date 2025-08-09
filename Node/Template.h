#pragma once

#include <string>
#include "Node.h"

namespace CHTL
{
    enum class TemplateKind
    {
        Style,
        Element,
        Var
    };

    class TemplateBase : public Node
    {
    public:
        TemplateBase() = default;
        explicit TemplateBase(std::string name) : name_(std::move(name)) {}
        virtual ~TemplateBase() = default;

        const std::string& name() const noexcept { return name_; }
        void setName(std::string n) { name_ = std::move(n); }

        virtual TemplateKind kind() const noexcept = 0;

    private:
        std::string name_ {};
    };

    class TemplateStyle : public TemplateBase
    {
    public:
        using TemplateBase::TemplateBase;
        TemplateKind kind() const noexcept override { return TemplateKind::Style; }
    };

    class TemplateElement : public TemplateBase
    {
    public:
        using TemplateBase::TemplateBase;
        TemplateKind kind() const noexcept override { return TemplateKind::Element; }
    };

    class TemplateVar : public TemplateBase
    {
    public:
        using TemplateBase::TemplateBase;
        TemplateKind kind() const noexcept override { return TemplateKind::Var; }
    };
}