#pragma once

#include <string>
#include <map>
#include "Node.h"

namespace CHTL
{
    class ConfigNode : public Node
    {
    public:
        // 简化：直接存键值配置（包含 Name 子块展开后的别名设置等）
        std::map<std::string, std::string>& options() { return options_; }
        const std::map<std::string, std::string>& options() const { return options_; }

    private:
        std::map<std::string, std::string> options_ {};
    };
}