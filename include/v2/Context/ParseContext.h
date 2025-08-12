#pragma once

#include "v2/State/ChtlParseState.h"
#include <string>
#include <map>
#include <memory>
#include <vector>

namespace chtl::v2 {

// 前向声明
class Node;
class Scope;

/**
 * CSS 上下文数据
 */
struct CssContextData {
    std::string currentSelector;
    std::string currentPropertyName;
    std::string currentPropertyValue;
    bool inPropertyValue = false;
};

/**
 * 模板上下文数据
 */
struct TemplateContextData {
    std::string templateName;
    std::vector<std::string> parameters;
    std::map<std::string, std::string> parameterValues;
    bool isDefinition = true;  // true: 定义, false: 引用
};

/**
 * 元素上下文数据
 */
struct ElementContextData {
    std::string tagName;
    std::string id;
    std::vector<std::string> classes;
    std::map<std::string, std::string> attributes;
    bool hasLocalStyle = false;
    bool hasLocalScript = false;
};

/**
 * 解析上下文
 * 包含当前解析状态的所有相关信息
 */
class ParseContext {
public:
    ParseContext(ChtlParseState state);
    ~ParseContext();
    
    // 状态管理
    ChtlParseState getState() const { return state_; }
    void setState(ChtlParseState state) { state_ = state; }
    
    // 节点管理
    std::shared_ptr<Node> getCurrentNode() const { return currentNode_; }
    void setCurrentNode(std::shared_ptr<Node> node) { currentNode_ = node; }
    
    // 作用域管理
    std::shared_ptr<Scope> getCurrentScope() const { return currentScope_; }
    void setCurrentScope(std::shared_ptr<Scope> scope) { currentScope_ = scope; }
    
    // 进入新作用域
    void enterScope(const std::string& name = "");
    void exitScope();
    
    // 变量管理
    void defineVariable(const std::string& name, const std::string& value);
    bool hasVariable(const std::string& name) const;
    std::string getVariable(const std::string& name) const;
    
    // 模板参数管理（用于模板定义内部）
    void defineParameter(const std::string& name);
    bool isParameter(const std::string& name) const;
    
    // 上下文特定数据访问
    CssContextData& getCssData() { return cssData_; }
    const CssContextData& getCssData() const { return cssData_; }
    
    TemplateContextData& getTemplateData() { return templateData_; }
    const TemplateContextData& getTemplateData() const { return templateData_; }
    
    ElementContextData& getElementData() { return elementData_; }
    const ElementContextData& getElementData() const { return elementData_; }
    
    // 错误位置信息
    void setLocation(int line, int column) {
        currentLine_ = line;
        currentColumn_ = column;
    }
    int getCurrentLine() const { return currentLine_; }
    int getCurrentColumn() const { return currentColumn_; }
    
    // 调试信息
    std::string toString() const;
    
private:
    ChtlParseState state_;
    std::shared_ptr<Node> currentNode_;
    std::shared_ptr<Scope> currentScope_;
    
    // 位置信息
    int currentLine_ = 1;
    int currentColumn_ = 1;
    
    // 上下文特定数据
    CssContextData cssData_;
    TemplateContextData templateData_;
    ElementContextData elementData_;
    
    // 作用域栈（用于嵌套作用域）
    std::vector<std::shared_ptr<Scope>> scopeStack_;
};

/**
 * 作用域
 * 管理变量和符号的可见性
 */
class Scope {
public:
    explicit Scope(const std::string& name = "", std::shared_ptr<Scope> parent = nullptr);
    
    // 变量管理
    void define(const std::string& name, const std::string& value);
    bool has(const std::string& name) const;
    std::string get(const std::string& name) const;
    
    // 参数管理（用于模板作用域）
    void defineParameter(const std::string& name);
    bool isParameter(const std::string& name) const;
    const std::vector<std::string>& getParameters() const { return parameters_; }
    
    // 父作用域
    std::shared_ptr<Scope> getParent() const { return parent_; }
    
    // 作用域名称（用于调试）
    const std::string& getName() const { return name_; }
    
private:
    std::string name_;
    std::shared_ptr<Scope> parent_;
    std::map<std::string, std::string> variables_;
    std::vector<std::string> parameters_;
};

} // namespace chtl::v2