#pragma once

#include <vector>
#include <memory>

#include "../Common/Token.h"
#include "../Node/Node.h"

namespace CHTL
{
    class BasicParser
    {
    public:
        virtual ~BasicParser() = default;
        virtual std::unique_ptr<Node> parse(const std::vector<Token>& tokens) = 0;
    };
}