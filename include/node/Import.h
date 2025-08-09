#ifndef CHTL_IMPORT_H
#define CHTL_IMPORT_H

#include "node/Node.h"

namespace chtl {

// Import节点 - 导入节点，用于[Import]语句
class Import : public Node {
private:
    std::string filePath_;                      // 导入文件路径
    std::vector<std::string> importItems_;      // 具体导入项（from...as）
    std::unordered_map<std::string, std::string> aliases_;  // 别名映射
    bool isNamespaceImport_ = false;           // 是否为命名空间导入
    std::string targetNamespace_;               // 目标命名空间
    
public:
    Import(const std::string& path = "")
        : Node(NodeType::IMPORT, "[Import]"), filePath_(path) {}
    
    // 文件路径管理
    const std::string& getFilePath() const { return filePath_; }
    void setFilePath(const std::string& path) { filePath_ = path; }
    
    // 导入项管理
    void addImportItem(const std::string& item, const std::string& alias = "") {
        importItems_.push_back(item);
        if (!alias.empty()) {
            aliases_[item] = alias;
        }
    }
    const std::vector<std::string>& getImportItems() const { return importItems_; }
    std::string getAlias(const std::string& item) const;
    bool hasAlias(const std::string& item) const { return aliases_.find(item) != aliases_.end(); }
    const std::unordered_map<std::string, std::string>& getAliases() const { return aliases_; }
    
    // 命名空间导入
    void setNamespaceImport(bool isNamespace) { isNamespaceImport_ = isNamespace; }
    bool isNamespaceImport() const { return isNamespaceImport_; }
    
    void setTargetNamespace(const std::string& ns) { targetNamespace_ = ns; }
    const std::string& getTargetNamespace() const { return targetNamespace_; }
    
    // 检查是否导入所有（*）
    bool isImportAll() const { 
        return importItems_.size() == 1 && importItems_[0] == "*"; 
    }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_IMPORT_H