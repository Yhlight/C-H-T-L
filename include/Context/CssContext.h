#ifndef CHTL_CSS_CONTEXT_H
#define CHTL_CSS_CONTEXT_H

#include "Context/BasicContext.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>

namespace chtl {

// CSS上下文 - 管理CSS解析过程中的信息
class CssContext : public BasicContext {
public:
    // 上下文状态管理
    enum class BlockType {
        NONE,
        SELECTOR,
        AT_RULE,
        MEDIA_QUERY,
        KEYFRAME
    };
    
    CssContext();
    virtual ~CssContext() = default;
    
    // BasicContext接口实现
    void enterScope(ScopeType scopeType, const std::string& scopeName = "") override;
    void exitScope() override;
    void reset() override;
    bool validate() override { return true; } // Placeholder
    
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
    
    // 验证方法
    bool isValidSelector(const std::string& selector) const;
    bool isValidProperty(const std::string& property) const;
    bool isValidValue(const std::string& property, const std::string& value) const;
    
    // 上下文状态管理
    void setCurrentBlock(BlockType type);
    BlockType getCurrentBlock() const;
    
    // 获取收集的信息
    std::set<std::string> getSelectors() const;
    std::set<std::string> getClassNames() const;
    std::set<std::string> getIdNames() const;
    std::vector<std::string> getImports() const;
    std::set<std::string> getMediaQueries() const;
    
    // CSS特定方法
    bool hasClass(const std::string& className) const;
    bool hasId(const std::string& idName) const;
    void addCustomProperty(const std::string& name, const std::string& value);
    std::string getProperty(const std::string& selector, const std::string& property) const;
    std::string getCustomProperty(const std::string& name) const;
    
    // 统计信息
    int getRuleCount() const { return ruleCount_; }
    int getDeclarationCount() const { return declarationCount_; }
    
    // 状态信息
    std::string getCurrentSelector() const { return currentSelector_; }
    
private:
    // CSS选择器存储
    std::set<std::string> selectors_;
    std::set<std::string> classNames_;
    std::set<std::string> idNames_;
    
    // CSS属性存储
    std::map<std::string, std::map<std::string, std::string>> properties_;
    std::map<std::string, std::string> customProperties_;
    
    // CSS特性存储
    std::set<std::string> mediaQueries_;
    std::vector<std::string> imports_;
    
    // 当前状态
    std::string currentSelector_;
    BlockType currentBlock_ = BlockType::NONE;
    std::stack<std::string> selectorStack_;
    
    // 统计信息
    int ruleCount_;
    int declarationCount_;
};

} // namespace chtl

#endif // CHTL_CSS_CONTEXT_H