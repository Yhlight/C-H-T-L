#ifndef CHTL_STATE_MACHINE_H
#define CHTL_STATE_MACHINE_H

#include <stack>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace chtl {

// CHTL编译器的状态枚举
enum class CHTLState {
    // 顶层状态
    INITIAL,                    // 初始状态
    IN_ELEMENT,                 // 在元素内部
    IN_TEXT,                    // 在text块内
    IN_STYLE,                   // 在style块内
    IN_SCRIPT,                  // 在script块内
    
    // 声明状态
    IN_TEMPLATE,                // 在[Template]声明内
    IN_CUSTOM,                  // 在[Custom]声明内
    IN_CONFIGURATION,           // 在[Configuration]内
    IN_NAMESPACE,               // 在[Namespace]内
    IN_IMPORT,                  // 在[Import]语句
    IN_ORIGIN,                  // 在[Origin]块内
    
    // 特殊状态
    IN_ATTRIBUTE,               // 在属性定义中
    IN_STYLE_SELECTOR,          // 在样式选择器中
    IN_STYLE_PROPERTY,          // 在样式属性中
    IN_TEMPLATE_INHERITANCE,    // 在模板继承中
    IN_SPECIALIZATION,          // 在特例化块中
    IN_DELETE_STATEMENT,        // 在delete语句中
    IN_INSERT_STATEMENT,        // 在insert语句中
    IN_EXCEPT_CONSTRAINT,       // 在except约束中
    
    // 原始嵌入状态
    IN_ORIGIN_HTML,             // 在[Origin] @Html内
    IN_ORIGIN_STYLE,            // 在[Origin] @Style内
    IN_ORIGIN_JAVASCRIPT,       // 在[Origin] @JavaScript内
    
    // 错误状态
    ERROR                       // 错误状态
};

// 状态转换事件
enum class CHTLEvent {
    // 基础事件
    OPEN_BRACE,                 // {
    CLOSE_BRACE,                // }
    OPEN_BRACKET,               // [
    CLOSE_BRACKET,              // ]
    SEMICOLON,                  // ;
    COLON,                      // :
    EQUALS,                     // =
    COMMA,                      // ,
    
    // 关键字事件
    KEYWORD_TEXT,               // text
    KEYWORD_STYLE,              // style
    KEYWORD_SCRIPT,             // script
    KEYWORD_TEMPLATE,           // [Template]
    KEYWORD_CUSTOM,             // [Custom]
    KEYWORD_CONFIGURATION,      // [Configuration]
    KEYWORD_NAMESPACE,          // [Namespace]
    KEYWORD_IMPORT,             // [Import]
    KEYWORD_ORIGIN,             // [Origin]
    KEYWORD_DELETE,             // delete
    KEYWORD_INSERT,             // insert
    KEYWORD_EXCEPT,             // except
    KEYWORD_INHERIT,            // inherit
    KEYWORD_FROM,               // from
    KEYWORD_AS,                 // as
    
    // 模板类型事件
    AT_STYLE,                   // @Style
    AT_ELEMENT,                 // @Element
    AT_VAR,                     // @Var
    AT_HTML,                    // @Html
    AT_JAVASCRIPT,              // @JavaScript
    AT_CHTL,                    // @Chtl
    
    // 标识符和字面量
    IDENTIFIER,                 // 标识符
    STRING_LITERAL,             // 字符串字面量
    NUMBER_LITERAL,             // 数字字面量
    
    // 特殊事件
    EOF_EVENT,                  // 文件结束
    UNKNOWN                     // 未知事件
};

// 状态机类
class CHTLStateMachine {
private:
    CHTLState currentState;
    std::stack<CHTLState> stateStack;
    std::vector<std::string> errors;
    
    // 状态转换表
    std::unordered_map<CHTLState, std::unordered_map<CHTLEvent, CHTLState>> transitionTable;
    
    // 初始化状态转换表
    void initializeTransitionTable();
    
    // 验证状态转换
    bool isValidTransition(CHTLState from, CHTLEvent event, CHTLState to);
    
public:
    CHTLStateMachine();
    ~CHTLStateMachine() = default;
    
    // 处理事件并进行状态转换
    bool processEvent(CHTLEvent event);
    
    // 推入状态（用于嵌套结构）
    void pushState(CHTLState state);
    
    // 弹出状态
    bool popState();
    
    // 获取当前状态
    CHTLState getCurrentState() const { return currentState; }
    
    // 检查是否在特定状态
    bool isInState(CHTLState state) const { return currentState == state; }
    
    // 检查是否可以使用某个特性
    bool canUseFeature(const std::string& feature) const;
    
    // 重置状态机
    void reset();
    
    // 错误处理
    void addError(const std::string& error);
    const std::vector<std::string>& getErrors() const { return errors; }
    bool hasErrors() const { return !errors.empty(); }
    
    // 状态验证
    bool isInValidState() const;
    bool canTransitionTo(CHTLState targetState) const;
    
    // 获取当前状态的字符串表示
    std::string getCurrentStateString() const;
    static std::string stateToString(CHTLState state);
    static std::string eventToString(CHTLEvent event);
};

} // namespace chtl

#endif // CHTL_STATE_MACHINE_H