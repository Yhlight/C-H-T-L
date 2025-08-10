#ifndef CHTL_NAMESPACE_MANAGER_H
#define CHTL_NAMESPACE_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <set>
#include "Node/Node.h"
#include "Node/Namespace.h"

namespace chtl {

// 命名空间成员信息
struct NamespaceMember {
    std::string name;                    // 成员名称
    NodeType type;                       // 成员类型
    std::shared_ptr<Node> node;          // 成员节点
    std::string fullPath;                // 完整路径（namespace.member）
};

// 命名空间详细信息
struct NamespaceDetail {
    std::string name;                    // 命名空间名称
    std::string parentPath;              // 父命名空间路径
    std::string fullPath;                // 完整路径
    std::weak_ptr<Namespace> node;       // 命名空间节点
    
    // 成员
    std::unordered_map<std::string, NamespaceMember> members;
    
    // 子命名空间
    std::unordered_map<std::string, std::shared_ptr<NamespaceDetail>> children;
    
    // 合并来源（如果是合并的命名空间）
    std::vector<std::string> mergedFrom;
};

// 命名空间冲突信息
struct NamespaceConflict {
    std::string memberName;              // 冲突的成员名
    std::string namespacePath;           // 命名空间路径
    std::vector<std::string> sources;    // 冲突来源
    std::string description;             // 冲突描述
};

// 命名空间管理器
class NamespaceManager {
public:
    NamespaceManager();
    ~NamespaceManager() = default;
    
    // 注册命名空间
    bool registerNamespace(std::shared_ptr<Namespace> ns, const std::string& parentPath = "");
    
    // 注册成员到命名空间
    bool registerMember(const std::string& namespacePath, 
                       const std::string& memberName,
                       NodeType type,
                       std::shared_ptr<Node> node);
    
    // 查找命名空间
    std::shared_ptr<NamespaceDetail> findNamespace(const std::string& path);
    
    // 查找成员
    std::shared_ptr<Node> findMember(const std::string& namespacePath, 
                                     const std::string& memberName);
    
    // 解析完整路径（如 space.room2.Box）
    std::pair<std::string, std::string> parseMemberPath(const std::string& fullPath);
    
    // 合并同名命名空间
    bool mergeNamespace(const std::string& path, std::shared_ptr<Namespace> ns);
    
    // 检测成员冲突
    std::vector<NamespaceConflict> detectConflicts();
    
    // 获取命名空间树
    std::shared_ptr<NamespaceDetail> getRootNamespace() { return root_; }
    
    // 设置当前命名空间（用于解析时的上下文）
    void setCurrentNamespace(const std::string& path) { currentNamespace_ = path; }
    std::string getCurrentNamespace() const { return currentNamespace_; }
    
    // 解析相对路径
    std::string resolveRelativePath(const std::string& relativePath);
    
    // 打印命名空间树（调试用）
    void printNamespaceTree() const;
    
private:
    // 辅助函数
    std::shared_ptr<NamespaceDetail> createNamespaceInfo(const std::string& name,
                                                         const std::string& parentPath);
    
    std::shared_ptr<NamespaceDetail> findOrCreateNamespace(const std::string& path);
    
    std::vector<std::string> splitPath(const std::string& path);
    std::string joinPath(const std::vector<std::string>& parts);
    
    void printNamespaceInfo(std::shared_ptr<NamespaceDetail> info, int depth) const;
    
private:
    // 根命名空间（全局）
    std::shared_ptr<NamespaceDetail> root_;
    
    // 当前命名空间路径
    std::string currentNamespace_;
    
    // 快速查找缓存
    std::unordered_map<std::string, std::shared_ptr<NamespaceDetail>> namespaceCache_;
};

} // namespace chtl

#endif // CHTL_NAMESPACE_MANAGER_H