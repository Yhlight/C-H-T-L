#include "Loader/ModuleLoader.h"
#include "Loader/FileLoader.h"
#include "Loader/CmodLoader.h"
#include "CmodSystem/CmodRegistry.h"
#include "Node/Node.h"
#include <filesystem>

namespace chtl {

namespace fs = std::filesystem;

ModuleLoader::ModuleLoader() 
    : fileLoader_(std::make_unique<FileLoader>()),
      cmodLoader_(std::make_unique<CmodLoader>()),
      registry_(std::make_shared<CmodRegistry>()) {
}

ModuleLoader::~ModuleLoader() = default;

// 初始化
bool ModuleLoader::initialize(const std::string& workDir) {
    workingDirectory_ = workDir.empty() ? fs::current_path().string() : workDir;
    
    // 初始化CMOD加载器
    if (!cmodLoader_->initialize(registry_)) {
        errors_.push_back("Failed to initialize CMOD loader");
        return false;
    }
    
    // 初始化注册表
    if (!registry_->initialize()) {
        errors_.push_back("Failed to initialize module registry");
        return false;
    }
    
    // 添加默认模块搜索路径
    addModulePath(workingDirectory_ + "/module");
    addModulePath(workingDirectory_ + "/modules");
    
    return true;
}

// 加载入口文件或模块
ModuleLoader::LoadResult ModuleLoader::load(const std::string& target) {
    LoadResult result{true, "", {}, nullptr, {}, {}};
    
    auto loadType = detectLoadType(target);
    
    switch (loadType) {
        case LoadType::FILE:
            if (fileLoader_->loadFile(target)) {
                result.loadedFiles.push_back(target);
                if (autoResolve_) {
                    fileLoader_->resolveDependencies();
                }
                if (fileLoader_->parseFile(target)) {
                    result.rootNode = fileLoader_->getAST(target);
                }
            } else {
                result.success = false;
                result.error = fileLoader_->getFileError(target);
            }
            break;
            
        case LoadType::MODULE: {
            auto modResult = cmodLoader_->loadModule(target);
            if (modResult.success) {
                result.loadedModules.push_back(target);
                result.rootNode = modResult.rootNode;
            } else {
                result.success = false;
                result.error = modResult.error;
                result.warnings = modResult.warnings;
            }
            break;
        }
            
        case LoadType::DIRECTORY:
            if (fileLoader_->loadDirectory(target, true)) {
                auto files = fileLoader_->getLoadedFiles();
                result.loadedFiles = files;
                if (autoResolve_) {
                    fileLoader_->resolveDependencies();
                }
                fileLoader_->parseAllFiles();
                // TODO: 合并所有文件的AST
                result.rootNode = std::make_shared<Element>("document");
            } else {
                result.success = false;
                result.error = "Failed to load directory: " + target;
            }
            break;
            
        default:
            result.success = false;
            result.error = "Unknown target type: " + target;
            break;
    }
    
    if (result.success) {
        loadedTargets_.push_back(target);
        if (cacheEnabled_ && result.rootNode) {
            astCache_[target] = result.rootNode;
        }
    }
    
    return result;
}

// 加载多个目标
ModuleLoader::LoadResult ModuleLoader::loadMultiple(const std::vector<std::string>& targets) {
    LoadResult result{true, "", {}, nullptr, {}, {}};
    std::vector<std::shared_ptr<Node>> asts;
    
    for (const auto& target : targets) {
        auto singleResult = load(target);
        
        if (!singleResult.success) {
            result.success = false;
            if (!result.error.empty()) result.error += "; ";
            result.error += singleResult.error;
        }
        
        result.warnings.insert(result.warnings.end(), 
                             singleResult.warnings.begin(), 
                             singleResult.warnings.end());
        
        result.loadedFiles.insert(result.loadedFiles.end(),
                                singleResult.loadedFiles.begin(),
                                singleResult.loadedFiles.end());
        
        result.loadedModules.insert(result.loadedModules.end(),
                                  singleResult.loadedModules.begin(),
                                  singleResult.loadedModules.end());
        
        if (singleResult.rootNode) {
            asts.push_back(singleResult.rootNode);
        }
    }
    
    if (!asts.empty()) {
        result.rootNode = mergeASTs(asts);
    }
    
    return result;
}

// 加载项目
ModuleLoader::LoadResult ModuleLoader::loadProject(const std::string& projectDir) {
    LoadResult result{true, "", {}, nullptr, {}, {}};
    
    // 查找项目配置文件
    std::string configFile = projectDir + "/chtl.config";
    if (fs::exists(configFile)) {
        // TODO: 解析配置文件
    }
    
    // 加载src目录
    std::string srcDir = projectDir + "/src";
    if (fs::exists(srcDir)) {
        auto dirResult = load(srcDir);
        result = dirResult;
    }
    
    // 加载module目录中的模块
    std::string moduleDir = projectDir + "/module";
    if (fs::exists(moduleDir)) {
        auto modules = registry_->scanDirectory(moduleDir);
        for (const auto& modInfo : modules) {
            auto modResult = cmodLoader_->loadModule(modInfo.name);
            if (modResult.success) {
                result.loadedModules.push_back(modInfo.name);
            }
        }
    }
    
    return result;
}

// 解析所有已加载的内容
bool ModuleLoader::parseAll() {
    return fileLoader_->parseAllFiles();
}

// 获取AST
std::shared_ptr<Node> ModuleLoader::getAST(const std::string& target) const {
    // 先检查缓存
    if (cacheEnabled_) {
        auto it = astCache_.find(target);
        if (it != astCache_.end()) {
            return it->second;
        }
    }
    
    // 检查文件加载器
    auto fileAst = fileLoader_->getAST(target);
    if (fileAst) {
        return fileAst;
    }
    
    // 检查CMOD加载器
    return cmodLoader_->getLoadedModule(target);
}

std::shared_ptr<Node> ModuleLoader::getMergedAST() const {
    std::vector<std::shared_ptr<Node>> asts;
    
    // 收集所有文件的AST
    std::vector<std::string> loadedFiles = getLoadedFiles();
    for (const auto& file : loadedFiles) {
        auto ast = fileLoader_->getAST(file);
        if (ast) {
            asts.push_back(ast);
        }
    }
    
    // 收集所有模块的AST
    for (const auto& module : cmodLoader_->getLoadedModules()) {
        auto ast = cmodLoader_->getLoadedModule(module);
        if (ast) {
            asts.push_back(ast);
        }
    }
    
    return mergeASTs(asts);
}

// 依赖管理
bool ModuleLoader::resolveDependencies() {
    bool fileSuccess = fileLoader_->resolveDependencies();
    
    // TODO: 解析CMOD模块依赖
    bool modSuccess = true;
    
    return fileSuccess && modSuccess;
}

std::vector<std::string> ModuleLoader::getUnresolvedDependencies() const {
    std::vector<std::string> unresolved;
    
    // TODO: 实现未解析依赖的收集
    
    return unresolved;
}

// 模块查询
bool ModuleLoader::hasModule(const std::string& moduleName) const {
    return cmodLoader_->isModuleLoaded(moduleName);
}

std::vector<std::string> ModuleLoader::getLoadedModules() const {
    return cmodLoader_->getLoadedModules();
}

// 文件查询
bool ModuleLoader::hasFile(const std::string& filePath) const {
    return fileLoader_->isFileLoaded(filePath);
}

std::vector<std::string> ModuleLoader::getLoadedFiles() const {
    std::vector<std::string> files;
    // TODO: FileLoader需要提供获取所有已加载文件的方法
    // 暂时返回空列表
    return files;
}

// 错误处理
bool ModuleLoader::hasErrors() const {
    return fileLoader_->hasErrors() || !errors_.empty();
}

std::vector<std::string> ModuleLoader::getErrors() const {
    std::vector<std::string> allErrors = errors_;
    
    auto fileErrors = fileLoader_->getErrors();
    allErrors.insert(allErrors.end(), fileErrors.begin(), fileErrors.end());
    
    return allErrors;
}

// 配置
void ModuleLoader::addModulePath(const std::string& path) {
    modulePaths_.push_back(path);
    cmodLoader_->addSearchPath(path);
    registry_->addSearchPath(path);
}

// 清理
void ModuleLoader::clear() {
    fileLoader_->clearAllFiles();
    cmodLoader_->clearCache();
    astCache_.clear();
    loadedTargets_.clear();
    errors_.clear();
}

void ModuleLoader::clearCache() {
    astCache_.clear();
    cmodLoader_->clearCache();
}

// 私有方法
ModuleLoader::LoadType ModuleLoader::detectLoadType(const std::string& target) const {
    fs::path path(target);
    
    // 检查是否为文件
    if (fs::exists(target)) {
        if (fs::is_regular_file(target)) {
            return LoadType::FILE;
        } else if (fs::is_directory(target)) {
            // 检查是否为CMOD模块目录
            if (fs::exists(target + "/info") && fs::exists(target + "/src")) {
                return LoadType::MODULE;
            }
            return LoadType::DIRECTORY;
        }
    }
    
    // 如果不存在，检查是否为模块名
    if (target.find('/') == std::string::npos && 
        target.find('\\') == std::string::npos) {
        // 可能是模块名
        if (cmodLoader_->findModule(target) != "") {
            return LoadType::MODULE;
        }
    }
    
    return LoadType::UNKNOWN;
}

std::shared_ptr<Node> ModuleLoader::mergeASTs(const std::vector<std::shared_ptr<Node>>& asts) const {
    if (asts.empty()) {
        return nullptr;
    }
    
    if (asts.size() == 1) {
        return asts[0];
    }
    
    // 创建合并的文档节点
    auto mergedDoc = std::make_shared<Element>("document");
    
    for (const auto& ast : asts) {
        if (ast) {
            // 将每个AST的子节点添加到合并文档中
            for (const auto& child : ast->getChildren()) {
                mergedDoc->appendChild(child);
            }
        }
    }
    
    return mergedDoc;
}

} // namespace chtl