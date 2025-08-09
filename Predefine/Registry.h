#pragma once

#include <string>
#include <unordered_set>

namespace CHTL
{
    class Registry
    {
    public:
        virtual ~Registry() = default;

        virtual const std::unordered_set<std::string>& elements() const = 0;
        virtual const std::unordered_set<std::string>& styles() const = 0;
        virtual const std::unordered_set<std::string>& variables() const = 0;
    };
}