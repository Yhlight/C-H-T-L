#include "ConfigGenerator.h"

#include "../Node/Node.h"

namespace CHTL
{
    std::string ConfigGenerator::generate(const Node& root)
    {
        (void)root;
        return "# CHTL configuration generated\n";
    }
}