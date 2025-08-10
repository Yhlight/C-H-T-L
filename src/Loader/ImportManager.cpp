#include "Loader/ImportManager.h"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Import.h"
#include "Node/Comment.h"

namespace chtl {

namespace fs = std::filesystem;

ImportManager::ImportManager() {
    // 设置默认搜索路径
    config_.searchPaths.push_back(".");
    config_.searchPaths.push_back("./modules");
    config_.searchPaths.push_back("./lib");
    
    // 注册默认的CHTL加载器
    registerLoader(".chtl", [this](const std::string& path) {
        return loadModuleFromFile(path);
    });
}

ImportResult ImportManager::importModule(const std::string& modulePath,
                                        const std::string& fromPath) {
    auto startTime = std::chrono::steady_clock::now();
    stats_.totalImports++;
    
    // 清空导入栈
    currentImportStack_.clear();
    
    // 执行导入
    ImportResult result = importModuleInternal(modulePath, fromPath, currentImportStack_);
    
    // 更新统计
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    stats_.totalTime += duration;
    
    if (!result.success) {
        stats_.failedImports++;
    }
    
    return result;
}

ImportResult ImportManager::importModuleInternal(const std::string& modulePath,
                                                const std::string& fromPath,
                                                std::vector<std::string>& importStack) {
    ImportResult result;
    
    // 解析模块路径
    std::string resolvedPath = resolveModulePath(modulePath, fromPath);
    if (resolvedPath.empty()) {
        result.errors.push_back("Cannot resolve module path: " + modulePath);
        return result;
    }
    
    result.resolvedPath = resolvedPath;
    
    // 检查是否已经在导入栈中（快速循环检测）
    if (std::find(importStack.begin(), importStack.end(), resolvedPath) != importStack.end()) {
        // 构建循环信息
        CircularDependency cycle;
        auto it = std::find(importStack.begin(), importStack.end(), resolvedPath);
        cycle.cycle.assign(it, importStack.end());
        cycle.cycle.push_back(resolvedPath);
        
        // 生成描述
        std::stringstream ss;
        ss << "Circular dependency: ";
        for (size_t i = 0; i < cycle.cycle.size(); ++i) {
            if (i > 0) ss << " -> ";
            ss << cycle.cycle[i];
        }
        cycle.description = ss.str();
        
        result.circularDeps.push_back(cycle);
        stats_.circularImports++;
        
        if (!config_.allowCircularDependencies) {
            result.errors.push_back(cycle.description);
            return result;
        }
        
        // 处理循环依赖
        return handleCircularDependency(resolvedPath, cycle);
    }
    
    // 检查导入深度
    if (importStack.size() >= config_.maxImportDepth) {
        result.errors.push_back("Maximum import depth exceeded: " + std::to_string(config_.maxImportDepth));
        return result;
    }
    
    // 检查缓存
    if (config_.enableCache) {
        auto cacheIt = cache_.find(resolvedPath);
        if (cacheIt != cache_.end()) {
            // 检查文件是否被修改
            auto fileTime = fs::last_write_time(resolvedPath);
            auto fileTimePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                fileTime - fs::file_time_type{} + std::chrono::system_clock::now()
            );
            
            if (fileTimePoint <= cacheIt->second.timestamp) {
                result.success = true;
                result.ast = cacheIt->second.ast->clone();
                stats_.cachedImports++;
                
                // 更新使用信息
                updateUsageInfo(resolvedPath);
                
                return result;
            }
        }
    }
    
    // 添加到导入栈
    importStack.push_back(resolvedPath);
    
    // 加载模块
    std::shared_ptr<Node> ast;
    
    // 查找合适的加载器
    fs::path filePath(resolvedPath);
    std::string extension = filePath.extension().string();
    
    auto loaderIt = loaders_.find(extension);
    if (loaderIt != loaders_.end()) {
        try {
            ast = loaderIt->second(resolvedPath);
        } catch (const std::exception& e) {
            result.errors.push_back("Failed to load module: " + std::string(e.what()));
            importStack.pop_back();
            return result;
        }
    } else {
        result.errors.push_back("No loader registered for extension: " + extension);
        importStack.pop_back();
        return result;
    }
    
    if (!ast) {
        result.errors.push_back("Failed to parse module: " + resolvedPath);
        importStack.pop_back();
        return result;
    }
    
    // 提取依赖
    std::vector<std::string> dependencies = extractDependencies(ast);
    
    // 添加到依赖图
    dependencyGraph_.addModule(resolvedPath, resolvedPath, dependencies);
    
    // 递归导入依赖
    for (const auto& dep : dependencies) {
        ImportResult depResult = importModuleInternal(dep, resolvedPath, importStack);
        if (!depResult.success) {
            result.errors.insert(result.errors.end(), 
                               depResult.errors.begin(), 
                               depResult.errors.end());
            result.warnings.insert(result.warnings.end(),
                                 depResult.warnings.begin(),
                                 depResult.warnings.end());
        }
        
        // 合并符号
        if (depResult.ast) {
            mergeImportedSymbols(ast, depResult.ast, dep);
        }
    }
    
    // 应用变换器
    applyTransformers(ast, resolvedPath);
    
    // 缓存结果
    if (config_.enableCache) {
        ImportCacheEntry cacheEntry;
        cacheEntry.ast = ast->clone();
        cacheEntry.resolvedPath = resolvedPath;
        cacheEntry.timestamp = std::chrono::system_clock::now();
        cacheEntry.dependencies = dependencies;
        cache_[resolvedPath] = cacheEntry;
        
        // 设置依赖图缓存
        dependencyGraph_.setModuleCache(resolvedPath, 
            std::weak_ptr<void>(std::static_pointer_cast<void>(ast)));
    }
    
    // 移除从导入栈
    importStack.pop_back();
    
    // 更新使用信息
    updateUsageInfo(resolvedPath);
    
    result.success = true;
    result.ast = ast;
    
    return result;
}

std::vector<ImportResult> ImportManager::importModules(const std::vector<std::string>& modules,
                                                      const std::string& fromPath) {
    std::vector<ImportResult> results;
    
    for (const auto& module : modules) {
        results.push_back(importModule(module, fromPath));
    }
    
    return results;
}

std::vector<CircularDependency> ImportManager::checkCircularDependencies() {
    return dependencyGraph_.detectAllCircularDependencies();
}

std::vector<std::string> ImportManager::getUnusedImports() {
    std::vector<std::string> unused;
    
    if (!config_.detectUnusedImports) {
        return unused;
    }
    
    // 检查所有已导入的模块
    for (const auto& [module, info] : usageInfo_) {
        if (info.empty()) {
            unused.push_back(module);
        }
    }
    
    return unused;
}

void ImportManager::clearCache() {
    cache_.clear();
    dependencyGraph_.clear();
    usageInfo_.clear();
}

void ImportManager::clearCacheForModule(const std::string& modulePath) {
    std::string resolved = resolveModulePath(modulePath);
    cache_.erase(resolved);
    
    // 清除依赖此模块的缓存
    auto dependents = dependencyGraph_.getDependents(resolved);
    for (const auto& dep : dependents) {
        cache_.erase(dep);
    }
}

std::string ImportManager::resolveModulePath(const std::string& modulePath,
                                            const std::string& fromPath) {
    // 如果是绝对路径，直接返回
    fs::path path(modulePath);
    if (path.is_absolute() && fs::exists(path)) {
        return path.string();
    }
    
    // 相对于当前文件路径查找
    if (!fromPath.empty()) {
        fs::path fromDir = fs::path(fromPath).parent_path();
        fs::path relPath = fromDir / modulePath;
        
        // 尝试不同的扩展名
        if (fs::exists(relPath)) {
            return relPath.string();
        }
        if (fs::exists(relPath.string() + ".chtl")) {
            return relPath.string() + ".chtl";
        }
        if (fs::exists(relPath.string() + ".cmod")) {
            return relPath.string() + ".cmod";
        }
    }
    
    // 在搜索路径中查找
    for (const auto& searchPath : config_.searchPaths) {
        fs::path searchDir(searchPath);
        fs::path fullPath = searchDir / modulePath;
        
        if (fs::exists(fullPath)) {
            return fullPath.string();
        }
        if (fs::exists(fullPath.string() + ".chtl")) {
            return fullPath.string() + ".chtl";
        }
        if (fs::exists(fullPath.string() + ".cmod")) {
            return fullPath.string() + ".cmod";
        }
    }
    
    return "";
}

void ImportManager::registerLoader(const std::string& extension, ModuleLoader loader) {
    loaders_[extension] = loader;
}

void ImportManager::registerTransformer(ModuleTransformer transformer) {
    transformers_.push_back(transformer);
}

std::shared_ptr<Node> ImportManager::loadModuleFromFile(const std::string& path) {
    // 创建词法分析器和解析器
    auto lexer = std::make_shared<StandardLexer>();
    auto context = context_ ? context_ : std::make_shared<StandardContext>();
    auto parser = std::make_shared<StandardParser>(lexer, context);
    
    // 初始化词法分析器
    if (!lexer->initialize(path)) {
        throw std::runtime_error("Failed to initialize lexer for: " + path);
    }
    
    // 解析文件
    return parser->parse();
}

std::vector<std::string> ImportManager::extractDependencies(std::shared_ptr<Node> ast) {
    std::vector<std::string> dependencies;
    
    if (!ast) return dependencies;
    
    // 递归遍历AST查找Import节点
    std::function<void(std::shared_ptr<Node>)> findImports = [&](std::shared_ptr<Node> node) {
        if (!node) return;
        
        if (node->getType() == NodeType::IMPORT) {
            auto importNode = std::static_pointer_cast<Import>(node);
            
            // 获取模块路径 - Import节点应该有path属性
            std::string path = importNode->getPath();
            if (!path.empty()) {
                dependencies.push_back(path);
            }
        }
        
        // 递归遍历子节点
        for (const auto& child : node->getChildren()) {
            findImports(child);
        }
    };
    
    findImports(ast);
    
    return dependencies;
}

ImportResult ImportManager::handleCircularDependency(const std::string& modulePath,
                                                    const CircularDependency& cycle) {
    ImportResult result;
    
    // 如果允许循环依赖，返回一个占位符节点
    if (config_.allowCircularDependencies) {
        result.success = true;
        result.ast = std::make_shared<Comment>("Circular dependency placeholder for: " + modulePath);
        result.warnings.push_back(cycle.description);
        return result;
    }
    
    result.errors.push_back(cycle.description);
    return result;
}

void ImportManager::mergeImportedSymbols(std::shared_ptr<Node> targetAst,
                                        std::shared_ptr<Node> importedAst,
                                        const std::string& modulePath) {
    if (!targetAst || !importedAst) return;
    
    // 检测符号冲突
    if (config_.autoResolveConflicts) {
        auto conflicts = detectSymbolConflicts(targetAst, importedAst);
        if (!conflicts.empty()) {
            // 记录警告
            for (const auto& conflict : conflicts) {
                if (context_) {
                    context_->addWarning("Symbol conflict from " + modulePath + ": " + conflict);
                }
            }
        }
    }
    
    // 简单实现：将导入的顶层节点添加到目标AST
    // 实际实现应该更智能地合并符号表
    for (const auto& child : importedAst->getChildren()) {
        targetAst->appendChild(child->clone());
    }
}

std::vector<std::string> ImportManager::detectSymbolConflicts(std::shared_ptr<Node> ast1,
                                                             std::shared_ptr<Node> ast2) {
    std::vector<std::string> conflicts;
    
    // 收集两个AST中的符号
    std::unordered_set<std::string> symbols1;
    std::unordered_set<std::string> symbols2;
    
    std::function<void(std::shared_ptr<Node>, std::unordered_set<std::string>&)> collectSymbols;
    collectSymbols = [&collectSymbols](std::shared_ptr<Node> ast, std::unordered_set<std::string>& symbols) {
        if (!ast) return;
        
        // 收集各种符号（函数、类、变量等）
        if (ast->getType() == NodeType::TEMPLATE || 
            ast->getType() == NodeType::CUSTOM) {
            try {
                auto nameAttr = ast->getAttribute("name");
                if (std::holds_alternative<std::string>(nameAttr)) {
                    symbols.insert(std::get<std::string>(nameAttr));
                }
            } catch (...) {
                // getAttribute可能抛出异常如果属性不存在
            }
        }
        
        // 递归遍历子节点
        for (const auto& child : ast->getChildren()) {
            collectSymbols(child, symbols);
        }
    };
    
    collectSymbols(ast1, symbols1);
    collectSymbols(ast2, symbols2);
    
    // 查找冲突
    for (const auto& symbol : symbols2) {
        if (symbols1.find(symbol) != symbols1.end()) {
            conflicts.push_back(symbol);
        }
    }
    
    return conflicts;
}

void ImportManager::applyTransformers(std::shared_ptr<Node>& ast, const std::string& modulePath) {
    for (const auto& transformer : transformers_) {
        transformer(ast, modulePath);
    }
}

void ImportManager::updateUsageInfo(const std::string& modulePath) {
    // 简单实现：标记模块已被使用
    usageInfo_[modulePath].insert("used");
}

} // namespace chtl