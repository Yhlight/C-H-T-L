#ifndef CHTL_IMPORT_RESOLVER_H
#define CHTL_IMPORT_RESOLVER_H

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include "Node/Import.h"

namespace chtl {

namespace fs = std::filesystem;

// 导入解析结果
struct ImportResolveResult {
    bool success = false;
    std::string resolvedPath;      // 解析后的完整路径
    std::string errorMessage;       // 错误信息
    bool isRelative = true;         // 是否为相对路径
    std::string fileExtension;      // 文件扩展名
};

// 导入路径解析器
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
    
private:
    // 根据导入类型获取默认扩展名
    std::string getDefaultExtension(Import::ImportType type) const;
    
    // 检查文件是否存在
    bool fileExists(const std::string& path) const;
    
    // 规范化路径
    std::string normalizePath(const std::string& path) const;
    
    // 判断是否为绝对路径
    bool isAbsolutePath(const std::string& path) const;
    
    // 获取文件扩展名
    std::string getExtension(const std::string& path) const;
    
    // 判断是否有扩展名
    bool hasExtension(const std::string& path) const;
    
    // 在目录中查找文件
    std::string findFileInDirectory(const std::string& directory,
                                   const std::string& filename,
                                   const std::string& extension) const;
    
    // 处理相对路径
    std::string resolveRelativePath(const std::string& basePath,
                                   const std::string& relativePath) const;
    
    // 验证文件扩展名是否匹配导入类型
    bool validateExtension(const std::string& extension,
                          Import::ImportType type) const;
    
private:
    std::string projectRoot_;       // 项目根目录
    
    // 支持的文件扩展名映射
    static const std::unordered_map<Import::ImportType, std::vector<std::string>> EXTENSION_MAP;
};

} // namespace chtl

#endif // CHTL_IMPORT_RESOLVER_H