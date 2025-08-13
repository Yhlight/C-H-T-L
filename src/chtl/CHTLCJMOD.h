#ifndef CHTL_CJMOD_H
#define CHTL_CJMOD_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <functional>
#include "CHTLContext.h"
#include "CHTLCMOD.h"

namespace chtl {

// 前向声明
class CHTLJSContext;
class ScriptProcessor;

// CJMOD扩展接口
class ICJMODExtension {
public:
    virtual ~ICJMODExtension() = default;
    
    // 获取扩展信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::string getDescription() const = 0;
    
    // 初始化扩展
    virtual bool initialize(std::shared_ptr<CHTLJSContext> context) = 0;
    
    // 处理脚本（在解析前）
    virtual std::string preprocess(const std::string& script) = 0;
    
    // 转换脚本（在解析后）
    virtual std::string transform(const std::string& script) = 0;
    
    // 注册自定义函数
    virtual void registerFunctions(std::shared_ptr<ScriptProcessor> processor) = 0;
    
    // 清理
    virtual void cleanup() = 0;
};

// CJMOD扩展工厂
using CJMODExtensionFactory = std::function<std::unique_ptr<ICJMODExtension>()>;

// CJMOD模块
class CJMODModule : public std::enable_shared_from_this<CJMODModule> {
private:
    std::string name;
    std::filesystem::path rootPath;
    CMODInfo info;  // 使用基础的CMODInfo，不扩展
    std::map<std::string, std::shared_ptr<CJMODModule>> subModules;
    std::vector<std::filesystem::path> sourceFiles;
    bool isSubModule;
    std::weak_ptr<CJMODModule> parent;
    
    // 加载的扩展
    std::vector<std::unique_ptr<ICJMODExtension>> extensions;
    
    // 动态库句柄
    void* libraryHandle = nullptr;
    
public:
    CJMODModule(const std::string& name, const std::filesystem::path& path, bool isSub = false);
    ~CJMODModule();
    
    // 加载模块
    bool load();
    bool loadFromDirectory(const std::filesystem::path& dir);
    bool loadFromCJMODFile(const std::filesystem::path& cjmodFile, const std::filesystem::path& target);
    
    // 加载扩展
    bool loadExtensions();
    bool loadExtensionFromFile(const std::filesystem::path& soFile);
    
    // 编译C++源码
    bool compileSources();
    
    // 信息加载（只需要基本的Info）
    bool loadInfo(const std::filesystem::path& infoFile);
    
    // 获取扩展
    const std::vector<std::unique_ptr<ICJMODExtension>>& getExtensions() const { return extensions; }
    ICJMODExtension* getExtension(const std::string& name) const;
    
    // 子模块管理
    void addSubModule(std::shared_ptr<CJMODModule> subModule);
    std::shared_ptr<CJMODModule> getSubModule(const std::string& name) const;
    std::vector<std::string> getSubModuleNames() const;
    
    // 获取器
    const std::string& getName() const { return name; }
    const CMODInfo& getInfo() const { return info; }
    const std::filesystem::path& getRootPath() const { return rootPath; }
    std::string getFullName() const;
    
private:
    // 库路径
    std::filesystem::path libraryPath;
    
    // 二进制解包（备用方案）
    bool unpackBinary(const std::filesystem::path& cjmodFile, const std::filesystem::path& targetDir);
};

// CJMOD管理器
class CJMODManager {
private:
    std::unordered_map<std::string, std::shared_ptr<CJMODModule>> loadedModules;
    std::vector<std::filesystem::path> modulePaths;
    std::shared_ptr<CHTLContext> context;
    std::shared_ptr<CHTLJSContext> jsContext;
    
    // 扩展工厂注册表
    std::unordered_map<std::string, CJMODExtensionFactory> extensionFactories;
    
    // 编译器设置
    std::string compiler = "g++";
    std::vector<std::string> compilerFlags = {"-std=c++17", "-fPIC", "-shared"};
    std::vector<std::string> includePaths;
    std::vector<std::string> libraryPaths;
    
public:
    CJMODManager(std::shared_ptr<CHTLContext> ctx);
    
    // 设置JS上下文
    void setJSContext(std::shared_ptr<CHTLJSContext> jsCtx) { jsContext = jsCtx; }
    
    // 路径管理
    void addModulePath(const std::filesystem::path& path);
    void addIncludePath(const std::filesystem::path& path);
    void addLibraryPath(const std::filesystem::path& path);
    
    // 模块加载
    std::shared_ptr<CJMODModule> loadModule(const std::string& moduleName);
    std::shared_ptr<CJMODModule> loadModuleFromPath(const std::filesystem::path& path);
    
    // 扩展注册
    void registerExtensionFactory(const std::string& name, CJMODExtensionFactory factory);
    std::unique_ptr<ICJMODExtension> createExtension(const std::string& name);
    
    // 应用扩展到脚本处理
    std::string preprocessScript(const std::string& script);
    std::string transformScript(const std::string& script);
    
    // 编译设置
    void setCompiler(const std::string& comp) { compiler = comp; }
    void addCompilerFlag(const std::string& flag) { compilerFlags.push_back(flag); }
    
    // 清理
    void clear();
};

// CJMOD构建器
class CJMODBuilder {
private:
    std::filesystem::path sourcePath;
    std::filesystem::path outputPath;
    CMODInfo moduleInfo;
    std::shared_ptr<CHTLContext> context;
    
public:
    CJMODBuilder(std::shared_ptr<CHTLContext> ctx);
    
    // 设置路径
    void setSourcePath(const std::filesystem::path& path) { sourcePath = path; }
    void setOutputPath(const std::filesystem::path& path) { outputPath = path; }
    
    // 构建模块
    bool build(const std::string& moduleName);
    bool buildFromTemplate(const std::string& moduleName, const std::string& templateType);
    
    // 编译C++代码
    bool compile(const std::filesystem::path& srcDir, const std::filesystem::path& outputFile);
    
    // 打包
    bool package(const std::filesystem::path& moduleDir, const std::filesystem::path& outputFile);
    
    // 验证
    bool validate(const std::filesystem::path& moduleDir);
};

// CJMOD处理器 - 与ScriptProcessor集成
class CJMODProcessor {
private:
    CJMODManager& manager;
    std::shared_ptr<ScriptProcessor> scriptProcessor;
    
public:
    CJMODProcessor(CJMODManager& mgr, std::shared_ptr<ScriptProcessor> processor)
        : manager(mgr), scriptProcessor(processor) {}
    
    // 加载CJMOD扩展
    bool loadCJMODExtensions(const std::string& moduleName);
    
    // 应用扩展
    bool applyExtensions(std::shared_ptr<CJMODModule> module);
    
    // 注册扩展函数
    void registerExtensionFunctions(ICJMODExtension* extension);
};

// CJMOD工具函数
namespace CJMODHelper {
    // 创建扩展模板
    bool createExtensionTemplate(const std::filesystem::path& path, 
                                const std::string& moduleName,
                                const std::string& extensionType);
    
    // 生成扩展骨架代码
    std::string generateExtensionSkeleton(const std::string& className,
                                         const std::string& extensionType);
    
    // 生成CMakeLists.txt
    std::string generateCMakeFile(const std::string& moduleName,
                                 const std::vector<std::string>& sources);
    
    // 验证C++代码
    bool validateCppCode(const std::filesystem::path& sourceFile);
    
    // 提取导出符号
    std::vector<std::string> extractExportedSymbols(const std::filesystem::path& soFile);
}

// 标准CJMOD扩展基类
class CJMODExtensionBase : public ICJMODExtension {
protected:
    std::string name;
    std::string version;
    std::string description;
    std::shared_ptr<CHTLJSContext> context;
    
public:
    CJMODExtensionBase(const std::string& n, const std::string& v, const std::string& d)
        : name(n), version(v), description(d) {}
    
    std::string getName() const override { return name; }
    std::string getVersion() const override { return version; }
    std::string getDescription() const override { return description; }
    
    bool initialize(std::shared_ptr<CHTLJSContext> ctx) override {
        context = ctx;
        return true;
    }
    
    // 默认实现
    std::string preprocess(const std::string& script) override { return script; }
    std::string transform(const std::string& script) override { return script; }
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {}
    void cleanup() override {}
};

// 导出宏（用于动态库）
#define CJMOD_EXPORT extern "C"
#define CJMOD_EXTENSION_FACTORY(className) \
    CJMOD_EXPORT std::unique_ptr<chtl::ICJMODExtension> createExtension() { \
        return std::make_unique<className>(); \
    }

} // namespace chtl

#endif // CHTL_CJMOD_H