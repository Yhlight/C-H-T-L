#ifndef CHTL_CMOD_INFO_H
#define CHTL_CMOD_INFO_H

#include <string>
#include <vector>
#include <unordered_map>

namespace chtl {

// CMOD模块信息
struct CmodInfo {
    // [Info]块中的基本信息
    std::string name;
    std::string version;
    std::string description;
    std::string author;
    std::string license;
    std::string dependencies;
    std::string category;
    std::string minCHTLVersion;
    std::string maxCHTLVersion;
    
    // 导出信息
    std::vector<std::string> exportedStyles;
    std::vector<std::string> exportedElements;
    std::vector<std::string> exportedVars;
    
    // 子模块信息
    std::vector<std::string> submodules;
    
    // 文件路径信息
    std::string modulePath;      // 模块根目录路径
    std::string infoFilePath;    // info文件路径
    
    // 验证信息是否有效
    bool isValid() const {
        return !name.empty() && !version.empty();
    }
    
    // 获取完整的模块名（包含父模块路径）
    std::string getFullName(const std::string& parentPath = "") const {
        if (parentPath.empty()) {
            return name;
        }
        return parentPath + "." + name;
    }
};

// CMOD文件结构
struct CmodStructure {
    std::string rootPath;           // 模块根目录
    std::string srcPath;            // src目录路径
    std::string infoPath;           // info目录路径
    std::string mainModuleFile;     // 主模块文件路径
    std::string infoFile;           // 信息文件路径
    std::vector<CmodStructure> submodules;  // 子模块结构
    
    // 验证结构是否符合CMOD标准
    bool isValid() const;
    
    // 获取模块名称（从路径推导）
    std::string getModuleName() const;
};

} // namespace chtl

#endif // CHTL_CMOD_INFO_H