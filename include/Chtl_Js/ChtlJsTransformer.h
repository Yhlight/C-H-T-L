#ifndef CHTL_JS_TRANSFORMER_H
#define CHTL_JS_TRANSFORMER_H

#include "ChtlJsTypes.h"
#include <string>
#include <memory>

namespace chtl {
namespace chtl_js {

/**
 * CHTL-JS转换器
 * 将CHTL扩展语法转换为标准JavaScript
 */
class ChtlJsTransformer {
private:
    ChtlJsTransformResult result_;
    
    // 转换方法
    std::string transformSelector(const SelectorInfo& selector);
    std::string transformListenCall(const ChtlMethodInfo& method, const std::string& target);
    std::string transformDelegateCall(const ChtlMethodInfo& method, const std::string& target);
    std::string transformAnimateCall(const AnimationInfo& animation);
    
    // 生成运行时调用
    std::string generateQuerySelector(const SelectorInfo& selector);
    std::string generateEventListener(const std::string& target, 
                                    const std::string& event, 
                                    const std::string& handler);
    std::string generateDelegation(const std::string& parent,
                                 const std::vector<std::string>& targets,
                                 const std::unordered_map<std::string, std::string>& handlers);
    std::string generateAnimation(const AnimationInfo& animation);
    
    // 工具方法
    std::string escapeJsString(const std::string& str);
    std::string generateCssObject(const std::unordered_map<std::string, std::string>& properties);
    bool needsTransform(const std::string& code);
    
public:
    ChtlJsTransformer();
    
    /**
     * 转换CHTL-JS代码为标准JavaScript
     * @param chtlJs CHTL-JS代码
     * @return 转换结果
     */
    ChtlJsTransformResult transform(const std::string& chtlJs);
    
    /**
     * 转换单个CHTL表达式
     * @param expression CHTL表达式（如{{selector}}）
     * @return 标准JavaScript代码
     */
    std::string transformExpression(const std::string& expression);
    
    /**
     * 注入CHTL运行时代码
     * @param jsCode 原始JavaScript代码
     * @param injectRuntime 是否注入运行时
     * @return 包含运行时的完整代码
     */
    std::string injectRuntime(const std::string& jsCode, bool injectRuntime = true);
    
    /**
     * 优化转换后的代码
     * @param jsCode 转换后的JavaScript代码
     * @return 优化后的代码
     */
    std::string optimize(const std::string& jsCode);
    
    /**
     * 获取转换统计信息
     */
    struct TransformStats {
        int selectorsTransformed;
        int methodsTransformed;
        int animationsTransformed;
        int linesAdded;
        int linesRemoved;
    };
    TransformStats getStatistics() const;
    
    /**
     * 获取最后的转换结果
     */
    const ChtlJsTransformResult& getLastResult() const { return result_; }
};

} // namespace chtl_js
} // namespace chtl

#endif // CHTL_JS_TRANSFORMER_H