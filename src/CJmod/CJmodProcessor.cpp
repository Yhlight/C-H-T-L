#include "CJmod/CJmodProcessor.h"
#include <algorithm>
#include <sstream>

namespace chtl {
namespace cjmod {

// CJmodProcessor 实现
CJmodProcessor& CJmodProcessor::getInstance() {
    static CJmodProcessor instance;
    return instance;
}

void CJmodProcessor::registerModule(std::unique_ptr<ICJmod> module) {
    if (!module) return;
    
    std::string name = module->getName();
    module->initialize();
    modules_[name] = std::move(module);
    enabledModules_.insert(name);
}

void CJmodProcessor::registerFactory(std::unique_ptr<ICJmodFactory> factory) {
    if (!factory) return;
    factories_[factory->getModuleName()] = std::move(factory);
}

std::string CJmodProcessor::processJavaScript(const std::string& code, 
                                             const std::set<std::string>& activeModules) {
    std::string result = code;
    
    // 确定要使用的模块
    std::set<std::string> modulesToUse = activeModules.empty() ? enabledModules_ : activeModules;
    
    // 预处理
    for (const auto& moduleName : modulesToUse) {
        if (modules_.find(moduleName) != modules_.end()) {
            result = modules_[moduleName]->preprocess(result);
        }
    }
    
    // 应用 CHTL 基础语法
    result = applyCHTLSyntax(result);
    
    // 应用模块转换
    for (const auto& moduleName : modulesToUse) {
        if (modules_.find(moduleName) != modules_.end()) {
            result = applyModuleTransforms(result, modules_[moduleName].get());
        }
    }
    
    // 后处理
    for (const auto& moduleName : modulesToUse) {
        if (modules_.find(moduleName) != modules_.end()) {
            result = modules_[moduleName]->postprocess(result);
        }
    }
    
    return result;
}

std::string CJmodProcessor::generateRuntime(const std::set<std::string>& activeModules) {
    std::stringstream runtime;
    runtime << "// CJmod Runtime Generated Code\n";
    runtime << "(function() {\n";
    runtime << "  'use strict';\n\n";
    
    // 确定要使用的模块
    std::set<std::string> modulesToUse = activeModules.empty() ? enabledModules_ : activeModules;
    
    // 收集所有运行时代码
    for (const auto& moduleName : modulesToUse) {
        if (modules_.find(moduleName) != modules_.end()) {
            runtime << "  // Module: " << moduleName << "\n";
            runtime << modules_[moduleName]->getRuntimeCode() << "\n\n";
        }
    }
    
    // 方法注入
    runtime << "  // Method Injections\n";
    for (const auto& moduleName : modulesToUse) {
        if (modules_.find(moduleName) != modules_.end()) {
            auto injections = modules_[moduleName]->getMethodInjections();
            for (const auto& injection : injections) {
                runtime << "  if (typeof " << injection.target << " !== 'undefined') {\n";
                runtime << "    " << injection.target << ".prototype." 
                       << injection.methodName << " = " << injection.implementation << ";\n";
                runtime << "  }\n";
            }
        }
    }
    
    runtime << "})();\n";
    return runtime.str();
}

std::string CJmodProcessor::applyModuleTransforms(const std::string& code, ICJmod* module) {
    std::string result = code;
    auto rules = module->getTransformRules();
    
    // 按优先级排序
    std::sort(rules.begin(), rules.end(), 
              [](const TransformRule& a, const TransformRule& b) {
                  return a.priority > b.priority;
              });
    
    // 应用转换规则
    for (const auto& rule : rules) {
        std::string transformed;
        std::smatch match;
        std::string::const_iterator searchStart(result.cbegin());
        
        while (std::regex_search(searchStart, result.cend(), match, rule.pattern)) {
            // 检查验证器
            if (rule.validator && !rule.validator(match.str())) {
                searchStart = match.suffix().first;
                continue;
            }
            
            // 应用转换
            transformed += std::string(searchStart, match[0].first);
            transformed += rule.transformer(match);
            searchStart = match.suffix().first;
        }
        
        transformed += std::string(searchStart, result.cend());
        result = transformed;
    }
    
    return result;
}

std::string CJmodProcessor::applyCHTLSyntax(const std::string& code) {
    return CHTLJSSyntaxProcessor::getInstance().process(code);
}

void CJmodProcessor::overrideCHTLSyntax(const std::string& syntax, const TransformRule& rule) {
    syntaxOverrides_[syntax] = rule;
    CHTLJSSyntaxProcessor::getInstance().setSyntaxOverride(syntax, rule.transformer);
}

// CHTLJSSyntaxProcessor 实现
CHTLJSSyntaxProcessor::CHTLJSSyntaxProcessor() {
    initializeOfficialSyntax();
}

CHTLJSSyntaxProcessor& CHTLJSSyntaxProcessor::getInstance() {
    static CHTLJSSyntaxProcessor instance;
    return instance;
}

void CHTLJSSyntaxProcessor::initializeOfficialSyntax() {
    // {{&}} -> this
    registerSyntax({
        "self-reference",
        std::regex(R"(\{\{&\}\})"),
        [](const std::smatch& match) { return "this"; },
        true  // 可以被覆写
    });
    
    // {{#id}} -> document.getElementById('id')
    registerSyntax({
        "id-selector",
        std::regex(R"(\{\{#([\w-]+)\}\})"),
        [](const std::smatch& match) {
            return "document.getElementById('" + match[1].str() + "')";
        },
        true
    });
    
    // {{.class}} -> document.getElementsByClassName('class')
    registerSyntax({
        "class-selector",
        std::regex(R"(\{\{\.(\w+)\}\})"),
        [](const std::smatch& match) {
            return "document.getElementsByClassName('" + match[1].str() + "')";
        },
        true
    });
    
    // obj->method() -> obj.method()
    registerSyntax({
        "method-call",
        std::regex(R"((\w+|this)->(\w+)\()"),
        [](const std::smatch& match) {
            return match[1].str() + "." + match[2].str() + "(";
        },
        false  // 核心语法，不允许覆写
    });
    
    // obj->listen("event", handler) -> obj.addEventListener("event", handler)
    registerSyntax({
        "listen-method",
        std::regex(R"((\w+|this)->listen\s*\(\s*["'](\w+)["'])"),
        [](const std::smatch& match) {
            return match[1].str() + ".addEventListener('" + match[2].str() + "'";
        },
        true
    });
}

void CHTLJSSyntaxProcessor::registerSyntax(const SyntaxRule& rule) {
    syntaxRules_.push_back(rule);
}

std::string CHTLJSSyntaxProcessor::process(const std::string& code) {
    std::string result = code;
    
    for (const auto& rule : syntaxRules_) {
        // 检查是否有覆写
        auto overrideIt = overrides_.find(rule.name);
        auto transformer = (overrideIt != overrides_.end()) 
                          ? overrideIt->second 
                          : rule.transformer;
        
        std::string transformed;
        std::smatch match;
        std::string::const_iterator searchStart(result.cbegin());
        
        while (std::regex_search(searchStart, result.cend(), match, rule.pattern)) {
            transformed += std::string(searchStart, match[0].first);
            transformed += transformer(match);
            searchStart = match.suffix().first;
        }
        
        transformed += std::string(searchStart, result.cend());
        result = transformed;
    }
    
    return result;
}

std::vector<std::string> CHTLJSSyntaxProcessor::getOverridableSyntax() const {
    std::vector<std::string> overridable;
    for (const auto& rule : syntaxRules_) {
        if (rule.canBeOverridden) {
            overridable.push_back(rule.name);
        }
    }
    return overridable;
}

void CHTLJSSyntaxProcessor::setSyntaxOverride(const std::string& syntaxName,
                                             const std::function<std::string(const std::smatch&)>& override) {
    overrides_[syntaxName] = override;
}

} // namespace cjmod
} // namespace chtl