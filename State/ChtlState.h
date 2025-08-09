#pragma once

#include "StandardState.h"

namespace CHTL
{
    class ChtlState : public StandardState
    {
    public:
        bool process(const std::string& src,
                     std::size_t& index,
                     BasicContext& context) override;
        const char* name() const noexcept override { return "ChtlState"; }
    };
}