#include "Module/ModuleResolver.h"
#include <filesystem>
#include <fstream>
#include <algorithm>

namespace chtl {

namespace fs = std::filesystem;

ModuleResolver::ModuleResolver() {
    // 默认官方模块路径
    #ifdef _WIN32
        officialModulePath_ = "C:/chtl/modules";
    #else
        officialModulePath_ = "/usr/local/chtl/modules";
    #endif
}

void ModuleResolver::initialize(const std::string& workingDir) {
    if (!workingDir.empty()) {
        currentPath_ = workingDir;
    } else {
        currentPath_ = fs::current_path().string();
    }
    
    // 设置本地module文件夹路径
    localModulePath_ = (fs::path(currentPath_) / "module").string();
    
    // 初始化搜索路径（按优先级）
    searchPaths_.clear();
    searchPaths_.push_back(officialModulePath_);
    searchPaths_.push_back(localModulePath_);
    searchPaths_.push_back(currentPath_);
}

std::shared_ptr<ModuleInfo> ModuleResolver::resolveModule(const std::string& moduleName) {
    // 检查缓存
    auto it = moduleCache_.find(moduleName);
    if (it != moduleCache_.end()) {
        return it->second;
    }
    
    // 查找模块文件
    std::string modulePath = findModuleFile(moduleName);
    if (modulePath.empty()) {
        return nullptr;
    }
    
    // 加载模块信息
    auto moduleInfo = loadModuleInfo(modulePath);
    if (moduleInfo) {
        moduleCache_[moduleName] = moduleInfo;
    }
    
    return moduleInfo;
}

std::string ModuleResolver::findModuleFile(const std::string& moduleName) {
    // 按优先级搜索：官方模块 -> module文件夹 -> 当前目录
    
    // 1. 搜索官方模块
    std::string path = searchInOfficialModules(moduleName);
    if (!path.empty()) return path;
    
    // 2. 搜索本地module文件夹
    path = searchInLocalModules(moduleName);
    if (!path.empty()) return path;
    
    // 3. 搜索当前目录
    path = searchInCurrentDirectory(moduleName);
    if (!path.empty()) return path;
    
    return "";
}

std::string ModuleResolver::searchInOfficialModules(const std::string& moduleName) {
    std::string basePath = moduleNameToPath(moduleName);
    
    for (const auto& ext : getModuleExtensions()) {
        std::string fullPath = (fs::path(officialModulePath_) / (basePath + ext)).string();
        if (fileExists(fullPath)) {
            return fullPath;
        }
    }
    
    // 如果是目录，查找index文件
    std::string dirPath = (fs::path(officialModulePath_) / basePath).string();
    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        for (const auto& ext : getModuleExtensions()) {
            std::string indexPath = (fs::path(dirPath) / ("index" + ext)).string();
            if (fileExists(indexPath)) {
                return indexPath;
            }
        }
    }
    
    return "";
}

std::string ModuleResolver::searchInLocalModules(const std::string& moduleName) {
    std::string basePath = moduleNameToPath(moduleName);
    
    for (const auto& ext : getModuleExtensions()) {
        std::string fullPath = (fs::path(localModulePath_) / (basePath + ext)).string();
        if (fileExists(fullPath)) {
            return fullPath;
        }
    }
    
    // 如果是目录，查找index文件
    std::string dirPath = (fs::path(localModulePath_) / basePath).string();
    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        for (const auto& ext : getModuleExtensions()) {
            std::string indexPath = (fs::path(dirPath) / ("index" + ext)).string();
            if (fileExists(indexPath)) {
                return indexPath;
            }
        }
    }
    
    return "";
}

std::string ModuleResolver::searchInCurrentDirectory(const std::string& moduleName) {
    std::string basePath = moduleNameToPath(moduleName);
    
    for (const auto& ext : getModuleExtensions()) {
        std::string fullPath = (fs::path(currentPath_) / (basePath + ext)).string();
        if (fileExists(fullPath)) {
            return fullPath;
        }
    }
    
    // 如果是目录，查找index文件
    std::string dirPath = (fs::path(currentPath_) / basePath).string();
    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        for (const auto& ext : getModuleExtensions()) {
            std::string indexPath = (fs::path(dirPath) / ("index" + ext)).string();
            if (fileExists(indexPath)) {
                return indexPath;
            }
        }
    }
    
    return "";
}

std::string ModuleResolver::moduleNameToPath(const std::string& moduleName) {
    // 将模块名转换为路径
    // 例如: Chtholly.Space -> Chtholly/Space
    std::string path = moduleName;
    std::replace(path.begin(), path.end(), '.', '/');
    return path;
}

std::shared_ptr<ModuleInfo> ModuleResolver::loadModuleInfo(const std::string& modulePath) {
    // 创建基本的模块信息
    auto moduleInfo = std::make_shared<ModuleInfo>("");
    moduleInfo->setPath(modulePath);
    
    // 根据路径判断模块类型
    if (modulePath.find(officialModulePath_) == 0) {
        moduleInfo->setType(ModuleInfo::ModuleType::OFFICIAL);
    } else if (modulePath.find(localModulePath_) == 0) {
        moduleInfo->setType(ModuleInfo::ModuleType::LOCAL);
    } else {
        moduleInfo->setType(ModuleInfo::ModuleType::CURRENT);
    }
    
    // TODO: 解析模块文件中的[Info]块来获取详细信息
    // 这里暂时返回基本信息
    
    return moduleInfo;
}

bool ModuleResolver::fileExists(const std::string& path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

} // namespace chtl