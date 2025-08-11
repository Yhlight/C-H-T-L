#ifndef CHTL_IMPORT_MANAGER_H
#define CHTL_IMPORT_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include <chrono>
#include "Loader/DependencyGraph.h"
#include "Loader/ImportResolver.h"
#include "Node/Node.h"
#include "Context/BasicContext.h"

namespace chtl {

// 导入配置
struct ImportConfig {
    bool allowCircularDependencies = false;     // 是否允许循环依赖
    bool enableCache = true;                    // 是否启用缓存
    bool detectUnusedImports = true;           // 是否检测未使用的导入
    bool autoResolveConflicts = true;          // 是否自动解决冲突
    size_t maxImportDepth = 100;               // 最大导入深度
    std::vector<std::string> searchPaths;      // 模块搜索路径
};

// 导入结果
struct ImportResult {
    bool success = false;
    std::shared_ptr<Node> ast;                 // 导入的AST
    std::string resolvedPath;                  // 解析后的路径
    std::vector<std::string> errors;           // 错误信息
    std::vector<std::string> warnings;         // 警告信息
    std::vector<CircularDependency> circularDeps; // 检测到的循环依赖
};

// 导入缓存项
struct ImportCacheEntry {
    std::shared_ptr<Node> ast;
    std::string resolvedPath;
    std::chrono::system_clock::time_point timestamp;
    std::vector<std::string> dependencies;
};

// 导入管理器
class ImportManager {
public:
    ImportManager();
    ~ImportManager() = default;
    
    // 设置配置
    void setConfig(const ImportConfig& config) { config_ = config; }
    const ImportConfig& getConfig() const { return config_; }
    
    // 设置上下文
    void setContext(std::shared_ptr<BasicContext> context) { context_ = context; }
    
    // 导入模块
    ImportResult importModule(const std::string& modulePath,
                             const std::string& fromPath = "");
    
    // 批量导入
    std::vector<ImportResult> importModules(const std::vector<std::string>& modules,
                                           const std::string& fromPath = "");
    
    // 检查循环依赖
    std::vector<CircularDependency> checkCircularDependencies();
    
    // 获取未使用的导入
    std::vector<std::string> getUnusedImports();
    
    // 清除缓存
    void clearCache();
    void clearCacheForModule(const std::string& modulePath);
    
    // 获取依赖图
    const DependencyGraph& getDependencyGraph() const { return dependencyGraph_; }
    
    // 解析模块路径
    std::string resolveModulePath(const std::string& modulePath,
                                 const std::string& fromPath = "");
    
    // 注册模块加载器
    using ModuleLoader = std::function<std::shared_ptr<Node>(const std::string&)>;
    void registerLoader(const std::string& extension, ModuleLoader loader);
    
    // 注册模块变换器（用于处理导入后的转换）
    using ModuleTransformer = std::function<void(std::shared_ptr<Node>&, const std::string&)>;
    void registerTransformer(ModuleTransformer transformer);
    
    // 获取导入统计
    struct ImportStats {
        size_t totalImports = 0;
        size_t cachedImports = 0;
        size_t circularImports = 0;
        size_t failedImports = 0;
        std::chrono::milliseconds totalTime{0};
    };
    ImportStats getStats() const { return stats_; }
    
private:
    // 内部导入实现
    ImportResult importModuleInternal(const std::string& modulePath,
                                     const std::string& fromPath,
                                     std::vector<std::string>& importStack);
    
    // 从文件加载模块
    std::shared_ptr<Node> loadModuleFromFile(const std::string& path);
    
    // 提取模块依赖
    std::vector<std::string> extractDependencies(std::shared_ptr<Node> ast);
    
    // 处理循环依赖
    ImportResult handleCircularDependency(const std::string& modulePath,
                                         const CircularDependency& cycle);
    
    // 合并导入的符号
    void mergeImportedSymbols(std::shared_ptr<Node> targetAst,
                             std::shared_ptr<Node> importedAst,
                             const std::string& modulePath);
    
    // 检测符号冲突
    std::vector<std::string> detectSymbolConflicts(std::shared_ptr<Node> ast1,
                                                   std::shared_ptr<Node> ast2);
    
    // 应用变换器
    void applyTransformers(std::shared_ptr<Node>& ast, const std::string& modulePath);
    
    // 更新使用信息
    void updateUsageInfo(const std::string& modulePath);
    
private:
    ImportConfig config_;
    std::shared_ptr<BasicContext> context_;
    DependencyGraph dependencyGraph_;
    std::unique_ptr<ImportResolver> resolver_;
    
    // 缓存
    std::unordered_map<std::string, ImportCacheEntry> cache_;
    
    // 模块加载器
    std::unordered_map<std::string, ModuleLoader> loaders_;
    
    // 模块变换器
    std::vector<ModuleTransformer> transformers_;
    
    // 使用信息
    std::unordered_map<std::string, std::unordered_set<std::string>> usageInfo_;
    
    // 统计信息
    mutable ImportStats stats_;
    
    // 当前导入栈（用于检测循环）
    std::vector<std::string> currentImportStack_;
};

} // namespace chtl

#endif // CHTL_IMPORT_MANAGER_H