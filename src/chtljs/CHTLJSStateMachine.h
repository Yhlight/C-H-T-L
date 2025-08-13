#ifndef CHTLJS_STATE_MACHINE_H
#define CHTLJS_STATE_MACHINE_H

#include <stack>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace chtljs {

// CHTL JS的状态枚举
enum class CHTLJSState {
    // JavaScript基础状态
    INITIAL,                        // 初始状态
    IN_STATEMENT,                   // 在语句中
    IN_EXPRESSION,                  // 在表达式中
    IN_FUNCTION,                    // 在函数内
    IN_CLASS,                       // 在类内
    IN_OBJECT_LITERAL,              // 在对象字面量内
    IN_ARRAY_LITERAL,               // 在数组字面量内
    
    // CHTL扩展状态
    IN_CHTL_SELECTOR,               // 在{{selector}}内
    IN_CHTL_SELECTOR_INDEX,         // 在选择器索引[n]内
    IN_ARROW_OPERATION,             // 在->操作中
    IN_LISTEN_CONFIG,               // 在listen配置内
    IN_DELEGATE_CONFIG,             // 在delegate配置内
    IN_ANIMATE_CONFIG,              // 在animate配置内
    
    // 特殊CHTL状态
    IN_EVENT_HANDLER,               // 在事件处理器定义中
    IN_CSS_BLOCK,                   // 在CSS块内（animate中）
    IN_WHEN_ARRAY,                  // 在when数组内
    IN_SELECTOR_ARRAY,              // 在选择器数组内
    
    // 错误状态
    ERROR                           // 错误状态
};

// CHTL JS事件
enum class CHTLJSEvent {
    // 基础JavaScript事件
    OPEN_BRACE,                     // {
    CLOSE_BRACE,                    // }
    OPEN_BRACKET,                   // [
    CLOSE_BRACKET,                  // ]
    OPEN_PAREN,                     // (
    CLOSE_PAREN,                    // )
    SEMICOLON,                      // ;
    COLON,                          // :
    COMMA,                          // ,
    DOT,                            // .
    
    // CHTL特殊事件
    DOUBLE_OPEN_BRACE,              // {{
    DOUBLE_CLOSE_BRACE,             // }}
    ARROW,                          // ->
    
    // CHTL方法事件
    METHOD_LISTEN,                  // listen
    METHOD_DELEGATE,                // delegate
    FUNCTION_ANIMATE,               // animate
    
    // 选择器事件
    SELECTOR_CLASS,                 // .className
    SELECTOR_ID,                    // #id
    SELECTOR_ELEMENT,               // element
    
    // 配置属性事件
    PROP_DURATION,                  // duration
    PROP_EASING,                    // easing
    PROP_BEGIN,                     // begin
    PROP_END,                       // end
    PROP_WHEN,                      // when
    PROP_AT,                        // at
    PROP_LOOP,                      // loop
    PROP_DIRECTION,                 // direction
    PROP_DELAY,                     // delay
    PROP_CALLBACK,                  // callback
    PROP_TARGET,                    // target
    
    // 通用事件
    IDENTIFIER,                     // 标识符
    STRING_LITERAL,                 // 字符串
    NUMBER_LITERAL,                 // 数字
    FUNCTION_EXPR,                  // 函数表达式
    ARROW_FUNCTION,                 // 箭头函数
    
    // 特殊事件
    EOF_EVENT,                      // 文件结束
    UNKNOWN                         // 未知事件
};

// CHTL特性类型
enum class CHTLFeature {
    ENHANCED_SELECTOR,              // {{selector}}
    ARROW_OPERATOR,                 // ->
    LISTEN_METHOD,                  // listen()
    DELEGATE_METHOD,                // delegate()
    ANIMATE_FUNCTION                // animate()
};

// 状态机类
class CHTLJSStateMachine {
private:
    CHTLJSState currentState;
    std::stack<CHTLJSState> stateStack;
    std::vector<std::string> errors;
    std::unordered_set<CHTLFeature> detectedFeatures;
    
    // 状态转换表
    std::unordered_map<CHTLJSState, std::unordered_map<CHTLJSEvent, CHTLJSState>> transitionTable;
    
    // CHTL特性检测
    bool inCHTLContext;
    int selectorDepth;
    
    // 初始化状态转换表
    void initializeTransitionTable();
    
    // 验证状态转换
    bool isValidTransition(CHTLJSState from, CHTLJSEvent event, CHTLJSState to);
    
    // 特性检测
    void detectFeature(CHTLJSEvent event);
    
public:
    CHTLJSStateMachine();
    ~CHTLJSStateMachine() = default;
    
    // 处理事件并进行状态转换
    bool processEvent(CHTLJSEvent event);
    
    // 推入状态（用于嵌套结构）
    void pushState(CHTLJSState state);
    
    // 弹出状态
    bool popState();
    
    // 获取当前状态
    CHTLJSState getCurrentState() const { return currentState; }
    
    // 检查是否在特定状态
    bool isInState(CHTLJSState state) const { return currentState == state; }
    
    // CHTL特性检测
    bool isInCHTLSelector() const { return currentState == CHTLJSState::IN_CHTL_SELECTOR; }
    bool isUsingCHTLFeatures() const { return !detectedFeatures.empty(); }
    const std::unordered_set<CHTLFeature>& getDetectedFeatures() const { return detectedFeatures; }
    
    // 验证CHTL语法
    bool validateCHTLSelector(const std::string& selector);
    bool validateListenConfig(const std::string& config);
    bool validateDelegateConfig(const std::string& config);
    bool validateAnimateConfig(const std::string& config);
    
    // 检查是否可以使用某个CHTL特性
    bool canUseCHTLFeature(CHTLFeature feature) const;
    
    // 重置状态机
    void reset();
    
    // 错误处理
    void addError(const std::string& error);
    const std::vector<std::string>& getErrors() const { return errors; }
    bool hasErrors() const { return !errors.empty(); }
    
    // 状态验证
    bool isInValidState() const;
    bool canTransitionTo(CHTLJSState targetState) const;
    
    // 获取当前状态的字符串表示
    std::string getCurrentStateString() const;
    static std::string stateToString(CHTLJSState state);
    static std::string eventToString(CHTLJSEvent event);
    static std::string featureToString(CHTLFeature feature);
};

// CHTL选择器验证器
class CHTLSelectorValidator {
private:
    std::string selector;
    bool isValid;
    std::string errorMessage;
    
public:
    CHTLSelectorValidator(const std::string& sel) : selector(sel), isValid(true) {}
    
    bool validate();
    bool isClassSelector() const;
    bool isIdSelector() const;
    bool isElementSelector() const;
    bool hasIndex() const;
    int getIndex() const;
    std::string getBaseSelector() const;
    const std::string& getError() const { return errorMessage; }
};

// 事件配置验证器
class EventConfigValidator {
private:
    std::unordered_map<std::string, std::string> events;
    bool isValid;
    std::string errorMessage;
    
public:
    bool validateListenConfig(const std::string& config);
    bool validateDelegateConfig(const std::string& config);
    bool hasEvent(const std::string& eventName) const;
    const std::string& getError() const { return errorMessage; }
};

// 动画配置验证器
class AnimateConfigValidator {
private:
    struct AnimateConfig {
        int duration = 0;
        std::string easing;
        std::unordered_map<std::string, std::string> begin;
        std::unordered_map<std::string, std::string> end;
        std::vector<std::pair<float, std::unordered_map<std::string, std::string>>> when;
        int loop = 1;
        std::string direction;
        int delay = 0;
        std::string callback;
    };
    
    AnimateConfig config;
    bool isValid;
    std::string errorMessage;
    
public:
    bool validate(const std::string& configStr);
    const AnimateConfig& getConfig() const { return config; }
    const std::string& getError() const { return errorMessage; }
};

} // namespace chtljs

#endif // CHTLJS_STATE_MACHINE_H