#pragma once

#include "BasicGenerator.h"

namespace CHTL
{
    class StandardGenerator : public BasicGenerator
    {
    public:
        std::string generate(const Node& root) override;
    };
}