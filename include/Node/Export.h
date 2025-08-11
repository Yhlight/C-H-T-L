#ifndef CHTL_EXPORT_H
#define CHTL_EXPORT_H

#include "Node/Node.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace chtl {

// Export节点 - 模块导出节点，用于[Export]语句
class Export : public Node {
public:
    // 导出项类型
    enum class ExportType {
        ELEMENT,    // @Element
        STYLE,      // @Style
        VAR,        // @Var
        NAMESPACE,  // 命名空间
        ALL         // * (导出所有)
    };
    
    // 导出项结构
    struct ExportItem {
        ExportType type;
        std::string name;
        std::string alias;  // 导出别名（可选）
        
        ExportItem(ExportType t, const std::string& n, const std::string& a = "") 
            : type(t), name(n), alias(a) {}
    };
    
private:
    std::vector<ExportItem> exportItems_;
    std::string fromNamespace_;  // 从哪个命名空间导出（可选）
    
public:
    Export() : Node(NodeType::EXPORT, "[Export]") {}
    
    // 导出项管理
    void addExportItem(ExportType type, const std::string& name, const std::string& alias = "") {
        exportItems_.emplace_back(type, name, alias);
    }
    
    void addExportItem(const ExportItem& item) {
        exportItems_.push_back(item);
    }
    
    const std::vector<ExportItem>& getExportItems() const { 
        return exportItems_; 
    }
    
    // 命名空间管理
    void setFromNamespace(const std::string& ns) { 
        fromNamespace_ = ns; 
    }
    
    const std::string& getFromNamespace() const { 
        return fromNamespace_; 
    }
    
    // 检查是否导出所有
    bool isExportAll() const {
        return exportItems_.size() == 1 && 
               exportItems_[0].type == ExportType::ALL &&
               exportItems_[0].name == "*";
    }
    
    // 获取特定类型的导出项
    std::vector<ExportItem> getExportsByType(ExportType type) const {
        std::vector<ExportItem> result;
        for (const auto& item : exportItems_) {
            if (item.type == type) {
                result.push_back(item);
            }
        }
        return result;
    }
    
    // 覆盖基类方法
    std::shared_ptr<Node> clone(bool deep = true) const override;
    std::string toString() const override;
    void accept(Visitor* visitor) override;
};

} // namespace chtl

#endif // CHTL_EXPORT_H