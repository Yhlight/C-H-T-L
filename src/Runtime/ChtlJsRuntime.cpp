#include "Runtime/ChtlJsRuntime.h"
#include <sstream>
#include <regex>
#include <algorithm>
#include <iomanip>

namespace chtl {

void ChtlJsRuntime::collectLocalScript(const std::string& scriptCode, const std::string& elementId) {
    // 创建增强器处理代码
    ChtlJsEnhancer enhancer;
    enhancer.setElementContext(elementId);
    enhancer.enterLocalScriptBlock();
    
    // 应用增强语法转换
    std::string enhancedCode = enhancer.processScript(scriptCode);
    
    // 处理{{&}}语法
    std::string processedCode = processAmpersandSyntax(enhancedCode, elementId);
    
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
    
    // 生成增强方法
    code << generateEnhancedMethods();
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

std::string ChtlJsRuntime::generateEnhancedMethods() {
    std::stringstream code;
    
    // listen方法 - 快捷事件绑定
    code << "  // Enhanced listen method for quick event binding\n";
    code << "  function addListenMethod(element) {\n";
    code << "    if (!element || typeof element !== 'object') return element;\n";
    code << "    \n";
    code << "    // Add listen method if not exists\n";
    code << "    if (!element.listen) {\n";
    code << "      element.listen = function(events) {\n";
    code << "        for (const [eventType, handler] of Object.entries(events)) {\n";
    code << "          if (typeof handler === 'function') {\n";
    code << "            this.addEventListener(eventType, handler);\n";
    code << "          }\n";
    code << "        }\n";
    code << "        return this;\n";
    code << "      };\n";
    code << "    }\n";
    code << "    \n";
    code << "    // Add to NodeList\n";
    code << "    if (element instanceof NodeList) {\n";
    code << "      element.listen = function(events) {\n";
    code << "        this.forEach(el => addListenMethod(el).listen(events));\n";
    code << "        return this;\n";
    code << "      };\n";
    code << "    }\n";
    code << "    \n";
    code << "    return element;\n";
    code << "  }\n";
    code << "  \n";
    
    // animate方法 - 动画支持
    code << "  // Enhanced animate method\n";
    code << "  window.CHTL.animate = function(config) {\n";
    code << "    const {\n";
    code << "      duration = 1000,\n";
    code << "      easing = 'ease-in-out',\n";
    code << "      begin = {},\n";
    code << "      end = {},\n";
    code << "      when = [],\n";
    code << "      loop = 1,\n";
    code << "      direction = 'normal',\n";
    code << "      delay = 0,\n";
    code << "      callback,\n";
    code << "      target\n";
    code << "    } = config;\n";
    code << "    \n";
    code << "    if (!target) {\n";
    code << "      console.error('Animation target not specified');\n";
    code << "      return;\n";
    code << "    }\n";
    code << "    \n";
    code << "    let startTime = null;\n";
    code << "    let currentLoop = 0;\n";
    code << "    let animationId = null;\n";
    code << "    \n";
    code << "    // Easing functions\n";
    code << "    const easings = {\n";
    code << "      'linear': t => t,\n";
    code << "      'ease-in': t => t * t,\n";
    code << "      'ease-out': t => t * (2 - t),\n";
    code << "      'ease-in-out': t => t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t\n";
    code << "    };\n";
    code << "    \n";
    code << "    const easingFunc = easings[easing] || easings['linear'];\n";
    code << "    \n";
    code << "    // Apply styles\n";
    code << "    function applyStyles(element, styles) {\n";
    code << "      Object.entries(styles).forEach(([prop, value]) => {\n";
    code << "        if (prop === 'transform') {\n";
    code << "          element.style.transform = value;\n";
    code << "        } else {\n";
    code << "          element.style[prop] = value;\n";
    code << "        }\n";
    code << "      });\n";
    code << "    }\n";
    code << "    \n";
    code << "    // Interpolate values\n";
    code << "    function interpolate(from, to, progress) {\n";
    code << "      if (typeof from === 'number' && typeof to === 'number') {\n";
    code << "        return from + (to - from) * progress;\n";
    code << "      }\n";
    code << "      return progress < 0.5 ? from : to;\n";
    code << "    }\n";
    code << "    \n";
    code << "    // Animation frame\n";
    code << "    function animate(timestamp) {\n";
    code << "      if (!startTime) {\n";
    code << "        startTime = timestamp - delay;\n";
    code << "        applyStyles(target, begin);\n";
    code << "      }\n";
    code << "      \n";
    code << "      const elapsed = timestamp - startTime - delay;\n";
    code << "      if (elapsed < 0) {\n";
    code << "        animationId = requestAnimationFrame(animate);\n";
    code << "        return;\n";
    code << "      }\n";
    code << "      \n";
    code << "      let progress = Math.min(elapsed / duration, 1);\n";
    code << "      if (direction === 'reverse') progress = 1 - progress;\n";
    code << "      \n";
    code << "      const easedProgress = easingFunc(progress);\n";
    code << "      \n";
    code << "      // Apply keyframes\n";
    code << "      const currentKeyframe = when.find(kf => kf.at >= easedProgress) || { ...end, at: 1 };\n";
    code << "      const prevKeyframe = when.filter(kf => kf.at < easedProgress).pop() || { ...begin, at: 0 };\n";
    code << "      \n";
    code << "      const keyframeProgress = (easedProgress - prevKeyframe.at) / (currentKeyframe.at - prevKeyframe.at);\n";
    code << "      \n";
    code << "      // Interpolate and apply styles\n";
    code << "      const interpolatedStyles = {};\n";
    code << "      Object.keys({...prevKeyframe, ...currentKeyframe}).forEach(key => {\n";
    code << "        if (key !== 'at' && prevKeyframe[key] !== undefined && currentKeyframe[key] !== undefined) {\n";
    code << "          interpolatedStyles[key] = interpolate(prevKeyframe[key], currentKeyframe[key], keyframeProgress);\n";
    code << "        }\n";
    code << "      });\n";
    code << "      \n";
    code << "      applyStyles(target, interpolatedStyles);\n";
    code << "      \n";
    code << "      // Check if animation is complete\n";
    code << "      if (progress >= 1) {\n";
    code << "        currentLoop++;\n";
    code << "        if (loop === -1 || currentLoop < loop) {\n";
    code << "          startTime = timestamp;\n";
    code << "          if (direction === 'alternate') {\n";
    code << "            direction = direction === 'normal' ? 'reverse' : 'normal';\n";
    code << "          }\n";
    code << "          animationId = requestAnimationFrame(animate);\n";
    code << "        } else {\n";
    code << "          applyStyles(target, end);\n";
    code << "          if (callback) callback();\n";
    code << "        }\n";
    code << "      } else {\n";
    code << "        animationId = requestAnimationFrame(animate);\n";
    code << "      }\n";
    code << "    }\n";
    code << "    \n";
    code << "    animationId = requestAnimationFrame(animate);\n";
    code << "    \n";
    code << "    // Return control object\n";
    code << "    return {\n";
    code << "      stop: () => {\n";
    code << "        if (animationId) {\n";
    code << "          cancelAnimationFrame(animationId);\n";
    code << "          animationId = null;\n";
    code << "        }\n";
    code << "      }\n";
    code << "    };\n";
    code << "  };\n";
    code << "  \n";
    
    // 修改原生方法以支持listen
    code << "  // Enhance native methods\n";
    code << "  const originalGetElementById = document.getElementById;\n";
    code << "  document.getElementById = function(...args) {\n";
    code << "    const element = originalGetElementById.apply(document, args);\n";
    code << "    return addListenMethod(element);\n";
    code << "  };\n";
    code << "  \n";
    code << "  const originalGetElementsByClassName = document.getElementsByClassName;\n";
    code << "  document.getElementsByClassName = function(...args) {\n";
    code << "    const elements = originalGetElementsByClassName.apply(document, args);\n";
    code << "    return addListenMethod(elements);\n";
    code << "  };\n";
    code << "  \n";
    code << "  const originalGetElementsByTagName = document.getElementsByTagName;\n";
    code << "  document.getElementsByTagName = function(...args) {\n";
    code << "    const elements = originalGetElementsByTagName.apply(document, args);\n";
    code << "    return addListenMethod(elements);\n";
    code << "  };\n";
    code << "  \n";
    code << "  const originalQuerySelector = document.querySelector;\n";
    code << "  document.querySelector = function(...args) {\n";
    code << "    const element = originalQuerySelector.apply(document, args);\n";
    code << "    return addListenMethod(element);\n";
    code << "  };\n";
    code << "  \n";
    code << "  const originalQuerySelectorAll = document.querySelectorAll;\n";
    code << "  document.querySelectorAll = function(...args) {\n";
    code << "    const elements = originalQuerySelectorAll.apply(document, args);\n";
    code << "    return addListenMethod(elements);\n";
    code << "  };\n";
    
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
    
    // 转换animate调用
    processed = transformAnimateSyntax(processed);
    
    // 如果在局部script块中，包装代码
    if (inLocalScriptBlock_ && !currentElementId_.empty()) {
        processed = wrapLocalScript(processed, currentElementId_);
    }
    
    return processed;
}

std::string ChtlJsEnhancer::transformSelectorSyntax(const std::string& code) {
    std::string result = code;
    
    // 匹配增强选择器模式 {{selector}} 或 {{selector[index]}}
    // 不匹配 {{&}} 和后面跟着 -> 的情况
    std::regex selectorRegex(R"(\{\{(?!&)([^}]+?)\}\}(?!->))");
    std::smatch match;
    std::string::const_iterator searchStart(result.cbegin());
    std::string processed;
    
    while (std::regex_search(searchStart, result.cend(), match, selectorRegex)) {
        processed += std::string(searchStart, match[0].first);
        
        std::string selector = match[1];
        std::string transformed;
        
        // 检查是否有数组索引访问 selector[index]
        std::regex indexRegex(R"(^(.+?)\[(\d+)\]$)");
        std::smatch indexMatch;
        
        if (std::regex_match(selector, indexMatch, indexRegex)) {
            // 有索引访问
            std::string baseSelector = indexMatch[1];
            std::string index = indexMatch[2];
            
            // 去除前后空格
            baseSelector.erase(0, baseSelector.find_first_not_of(" \t"));
            baseSelector.erase(baseSelector.find_last_not_of(" \t") + 1);
            
            transformed = transformSingleSelector(baseSelector, index);
        } else {
            // 无索引访问
            selector.erase(0, selector.find_first_not_of(" \t"));
            selector.erase(selector.find_last_not_of(" \t") + 1);
            
            transformed = transformSingleSelector(selector);
        }
        
        processed += transformed;
        searchStart = match[0].second;
    }
    
    processed += std::string(searchStart, result.cend());
    
    // 处理 -> 操作符（CHTL语法标识）
    // -> 直接替换为 . 
    std::regex arrowRegex(R"(->)");
    result = std::regex_replace(processed, arrowRegex, ".");
    
    return result;
}

std::string ChtlJsEnhancer::transformSingleSelector(const std::string& selector, const std::string& index) {
    std::string result;
    
    // 判断选择器类型
    if (selector.empty()) {
        return "null";
    }
    
    // 检查是否是复合选择器（包含空格）
    bool isCompound = selector.find(' ') != std::string::npos;
    
    if (isCompound) {
        // 复合选择器，使用querySelectorAll
        result = "document.querySelectorAll('" + selector + "')";
        if (!index.empty()) {
            result += "[" + index + "]";
        }
    } else if (selector[0] == '.') {
        // 类选择器
        if (index.empty()) {
            result = "document.querySelectorAll('" + selector + "')";
        } else {
            result = "document.getElementsByClassName('" + selector.substr(1) + "')[" + index + "]";
        }
    } else if (selector[0] == '#') {
        // ID选择器
        result = "document.getElementById('" + selector.substr(1) + "')";
    } else {
        // 无修饰符选择器：先尝试标签，再尝试ID，最后尝试类
        if (index.empty()) {
            // 先尝试标签，再尝试ID，最后尝试类
            result = "(document.getElementsByTagName('" + selector + "')[0] || " +
                     "document.getElementById('" + selector + "') || " +
                     "document.getElementsByClassName('" + selector + "')[0])";
        } else {
            // 有索引，肯定是标签选择器
            result = "document.getElementsByTagName('" + selector + "')[" + index + "]";
        }
    }
    
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

std::string ChtlJsEnhancer::transformAnimateSyntax(const std::string& code) {
    std::string result = code;
    
    // 匹配 animate({ ... }) 调用
    std::regex animateRegex(R"(animate\s*\(\s*\{)");
    
    // 查找所有animate调用的位置
    std::smatch match;
    std::string::const_iterator searchStart(result.cbegin());
    std::string processed;
    
    while (std::regex_search(searchStart, result.cend(), match, animateRegex)) {
        // 添加匹配之前的内容
        processed += std::string(searchStart, match[0].first);
        
        // 找到animate调用，需要解析配置对象
        size_t braceStart = match[0].second - result.cbegin() - 1;
        size_t braceEnd = findMatchingBrace(result, braceStart);
        
        if (braceEnd != std::string::npos) {
            // 提取配置对象内容
            std::string configContent = result.substr(braceStart + 1, braceEnd - braceStart - 1);
            
            // 检查是否有target属性，如果没有，需要推断
            if (configContent.find("target:") == std::string::npos) {
                // 查找最近的选择器
                std::string targetSelector = findNearestSelector(processed);
                if (!targetSelector.empty()) {
                    // 在配置对象中添加target属性
                    configContent = "target: " + targetSelector + ", " + configContent;
                }
            }
            
            // 重构animate调用
            processed += "CHTL.animate({ " + configContent + " })";
            searchStart = result.cbegin() + braceEnd + 1;
        } else {
            // 没有找到匹配的括号，保持原样
            processed += match[0].str();
            searchStart = match[0].second;
        }
    }
    
    // 添加剩余内容
    processed += std::string(searchStart, result.cend());
    
    return processed;
}

size_t ChtlJsEnhancer::findMatchingBrace(const std::string& code, size_t startPos) {
    int braceCount = 1;
    bool inString = false;
    char stringChar = '\0';
    
    for (size_t i = startPos + 1; i < code.length(); ++i) {
        char ch = code[i];
        
        // 处理字符串
        if (!inString && (ch == '"' || ch == '\'' || ch == '`')) {
            inString = true;
            stringChar = ch;
        } else if (inString && ch == stringChar && code[i-1] != '\\') {
            inString = false;
        } else if (!inString) {
            if (ch == '{') {
                braceCount++;
            } else if (ch == '}') {
                braceCount--;
                if (braceCount == 0) {
                    return i;
                }
            }
        }
    }
    
    return std::string::npos;
}

std::string ChtlJsEnhancer::findNearestSelector(const std::string& code) {
    // 从后向前查找最近的选择器
    std::regex selectorRegex(R"((\{\{[^}]+\}\})\s*(?:->|\.))");
    std::smatch match;
    std::string::const_reverse_iterator searchStart(code.crbegin());
    
    if (std::regex_search(searchStart, code.crend(), match, selectorRegex)) {
        return match[1].str();
    }
    
    return "";
}

} // namespace chtl