#ifndef CHTL_NAMESPACE_H
#define CHTL_NAMESPACE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <set>
#include "CHTLContext.h"

namespace chtl {

// 前向声明
class CHTLGenerator;
class TemplateManager;
class CustomManager;

// 命名空间中的项目类型
enum class NamespaceItemType {
    CUSTOM_ELEMENT,
    CUSTOM_STYLE,
    CUSTOM_VAR,
    TEMPLATE_ELEMENT,
    TEMPLATE_STYLE,
    TEMPLATE_VAR,
    NESTED_NAMESPACE
};

// 命名空间项目
struct NamespaceItem {
    NamespaceItemType type;
    std::string name;
    std::string fullPath;  // 完整路径（包含命名空间）
    std::shared_ptr<void> definition;  // 实际定义的指针
    std::string sourceFile;  // 来源文件
    int lineNumber;  // 定义所在行号
};

// 命名空间定义
class NamespaceDefinition : public std::enable_shared_from_this<NamespaceDefinition> {
private:
    std::string name;
    std::string fullPath;  // 完整命名空间路径
    std::weak_ptr<NamespaceDefinition> parent;  // 父命名空间
    
    // 子命名空间
    std::unordered_map<std::string, std::shared_ptr<NamespaceDefinition>> childNamespaces;
    
    // 命名空间中的项目
    std::unordered_map<std::string, std::vector<NamespaceItem>> items;
    
    // 源信息
    std::string sourceFile;
    int startLine;
    int endLine;
    
public:
    NamespaceDefinition(const std::string& name, const std::string& fullPath = "")
        : name(name), fullPath(fullPath.empty() ? name : fullPath), 
          startLine(0), endLine(0) {}
    
    // 获取器
    const std::string& getName() const { return name; }
    const std::string& getFullPath() const { return fullPath; }
    std::shared_ptr<NamespaceDefinition> getParent() const { return parent.lock(); }
    
    // 设置父命名空间
    void setParent(std::shared_ptr<NamespaceDefinition> p) { parent = p; }
    
    // 子命名空间管理
    std::shared_ptr<NamespaceDefinition> addChildNamespace(const std::string& childName);
    std::shared_ptr<NamespaceDefinition> getChildNamespace(const std::string& childName) const;
    std::vector<std::string> getChildNamespaceNames() const;
    
    // 项目管理
    void addItem(const NamespaceItem& item);
    std::vector<NamespaceItem> getItems(const std::string& itemName) const;
    std::vector<NamespaceItem> getAllItems() const;
    bool hasItem(const std::string& itemName) const;
    
    // 查找项目（支持特定类型）
    std::shared_ptr<void> findItem(const std::string& itemName, NamespaceItemType type) const;
    
    // 合并另一个命名空间
    bool merge(const NamespaceDefinition& other, std::vector<std::string>& conflicts);
    
    // 源信息
    void setSourceInfo(const std::string& file, int start, int end) {
        sourceFile = file;
        startLine = start;
        endLine = end;
    }
};

// 命名空间管理器
class NamespaceManager {
private:
    // 根命名空间（全局）
    std::shared_ptr<NamespaceDefinition> globalNamespace;
    
    // 所有命名空间的快速查找表（fullPath -> NamespaceDefinition）
    std::unordered_map<std::string, std::shared_ptr<NamespaceDefinition>> namespaceIndex;
    
    // 当前活动的命名空间栈
    std::vector<std::shared_ptr<NamespaceDefinition>> namespaceStack;
    
    // 文件默认命名空间映射
    std::unordered_map<std::string, std::string> fileDefaultNamespaces;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
    // 关联的管理器
    std::shared_ptr<TemplateManager> templateManager;
    std::shared_ptr<CustomManager> customManager;
    
public:
    NamespaceManager(std::shared_ptr<CHTLContext> ctx);
    
    // 设置管理器
    void setTemplateManager(std::shared_ptr<TemplateManager> mgr) { templateManager = mgr; }
    void setCustomManager(std::shared_ptr<CustomManager> mgr) { customManager = mgr; }
    
    // 命名空间操作
    void beginNamespace(const std::string& name);
    void endNamespace();
    std::shared_ptr<NamespaceDefinition> getCurrentNamespace() const;
    
    // 创建或获取命名空间
    std::shared_ptr<NamespaceDefinition> getOrCreateNamespace(const std::string& path);
    
    // 查找命名空间
    std::shared_ptr<NamespaceDefinition> findNamespace(const std::string& path) const;
    
    // 注册项目到当前命名空间
    void registerItem(const std::string& itemName, NamespaceItemType type, 
                     std::shared_ptr<void> definition);
    
    // 从指定命名空间查找项目
    std::shared_ptr<void> findItemInNamespace(const std::string& itemName, 
                                              const std::string& namespacePath,
                                              NamespaceItemType type) const;
    
    // 设置文件默认命名空间
    void setFileDefaultNamespace(const std::string& filePath, const std::string& namespaceName);
    std::string getFileDefaultNamespace(const std::string& filePath) const;
    
    // 合并命名空间
    bool mergeNamespaces(const std::string& targetPath, const std::string& sourcePath);
    
    // 冲突检测
    std::vector<std::string> detectConflicts(const std::string& namespacePath) const;
    
    // 清理
    void clear();
};

// 命名空间解析器
class NamespaceResolver {
private:
    const NamespaceManager& manager;
    
public:
    NamespaceResolver(const NamespaceManager& mgr) : manager(mgr) {}
    
    // 解析带命名空间的引用
    struct NamespaceReference {
        std::string itemName;
        std::string namespacePath;
        bool hasExplicitNamespace;
    };
    
    // 解析 "ItemName from namespace.path" 格式
    NamespaceReference parseReference(const std::string& reference);
    
    // 解析命名空间路径（支持嵌套）
    std::vector<std::string> parseNamespacePath(const std::string& path);
    
    // 构建完整的命名空间路径
    std::string buildFullPath(const std::vector<std::string>& components);
    
    // 查找项目（考虑当前命名空间上下文）
    std::shared_ptr<void> resolveItem(const std::string& itemName, 
                                      NamespaceItemType type,
                                      const std::string& fromNamespace = "");
};

// 命名空间处理器
class NamespaceProcessor {
private:
    NamespaceManager& manager;
    CHTLGenerator& generator;
    
public:
    NamespaceProcessor(NamespaceManager& mgr, CHTLGenerator& gen)
        : manager(mgr), generator(gen) {}
    
    // 处理命名空间声明
    void processNamespaceDeclaration(const std::string& declaration);
    
    // 处理带命名空间的使用语句
    bool processNamespacedUse(const std::string& useStatement, NamespaceItemType expectedType);
    
    // 解析命名空间块
    struct NamespaceBlock {
        std::string name;
        bool hasBody;  // 是否有花括号体
        std::vector<std::string> nestedDeclarations;  // 嵌套的命名空间声明
    };
    
    NamespaceBlock parseNamespaceBlock(const std::string& declaration);
};

// 命名空间合并策略
class NamespaceMerger {
public:
    // 合并选项
    struct MergeOptions {
        bool allowDuplicates = false;  // 是否允许重复项
        bool overwriteExisting = false;  // 是否覆盖已存在的项
        bool deepMerge = true;  // 是否深度合并子命名空间
    };
    
    // 合并两个命名空间
    static bool merge(NamespaceDefinition& target, 
                     const NamespaceDefinition& source,
                     const MergeOptions& options,
                     std::vector<std::string>& conflicts);
    
    // 检测潜在冲突
    static std::vector<std::string> detectPotentialConflicts(
        const NamespaceDefinition& ns1,
        const NamespaceDefinition& ns2);
    
    // 解决冲突的策略
    enum class ConflictResolution {
        KEEP_FIRST,     // 保留第一个
        KEEP_SECOND,    // 保留第二个
        KEEP_BOTH,      // 保留两个（需要重命名）
        ERROR           // 报错
    };
    
    static ConflictResolution resolveConflict(const NamespaceItem& item1,
                                             const NamespaceItem& item2);
};

// 辅助函数
namespace NamespaceHelper {
    // 验证命名空间名称
    bool isValidNamespaceName(const std::string& name);
    
    // 分割命名空间路径
    std::vector<std::string> splitPath(const std::string& path);
    
    // 连接命名空间路径
    std::string joinPath(const std::vector<std::string>& components);
    
    // 获取项目类型的字符串表示
    std::string itemTypeToString(NamespaceItemType type);
    
    // 从文件路径生成默认命名空间名
    std::string generateDefaultNamespace(const std::string& filePath);
    
    // 检查是否是保留的命名空间名
    bool isReservedNamespace(const std::string& name);
}

} // namespace chtl

#endif // CHTL_NAMESPACE_H