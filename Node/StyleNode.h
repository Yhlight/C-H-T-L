#ifndef CHTL_NODE_STYLENODE_H
#define CHTL_NODE_STYLENODE_H

#include "Node.h"
#include <unordered_map>
#include <vector>

namespace CHTL {

/**
 * 样式节点 - 表示style块
 */
class StyleNode : public Node {
public:
    StyleNode();
    ~StyleNode() = default;
    
    // 实现visitor模式
    void accept(NodeVisitor* visitor) override;
    
    // 内联样式
    void addInlineStyle(const std::string& property, const std::string& value);
    const std::unordered_map<std::string, std::string>& getInlineStyles() const { return inlineStyles_; }
    
    // 类选择器
    void addClassSelector(const std::string& className);
    void addClassRule(const std::string& className, const std::string& property, const std::string& value);
    const std::vector<std::string>& getClassSelectors() const { return classSelectors_; }
    const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getClassRules() const { return classRules_; }
    
    // ID选择器
    void addIdSelector(const std::string& id);
    void addIdRule(const std::string& id, const std::string& property, const std::string& value);
    const std::vector<std::string>& getIdSelectors() const { return idSelectors_; }
    const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getIdRules() const { return idRules_; }
    
    // 原始CSS内容
    void setRawCSS(const std::string& css) { rawCSS_ = css; }
    const std::string& getRawCSS() const { return rawCSS_; }
    
    // 作用域（用于生成唯一的类名）
    void setScope(const std::string& scope) { scope_ = scope; }
    const std::string& getScope() const { return scope_; }
    
    // 是否是全局样式
    void setGlobal(bool global) { global_ = global; }
    bool isGlobal() const { return global_; }
    
    // 克隆
    NodePtr clone() const override;
    
    // 调试信息
    std::string toString() const override;
    
private:
    // 内联样式
    std::unordered_map<std::string, std::string> inlineStyles_;
    
    // 类选择器和规则
    std::vector<std::string> classSelectors_;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> classRules_;
    
    // ID选择器和规则
    std::vector<std::string> idSelectors_;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> idRules_;
    
    // 原始CSS
    std::string rawCSS_;
    
    // 作用域
    std::string scope_;
    
    // 是否全局
    bool global_ = false;
};

} // namespace CHTL

#endif // CHTL_NODE_STYLENODE_H