#ifndef CHTL_SCRIPT_MANAGER_H
#define CHTL_SCRIPT_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>

namespace chtl {

// 前向声明
class Script;
class Node;

// Script执行上下文
class ScriptContext {
private:
    std::unordered_map<std::string, std::string> variables_;
    std::unordered_map<std::string, std::string> functions_;
    std::shared_ptr<ScriptContext> parent_;
    
public:
    ScriptContext(std::shared_ptr<ScriptContext> parent = nullptr) 
        : parent_(parent) {}
    
    // 变量管理
    void setVariable(const std::string& name, const std::string& value) {
        variables_[name] = value;
    }
    
    std::string getVariable(const std::string& name) const {
        auto it = variables_.find(name);
        if (it != variables_.end()) {
            return it->second;
        }
        return parent_ ? parent_->getVariable(name) : "";
    }
    
    // 函数管理
    void setFunction(const std::string& name, const std::string& body) {
        functions_[name] = body;
    }
    
    std::string getFunction(const std::string& name) const {
        auto it = functions_.find(name);
        if (it != functions_.end()) {
            return it->second;
        }
        return parent_ ? parent_->getFunction(name) : "";
    }
    
    // 创建子上下文
    std::shared_ptr<ScriptContext> createChildContext() {
        // TODO: Implement proper context creation
        return std::make_shared<ScriptContext>();
    }
};

// Script管理器 - 负责管理和执行Script节点
class ScriptManager {
public:
    // 执行结果
    struct ExecutionResult {
        bool success;
        std::string output;
        std::string error;
        std::unordered_map<std::string, std::string> exports;
    };
    
    // 执行回调
    using ExecutionCallback = std::function<void(const ExecutionResult&)>;
    
private:
    std::unordered_map<std::string, std::shared_ptr<Script>> namedScripts_;
    std::vector<std::shared_ptr<Script>> anonymousScripts_;
    std::shared_ptr<ScriptContext> globalContext_;
    
    // 执行选项
    bool enableAsync_ = true;
    bool enableModules_ = true;
    bool strictMode_ = true;
    
public:
    ScriptManager();
    ~ScriptManager();
    
    // 注册Script节点
    void registerScript(std::shared_ptr<Script> script);
    
    // 执行Script
    ExecutionResult executeScript(std::shared_ptr<Script> script, 
                                 std::shared_ptr<ScriptContext> context = nullptr);
    
    // 异步执行Script
    void executeScriptAsync(std::shared_ptr<Script> script,
                           ExecutionCallback callback,
                           std::shared_ptr<ScriptContext> context = nullptr);
    
    // 执行命名的Script
    ExecutionResult executeNamedScript(const std::string& name,
                                      std::shared_ptr<ScriptContext> context = nullptr);
    
    // 批量执行Scripts
    std::vector<ExecutionResult> executeAll(std::shared_ptr<Node> ast);
    
    // 生成最终的JavaScript代码
    std::string generateJavaScript(std::shared_ptr<Node> ast);
    
    // 配置选项
    void setEnableAsync(bool enable) { enableAsync_ = enable; }
    void setEnableModules(bool enable) { enableModules_ = enable; }
    void setStrictMode(bool enable) { strictMode_ = enable; }
    
    // 获取全局上下文
    std::shared_ptr<ScriptContext> getGlobalContext() { return globalContext_; }
    
private:
    // 收集AST中的所有Script节点
    void collectScripts(std::shared_ptr<Node> node, 
                       std::vector<std::shared_ptr<Script>>& scripts);
    
    // 解析依赖关系
    std::vector<std::shared_ptr<Script>> resolveDependencies(
        const std::vector<std::shared_ptr<Script>>& scripts);
    
    // 创建执行环境代码
    std::string createExecutionEnvironment();
    
    // 包装Script代码
    std::string wrapScriptCode(std::shared_ptr<Script> script,
                              std::shared_ptr<ScriptContext> context);
};

} // namespace chtl

#endif // CHTL_SCRIPT_MANAGER_H