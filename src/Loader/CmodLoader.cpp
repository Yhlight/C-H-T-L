#include "Loader/CmodLoader.h"
#include "CmodSystem/CmodRegistry.h"
#include "CmodSystem/CmodExtractor.h"
#include "CmodSystem/CmodValidator.h"
#include "Node/Node.h"
#include <filesystem>

namespace chtl {

namespace fs = std::filesystem;

CmodLoader::CmodLoader() = default;
CmodLoader::~CmodLoader() = default;

bool CmodLoader::initialize(std::shared_ptr<CmodRegistry> registry) {
    registry_ = registry;
    
    // 添加默认搜索路径
    searchPaths_ = getDefaultSearchPaths();
    
    return true;
}

CmodLoader::LoadResult CmodLoader::loadModule(const std::string& moduleName, 
                                             const LoadOptions& options) {
    LoadResult result{false, "", {}, nullptr, nullptr};
    
    // 检查是否已加载
    if (isModuleLoaded(moduleName)) {
        result.success = true;
        result.rootNode = getLoadedModule(moduleName);
        return result;
    }
    
    // 查找模块路径
    std::string modulePath = findModulePath(moduleName);
    if (modulePath.empty()) {
        result.error = "Module not found: " + moduleName;
        return result;
    }
    
    // 从路径加载
    return loadFromPath(modulePath, options);
}

CmodLoader::LoadResult CmodLoader::loadFromPath(const std::string& modulePath,
                                               const LoadOptions& options) {
    LoadResult result{false, "", {}, nullptr, nullptr};
    
    // 验证模块
    if (options.validateBeforeLoad) {
        CmodValidator validator;
        auto validationResult = validator.validateModule(modulePath);
        if (!validationResult.isValid) {
            result.error = "Module validation failed";
            result.warnings = validationResult.errors;
            return result;
        }
        result.warnings = validationResult.warnings;
    }
    
    // 提取模块信息
    CmodExtractor extractor;
    auto info = extractor.extractFromDirectory(modulePath);
    if (!info) {
        result.error = "Failed to extract module information";
        return result;
    }
    
    result.info = std::move(info);
    
    // TODO: 实际解析模块文件并创建AST
    result.rootNode = std::make_shared<Node>(NodeType::DOCUMENT);
    
    // 缓存已加载的模块
    if (options.cacheLoadedModules) {
        LoadedModule module;
        module.rootNode = result.rootNode;
        module.info = std::make_unique<CmodInfo>(*result.info);
        module.loadPath = modulePath;
        module.dependencies = parseDependencies(result.info->dependencies);
        
        loadedModules_[result.info->name] = std::move(module);
    }
    
    // 加载依赖
    if (options.loadDependencies && !result.info->dependencies.empty()) {
        loadDependencies(result.info->dependencies, options);
    }
    
    result.success = true;
    return result;
}

CmodLoader::LoadResult CmodLoader::loadFromPackage(const std::string& cmodFilePath,
                                                  const LoadOptions& options) {
    LoadResult result{false, "", {}, nullptr, nullptr};
    
    // TODO: 实现从.cmod包文件加载
    result.error = "Loading from package not yet implemented";
    
    return result;
}

CmodLoader::LoadResult CmodLoader::loadSubmodule(const std::string& parentModule,
                                                const std::string& submoduleName,
                                                const LoadOptions& options) {
    std::string fullModuleName = parentModule + "." + submoduleName;
    return loadModule(fullModuleName, options);
}

bool CmodLoader::isModuleLoaded(const std::string& moduleName) const {
    return loadedModules_.find(moduleName) != loadedModules_.end();
}

std::shared_ptr<Node> CmodLoader::getLoadedModule(const std::string& moduleName) const {
    auto it = loadedModules_.find(moduleName);
    if (it != loadedModules_.end()) {
        return it->second.rootNode;
    }
    return nullptr;
}

const CmodInfo* CmodLoader::getModuleInfo(const std::string& moduleName) const {
    auto it = loadedModules_.find(moduleName);
    if (it != loadedModules_.end()) {
        return it->second.info.get();
    }
    return nullptr;
}

bool CmodLoader::unloadModule(const std::string& moduleName) {
    return loadedModules_.erase(moduleName) > 0;
}

CmodLoader::LoadResult CmodLoader::reloadModule(const std::string& moduleName,
                                               const LoadOptions& options) {
    unloadModule(moduleName);
    return loadModule(moduleName, options);
}

std::vector<std::string> CmodLoader::getLoadedModules() const {
    std::vector<std::string> modules;
    modules.reserve(loadedModules_.size());
    
    for (const auto& [name, module] : loadedModules_) {
        modules.push_back(name);
    }
    
    return modules;
}

std::string CmodLoader::resolveImport(const std::string& importStatement) const {
    // 解析Import语句，提取模块名
    // 格式: [Import] @Chtl from ModuleName
    size_t fromPos = importStatement.find("from");
    if (fromPos != std::string::npos) {
        std::string moduleName = importStatement.substr(fromPos + 4);
        // 去除空格
        moduleName.erase(0, moduleName.find_first_not_of(" \t"));
        moduleName.erase(moduleName.find_last_not_of(" \t;") + 1);
        return moduleName;
    }
    
    return "";
}

std::string CmodLoader::findModule(const std::string& moduleName) const {
    return findModulePath(moduleName);
}

void CmodLoader::clearCache() {
    loadedModules_.clear();
}

void CmodLoader::addSearchPath(const std::string& path) {
    searchPaths_.push_back(path);
}

void CmodLoader::removeSearchPath(const std::string& path) {
    searchPaths_.erase(
        std::remove(searchPaths_.begin(), searchPaths_.end(), path),
        searchPaths_.end()
    );
}

std::vector<std::string> CmodLoader::getSearchPaths() const {
    return searchPaths_;
}

// 私有方法实现
CmodLoader::LoadResult CmodLoader::loadModuleInternal(const std::string& modulePath,
                                                     const std::string& moduleName,
                                                     const LoadOptions& options) {
    // 内部加载实现
    return loadFromPath(modulePath, options);
}

bool CmodLoader::loadDependencies(const std::string& dependencies,
                                const LoadOptions& options) {
    auto deps = parseDependencies(dependencies);
    bool allLoaded = true;
    
    for (const auto& dep : deps) {
        auto result = loadModule(dep, options);
        if (!result.success) {
            allLoaded = false;
        }
    }
    
    return allLoaded;
}

std::shared_ptr<Node> CmodLoader::parseModuleFile(const std::string& filePath) {
    // TODO: 实际解析模块文件
    return std::make_shared<Node>(NodeType::DOCUMENT);
}

std::shared_ptr<Node> CmodLoader::mergeModuleFiles(const std::vector<std::string>& filePaths) {
    auto merged = std::make_shared<Node>(NodeType::DOCUMENT);
    
    for (const auto& path : filePaths) {
        auto node = parseModuleFile(path);
        if (node) {
            for (const auto& child : node->getChildren()) {
                merged->appendChild(child);
            }
        }
    }
    
    return merged;
}

std::string CmodLoader::findModulePath(const std::string& moduleName) const {
    // 在搜索路径中查找模块
    for (const auto& searchPath : searchPaths_) {
        std::string modulePath = findModuleInDirectory(searchPath, moduleName);
        if (!modulePath.empty()) {
            return modulePath;
        }
    }
    
    // 检查注册表
    if (registry_) {
        auto module = registry_->getModule(moduleName);
        if (module) {
            return module->installPath;
        }
    }
    
    return "";
}

std::string CmodLoader::findModuleInDirectory(const std::string& dir, 
                                             const std::string& moduleName) const {
    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        return "";
    }
    
    // 直接查找模块目录
    std::string modulePath = dir + "/" + moduleName;
    if (fs::exists(modulePath) && fs::is_directory(modulePath)) {
        // 验证是否为有效的CMOD模块
        if (fs::exists(modulePath + "/info") && fs::exists(modulePath + "/src")) {
            return modulePath;
        }
    }
    
    // 处理子模块路径 (如 Module.SubModule)
    size_t dotPos = moduleName.find('.');
    if (dotPos != std::string::npos) {
        std::string parentName = moduleName.substr(0, dotPos);
        std::string subName = moduleName.substr(dotPos + 1);
        
        std::string parentPath = findModuleInDirectory(dir, parentName);
        if (!parentPath.empty()) {
            return findModuleInDirectory(parentPath + "/src", subName);
        }
    }
    
    return "";
}

bool CmodLoader::checkCircularDependency(const std::string& moduleName,
                                       std::vector<std::string>& loadingStack) const {
    if (std::find(loadingStack.begin(), loadingStack.end(), moduleName) != loadingStack.end()) {
        return true; // 发现循环依赖
    }
    
    loadingStack.push_back(moduleName);
    
    auto info = getModuleInfo(moduleName);
    if (info) {
        auto deps = parseDependencies(info->dependencies);
        for (const auto& dep : deps) {
            if (checkCircularDependency(dep, loadingStack)) {
                return true;
            }
        }
    }
    
    loadingStack.pop_back();
    return false;
}

bool CmodLoader::validateModule(const CmodInfo& info) const {
    // 基本验证
    if (info.name.empty() || info.version.empty()) {
        return false;
    }
    
    // TODO: 更多验证逻辑
    
    return true;
}

std::vector<std::string> CmodLoader::getDefaultSearchPaths() {
    std::vector<std::string> paths;
    
    // 当前目录的module文件夹
    paths.push_back("./module");
    paths.push_back("./modules");
    
    // 用户目录
    if (const char* home = std::getenv("HOME")) {
        paths.push_back(std::string(home) + "/.chtl/modules");
    }
    
    // 系统目录
    paths.push_back("/usr/local/share/chtl/modules");
    paths.push_back("/usr/share/chtl/modules");
    
    return paths;
}

std::vector<std::string> CmodLoader::parseDependencies(const std::string& depStr) const {
    std::vector<std::string> deps;
    
    if (depStr.empty()) {
        return deps;
    }
    
    // 简单的逗号分隔解析
    std::stringstream ss(depStr);
    std::string dep;
    
    while (std::getline(ss, dep, ',')) {
        // 去除空格
        dep.erase(0, dep.find_first_not_of(" \t"));
        dep.erase(dep.find_last_not_of(" \t") + 1);
        
        // 去除版本信息（如果有）
        size_t atPos = dep.find('@');
        if (atPos != std::string::npos) {
            dep = dep.substr(0, atPos);
        }
        
        if (!dep.empty()) {
            deps.push_back(dep);
        }
    }
    
    return deps;
}

} // namespace chtl