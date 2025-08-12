#ifndef CHTL_JS_RUNTIME_H
#define CHTL_JS_RUNTIME_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>
#include <set>

namespace chtl {

// 前向声明
class Script;

// 事件委托信息
struct EventDelegation {
    std::string parentSelector;           // 父元素选择器
    std::vector<std::string> targetSelectors;  // 目标元素选择器列表
    std::string eventType;                // 事件类型
    std::string handlerCode;              // 处理函数代码
    std::string handlerId;                // 处理函数ID（用于去重）
};

// CHTL JS运行时环境
class ChtlJsRuntime {
public:
    static ChtlJsRuntime& getInstance() {
        static ChtlJsRuntime instance;
        return instance;
    }
    
private:
    ChtlJsRuntime() = default;
    
    // 全局表：存储事件委托
    std::unordered_map<std::string, std::vector<EventDelegation>> eventDelegations_;
    
    // 收集的局部script块代码
    std::vector<std::string> collectedScripts_;
    
    // 已注册的处理函数ID（用于去重）
    std::set<std::string> registeredHandlers_;
    
    // 元素ID计数器
    int elementIdCounter_ = 0;
    
public:
    // 禁用拷贝和赋值
    ChtlJsRuntime(const ChtlJsRuntime&) = delete;
    ChtlJsRuntime& operator=(const ChtlJsRuntime&) = delete;
    
    // 脚本收集
    struct ElementInfo {
        std::string id;
        std::string className;
        bool hasLocalStyle = false;
        std::string localStyleSelector; // 局部样式中定义的选择器
    };
    
    void collectLocalScript(const std::string& scriptCode, const ElementInfo& elementInfo);
    
    // 保留旧的接口以兼容
    void collectLocalScript(const std::string& scriptCode, const std::string& elementId) {
        ElementInfo info;
        info.id = elementId;
        collectLocalScript(scriptCode, info);
    }
    
    // 注册事件委托
    void registerEventDelegation(const EventDelegation& delegation);
    
    // 生成运行时代码
    std::string generateRuntimeCode();
    
    // 生成事件委托代码
    std::string generateDelegationCode();
    
    // 生成delegate函数定义
    std::string generateDelegateFunction();
    
    // 生成增强方法（listen、animate等）
    std::string generateEnhancedMethods();
    
    // 处理{{&}}语法（在特定上下文中）
    std::string processAmpersandSyntax(const std::string& code, const ElementInfo& elementInfo);
    
    // 解析delegate调用
    std::vector<EventDelegation> parseDelegateCall(const std::string& code);
    
    // 生成唯一的元素ID
    std::string generateElementId();
    
    // 清空运行时状态（用于新文档）
    void reset();
    
    // 获取事件委托信息
    const std::unordered_map<std::string, std::vector<EventDelegation>>& getEventDelegations() const {
        return eventDelegations_;
    }
    
    // 检查是否有已收集的脚本
    bool hasCollectedScripts() const {
        return !collectedScripts_.empty();
    }
};

// CHTL JS语法增强处理器
class ChtlJsEnhancer {
private:
    bool inLocalScriptBlock_ = false;
    std::string currentElementId_;
    
public:
    // 设置当前处理的元素上下文
    void setElementContext(const std::string& elementId) {
        currentElementId_ = elementId;
    }
    
    // 进入/退出局部script块
    void enterLocalScriptBlock() { inLocalScriptBlock_ = true; }
    void exitLocalScriptBlock() { inLocalScriptBlock_ = false; }
    
    // 处理script代码
    std::string processScript(const std::string& scriptCode);
    
    // 提取delegate调用
    std::string extractDelegateCalls(const std::string& code);
    
    // 转换{{selector}}语法为document.querySelector
    std::string transformSelectorSyntax(const std::string& code);
    
    // 转换单个选择器
    std::string transformSingleSelector(const std::string& selector, const std::string& index = "");
    
    // 转换animate语法
    std::string transformAnimateSyntax(const std::string& code);
    
    // 查找匹配的大括号
    size_t findMatchingBrace(const std::string& code, size_t startPos);
    
    // 查找最近的选择器
    std::string findNearestSelector(const std::string& code);
    
    // 包装局部script代码
    std::string wrapLocalScript(const std::string& code, const std::string& elementId);
};

} // namespace chtl

#endif // CHTL_JS_RUNTIME_H