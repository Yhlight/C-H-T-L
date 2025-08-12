#ifndef CHTL_NODE_CUSTOMNODE_H
#define CHTL_NODE_CUSTOMNODE_H

#include "Node.h"
#include <vector>
#include <unordered_map>

namespace CHTL {

/**
 * 自定义节点 - 表示@Style, @Element, @Var自定义
 */
class CustomNode : public Node {
public:
    enum class CustomType {
        STYLE,
        ELEMENT,
        VAR
    };
    
    enum class ElementOperation {
        NONE,
        INDEX,      // 通过索引获取元素
        INSERT,     // 插入元素
        DELETE      // 删除元素
    };
    
    CustomNode(CustomType type, const std::string& name);
    ~CustomNode() = default;
    
    // 实现visitor模式
    void accept(NodeVisitor* visitor) override;
    
    // 自定义类型
    CustomType getCustomType() const { return customType_; }
    
    // 自定义名称
    const std::string& getName() const { return name_; }
    
    // 特化（使用的模板名）
    void setSpecialization(const std::string& templateName) { specialization_ = templateName; }
    const std::string& getSpecialization() const { return specialization_; }
    bool hasSpecialization() const { return !specialization_.empty(); }
    
    // 元素操作（用于@Element自定义）
    void setElementOperation(ElementOperation op) { elementOp_ = op; }
    ElementOperation getElementOperation() const { return elementOp_; }
    
    // 操作参数
    void setOperationIndex(int index) { opIndex_ = index; }
    int getOperationIndex() const { return opIndex_; }
    
    // 无值样式组（用于@Style自定义）
    void addNoValueStyle(const std::string& property);
    const std::vector<std::string>& getNoValueStyles() const { return noValueStyles_; }
    
    // 参数映射（用于模板特化）
    void setParameter(const std::string& name, const std::string& value);
    const std::unordered_map<std::string, std::string>& getParameters() const { return parameters_; }
    
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
    CustomType customType_;
    std::string name_;
    std::string specialization_;
    ElementOperation elementOp_ = ElementOperation::NONE;
    int opIndex_ = -1;
    std::vector<std::string> noValueStyles_;
    std::unordered_map<std::string, std::string> parameters_;
    bool exported_ = false;
    std::string namespace_;
};

} // namespace CHTL

#endif // CHTL_NODE_CUSTOMNODE_H