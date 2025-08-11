#ifndef CHTL_CJMOD_LOADER_H
#define CHTL_CJMOD_LOADER_H

#include <string>
#include <memory>
#include <unordered_map>
#include "CJmod/CJmodCorrect.h"

namespace chtl {
namespace cjmod {

// CJmod 加载器
class CJmodLoader {
public:
    static CJmodLoader& getInstance();
    
    // 加载 CJmod 模块
    std::shared_ptr<ICJmod> loadModule(const std::string& path);
    
    // 注册内置模块
    void registerBuiltinModule(const std::string& name, std::shared_ptr<ICJmod> module);
    
    // 初始化内置模块
    void initializeBuiltins();
    
private:
    CJmodLoader() = default;
    
    // 解析模块路径
    std::pair<std::string, std::string> parseModulePath(const std::string& path);
    
    // 从文件加载模块
    std::shared_ptr<ICJmod> loadFromFile(const std::string& filePath);
    
    // 从包管理器加载模块
    std::shared_ptr<ICJmod> loadFromPackage(const std::string& packageName);
    
    // 内置模块映射
    std::unordered_map<std::string, std::shared_ptr<ICJmod>> builtinModules_;
    
    // 已加载模块缓存
    std::unordered_map<std::string, std::shared_ptr<ICJmod>> moduleCache_;
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_LOADER_H