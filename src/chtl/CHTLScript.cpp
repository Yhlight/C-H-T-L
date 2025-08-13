#include "CHTLScript.h"
#include "CHTLGenerator.h"
#include "CHTLCJMOD.h"
#include "CHTLJSContext.h"
#include <regex>
#include <sstream>
#include <algorithm>
#include <set>

namespace chtl {

// ScriptManager 实现
void ScriptManager::addLocalScript(const std::string& elementPath, std::shared_ptr<ScriptBlock> script) {
    script->setScope(elementPath);
    localScripts[elementPath].push_back(script);
}

void ScriptManager::addGlobalScript(std::shared_ptr<ScriptBlock> script) {
    globalScripts.push_back(script);
}

std::vector<std::shared_ptr<ScriptBlock>> ScriptManager::getScriptsForElement(const std::string& elementPath) const {
    auto it = localScripts.find(elementPath);
    if (it != localScripts.end()) {
        return it->second;
    }
    return {};
}

std::string ScriptManager::generateScopeId(const std::string& elementPath) {
    auto it = scopeIdMap.find(elementPath);
    if (it != scopeIdMap.end()) {
        return it->second;
    }
    
    std::string scopeId = "chtl_scope_" + std::to_string(++scopeIdCounter);
    scopeIdMap[elementPath] = scopeId;
    return scopeId;
}

std::string ScriptManager::getScopeId(const std::string& elementPath) const {
    auto it = scopeIdMap.find(elementPath);
    if (it != scopeIdMap.end()) {
        return it->second;
    }
    return "";
}

void ScriptManager::processAllScripts() {
    // 处理所有局部脚本
    for (auto& [path, scripts] : localScripts) {
        for (auto& script : scripts) {
            if (!script->hasBeenProcessed()) {
                // TODO: 处理脚本内容
                script->markProcessed();
            }
        }
    }
    
    // 处理全局脚本
    for (auto& script : globalScripts) {
        if (!script->hasBeenProcessed()) {
            script->markProcessed();
        }
    }
}

std::string ScriptManager::generateJavaScript() const {
    std::stringstream js;
    
    // 生成CHTL运行时支持代码
    js << "// CHTL Runtime Support\n";
    js << "(function() {\n";
    js << "  'use strict';\n\n";
    
    // 生成作用域映射
    js << "  // Scope mappings\n";
    js << "  const CHTL_SCOPES = {\n";
    for (const auto& [path, scopeId] : scopeIdMap) {
        js << "    '" << ScriptHelper::escapeJavaScript(scopeId) << "': '" 
           << ScriptHelper::escapeJavaScript(path) << "',\n";
    }
    js << "  };\n\n";
    
    // 生成查询辅助函数
    js << "  // Query helper functions\n";
    js << "  function chtl_query(selector, scope) {\n";
    js << "    if (scope) {\n";
    js << "      const scopeEl = document.querySelector('[data-chtl-scope=\"' + scope + '\"]');\n";
    js << "      return scopeEl ? scopeEl.querySelectorAll(selector) : [];\n";
    js << "    }\n";
    js << "    return document.querySelectorAll(selector);\n";
    js << "  }\n\n";
    
    js << "  function chtl_queryOne(selector, scope) {\n";
    js << "    if (scope) {\n";
    js << "      const scopeEl = document.querySelector('[data-chtl-scope=\"' + scope + '\"]');\n";
    js << "      return scopeEl ? scopeEl.querySelector(selector) : null;\n";
    js << "    }\n";
    js << "    return document.querySelector(selector);\n";
    js << "  }\n\n";
    
    // 添加CHTL JS扩展运行时
    js << CHTLJSExtensions::RuntimeCodeGenerator::generateListenRuntime() << "\n";
    js << CHTLJSExtensions::RuntimeCodeGenerator::generateDelegateRuntime() << "\n";
    js << CHTLJSExtensions::RuntimeCodeGenerator::generateAnimateRuntime() << "\n";
    
    // 生成事件委托初始化
    js << CHTLJSExtensions::EventDelegationManager::generateDelegationInit() << "\n";
    
    // 生成局部脚本
    js << "  // Local scripts\n";
    for (const auto& [path, scripts] : localScripts) {
        std::string scopeId = getScopeId(path);
        if (!scopeId.empty()) {
            js << "  // Scripts for: " << path << "\n";
            js << "  (function() {\n";
            js << "    const __scope = '" << scopeId << "';\n";
            
            for (const auto& script : scripts) {
                js << script->getContent() << "\n";
            }
            
            js << "  })();\n\n";
        }
    }
    
    // 生成全局脚本
    if (!globalScripts.empty()) {
        js << "  // Global scripts\n";
        for (const auto& script : globalScripts) {
            js << script->getContent() << "\n";
        }
    }
    
    js << "})();\n";
    
    return js.str();
}

void ScriptManager::clear() {
    localScripts.clear();
    globalScripts.clear();
    scopeIdMap.clear();
    scopeIdCounter = 0;
}

// EnhancedSelectorProcessor 实现
EnhancedSelector EnhancedSelectorProcessor::parseSelector(const std::string& selectorStr) {
    EnhancedSelector selector;
    selector.selector = selectorStr;
    
    // 去除首尾空格
    std::string trimmed = selectorStr;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);
    
    // 检查是否有索引
    auto [baseSelector, index] = parseIndexedSelector(trimmed);
    if (index >= 0) {
        selector.hasIndex = true;
        selector.index = index;
        trimmed = baseSelector;
    }
    
    // 检查是否是后代选择器
    if (trimmed.find(' ') != std::string::npos) {
        selector.type = SelectorType::DESCENDANT;
        size_t spacePos = trimmed.find(' ');
        selector.primaryTarget = trimmed.substr(0, spacePos);
        selector.secondaryTarget = trimmed.substr(spacePos + 1);
        
        // 去除次要目标的空格
        selector.secondaryTarget.erase(0, selector.secondaryTarget.find_first_not_of(" \t"));
        selector.secondaryTarget.erase(selector.secondaryTarget.find_last_not_of(" \t") + 1);
    } else {
        // 单一选择器
        selector.type = detectSelectorType(trimmed);
        selector.primaryTarget = trimmed;
        
        // 对于类和ID选择器，去除前缀符号
        if (selector.type == SelectorType::CLASS && selector.primaryTarget[0] == '.') {
            selector.primaryTarget = selector.primaryTarget.substr(1);
        } else if (selector.type == SelectorType::ID && selector.primaryTarget[0] == '#') {
            selector.primaryTarget = selector.primaryTarget.substr(1);
        }
    }
    
    return selector;
}

std::string EnhancedSelectorProcessor::toJavaScript(const EnhancedSelector& selector, 
                                                   const std::string& currentScope) {
    std::stringstream js;
    std::string queryFunc = selector.hasIndex ? "chtl_query" : "chtl_queryOne";
    
    // 构建CSS选择器字符串
    std::string cssSelector;
    switch (selector.type) {
        case SelectorType::TAG:
            cssSelector = selector.primaryTarget;
            break;
        case SelectorType::CLASS:
            cssSelector = "." + selector.primaryTarget;
            break;
        case SelectorType::ID:
            cssSelector = "#" + selector.primaryTarget;
            break;
        case SelectorType::AUTO:
            // 自动推断：先尝试ID，然后类，最后标签
            js << "(chtl_queryOne('#" << selector.primaryTarget << "', " 
               << (currentScope.empty() ? "null" : "'" + currentScope + "'") << ") || ";
            js << "chtl_queryOne('." << selector.primaryTarget << "', "
               << (currentScope.empty() ? "null" : "'" + currentScope + "'") << ") || ";
            js << "chtl_queryOne('" << selector.primaryTarget << "', "
               << (currentScope.empty() ? "null" : "'" + currentScope + "'") << "))";
            
            if (selector.hasIndex) {
                js << "[" << selector.index << "]";
            }
            return js.str();
        case SelectorType::DESCENDANT:
            cssSelector = selector.primaryTarget + " " + selector.secondaryTarget;
            break;
        case SelectorType::INDEXED:
            cssSelector = selector.primaryTarget;
            queryFunc = "chtl_query";  // 索引选择器总是返回数组
            break;
    }
    
    // 生成查询代码
    js << queryFunc << "('" << cssSelector << "', " 
       << (currentScope.empty() ? "null" : "'" + currentScope + "'") << ")";
    
    if (selector.hasIndex) {
        js << "[" << selector.index << "]";
    }
    
    return js.str();
}

SelectorType EnhancedSelectorProcessor::detectSelectorType(const std::string& selector) {
    if (selector.empty()) {
        return SelectorType::AUTO;
    }
    
    if (selector[0] == '.') {
        return SelectorType::CLASS;
    } else if (selector[0] == '#') {
        return SelectorType::ID;
    } else {
        // 检查是否是有效的HTML标签名
        static const std::set<std::string> htmlTags = {
            "a", "button", "div", "span", "p", "h1", "h2", "h3", "h4", "h5", "h6",
            "form", "input", "textarea", "select", "option", "table", "tr", "td", "th",
            "ul", "ol", "li", "img", "video", "audio", "canvas", "svg", "iframe",
            "header", "footer", "nav", "main", "section", "article", "aside"
        };
        
        if (htmlTags.find(selector) != htmlTags.end()) {
            return SelectorType::TAG;
        }
        
        return SelectorType::AUTO;
    }
}

std::pair<std::string, int> EnhancedSelectorProcessor::parseIndexedSelector(const std::string& selector) {
    std::regex indexRegex(R"((.+)\[(\d+)\]$)");
    std::smatch match;
    
    if (std::regex_match(selector, match, indexRegex)) {
        std::string base = match[1];
        int index = std::stoi(match[2]);
        return {base, index};
    }
    
    return {selector, -1};
}

// ScriptProcessor 实现
std::shared_ptr<CHTLContext> ScriptProcessor::getContext() const {
    return manager.getContext();
}

std::shared_ptr<ScriptBlock> ScriptProcessor::processScriptBlock(const std::string& content,
                                                                const std::string& scope) {
    auto block = std::make_shared<ScriptBlock>(ScriptType::JAVASCRIPT, scope);
    
    // 获取JS上下文
    auto jsContext = manager.getJSContext();
    if (!jsContext) {
        return block;
    }
    
    // 进入脚本状态
    jsContext->getStateMachine().handleEvent(CHTLJSEvent::EnterScript);
    
    // 检测脚本类型
    ScriptType type = detectScriptType(content);
    block->type = type;
    
    std::string processedContent = content;
    
    // 如果是CHTL JS，处理增强功能
    if (type == ScriptType::CHTLJS) {
        // 应用CJMOD扩展（预处理）
        if (cjmodManager) {
            processedContent = cjmodManager->preprocessScript(processedContent);
        }
        
        // 处理无修饰字面量
        processedContent = processUnquotedLiterals(processedContent, jsContext);
        
        // 处理箭头语法
        if (ScriptHelper::hasArrowSyntax(processedContent)) {
            processedContent = ScriptHelper::convertArrowToDot(processedContent);
        }
        
        // 处理增强选择器
        processedContent = processEnhancedSelectors(processedContent, block->selectors);
        
        // 检测并处理特殊方法
        processedContent = detectAndProcessMethods(processedContent);
        
        // 应用CJMOD扩展（转换）
        if (cjmodManager) {
            processedContent = cjmodManager->transformScript(processedContent);
        }
    }
    
    // 退出脚本状态
    jsContext->getStateMachine().handleEvent(CHTLJSEvent::ExitScript);
    
    block->content = processedContent;
    block->isProcessed = true;
    
    return block;
}

std::string ScriptProcessor::processEnhancedSelectors(const std::string& script, 
                                                     std::vector<EnhancedSelector>& selectors) {
    std::string processed = script;
    EnhancedSelectorProcessor selectorProcessor(manager);
    
    // 首先转换箭头语法
    if (ScriptHelper::hasArrowSyntax(processed)) {
        processed = ScriptHelper::convertArrowToDot(processed);
    }
    
    // 正则表达式匹配增强选择器 {{...}}
    std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
    std::smatch match;
    
    std::string::const_iterator searchStart(processed.cbegin());
    std::stringstream result;
    size_t lastPos = 0;
    
    while (std::regex_search(searchStart, processed.cend(), match, selectorRegex)) {
        // 添加匹配前的内容
        size_t matchPos = std::distance(processed.cbegin(), match[0].first);
        result << processed.substr(lastPos, matchPos - lastPos);
        
        // 解析选择器
        std::string selectorStr = match[1];
        EnhancedSelector selector = selectorProcessor.parseSelector(selectorStr);
        selectors.push_back(selector);
        
        // 生成JavaScript代码
        std::string jsCode = selectorProcessor.toJavaScript(selector, "");
        
        // 检查是否有方法调用
        size_t nextPos = matchPos + match[0].length();
        if (nextPos < processed.length() && processed[nextPos] == '.') {
            // 检查是否是listen或delegate方法
            std::regex methodRegex(R"(\.(\w+)\s*\()");
            std::smatch methodMatch;
            std::string methodStr = processed.substr(nextPos);
            
            if (std::regex_search(methodStr, methodMatch, methodRegex)) {
                std::string methodName = methodMatch[1];
                
                if (methodName == "listen") {
                    // 提取listen的配置
                    std::regex configRegex(R"(\((\{[^}]+\})\))");
                    std::smatch configMatch;
                    if (std::regex_search(methodStr, configMatch, configRegex)) {
                        std::string config = configMatch[1];
                        jsCode = CHTLJSExtensions::EnhancedMethodProcessor::processListen(jsCode, config);
                        
                        // 跳过整个方法调用
                        lastPos = nextPos + configMatch.position() + configMatch[0].length();
                        searchStart = processed.cbegin() + lastPos;
                        result << jsCode;
                        continue;
                    }
                } else if (methodName == "delegate") {
                    // 提取delegate的配置
                    std::regex configRegex(R"(\((\{[\s\S]+?\})\))");
                    std::smatch configMatch;
                    if (std::regex_search(methodStr, configMatch, configRegex)) {
                        std::string config = configMatch[1];
                        jsCode = CHTLJSExtensions::EnhancedMethodProcessor::processDelegate(jsCode, config);
                        
                        // 跳过整个方法调用
                        lastPos = nextPos + configMatch.position() + configMatch[0].length();
                        searchStart = processed.cbegin() + lastPos;
                        result << jsCode;
                        continue;
                    }
                }
            }
        }
        
        result << jsCode;
        
        // 更新位置
        lastPos = matchPos + match[0].length();
        searchStart = match.suffix().first;
    }
    
    // 处理animate函数
    std::regex animateRegex(R"(animate\s*\((\{[\s\S]+?\})\))");
    std::string remaining = processed.substr(lastPos);
    std::smatch animateMatch;
    
    if (std::regex_search(remaining, animateMatch, animateRegex)) {
        result << remaining.substr(0, animateMatch.position());
        std::string animConfig = animateMatch[1];
        result << CHTLJSExtensions::AnimationProcessor::processAnimate(animConfig);
        result << remaining.substr(animateMatch.position() + animateMatch[0].length());
    } else {
        // 添加剩余内容
        result << remaining;
    }
    
    return result.str();
}

ScriptType ScriptProcessor::detectScriptType(const std::string& content) {
    // 如果包含增强选择器，则是CHTL JS
    if (ScriptHelper::hasEnhancedSelector(content)) {
        return ScriptType::CHTLJS;
    }
    
    // 如果包含->语法，则是CHTL JS
    if (ScriptHelper::hasArrowSyntax(content)) {
        return ScriptType::CHTLJS;
    }
    
    // 如果包含listen/delegate/animate，则是CHTL JS
    std::regex chtlMethods(R"(\b(listen|delegate|animate)\s*\()");
    if (std::regex_search(content, chtlMethods)) {
        return ScriptType::CHTLJS;
    }
    
    // 检查CJMOD注册的语法模式
    for (const auto& [pattern, transformer] : syntaxTransformers) {
        std::regex patternRegex(pattern);
        if (std::regex_search(content, patternRegex)) {
            return ScriptType::CHTLJS;
        }
    }
    
    // 默认为普通JavaScript
    return ScriptType::JAVASCRIPT;
}

std::string ScriptProcessor::applyCJMODExtensions(const std::string& script) {
    std::string result = script;
    
    // 应用注册的语法转换器
    for (const auto& [pattern, transformer] : syntaxTransformers) {
        std::regex patternRegex(pattern);
        std::smatch match;
        std::string::const_iterator searchStart(result.cbegin());
        std::stringstream transformed;
        size_t lastPos = 0;
        
        while (std::regex_search(searchStart, result.cend(), match, patternRegex)) {
            size_t matchPos = std::distance(result.cbegin(), match[0].first);
            transformed << result.substr(lastPos, matchPos - lastPos);
            
            // 应用转换器
            std::string matchedText = match[0];
            transformed << transformer(matchedText);
            
            lastPos = matchPos + match[0].length();
            searchStart = match.suffix().first;
        }
        
        transformed << result.substr(lastPos);
        result = transformed.str();
    }
    
    // 处理自定义函数调用
    std::regex funcRegex(R"(\b(\w+)\s*\(([^)]*)\))");
    std::smatch funcMatch;
    std::string::const_iterator searchStart(result.cbegin());
    std::stringstream processed;
    size_t lastPos = 0;
    
    while (std::regex_search(searchStart, result.cend(), funcMatch, funcRegex)) {
        std::string funcName = funcMatch[1];
        
        // 检查是否是自定义函数
        if (customFunctions.find(funcName) != customFunctions.end()) {
            size_t matchPos = std::distance(result.cbegin(), funcMatch[0].first);
            processed << result.substr(lastPos, matchPos - lastPos);
            
            // 解析参数
            std::string argsStr = funcMatch[2];
            std::vector<std::string> args;
            
            // 简单的参数分割（需要更复杂的解析来处理嵌套）
            std::stringstream argStream(argsStr);
            std::string arg;
            while (std::getline(argStream, arg, ',')) {
                // 去除空格
                arg.erase(0, arg.find_first_not_of(" \t"));
                arg.erase(arg.find_last_not_of(" \t") + 1);
                args.push_back(arg);
            }
            
            // 调用自定义函数
            std::string replacement = customFunctions[funcName](args);
            processed << replacement;
            
            lastPos = matchPos + funcMatch[0].length();
        }
        
        searchStart = funcMatch.suffix().first;
    }
    
    if (lastPos < result.length()) {
        processed << result.substr(lastPos);
    }
    
    return processed.str();
}

void ScriptProcessor::registerFunction(const std::string& name, 
                                     std::function<std::string(const std::vector<std::string>&)> func) {
    customFunctions[name] = func;
}

void ScriptProcessor::registerTransformer(const std::string& pattern,
                                        std::function<std::string(const std::string&)> transformer) {
    syntaxTransformers.push_back({pattern, transformer});
}

// CHTLJSTransformer 实现
std::string CHTLJSTransformer::transform(const std::string& chtljs) {
    std::string transformed = chtljs;
    
    // 转换增强选择器
    std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
    transformed = std::regex_replace(transformed, selectorRegex, 
        [this](const std::smatch& match) {
            return transformSelector(match[1]);
        });
    
    // TODO: 转换其他CHTL JS特性
    
    return transformed;
}

std::string CHTLJSTransformer::transformSelector(const std::string& selectorExpr) {
    EnhancedSelectorProcessor processor(scriptManager);
    EnhancedSelector selector = processor.parseSelector(selectorExpr);
    
    std::string scopeId = scriptManager.getScopeId(currentScope);
    return processor.toJavaScript(selector, scopeId);
}

std::string CHTLJSTransformer::generateQueryCode(const EnhancedSelector& selector) {
    std::stringstream js;
    
    switch (selector.type) {
        case SelectorType::TAG:
            js << "document.getElementsByTagName('" << selector.primaryTarget << "')";
            break;
        case SelectorType::CLASS:
            js << "document.getElementsByClassName('" << selector.primaryTarget << "')";
            break;
        case SelectorType::ID:
            js << "document.getElementById('" << selector.primaryTarget << "')";
            break;
        default:
            js << "document.querySelector('" << selector.selector << "')";
    }
    
    if (selector.hasIndex) {
        js << "[" << selector.index << "]";
    }
    
    return js.str();
}

// ScriptIsolator 实现
std::string ScriptIsolator::wrapInIsolation(const std::string& script, const std::string& scopeId) {
    std::stringstream wrapped;
    wrapped << "(function() {\n";
    wrapped << "  'use strict';\n";
    wrapped << "  const __currentScope = '" << scopeId << "';\n";
    wrapped << script << "\n";
    wrapped << "})();\n";
    return wrapped.str();
}

std::string ScriptIsolator::wrapAsModule(const std::string& script, const std::string& moduleName) {
    std::stringstream wrapped;
    wrapped << "const " << moduleName << " = (function() {\n";
    wrapped << "  'use strict';\n";
    wrapped << script << "\n";
    wrapped << "  return { /* exported values */ };\n";
    wrapped << "})();\n";
    return wrapped.str();
}

std::string ScriptIsolator::wrapInIIFE(const std::string& script) {
    return "(function() {\n" + script + "\n})();\n";
}

std::string ScriptIsolator::generateScopeBinding(const std::string& scopeId) {
    std::stringstream binding;
    binding << "const __scope = document.querySelector('[data-chtl-scope=\"" << scopeId << "\"]');\n";
    binding << "if (!__scope) {\n";
    binding << "  console.warn('CHTL: Scope element not found for " << scopeId << "');\n";
    binding << "}\n";
    return binding.str();
}

// ScriptHelper 实现
namespace ScriptHelper {

bool hasEnhancedSelector(const std::string& script) {
    std::regex selectorRegex(R"(\{\{[^}]+\}\})");
    return std::regex_search(script, selectorRegex);
}

std::vector<std::string> extractEnhancedSelectors(const std::string& script) {
    std::vector<std::string> selectors;
    std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
    std::smatch match;
    
    std::string::const_iterator searchStart(script.cbegin());
    while (std::regex_search(searchStart, script.cend(), match, selectorRegex)) {
        selectors.push_back(match[1]);
        searchStart = match.suffix().first;
    }
    
    return selectors;
}

bool isValidSelector(const std::string& selector) {
    // 基本验证
    if (selector.empty()) {
        return false;
    }
    
    // 检查是否包含非法字符
    std::regex invalidChars(R"([<>\"'])");
    if (std::regex_search(selector, invalidChars)) {
        return false;
    }
    
    return true;
}

std::string escapeJavaScript(const std::string& str) {
    std::string escaped;
    for (char c : str) {
        switch (c) {
            case '\'': escaped += "\\'"; break;
            case '"': escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default: escaped += c;
        }
    }
    return escaped;
}

std::string generateUniqueFunctionName(const std::string& base) {
    static int counter = 0;
    return base + "_" + std::to_string(++counter);
}

bool isValidCSSSelector(const std::string& selector) {
    // 简单的CSS选择器验证
    std::regex validSelector(R"(^[#.\w\s\[\]:,-]+$)");
    return std::regex_match(selector, validSelector);
}

std::vector<std::string> decomposeSelector(const std::string& selector) {
    std::vector<std::string> parts;
    std::stringstream ss(selector);
    std::string part;
    
    while (ss >> part) {
        parts.push_back(part);
    }
    
    return parts;
}

bool hasArrowSyntax(const std::string& script) {
    // 检查是否包含->语法
    std::regex arrowRegex(R"(\}\}\s*->)");
    return std::regex_search(script, arrowRegex);
}

std::string convertArrowToDot(const std::string& script) {
    // 将->替换为.
    std::regex arrowRegex(R"(->)");
    return std::regex_replace(script, arrowRegex, ".");
}

} // namespace ScriptHelper

// CHTLJSExtensions 实现
namespace CHTLJSExtensions {

// EventDelegationManager 静态成员初始化
std::map<std::string, std::vector<EventDelegationConfig>> EventDelegationManager::delegationRegistry;
int EventDelegationManager::delegationIdCounter = 0;

// EnhancedMethodProcessor 实现
std::string EnhancedMethodProcessor::processListen(const std::string& selector, const std::string& config) {
    std::stringstream js;
    auto events = parseEventConfig(config);
    
    js << "(" << selector << ").forEach(function(el) {\n";
    for (const auto& event : events) {
        js << "  " << generateEventListenerCode("el", event) << "\n";
    }
    js << "});\n";
    
    return js.str();
}

std::string EnhancedMethodProcessor::processDelegate(const std::string& selector, const std::string& config) {
    auto delegateConfig = parseDelegateConfig(config);
    delegateConfig.parentSelector = selector;
    
    return EventDelegationManager::registerDelegation(delegateConfig);
}

std::vector<EventListenerConfig> EnhancedMethodProcessor::parseEventConfig(const std::string& config) {
    std::vector<EventListenerConfig> events;
    
    // 简化的解析逻辑 - 实际应该使用更复杂的解析器
    std::regex eventRegex(R"((\w+)\s*:\s*([^,]+)(?:,|})");
    std::smatch match;
    std::string::const_iterator searchStart(config.cbegin());
    
    while (std::regex_search(searchStart, config.cend(), match, eventRegex)) {
        EventListenerConfig event;
        event.eventType = match[1];
        event.callback = match[2];
        event.isInline = event.callback.find("function") != std::string::npos ||
                        event.callback.find("=>") != std::string::npos;
        events.push_back(event);
        searchStart = match.suffix().first;
    }
    
    return events;
}

EventDelegationConfig EnhancedMethodProcessor::parseDelegateConfig(const std::string& config) {
    EventDelegationConfig delegateConfig;
    
    // 解析target
    std::regex targetRegex(R"(target\s*:\s*(\{[^}]+\}|\[[^\]]+\]))");
    std::smatch targetMatch;
    if (std::regex_search(config, targetMatch, targetRegex)) {
        std::string targetStr = targetMatch[1];
        
        // 判断是单个还是数组
        if (targetStr[0] == '[') {
            // 数组形式
            std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
            std::smatch selectorMatch;
            std::string::const_iterator searchStart(targetStr.cbegin());
            
            while (std::regex_search(searchStart, targetStr.cend(), selectorMatch, selectorRegex)) {
                delegateConfig.targets.push_back(selectorMatch[1]);
                searchStart = selectorMatch.suffix().first;
            }
        } else {
            // 单个选择器
            std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
            std::smatch selectorMatch;
            if (std::regex_search(targetStr, selectorMatch, selectorRegex)) {
                delegateConfig.targets.push_back(selectorMatch[1]);
            }
        }
    }
    
    // 解析事件
    std::regex eventStartRegex(R"(target\s*:[^,]+,\s*(.+)\})");
    std::smatch eventStartMatch;
    if (std::regex_search(config, eventStartMatch, eventStartRegex)) {
        std::string eventsStr = eventStartMatch[1];
        delegateConfig.events = parseEventConfig("{" + eventsStr + "}");
    }
    
    return delegateConfig;
}

std::string EnhancedMethodProcessor::generateEventListenerCode(const std::string& element, 
                                                              const EventListenerConfig& event) {
    std::stringstream js;
    js << element << ".addEventListener('" << event.eventType << "', ";
    
    if (event.isInline) {
        js << event.callback;
    } else {
        js << event.callback;
    }
    
    js << ");";
    return js.str();
}

std::string EnhancedMethodProcessor::generateDelegationCode(const EventDelegationConfig& config) {
    std::stringstream js;
    std::string delegationId = EventDelegationManager::getOrCreateDelegationId(config.parentSelector);
    
    js << "// Event delegation for " << config.parentSelector << "\n";
    js << "(function() {\n";
    js << "  const parent = " << config.parentSelector << ";\n";
    js << "  if (!parent) return;\n\n";
    
    // 为每个事件类型生成处理器
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> eventMap;
    for (const auto& event : config.events) {
        for (const auto& target : config.targets) {
            eventMap[event.eventType].push_back({target, event.callback});
        }
    }
    
    for (const auto& [eventType, handlers] : eventMap) {
        js << "  parent.addEventListener('" << eventType << "', function(e) {\n";
        
        for (const auto& [target, callback] : handlers) {
            js << "    if (e.target.matches('" << target << "')) {\n";
            js << "      (" << callback << ").call(e.target, e);\n";
            js << "    }\n";
        }
        
        js << "  });\n\n";
    }
    
    js << "})();\n";
    
    return js.str();
}

// AnimationProcessor 实现
std::string AnimationProcessor::processAnimate(const std::string& config) {
    auto animConfig = parseAnimationConfig(config);
    return generateAnimationFunction(animConfig);
}

AnimationConfig AnimationProcessor::parseAnimationConfig(const std::string& config) {
    AnimationConfig animConfig;
    
    // 解析duration
    std::regex durationRegex(R"(duration\s*:\s*(\d+))");
    std::smatch durationMatch;
    if (std::regex_search(config, durationMatch, durationRegex)) {
        animConfig.duration = std::stoi(durationMatch[1]);
    }
    
    // 解析easing
    std::regex easingRegex(R"(easing\s*:\s*([^,]+))");
    std::smatch easingMatch;
    if (std::regex_search(config, easingMatch, easingRegex)) {
        animConfig.easing = easingMatch[1];
    }
    
    // 解析loop
    std::regex loopRegex(R"(loop\s*:\s*(-?\d+))");
    std::smatch loopMatch;
    if (std::regex_search(config, loopMatch, loopRegex)) {
        animConfig.loop = std::stoi(loopMatch[1]);
    }
    
    // 解析delay
    std::regex delayRegex(R"(delay\s*:\s*(\d+))");
    std::smatch delayMatch;
    if (std::regex_search(config, delayMatch, delayRegex)) {
        animConfig.delay = std::stoi(delayMatch[1]);
    }
    
    // TODO: 解析begin, end, when等复杂配置
    
    return animConfig;
}

std::string AnimationProcessor::generateAnimationFunction(const AnimationConfig& config) {
    std::stringstream js;
    
    // 返回一个函数，该函数接受元素作为参数
    js << "(function(element) {\n";
    js << "  if (!element) return;\n";
    js << "  const duration = " << config.duration << ";\n";
    js << "  const easing = " << parseEasing(config.easing) << ";\n";
    js << "  const loop = " << config.loop << ";\n";
    js << "  const delay = " << config.delay << ";\n";
    js << "  let startTime = null;\n";
    js << "  let currentLoop = 0;\n\n";
    
    js << "  function applyProperties(el, properties) {\n";
    js << "    Object.keys(properties).forEach(function(prop) {\n";
    js << "      if (prop === 'transform') {\n";
    js << "        el.style.transform = properties[prop];\n";
    js << "      } else {\n";
    js << "        el.style[prop] = properties[prop];\n";
    js << "      }\n";
    js << "    });\n";
    js << "  }\n\n";
    
    js << generateRAFLoop(config);
    
    js << "  setTimeout(function() {\n";
    js << "    requestAnimationFrame(animate);\n";
    js << "  }, delay);\n";
    js << "})";
    
    return js.str();
}

std::string AnimationProcessor::parseEasing(const std::string& easing) {
    // 将缓动函数名转换为实际的函数
    if (easing == "ease-in-out" || easing == "ease-in-out") {
        return "function(t) { return t < 0.5 ? 2*t*t : -1+(4-2*t)*t; }";
    } else if (easing == "ease-in" || easing == "ease-in") {
        return "function(t) { return t*t; }";
    } else if (easing == "ease-out" || easing == "ease-out") {
        return "function(t) { return t*(2-t); }";
    } else {
        return "function(t) { return t; }"; // linear
    }
}

std::string AnimationProcessor::generateRAFLoop(const AnimationConfig& config) {
    std::stringstream js;
    
    js << "  function animate(timestamp) {\n";
    js << "    if (!startTime) startTime = timestamp;\n";
    js << "    const elapsed = timestamp - startTime;\n";
    js << "    const progress = Math.min(elapsed / duration, 1);\n";
    js << "    const easedProgress = easing(progress);\n\n";
    
    // 应用动画属性
    if (!config.begin.empty()) {
        js << "    if (progress === 0) {\n";
        js << "      applyProperties(element, " << mapToJsObject(config.begin) << ");\n";
        js << "    }\n\n";
    }
    
    if (!config.when.empty()) {
        js << "    // 应用关键帧\n";
        for (const auto& keyframe : config.when) {
            js << "    if (easedProgress >= " << keyframe.at << ") {\n";
            js << "      applyProperties(element, " << mapToJsObject(keyframe.properties) << ");\n";
            js << "    }\n";
        }
        js << "\n";
    }
    
    if (!config.end.empty()) {
        js << "    if (progress === 1) {\n";
        js << "      applyProperties(element, " << mapToJsObject(config.end) << ");\n";
        js << "    }\n\n";
    }
    
    js << "    if (progress < 1) {\n";
    js << "      requestAnimationFrame(animate);\n";
    js << "    } else {\n";
    js << "      currentLoop++;\n";
    js << "      if (loop === -1 || currentLoop < loop) {\n";
    js << "        startTime = null;\n";
    js << "        requestAnimationFrame(animate);\n";
    js << "      }";
    
    if (!config.callback.empty()) {
        js << " else if (" << config.callback << ") {\n";
        js << "        " << config.callback << "();\n";
        js << "      }";
    }
    
    js << "\n";
    js << "    }\n";
    js << "  }\n";
    
    return js.str();
}

// 辅助函数：将map转换为JavaScript对象字符串
static std::string mapToJsObject(const std::map<std::string, std::string>& map) {
    std::stringstream js;
    js << "{";
    bool first = true;
    for (const auto& [key, value] : map) {
        if (!first) js << ", ";
        js << "'" << key << "': ";
        // 检查是否是字符串值（包含引号）
        if (value.front() == '"' || value.front() == '\'') {
            js << value;
        } else {
            js << "'" << value << "'";
        }
        first = false;
    }
    js << "}";
    return js.str();
}

// EventDelegationManager 实现
std::string EventDelegationManager::registerDelegation(const EventDelegationConfig& config) {
    std::string id = getOrCreateDelegationId(config.parentSelector);
    mergeDelegation(id, config);
    return EnhancedMethodProcessor::generateDelegationCode(config);
}

std::string EventDelegationManager::getOrCreateDelegationId(const std::string& parentSelector) {
    // 查找已存在的委托
    for (const auto& [id, configs] : delegationRegistry) {
        if (!configs.empty() && configs[0].parentSelector == parentSelector) {
            return id;
        }
    }
    
    // 创建新的委托ID
    std::string newId = "delegation_" + std::to_string(++delegationIdCounter);
    delegationRegistry[newId] = std::vector<EventDelegationConfig>();
    return newId;
}

void EventDelegationManager::mergeDelegation(const std::string& id, const EventDelegationConfig& config) {
    delegationRegistry[id].push_back(config);
}

std::string EventDelegationManager::generateDelegationInit() {
    std::stringstream js;
    
    js << "// Event delegation initialization\n";
    js << "const CHTL_DELEGATIONS = {};\n\n";
    
    for (const auto& [id, configs] : delegationRegistry) {
        if (!configs.empty()) {
            js << "CHTL_DELEGATIONS['" << id << "'] = {\n";
            js << "  parent: '" << configs[0].parentSelector << "',\n";
            js << "  handlers: []\n";
            js << "};\n";
        }
    }
    
    return js.str();
}

void EventDelegationManager::clear() {
    delegationRegistry.clear();
    delegationIdCounter = 0;
}

// RuntimeCodeGenerator 实现
std::string RuntimeCodeGenerator::generateListenRuntime() {
    return R"(
// CHTL listen runtime support
function chtl_listen(element, config) {
    if (!element) return;
    
    const elements = Array.isArray(element) ? element : [element];
    
    elements.forEach(function(el) {
        Object.keys(config).forEach(function(eventType) {
            el.addEventListener(eventType, config[eventType]);
        });
    });
}
)";
}

std::string RuntimeCodeGenerator::generateDelegateRuntime() {
    return R"(
// CHTL delegate runtime support
function chtl_delegate(parent, config) {
    if (!parent) return;
    
    const targets = Array.isArray(config.target) ? config.target : [config.target];
    
    Object.keys(config).forEach(function(key) {
        if (key === 'target') return;
        
        parent.addEventListener(key, function(e) {
            targets.forEach(function(selector) {
                if (e.target.matches(selector)) {
                    config[key].call(e.target, e);
                }
            });
        });
    });
}
)";
}

std::string RuntimeCodeGenerator::generateAnimateRuntime() {
    return R"(
// CHTL animate runtime support
function chtl_animate(config) {
    // 返回一个接受元素的函数
    return function(element) {
        if (!element) {
            console.error('CHTL animate: element is required');
            return;
        }
        
        const duration = config.duration || 1000;
        const easing = config.easing || function(t) { return t; };
        const loop = config.loop || 1;
        const delay = config.delay || 0;
        
        let startTime = null;
        let currentLoop = 0;
        
        function interpolate(start, end, progress) {
            if (typeof start === 'number' && typeof end === 'number') {
                return start + (end - start) * progress;
            }
            return progress < 0.5 ? start : end;
        }
        
        function applyProperties(el, properties) {
            Object.keys(properties).forEach(function(prop) {
                if (prop === 'transform') {
                    el.style.transform = properties[prop];
                } else {
                    el.style[prop] = properties[prop];
                }
            });
        }
        
        function animate(timestamp) {
            if (!startTime) startTime = timestamp;
            const elapsed = timestamp - startTime;
            const progress = Math.min(elapsed / duration, 1);
            const easedProgress = easing(progress);
            
            // Apply animation
            if (config.begin && progress === 0) {
                applyProperties(element, config.begin);
            }
            
            if (config.when) {
                // Apply keyframes
                for (let i = 0; i < config.when.length; i++) {
                    const keyframe = config.when[i];
                    if (easedProgress >= keyframe.at) {
                        applyProperties(element, keyframe);
                    }
                }
            }
            
            if (config.end && progress === 1) {
                applyProperties(element, config.end);
            }
            
            if (progress < 1) {
                requestAnimationFrame(animate);
            } else {
                currentLoop++;
                if (loop === -1 || currentLoop < loop) {
                    startTime = null;
                    requestAnimationFrame(animate);
                } else if (config.callback) {
                    config.callback();
                }
            }
        }
        
        setTimeout(function() {
            requestAnimationFrame(animate);
        }, delay);
    };
}
)";
}

std::string RuntimeCodeGenerator::generateFullRuntime() {
    std::stringstream runtime;
    
    runtime << "// CHTL JS Runtime Support\n";
    runtime << "(function(window) {\n";
    runtime << "  'use strict';\n\n";
    
    runtime << generateListenRuntime() << "\n";
    runtime << generateDelegateRuntime() << "\n";
    runtime << generateAnimateRuntime() << "\n";
    
    runtime << "  // Export to global scope\n";
    runtime << "  window.chtl_listen = chtl_listen;\n";
    runtime << "  window.chtl_delegate = chtl_delegate;\n";
    runtime << "  window.chtl_animate = chtl_animate;\n";
    
    runtime << "})(window);\n";
    
    return runtime.str();
}

} // namespace CHTLJSExtensions

} // namespace chtl