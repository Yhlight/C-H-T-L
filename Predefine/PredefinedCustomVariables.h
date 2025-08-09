#pragma once

#include "Registry.h"

namespace CHTL
{
    class PredefinedCustomVariables : public Registry
    {
    public:
        const std::unordered_set<std::string>& elements() const override { return empty_; }
        const std::unordered_set<std::string>& styles() const override { return empty_; }
        const std::unordered_set<std::string>& variables() const override { return variables_; }

    private:
        std::unordered_set<std::string> variables_ { };
        std::unordered_set<std::string> empty_ { };
    };
}