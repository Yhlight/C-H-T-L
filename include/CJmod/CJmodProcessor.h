#ifndef CHTL_CJMOD_PROCESSOR_H
#define CHTL_CJMOD_PROCESSOR_H

#include "CJmodCore.h"
#include <memory>
#include <vector>
#include <map>
#include <dlfcn.h>  // 动态加载

namespace chtl {
namespace cjmod {

// 内部实现类声明
class ScanContextImpl;
class GenerateContextImpl;

// 语法规则内部表示
struct SyntaxRuleInternal {
    std::string name;
    int priority;
    std::string pattern;
    SyntaxBuilder::ScanFunc scanFunc;
    SyntaxBuilder::GenerateFunc generateFunc;
    SyntaxBuilder::ValidateFunc validateFunc;
    
    // 从 SyntaxBuilder 创建
    static std::unique_ptr<SyntaxRuleInternal> fromBuilder(const SyntaxBuilder* builder);
};

// CJmod 处理器 - 核心引擎
class CJmodProcessor {
public:
    // 单例模式
    static CJmodProcessor& getInstance();
    
    // 加载模块
    bool loadModule(const std::string& modulePath);
    bool loadModuleFromMemory(std::unique_ptr<CJmodModule> module);
    
    // 处理 JavaScript 代码
    std::string processScript(const std::string& script, 
                            const std::vector<std::string>& activeModules = {});
    
    // 获取运行时代码
    std::string getRuntimeCode(const std::vector<std::string>& modules = {});
    
    // 模块管理
    std::vector<std::string> getLoadedModules() const;
    bool isModuleLoaded(const std::string& name) const;
    void unloadModule(const std::string& name);
    void unloadAllModules();
    
    // 错误处理
    const std::vector<std::string>& getLastErrors() const { return lastErrors_; }
    const std::vector<std::string>& getLastWarnings() const { return lastWarnings_; }
    
private:
    CJmodProcessor() = default;
    ~CJmodProcessor();
    
    // 禁用拷贝
    CJmodProcessor(const CJmodProcessor&) = delete;
    CJmodProcessor& operator=(const CJmodProcessor&) = delete;
    
    // 内部处理
    std::string applySyntaxRules(const std::string& code, 
                               const std::vector<SyntaxRuleInternal*>& rules);
    
    void collectActiveRules(const std::vector<std::string>& moduleNames,
                          std::vector<SyntaxRuleInternal*>& outRules);
    
    // 模块存储
    struct ModuleInfo {
        std::unique_ptr<CJmodModule> module;
        std::vector<std::unique_ptr<SyntaxRuleInternal>> rules;
        RuntimeBuilder runtime;
        void* dlHandle = nullptr;  // 动态库句柄
    };
    
    std::map<std::string, std::unique_ptr<ModuleInfo>> modules_;
    
    // 状态管理
    StateManager globalState_;
    
    // 错误信息
    std::vector<std::string> lastErrors_;
    std::vector<std::string> lastWarnings_;
    
    // 动态加载
    void* loadDynamicLibrary(const std::string& path);
    void unloadDynamicLibrary(void* handle);
};

// 辅助函数 - 集成到 CHTL 编译器
namespace integration {
    
    // 初始化 CJmod 系统
    void initialize();
    
    // 加载标准模块
    void loadStandardModules();
    
    // 处理 Import 声明
    bool processImport(const std::string& moduleName, const std::string& source);
    
    // 获取模块信息
    struct ModuleMetadata {
        std::string name;
        std::string version;
        std::string description;
        std::string author;
        std::vector<std::string> syntaxRules;
        std::vector<std::string> dependencies;
    };
    
    ModuleMetadata getModuleMetadata(const std::string& moduleName);
}

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_PROCESSOR_H