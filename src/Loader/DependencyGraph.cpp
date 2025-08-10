#include "Loader/DependencyGraph.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <functional>

namespace chtl {

DependencyGraph::DependencyGraph() {
}

void DependencyGraph::addModule(const std::string& modulePath, 
                               const std::string& resolvedPath,
                               const std::vector<std::string>& dependencies) {
    auto& info = modules_[modulePath];
    info.path = modulePath;
    info.resolvedPath = resolvedPath;
    info.imports = dependencies;
    needRebuildReverse_ = true;
    
    // 确保所有依赖也在图中
    for (const auto& dep : dependencies) {
        if (modules_.find(dep) == modules_.end()) {
            modules_[dep].path = dep;
        }
    }
}

bool DependencyGraph::hasCircularDependency(const std::string& modulePath) {
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> recursionStack;
    std::vector<std::string> currentPath;
    std::vector<CircularDependency> cycles;
    
    return detectCycleDFS(modulePath, visited, recursionStack, currentPath, cycles);
}

std::vector<CircularDependency> DependencyGraph::detectAllCircularDependencies() {
    std::vector<CircularDependency> cycles;
    std::unordered_set<std::string> visited;
    
    for (const auto& [module, info] : modules_) {
        if (visited.find(module) == visited.end()) {
            std::unordered_set<std::string> recursionStack;
            std::vector<std::string> currentPath;
            detectCycleDFS(module, visited, recursionStack, currentPath, cycles);
        }
    }
    
    return cycles;
}

bool DependencyGraph::detectCycleDFS(const std::string& module,
                                    std::unordered_set<std::string>& visited,
                                    std::unordered_set<std::string>& recursionStack,
                                    std::vector<std::string>& currentPath,
                                    std::vector<CircularDependency>& cycles) {
    visited.insert(module);
    recursionStack.insert(module);
    currentPath.push_back(module);
    
    auto it = modules_.find(module);
    if (it != modules_.end()) {
        for (const auto& dep : it->second.imports) {
            if (recursionStack.find(dep) != recursionStack.end()) {
                // 找到循环
                CircularDependency cycle;
                
                // 提取循环部分
                auto cycleStart = std::find(currentPath.begin(), currentPath.end(), dep);
                cycle.cycle.assign(cycleStart, currentPath.end());
                cycle.cycle.push_back(dep); // 添加回到起点
                
                // 生成描述
                std::stringstream ss;
                ss << "Circular dependency detected: ";
                for (size_t i = 0; i < cycle.cycle.size(); ++i) {
                    if (i > 0) ss << " -> ";
                    ss << cycle.cycle[i];
                }
                cycle.description = ss.str();
                
                cycles.push_back(cycle);
                return true;
            }
            
            if (visited.find(dep) == visited.end()) {
                if (detectCycleDFS(dep, visited, recursionStack, currentPath, cycles)) {
                    // 子路径中发现循环
                }
            }
        }
    }
    
    recursionStack.erase(module);
    currentPath.pop_back();
    return false;
}

bool DependencyGraph::isModuleImported(const std::string& modulePath) const {
    auto it = modules_.find(modulePath);
    return it != modules_.end() && it->second.isProcessed;
}

std::weak_ptr<void> DependencyGraph::getModuleCache(const std::string& modulePath) const {
    auto it = modules_.find(modulePath);
    if (it != modules_.end()) {
        return it->second.cachedModule;
    }
    return std::weak_ptr<void>();
}

void DependencyGraph::setModuleCache(const std::string& modulePath, std::weak_ptr<void> cache) {
    auto it = modules_.find(modulePath);
    if (it != modules_.end()) {
        it->second.cachedModule = cache;
        it->second.isProcessed = true;
    }
}

std::vector<std::string> DependencyGraph::getTopologicalOrder() {
    std::vector<std::string> result;
    std::unordered_set<std::string> visited;
    
    for (const auto& [module, info] : modules_) {
        if (visited.find(module) == visited.end()) {
            topologicalSortDFS(module, visited, result);
        }
    }
    
    // 反转结果（依赖在前）
    std::reverse(result.begin(), result.end());
    return result;
}

void DependencyGraph::topologicalSortDFS(const std::string& module,
                                        std::unordered_set<std::string>& visited,
                                        std::vector<std::string>& result) {
    visited.insert(module);
    
    auto it = modules_.find(module);
    if (it != modules_.end()) {
        for (const auto& dep : it->second.imports) {
            if (visited.find(dep) == visited.end()) {
                topologicalSortDFS(dep, visited, result);
            }
        }
    }
    
    result.push_back(module);
}

void DependencyGraph::clear() {
    modules_.clear();
    reverseDependencies_.clear();
    needRebuildReverse_ = true;
}

std::unordered_set<std::string> DependencyGraph::getAllDependencies(const std::string& modulePath) {
    std::unordered_set<std::string> allDeps;
    std::unordered_set<std::string> visited;
    
    std::function<void(const std::string&)> collectDeps = [&](const std::string& module) {
        if (visited.find(module) != visited.end()) {
            return;
        }
        visited.insert(module);
        
        auto it = modules_.find(module);
        if (it != modules_.end()) {
            for (const auto& dep : it->second.imports) {
                allDeps.insert(dep);
                collectDeps(dep);
            }
        }
    };
    
    collectDeps(modulePath);
    return allDeps;
}

std::vector<std::string> DependencyGraph::getDependents(const std::string& modulePath) {
    if (needRebuildReverse_) {
        buildReverseDependencies();
    }
    
    auto it = reverseDependencies_.find(modulePath);
    if (it != reverseDependencies_.end()) {
        return it->second;
    }
    return {};
}

void DependencyGraph::buildReverseDependencies() {
    reverseDependencies_.clear();
    
    for (const auto& [module, info] : modules_) {
        for (const auto& dep : info.imports) {
            reverseDependencies_[dep].push_back(module);
        }
    }
    
    needRebuildReverse_ = false;
}

void DependencyGraph::printGraph() const {
    std::cout << "Dependency Graph:\n";
    std::cout << "================\n";
    
    for (const auto& [module, info] : modules_) {
        std::cout << module;
        if (!info.resolvedPath.empty() && info.resolvedPath != module) {
            std::cout << " (" << info.resolvedPath << ")";
        }
        std::cout << ":\n";
        
        if (info.imports.empty()) {
            std::cout << "  (no dependencies)\n";
        } else {
            for (const auto& dep : info.imports) {
                std::cout << "  -> " << dep << "\n";
            }
        }
        
        if (info.isProcessed) {
            std::cout << "  [PROCESSED]";
            if (!info.cachedModule.expired()) {
                std::cout << " [CACHED]";
            }
            std::cout << "\n";
        }
        
        std::cout << "\n";
    }
}

} // namespace chtl