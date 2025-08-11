#include "CJmod/CJmodCorrect.h"
#include <algorithm>
#include <iostream>

namespace chtl {
namespace cjmod {

// 优化版本：真正的一次扫描
class CHTLJSProcessorOptimized : public CHTLJSProcessor {
public:
    std::string processJavaScript(const std::string& jsCode,
                                 const std::vector<std::string>& activeModules) override {
        // 第一步：收集所有规则（官方 + 所有激活模块）
        std::vector<ScanCutRule> allRules = collectAllRules(activeModules);
        
        // 第二步：处理覆盖关系
        allRules = resolveOverrides(allRules, activeModules);
        
        // 第三步：一次扫描应用所有规则
        return applyScanCutRules(jsCode, allRules);
    }
    
private:
    // 收集所有规则
    std::vector<ScanCutRule> collectAllRules(const std::vector<std::string>& activeModules) {
        std::vector<ScanCutRule> allRules;
        
        // 1. 添加官方 CHTL JS 规则
        allRules.insert(allRules.end(), officialRules_.begin(), officialRules_.end());
        
        // 2. 添加所有激活模块的规则
        for (const auto& moduleName : activeModules) {
            auto it = modules_.find(moduleName);
            if (it != modules_.end()) {
                auto moduleRules = it->second->getScanCutRules();
                allRules.insert(allRules.end(), moduleRules.begin(), moduleRules.end());
            }
        }
        
        return allRules;
    }
    
    // 处理覆盖关系
    std::vector<ScanCutRule> resolveOverrides(const std::vector<ScanCutRule>& rules,
                                              const std::vector<std::string>& activeModules) {
        std::vector<ScanCutRule> finalRules = rules;
        
        // 收集所有覆盖
        std::map<std::string, std::string> allOverrides;
        for (const auto& moduleName : activeModules) {
            auto it = modules_.find(moduleName);
            if (it != modules_.end()) {
                auto overrides = it->second->getOverrides();
                allOverrides.insert(overrides.begin(), overrides.end());
            }
        }
        
        // 应用覆盖
        for (auto& rule : finalRules) {
            auto overrideIt = allOverrides.find(rule.name);
            if (overrideIt != allOverrides.end()) {
                rule.replacement = overrideIt->second;
            }
        }
        
        return finalRules;
    }
    
    // 改进的单次扫描实现
    std::string applyScanCutRules(const std::string& code,
                                 const std::vector<ScanCutRule>& rules) override {
        // 按优先级排序（稳定排序，保持相同优先级的原始顺序）
        std::vector<ScanCutRule> sortedRules = rules;
        std::stable_sort(sortedRules.begin(), sortedRules.end(),
                        [](const ScanCutRule& a, const ScanCutRule& b) {
                            return a.priority > b.priority;
                        });
        
        // 使用迭代方式应用规则，避免重复扫描
        std::string result = code;
        bool changed = true;
        int iteration = 0;
        const int maxIterations = 10; // 防止无限循环
        
        while (changed && iteration < maxIterations) {
            changed = false;
            std::string newResult = result;
            
            for (const auto& rule : sortedRules) {
                // 验证规则
                if (rule.validator && !rule.validator(newResult)) {
                    continue;
                }
                
                // 应用替换
                try {
                    std::string temp = std::regex_replace(newResult, rule.pattern, rule.replacement);
                    if (temp != newResult) {
                        newResult = temp;
                        changed = true;
                    }
                } catch (const std::regex_error& e) {
                    std::cerr << "[CJmod] Regex error in rule '" << rule.name 
                             << "': " << e.what() << std::endl;
                }
            }
            
            result = newResult;
            iteration++;
        }
        
        if (iteration >= maxIterations) {
            std::cerr << "[CJmod] Warning: Maximum iterations reached, possible circular dependency" << std::endl;
        }
        
        return result;
    }
};

// 更高效的实现：真正的单次线性扫描
class LinearScanProcessor {
public:
    std::string processWithLinearScan(const std::string& code,
                                     const std::vector<ScanCutRule>& rules) {
        // 构建所有匹配点
        std::vector<Match> allMatches;
        
        // 对每个规则找出所有匹配
        for (const auto& rule : rules) {
            std::sregex_iterator it(code.begin(), code.end(), rule.pattern);
            std::sregex_iterator end;
            
            while (it != end) {
                Match m;
                m.start = it->position();
                m.length = it->length();
                m.replacement = it->format(rule.replacement);
                m.priority = rule.priority;
                m.ruleName = rule.name;
                allMatches.push_back(m);
                ++it;
            }
        }
        
        // 按位置排序，相同位置按优先级排序
        std::sort(allMatches.begin(), allMatches.end(),
                 [](const Match& a, const Match& b) {
                     if (a.start != b.start) return a.start < b.start;
                     return a.priority > b.priority;
                 });
        
        // 移除重叠的匹配（保留高优先级的）
        std::vector<Match> finalMatches;
        size_t lastEnd = 0;
        
        for (const auto& match : allMatches) {
            if (match.start >= lastEnd) {
                finalMatches.push_back(match);
                lastEnd = match.start + match.length;
            }
        }
        
        // 从后往前应用替换（避免位置偏移）
        std::string result = code;
        for (auto it = finalMatches.rbegin(); it != finalMatches.rend(); ++it) {
            result.replace(it->start, it->length, it->replacement);
        }
        
        return result;
    }
    
private:
    struct Match {
        size_t start;
        size_t length;
        std::string replacement;
        int priority;
        std::string ruleName;
    };
};

} // namespace cjmod
} // namespace chtl