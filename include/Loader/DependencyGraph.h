#ifndef CHTL_DEPENDENCY_GRAPH_H
#define CHTL_DEPENDENCY_GRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

namespace chtl {

// 依赖信息
struct DependencyInfo {
    std::string path;                    // 模块路径
    std::string resolvedPath;            // 解析后的绝对路径
    std::vector<std::string> imports;    // 该模块导入的其他模块
    bool isProcessing = false;           // 是否正在处理（用于检测循环）
    bool isProcessed = false;            // 是否已处理完成
    std::weak_ptr<void> cachedModule;    // 缓存的模块对象
};

// 循环依赖信息
struct CircularDependency {
    std::vector<std::string> cycle;      // 形成循环的模块路径
    std::string description;             // 循环描述
};

// 依赖图类 - 管理模块间的依赖关系
class DependencyGraph {
public:
    DependencyGraph();
    ~DependencyGraph() = default;
    
    // 添加模块及其依赖
    void addModule(const std::string& modulePath, 
                   const std::string& resolvedPath,
                   const std::vector<std::string>& dependencies);
    
    // 检查是否存在循环依赖
    bool hasCircularDependency(const std::string& modulePath);
    
    // 获取所有循环依赖
    std::vector<CircularDependency> detectAllCircularDependencies();
    
    // 检查模块是否已导入
    bool isModuleImported(const std::string& modulePath) const;
    
    // 获取模块的缓存
    std::weak_ptr<void> getModuleCache(const std::string& modulePath) const;
    
    // 设置模块缓存
    void setModuleCache(const std::string& modulePath, std::weak_ptr<void> cache);
    
    // 获取拓扑排序的模块列表（依赖在前）
    std::vector<std::string> getTopologicalOrder();
    
    // 清除所有依赖信息
    void clear();
    
    // 获取模块的所有依赖（递归）
    std::unordered_set<std::string> getAllDependencies(const std::string& modulePath);
    
    // 获取依赖于指定模块的所有模块
    std::vector<std::string> getDependents(const std::string& modulePath);
    
    // 打印依赖图（调试用）
    void printGraph() const;
    
private:
    // 深度优先搜索检测循环
    bool detectCycleDFS(const std::string& module,
                        std::unordered_set<std::string>& visited,
                        std::unordered_set<std::string>& recursionStack,
                        std::vector<std::string>& currentPath,
                        std::vector<CircularDependency>& cycles);
    
    // 拓扑排序的DFS辅助函数
    void topologicalSortDFS(const std::string& module,
                           std::unordered_set<std::string>& visited,
                           std::vector<std::string>& result);
    
    // 构建反向依赖图
    void buildReverseDependencies();
    
private:
    // 模块依赖信息映射
    std::unordered_map<std::string, DependencyInfo> modules_;
    
    // 反向依赖图（模块 -> 依赖它的模块列表）
    std::unordered_map<std::string, std::vector<std::string>> reverseDependencies_;
    
    // 是否需要重建反向依赖图
    mutable bool needRebuildReverse_ = true;
};

} // namespace chtl

#endif // CHTL_DEPENDENCY_GRAPH_H