#ifndef CHTLJS_CONTEXT_H
#define CHTLJS_CONTEXT_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <stack>
#include <optional>
#include <functional>
#include "CHTLJSStateMachine.h"

namespace chtljs {

// 前向声明
class DOMReference;
class EventBinding;
class AnimationDefinition;
class CHTLMethodCall;

// DOM元素引用类型
enum class DOMReferenceType {
    CLASS_SELECTOR,     // .className
    ID_SELECTOR,        // #id
    ELEMENT_SELECTOR,   // element
    COMPLEX_SELECTOR,   // 复合选择器
    INDEXED_SELECTOR    // 带索引的选择器
};

// DOM元素引用
class DOMReference {
private:
    std::string selector;
    DOMReferenceType type;
    std::optional<int> index;
    std::string originalExpression;  // 原始的{{}}表达式
    
public:
    DOMReference(const std::string& sel, DOMReferenceType t) 
        : selector(sel), type(t) {}
    
    const std::string& getSelector() const { return selector; }
    DOMReferenceType getType() const { return type; }
    
    void setIndex(int idx) { index = idx; }
    std::optional<int> getIndex() const { return index; }
    
    void setOriginalExpression(const std::string& expr) { originalExpression = expr; }
    const std::string& getOriginalExpression() const { return originalExpression; }
    
    // 生成JavaScript代码
    std::string toJavaScript() const;
    std::string toQuerySelector() const;
};

// 事件处理器信息
struct EventHandler {
    std::string eventName;
    std::string handlerCode;
    bool isArrowFunction;
    bool isAnonymous;
    std::string functionName;
};

// 事件绑定
class EventBinding {
private:
    std::shared_ptr<DOMReference> target;
    std::vector<EventHandler> handlers;
    bool isDelegated;
    std::vector<std::shared_ptr<DOMReference>> delegateTargets;
    
public:
    EventBinding(std::shared_ptr<DOMReference> t) : target(t), isDelegated(false) {}
    
    void addHandler(const EventHandler& handler);
    void setDelegated(bool delegated) { isDelegated = delegated; }
    void addDelegateTarget(std::shared_ptr<DOMReference> target);
    
    const std::shared_ptr<DOMReference>& getTarget() const { return target; }
    const std::vector<EventHandler>& getHandlers() const { return handlers; }
    bool getIsDelegated() const { return isDelegated; }
    
    // 生成addEventListener代码
    std::string generateListenerCode() const;
    // 生成事件委托代码
    std::string generateDelegateCode() const;
};

// CSS属性
struct CSSProperty {
    std::string name;
    std::string value;
    bool isVariable;  // 是否是CSS变量
};

// 动画关键帧
struct AnimationKeyframe {
    float at;  // 0.0 - 1.0
    std::vector<CSSProperty> properties;
};

// 动画定义
class AnimationDefinition {
private:
    int duration;  // ms
    std::string easing;
    std::vector<CSSProperty> beginState;
    std::vector<CSSProperty> endState;
    std::vector<AnimationKeyframe> keyframes;
    int loop;  // -1 表示无限循环
    std::string direction;
    int delay;  // ms
    std::string callbackCode;
    
public:
    AnimationDefinition() : duration(0), loop(1), delay(0) {}
    
    // Setters
    void setDuration(int d) { duration = d; }
    void setEasing(const std::string& e) { easing = e; }
    void setLoop(int l) { loop = l; }
    void setDirection(const std::string& d) { direction = d; }
    void setDelay(int d) { delay = d; }
    void setCallback(const std::string& c) { callbackCode = c; }
    
    void addBeginProperty(const CSSProperty& prop) { beginState.push_back(prop); }
    void addEndProperty(const CSSProperty& prop) { endState.push_back(prop); }
    void addKeyframe(const AnimationKeyframe& kf) { keyframes.push_back(kf); }
    
    // 生成requestAnimationFrame代码
    std::string generateAnimationCode() const;
    // 生成CSS动画代码（如果可能）
    std::string generateCSSAnimation() const;
};

// CHTL方法调用信息
class CHTLMethodCall {
public:
    enum class MethodType {
        LISTEN,
        DELEGATE,
        ANIMATE
    };
    
private:
    MethodType type;
    std::shared_ptr<DOMReference> target;  // 对于animate可能为null
    std::string configCode;  // 原始配置代码
    
public:
    CHTLMethodCall(MethodType t) : type(t) {}
    
    void setTarget(std::shared_ptr<DOMReference> t) { target = t; }
    void setConfigCode(const std::string& code) { configCode = code; }
    
    MethodType getType() const { return type; }
    const std::shared_ptr<DOMReference>& getTarget() const { return target; }
    const std::string& getConfigCode() const { return configCode; }
};

// CHTL JS上下文
class CHTLJSContext {
private:
    // 状态机
    std::unique_ptr<CHTLJSStateMachine> stateMachine;
    
    // DOM引用管理
    std::vector<std::shared_ptr<DOMReference>> domReferences;
    std::unordered_map<std::string, std::shared_ptr<DOMReference>> selectorCache;
    
    // 事件绑定管理
    std::vector<std::shared_ptr<EventBinding>> eventBindings;
    
    // 动画管理
    std::vector<std::shared_ptr<AnimationDefinition>> animations;
    
    // CHTL方法调用追踪
    std::vector<std::shared_ptr<CHTLMethodCall>> methodCalls;
    
    // 当前处理的上下文
    std::shared_ptr<DOMReference> currentTarget;
    std::shared_ptr<EventBinding> currentBinding;
    std::shared_ptr<AnimationDefinition> currentAnimation;
    
    // 符号表（变量和函数）
    std::unordered_map<std::string, std::string> variables;
    std::unordered_map<std::string, std::string> functions;
    
    // 父CHTL上下文引用（用于查找CSS类名等）
    void* parentCHTLContext;  // 避免循环依赖
    
    // 错误和警告
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
public:
    CHTLJSContext();
    ~CHTLJSContext() = default;
    
    // 状态机访问
    CHTLJSStateMachine& getStateMachine() { return *stateMachine; }
    
    // DOM引用管理
    std::shared_ptr<DOMReference> createDOMReference(const std::string& selector);
    std::shared_ptr<DOMReference> getCachedReference(const std::string& selector);
    void registerDOMReference(std::shared_ptr<DOMReference> ref);
    
    // 事件绑定管理
    std::shared_ptr<EventBinding> createEventBinding(std::shared_ptr<DOMReference> target);
    void registerEventBinding(std::shared_ptr<EventBinding> binding);
    std::vector<std::shared_ptr<EventBinding>> getBindingsForTarget(const std::string& selector);
    
    // 动画管理
    std::shared_ptr<AnimationDefinition> createAnimation();
    void registerAnimation(std::shared_ptr<AnimationDefinition> animation);
    
    // CHTL方法调用
    void registerMethodCall(std::shared_ptr<CHTLMethodCall> call);
    const std::vector<std::shared_ptr<CHTLMethodCall>>& getMethodCalls() const { return methodCalls; }
    
    // 当前上下文管理
    void setCurrentTarget(std::shared_ptr<DOMReference> target) { currentTarget = target; }
    void setCurrentBinding(std::shared_ptr<EventBinding> binding) { currentBinding = binding; }
    void setCurrentAnimation(std::shared_ptr<AnimationDefinition> animation) { currentAnimation = animation; }
    
    std::shared_ptr<DOMReference> getCurrentTarget() const { return currentTarget; }
    std::shared_ptr<EventBinding> getCurrentBinding() const { return currentBinding; }
    std::shared_ptr<AnimationDefinition> getCurrentAnimation() const { return currentAnimation; }
    
    // 符号表管理
    void registerVariable(const std::string& name, const std::string& value);
    void registerFunction(const std::string& name, const std::string& body);
    std::optional<std::string> lookupVariable(const std::string& name) const;
    std::optional<std::string> lookupFunction(const std::string& name) const;
    
    // 父上下文
    void setParentContext(void* ctx) { parentCHTLContext = ctx; }
    void* getParentContext() const { return parentCHTLContext; }
    
    // 验证
    bool validateSelector(const std::string& selector);
    bool validateEventName(const std::string& eventName);
    bool validateCSSProperty(const std::string& property);
    
    // 代码生成
    std::string generateInitializationCode() const;
    std::string generateDOMReadyWrapper(const std::string& code) const;
    
    // 错误和警告
    void addError(const std::string& error) { errors.push_back(error); }
    void addWarning(const std::string& warning) { warnings.push_back(warning); }
    const std::vector<std::string>& getErrors() const { return errors; }
    const std::vector<std::string>& getWarnings() const { return warnings; }
    bool hasErrors() const { return !errors.empty(); }
    
    // 重置上下文
    void reset();
    
    // 检测CHTL特性使用情况
    bool isUsingCHTLFeatures() const;
    std::vector<std::string> getUsedCHTLFeatures() const;
};

// 辅助函数
namespace CHTLJSHelper {
    // 解析选择器
    DOMReferenceType parseSelector(const std::string& selector);
    std::string extractSelectorBase(const std::string& selector);
    std::optional<int> extractSelectorIndex(const std::string& selector);
    
    // 验证JavaScript代码片段
    bool isValidJavaScriptIdentifier(const std::string& identifier);
    bool isValidEventName(const std::string& eventName);
    
    // 生成唯一ID
    std::string generateUniqueId(const std::string& prefix = "chtl");
}

} // namespace chtljs

#endif // CHTLJS_CONTEXT_H