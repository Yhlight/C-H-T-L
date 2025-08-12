#include "CJmod/CJmodCorrect.h"
#include <algorithm>
#include <iostream>

namespace chtl {
namespace cjmod {

CHTLJSProcessor& CHTLJSProcessor::getInstance() {
    static CHTLJSProcessor instance;
    return instance;
}

void CHTLJSProcessor::registerModule(std::shared_ptr<ICJmod> module) {
    if (module) {
        modules_[module->getName()] = module;
        std::cout << "[CJmod] Registered module: " << module->getName() << std::endl;
    }
}

std::string CHTLJSProcessor::processJavaScript(const std::string& jsCode,
                                               const std::vector<std::string>& activeModules) {
    std::string result = jsCode;
    
    // 首先应用官方 CHTL JS 规则
    result = applyScanCutRules(result, officialRules_);
    
    // 然后应用每个活跃模块的规则
    for (const auto& moduleName : activeModules) {
        auto it = modules_.find(moduleName);
        if (it != modules_.end()) {
            auto module = it->second;
            
            // 获取模块的覆盖规则
            auto overrides = module->getOverrides();
            if (!overrides.empty()) {
                // 覆盖官方规则
                std::vector<ScanCutRule> modifiedRules = officialRules_;
                for (auto& rule : modifiedRules) {
                    auto overrideIt = overrides.find(rule.name);
                    if (overrideIt != overrides.end()) {
                        rule.replacement = overrideIt->second;
                    }
                }
                result = applyScanCutRules(result, modifiedRules);
            }
            
            // 应用模块自定义规则
            auto moduleRules = module->getScanCutRules();
            result = applyScanCutRules(result, moduleRules);
        }
    }
    
    return result;
}

std::string CHTLJSProcessor::getCombinedRuntime(const std::vector<std::string>& activeModules) {
    std::string runtime;
    
    // 收集所有运行时代码
    std::vector<RuntimeInjection> beforeInjections;
    std::vector<RuntimeInjection> afterInjections;
    
    for (const auto& moduleName : activeModules) {
        auto it = modules_.find(moduleName);
        if (it != modules_.end()) {
            auto injections = it->second->getRuntimeInjections();
            for (const auto& injection : injections) {
                if (injection.position == "before") {
                    beforeInjections.push_back(injection);
                } else {
                    afterInjections.push_back(injection);
                }
            }
        }
    }
    
    // 先注入 "before" 代码
    for (const auto& injection : beforeInjections) {
        runtime += injection.code + "\n\n";
    }
    
    // 后注入 "after" 代码
    for (const auto& injection : afterInjections) {
        runtime += injection.code + "\n\n";
    }
    
    return runtime;
}

std::string CHTLJSProcessor::applyScanCutRules(const std::string& code,
                                               const std::vector<ScanCutRule>& rules) {
    // 按优先级排序规则（高优先级先执行）
    std::vector<ScanCutRule> sortedRules = rules;
    std::sort(sortedRules.begin(), sortedRules.end(),
              [](const ScanCutRule& a, const ScanCutRule& b) {
                  return a.priority > b.priority;
              });
    
    std::string result = code;
    
    // 应用每个规则
    for (const auto& rule : sortedRules) {
        // 如果有验证函数，先验证
        if (rule.validator && !rule.validator(result)) {
            continue;
        }
        
        // 使用 regex_replace 进行替换
        try {
            result = std::regex_replace(result, rule.pattern, rule.replacement);
        } catch (const std::regex_error& e) {
            std::cerr << "[CJmod] Regex error in rule '" << rule.name << "': " << e.what() << std::endl;
        }
    }
    
    return result;
}

} // namespace cjmod
} // namespace chtl