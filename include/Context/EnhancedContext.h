#ifndef CHTL_ENHANCED_CONTEXT_H
#define CHTL_ENHANCED_CONTEXT_H

#include "Context/StandardContext.h"
#include <memory>
#include <unordered_map>
#include <stack>
#include <optional>
#include <variant>

namespace chtl {

// 作用域类型
enum class Scope {
    GLOBAL,              // 全局作用域
    TOP_LEVEL,           // 文件顶层
    TEMPLATE_DEFINITION, // 模板定义内部
    CUSTOM_DEFINITION,   // 自定义组件定义内部
    ELEMENT_BODY,        // 元素体内部
    STYLE_BLOCK,         // style {} 块内部
    SCRIPT_BLOCK,        // script {} 块内部
    NAMESPACE_BLOCK      // 命名空间内部
};

// 组件模板
struct ComponentTemplate {
    std::string name;
    std::string type;  // "Element"
    std::unique_ptr<Node> content;  // 模板内容
    std::unordered_map<std::string, std::string> defaultProps;
    
    // 克隆模板内容
    std::unique_ptr<Node> instantiate() const;
};

// 样式模板
struct StyleTemplate {
    std::string name;
    std::string cssContent;  // 纯 CSS 内容
    std::vector<std::pair<std::string, std::string>> rules;  // 属性-值对
};

// 变量组
struct VariableGroup {
    std::string name;
    std::unordered_map<std::string, std::string> values;
    
    // 获取变量值
    std::optional<std::string> getValue(const std::string& key) const {
        auto it = values.find(key);
        return it != values.end() ? std::optional<std::string>(it->second) : std::nullopt;
    }
};

// 当前元素上下文
struct ElementContext {
    std::string tagName;
    std::vector<std::string> classes;
    std::string id;
    Node* currentNode;  // 当前正在处理的节点
};

class EnhancedContext : public StandardContext {
private:
    // 模板存储
    std::unordered_map<std::string, ComponentTemplate> components_;
    std::unordered_map<std::string, StyleTemplate> styles_;
    std::unordered_map<std::string, VariableGroup> variables_;
    
    // 命名空间模板存储
    std::unordered_map<std::string, std::unordered_map<std::string, ComponentTemplate>> nsComponents_;
    std::unordered_map<std::string, std::unordered_map<std::string, StyleTemplate>> nsStyles_;
    std::unordered_map<std::string, std::unordered_map<std::string, VariableGroup>> nsVariables_;
    
    // 作用域栈
    std::stack<Scope> scopeStack_;
    
    // 元素上下文栈（用于 & 推导）
    std::stack<ElementContext> elementStack_;
    
    // 当前命名空间
    std::string currentNamespace_;
    
public:
    EnhancedContext();
    virtual ~EnhancedContext() = default;
    
    // 作用域管理
    void pushScope(Scope scope);
    void popScope();
    Scope getCurrentScope() const;
    bool isInScope(Scope scope) const;
    
    // 元素上下文管理
    void pushElement(const ElementContext& ctx);
    void popElement();
    ElementContext* getCurrentElement();
    
    // 模板注册（编译时）
    void registerComponent(const std::string& name, ComponentTemplate&& tmpl);
    void registerStyle(const std::string& name, StyleTemplate&& tmpl);
    void registerVariable(const std::string& name, VariableGroup&& vars);
    
    // 命名空间模板注册
    void registerNamespacedComponent(const std::string& ns, const std::string& name, ComponentTemplate&& tmpl);
    void registerNamespacedStyle(const std::string& ns, const std::string& name, StyleTemplate&& tmpl);
    void registerNamespacedVariable(const std::string& ns, const std::string& name, VariableGroup&& vars);
    
    // 模板查找
    ComponentTemplate* findComponent(const std::string& name);
    StyleTemplate* findStyle(const std::string& name);
    VariableGroup* findVariable(const std::string& name);
    
    // 带命名空间的查找
    ComponentTemplate* findComponent(const std::string& ns, const std::string& name);
    StyleTemplate* findStyle(const std::string& ns, const std::string& name);
    VariableGroup* findVariable(const std::string& ns, const std::string& name);
    
    // 变量值查找（用于编译时替换）
    std::optional<std::string> getVariableValue(const std::string& groupName, const std::string& key);
    std::optional<std::string> getVariableValue(const std::string& ns, const std::string& groupName, const std::string& key);
    
    // & 符号推导
    std::string resolveAmpersand() const;
    
    // 命名空间管理
    void enterNamespace(const std::string& name);
    void exitNamespace();
    std::string getCurrentNamespace() const { return currentNamespace_; }
    
    // 验证方法
    bool isValidComponentName(const std::string& name) const;
    bool isValidStyleName(const std::string& name) const;
    bool isValidVariableName(const std::string& name) const;
    
    // 错误报告增强
    void reportUndefinedComponent(const std::string& name);
    void reportUndefinedStyle(const std::string& name);
    void reportUndefinedVariable(const std::string& group, const std::string& key);
    
    // 调试支持
    void dumpTemplates() const;
};

} // namespace chtl

#endif // CHTL_ENHANCED_CONTEXT_H