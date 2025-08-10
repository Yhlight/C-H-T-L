#include "Node/Script.h"
// #include "Visitor/Visitor.h" // Not implemented yet
#include "Runtime/ChtlJsRuntime.h"
#include <sstream>

namespace chtl {

std::string Script::generateWrappedCode() const {
    std::stringstream ss;
    
    // 如果是局部内联脚本，使用运行时处理
    if (scriptType_ == ScriptType::INLINE && isScoped()) {
        // 获取运行时实例
        auto& runtime = ChtlJsRuntime::getInstance();
        
        // 获取或生成元素ID
        std::string elementId = scope_.empty() ? 
            runtime.generateElementId() : scope_;
        
        // 收集局部脚本
        runtime.collectLocalScript(content_, elementId);
        
        // 返回空字符串，因为代码已被收集
        return "";
    }
    
    // 原有的包装逻辑
    switch (scriptType_) {
        case ScriptType::GLOBAL:
            // 全局脚本直接执行
            ss << content_;
            break;
            
        case ScriptType::MODULE:
            // 模块脚本使用ES6模块语法
            ss << "(function() {\n";
            ss << "  'use strict';\n";
            if (hasExports()) {
                ss << "  const exports = {};\n";
            }
            ss << content_ << "\n";
            if (hasExports()) {
                ss << "  return exports;\n";
            }
            ss << "})()";
            break;
            
        case ScriptType::SCOPED:
            // 作用域脚本使用IIFE包装
            ss << "(function(" << (scope_.empty() ? "" : "$scope") << ") {\n";
            ss << "  'use strict';\n";
            ss << content_ << "\n";
            ss << "})(" << (scope_.empty() ? "" : "window.CHTL." + scope_) << ")";
            break;
            
        case ScriptType::INLINE:
        default:
            // 内联脚本简单包装
            ss << "(function() {\n";
            ss << content_ << "\n";
            ss << "})()";
            break;
    }
    
    // 如果是异步执行，包装在Promise中
    if (isAsync_) {
        std::string wrapped = ss.str();
        ss.str("");
        ss << "Promise.resolve().then(() => {\n";
        ss << "  " << wrapped << ";\n";
        ss << "})";
    }
    
    return ss.str();
}

std::shared_ptr<Node> Script::clone(bool deep) const {
    auto cloned = std::make_shared<Script>();
    
    // 复制所有属性
    cloned->content_ = content_;
    cloned->name_ = name_;
    cloned->scriptType_ = scriptType_;
    cloned->timing_ = timing_;
    cloned->isAsync_ = isAsync_;
    cloned->scope_ = scope_;
    cloned->dependencies_ = dependencies_;
    cloned->exports_ = exports_;
    
    // 复制基类属性
    cloned->setTagName(getTagName());
    // Script nodes don't have attributes like Element nodes
    
    // Script节点通常没有子节点
    if (deep) {
        for (const auto& child : getChildren()) {
            cloned->addChild(child->clone(true));
        }
    }
    
    return cloned;
}

std::string Script::toString() const {
    std::stringstream ss;
    ss << "[Script";
    
    if (hasName()) {
        ss << " @" << name_;
    }
    
    // 显示脚本类型
    switch (scriptType_) {
        case ScriptType::MODULE:
            ss << " type=\"module\"";
            break;
        case ScriptType::GLOBAL:
            ss << " type=\"global\"";
            break;
        case ScriptType::SCOPED:
            if (!scope_.empty()) {
                ss << " scope=\"" << scope_ << "\"";
            }
            break;
        default:
            break;
    }
    
    // 显示执行时机
    switch (timing_) {
        case ExecutionTiming::DEFERRED:
            ss << " defer";
            break;
        case ExecutionTiming::ON_LOAD:
            ss << " onload";
            break;
        case ExecutionTiming::ON_MOUNT:
            ss << " onmount";
            break;
        case ExecutionTiming::ON_DEMAND:
            ss << " ondemand";
            break;
        default:
            break;
    }
    
    if (isAsync_) {
        ss << " async";
    }
    
    ss << "] {";
    
    // 显示内容的前50个字符
    if (!content_.empty()) {
        std::string preview = content_.substr(0, 50);
        if (content_.length() > 50) {
            preview += "...";
        }
        ss << preview;
    }
    
    ss << "}";
    
    return ss.str();
}

void Script::accept(Visitor* visitor) {
    (void)visitor; // Suppress unused parameter warning
    // TODO: Implement when Visitor class is added
    // visitor->visit(this);
}

} // namespace chtl