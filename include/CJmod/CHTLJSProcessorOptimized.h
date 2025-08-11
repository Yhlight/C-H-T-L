#ifndef CHTL_CJMOD_CHTLJS_PROCESSOR_OPTIMIZED_H
#define CHTL_CJMOD_CHTLJS_PROCESSOR_OPTIMIZED_H

#include "CJmod/CJmodCorrect.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <regex>
#include <chrono>

namespace chtl {
namespace cjmod {

/**
 * 优化的 CHTL JS 处理器 - 单次扫描实现
 */
class CHTLJSProcessorOptimized {
public:
    // 匹配结果
    struct MatchResult {
        bool found = false;
        size_t position = 0;
        size_t length = 0;
        const ScanCutRule* rule = nullptr;
        std::smatch match;
    };
    
    // 性能统计
    struct PerformanceStats {
        size_t totalRules = 0;
        size_t totalMatches = 0;
        double scanTime = 0.0;
        double replaceTime = 0.0;
        size_t bytesProcessed = 0;
        std::unordered_map<std::string, size_t> ruleHits;
    };
    
    CHTLJSProcessorOptimized();
    ~CHTLJSProcessorOptimized();
    
    /**
     * 注册模块
     */
    void registerModule(const std::string& name, std::shared_ptr<ICJmod> module);
    
    /**
     * 单次扫描处理
     * @param jsCode 输入的 JavaScript 代码
     * @param activeModules 活跃的模块列表
     * @return 处理后的代码
     */
    std::string process(const std::string& jsCode, 
                       const std::vector<std::string>& activeModules);
    
    /**
     * 获取性能统计
     */
    PerformanceStats getStats() const { return stats_; }
    
    /**
     * 重置统计
     */
    void resetStats();
    
    /**
     * 启用/禁用缓存
     */
    void enableCache(bool enable) { cacheEnabled_ = enable; }
    
private:
    // 优化的匹配器
    class OptimizedMatcher {
    public:
        struct CompiledRule {
            ScanCutRule rule;
            std::regex regex;
            size_t id;
        };
        
        void addRule(const ScanCutRule& rule, size_t id);
        MatchResult findNextMatch(const std::string& text, size_t startPos);
        void clear();
        
    private:
        std::vector<CompiledRule> compiledRules_;
        
        // 优化：预先编译的组合正则表达式（用于快速跳过）
        std::regex combinedSkipRegex_;
        bool skipRegexDirty_ = true;
        void rebuildSkipRegex();
    };
    
    // 模块存储
    std::unordered_map<std::string, std::shared_ptr<ICJmod>> modules_;
    
    // 官方规则缓存
    std::vector<ScanCutRule> officialRules_;
    bool officialRulesCached_ = false;
    
    // 性能统计
    mutable PerformanceStats stats_;
    
    // 缓存
    bool cacheEnabled_ = true;
    std::unordered_map<size_t, std::string> processCache_;
    static constexpr size_t MAX_CACHE_SIZE = 100;
    
    // 收集所有规则
    std::vector<ScanCutRule> collectAllRules(const std::vector<std::string>& activeModules);
    
    // 获取官方规则
    std::vector<ScanCutRule> getOfficialRules();
    
    // 应用替换
    std::string applyReplacement(const MatchResult& match, const std::string& text);
    
    // 注入运行时代码
    std::string injectRuntimeCode(const std::string& code, 
                                 const std::vector<std::string>& activeModules);
    
    // 计算哈希（用于缓存）
    size_t calculateHash(const std::string& code, 
                        const std::vector<std::string>& modules);
    
    // 性能计时器
    class Timer {
        std::chrono::steady_clock::time_point start_;
        double& target_;
    public:
        Timer(double& target) : target_(target) {
            start_ = std::chrono::steady_clock::now();
        }
        ~Timer() {
            auto end = std::chrono::steady_clock::now();
            target_ += std::chrono::duration<double>(end - start_).count();
        }
    };
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_CHTLJS_PROCESSOR_OPTIMIZED_H