#include "CJmod/CJmodProcessor.h"
#include "CJmod/CJmodContextImpl.cpp"  // 包含上下文实现
#include <algorithm>
#include <regex>
#include <dlfcn.h>
#include <iostream>

namespace chtl {
namespace cjmod {

// SyntaxRuleInternal 实现
std::unique_ptr<SyntaxRuleInternal> SyntaxRuleInternal::fromBuilder(const SyntaxBuilder* builder) {
    auto rule = std::make_unique<SyntaxRuleInternal>();
    rule->name = builder->name_;
    rule->priority = builder->priority_;
    rule->pattern = builder->pattern_;
    rule->scanFunc = builder->scanFunc_;
    rule->generateFunc = builder->generateFunc_;
    rule->validateFunc = builder->validateFunc_;
    return rule;
}

// CJmodProcessor 实现
CJmodProcessor& CJmodProcessor::getInstance() {
    static CJmodProcessor instance;
    return instance;
}

CJmodProcessor::~CJmodProcessor() {
    unloadAllModules();
}

bool CJmodProcessor::loadModule(const std::string& modulePath) {
    // 动态加载 .so/.dll 文件
    void* handle = loadDynamicLibrary(modulePath);
    if (!handle) {
        lastErrors_.push_back("Failed to load module: " + modulePath);
        return false;
    }
    
    // 获取创建函数
    typedef CJmodModule* (*CreateFunc)();
    CreateFunc create = (CreateFunc)dlsym(handle, "cjmod_create");
    
    if (!create) {
        lastErrors_.push_back("Module missing cjmod_create function: " + modulePath);
        dlclose(handle);
        return false;
    }
    
    // 创建模块实例
    CJmodModule* modulePtr = create();
    if (!modulePtr) {
        lastErrors_.push_back("Failed to create module instance: " + modulePath);
        dlclose(handle);
        return false;
    }
    
    // 初始化模块
    modulePtr->initialize();
    
    // 存储模块信息
    auto info = std::make_unique<ModuleInfo>();
    info->module = std::unique_ptr<CJmodModule>(modulePtr);
    info->dlHandle = handle;
    
    // 提取语法规则
    for (const auto& builder : info->module->syntaxBuilders_) {
        info->rules.push_back(SyntaxRuleInternal::fromBuilder(builder.get()));
    }
    
    // 复制运行时
    info->runtime = info->module->runtimeBuilder_;
    
    std::string moduleName = info->module->getName();
    modules_[moduleName] = std::move(info);
    
    return true;
}

bool CJmodProcessor::loadModuleFromMemory(std::unique_ptr<CJmodModule> module) {
    if (!module) return false;
    
    // 初始化模块
    module->initialize();
    
    // 存储模块信息
    auto info = std::make_unique<ModuleInfo>();
    std::string moduleName = module->getName();
    
    // 提取语法规则
    for (const auto& builder : module->syntaxBuilders_) {
        info->rules.push_back(SyntaxRuleInternal::fromBuilder(builder.get()));
    }
    
    // 复制运行时
    info->runtime = module->runtimeBuilder_;
    
    info->module = std::move(module);
    info->dlHandle = nullptr;  // 内存加载，无动态库句柄
    
    modules_[moduleName] = std::move(info);
    
    return true;
}

std::string CJmodProcessor::processScript(const std::string& script, 
                                        const std::vector<std::string>& activeModules) {
    lastErrors_.clear();
    lastWarnings_.clear();
    
    // 收集要使用的规则
    std::vector<SyntaxRuleInternal*> rules;
    collectActiveRules(activeModules.empty() ? getLoadedModules() : activeModules, rules);
    
    // 应用语法规则
    return applySyntaxRules(script, rules);
}

std::string CJmodProcessor::getRuntimeCode(const std::vector<std::string>& modules) {
    std::vector<std::string> targetModules = modules.empty() ? getLoadedModules() : modules;
    
    // 合并所有模块的运行时
    RuntimeBuilder combined;
    
    for (const auto& moduleName : targetModules) {
        auto it = modules_.find(moduleName);
        if (it != modules_.end()) {
            // 合并运行时代码
            const RuntimeBuilder& moduleRuntime = it->second->runtime;
            
            // TODO: 实现 RuntimeBuilder 的合并逻辑
            // 这里需要合并 functions_, classes_, prototypes_, globals_, initCode_
            // 暂时简化处理
        }
    }
    
    return combined.generate();
}

std::vector<std::string> CJmodProcessor::getLoadedModules() const {
    std::vector<std::string> names;
    for (const auto& [name, info] : modules_) {
        names.push_back(name);
    }
    return names;
}

bool CJmodProcessor::isModuleLoaded(const std::string& name) const {
    return modules_.find(name) != modules_.end();
}

void CJmodProcessor::unloadModule(const std::string& name) {
    auto it = modules_.find(name);
    if (it != modules_.end()) {
        if (it->second->dlHandle) {
            unloadDynamicLibrary(it->second->dlHandle);
        }
        modules_.erase(it);
    }
}

void CJmodProcessor::unloadAllModules() {
    for (auto& [name, info] : modules_) {
        if (info->dlHandle) {
            unloadDynamicLibrary(info->dlHandle);
        }
    }
    modules_.clear();
}

std::string CJmodProcessor::applySyntaxRules(const std::string& code, 
                                           const std::vector<SyntaxRuleInternal*>& rules) {
    // 按优先级排序规则
    std::vector<SyntaxRuleInternal*> sortedRules = rules;
    std::sort(sortedRules.begin(), sortedRules.end(), 
              [](const SyntaxRuleInternal* a, const SyntaxRuleInternal* b) {
                  return a->priority > b->priority;
              });
    
    // 创建扫描上下文
    auto scanCtx = std::make_unique<ScanContextImpl>(code, &globalState_);
    
    // 收集所有切割点
    std::vector<std::pair<ScanResult, SyntaxRuleInternal*>> allCuts;
    
    for (auto* rule : sortedRules) {
        std::vector<ScanResult> cuts;
        
        if (rule->scanFunc) {
            // 使用自定义扫描函数
            cuts = rule->scanFunc(scanCtx.get());
        } else if (!rule->pattern.empty()) {
            // 使用正则表达式扫描
            std::regex regex(rule->pattern);
            auto it = std::sregex_iterator(code.begin(), code.end(), regex);
            auto end = std::sregex_iterator();
            
            for (; it != end; ++it) {
                if (scanCtx->isProcessed(it->position())) continue;
                
                ScanResult result;
                result.start = it->position();
                result.end = result.start + it->length();
                result.content = it->str();
                
                // 填充捕获组
                for (size_t i = 1; i < it->size(); i++) {
                    result.captures[std::to_string(i)] = (*it)[i];
                }
                
                if (!rule->validateFunc || rule->validateFunc(result)) {
                    cuts.push_back(result);
                    scanCtx->markProcessed(result.start, result.end);
                }
            }
        }
        
        // 关联规则和切割点
        for (auto& cut : cuts) {
            allCuts.push_back({cut, rule});
        }
    }
    
    // 按位置排序切割点
    std::sort(allCuts.begin(), allCuts.end(), 
              [](const auto& a, const auto& b) {
                  return a.first.start < b.first.start;
              });
    
    // 创建生成上下文
    RuntimeBuilder runtime;
    auto genCtx = std::make_unique<GenerateContextImpl>(&runtime, &globalState_);
    
    // 生成最终代码
    std::string result;
    size_t lastPos = 0;
    
    for (const auto& [cut, rule] : allCuts) {
        // 添加未处理的部分
        if (cut.start > lastPos) {
            result += code.substr(lastPos, cut.start - lastPos);
        }
        
        // 应用转换
        if (rule->generateFunc) {
            result += rule->generateFunc(cut, genCtx.get());
        } else {
            result += cut.content;  // 无转换，保持原样
        }
        
        lastPos = cut.end;
    }
    
    // 添加剩余部分
    if (lastPos < code.length()) {
        result += code.substr(lastPos);
    }
    
    // 处理错误和警告
    for (const auto& [msg, context] : genCtx->getErrors()) {
        lastErrors_.push_back(msg + " in: " + context);
    }
    
    for (const auto& [msg, context] : genCtx->getWarnings()) {
        lastWarnings_.push_back(msg + " in: " + context);
    }
    
    return result;
}

void CJmodProcessor::collectActiveRules(const std::vector<std::string>& moduleNames,
                                      std::vector<SyntaxRuleInternal*>& outRules) {
    for (const auto& moduleName : moduleNames) {
        auto it = modules_.find(moduleName);
        if (it != modules_.end()) {
            for (const auto& rule : it->second->rules) {
                outRules.push_back(rule.get());
            }
        }
    }
}

void* CJmodProcessor::loadDynamicLibrary(const std::string& path) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        lastErrors_.push_back("dlopen failed: " + std::string(dlerror()));
    }
    return handle;
}

void CJmodProcessor::unloadDynamicLibrary(void* handle) {
    if (handle) {
        dlclose(handle);
    }
}

// 集成函数实现
namespace integration {

void initialize() {
    // 初始化 CJmod 系统
    auto& processor = CJmodProcessor::getInstance();
    
    // 加载内置模块
    loadStandardModules();
}

void loadStandardModules() {
    // 这里可以加载标准库模块
    // 例如：@cjmod/reactive, @cjmod/animate, @cjmod/delegate 等
}

bool processImport(const std::string& moduleName, const std::string& source) {
    auto& processor = CJmodProcessor::getInstance();
    
    if (source == "builtin") {
        // 内置模块，已经预加载
        return processor.isModuleLoaded(moduleName);
    } else if (source.find("file:") == 0) {
        // 从文件加载
        std::string path = source.substr(5);
        return processor.loadModule(path);
    } else if (source.find("npm:") == 0) {
        // 从 npm 加载（需要额外实现）
        // TODO: 实现 npm 模块加载
        return false;
    }
    
    return false;
}

ModuleMetadata getModuleMetadata(const std::string& moduleName) {
    auto& processor = CJmodProcessor::getInstance();
    ModuleMetadata meta;
    
    if (processor.isModuleLoaded(moduleName)) {
        // TODO: 从模块中提取元数据
        // 这需要在 ModuleInfo 中存储更多信息
    }
    
    return meta;
}

} // namespace integration

} // namespace cjmod
} // namespace chtl