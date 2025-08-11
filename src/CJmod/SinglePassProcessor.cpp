#include "CJmod/CJmodEnhanced.h"
#include <algorithm>
#include <queue>

namespace chtl {
namespace cjmod {

// 单次扫描实现
std::vector<SinglePassProcessor::RuleMatch> 
SinglePassProcessor::collectAllMatches(const std::string& code, 
                                      const std::vector<EnhancedScanRule>& rules) {
    std::vector<RuleMatch> allMatches;
    
    // 构建一个字符到规则的映射，加速查找
    std::unordered_map<char, std::vector<const EnhancedScanRule*>> firstCharMap;
    for (const auto& rule : rules) {
        // 这里简化处理，实际应该从正则或模式中提取首字符
        // ...
    }
    
    // 单次遍历代码
    for (size_t i = 0; i < code.length(); ++i) {
        // 尝试所有可能在此位置匹配的规则
        for (const auto& rule : rules) {
            if (std::holds_alternative<std::regex>(rule.matcher)) {
                const auto& regex = std::get<std::regex>(rule.matcher);
                std::smatch match;
                
                // 从当前位置开始匹配
                if (std::regex_search(code.begin() + i, code.end(), match, regex)) {
                    RuleMatch rm;
                    rm.start = i + match.position();
                    rm.end = rm.start + match.length();
                    rm.priority = rule.priority;
                    
                    // 生成替换文本
                    if (std::holds_alternative<std::string>(rule.replacer)) {
                        rm.replacement = match.format(std::get<std::string>(rule.replacer));
                    } else if (auto* fn = std::get_if<std::function<std::string(const std::smatch&)>>(&rule.replacer)) {
                        rm.replacement = (*fn)(match);
                    }
                    
                    allMatches.push_back(rm);
                }
            }
            // 处理其他类型的匹配器...
        }
    }
    
    return allMatches;
}

std::string SinglePassProcessor::applyReplacements(const std::string& code, 
                                                  std::vector<RuleMatch>& matches) {
    // 按位置和优先级排序
    std::sort(matches.begin(), matches.end(), [](const RuleMatch& a, const RuleMatch& b) {
        if (a.start != b.start) return a.start < b.start;
        return a.priority > b.priority;  // 高优先级优先
    });
    
    // 去除重叠的匹配（保留高优先级的）
    std::vector<RuleMatch> nonOverlapping;
    size_t lastEnd = 0;
    
    for (const auto& match : matches) {
        if (match.start >= lastEnd) {
            nonOverlapping.push_back(match);
            lastEnd = match.end;
        }
    }
    
    // 应用替换（从后往前，避免位置偏移）
    std::string result = code;
    for (auto it = nonOverlapping.rbegin(); it != nonOverlapping.rend(); ++it) {
        result.replace(it->start, it->end - it->start, it->replacement);
    }
    
    return result;
}

// 优化版的 CJmod 处理器（单次扫描）
class OptimizedCHTLJSProcessor {
public:
    std::string processJavaScriptSinglePass(const std::string& jsCode,
                                           const std::vector<std::string>& activeModules) {
        // 收集所有规则
        std::vector<EnhancedScanRule> allRules;
        
        // 添加官方规则
        // ...
        
        // 添加模块规则
        for (const auto& moduleName : activeModules) {
            // 获取模块规则并添加
            // ...
        }
        
        // 单次扫描处理
        SinglePassProcessor processor;
        auto matches = processor.collectAllMatches(jsCode, allRules);
        return processor.applyReplacements(jsCode, matches);
    }
};

} // namespace cjmod
} // namespace chtl