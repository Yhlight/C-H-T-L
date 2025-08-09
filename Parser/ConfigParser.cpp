#include "ConfigParser.h"

#include "../Node/Node.h"

namespace CHTL
{
    std::unique_ptr<Node> ConfigParser::parse(const std::vector<Token>& tokens)
    {
        auto root = std::make_unique<Element>("config-root");
        (void)tokens;
        return root;
    }
}