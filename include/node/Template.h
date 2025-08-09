#ifndef CHTL_TEMPLATE_H
#define CHTL_TEMPLATE_H

#include "node/Node.h"

namespace chtl {

// Template节点 - 支持三种模板类型：@Style、@Element、@Var
class Template : public Node {
public:
    enum class TemplateType {
        STYLE,      // @Style模板
        ELEMENT,    // @Element模板
        VAR         // @Var模板
    };
    
private:
    TemplateType templateType_;
    std::string templateName_;
    std::unordered_map<std::string, std::string> parameters_;  // 模板参数
    std::vector<std::string> inheritFrom_;                     // 继承列表
    bool isExplicitInherit_ = false;                          // 是否显式inherit
    
public:
    Template(TemplateType type, const std::string& name)
        : Node(NodeType::TEMPLATE, "[Template]"), templateType_(type), templateName_(name) {}
    
    // 模板类型和名称
    TemplateType getTemplateType() const { return templateType_; }
    const std::string& getTemplateName() const { return templateName_; }
    void setTemplateName(const std::string& name) { templateName_ = name; }
    
    // 参数管理
    void setParameter(const std::string& name, const std::string& value) { parameters_[name] = value; }
    std::string getParameter(const std::string& name) const;
    bool hasParameter(const std::string& name) const { return parameters_.find(name) != parameters_.end(); }
    const std::unordered_map<std::string, std::string>& getParameters() const { return parameters_; }
    
    // 继承管理
    void addInheritance(const std::string& templateName) { inheritFrom_.push_back(templateName); }
    const std::vector<std::string>& getInheritance() const { return inheritFrom_; }
    void setExplicitInherit(bool explicit_) { isExplicitInherit_ = explicit_; }
    bool isExplicitInherit() const { return isExplicitInherit_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_TEMPLATE_H