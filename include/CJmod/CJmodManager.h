#ifndef CHTL_CJMOD_MANAGER_H
#define CHTL_CJMOD_MANAGER_H

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include "CJmodLoader.h"
#include "Node/Node.h"

namespace chtl {

// 前向声明
class StandardParser;
class WebGenerator;
class CJmodTransformer;
class CJmodRegistry;

// CJmod 扩展接口
class ICJmodExtension {
public:
    virtual ~ICJmodExtension() = default;
    
    // 解析时钩子
    virtual void onParse(StandardParser* parser) {}
    
    // AST 转换钩子
    virtual void transformAST(std::shared_ptr<Node> ast) {}
    
    // 代码生成钩子
    virtual void onGenerate(WebGenerator* generator) {}
    
    // 获取运行时代码
    virtual std::string getRuntimeCode() const { return ""; }
};

// CJmod 管理器（单例模式）
class CJmodManager {
public:
    static CJmodManager& getInstance();
    
    // 初始化
    void initialize();
    
    // 模块管理
    bool loadModule(const std::string& modulePath);
    bool loadModuleFromPackage(const std::string& packageName, const std::string& version = "latest");
    void unloadModule(const std::string& moduleName);
    
    // 注册扩展
    void registerExtension(const std::string& moduleName, std::unique_ptr<ICJmodExtension> extension);
    
    // 获取扩展
    ICJmodExtension* getExtension(const std::string& moduleName);
    std::vector<ICJmodExtension*> getAllExtensions();
    
    // 处理导入
    void processImports(const std::vector<std::string>& imports);
    
    // 转换脚本
    std::string transformScript(const std::string& script, const std::string& context = "");
    
    // 生成运行时
    std::string generateCombinedRuntime();
    
    // 模块查询
    bool hasModule(const std::string& name) const;
    std::vector<std::string> getLoadedModules() const;
    
    // 配置
    void setModulePath(const std::string& path);
    void setRegistry(const std::string& registryUrl);
    
private:
    CJmodManager() = default;
    ~CJmodManager() = default;
    CJmodManager(const CJmodManager&) = delete;
    CJmodManager& operator=(const CJmodManager&) = delete;
    
    std::unique_ptr<CJmodLoader> loader_;
    std::unique_ptr<CJmodRegistry> registry_;
    std::unique_ptr<CJmodTransformer> transformer_;
    
    std::map<std::string, std::unique_ptr<ICJmodExtension>> extensions_;
    std::map<std::string, CJmodDefinition> loadedModules_;
    
    std::string modulePath_;
    std::string registryUrl_;
    
    // 内部方法
    std::unique_ptr<ICJmodExtension> createExtension(const CJmodDefinition& module);
    bool downloadModule(const std::string& packageName, const std::string& version);
};

} // namespace chtl

#endif // CHTL_CJMOD_MANAGER_H