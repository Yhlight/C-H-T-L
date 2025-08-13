#ifndef CHTLJS_STATE_MACHINE_H
#define CHTLJS_STATE_MACHINE_H

#include <string>
#include <stack>
#include <memory>
#include <unordered_map>

namespace chtl {

// CHTL JS 状态
enum class CHTLJSState {
    // 基础状态
    Default,
    InScript,
    InExpression,
    
    // 增强选择器状态
    InEnhancedSelector,
    InSelectorExpression,
    
    // 方法调用状态
    InMethodCall,
    InListenCall,
    InDelegateCall,
    InAnimateCall,
    
    // 对象字面量状态
    InObjectLiteral,
    InObjectProperty,
    InObjectValue,
    
    // 数组状态
    InArray,
    InArrayElement,
    
    // 函数状态
    InFunction,
    InFunctionParameters,
    InFunctionBody,
    
    // 无修饰字面量状态
    InUnquotedContext,      // 允许无修饰字面量的上下文
    InStyleValue,           // 样式值上下文
    InAttributeValue,       // 属性值上下文
    InVariableValue,        // 变量值上下文
    
    // 字符串状态
    InString,
    InTemplate,
    
    // 错误状态
    Error
};

// CHTL JS 事件
enum class CHTLJSEvent {
    // 基础事件
    EnterScript,
    ExitScript,
    
    // 选择器事件
    StartEnhancedSelector,
    EndEnhancedSelector,
    
    // 方法事件
    StartMethodCall,
    EndMethodCall,
    StartListen,
    StartDelegate,
    StartAnimate,
    
    // 对象事件
    StartObject,
    EndObject,
    StartProperty,
    EndProperty,
    Colon,
    Comma,
    
    // 数组事件
    StartArray,
    EndArray,
    
    // 函数事件
    StartFunction,
    EndFunction,
    StartParameters,
    EndParameters,
    
    // 字面量事件
    StartUnquotedLiteral,
    EndUnquotedLiteral,
    DetectUnquotedContext,
    
    // 字符串事件
    StartString,
    EndString,
    StartTemplate,
    EndTemplate,
    
    // 箭头语法
    ArrowOperator,
    
    // 错误事件
    InvalidSyntax
};

// 无修饰字面量上下文
struct UnquotedLiteralContext {
    enum Type {
        None,
        StyleProperty,      // CSS属性值
        AttributeValue,     // HTML属性值
        VariableAssignment, // 变量赋值
        ObjectValue,        // 对象属性值
        FunctionArgument,   // 函数参数
        ArrayElement        // 数组元素
    };
    
    Type type = None;
    std::string propertyName;  // 属性名（如果适用）
    bool allowsUnquoted = false;
    
    // 判断是否允许无修饰字面量
    bool canUseUnquoted() const;
    
    // 验证无修饰字面量
    bool isValidUnquoted(const std::string& value) const;
};

// CHTL JS 状态机
class CHTLJSStateMachine {
private:
    std::stack<CHTLJSState> stateStack;
    CHTLJSState currentState;
    UnquotedLiteralContext unquotedContext;
    
    // 状态转换表
    std::unordered_map<std::pair<CHTLJSState, CHTLJSEvent>, CHTLJSState, 
                      std::hash<std::pair<CHTLJSState, CHTLJSEvent>>> transitionTable;
    
    // 初始化转换表
    void initializeTransitions();
    
    // 更新无修饰字面量上下文
    void updateUnquotedContext(CHTLJSState newState, CHTLJSEvent event);
    
public:
    CHTLJSStateMachine();
    
    // 处理事件
    bool handleEvent(CHTLJSEvent event);
    
    // 状态查询
    CHTLJSState getCurrentState() const { return currentState; }
    bool isInState(CHTLJSState state) const;
    bool canTransition(CHTLJSEvent event) const;
    
    // 无修饰字面量支持
    bool canUseUnquotedLiteral() const { return unquotedContext.canUseUnquoted(); }
    bool isValidUnquotedLiteral(const std::string& value) const { 
        return unquotedContext.isValidUnquoted(value); 
    }
    UnquotedLiteralContext::Type getUnquotedContextType() const { 
        return unquotedContext.type; 
    }
    
    // 栈操作
    void pushState(CHTLJSState state);
    void popState();
    
    // 重置
    void reset();
    
    // 调试
    std::string getStateString() const;
    std::string getEventString(CHTLJSEvent event) const;
};

// 辅助函数
namespace CHTLJSStateMachineHelper {
    // 检测当前token是否开启无修饰字面量上下文
    CHTLJSEvent detectUnquotedContextStart(const std::string& token);
    
    // 判断是否是有效的无修饰字面量
    bool isValidUnquotedValue(const std::string& value, UnquotedLiteralContext::Type context);
    
    // 转换无修饰字面量为引号字符串
    std::string quoteUnquotedLiteral(const std::string& value);
}

} // namespace chtl

#endif // CHTLJS_STATE_MACHINE_H