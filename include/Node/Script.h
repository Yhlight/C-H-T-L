#ifndef CHTL_SCRIPT_H
#define CHTL_SCRIPT_H

#include "Node/Node.h"
#include <string>
#include <unordered_map>

namespace chtl {

// Script节点 - 表示局部JavaScript代码块
class Script : public Node {
public:
    // Script类型
    enum class ScriptType {
        INLINE,         // 内联脚本
        MODULE,         // 模块脚本
        SCOPED,         // 作用域脚本（默认）
        GLOBAL          // 全局脚本
    };
    
    // 执行时机
    enum class ExecutionTiming {
        IMMEDIATE,      // 立即执行
        DEFERRED,       // 延迟执行
        ON_LOAD,        // 加载时执行
        ON_MOUNT,       // 挂载时执行
        ON_DEMAND       // 按需执行
    };
    
private:
    std::string content_;           // JavaScript代码内容
    std::string name_;              // 脚本名称（可选）
    ScriptType scriptType_;         // 脚本类型
    ExecutionTiming timing_;        // 执行时机
    bool isAsync_;                  // 是否异步执行
    std::string scope_;             // 作用域标识
    std::vector<std::string> dependencies_;  // 依赖的其他脚本
    std::unordered_map<std::string, std::string> exports_;  // 导出的变量/函数
    
public:
    Script() : Node(NodeType::SCRIPT, "[Script]"), 
               scriptType_(ScriptType::SCOPED),
               timing_(ExecutionTiming::IMMEDIATE),
               isAsync_(false) {}
    
    // 内容管理
    const std::string& getContent() const { return content_; }
    void setContent(const std::string& content) { content_ = content; }
    void appendContent(const std::string& content) { content_ += content; }
    
    // 名称管理
    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }
    bool hasName() const { return !name_.empty(); }
    
    // 类型管理
    ScriptType getScriptType() const { return scriptType_; }
    void setScriptType(ScriptType type) { scriptType_ = type; }
    
    // 执行时机管理
    ExecutionTiming getTiming() const { return timing_; }
    void setTiming(ExecutionTiming timing) { timing_ = timing; }
    
    // 异步管理
    bool isAsync() const { return isAsync_; }
    void setAsync(bool async) { isAsync_ = async; }
    
    // 作用域管理
    const std::string& getScope() const { return scope_; }
    void setScope(const std::string& scope) { scope_ = scope; }
    bool isScoped() const { return !scope_.empty() || scriptType_ == ScriptType::SCOPED; }
    
    // 依赖管理
    void addDependency(const std::string& dep) { dependencies_.push_back(dep); }
    const std::vector<std::string>& getDependencies() const { return dependencies_; }
    bool hasDependencies() const { return !dependencies_.empty(); }
    
    // 导出管理
    void addExport(const std::string& name, const std::string& value = "") {
        exports_[name] = value;
    }
    const std::unordered_map<std::string, std::string>& getExports() const { 
        return exports_; 
    }
    bool hasExports() const { return !exports_.empty(); }
    
    // 生成包装后的JavaScript代码
    std::string generateWrappedCode() const;
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_SCRIPT_H