#ifndef CHTL_BASIC_CONTEXT_H
#define CHTL_BASIC_CONTEXT_H

#include <string>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>
#include "Common/Token.h"

namespace chtl {

// 前向声明
class Node;

// 上下文类型枚举
enum class ContextType {
    CHTL,       // CHTL主上下文
    CSS,        // CSS上下文
    JS,         // JavaScript上下文
    CHTL_JS,    // CHTL-JS上下文
    CONFIG      // 配置上下文
};

// 作用域类型
enum class ScopeType {
    GLOBAL,     // 全局作用域
    NAMESPACE,  // 命名空间作用域
    ELEMENT,    // 元素作用域
    BLOCK,      // 块作用域
    TEMPLATE,   // 模板作用域
    CUSTOM,     // 自定义作用域
    CONFIG,     // 配置作用域
    FUNCTION,   // 函数作用域（JS/CSS）
    CLASS       // 类作用域（JS）
};

// 符号信息
struct SymbolInfo {
    std::string name;
    TokenType type;
    std::string value;
    int line;
    int column;
    ScopeType scope;
    std::unordered_map<std::string, std::string> attributes;
    
    SymbolInfo() : type(TokenType::UNKNOWN), line(0), column(0), scope(ScopeType::GLOBAL) {}
};

// 作用域信息
struct ScopeInfo {
    ScopeType type;
    std::string name;
    int startLine;
    int startColumn;
    std::unordered_map<std::string, SymbolInfo> symbols;
    std::shared_ptr<ScopeInfo> parent;
    
    ScopeInfo(ScopeType t, const std::string& n = "") 
        : type(t), name(n), startLine(0), startColumn(0), parent(nullptr) {}
};

// 上下文基类
class BasicContext {
protected:
    ContextType type_;
    std::string name_;
    std::shared_ptr<ScopeInfo> currentScope_;
    std::stack<std::shared_ptr<ScopeInfo>> scopeStack_;
    std::unordered_map<std::string, SymbolInfo> globalSymbols_;
    
    // 错误和警告
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 配置选项
    std::unordered_map<std::string, std::string> config_;
    
public:
    // 构造函数
    BasicContext(ContextType type, const std::string& name);
    
    // 虚析构函数
    virtual ~BasicContext() = default;
    
    // 获取上下文类型
    ContextType getType() const { return type_; }
    
    // 获取上下文名称
    const std::string& getName() const { return name_; }
    
    // 作用域管理
    virtual void enterScope(ScopeType scopeType, const std::string& scopeName = "");
    virtual void exitScope();
    std::shared_ptr<ScopeInfo> getCurrentScope() const { return currentScope_; }
    bool isInScope(ScopeType scopeType) const;
    
    // 符号管理
    virtual bool addSymbol(const std::string& name, const SymbolInfo& info);
    virtual bool hasSymbol(const std::string& name) const;
    virtual SymbolInfo* getSymbol(const std::string& name);
    virtual const SymbolInfo* getSymbol(const std::string& name) const;
    virtual bool removeSymbol(const std::string& name);
    
    // 查找符号（包括父作用域）
    virtual SymbolInfo* lookupSymbol(const std::string& name);
    virtual const SymbolInfo* lookupSymbol(const std::string& name) const;
    
    // 错误和警告管理
    void addError(const std::string& error) { errors_.push_back(error); }
    void addWarning(const std::string& warning) { warnings_.push_back(warning); }
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    void clearErrors() { errors_.clear(); }
    void clearWarnings() { warnings_.clear(); }
    bool hasErrors() const { return !errors_.empty(); }
    bool hasWarnings() const { return !warnings_.empty(); }
    
    // 配置管理
    void setConfig(const std::string& key, const std::string& value) { config_[key] = value; }
    std::string getConfig(const std::string& key, const std::string& defaultValue = "") const;
    bool hasConfig(const std::string& key) const { return config_.find(key) != config_.end(); }
    const std::unordered_map<std::string, std::string>& getConfiguration() const { return config_; }
    
    // 获取全局符号表
    const std::unordered_map<std::string, SymbolInfo>& getGlobalSymbols() const { return globalSymbols_; }
    
    // 上下文验证
    virtual bool validate() = 0;
    
    // 重置上下文
    virtual void reset();
    
    // 打印调试信息
    virtual void printDebugInfo() const;
    
    // 模板和自定义注册（CHTL特有）
    virtual void registerTemplate(const std::string& name, std::shared_ptr<Node> templateNode) {
        // 默认实现：添加到符号表
        SymbolInfo info{name, "template", "", getCurrentLine(), getCurrentColumn()};
        addSymbol(name, info);
        (void)templateNode; // 避免未使用警告
    }
    virtual void registerCustom(const std::string& name, std::shared_ptr<Node> customNode) {
        // 默认实现：添加到符号表
        SymbolInfo info{name, "custom", "", getCurrentLine(), getCurrentColumn()};
        addSymbol(name, info);
        (void)customNode; // 避免未使用警告
    }
    virtual std::shared_ptr<Node> getTemplate(const std::string& name) const {
        // 子类应该实现具体的获取逻辑
        (void)name; // 避免未使用警告
        return nullptr;
    }
    virtual std::shared_ptr<Node> getCustom(const std::string& name) const {
        // 子类应该实现具体的获取逻辑
        (void)name; // 避免未使用警告
        return nullptr;
    }
    
    // 上下文管理
    virtual void pushContext(const std::string& name);
    virtual void popContext();
    
protected:
    // 辅助方法
    std::string formatError(const std::string& message, int line, int column) const;
    std::string formatWarning(const std::string& message, int line, int column) const;
};

} // namespace chtl

#endif // CHTL_BASIC_CONTEXT_H