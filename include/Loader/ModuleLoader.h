#ifndef CHTL_MODULE_LOADER_H
#define CHTL_MODULE_LOADER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace chtl {

// 前向声明
class FileLoader;
class CmodLoader;
class CmodRegistry;
class Node;

// 模块加载器 - 统一管理文件和CMOD模块的加载
class ModuleLoader {
public:
    // 加载结果
    struct LoadResult {
        bool success;
        std::string error;
        std::vector<std::string> warnings;
        std::shared_ptr<Node> rootNode;
        std::vector<std::string> loadedFiles;
        std::vector<std::string> loadedModules;
    };
    
    ModuleLoader();
    ~ModuleLoader();
    
    // 初始化
    bool initialize(const std::string& workDir = "");
    
    // 加载入口文件或模块
    LoadResult load(const std::string& target);
    
    // 加载多个目标
    LoadResult loadMultiple(const std::vector<std::string>& targets);
    
    // 加载项目（目录）
    LoadResult loadProject(const std::string& projectDir);
    
    // 解析所有已加载的内容
    bool parseAll();
    
    // 获取AST
    std::shared_ptr<Node> getAST(const std::string& target) const;
    std::shared_ptr<Node> getMergedAST() const;
    
    // 依赖管理
    bool resolveDependencies();
    std::vector<std::string> getUnresolvedDependencies() const;
    
    // 模块查询
    bool hasModule(const std::string& moduleName) const;
    std::vector<std::string> getLoadedModules() const;
    
    // 文件查询
    bool hasFile(const std::string& filePath) const;
    std::vector<std::string> getLoadedFiles() const;
    
    // 错误处理
    bool hasErrors() const;
    std::vector<std::string> getErrors() const;
    
    // 配置
    void addModulePath(const std::string& path);
    void setAutoResolveDependencies(bool autoResolve) { autoResolve_ = autoResolve; }
    void setCacheEnabled(bool enabled) { cacheEnabled_ = enabled; }
    
    // 清理
    void clear();
    void clearCache();
    
private:
    // 判断加载类型
    enum class LoadType {
        FILE,
        MODULE,
        DIRECTORY,
        UNKNOWN
    };
    
    LoadType detectLoadType(const std::string& target) const;
    
    // 合并AST
    std::shared_ptr<Node> mergeASTs(const std::vector<std::shared_ptr<Node>>& asts) const;
    
    // 加载器
    std::unique_ptr<FileLoader> fileLoader_;
    std::unique_ptr<CmodLoader> cmodLoader_;
    std::shared_ptr<CmodRegistry> registry_;
    
    // 配置
    std::string workingDirectory_;
    std::vector<std::string> modulePaths_;
    bool autoResolve_ = true;
    bool cacheEnabled_ = true;
    
    // 缓存
    std::unordered_map<std::string, std::shared_ptr<Node>> astCache_;
    
    // 状态
    std::vector<std::string> loadedTargets_;
    std::vector<std::string> errors_;
};

} // namespace chtl

#endif // CHTL_MODULE_LOADER_H