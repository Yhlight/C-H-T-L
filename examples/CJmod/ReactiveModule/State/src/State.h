#pragma once

#include "CJmod/CJmodSubmodule.h"

namespace chtl {
namespace cjmod {

class StateSubmodule : public SubmoduleBase {
public:
    StateSubmodule() : SubmoduleBase("ReactiveModule", "State", "1.0.0") {}
    
    std::vector<ScanCutRule> getScanCutRules() const override;
    std::vector<RuntimeInjection> getRuntimeInjections() const override;
};

} // namespace cjmod
} // namespace chtl