#pragma once

#include "BasicGenerator.h"

namespace CHTL
{
    class ConfigGenerator : public BasicGenerator
    {
    public:
        std::string generate(const Node& root) override;
    };
}