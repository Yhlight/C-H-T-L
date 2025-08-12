#include "CJmod/CJmodProcessor.h"
#include <sstream>
#include <memory>
#include <map>

namespace chtl {
namespace cjmod {

// 简化的实现类
class CJmodProcessorImpl {
public:
    std::map<std::string, std::string> modules_;
};

static CJmodProcessorImpl* g_impl = nullptr;

// CJmodProcessor 实现
CJmodProcessor::~CJmodProcessor() {
    delete g_impl;
    g_impl = nullptr;
}

CJmodProcessor& CJmodProcessor::getInstance() {
    static CJmodProcessor instance;
    if (!g_impl) {
        g_impl = new CJmodProcessorImpl();
    }
    return instance;
}

bool CJmodProcessor::loadModule(const std::string& modulePath) {
    if (g_impl) {
        g_impl->modules_[modulePath] = "loaded";
        return true;
    }
    return false;
}

bool CJmodProcessor::loadModuleFromMemory(std::unique_ptr<CJmodModule> /*module*/) {
    // 简化实现
    return true;
}

std::string CJmodProcessor::processScript(const std::string& script, 
                                        const std::vector<std::string>& /*activeModules*/) {
    // 暂时直接返回原始脚本
    return script;
}

std::string CJmodProcessor::getRuntimeCode(const std::vector<std::string>& /*modules*/) {
    std::stringstream runtime;
    runtime << "// CJmod Runtime\n";
    runtime << "(function(window) {\n";
    runtime << "  'use strict';\n";
    runtime << "  window.CHTL = window.CHTL || {};\n";
    runtime << "  window.CHTL.modules = window.CHTL.modules || {};\n";
    runtime << "})(window);\n";
    return runtime.str();
}

std::vector<std::string> CJmodProcessor::getLoadedModules() const {
    std::vector<std::string> result;
    if (g_impl) {
        for (const auto& [name, _] : g_impl->modules_) {
            result.push_back(name);
        }
    }
    return result;
}

bool CJmodProcessor::isModuleLoaded(const std::string& name) const {
    return g_impl && g_impl->modules_.find(name) != g_impl->modules_.end();
}

void CJmodProcessor::unloadModule(const std::string& name) {
    if (g_impl) {
        g_impl->modules_.erase(name);
    }
}

void CJmodProcessor::unloadAllModules() {
    if (g_impl) {
        g_impl->modules_.clear();
    }
}

// 私有方法
std::string CJmodProcessor::applySyntaxRules(const std::string& code, 
                                            const std::vector<SyntaxRuleInternal*>& /*rules*/) {
    return code;
}

void CJmodProcessor::collectActiveRules(const std::vector<std::string>& /*moduleNames*/,
                                      std::vector<SyntaxRuleInternal*>& /*outRules*/) {
    // 空实现
}

void* CJmodProcessor::loadDynamicLibrary(const std::string& /*path*/) {
    return nullptr;
}

void CJmodProcessor::unloadDynamicLibrary(void* /*handle*/) {
    // 空实现
}

// SyntaxRuleInternal 实现
std::unique_ptr<SyntaxRuleInternal> SyntaxRuleInternal::fromBuilder(const SyntaxBuilder* /*builder*/) {
    auto rule = std::make_unique<SyntaxRuleInternal>();
    rule->name = "rule";
    rule->priority = 100;
    return rule;
}

// 集成函数
namespace integration {

void initialize() {
    CJmodProcessor::getInstance();
}

bool processImport(const std::string& /*moduleName*/, const std::string& source) {
    return CJmodProcessor::getInstance().loadModule(source);
}

void loadStandardModules() {
    // 暂时为空
}

ModuleMetadata getModuleMetadata(const std::string& moduleName) {
    ModuleMetadata metadata;
    metadata.name = moduleName;
    metadata.version = "1.0.0";
    return metadata;
}

} // namespace integration

} // namespace cjmod
} // namespace chtl