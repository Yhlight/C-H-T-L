#include "ChtlState.h"

#include <string>
#include "../Common/GlobalMap.h"
#include "../Context/BasicContext.h"

namespace CHTL
{
    bool ChtlState::process(const std::string& src, std::size_t& index, BasicContext& context)
    {
        // 复用 StandardState 的处理
        const std::size_t before = index;
        const bool ok = StandardState::process(src, index, context);
        if (!ok) return false;

        // CE对等式：在上下文层面解释，而不是词法替换
        // 这里保持 token 为 ':' 或 '='，由后续语法阶段解释

        return true;
    }
}