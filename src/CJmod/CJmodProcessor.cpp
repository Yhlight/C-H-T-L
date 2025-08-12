#include "CJmod/CJmodProcessor.h"
#include "CJmod/CJmodContextImpl.h"
#include <algorithm>
#include <regex>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #define DLOPEN(path) LoadLibraryA(path)
    #define DLSYM(handle, symbol) GetProcAddress((HMODULE)handle, symbol)
    #define DLCLOSE(handle) FreeLibrary((HMODULE)handle)
    #define DLERROR() "Windows DLL error"
#else
    #include <dlfcn.h>
    #define DLOPEN(path) dlopen(path, RTLD_LAZY)
    #define DLSYM(handle, symbol) dlsym(handle, symbol)
    #define DLCLOSE(handle) dlclose(handle)
    #define DLERROR() dlerror()
#endif

namespace chtl {
namespace cjmod {

// CJmod 模块创建函数类型
typedef CJmodModule* (*CreateModuleFunc)();
typedef void (*DestroyModuleFunc)(CJmodModule*);

CJmodProcessor::CJmodProcessor() = default;

CJmodProcessor::~CJmodProcessor() {
    // 卸载所有模块
    for (auto& [name, info] : modules_) {
        if (info.destroyFunc && info.module) {
            info.destroyFunc(info.module);
        }
        if (info.handle) {
            DLCLOSE(info.handle);
        }
    }
}

CJmodProcessor& CJmodProcessor::getInstance() {
    static CJmodProcessor instance;
    return instance;
}

bool CJmodProcessor::loadModule(const std::string& modulePath) {
    // 检查是否已加载
    if (modules_.find(modulePath) != modules_.end()) {
        return true;
    }
    
    // 加载动态库
    void* handle = DLOPEN(modulePath.c_str());
    if (!handle) {
        std::cerr << "Failed to load module: " << modulePath << " - " << DLERROR() << std::endl;
        return false;
    }
    
    // 获取创建函数
    CreateModuleFunc createFunc = (CreateModuleFunc)DLSYM(handle, "createModule");
    if (!createFunc) {
        std::cerr << "Module does not export createModule: " << modulePath << std::endl;
        DLCLOSE(handle);
        return false;
    }
    
    // 获取销毁函数（可选）
    DestroyModuleFunc destroyFunc = (DestroyModuleFunc)DLSYM(handle, "destroyModule");
    
    // 创建模块实例
    CJmodModule* module = createFunc();
    if (!module) {
        std::cerr << "Failed to create module instance: " << modulePath << std::endl;
        DLCLOSE(handle);
        return false;
    }
    
    // 获取模块信息
    ModuleInfo info;
    info.module = module;
    info.handle = handle;
    info.destroyFunc = destroyFunc;
    
    // 获取语法规则
    auto syntaxRules = module->syntax();
    for (auto& rule : syntaxRules) {
        info.rules.push_back(rule.build());
    }
    
    // 获取运行时构建器
    info.runtimeBuilder = std::make_unique<RuntimeBuilder>();
    module->runtime(*info.runtimeBuilder);
    
    // 存储模块
    modules_[modulePath] = std::move(info);
    activeModules_.insert(modulePath);
    
    return true;
}

bool CJmodProcessor::unloadModule(const std::string& modulePath) {
    auto it = modules_.find(modulePath);
    if (it == modules_.end()) {
        return false;
    }
    
    // 清理模块
    ModuleInfo& info = it->second;
    if (info.destroyFunc && info.module) {
        info.destroyFunc(info.module);
    }
    if (info.handle) {
        DLCLOSE(info.handle);
    }
    
    // 从活跃列表中移除
    activeModules_.erase(modulePath);
    modules_.erase(it);
    
    return true;
}

bool CJmodProcessor::loadModuleFromMemory(std::unique_ptr<CJmodModule> module) {
    if (!module) {
        return false;
    }
    
    // 生成一个唯一的名称
    std::string name = "memory:" + std::to_string(reinterpret_cast<uintptr_t>(module.get()));
    
    // 创建模块信息
    ModuleInfo info;
    info.module = module.release();  // 转移所有权
    info.handle = nullptr;  // 内存模块没有动态库句柄
    info.destroyFunc = nullptr;  // 内存模块不需要销毁函数
    
    // 获取语法规则
    auto syntaxRules = info.module->syntax();
    for (auto& rule : syntaxRules) {
        info.rules.push_back(rule.build());
    }
    
    // 获取运行时构建器
    info.runtimeBuilder = std::make_unique<RuntimeBuilder>();
    info.module->runtime(*info.runtimeBuilder);
    
    // 存储模块
    modules_[name] = std::move(info);
    activeModules_.insert(name);
    
    return true;
}

std::string CJmodProcessor::processScript(const std::string& script, 
                                        const std::vector<std::string>& activeModules) {
    // 创建状态管理器
    StateManager stateManager;
    
    // 收集所有活跃模块的规则
    std::vector<std::shared_ptr<SyntaxRule>> allRules;
    
    // 如果没有指定活跃模块，使用所有已加载的模块
    auto modulesToUse = activeModules.empty() ? activeModules_ : std::set<std::string>(activeModules.begin(), activeModules.end());
    
    for (const auto& modulePath : modulesToUse) {
        const auto& moduleInfo = modules_[modulePath];
        allRules.insert(allRules.end(), moduleInfo.rules.begin(), moduleInfo.rules.end());
    }
    
    // 按优先级排序规则
    std::sort(allRules.begin(), allRules.end(), 
        [](const auto& a, const auto& b) { return a->priority > b->priority; });
    
    // 单遍扫描和转换
    std::string result;
    size_t lastPos = 0;
    
    while (lastPos < script.length()) {
        ScanContextImpl scanCtx(script, lastPos, &stateManager);
        ScanResult bestMatch;
        std::shared_ptr<SyntaxRule> bestRule;
        
        // 尝试所有规则
        for (const auto& rule : allRules) {
            // 跳过已处理的位置
            if (scanCtx.isProcessed(0)) continue;
            
            auto matches = rule->scan(&scanCtx);
            if (!matches.empty()) {
                // 选择最早的匹配
                for (const auto& match : matches) {
                    if (!bestRule || match.start < bestMatch.start) {
                        bestMatch = match;
                        bestRule = rule;
                    }
                }
            }
        }
        
        if (bestRule) {
            // 添加匹配前的内容
            if (bestMatch.start > 0) {
                result += script.substr(lastPos, bestMatch.start);
            }
            
            // 生成替换内容
            RuntimeBuilder runtime;
            GenerateContextImpl genCtx(&runtime, &stateManager);
            std::string replacement = bestRule->generate(bestMatch, &genCtx);
            result += replacement;
            
            // 标记已处理区域
            scanCtx.markProcessed(bestMatch.start, bestMatch.end);
            
            // 更新位置
            lastPos += bestMatch.end;
        } else {
            // 没有匹配，添加当前字符
            result += script[lastPos];
            lastPos++;
        }
    }
    
    return result;
}

std::string CJmodProcessor::getRuntimeCode(const std::vector<std::string>& modules) {
    std::stringstream runtime;
    
    runtime << "// CJmod Runtime\n";
    runtime << "(function(window) {\n";
    runtime << "  'use strict';\n";
    runtime << "  \n";
    runtime << "  window.CHTL = window.CHTL || {};\n";
    runtime << "  window.CHTL.modules = window.CHTL.modules || {};\n";
    runtime << "  \n";
    
    // 收集所有模块的运行时代码
    for (const auto& modulePath : activeModules_) {
        const auto& moduleInfo = modules_[modulePath];
        if (moduleInfo.runtimeBuilder) {
            std::string moduleRuntime = moduleInfo.runtimeBuilder->generate();
            if (!moduleRuntime.empty()) {
                runtime << "  // Module: " << modulePath << "\n";
                runtime << moduleRuntime << "\n";
            }
        }
    }
    
    runtime << "})(window);\n";
    
    return runtime.str();
}

std::vector<std::string> CJmodProcessor::getLoadedModules() const {
    std::vector<std::string> result;
    for (const auto& [name, _] : modules_) {
        result.push_back(name);
    }
    return result;
}

bool CJmodProcessor::isModuleLoaded(const std::string& name) const {
    return modules_.find(name) != modules_.end();
}

void CJmodProcessor::unloadModule(const std::string& name) {
    auto it = modules_.find(name);
    if (it != modules_.end()) {
        // 清理模块
        ModuleInfo& info = it->second;
        if (info.destroyFunc && info.module) {
            info.destroyFunc(info.module);
        } else if (info.module) {
            delete info.module;  // 对于内存模块
        }
        if (info.handle) {
            DLCLOSE(info.handle);
        }
        
        // 从活跃列表中移除
        activeModules_.erase(name);
        modules_.erase(it);
    }
}

// ==================== 集成函数实现 ====================

namespace integration {

static bool initialized = false;

// 外部函数声明
void initializeBuiltinModules();

void initialize() {
    if (initialized) return;
    
    // 初始化内置模块
    initializeBuiltinModules();
    
    initialized = true;
}

bool processImport(const std::string& moduleName, const std::string& path) {
    auto& processor = CJmodProcessor::getInstance();
    
    // 检查是否是内置模块
    if (path.find("builtin:") == 0) {
        // 内置模块已经在初始化时注册
        // 只需要确保它被激活
        if (processor.getLoadedModules().empty()) {
            // 如果还没有任何模块，重新初始化
            initialize();
        }
        return true;
    }
    
    // 如果提供了路径，加载外部模块
    if (!path.empty()) {
        return processor.loadModule(path);
    }
    
    return false;
}

} // namespace integration

} // namespace cjmod
} // namespace chtl