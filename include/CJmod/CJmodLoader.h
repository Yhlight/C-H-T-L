#ifndef CHTL_CJMOD_LOADER_H
#define CHTL_CJMOD_LOADER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "Node/Node.h"

namespace chtl {

// CJmod 扩展方法定义
struct CJmodMethod {
    std::string name;
    std::string implementation;
    std::vector<std::string> parameters;
};

// CJmod 操作符定义
struct CJmodOperator {
    std::string symbol;
    std::string implementation;
    int precedence;
};

// CJmod 定义
struct CJmodDefinition {
    std::string name;
    std::string version;
    std::string description;
    
    // 扩展
    std::vector<CJmodMethod> methods;
    std::vector<CJmodOperator> operators;
    
    // 运行时代码
    std::string initCode;
    std::string runtimeCode;
    
    // 依赖
    std::map<std::string, std::string> dependencies;
};

// CJmod 加载器
class CJmodLoader {
public:
    CJmodLoader();
    ~CJmodLoader();
    
    // 加载模块
    bool loadModule(const std::string& modulePath);
    bool loadModuleFromString(const std::string& moduleContent);
    
    // 注册模块
    void registerModule(const CJmodDefinition& module);
    
    // 查询模块
    bool hasModule(const std::string& name) const;
    const CJmodDefinition* getModule(const std::string& name) const;
    
    // 处理脚本中的 CJmod 扩展
    std::string processScript(const std::string& script) const;
    
    // 生成运行时代码
    std::string generateRuntimeCode() const;
    
    // 获取所有已加载的模块
    std::vector<std::string> getLoadedModules() const;
    
private:
    std::map<std::string, CJmodDefinition> modules_;
    
    // 解析模块定义
    CJmodDefinition parseModuleDefinition(const std::string& content);
    
    // 转换扩展语法
    std::string transformExtendedSyntax(const std::string& script) const;
};

} // namespace chtl

#endif // CHTL_CJMOD_LOADER_H