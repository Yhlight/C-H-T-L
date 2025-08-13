#include "CHTLJSStateMachine.h"
#include <regex>
#include <algorithm>
#include <sstream>
#include <set>

namespace chtl {

// UnquotedLiteralContext 实现
bool UnquotedLiteralContext::canUseUnquoted() const {
    switch (type) {
        case StyleProperty:
        case AttributeValue:
        case VariableAssignment:
        case ObjectValue:
            return allowsUnquoted;
        case FunctionArgument:
        case ArrayElement:
            // 函数参数和数组元素通常需要引号
            return false;
        default:
            return false;
    }
}

bool UnquotedLiteralContext::isValidUnquoted(const std::string& value) const {
    if (!canUseUnquoted()) {
        return false;
    }
    
    // 检查是否是有效的无修饰字面量
    // 1. 不能为空
    if (value.empty()) {
        return false;
    }
    
    // 2. 不能以数字开头（除非是纯数字）
    if (std::isdigit(value[0])) {
        // 检查是否是有效的数字
        std::regex numberRegex(R"(^\d+(\.\d+)?$)");
        if (!std::regex_match(value, numberRegex)) {
            return false;
        }
    }
    
    // 3. 只能包含字母、数字、下划线、连字符
    std::regex validChars(R"(^[a-zA-Z_][a-zA-Z0-9_-]*$)");
    if (!std::regex_match(value, validChars)) {
        return false;
    }
    
    // 4. 不能是JavaScript保留字
    static const std::set<std::string> reservedWords = {
        "true", "false", "null", "undefined", "this", "super",
        "new", "delete", "typeof", "instanceof", "in", "of",
        "var", "let", "const", "function", "class", "extends",
        "if", "else", "for", "while", "do", "switch", "case",
        "break", "continue", "return", "throw", "try", "catch",
        "finally", "async", "await", "yield", "import", "export"
    };
    
    if (reservedWords.find(value) != reservedWords.end()) {
        return false;
    }
    
    // 5. 特殊上下文验证
    switch (type) {
        case StyleProperty:
            // CSS属性值的特殊规则
            if (propertyName == "color") {
                // 颜色名称允许无修饰
                static const std::set<std::string> colorNames = {
                    "red", "green", "blue", "black", "white", "yellow",
                    "cyan", "magenta", "gray", "grey", "orange", "purple"
                };
                return colorNames.find(value) != colorNames.end();
            }
            break;
        case AttributeValue:
            // HTML属性值的特殊规则
            if (propertyName == "type" || propertyName == "id" || 
                propertyName == "class" || propertyName == "name") {
                return true;
            }
            break;
        default:
            break;
    }
    
    return true;
}

// CHTLJSStateMachine 实现
CHTLJSStateMachine::CHTLJSStateMachine() : currentState(CHTLJSState::Default) {
    initializeTransitions();
}

void CHTLJSStateMachine::initializeTransitions() {
    // 基础转换
    transitionTable[{CHTLJSState::Default, CHTLJSEvent::EnterScript}] = CHTLJSState::InScript;
    transitionTable[{CHTLJSState::InScript, CHTLJSEvent::ExitScript}] = CHTLJSState::Default;
    
    // 增强选择器转换
    transitionTable[{CHTLJSState::InScript, CHTLJSEvent::StartEnhancedSelector}] = CHTLJSState::InEnhancedSelector;
    transitionTable[{CHTLJSState::InEnhancedSelector, CHTLJSEvent::EndEnhancedSelector}] = CHTLJSState::InScript;
    
    // 对象字面量转换
    transitionTable[{CHTLJSState::InScript, CHTLJSEvent::StartObject}] = CHTLJSState::InObjectLiteral;
    transitionTable[{CHTLJSState::InObjectLiteral, CHTLJSEvent::StartProperty}] = CHTLJSState::InObjectProperty;
    transitionTable[{CHTLJSState::InObjectProperty, CHTLJSEvent::Colon}] = CHTLJSState::InObjectValue;
    transitionTable[{CHTLJSState::InObjectValue, CHTLJSEvent::Comma}] = CHTLJSState::InObjectLiteral;
    transitionTable[{CHTLJSState::InObjectValue, CHTLJSEvent::EndObject}] = CHTLJSState::InScript;
    transitionTable[{CHTLJSState::InObjectLiteral, CHTLJSEvent::EndObject}] = CHTLJSState::InScript;
    
    // 方法调用转换
    transitionTable[{CHTLJSState::InScript, CHTLJSEvent::StartListen}] = CHTLJSState::InListenCall;
    transitionTable[{CHTLJSState::InScript, CHTLJSEvent::StartDelegate}] = CHTLJSState::InDelegateCall;
    transitionTable[{CHTLJSState::InScript, CHTLJSEvent::StartAnimate}] = CHTLJSState::InAnimateCall;
    
    // 无修饰字面量转换
    transitionTable[{CHTLJSState::InObjectValue, CHTLJSEvent::StartUnquotedLiteral}] = CHTLJSState::InUnquotedContext;
    transitionTable[{CHTLJSState::InUnquotedContext, CHTLJSEvent::EndUnquotedLiteral}] = CHTLJSState::InObjectValue;
}

bool CHTLJSStateMachine::handleEvent(CHTLJSEvent event) {
    auto key = std::make_pair(currentState, event);
    auto it = transitionTable.find(key);
    
    if (it != transitionTable.end()) {
        CHTLJSState newState = it->second;
        updateUnquotedContext(newState, event);
        pushState(currentState);
        currentState = newState;
        return true;
    }
    
    return false;
}

void CHTLJSStateMachine::updateUnquotedContext(CHTLJSState newState, CHTLJSEvent event) {
    switch (event) {
        case CHTLJSEvent::StartObject:
            if (currentState == CHTLJSState::InAnimateCall) {
                // animate配置对象中的样式属性
                unquotedContext.type = UnquotedLiteralContext::StyleProperty;
                unquotedContext.allowsUnquoted = true;
            }
            break;
            
        case CHTLJSEvent::StartProperty:
            // 记录属性名
            unquotedContext.propertyName = ""; // 需要从解析器获取
            break;
            
        case CHTLJSEvent::Colon:
            // 进入属性值上下文
            if (currentState == CHTLJSState::InObjectProperty) {
                // 根据属性名判断是否允许无修饰字面量
                if (unquotedContext.type == UnquotedLiteralContext::StyleProperty) {
                    unquotedContext.allowsUnquoted = true;
                } else {
                    unquotedContext.allowsUnquoted = false;
                }
            }
            break;
            
        case CHTLJSEvent::DetectUnquotedContext:
            // 检测当前是否在可以使用无修饰字面量的上下文中
            if (currentState == CHTLJSState::InObjectValue) {
                unquotedContext.allowsUnquoted = true;
            }
            break;
            
        default:
            break;
    }
}

bool CHTLJSStateMachine::isInState(CHTLJSState state) const {
    return currentState == state;
}

bool CHTLJSStateMachine::canTransition(CHTLJSEvent event) const {
    auto key = std::make_pair(currentState, event);
    return transitionTable.find(key) != transitionTable.end();
}

void CHTLJSStateMachine::pushState(CHTLJSState state) {
    stateStack.push(state);
}

void CHTLJSStateMachine::popState() {
    if (!stateStack.empty()) {
        currentState = stateStack.top();
        stateStack.pop();
    }
}

void CHTLJSStateMachine::reset() {
    currentState = CHTLJSState::Default;
    while (!stateStack.empty()) {
        stateStack.pop();
    }
    unquotedContext = UnquotedLiteralContext();
}

std::string CHTLJSStateMachine::getStateString() const {
    switch (currentState) {
        case CHTLJSState::Default: return "Default";
        case CHTLJSState::InScript: return "InScript";
        case CHTLJSState::InExpression: return "InExpression";
        case CHTLJSState::InEnhancedSelector: return "InEnhancedSelector";
        case CHTLJSState::InObjectLiteral: return "InObjectLiteral";
        case CHTLJSState::InObjectProperty: return "InObjectProperty";
        case CHTLJSState::InObjectValue: return "InObjectValue";
        case CHTLJSState::InUnquotedContext: return "InUnquotedContext";
        case CHTLJSState::InListenCall: return "InListenCall";
        case CHTLJSState::InDelegateCall: return "InDelegateCall";
        case CHTLJSState::InAnimateCall: return "InAnimateCall";
        default: return "Unknown";
    }
}

std::string CHTLJSStateMachine::getEventString(CHTLJSEvent event) const {
    switch (event) {
        case CHTLJSEvent::EnterScript: return "EnterScript";
        case CHTLJSEvent::ExitScript: return "ExitScript";
        case CHTLJSEvent::StartEnhancedSelector: return "StartEnhancedSelector";
        case CHTLJSEvent::EndEnhancedSelector: return "EndEnhancedSelector";
        case CHTLJSEvent::StartObject: return "StartObject";
        case CHTLJSEvent::EndObject: return "EndObject";
        case CHTLJSEvent::StartProperty: return "StartProperty";
        case CHTLJSEvent::Colon: return "Colon";
        case CHTLJSEvent::StartUnquotedLiteral: return "StartUnquotedLiteral";
        case CHTLJSEvent::EndUnquotedLiteral: return "EndUnquotedLiteral";
        default: return "Unknown";
    }
}

// 辅助函数实现
namespace CHTLJSStateMachineHelper {

CHTLJSEvent detectUnquotedContextStart(const std::string& token) {
    // 检测是否是开始对象的标记
    if (token == "{") {
        return CHTLJSEvent::StartObject;
    }
    
    // 检测是否是属性名
    if (token.find(':') == std::string::npos && 
        token.find('{') == std::string::npos &&
        token.find('}') == std::string::npos) {
        return CHTLJSEvent::StartProperty;
    }
    
    // 检测是否是冒号
    if (token == ":") {
        return CHTLJSEvent::Colon;
    }
    
    return CHTLJSEvent::InvalidSyntax;
}

bool isValidUnquotedValue(const std::string& value, UnquotedLiteralContext::Type context) {
    UnquotedLiteralContext ctx;
    ctx.type = context;
    ctx.allowsUnquoted = true;
    return ctx.isValidUnquoted(value);
}

std::string quoteUnquotedLiteral(const std::string& value) {
    // 如果值包含特殊字符，使用双引号
    if (value.find('\'') != std::string::npos) {
        return "\"" + value + "\"";
    }
    // 否则使用单引号
    return "'" + value + "'";
}

} // namespace CHTLJSStateMachineHelper

} // namespace chtl