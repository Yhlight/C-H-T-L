// WebGenerator CJmod 集成部分
#include "Generator/WebGenerator.h"
#include "CJmod/CJmodProcessor.h"
#include <set>

namespace chtl {

// 修改 processJavaScriptEnhancements 方法
std::string WebGenerator::processJavaScriptEnhancementsWithCJmod(const std::string& code) {
    // 获取当前活跃的 CJmod 模块
    std::set<std::string> activeModules;
    
    // 从上下文获取导入的模块
    if (currentContext_ && currentContext_->hasCJmodImports()) {
        activeModules = currentContext_->getCJmodImports();
    }
    
    // 使用 CJmod 处理器
    auto& processor = cjmod::CJmodProcessor::getInstance();
    std::string processedCode = processor.processJavaScript(code, activeModules);
    
    // 如果没有 CJmod，回退到原始处理
    if (activeModules.empty()) {
        return processJavaScriptEnhancements(processedCode);
    }
    
    return processedCode;
}

// 生成 CJmod 运行时
void WebGenerator::generateCJmodRuntime() {
    if (!currentContext_ || !currentContext_->hasCJmodImports()) {
        return;
    }
    
    auto& processor = cjmod::CJmodProcessor::getInstance();
    std::set<std::string> activeModules = currentContext_->getCJmodImports();
    
    std::string runtime = processor.generateRuntime(activeModules);
    
    // 在所有用户代码之前注入运行时
    jsCollector_.prependLine(runtime);
}

// 示例：如何在 main.cpp 中注册模块
void registerBuiltinCJmods() {
    auto& processor = cjmod::CJmodProcessor::getInstance();
    
    // 注册内置模块工厂
    processor.registerFactory(std::make_unique<cjmod::ReactiveModuleFactory>());
    
    // 直接注册模块实例
    processor.registerModule(std::make_unique<cjmod::ReactiveModule>());
    processor.registerModule(std::make_unique<cjmod::EnhancedSelfReference>());
}

// 动态加载 CJmod（从共享库）
#ifdef __linux__
#include <dlfcn.h>

bool loadCJmodFromLibrary(const std::string& libraryPath) {
    void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load CJmod library: " << dlerror() << std::endl;
        return false;
    }
    
    // 查找注册函数
    typedef void (*RegisterFunc)();
    RegisterFunc registerModule = (RegisterFunc) dlsym(handle, "registerCJmod");
    
    if (!registerModule) {
        std::cerr << "Cannot find registerCJmod function: " << dlerror() << std::endl;
        dlclose(handle);
        return false;
    }
    
    // 调用注册函数
    registerModule();
    return true;
}
#endif

} // namespace chtl