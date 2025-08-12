#include "CJmod/CJmodSimple.h"
#include <algorithm>
#include <unordered_map>

namespace chtl {
namespace cjmod {

// CJmodLoader 内部实现类
class CJmodLoaderImpl {
public:
    std::unordered_map<std::string, bool> loadedModules_;
};

// CJmodLoader 实现
CJmodLoader::CJmodLoader() : impl_(new CJmodLoaderImpl()) {}
CJmodLoader::~CJmodLoader() { delete impl_; }

CJmodLoader& CJmodLoader::getInstance() {
    static CJmodLoader instance;
    return instance;
}
    
void CJmodLoader::initializeBuiltins() {
    // 注册内置模块
    impl_->loadedModules_["reactive"] = true;
    impl_->loadedModules_["animate"] = true;
    impl_->loadedModules_["delegate"] = true;
}

bool CJmodLoader::loadModule(const std::string& name) {
    impl_->loadedModules_[name] = true;
    return true;
}

bool CJmodLoader::isModuleLoaded(const std::string& name) const {
    return impl_->loadedModules_.find(name) != impl_->loadedModules_.end();
}

// CHTLJSProcessor 实现
CHTLJSProcessor& CHTLJSProcessor::getInstance() {
    static CHTLJSProcessor instance;
    return instance;
}

std::string CHTLJSProcessor::processJavaScript(const std::string& jsCode, 
                                             const std::vector<std::string>& /*modules*/) {
    // 暂时直接返回原始代码
    return jsCode;
}

std::string CHTLJSProcessor::getCombinedRuntime(const std::vector<std::string>& modules) {
        // 返回基础运行时代码
        return R"(
// CJmod Runtime (Simplified)
(function(window) {
    window.CHTL = window.CHTL || {};
    window.CHTL.modules = window.CHTL.modules || {};
    
    // Module registration
    window.CHTL.register = function(name, module) {
        window.CHTL.modules[name] = module;
    };
    
    // Reactive module stub
    if ()" + std::to_string(std::find(modules.begin(), modules.end(), "reactive") != modules.end()) + R"() {
        window.CHTL.register('reactive', {
            reactive: function(value) {
                return { value: value };
            }
        });
    }
})(window);
)";
}

} // namespace cjmod
} // namespace chtl