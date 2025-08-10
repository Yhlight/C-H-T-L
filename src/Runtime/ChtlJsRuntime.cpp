#include "Runtime/ChtlJsRuntime.h"
#include <sstream>
#include <regex>
#include <algorithm>
#include <iomanip>

namespace chtl {

void ChtlJsRuntime::collectLocalScript(const std::string& scriptCode, const std::string& elementId) {
    // 处理{{&}}语法
    std::string processedCode = processAmpersandSyntax(scriptCode, elementId);
    
    // 解析并提取delegate调用
    auto delegations = parseDelegateCall(processedCode);
    for (const auto& delegation : delegations) {
        registerEventDelegation(delegation);
    }
    
    // 包装脚本代码
    std::stringstream wrapped;
    wrapped << "(function() {\n";
    wrapped << "  'use strict';\n";
    if (!elementId.empty()) {
        wrapped << "  const element = document.getElementById('" << elementId << "');\n";
        wrapped << "  if (!element) return;\n";
        wrapped << "  const {{&}} = element;\n";
    }
    wrapped << processedCode << "\n";
    wrapped << "})();\n";
    
    collectedScripts_.push_back(wrapped.str());
}

void ChtlJsRuntime::registerEventDelegation(const EventDelegation& delegation) {
    // 检查是否已注册过相同的处理函数
    if (registeredHandlers_.find(delegation.handlerId) != registeredHandlers_.end()) {
        return;
    }
    
    // 添加到对应父元素的委托列表
    eventDelegations_[delegation.parentSelector].push_back(delegation);
    registeredHandlers_.insert(delegation.handlerId);
}

std::string ChtlJsRuntime::generateRuntimeCode() {
    std::stringstream code;
    
    // CHTL JS运行时环境
    code << "// CHTL JS Runtime Environment\n";
    code << "(function(window) {\n";
    code << "  'use strict';\n";
    code << "  \n";
    code << "  // Initialize CHTL namespace\n";
    code << "  window.CHTL = window.CHTL || {};\n";
    code << "  window.CHTL.runtime = window.CHTL.runtime || {};\n";
    code << "  \n";
    
    // 生成delegate函数
    code << generateDelegateFunction();
    code << "  \n";
    
    // 生成选择器辅助函数
    code << "  // Selector helper function\n";
    code << "  window.CHTL.$ = function(selector) {\n";
    code << "    if (typeof selector === 'string') {\n";
    code << "      return document.querySelector(selector);\n";
    code << "    }\n";
    code << "    return selector;\n";
    code << "  };\n";
    code << "  \n";
    code << "  window.CHTL.$$ = function(selector) {\n";
    code << "    if (typeof selector === 'string') {\n";
    code << "      return document.querySelectorAll(selector);\n";
    code << "    }\n";
    code << "    return selector;\n";
    code << "  };\n";
    code << "  \n";
    
    // 生成事件委托注册代码
    if (!eventDelegations_.empty()) {
        code << "  // Register event delegations\n";
        code << generateDelegationCode();
    }
    
    code << "})(window);\n\n";
    
    // 添加收集的局部脚本
    if (!collectedScripts_.empty()) {
        code << "// Collected local scripts\n";
        for (const auto& script : collectedScripts_) {
            code << script << "\n";
        }
    }
    
    return code.str();
}

std::string ChtlJsRuntime::generateDelegateFunction() {
    std::stringstream code;
    
    code << "  // Event delegation function\n";
    code << "  window.CHTL.delegate = function(parentSelector, config) {\n";
    code << "    const parent = typeof parentSelector === 'string' ? \n";
    code << "      document.querySelector(parentSelector) : parentSelector;\n";
    code << "    \n";
    code << "    if (!parent) {\n";
    code << "      console.warn('Parent element not found:', parentSelector);\n";
    code << "      return;\n";
    code << "    }\n";
    code << "    \n";
    code << "    // Normalize target selectors\n";
    code << "    const targetSelectors = Array.isArray(config.target) ? \n";
    code << "      config.target : [config.target];\n";
    code << "    \n";
    code << "    // Get event handlers\n";
    code << "    const events = Object.keys(config).filter(key => key !== 'target');\n";
    code << "    \n";
    code << "    // Create delegation key for deduplication\n";
    code << "    const delegationKey = parentSelector + '::' + targetSelectors.join(',');\n";
    code << "    \n";
    code << "    // Check if delegation already exists\n";
    code << "    parent.__delegations = parent.__delegations || {};\n";
    code << "    \n";
    code << "    events.forEach(eventType => {\n";
    code << "      const eventKey = delegationKey + '::' + eventType;\n";
    code << "      \n";
    code << "      // Skip if already delegated\n";
    code << "      if (parent.__delegations[eventKey]) return;\n";
    code << "      \n";
    code << "      // Create delegated handler\n";
    code << "      const handler = function(e) {\n";
    code << "        let target = e.target;\n";
    code << "        \n";
    code << "        // Walk up the DOM tree\n";
    code << "        while (target && target !== parent) {\n";
    code << "          // Check if target matches any selector\n";
    code << "          for (const selector of targetSelectors) {\n";
    code << "            if (target.matches(selector)) {\n";
    code << "              // Call handler with correct context\n";
    code << "              config[eventType].call(target, e);\n";
    code << "              return;\n";
    code << "            }\n";
    code << "          }\n";
    code << "          target = target.parentElement;\n";
    code << "        }\n";
    code << "      };\n";
    code << "      \n";
    code << "      // Add event listener\n";
    code << "      parent.addEventListener(eventType, handler);\n";
    code << "      parent.__delegations[eventKey] = handler;\n";
    code << "    });\n";
    code << "  };\n";
    
    return code.str();
}

std::string ChtlJsRuntime::generateDelegationCode() {
    std::stringstream code;
    
    code << "  document.addEventListener('DOMContentLoaded', function() {\n";
    
    for (const auto& [parentSelector, delegations] : eventDelegations_) {
        // 按事件类型分组
        std::unordered_map<std::string, std::vector<const EventDelegation*>> byEvent;
        for (const auto& delegation : delegations) {
            byEvent[delegation.eventType].push_back(&delegation);
        }
        
        // 生成每个事件类型的委托
        for (const auto& [eventType, eventDelegations] : byEvent) {
            code << "    // Delegation for " << parentSelector << " - " << eventType << "\n";
            code << "    CHTL.delegate('" << parentSelector << "', {\n";
            
            // 收集所有目标选择器
            std::set<std::string> allTargets;
            for (const auto* del : eventDelegations) {
                allTargets.insert(del->targetSelectors.begin(), del->targetSelectors.end());
            }
            
            // 生成目标选择器数组
            code << "      target: [";
            bool first = true;
            for (const auto& target : allTargets) {
                if (!first) code << ", ";
                code << "'" << target << "'";
                first = false;
            }
            code << "],\n";
            
            // 生成事件处理函数
            code << "      " << eventType << ": function(e) {\n";
            code << "        const target = this;\n";
            
            // 为每个委托生成条件检查
            for (const auto* del : eventDelegations) {
                if (del->targetSelectors.size() > 1) {
                    code << "        if (";
                    bool firstSelector = true;
                    for (const auto& selector : del->targetSelectors) {
                        if (!firstSelector) code << " || ";
                        code << "target.matches('" << selector << "')";
                        firstSelector = false;
                    }
                    code << ") {\n";
                } else {
                    code << "        if (target.matches('" << del->targetSelectors[0] << "')) {\n";
                }
                code << "          " << del->handlerCode << "\n";
                code << "        }\n";
            }
            
            code << "      }\n";
            code << "    });\n";
        }
    }
    
    code << "  });\n";
    
    return code.str();
}

std::string ChtlJsRuntime::processAmpersandSyntax(const std::string& code, const std::string& elementContext) {
    if (elementContext.empty()) {
        return code;
    }
    
    // 替换 {{&}} 为元素引用
    std::regex ampersandRegex(R"(\{\{&\}\})");
    std::string result = std::regex_replace(code, ampersandRegex, 
        "document.getElementById('" + elementContext + "')");
    
    return result;
}

std::vector<EventDelegation> ChtlJsRuntime::parseDelegateCall(const std::string& code) {
    std::vector<EventDelegation> delegations;
    
    // 简化的delegate调用解析（实际实现需要更复杂的解析器）
    std::regex delegateRegex(R"(\{\{([^}]+)\}\}->delegate\s*\()");
    std::smatch match;
    
    std::string::const_iterator searchStart(code.cbegin());
    while (std::regex_search(searchStart, code.cend(), match, delegateRegex)) {
        EventDelegation delegation;
        delegation.parentSelector = match[1];
        
        // TODO: 解析delegate调用的完整参数
        // 这里需要一个更复杂的JavaScript解析器
        
        searchStart = match.suffix().first;
    }
    
    return delegations;
}

std::string ChtlJsRuntime::generateElementId() {
    std::stringstream id;
    id << "chtl-element-" << std::setfill('0') << std::setw(6) << elementIdCounter_++;
    return id.str();
}

void ChtlJsRuntime::reset() {
    eventDelegations_.clear();
    collectedScripts_.clear();
    registeredHandlers_.clear();
    elementIdCounter_ = 0;
}

// ChtlJsEnhancer实现

std::string ChtlJsEnhancer::processScript(const std::string& scriptCode) {
    std::string processed = scriptCode;
    
    // 转换选择器语法
    processed = transformSelectorSyntax(processed);
    
    // 如果在局部script块中，包装代码
    if (inLocalScriptBlock_ && !currentElementId_.empty()) {
        processed = wrapLocalScript(processed, currentElementId_);
    }
    
    return processed;
}

std::string ChtlJsEnhancer::transformSelectorSyntax(const std::string& code) {
    // 转换 {{selector}} 为 document.querySelector(selector)
    std::regex selectorRegex(R"(\{\{([^}]+)\}\}(?!->))");
    std::string result = std::regex_replace(code, selectorRegex, 
        "document.querySelector('$1')");
    
    return result;
}

std::string ChtlJsEnhancer::wrapLocalScript(const std::string& code, const std::string& elementId) {
    // 局部script已经在runtime中处理
    return code;
}

std::string ChtlJsEnhancer::extractDelegateCalls(const std::string& code) {
    // 提取并转换delegate调用
    std::regex delegateRegex(R"(\{\{([^}]+)\}\}->delegate\s*\(([^)]+)\))");
    std::string result = std::regex_replace(code, delegateRegex,
        "CHTL.delegate('$1', $2)");
    
    return result;
}

} // namespace chtl