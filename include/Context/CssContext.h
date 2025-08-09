#ifndef CHTL_CSS_CONTEXT_H
#define CHTL_CSS_CONTEXT_H

#include "Context/BasicContext.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace chtl {

// CSS上下文 - 管理CSS解析过程中的信息
class CssContext : public BasicContext {
private:
    // CSS选择器信息
    std::unordered_set<std::string> selectors_;
    std::unordered_set<std::string> classNames_;
    std::unordered_set<std::string> idNames_;
    
    // CSS属性信息
    std::unordered_map<std::string, std::vector<std::string>> properties_;  // 属性名 -> 值列表
    std::unordered_map<std::string, std::string> variables_;  // CSS变量
    
    // @规则信息
    std::vector<std::string> mediaQueries_;
    std::vector<std::string> keyframes_;
    std::vector<std::string> imports_;
    
    // 当前解析状态
    std::string currentSelector_;
    std::string currentProperty_;
    std::string currentAtRule_;
    
    // 统计信息
    int ruleCount_;
    int declarationCount_;

public:
    CssContext();
    virtual ~CssContext() = default;
    
    // BasicContext接口实现
    void enterScope() override;
    void exitScope() override;
    void reset() override;
    
    // CSS选择器管理
    void addSelector(const std::string& selector);
    void addClass(const std::string& className);
    void addId(const std::string& id);
    bool hasSelector(const std::string& selector) const;
    std::vector<std::string> getAllSelectors() const;
    
    // CSS属性管理
    void addProperty(const std::string& property, const std::string& value);
    void addVariable(const std::string& name, const std::string& value);
    bool hasProperty(const std::string& property) const;
    std::vector<std::string> getPropertyValues(const std::string& property) const;
    
    // @规则管理
    void addMediaQuery(const std::string& query);
    void addKeyframe(const std::string& name);
    void addImport(const std::string& url);
    
    // 当前状态管理
    void setCurrentSelector(const std::string& selector) { currentSelector_ = selector; }
    void setCurrentProperty(const std::string& property) { currentProperty_ = property; }
    void setCurrentAtRule(const std::string& rule) { currentAtRule_ = rule; }
    
    std::string getCurrentSelector() const { return currentSelector_; }
    std::string getCurrentProperty() const { return currentProperty_; }
    std::string getCurrentAtRule() const { return currentAtRule_; }
    
    // 统计信息
    int getRuleCount() const { return ruleCount_; }
    int getDeclarationCount() const { return declarationCount_; }
    void incrementRuleCount() { ruleCount_++; }
    void incrementDeclarationCount() { declarationCount_++; }
    
    // CSS验证
    bool isValidSelector(const std::string& selector) const;
    bool isValidProperty(const std::string& property) const;
    bool isValidValue(const std::string& property, const std::string& value) const;
};

} // namespace chtl

#endif // CHTL_CSS_CONTEXT_H