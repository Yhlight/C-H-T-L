#ifndef CHTL_IMPORT_H
#define CHTL_IMPORT_H

#include "Node/Node.h"

namespace chtl {

// Import节点 - 导入节点，用于[Import]语句
class Import : public Node {
public:
    // 导入类型枚举
    enum class ImportType {
        ALL,              // *
        HTML,             // @Html
        CSS,              // @Style
        JS,               // @JavaScript
        CHTL,             // @Chtl
        CUSTOM_ELEMENT,   // [Custom] @Element
        CUSTOM_STYLE,     // [Custom] @Style
        CUSTOM_VAR,       // [Custom] @Var
        TEMPLATE_ELEMENT, // [Template] @Element
        TEMPLATE_STYLE,   // [Template] @Style
        TEMPLATE_VAR      // [Template] @Var
    };
    
private:
    std::string filePath_;                      // 导入文件路径
    std::vector<std::string> importItems_;      // 具体导入项（from...as）
    std::unordered_map<std::string, std::string> aliases_;  // 别名映射
    bool isNamespaceImport_ = false;           // 是否为命名空间导入
    std::string targetNamespace_;               // 目标命名空间
    ImportType importType_ = ImportType::CHTL;  // 导入类型
    std::string importName_;                    // 导入项名称（对于具体的导入）
    std::string alias_;                         // 别名
    bool inline_ = false;                       // 是否内联（inline关键字）
    
public:
    Import(const std::string& path = "")
        : Node(NodeType::IMPORT, "[Import]"), filePath_(path) {}
    
    // 导入类型管理
    ImportType getType() const { return importType_; }
    void setType(ImportType type) { importType_ = type; }
    
    // 导入名称管理
    const std::string& getName() const { return importName_; }
    void setName(const std::string& name) { importName_ = name; }
    
    // 路径管理
    const std::string& getPath() const { return filePath_; }
    void setPath(const std::string& path) { filePath_ = path; }
    
    // 别名管理
    const std::string& getAlias() const { return alias_; }
    void setAlias(const std::string& alias) { alias_ = alias; }
    
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
    
    // 内联支持
    void setInline(bool inlineFlag) { inline_ = inlineFlag; }
    bool isInline() const { return inline_; }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_IMPORT_H