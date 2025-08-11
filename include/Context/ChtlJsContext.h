#ifndef CHTL_JS_CONTEXT_H
#define CHTL_JS_CONTEXT_H

#include "Context/BasicContext.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace chtl {

/**
 * CHTL-JS上下文
 * 管理CHTL-JS编译过程中的符号表、选择器缓存、方法映射等
 */
class ChtlJsContext : public BasicContext {
public:
    // 选择器信息
    struct SelectorInfo {
        std::string selector;
        std::string type;        // "id", "class", "tag", "mixed"
        int usageCount;
        std::vector<size_t> locations;  // 使用位置
    };
    
    // CHTL方法信息
    struct ChtlMethodInfo {
        std::string methodName;
        std::string targetSelector;
        std::unordered_map<std::string, std::string> parameters;
        size_t location;
    };
    
    // 动画信息
    struct AnimationInfo {
        std::string id;
        int duration;
        std::string easing;
        std::unordered_map<std::string, std::string> beginState;
        std::unordered_map<std::string, std::string> endState;
        std::vector<std::pair<double, std::unordered_map<std::string, std::string>>> keyframes;
    };
    
private:
    // 选择器管理
    std::unordered_map<std::string, SelectorInfo> selectors_;
    std::unordered_set<std::string> cachedSelectors_;  // 已缓存的选择器
    
    // CHTL方法调用
    std::vector<ChtlMethodInfo> listenCalls_;
    std::vector<ChtlMethodInfo> delegateCalls_;
    std::vector<AnimationInfo> animations_;
    
    // 转换映射
    std::unordered_map<std::string, std::string> selectorVariables_;  // 选择器到变量名的映射
    std::unordered_map<std::string, std::string> methodTransforms_;   // CHTL方法到JS函数的映射
    
    // 运行时函数
    std::unordered_set<std::string> requiredRuntimeFunctions_;
    
    // 统计信息
    int totalSelectors_;
    int totalChtlMethods_;
    int totalAnimations_;
    
public:
    ChtlJsContext();
    virtual ~ChtlJsContext() = default;
    
    // 实现BasicContext接口
    void enterScope(ScopeType scopeType, const std::string& scopeName = "") override;
    void exitScope() override;
    void reset() override;
    bool validate() override;
    
    // 选择器管理
    void registerSelector(const std::string& selector, size_t location);
    bool hasSelector(const std::string& selector) const;
    std::string getSelectorVariable(const std::string& selector);
    const SelectorInfo* getSelectorInfo(const std::string& selector) const;
    std::vector<std::string> getAllSelectors() const;
    
    // CHTL方法管理
    void registerListenCall(const std::string& selector, 
                          const std::unordered_map<std::string, std::string>& events,
                          size_t location);
    void registerDelegateCall(const std::string& parentSelector,
                            const std::vector<std::string>& childSelectors,
                            const std::unordered_map<std::string, std::string>& events,
                            size_t location);
    void registerAnimation(const AnimationInfo& animation);
    
    // 转换支持
    std::string transformSelector(const std::string& selector);
    std::string transformMethod(const std::string& method, const std::string& target);
    void requireRuntimeFunction(const std::string& functionName);
    std::vector<std::string> getRequiredRuntimeFunctions() const;
    
    // 优化支持
    bool shouldCacheSelector(const std::string& selector) const;
    std::vector<std::string> getFrequentlyUsedSelectors(int threshold = 2) const;
    
    // 验证
    bool validateSelector(const std::string& selector) const;
    bool validateEventName(const std::string& event) const;
    bool validateAnimationConfig(const AnimationInfo& animation) const;
    
    // 统计
    int getTotalSelectors() const { return totalSelectors_; }
    int getTotalChtlMethods() const { return totalChtlMethods_; }
    int getTotalAnimations() const { return totalAnimations_; }
    
    // 错误和警告
    void reportSelectorError(const std::string& selector, const std::string& error);
    void reportMethodError(const std::string& method, const std::string& error);
    void reportAnimationError(const std::string& error);
    
private:
    // 选择器分析
    std::string analyzeSelectorType(const std::string& selector) const;
    std::string generateSelectorVariable(const std::string& selector);
    
    // 验证辅助
    bool isValidCssSelector(const std::string& selector) const;
    bool isValidEventName(const std::string& event) const;
    
    // 初始化
    void initializeMethodTransforms();
    void initializeRuntimeFunctions();
};

} // namespace chtl

#endif // CHTL_JS_CONTEXT_H