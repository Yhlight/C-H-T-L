#include "CJmod/CJmodLoader.h"
#include "CJmod/CJmodSubmodule.h"
#include "Loader/ImportResolver.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace chtl {
namespace cjmod {

// 扩展 CJmodLoader 以支持子模块
std::shared_ptr<ICJmod> CJmodLoader::loadSubmodule(const std::string& parentModule, 
                                                   const std::string& submoduleName) {
    std::string fullName = parentModule + "." + submoduleName;
    
    // 检查缓存
    auto it = loadedModules_.find(fullName);
    if (it != loadedModules_.end()) {
        return it->second;
    }
    
    // 查找父模块
    auto parentIt = loadedModules_.find(parentModule);
    if (parentIt == loadedModules_.end()) {
        std::cerr << "[CJmod] Parent module not loaded: " << parentModule << std::endl;
        return nullptr;
    }
    
    // 检查父模块是否支持子模块
    auto parentWithSub = std::dynamic_pointer_cast<ICJmodWithSubmodules>(parentIt->second);
    if (!parentWithSub) {
        std::cerr << "[CJmod] Parent module does not support submodules: " << parentModule << std::endl;
        return nullptr;
    }
    
    // 通过父模块加载子模块
    auto submodule = parentWithSub->loadSubmodule(submoduleName);
    if (submodule) {
        loadedModules_[fullName] = submodule;
        std::cout << "[CJmod] Loaded submodule: " << fullName << std::endl;
    }
    
    return submodule;
}

std::shared_ptr<ICJmod> CJmodLoader::loadWithSubmodules(const std::string& path) {
    // 解析路径，查看是否包含子模块
    size_t dotPos = path.find('.');
    size_t slashPos = path.find('/');
    
    // 确定分隔符位置
    size_t sepPos = std::string::npos;
    if (dotPos != std::string::npos && slashPos != std::string::npos) {
        sepPos = std::min(dotPos, slashPos);
    } else if (dotPos != std::string::npos) {
        sepPos = dotPos;
    } else if (slashPos != std::string::npos) {
        sepPos = slashPos;
    }
    
    if (sepPos != std::string::npos) {
        // 包含子模块路径
        std::string mainModule = path.substr(0, sepPos);
        std::string submodulePath = path.substr(sepPos + 1);
        
        // 先加载主模块
        auto main = loadModule(mainModule);
        if (!main) {
            return nullptr;
        }
        
        // 处理通配符
        if (submodulePath == "*") {
            // 加载所有子模块
            auto mainWithSub = std::dynamic_pointer_cast<ICJmodWithSubmodules>(main);
            if (mainWithSub) {
                auto composite = std::make_shared<CompositeModule>(main, path);
                
                for (const auto& subInfo : mainWithSub->getSubmodules()) {
                    if (subInfo.autoLoad) {
                        auto sub = loadSubmodule(mainModule, subInfo.name);
                        if (sub) {
                            composite->addSubmodule(subInfo.name, sub);
                        }
                    }
                }
                
                return composite;
            }
        } else {
            // 加载特定子模块
            return loadSubmodule(mainModule, submodulePath);
        }
    }
    
    // 没有子模块，正常加载
    return loadModule(path);
}

} // namespace cjmod
} // namespace chtl