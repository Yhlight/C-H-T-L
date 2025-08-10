#ifndef CHTL_MODULE_RESOLVER_H
#define CHTL_MODULE_RESOLVER_H

#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "Module/ModuleInfo.h"

namespace chtl {

// 模块解析器 - 负责查找和加载模块
class ModuleResolver {
private:
    std::vector<std::string> searchPaths_;      // 搜索路径列表
    std::string officialModulePath_;            // 官方模块路径
    std::string localModulePath_;               // 本地module文件夹路径
    std::string currentPath_;                   // 当前工作目录
    
    // 缓存已解析的模块
    std::unordered_map<std::string, std::shared_ptr<ModuleInfo>> moduleCache_;
    
public:
    ModuleResolver();
    
    // 初始化搜索路径
    void initialize(const std::string& workingDir = "");
    
    // 解析模块
    std::shared_ptr<ModuleInfo> resolveModule(const std::string& moduleName);
    
    // 查找模块文件
    std::string findModuleFile(const std::string& moduleName);
    
    // 搜索路径管理
    void addSearchPath(const std::string& path) {
        searchPaths_.push_back(path);
    }
    
    const std::vector<std::string>& getSearchPaths() const {
        return searchPaths_;
    }
    
    // 设置官方模块路径
    void setOfficialModulePath(const std::string& path) {
        officialModulePath_ = path;
    }
    
    // 清除缓存
    void clearCache() {
        moduleCache_.clear();
    }
    
private:
    // 搜索策略：官方模块 -> module文件夹 -> 当前目录
    std::string searchInOfficialModules(const std::string& moduleName);
    std::string searchInLocalModules(const std::string& moduleName);
    std::string searchInCurrentDirectory(const std::string& moduleName);
    
    // 将模块名转换为文件路径
    std::string moduleNameToPath(const std::string& moduleName);
    
    // 加载模块信息
    std::shared_ptr<ModuleInfo> loadModuleInfo(const std::string& modulePath);
    
    // 检查文件是否存在
    bool fileExists(const std::string& path);
    
    // 获取模块文件扩展名列表
    std::vector<std::string> getModuleExtensions() {
        return {".chtl", ".cmod", ".chtm"};
    }
};

} // namespace chtl

#endif // CHTL_MODULE_RESOLVER_H