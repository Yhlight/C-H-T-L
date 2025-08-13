#ifndef CHTLJS_CONTEXT_H
#define CHTLJS_CONTEXT_H

#include <string>
#include <memory>
#include <unordered_map>
#include <stack>
#include <vector>
#include "CHTLJSStateMachine.h"

namespace chtl {

// 前向声明
class CHTLContext;

// CHTL JS符号信息
struct CHTLJSSymbol {
    enum Type {
        Variable,
        Function,
        Selector,
        Method,
        Animation,
        UnquotedValue
    };
    
    Type type;
    std::string name;
    std::string value;
    std::string scope;
    int lineNumber;
    
    // 无修饰字面量特定信息
    bool isUnquoted = false;
    std::string quotedValue;  // 转换后的引号版本
};

// CHTL JS作用域
class CHTLJSScope {
private:
    std::string name;
    std::unordered_map<std::string, CHTLJSSymbol> symbols;
    std::shared_ptr<CHTLJSScope> parent;
    
public:
    CHTLJSScope(const std::string& n, std::shared_ptr<CHTLJSScope> p = nullptr)
        : name(n), parent(p) {}
    
    void addSymbol(const std::string& name, const CHTLJSSymbol& symbol);
    CHTLJSSymbol* findSymbol(const std::string& name);
    const CHTLJSSymbol* findSymbol(const std::string& name) const;
    
    const std::string& getName() const { return name; }
    std::shared_ptr<CHTLJSScope> getParent() const { return parent; }
};

// CHTL JS上下文
class CHTLJSContext {
private:
    std::shared_ptr<CHTLContext> baseContext;
    std::shared_ptr<CHTLJSScope> globalScope;
    std::shared_ptr<CHTLJSScope> currentScope;
    std::stack<std::shared_ptr<CHTLJSScope>> scopeStack;
    
    // 状态机
    std::unique_ptr<CHTLJSStateMachine> stateMachine;
    
    // DOM引用缓存
    std::unordered_map<std::string, std::string> domReferences;
    
    // 事件绑定记录
    std::vector<std::pair<std::string, std::string>> eventBindings;
    
    // 动画定义
    std::unordered_map<std::string, std::string> animations;
    
    // 无修饰字面量映射
    std::unordered_map<std::string, std::string> unquotedLiterals;
    
    // 配置选项
    struct Config {
        bool allowUnquotedLiterals = true;
        bool autoQuoteUnquoted = true;
        bool validateUnquoted = true;
    } config;
    
public:
    CHTLJSContext(std::shared_ptr<CHTLContext> base);
    
    // 作用域管理
    void enterScope(const std::string& name);
    void exitScope();
    std::shared_ptr<CHTLJSScope> getCurrentScope() const { return currentScope; }
    
    // 符号管理
    void addVariable(const std::string& name, const std::string& value, bool isUnquoted = false);
    void addFunction(const std::string& name, const std::string& params);
    void addSelector(const std::string& selector);
    void addMethod(const std::string& object, const std::string& method);
    void addAnimation(const std::string& name, const std::string& config);
    
    // 无修饰字面量管理
    bool isUnquotedLiteralAllowed() const;
    bool validateUnquotedLiteral(const std::string& value) const;
    std::string processUnquotedLiteral(const std::string& value);
    void registerUnquotedLiteral(const std::string& original, const std::string& quoted);
    
    // DOM引用管理
    void addDOMReference(const std::string& selector, const std::string& jsCode);
    std::string getDOMReference(const std::string& selector) const;
    
    // 事件绑定管理
    void addEventBinding(const std::string& selector, const std::string& event);
    const std::vector<std::pair<std::string, std::string>>& getEventBindings() const { 
        return eventBindings; 
    }
    
    // 状态机访问
    CHTLJSStateMachine& getStateMachine() { return *stateMachine; }
    const CHTLJSStateMachine& getStateMachine() const { return *stateMachine; }
    
    // 配置
    void setAllowUnquotedLiterals(bool allow) { config.allowUnquotedLiterals = allow; }
    void setAutoQuoteUnquoted(bool autoQuote) { config.autoQuoteUnquoted = autoQuote; }
    void setValidateUnquoted(bool validate) { config.validateUnquoted = validate; }
    
    bool getAllowUnquotedLiterals() const { return config.allowUnquotedLiterals; }
    bool getAutoQuoteUnquoted() const { return config.autoQuoteUnquoted; }
    bool getValidateUnquoted() const { return config.validateUnquoted; }
    
    // 错误处理
    void reportError(const std::string& error);
    void reportWarning(const std::string& warning);
    
    // 重置
    void reset();
    
    // 调试
    void dumpSymbols() const;
    void dumpUnquotedLiterals() const;
};

// CHTL JS上下文辅助工具
namespace CHTLJSContextHelper {
    // 检测是否需要引号
    bool needsQuotes(const std::string& value);
    
    // 智能引号添加
    std::string smartQuote(const std::string& value);
    
    // 验证标识符
    bool isValidIdentifier(const std::string& identifier);
    
    // 提取选择器类型
    std::string extractSelectorType(const std::string& selector);
}

} // namespace chtl

#endif // CHTLJS_CONTEXT_H