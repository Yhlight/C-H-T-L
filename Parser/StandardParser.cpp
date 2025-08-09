#include "StandardParser.h"

#include "../Node/Node.h"

namespace CHTL
{
    std::unique_ptr<Node> StandardParser::parse(const std::vector<Token>& tokens)
    {
        // 占位实现：返回一个空的根节点（Element: root）
        auto root = std::make_unique<Element>("root");
        (void)tokens;
        return root;
    }
}