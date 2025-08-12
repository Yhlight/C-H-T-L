#ifndef CHTL_NODE_TEMPLATENODE_H
#define CHTL_NODE_TEMPLATENODE_H

#include "Node.h"
#include <vector>

namespace CHTL {

/**
 * 模板节点 - 表示@Style, @Element, @Var模板
 */
class TemplateNode : public Node {
public:
    enum class TemplateType {
        STYLE,
        ELEMENT,
        VAR
    };
    
    TemplateNode(TemplateType type, const std::string& name);
    ~TemplateNode() = default;
    
    // 实现visitor模式
    void accept(NodeVisitor* visitor) override;
    
    // 模板类型
    TemplateType getTemplateType() const { return templateType_; }
    
    // 模板名称
    const std::string& getName() const { return name_; }
    
    // 继承
    void setInherits(const std::string& inherits) { inherits_ = inherits; }
    const std::string& getInherits() const { return inherits_; }
    bool hasInherits() const { return !inherits_.empty(); }
    
    // 参数（用于@Var模板）
    void addParameter(const std::string& name, const std::string& defaultValue = "");
    bool hasParameter(const std::string& name) const;
    const std::string& getParameterDefault(const std::string& name) const;
    const std::vector<std::pair<std::string, std::string>>& getParameters() const { return parameters_; }
    
    // 导出设置
    void setExported(bool exported) { exported_ = exported; }
    bool isExported() const { return exported_; }
    
    // 命名空间
    void setNamespace(const std::string& ns) { namespace_ = ns; }
    const std::string& getNamespace() const { return namespace_; }
    
    // 获取完整限定名
    std::string getQualifiedName() const;
    
    // 克隆
    NodePtr clone() const override;
    
    // 调试信息
    std::string toString() const override;
    
private:
    TemplateType templateType_;
    std::string name_;
    std::string inherits_;
    std::vector<std::pair<std::string, std::string>> parameters_; // name -> default value
    bool exported_ = false;
    std::string namespace_;
};

} // namespace CHTL

#endif // CHTL_NODE_TEMPLATENODE_H