#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace CHTL {

// 符号类型
enum class SymbolType {
    TEMPLATE_STYLE,
    TEMPLATE_ELEMENT,
    TEMPLATE_VAR,
    CUSTOM_STYLE,
    CUSTOM_ELEMENT,
    CUSTOM_VAR,
    NAMESPACE,
    IMPORT,
    VARIABLE
};

// 符号信息
class Symbol {
public:
    Symbol(const std::string& name, SymbolType type);
    
    const std::string& getName() const { return name_; }
    SymbolType getType() const { return type_; }
    
    void setNamespace(const std::string& ns) { namespace_ = ns; }
    const std::string& getNamespace() const { return namespace_; }
    
    void setFilePath(const std::string& path) { filePath_ = path; }
    const std::string& getFilePath() const { return filePath_; }
    
    // 对于变量类型的符号
    void setValue(const std::string& value) { value_ = value; }
    const std::string& getValue() const { return value_; }
    
    // 对于模板和自定义类型
    void setContent(std::shared_ptr<void> content) { content_ = content; }
    std::shared_ptr<void> getContent() const { return content_; }
    
private:
    std::string name_;
    SymbolType type_;
    std::string namespace_;
    std::string filePath_;
    std::string value_;
    std::shared_ptr<void> content_;
};

// 作用域
class Scope {
public:
    explicit Scope(const std::string& name = "", Scope* parent = nullptr);
    
    // 符号管理
    bool addSymbol(std::shared_ptr<Symbol> symbol);
    std::shared_ptr<Symbol> findSymbol(const std::string& name, SymbolType type) const;
    std::shared_ptr<Symbol> findSymbolInScope(const std::string& name, SymbolType type) const;
    
    // 子作用域管理
    Scope* createChildScope(const std::string& name);
    Scope* getParent() const { return parent_; }
    const std::vector<std::unique_ptr<Scope>>& getChildren() const { return children_; }
    
    const std::string& getName() const { return name_; }
    
private:
    std::string name_;
    Scope* parent_;
    std::vector<std::unique_ptr<Scope>> children_;
    std::unordered_multimap<std::string, std::shared_ptr<Symbol>> symbols_;
};

// 符号表
class SymbolTable {
public:
    SymbolTable();
    
    // 作用域管理
    void enterScope(const std::string& name = "");
    void exitScope();
    Scope* getCurrentScope() const { return currentScope_; }
    
    // 符号管理
    bool defineSymbol(const std::string& name, SymbolType type);
    bool defineSymbol(std::shared_ptr<Symbol> symbol);
    std::shared_ptr<Symbol> lookupSymbol(const std::string& name, SymbolType type) const;
    
    // 命名空间支持
    bool defineNamespace(const std::string& name);
    bool enterNamespace(const std::string& name);
    void exitNamespace();
    std::string getCurrentNamespace() const;
    
    // 导入管理
    void addImport(const std::string& path, const std::string& alias = "");
    std::vector<std::string> getImports() const;
    
    // 配置管理
    void setConfiguration(const std::string& key, const std::string& value);
    std::string getConfiguration(const std::string& key) const;
    
    // 验证
    bool validateSymbolUsage(const std::string& name, SymbolType type) const;
    std::vector<std::string> getUndefinedSymbols() const;
    
private:
    std::unique_ptr<Scope> rootScope_;
    Scope* currentScope_;
    std::vector<std::string> namespaceStack_;
    std::unordered_map<std::string, std::string> configurations_;
    std::vector<std::pair<std::string, std::string>> imports_; // path, alias
    mutable std::vector<std::string> undefinedSymbols_;
};

} // namespace CHTL

#endif // SYMBOL_TABLE_H