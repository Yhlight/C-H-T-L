#include "CHTLScript.h"
#include "CHTLGenerator.h"
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
void ScriptProcessor::processScriptBlock(const std::string& content, const std::string& currentScope) {
    // 检测脚本类型
    ScriptType type = detectScriptType(content);
    
    // 创建脚本块
    auto scriptBlock = std::make_shared<ScriptBlock>(content, type);
    scriptBlock->setScope(currentScope);
    
    // 如果包含增强选择器，进行处理
    if (ScriptHelper::hasEnhancedSelector(content)) {
        std::vector<EnhancedSelector> selectors;
        std::string processedContent = processEnhancedSelectors(content, selectors);
        scriptBlock->setContent(processedContent);
        
        for (const auto& sel : selectors) {
            scriptBlock->addSelector(sel);
        }
    }
    
    // 添加到管理器
    if (currentScope.empty()) {
        manager.addGlobalScript(scriptBlock);
    } else {
        manager.addLocalScript(currentScope, scriptBlock);
    }
}

std::string ScriptProcessor::processEnhancedSelectors(const std::string& script, 
                                                     std::vector<EnhancedSelector>& selectors) {
    std::string processed = script;
    EnhancedSelectorProcessor selectorProcessor(manager);
    
    // 正则表达式匹配增强选择器 {{...}}
    std::regex selectorRegex(R"(\{\{([^}]+)\}\})");
    std::smatch match;
    
    std::string::const_iterator searchStart(script.cbegin());
    std::stringstream result;
    size_t lastPos = 0;
    
    while (std::regex_search(searchStart, script.cend(), match, selectorRegex)) {
        // 添加匹配前的内容
        size_t matchPos = std::distance(script.cbegin(), match[0].first);
        result << script.substr(lastPos, matchPos - lastPos);
        
        // 解析选择器
        std::string selectorStr = match[1];
        EnhancedSelector selector = selectorProcessor.parseSelector(selectorStr);
        selectors.push_back(selector);
        
        // 生成JavaScript代码
        std::string jsCode = selectorProcessor.toJavaScript(selector, "");
        result << jsCode;
        
        // 更新位置
        lastPos = matchPos + match[0].length();
        searchStart = match.suffix().first;
    }
    
    // 添加剩余内容
    result << script.substr(lastPos);
    
    return result.str();
}

ScriptType ScriptProcessor::detectScriptType(const std::string& content) {
    // 如果包含增强选择器，则是CHTL JS
    if (ScriptHelper::hasEnhancedSelector(content)) {
        return ScriptType::CHTL_JS;
    }
    
    // TODO: 添加更多CHTL JS特性检测
    
    return ScriptType::JAVASCRIPT;
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

} // namespace ScriptHelper

} // namespace chtl