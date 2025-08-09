#pragma once

#include "BasicState.h"

namespace CHTL
{
    class StandardState : public BasicState
    {
    public:
        bool process(const std::string& src,
                     std::size_t& index,
                     BasicContext& context) override;
        const char* name() const noexcept override { return "StandardState"; }
    };
}