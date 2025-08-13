#include "CHTLStateMachine.h"
#include <algorithm>

namespace chtl {

CHTLStateMachine::CHTLStateMachine() : currentState(CHTLState::INITIAL) {
    initializeTransitionTable();
}

void CHTLStateMachine::initializeTransitionTable() {
    // 初始状态转换
    transitionTable[CHTLState::INITIAL] = {
        {CHTLEvent::IDENTIFIER, CHTLState::IN_ELEMENT},
        {CHTLEvent::KEYWORD_TEXT, CHTLState::IN_TEXT},
        {CHTLEvent::KEYWORD_TEMPLATE, CHTLState::IN_TEMPLATE},
        {CHTLEvent::KEYWORD_CUSTOM, CHTLState::IN_CUSTOM},
        {CHTLEvent::KEYWORD_CONFIGURATION, CHTLState::IN_CONFIGURATION},
        {CHTLEvent::KEYWORD_NAMESPACE, CHTLState::IN_NAMESPACE},
        {CHTLEvent::KEYWORD_IMPORT, CHTLState::IN_IMPORT},
        {CHTLEvent::KEYWORD_ORIGIN, CHTLState::IN_ORIGIN}
    };
    
    // 元素内部状态转换
    transitionTable[CHTLState::IN_ELEMENT] = {
        {CHTLEvent::OPEN_BRACE, CHTLState::IN_ELEMENT},
        {CHTLEvent::CLOSE_BRACE, CHTLState::INITIAL},
        {CHTLEvent::IDENTIFIER, CHTLState::IN_ATTRIBUTE},
        {CHTLEvent::KEYWORD_STYLE, CHTLState::IN_STYLE},
        {CHTLEvent::KEYWORD_SCRIPT, CHTLState::IN_SCRIPT},
        {CHTLEvent::KEYWORD_TEXT, CHTLState::IN_TEXT},
        {CHTLEvent::KEYWORD_EXCEPT, CHTLState::IN_EXCEPT_CONSTRAINT},
        {CHTLEvent::AT_STYLE, CHTLState::IN_ATTRIBUTE},
        {CHTLEvent::AT_ELEMENT, CHTLState::IN_ATTRIBUTE}
    };
    
    // 样式块状态转换
    transitionTable[CHTLState::IN_STYLE] = {
        {CHTLEvent::OPEN_BRACE, CHTLState::IN_STYLE},
        {CHTLEvent::CLOSE_BRACE, CHTLState::IN_ELEMENT},
        {CHTLEvent::IDENTIFIER, CHTLState::IN_STYLE_PROPERTY},
        {CHTLEvent::AT_STYLE, CHTLState::IN_TEMPLATE_INHERITANCE}
    };
    
    // 模板声明状态转换
    transitionTable[CHTLState::IN_TEMPLATE] = {
        {CHTLEvent::AT_STYLE, CHTLState::IN_TEMPLATE},
        {CHTLEvent::AT_ELEMENT, CHTLState::IN_TEMPLATE},
        {CHTLEvent::AT_VAR, CHTLState::IN_TEMPLATE},
        {CHTLEvent::IDENTIFIER, CHTLState::IN_TEMPLATE},
        {CHTLEvent::OPEN_BRACE, CHTLState::IN_TEMPLATE}
    };
    
    // 自定义声明状态转换
    transitionTable[CHTLState::IN_CUSTOM] = {
        {CHTLEvent::AT_STYLE, CHTLState::IN_CUSTOM},
        {CHTLEvent::AT_ELEMENT, CHTLState::IN_CUSTOM},
        {CHTLEvent::AT_VAR, CHTLState::IN_CUSTOM},
        {CHTLEvent::IDENTIFIER, CHTLState::IN_CUSTOM},
        {CHTLEvent::OPEN_BRACE, CHTLState::IN_SPECIALIZATION}
    };
    
    // 特例化块状态转换
    transitionTable[CHTLState::IN_SPECIALIZATION] = {
        {CHTLEvent::KEYWORD_DELETE, CHTLState::IN_DELETE_STATEMENT},
        {CHTLEvent::KEYWORD_INSERT, CHTLState::IN_INSERT_STATEMENT},
        {CHTLEvent::CLOSE_BRACE, CHTLState::IN_CUSTOM}
    };
}

bool CHTLStateMachine::processEvent(CHTLEvent event) {
    auto stateIt = transitionTable.find(currentState);
    if (stateIt == transitionTable.end()) {
        addError("No transition table for current state: " + stateToString(currentState));
        return false;
    }
    
    auto eventIt = stateIt->second.find(event);
    if (eventIt == stateIt->second.end()) {
        addError("Invalid event " + eventToString(event) + " in state " + stateToString(currentState));
        return false;
    }
    
    CHTLState newState = eventIt->second;
    if (!isValidTransition(currentState, event, newState)) {
        addError("Invalid transition from " + stateToString(currentState) + 
                " to " + stateToString(newState) + " with event " + eventToString(event));
        return false;
    }
    
    currentState = newState;
    return true;
}

void CHTLStateMachine::pushState(CHTLState state) {
    stateStack.push(currentState);
    currentState = state;
}

bool CHTLStateMachine::popState() {
    if (stateStack.empty()) {
        addError("Cannot pop state: stack is empty");
        return false;
    }
    
    currentState = stateStack.top();
    stateStack.pop();
    return true;
}

bool CHTLStateMachine::canUseFeature(const std::string& feature) const {
    // 检查在当前状态下是否可以使用某个特性
    if (feature == "style" && currentState == CHTLState::IN_ELEMENT) {
        return true;
    }
    if (feature == "script" && currentState == CHTLState::IN_ELEMENT) {
        return true;
    }
    if (feature == "template" && currentState == CHTLState::INITIAL) {
        return true;
    }
    if (feature == "custom" && currentState == CHTLState::INITIAL) {
        return true;
    }
    if (feature == "delete" && currentState == CHTLState::IN_SPECIALIZATION) {
        return true;
    }
    if (feature == "insert" && currentState == CHTLState::IN_SPECIALIZATION) {
        return true;
    }
    
    return false;
}

void CHTLStateMachine::reset() {
    currentState = CHTLState::INITIAL;
    while (!stateStack.empty()) {
        stateStack.pop();
    }
    errors.clear();
}

void CHTLStateMachine::addError(const std::string& error) {
    errors.push_back(error);
}

bool CHTLStateMachine::isInValidState() const {
    return currentState != CHTLState::ERROR;
}

bool CHTLStateMachine::canTransitionTo(CHTLState targetState) const {
    auto stateIt = transitionTable.find(currentState);
    if (stateIt == transitionTable.end()) {
        return false;
    }
    
    for (const auto& [event, state] : stateIt->second) {
        if (state == targetState) {
            return true;
        }
    }
    
    return false;
}

bool CHTLStateMachine::isValidTransition(CHTLState from, CHTLEvent event, CHTLState to) {
    // 基本验证逻辑
    // 可以根据CHTL语法规则添加更多验证
    
    // 不能从错误状态转换
    if (from == CHTLState::ERROR) {
        return false;
    }
    
    // 特殊验证规则
    if (from == CHTLState::IN_STYLE && to == CHTLState::IN_SCRIPT) {
        return false;  // 不能直接从style转到script
    }
    
    return true;
}

std::string CHTLStateMachine::getCurrentStateString() const {
    return stateToString(currentState);
}

std::string CHTLStateMachine::stateToString(CHTLState state) {
    switch (state) {
        case CHTLState::INITIAL: return "INITIAL";
        case CHTLState::IN_ELEMENT: return "IN_ELEMENT";
        case CHTLState::IN_TEXT: return "IN_TEXT";
        case CHTLState::IN_STYLE: return "IN_STYLE";
        case CHTLState::IN_SCRIPT: return "IN_SCRIPT";
        case CHTLState::IN_TEMPLATE: return "IN_TEMPLATE";
        case CHTLState::IN_CUSTOM: return "IN_CUSTOM";
        case CHTLState::IN_CONFIGURATION: return "IN_CONFIGURATION";
        case CHTLState::IN_NAMESPACE: return "IN_NAMESPACE";
        case CHTLState::IN_IMPORT: return "IN_IMPORT";
        case CHTLState::IN_ORIGIN: return "IN_ORIGIN";
        case CHTLState::IN_ATTRIBUTE: return "IN_ATTRIBUTE";
        case CHTLState::IN_STYLE_SELECTOR: return "IN_STYLE_SELECTOR";
        case CHTLState::IN_STYLE_PROPERTY: return "IN_STYLE_PROPERTY";
        case CHTLState::IN_TEMPLATE_INHERITANCE: return "IN_TEMPLATE_INHERITANCE";
        case CHTLState::IN_SPECIALIZATION: return "IN_SPECIALIZATION";
        case CHTLState::IN_DELETE_STATEMENT: return "IN_DELETE_STATEMENT";
        case CHTLState::IN_INSERT_STATEMENT: return "IN_INSERT_STATEMENT";
        case CHTLState::IN_EXCEPT_CONSTRAINT: return "IN_EXCEPT_CONSTRAINT";
        case CHTLState::IN_ORIGIN_HTML: return "IN_ORIGIN_HTML";
        case CHTLState::IN_ORIGIN_STYLE: return "IN_ORIGIN_STYLE";
        case CHTLState::IN_ORIGIN_JAVASCRIPT: return "IN_ORIGIN_JAVASCRIPT";
        case CHTLState::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string CHTLStateMachine::eventToString(CHTLEvent event) {
    switch (event) {
        case CHTLEvent::OPEN_BRACE: return "{";
        case CHTLEvent::CLOSE_BRACE: return "}";
        case CHTLEvent::OPEN_BRACKET: return "[";
        case CHTLEvent::CLOSE_BRACKET: return "]";
        case CHTLEvent::SEMICOLON: return ";";
        case CHTLEvent::COLON: return ":";
        case CHTLEvent::EQUALS: return "=";
        case CHTLEvent::COMMA: return ",";
        case CHTLEvent::KEYWORD_TEXT: return "text";
        case CHTLEvent::KEYWORD_STYLE: return "style";
        case CHTLEvent::KEYWORD_SCRIPT: return "script";
        case CHTLEvent::KEYWORD_TEMPLATE: return "[Template]";
        case CHTLEvent::KEYWORD_CUSTOM: return "[Custom]";
        case CHTLEvent::KEYWORD_CONFIGURATION: return "[Configuration]";
        case CHTLEvent::KEYWORD_NAMESPACE: return "[Namespace]";
        case CHTLEvent::KEYWORD_IMPORT: return "[Import]";
        case CHTLEvent::KEYWORD_ORIGIN: return "[Origin]";
        case CHTLEvent::KEYWORD_DELETE: return "delete";
        case CHTLEvent::KEYWORD_INSERT: return "insert";
        case CHTLEvent::KEYWORD_EXCEPT: return "except";
        case CHTLEvent::KEYWORD_INHERIT: return "inherit";
        case CHTLEvent::KEYWORD_FROM: return "from";
        case CHTLEvent::KEYWORD_AS: return "as";
        case CHTLEvent::AT_STYLE: return "@Style";
        case CHTLEvent::AT_ELEMENT: return "@Element";
        case CHTLEvent::AT_VAR: return "@Var";
        case CHTLEvent::AT_HTML: return "@Html";
        case CHTLEvent::AT_JAVASCRIPT: return "@JavaScript";
        case CHTLEvent::AT_CHTL: return "@Chtl";
        case CHTLEvent::IDENTIFIER: return "IDENTIFIER";
        case CHTLEvent::STRING_LITERAL: return "STRING";
        case CHTLEvent::NUMBER_LITERAL: return "NUMBER";
        case CHTLEvent::EOF_EVENT: return "EOF";
        case CHTLEvent::UNKNOWN: return "UNKNOWN";
        default: return "UNDEFINED";
    }
}

} // namespace chtl