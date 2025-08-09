#ifndef CHTL_NAMESPACE_H
#define CHTL_NAMESPACE_H

#include "node/Node.h"

namespace chtl {

// Namespace节点 - 命名空间节点
class Namespace : public Node {
private:
    std::string namespaceName_;
    std::vector<std::string> namespacePath_;    // 嵌套命名空间路径
    bool isExport_ = false;                     // 是否导出
    
public:
    Namespace(const std::string& name)
        : Node(NodeType::NAMESPACE, "[Namespace]"), namespaceName_(name) {}
    
    // 命名空间名称
    const std::string& getNamespaceName() const { return namespaceName_; }
    void setNamespaceName(const std::string& name) { namespaceName_ = name; }
    
    // 命名空间路径（支持嵌套）
    void addToPath(const std::string& name) { namespacePath_.push_back(name); }
    const std::vector<std::string>& getNamespacePath() const { return namespacePath_; }
    void setNamespacePath(const std::vector<std::string>& path) { namespacePath_ = path; }
    std::string getFullPath() const;
    
    // 导出标记
    void setExport(bool export_) { isExport_ = export_; }
    bool isExport() const { return isExport_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_NAMESPACE_H