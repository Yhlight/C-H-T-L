#ifndef CHTL_JS_TYPES_H
#define CHTL_JS_TYPES_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace chtl {
namespace chtl_js {

// CHTL-JS特有的Token类型
enum class ChtlJsTokenType {
    // CHTL选择器
    DOUBLE_BRACE_OPEN,   // {{
    DOUBLE_BRACE_CLOSE,  // }}
    
    // CHTL操作符
    ARROW,               // ->
    
    // CHTL关键字
    ANIMATE,             // animate
    LISTEN,              // listen
    DELEGATE,            // delegate
    
    // 标准JS token（继承）
    JS_TOKEN             // 包装标准JS token
};

// CHTL-JS语法节点类型
enum class ChtlJsNodeType {
    // 选择器节点
    SELECTOR_EXPRESSION,     // {{selector}}
    
    // CHTL方法调用
    CHTL_METHOD_CALL,       // ->method()
    LISTEN_CALL,            // ->listen({...})
    DELEGATE_CALL,          // ->delegate({...})
    ANIMATE_CALL,           // animate({...})
    
    // 标准JS节点
    STANDARD_JS             // 标准JavaScript代码
};

// 选择器类型
enum class SelectorType {
    ID,                     // #id
    CLASS,                  // .class
    TAG,                    // tag
    MIXED,                  // .class tag
    INDEXED,                // tag[0]
    AUTO                    // 自动检测（id优先）
};

// 选择器信息
struct SelectorInfo {
    std::string rawSelector;     // 原始选择器字符串
    SelectorType type;           // 选择器类型
    std::string mainSelector;    // 主选择器（如类名、ID、标签名）
    std::string subSelector;     // 子选择器（用于复合选择器）
    int index = -1;              // 索引（如果有）
    
    SelectorInfo(const std::string& raw = "") 
        : rawSelector(raw), type(SelectorType::AUTO) {}
};

// CHTL方法信息
struct ChtlMethodInfo {
    std::string methodName;      // 方法名（listen, delegate等）
    std::vector<std::string> arguments;  // 参数列表
    std::unordered_map<std::string, std::string> eventHandlers;  // 事件处理器映射
};

// 动画关键帧
struct AnimationKeyframe {
    double at;                   // 时间点（0.0-1.0）
    std::unordered_map<std::string, std::string> properties;  // CSS属性
};

// 动画信息
struct AnimationInfo {
    int duration = 1000;         // 持续时间（毫秒）
    std::string easing = "linear";  // 缓动函数
    std::unordered_map<std::string, std::string> beginState;  // 起始状态
    std::unordered_map<std::string, std::string> endState;    // 结束状态
    std::vector<AnimationKeyframe> keyframes;  // 关键帧
};

// CHTL-JS转换结果
struct ChtlJsTransformResult {
    std::string transformedCode;     // 转换后的标准JS代码
    std::vector<SelectorInfo> selectors;  // 使用的选择器
    std::vector<ChtlMethodInfo> chtlMethods;  // 使用的CHTL方法
    std::vector<AnimationInfo> animations;    // 动画定义
    
    bool hasErrors = false;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 统计信息
    int selectorCount = 0;
    int chtlMethodCount = 0;
    int animationCount = 0;
    int eventListenerCount = 0;
    int delegateCount = 0;
};

// CHTL运行时函数名
namespace ChtlRuntime {
    const std::string QUERY_SELECTOR = "$chtl_querySelector";
    const std::string QUERY_SELECTOR_ALL = "$chtl_querySelectorAll";
    const std::string ADD_LISTENER = "$chtl_addListener";
    const std::string DELEGATE_EVENT = "$chtl_delegateEvent";
    const std::string ANIMATE = "$chtl_animate";
}

} // namespace chtl_js
} // namespace chtl

#endif // CHTL_JS_TYPES_H