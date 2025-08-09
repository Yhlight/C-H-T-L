#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include "Node.h"

namespace CHTL
{
    enum class OperateKind
    {
        Inherit,
        Delete,
        Insert,
        After,
        Before,
        Replace,
        AtTop,
        AtBottom,
        From,
        As,
        Except
    };

    class OperateNode : public Node
    {
    public:
        OperateNode() = default;
        explicit OperateNode(OperateKind kind) : kind_(kind) {}

        OperateKind kind() const noexcept { return kind_; }
        void setKind(OperateKind k) noexcept { kind_ = k; }

        // 目标（如选择器、名称等）
        std::string& target() { return target_; }
        const std::string& target() const { return target_; }

        // 参数（如位置、替换内容、异常列表等）
        std::vector<std::string>& args() { return args_; }
        const std::vector<std::string>& args() const { return args_; }

        // 其他键值数据（灵活扩展）
        std::map<std::string, std::string>& extras() { return extras_; }
        const std::map<std::string, std::string>& extras() const { return extras_; }

    private:
        OperateKind kind_ { OperateKind::Inherit };
        std::string target_ {};
        std::vector<std::string> args_ {};
        std::map<std::string, std::string> extras_ {};
    };
}