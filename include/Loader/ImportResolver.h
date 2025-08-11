#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "Node/Import.h"

namespace chtl {

// 导入解析结果
struct ImportResolveResult {
    bool success = false;
    std::string resolvedPath;       // 解析后的完整路径
    std::string fileExtension;      // 文件扩展名
    bool isRelative = false;        // 是否为相对路径
    bool isWildcard = false;        // 是否为通配符导入
    std::vector<std::string> wildcardResults;  // 通配符匹配的所有文件
    std::string errorMessage;       // 错误信息
};

class ImportResolver {
public:
    ImportResolver();
    ~ImportResolver() = default;
    
    // 解析导入路径
    ImportResolveResult resolve(const std::string& importPath, 
                               Import::ImportType type,
                               const std::string& currentFilePath);
    
    // 设置项目根目录
    void setProjectRoot(const std::string& root) { projectRoot_ = root; }
    
    // 获取项目根目录
    const std::string& getProjectRoot() const { return projectRoot_; }
    
    // 设置官方模块路径
    void setOfficialModulePath(const std::string& path) { officialModulePath_ = path; }
    
private:
    // 路径类型
    enum class PathType {
        NAME_ONLY,                    // 只有名称，没有后缀名
        NAME_WITH_EXT,               // 有具体的后缀名
        SPECIFIC_PATH_WITH_FILE,     // 具体路径（包含文件信息）
        SPECIFIC_PATH_WITHOUT_FILE   // 具体路径（不包含文件信息）
    };
    
    // 判断导入类型
    bool isResourceImport(Import::ImportType type) const;
    bool isChtlImport(Import::ImportType type) const;
    
    // 解析不同类型的导入
    ImportResolveResult resolveResourceImport(const std::string& path,
                                            Import::ImportType type,
                                            const std::filesystem::path& currentDir);
    
    ImportResolveResult resolveChtlImport(const std::string& path,
                                        Import::ImportType type,
                                        const std::filesystem::path& currentDir);
    
    ImportResolveResult resolveCJmodImport(const std::string& path,
                                         const std::filesystem::path& currentDir);
    
    // 模块名称解析
    ImportResolveResult resolveModuleName(const std::string& name,
                                        Import::ImportType type,
                                        const std::filesystem::path& currentDir,
                                        bool includeChtl);
    
    ImportResolveResult resolveModuleNameWithExt(const std::string& name,
                                               Import::ImportType type,
                                               const std::filesystem::path& currentDir,
                                               bool includeChtl);
    
    // 判断路径类型
    PathType getPathType(const std::string& path) const;
    
    // 解析具体路径
    ImportResolveResult resolveSpecificPath(const std::string& path,
                                          Import::ImportType type);
    
    // 通配符和子模块导入
    bool isWildcardImport(const std::string& path) const;
    bool isSubmoduleImport(const std::string& path) const;
    
    ImportResolveResult resolveWildcardImport(const std::string& pattern,
                                            Import::ImportType type,
                                            const std::filesystem::path& currentDir);
    
    ImportResolveResult resolveSubmoduleImport(const std::string& path,
                                             Import::ImportType type,
                                             const std::filesystem::path& currentDir);
    
    // 辅助方法
    std::string getDefaultExtension(Import::ImportType type) const;
    bool fileExists(const std::string& path) const;
    std::string normalizePath(const std::string& path) const;
    bool isAbsolutePath(const std::string& path) const;
    std::string getExtension(const std::string& path) const;
    bool hasExtension(const std::string& path) const;
    std::string findFileInDirectory(const std::string& directory,
                                   const std::string& filename,
                                   const std::string& extension) const;
    std::string resolveRelativePath(const std::string& basePath,
                                   const std::string& relativePath) const;
    bool validateExtension(const std::string& extension,
                         Import::ImportType type) const;
    
    // 静态扩展名映射表
    static const std::unordered_map<Import::ImportType, std::vector<std::string>> EXTENSION_MAP;
    
    // 成员变量
    std::string projectRoot_;
    std::filesystem::path officialModulePath_;  // 官方模块路径
};

} // namespace chtl