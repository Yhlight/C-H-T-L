#pragma once

#include "Registry.h"

namespace CHTL
{
    class PredefinedCustomElements : public Registry
    {
    public:
        const std::unordered_set<std::string>& elements() const override { return elements_; }
        const std::unordered_set<std::string>& styles() const override { return empty_; }
        const std::unordered_set<std::string>& variables() const override { return empty_; }

    private:
        std::unordered_set<std::string> elements_ { };
        std::unordered_set<std::string> empty_ { };
    };
}