#pragma once

#include "CJmod/CJmodSubmodule.h"
#include <memory>
#include <unordered_map>

namespace chtl {
namespace cjmod {

class ReactiveModule : public ICJmodWithSubmodules {
private:
    std::unordered_map<std::string, std::shared_ptr<ICJmod>> submodules_;
    
public:
    ReactiveModule();
    virtual ~ReactiveModule() = default;
    
    // ICJmod 基础接口
    std::string getName() const override { return "ReactiveModule"; }
    std::string getVersion() const override { return "1.0.0"; }
    
    std::vector<ScanCutRule> getScanCutRules() const override;
    std::vector<RuntimeInjection> getRuntimeInjections() const override;
    std::unordered_map<std::string, std::string> getOverrides() const override;
    
    // ICJmodWithSubmodules 接口
    std::vector<SubmoduleInfo> getSubmodules() const override;
    std::shared_ptr<ICJmod> loadSubmodule(const std::string& name) override;
    bool hasSubmodule(const std::string& name) const override;
    
private:
    void initializeSubmodules();
};

// 导出函数
extern "C" {
    std::shared_ptr<ICJmod> createReactiveModule();
}

} // namespace cjmod
} // namespace chtl