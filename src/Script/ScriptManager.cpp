#include "Script/ScriptManager.h"
#include "Node/Script.h"
#include "Node/Node.h"
#include <sstream>
#include <algorithm>

namespace chtl {

ScriptManager::ScriptManager() {
    globalContext_ = std::make_shared<ScriptContext>();
}

ScriptManager::~ScriptManager() = default;

void ScriptManager::registerScript(std::shared_ptr<Script> script) {
    if (script->hasName()) {
        namedScripts_[script->getName()] = script;
    } else {
        anonymousScripts_.push_back(script);
    }
}

ScriptManager::ExecutionResult ScriptManager::executeScript(
    std::shared_ptr<Script> script, 
    std::shared_ptr<ScriptContext> context) {
    
    ExecutionResult result;
    result.success = true;
    
    if (!context) {
        context = globalContext_;
    }
    
    try {
        // 生成包装后的代码
        std::string wrappedCode = wrapScriptCode(script, context);
        
        // TODO: 实际的JavaScript执行需要集成JavaScript引擎
        // 这里只是生成代码，实际执行需要V8或其他JS引擎
        result.output = wrappedCode;
        
        // 处理导出
        if (script->hasExports()) {
            result.exports = script->getExports();
        }
        
    } catch (const std::exception& e) {
        result.success = false;
        result.error = e.what();
    }
    
    return result;
}

void ScriptManager::executeScriptAsync(
    std::shared_ptr<Script> script,
    ExecutionCallback callback,
    std::shared_ptr<ScriptContext> context) {
    
    // 简化实现：同步执行后调用回调
    // 实际实现应该使用异步执行机制
    ExecutionResult result = executeScript(script, context);
    if (callback) {
        callback(result);
    }
}

ScriptManager::ExecutionResult ScriptManager::executeNamedScript(
    const std::string& name,
    std::shared_ptr<ScriptContext> context) {
    
    auto it = namedScripts_.find(name);
    if (it != namedScripts_.end()) {
        return executeScript(it->second, context);
    }
    
    ExecutionResult result;
    result.success = false;
    result.error = "Script not found: " + name;
    return result;
}

std::vector<ScriptManager::ExecutionResult> ScriptManager::executeAll(
    std::shared_ptr<Node> ast) {
    
    std::vector<ExecutionResult> results;
    
    // 收集所有Script节点
    std::vector<std::shared_ptr<Script>> scripts;
    collectScripts(ast, scripts);
    
    // 解析依赖关系并排序
    scripts = resolveDependencies(scripts);
    
    // 执行每个Script
    for (const auto& script : scripts) {
        results.push_back(executeScript(script));
    }
    
    return results;
}

std::string ScriptManager::generateJavaScript(std::shared_ptr<Node> ast) {
    std::stringstream output;
    
    // 创建执行环境
    output << createExecutionEnvironment() << "\n\n";
    
    // 收集所有Script节点
    std::vector<std::shared_ptr<Script>> scripts;
    collectScripts(ast, scripts);
    
    // 解析依赖关系并排序
    scripts = resolveDependencies(scripts);
    
    // 生成每个Script的代码
    for (const auto& script : scripts) {
        output << "// Script";
        if (script->hasName()) {
            output << " @" << script->getName();
        }
        output << "\n";
        
        // 添加执行时机注释
        switch (script->getTiming()) {
            case Script::ExecutionTiming::DEFERRED:
                output << "// Execution: deferred\n";
                break;
            case Script::ExecutionTiming::ON_LOAD:
                output << "// Execution: onload\n";
                break;
            case Script::ExecutionTiming::ON_MOUNT:
                output << "// Execution: onmount\n";
                break;
            case Script::ExecutionTiming::ON_DEMAND:
                output << "// Execution: ondemand\n";
                break;
            default:
                break;
        }
        
        output << script->generateWrappedCode() << ";\n\n";
    }
    
    return output.str();
}

void ScriptManager::collectScripts(std::shared_ptr<Node> node, 
                                  std::vector<std::shared_ptr<Script>>& scripts) {
    if (!node) return;
    
    // 检查是否是Script节点
    if (node->getType() == NodeType::SCRIPT) {
        auto scriptNode = std::dynamic_pointer_cast<Script>(node);
        if (scriptNode) {
            scripts.push_back(scriptNode);
            registerScript(scriptNode);
        }
    }
    
    // 递归遍历子节点
    for (const auto& child : node->getChildren()) {
        collectScripts(child, scripts);
    }
}

std::vector<std::shared_ptr<Script>> ScriptManager::resolveDependencies(
    const std::vector<std::shared_ptr<Script>>& scripts) {
    
    // 简化实现：按照声明顺序执行
    // TODO: 实现真正的依赖解析算法
    std::vector<std::shared_ptr<Script>> sorted = scripts;
    
    // 将有依赖的脚本放在后面
    std::stable_sort(sorted.begin(), sorted.end(), 
        [](const auto& a, const auto& b) {
            return !a->hasDependencies() && b->hasDependencies();
        });
    
    return sorted;
}

std::string ScriptManager::createExecutionEnvironment() {
    std::stringstream env;
    
    env << "// CHTL Script Execution Environment\n";
    env << "(function(window) {\n";
    env << "  'use strict';\n";
    env << "  \n";
    env << "  // Initialize CHTL namespace\n";
    env << "  window.CHTL = window.CHTL || {};\n";
    env << "  window.CHTL.modules = window.CHTL.modules || {};\n";
    env << "  window.CHTL.scripts = window.CHTL.scripts || {};\n";
    env << "  \n";
    env << "  // Script registry\n";
    env << "  const scriptRegistry = new Map();\n";
    env << "  \n";
    env << "  // Module loader\n";
    env << "  window.CHTL.loadModule = function(name) {\n";
    env << "    return window.CHTL.modules[name] || null;\n";
    env << "  };\n";
    env << "  \n";
    env << "  // Script executor\n";
    env << "  window.CHTL.executeScript = function(name) {\n";
    env << "    const script = scriptRegistry.get(name);\n";
    env << "    if (script && typeof script === 'function') {\n";
    env << "      return script();\n";
    env << "    }\n";
    env << "    return null;\n";
    env << "  };\n";
    env << "  \n";
    env << "})(window);\n";
    
    return env.str();
}

std::string ScriptManager::wrapScriptCode(std::shared_ptr<Script> script,
                                         std::shared_ptr<ScriptContext> context) {
    (void)context; // Suppress unused parameter warning
    std::stringstream wrapped;
    
    // 根据执行时机包装代码
    switch (script->getTiming()) {
        case Script::ExecutionTiming::ON_LOAD:
            wrapped << "window.addEventListener('load', function() {\n";
            wrapped << script->generateWrappedCode();
            wrapped << "\n})";
            break;
            
        case Script::ExecutionTiming::ON_MOUNT:
            wrapped << "document.addEventListener('DOMContentLoaded', function() {\n";
            wrapped << script->generateWrappedCode();
            wrapped << "\n})";
            break;
            
        case Script::ExecutionTiming::DEFERRED:
            wrapped << "setTimeout(function() {\n";
            wrapped << script->generateWrappedCode();
            wrapped << "\n}, 0)";
            break;
            
        case Script::ExecutionTiming::ON_DEMAND:
            if (script->hasName()) {
                wrapped << "window.CHTL.scripts['" << script->getName() << "'] = function() {\n";
                wrapped << script->generateWrappedCode();
                wrapped << "\n}";
            } else {
                wrapped << script->generateWrappedCode();
            }
            break;
            
        default:
            wrapped << script->generateWrappedCode();
            break;
    }
    
    return wrapped.str();
}

} // namespace chtl