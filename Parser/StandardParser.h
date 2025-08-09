#pragma once

#include "BasicParser.h"

namespace CHTL
{
    class StandardParser : public BasicParser
    {
    public:
        std::unique_ptr<Node> parse(const std::vector<Token>& tokens) override;
    };
}