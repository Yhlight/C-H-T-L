#ifndef CHTL_STATE_SYMBOLTABLE_H
#define CHTL_STATE_SYMBOLTABLE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <stack>
#include "Common/Types.h"
#include "Node/Node.h"

namespace CHTL {

// Forward declarations
class Symbol;
class Scope;
using SymbolPtr = std::shared_ptr<Symbol>;
using ScopePtr = std::shared_ptr<Scope>;

/**
 * 符号 - 表示符号表中的一个条目
 */
class Symbol {
public:
    Symbol(const std::string& name, SymbolType type);
    ~Symbol() = default;
    
    // 基本属性
    const std::string& getName() const { return name_; }
    SymbolType getType() const { return type_; }
    
    // 作用域
    void setScope(Scope* scope) { scope_ = scope; }
    Scope* getScope() const { return scope_; }
    
    // 内容（如模板、自定义的AST节点）
    void setContent(NodePtr content) { content_ = content; }
    NodePtr getContent() const { return content_; }
    
    // 值（用于变量）
    void setValue(const std::string& value) { value_ = value; }
    const std::string& getValue() const { return value_; }
    
    // 属性
    void setAttribute(const std::string& key, const std::string& value);
    std::string getAttribute(const std::string& key) const;
    bool hasAttribute(const std::string& key) const;
    
    // 位置信息
    void setLocation(int line, int column) { line_ = line; column_ = column; }
    int getLine() const { return line_; }
    int getColumn() const { return column_; }
    
    // 调试信息
    std::string toString() const;
    
private:
    std::string name_;
    SymbolType type_;
    Scope* scope_ = nullptr;
    NodePtr content_;
    std::string value_;
    std::unordered_map<std::string, std::string> attributes_;
    int line_ = 0;
    int column_ = 0;
};

/**
 * 作用域 - 表示符号的作用域
 */
class Scope {
public:
    enum class ScopeType {
        GLOBAL,
        NAMESPACE,
        TEMPLATE,
        CUSTOM,
        ELEMENT,
        BLOCK
    };
    
    Scope(const std::string& name, ScopeType type, Scope* parent = nullptr);
    ~Scope() = default;
    
    // 基本属性
    const std::string& getName() const { return name_; }
    ScopeType getType() const { return type_; }
    
    // 父子关系
    Scope* getParent() const { return parent_; }
    void addChild(ScopePtr child);
    const std::vector<ScopePtr>& getChildren() const { return children_; }
    
    // 符号管理
    bool define(SymbolPtr symbol);
    SymbolPtr lookup(const std::string& name) const;
    SymbolPtr lookupLocal(const std::string& name) const;
    
    // 获取所有符号
    const std::unordered_map<std::string, SymbolPtr>& getSymbols() const { return symbols_; }
    
    // 命名空间支持
    void setNamespace(const std::string& ns) { namespace_ = ns; }
    const std::string& getNamespace() const { return namespace_; }
    
    // 获取完整限定名
    std::string getQualifiedName() const;
    
    // 调试信息
    std::string toString() const;
    
private:
    std::string name_;
    ScopeType type_;
    Scope* parent_;
    std::vector<ScopePtr> children_;
    std::unordered_map<std::string, SymbolPtr> symbols_;
    std::string namespace_;
};

/**
 * 符号表 - 管理所有符号和作用域
 */
class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable() = default;
    
    // 作用域管理
    void enterScope(const std::string& name, Scope::ScopeType type);
    void exitScope();
    Scope* getCurrentScope() const { return currentScope_; }
    
    // 符号定义和查找
    bool defineSymbol(SymbolPtr symbol);
    SymbolPtr lookupSymbol(const std::string& name) const;
    SymbolPtr lookupSymbolInNamespace(const std::string& name, const std::string& ns) const;
    
    // 命名空间管理
    void enterNamespace(const std::string& ns);
    void exitNamespace();
    const std::string& getCurrentNamespace() const { return currentNamespace_; }
    
    // 导入管理
    void addImport(const std::string& path, const std::string& alias = "");
    bool hasImport(const std::string& path) const;
    std::string getImportAlias(const std::string& path) const;
    
    // 获取所有符号（用于代码生成）
    std::vector<SymbolPtr> getAllSymbols() const;
    std::vector<SymbolPtr> getSymbolsByType(SymbolType type) const;
    
    // 错误处理
    void addError(const std::string& error, int line = 0, int column = 0);
    const std::vector<std::string>& getErrors() const { return errors_; }
    
    // 清理
    void clear();
    
    // 调试
    void printSymbolTable() const;
    
private:
    // 全局作用域
    ScopePtr globalScope_;
    
    // 当前作用域
    Scope* currentScope_;
    
    // 作用域栈
    std::stack<Scope*> scopeStack_;
    
    // 当前命名空间
    std::string currentNamespace_;
    
    // 命名空间栈
    std::stack<std::string> namespaceStack_;
    
    // 导入映射 (path -> alias)
    std::unordered_map<std::string, std::string> imports_;
    
    // 错误信息
    std::vector<std::string> errors_;
    
    // 辅助方法
    void collectSymbols(Scope* scope, std::vector<SymbolPtr>& symbols) const;
};

} // namespace CHTL

#endif // CHTL_STATE_SYMBOLTABLE_H