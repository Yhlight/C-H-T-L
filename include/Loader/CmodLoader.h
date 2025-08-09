#ifndef CHTL_CMOD_LOADER_H
#define CHTL_CMOD_LOADER_H

#include "CmodSystem/CmodInfo.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace chtl {

// 前向声明
class CmodRegistry;
class BasicParser;
class Node;

// CMOD加载器 - 加载和管理CMOD模块
class CmodLoader {
public:
    // 加载结果
    struct LoadResult {
        bool success;
        std::string error;
        std::vector<std::string> warnings;
        std::shared_ptr<Node> rootNode;     // 解析后的根节点
        std::unique_ptr<CmodInfo> info;     // 模块信息
    };
    
    // 加载选项
    struct LoadOptions {
        bool validateBeforeLoad = true;
        bool loadDependencies = true;
        bool cacheLoadedModules = true;
        bool resolveSymlinks = false;
        int maxDepth = 10;
        
        LoadOptions() = default;
    };
    
    CmodLoader();
    ~CmodLoader();
    
    // 初始化加载器
    bool initialize(std::shared_ptr<CmodRegistry> registry = nullptr);
    
    // 加载CMOD模块
    LoadResult loadModule(const std::string& moduleName, 
                         const LoadOptions& options = {});
    
    // 从路径加载模块
    LoadResult loadFromPath(const std::string& modulePath,
                           const LoadOptions& options = {});
    
    // 从.cmod文件加载
    LoadResult loadFromPackage(const std::string& cmodFilePath,
                              const LoadOptions& options = {});
    
    // 加载子模块
    LoadResult loadSubmodule(const std::string& parentModule,
                            const std::string& submoduleName,
                            const LoadOptions& options = {});
    
    // 检查模块是否已加载
    bool isModuleLoaded(const std::string& moduleName) const;
    
    // 获取已加载的模块
    std::shared_ptr<Node> getLoadedModule(const std::string& moduleName) const;
    
    // 获取模块信息
    const CmodInfo* getModuleInfo(const std::string& moduleName) const;
    
    // 卸载模块
    bool unloadModule(const std::string& moduleName);
    
    // 重新加载模块
    LoadResult reloadModule(const std::string& moduleName,
                           const LoadOptions& options = {});
    
    // 获取所有已加载的模块
    std::vector<std::string> getLoadedModules() const;
    
    // 解析导入语句 (Import @Chtl from 模块名)
    std::string resolveImport(const std::string& importStatement) const;
    
    // 查找模块
    std::string findModule(const std::string& moduleName) const;
    
    // 清理缓存
    void clearCache();
    
    // 设置模块搜索路径
    void addSearchPath(const std::string& path);
    void removeSearchPath(const std::string& path);
    std::vector<std::string> getSearchPaths() const;
    
private:
    // 已加载模块的缓存
    struct LoadedModule {
        std::shared_ptr<Node> rootNode;
        std::unique_ptr<CmodInfo> info;
        std::string loadPath;
        std::vector<std::string> dependencies;
    };
    
    // 模块缓存
    std::unordered_map<std::string, LoadedModule> loadedModules_;
    
    // 模块注册表
    std::shared_ptr<CmodRegistry> registry_;
    
    // 搜索路径
    std::vector<std::string> searchPaths_;
    
    // 解析器
    std::unique_ptr<BasicParser> parser_;
    
    // 加载实现
    LoadResult loadModuleInternal(const std::string& modulePath,
                                 const std::string& moduleName,
                                 const LoadOptions& options);
    
    // 加载依赖
    bool loadDependencies(const std::string& dependencies,
                         const LoadOptions& options);
    
    // 解析模块文件
    std::shared_ptr<Node> parseModuleFile(const std::string& filePath);
    
    // 合并模块（用于处理多个文件的模块）
    std::shared_ptr<Node> mergeModuleFiles(const std::vector<std::string>& filePaths);
    
    // 查找模块路径
    std::string findModulePath(const std::string& moduleName) const;
    
    // 在目录中查找模块
    std::string findModuleInDirectory(const std::string& dir, 
                                     const std::string& moduleName) const;
    
    // 检查循环依赖
    bool checkCircularDependency(const std::string& moduleName,
                                std::vector<std::string>& loadingStack) const;
    
    // 验证模块
    bool validateModule(const CmodInfo& info) const;
    
    // 从配置的默认路径获取
    static std::vector<std::string> getDefaultSearchPaths();
    
    // 解析依赖字符串
    std::vector<std::string> parseDependencies(const std::string& depStr) const;
};

} // namespace chtl

#endif // CHTL_CMOD_LOADER_H