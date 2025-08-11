#ifndef CHTL_STYLE_H
#define CHTL_STYLE_H

#include "Node/Node.h"

namespace chtl {

// Style节点 - 支持局部样式（内联或元素内）和全局样式
class Style : public Node {
public:
    enum class StyleScope {
        LOCAL,      // 局部样式（元素内的style块）
        GLOBAL      // 全局样式（独立的style块）
    };
    
    // 添加StyleType别名以与代码一致
    using StyleType = StyleScope;
    
private:
    StyleScope scope_;
    std::string cssContent_;                                    // 原始CSS内容
    std::unordered_map<std::string, std::string> rules_;      // 解析后的CSS规则
    std::vector<std::string> selectors_;                       // CSS选择器
    bool isScoped_ = false;                                    // 是否为作用域样式
    std::string parentElement_;                                // 父元素（用于局部样式）
    std::string selector_;                                     // 主选择器（用于全局样式）
    
public:
    Style(StyleScope scope = StyleScope::LOCAL)
        : Node(NodeType::STYLE, "style"), scope_(scope) {}
    
    // 作用域管理
    StyleScope getScope() const { return scope_; }
    void setScope(StyleScope scope) { scope_ = scope; }
    void setType(StyleType type) { scope_ = type; }
    bool isGlobal() const { return scope_ == StyleScope::GLOBAL; }
    bool isLocal() const { return scope_ == StyleScope::LOCAL; }
    
    // CSS内容管理
    const std::string& getCssContent() const { return cssContent_; }
    void setCssContent(const std::string& content) { cssContent_ = content; }
    void setContent(const std::string& content) { cssContent_ = content; }
    void appendCssContent(const std::string& content) { cssContent_ += content; }
    
    // 主选择器管理（用于全局样式）
    const std::string& getSelector() const { return selector_; }
    void setSelector(const std::string& selector) { selector_ = selector; }
    
    // CSS规则管理
    void addRule(const std::string& property, const std::string& value) { rules_[property] = value; }
    std::string getRule(const std::string& property) const;
    bool hasRule(const std::string& property) const { return rules_.find(property) != rules_.end(); }
    const std::unordered_map<std::string, std::string>& getRules() const { return rules_; }
    void clearRules() { rules_.clear(); }
    
    // 选择器管理
    void addSelector(const std::string& selector) { selectors_.push_back(selector); }
    const std::vector<std::string>& getSelectors() const { return selectors_; }
    void clearSelectors() { selectors_.clear(); }
    
    // 作用域样式
    void setScoped(bool scoped) { isScoped_ = scoped; }
    bool isScoped() const { return isScoped_; }
    
    // 父元素（局部样式）
    void setParentElement(const std::string& element) { parentElement_ = element; }
    const std::string& getParentElement() const { return parentElement_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_STYLE_H