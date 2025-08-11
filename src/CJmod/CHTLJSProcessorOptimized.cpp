#include "CJmod/CHTLJSProcessorOptimized.h"
#include <algorithm>
#include <sstream>
#include <iostream>

namespace chtl {
namespace cjmod {

// OptimizedMatcher 实现
void CHTLJSProcessorOptimized::OptimizedMatcher::addRule(const ScanCutRule& rule, size_t id) {
    CompiledRule compiled;
    compiled.rule = rule;
    compiled.regex = std::regex(rule.pattern);
    compiled.id = id;
    compiledRules_.push_back(compiled);
    skipRegexDirty_ = true;
}

CHTLJSProcessorOptimized::MatchResult 
CHTLJSProcessorOptimized::OptimizedMatcher::findNextMatch(const std::string& text, size_t startPos) {
    MatchResult bestMatch;
    bestMatch.position = std::string::npos;
    
    // 找到最早的匹配
    for (auto& compiledRule : compiledRules_) {
        std::smatch match;
        std::string::const_iterator searchStart = text.begin() + startPos;
        
        if (std::regex_search(searchStart, text.end(), match, compiledRule.regex)) {
            size_t matchPos = startPos + match.position();
            
            // 如果这个匹配更早，或者位置相同但优先级更高，则使用它
            if (matchPos < bestMatch.position || 
                (matchPos == bestMatch.position && 
                 compiledRule.rule.priority > bestMatch.rule->priority)) {
                bestMatch.found = true;
                bestMatch.position = matchPos;
                bestMatch.length = match.length();
                bestMatch.rule = &compiledRule.rule;
                bestMatch.match = match;
            }
        }
    }
    
    return bestMatch;
}

void CHTLJSProcessorOptimized::OptimizedMatcher::clear() {
    compiledRules_.clear();
    skipRegexDirty_ = true;
}

void CHTLJSProcessorOptimized::OptimizedMatcher::rebuildSkipRegex() {
    // TODO: 构建组合的跳过正则表达式以优化性能
    skipRegexDirty_ = false;
}

// CHTLJSProcessorOptimized 实现
CHTLJSProcessorOptimized::CHTLJSProcessorOptimized() {}

CHTLJSProcessorOptimized::~CHTLJSProcessorOptimized() {}

void CHTLJSProcessorOptimized::registerModule(const std::string& name, 
                                             std::shared_ptr<ICJmod> module) {
    modules_[name] = module;
}

std::string CHTLJSProcessorOptimized::process(const std::string& jsCode,
                                             const std::vector<std::string>& activeModules) {
    Timer totalTimer(stats_.scanTime);
    
    // 检查缓存
    if (cacheEnabled_) {
        size_t hash = calculateHash(jsCode, activeModules);
        auto cacheIt = processCache_.find(hash);
        if (cacheIt != processCache_.end()) {
            return cacheIt->second;
        }
    }
    
    // 收集所有规则
    auto allRules = collectAllRules(activeModules);
    stats_.totalRules = allRules.size();
    
    // 构建优化的匹配器
    OptimizedMatcher matcher;
    for (size_t i = 0; i < allRules.size(); ++i) {
        matcher.addRule(allRules[i], i);
    }
    
    // 单次扫描处理
    std::string result;
    result.reserve(jsCode.size() * 1.2); // 预分配空间
    
    size_t lastPos = 0;
    size_t pos = 0;
    
    while (pos < jsCode.length()) {
        auto match = matcher.findNextMatch(jsCode, pos);
        
        if (match.found) {
            // 添加匹配前的内容
            if (match.position > lastPos) {
                result.append(jsCode, lastPos, match.position - lastPos);
            }
            
            // 应用替换
            {
                Timer replaceTimer(stats_.replaceTime);
                std::string replacement = applyReplacement(match, jsCode);
                result.append(replacement);
            }
            
            // 更新统计
            stats_.totalMatches++;
            stats_.ruleHits[match.rule->name]++;
            
            // 更新位置
            lastPos = match.position + match.length;
            pos = lastPos;
        } else {
            // 没有更多匹配，添加剩余内容
            if (lastPos < jsCode.length()) {
                result.append(jsCode, lastPos);
            }
            break;
        }
    }
    
    // 注入运行时代码
    result = injectRuntimeCode(result, activeModules);
    
    // 更新统计
    stats_.bytesProcessed += jsCode.size();
    
    // 缓存结果
    if (cacheEnabled_ && processCache_.size() < MAX_CACHE_SIZE) {
        size_t hash = calculateHash(jsCode, activeModules);
        processCache_[hash] = result;
    }
    
    return result;
}

void CHTLJSProcessorOptimized::resetStats() {
    stats_ = PerformanceStats();
}

std::vector<ScanCutRule> CHTLJSProcessorOptimized::collectAllRules(
    const std::vector<std::string>& activeModules) {
    
    std::vector<ScanCutRule> allRules;
    
    // 获取官方规则
    auto officialRules = getOfficialRules();
    
    // 检查是否有模块覆盖
    std::unordered_map<std::string, std::string> overrides;
    for (const auto& moduleName : activeModules) {
        auto it = modules_.find(moduleName);
        if (it != modules_.end()) {
            auto moduleOverrides = it->second->getOverrides();
            overrides.insert(moduleOverrides.begin(), moduleOverrides.end());
        }
    }
    
    // 应用覆盖到官方规则
    for (auto& rule : officialRules) {
        auto overrideIt = overrides.find(rule.name);
        if (overrideIt != overrides.end()) {
            rule.replacement = overrideIt->second;
        }
        allRules.push_back(rule);
    }
    
    // 添加模块自定义规则
    for (const auto& moduleName : activeModules) {
        auto it = modules_.find(moduleName);
        if (it != modules_.end()) {
            auto moduleRules = it->second->getScanCutRules();
            allRules.insert(allRules.end(), moduleRules.begin(), moduleRules.end());
        }
    }
    
    // 按优先级排序（稳定排序以保持相同优先级的顺序）
    std::stable_sort(allRules.begin(), allRules.end(),
                    [](const ScanCutRule& a, const ScanCutRule& b) {
                        return a.priority > b.priority;
                    });
    
    return allRules;
}

std::vector<ScanCutRule> CHTLJSProcessorOptimized::getOfficialRules() {
    if (officialRulesCached_) {
        return officialRules_;
    }
    
    // 定义官方 CHTL JS 规则
    officialRules_ = {
        // 响应式语法
        {"reactive_declaration", R"(reactive\s+(\w+)\s*=\s*([^;]+);)", 
         "let $1 = createReactive($2);", 100},
        
        // 监听器语法
        {"watch_syntax", R"(watch\s*\(\s*([^,]+),\s*([^)]+)\s*\))", 
         "createWatcher(() => $1, $2)", 90},
        
        // 计算属性
        {"computed_property", R"(computed\s+(\w+)\s*=\s*\(([^)]*)\)\s*=>\s*{([^}]+)})", 
         "const $1 = createComputed(($2) => {$3})", 85},
        
        // 异步函数增强
        {"async_enhanced", R"(async\*\s+function\s+(\w+))", 
         "async function $1", 80},
        
        // 管道操作符
        {"pipe_operator", R"((\w+)\s*\|>\s*(\w+))", 
         "$2($1)", 75},
        
        // 模板字符串增强
        {"template_enhanced", R"(\$\{([^}]+)\}!)", 
         "${escapeHtml($1)}", 70}
    };
    
    officialRulesCached_ = true;
    return officialRules_;
}

std::string CHTLJSProcessorOptimized::applyReplacement(const MatchResult& match,
                                                      const std::string& text) {
    std::string replacement = match.rule->replacement;
    
    // 处理捕获组替换
    for (size_t i = 0; i < match.match.size(); ++i) {
        std::string placeholder = "$" + std::to_string(i);
        size_t pos = 0;
        while ((pos = replacement.find(placeholder, pos)) != std::string::npos) {
            replacement.replace(pos, placeholder.length(), match.match[i]);
            pos += match.match[i].length();
        }
    }
    
    // 如果有验证器，验证替换
    if (match.rule->validator) {
        if (!match.rule->validator(match.match[0], replacement)) {
            // 验证失败，返回原文本
            return match.match[0];
        }
    }
    
    return replacement;
}

std::string CHTLJSProcessorOptimized::injectRuntimeCode(const std::string& code,
                                                       const std::vector<std::string>& activeModules) {
    std::stringstream result;
    
    // 收集所有运行时注入
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
    
    // 注入 before 代码
    for (const auto& injection : beforeInjections) {
        result << injection.code << "\n\n";
    }
    
    // 原始代码
    result << code;
    
    // 注入 after 代码
    for (const auto& injection : afterInjections) {
        result << "\n\n" << injection.code;
    }
    
    return result.str();
}

size_t CHTLJSProcessorOptimized::calculateHash(const std::string& code,
                                              const std::vector<std::string>& modules) {
    std::hash<std::string> hasher;
    size_t hash = hasher(code);
    
    for (const auto& module : modules) {
        hash ^= hasher(module) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    
    return hash;
}

} // namespace cjmod
} // namespace chtl