#include "Loader/ImportResolver.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

namespace chtl {

// 扩展名映射表
const std::unordered_map<Import::ImportType, std::vector<std::string>> ImportResolver::EXTENSION_MAP = {
    {Import::ImportType::HTML, {".html", ".htm", ".xhtml"}},
    {Import::ImportType::CSS, {".css", ".scss", ".sass", ".less"}},
    {Import::ImportType::JS, {".js", ".mjs", ".jsx", ".ts", ".tsx"}},
    {Import::ImportType::CHTL, {".chtl", ".cmod"}},  // cmod优先
    {Import::ImportType::CUSTOM_ELEMENT, {".chtl", ".cmod"}},
    {Import::ImportType::CUSTOM_STYLE, {".chtl", ".cmod"}},
    {Import::ImportType::CUSTOM_VAR, {".chtl", ".cmod"}},
    {Import::ImportType::TEMPLATE_ELEMENT, {".chtl", ".cmod"}},
    {Import::ImportType::TEMPLATE_STYLE, {".chtl", ".cmod"}},
    {Import::ImportType::TEMPLATE_VAR, {".chtl", ".cmod"}},
    {Import::ImportType::ALL, {".chtl", ".cmod"}},
    {Import::ImportType::CJMOD, {".cjmod", ".cjmod.json", ".js"}}
};

ImportResolver::ImportResolver() {
    // 默认使用当前工作目录作为项目根目录
    projectRoot_ = fs::current_path().string();
    
    // 设置官方模块路径（编译器目录下的module文件夹）
    // 假设编译器在系统PATH中或有环境变量指定
    if (const char* compilerPath = std::getenv("CHTL_COMPILER_PATH")) {
        officialModulePath_ = fs::path(compilerPath).parent_path() / "module";
    } else {
        // 尝试从可执行文件路径推断
        officialModulePath_ = fs::current_path() / "module";
    }
}

ImportResolveResult ImportResolver::resolve(const std::string& importPath, 
                                          Import::ImportType type,
                                          const std::string& currentFilePath) {
    ImportResolveResult result;
    
    // 处理空路径
    if (importPath.empty()) {
        result.errorMessage = "Import path cannot be empty";
        return result;
    }
    
    // 获取当前文件所在目录
    fs::path currentFile(currentFilePath);
    fs::path currentDir = currentFile.parent_path();
    if (currentDir.empty()) {
        currentDir = fs::current_path();
    }
    
    // 规范化导入路径
    std::string normalizedPath = normalizePath(importPath);
    
    // 检查是否为通配符导入
    if (isWildcardImport(normalizedPath)) {
        return resolveWildcardImport(normalizedPath, type, currentDir);
    }
    
    // 检查是否为子模块导入（包含'.'但不是文件扩展名）
    if (isSubmoduleImport(normalizedPath)) {
        return resolveSubmoduleImport(normalizedPath, type, currentDir);
    }
    
    // 判断路径类型
    PathType pathType = getPathType(normalizedPath);
    
    switch (pathType) {
        case PathType::NAME_ONLY:
            // 只有名称，没有后缀名
            return resolveNameOnly(normalizedPath, type, currentDir);
            
        case PathType::NAME_WITH_EXT:
            // 有具体的后缀名
            return resolveNameWithExtension(normalizedPath, type, currentDir);
            
        case PathType::SPECIFIC_PATH_WITH_FILE:
            // 具体路径（包含文件信息）
            return resolveSpecificPath(normalizedPath, type);
            
        case PathType::SPECIFIC_PATH_WITHOUT_FILE:
            // 具体路径（不包含文件信息）
            result.errorMessage = "Path must include a file name: " + normalizedPath;
            return result;
    }
    
    result.errorMessage = "Unable to resolve import path: " + normalizedPath;
    return result;
}

ImportResolver::PathType ImportResolver::getPathType(const std::string& path) const {
    // 检查是否包含路径分隔符
    bool hasPathSep = (path.find('/') != std::string::npos || 
                       path.find('\\') != std::string::npos);
    
    if (!hasPathSep) {
        // 没有路径分隔符
        if (hasExtension(path)) {
            return PathType::NAME_WITH_EXT;
        } else {
            return PathType::NAME_ONLY;
        }
    } else {
        // 有路径分隔符
        fs::path p(path);
        if (p.filename().empty()) {
            return PathType::SPECIFIC_PATH_WITHOUT_FILE;
        } else {
            return PathType::SPECIFIC_PATH_WITH_FILE;
        }
    }
}

ImportResolveResult ImportResolver::resolveNameOnly(const std::string& name,
                                                  Import::ImportType type,
                                                  const fs::path& currentDir) {
    ImportResolveResult result;
    
    // 搜索顺序：
    // 1. 官方模块目录
    // 2. 当前目录的module文件夹
    // 3. 当前目录
    
    std::vector<fs::path> searchPaths = {
        officialModulePath_,
        currentDir / "module",
        currentDir
    };
    
    // 获取该类型支持的扩展名（对于CHTL类型，.cmod优先）
    std::vector<std::string> extensions;
    if (type == Import::ImportType::CHTL || 
        type == Import::ImportType::CUSTOM_ELEMENT ||
        type == Import::ImportType::CUSTOM_STYLE ||
        type == Import::ImportType::CUSTOM_VAR ||
        type == Import::ImportType::TEMPLATE_ELEMENT ||
        type == Import::ImportType::TEMPLATE_STYLE ||
        type == Import::ImportType::TEMPLATE_VAR ||
        type == Import::ImportType::ALL) {
        // 对于CHTL相关类型，.cmod优先
        extensions = {".cmod", ".chtl"};
    } else {
        auto it = EXTENSION_MAP.find(type);
        if (it != EXTENSION_MAP.end()) {
            extensions = it->second;
        }
    }
    
    // 在每个搜索路径中查找
    for (const auto& searchPath : searchPaths) {
        if (!fs::exists(searchPath) || !fs::is_directory(searchPath)) {
            continue;
        }
        
        // 尝试每个扩展名
        for (const auto& ext : extensions) {
            fs::path filePath = searchPath / (name + ext);
            
            if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
                result.resolvedPath = filePath.string();
                result.fileExtension = ext;
                result.success = true;
                result.isRelative = false;
                return result;
            }
        }
    }
    
    // 构建错误信息
    result.errorMessage = "Module '" + name + "' not found. Searched in: ";
    for (size_t i = 0; i < searchPaths.size(); ++i) {
        if (i > 0) result.errorMessage += ", ";
        result.errorMessage += searchPaths[i].string();
    }
    result.errorMessage += " (tried extensions: ";
    for (size_t i = 0; i < extensions.size(); ++i) {
        if (i > 0) result.errorMessage += ", ";
        result.errorMessage += extensions[i];
    }
    result.errorMessage += ")";
    
    return result;
}

ImportResolveResult ImportResolver::resolveNameWithExtension(const std::string& name,
                                                           Import::ImportType type,
                                                           const fs::path& currentDir) {
    ImportResolveResult result;
    
    // 搜索顺序：
    // 1. 官方模块目录
    // 2. 当前目录的module文件夹
    // 3. 当前目录
    
    std::vector<fs::path> searchPaths = {
        officialModulePath_,
        currentDir / "module",
        currentDir
    };
    
    // 在每个搜索路径中查找
    for (const auto& searchPath : searchPaths) {
        if (!fs::exists(searchPath) || !fs::is_directory(searchPath)) {
            continue;
        }
        
        fs::path filePath = searchPath / name;
        
        if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
            result.resolvedPath = filePath.string();
            result.fileExtension = getExtension(name);
            result.success = true;
            result.isRelative = false;
            
            // 验证扩展名是否匹配类型
            if (!validateExtension(result.fileExtension, type)) {
                result.success = false;
                result.errorMessage = "File extension '" + result.fileExtension + 
                                    "' does not match import type";
                return result;
            }
            
            return result;
        }
    }
    
    // 构建错误信息
    result.errorMessage = "File '" + name + "' not found. Searched in: ";
    for (size_t i = 0; i < searchPaths.size(); ++i) {
        if (i > 0) result.errorMessage += ", ";
        result.errorMessage += searchPaths[i].string();
    }
    
    return result;
}

ImportResolveResult ImportResolver::resolveSpecificPath(const std::string& path,
                                                       Import::ImportType type) {
    ImportResolveResult result;
    
    fs::path filePath(path);
    
    // 如果是相对路径，基于当前工作目录解析
    if (!filePath.is_absolute()) {
        filePath = fs::current_path() / filePath;
        result.isRelative = true;
    } else {
        result.isRelative = false;
    }
    
    // 检查文件是否存在
    if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
        result.resolvedPath = filePath.string();
        result.fileExtension = getExtension(path);
        
        // 验证扩展名
        if (!validateExtension(result.fileExtension, type)) {
            result.success = false;
            result.errorMessage = "File extension '" + result.fileExtension + 
                                "' does not match import type";
            return result;
        }
        
        result.success = true;
        return result;
    }
    
    result.errorMessage = "File not found: " + filePath.string();
    return result;
}

bool ImportResolver::isWildcardImport(const std::string& path) const {
    return path.find('*') != std::string::npos;
}

bool ImportResolver::isSubmoduleImport(const std::string& path) const {
    // 检查是否包含'.'但不是文件扩展名
    size_t dotPos = path.find('.');
    if (dotPos == std::string::npos) {
        return false;
    }
    
    // 检查'.'后面是否是已知的文件扩展名
    std::string afterDot = path.substr(dotPos);
    
    // 如果包含路径分隔符，则不是子模块
    if (afterDot.find('/') != std::string::npos || 
        afterDot.find('\\') != std::string::npos) {
        return false;
    }
    
    // 检查是否是文件扩展名
    for (const auto& [type, extensions] : EXTENSION_MAP) {
        for (const auto& ext : extensions) {
            if (afterDot == ext) {
                return false;  // 是文件扩展名，不是子模块
            }
        }
    }
    
    return true;  // 是子模块
}

ImportResolveResult ImportResolver::resolveWildcardImport(const std::string& pattern,
                                                        Import::ImportType type,
                                                        const fs::path& currentDir) {
    ImportResolveResult result;
    
    // 将 '.* ' 转换为 '/*'
    std::string normalizedPattern = pattern;
    size_t pos = normalizedPattern.find(".*");
    while (pos != std::string::npos) {
        normalizedPattern.replace(pos, 2, "/*");
        pos = normalizedPattern.find(".*", pos + 2);
    }
    
    // 解析路径和通配符部分
    fs::path patternPath(normalizedPattern);
    fs::path directory = patternPath.parent_path();
    std::string wildcard = patternPath.filename().string();
    
    // 解析通配符
    std::string extension;
    if (wildcard == "*") {
        // 导入所有 .cmod 和 .chtl 文件
        extension = "";
    } else if (wildcard == "*.cmod") {
        extension = ".cmod";
    } else if (wildcard == "*.chtl") {
        extension = ".chtl";
    } else {
        result.errorMessage = "Invalid wildcard pattern: " + pattern;
        return result;
    }
    
    // 解析目录路径
    fs::path resolvedDir;
    if (directory.is_absolute()) {
        resolvedDir = directory;
    } else if (directory.empty()) {
        resolvedDir = currentDir;
    } else {
        resolvedDir = currentDir / directory;
    }
    
    // 检查目录是否存在
    if (!fs::exists(resolvedDir) || !fs::is_directory(resolvedDir)) {
        result.errorMessage = "Directory not found: " + resolvedDir.string();
        return result;
    }
    
    // 收集匹配的文件
    result.wildcardResults.clear();
    try {
        for (const auto& entry : fs::directory_iterator(resolvedDir)) {
            if (entry.is_regular_file()) {
                std::string fileExt = entry.path().extension().string();
                
                if (extension.empty()) {
                    // 匹配所有 .cmod 和 .chtl 文件
                    if (fileExt == ".cmod" || fileExt == ".chtl") {
                        result.wildcardResults.push_back(entry.path().string());
                    }
                } else if (fileExt == extension) {
                    // 匹配特定扩展名
                    result.wildcardResults.push_back(entry.path().string());
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        result.errorMessage = "Error reading directory: " + e.what();
        return result;
    }
    
    if (result.wildcardResults.empty()) {
        result.errorMessage = "No files matched pattern: " + pattern;
        return result;
    }
    
    result.success = true;
    result.isWildcard = true;
    return result;
}

ImportResolveResult ImportResolver::resolveSubmoduleImport(const std::string& path,
                                                         Import::ImportType type,
                                                         const fs::path& currentDir) {
    ImportResolveResult result;
    
    // 支持 '.' 和 '/' 作为子模块分隔符
    std::string normalizedPath = path;
    std::replace(normalizedPath.begin(), normalizedPath.end(), '.', '/');
    
    // 分离模块名和子模块路径
    size_t firstSep = normalizedPath.find('/');
    std::string moduleName = normalizedPath.substr(0, firstSep);
    std::string submodulePath = (firstSep != std::string::npos) ? 
                                normalizedPath.substr(firstSep + 1) : "";
    
    // 检查是否是通配符子模块导入
    if (submodulePath == "*") {
        // 先找到主模块
        auto mainModuleResult = resolveNameOnly(moduleName, type, currentDir);
        if (!mainModuleResult.success) {
            result.errorMessage = "Cannot find module '" + moduleName + 
                                "' for submodule import";
            return result;
        }
        
        // 获取主模块所在目录
        fs::path mainModulePath(mainModuleResult.resolvedPath);
        fs::path moduleDir = mainModulePath.parent_path() / moduleName;
        
        // 检查子模块目录是否存在
        if (!fs::exists(moduleDir) || !fs::is_directory(moduleDir)) {
            result.errorMessage = "Module '" + moduleName + 
                                "' does not have submodules directory";
            return result;
        }
        
        // 收集所有子模块
        result.wildcardResults.clear();
        try {
            for (const auto& entry : fs::recursive_directory_iterator(moduleDir)) {
                if (entry.is_regular_file()) {
                    std::string ext = entry.path().extension().string();
                    if (ext == ".cmod" || ext == ".chtl") {
                        result.wildcardResults.push_back(entry.path().string());
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            result.errorMessage = "Error reading submodules: " + e.what();
            return result;
        }
        
        if (result.wildcardResults.empty()) {
            result.errorMessage = "No submodules found in module '" + moduleName + "'";
            return result;
        }
        
        result.success = true;
        result.isWildcard = true;
        return result;
    } else {
        // 具体的子模块
        // 先找到主模块目录
        auto mainModuleResult = resolveNameOnly(moduleName, type, currentDir);
        if (!mainModuleResult.success) {
            result.errorMessage = "Cannot find module '" + moduleName + 
                                "' for submodule import";
            return result;
        }
        
        fs::path mainModulePath(mainModuleResult.resolvedPath);
        fs::path moduleDir = mainModulePath.parent_path() / moduleName;
        
        // 在子模块目录中查找
        fs::path submoduleFile = moduleDir / submodulePath;
        
        // 如果没有扩展名，尝试 .cmod 和 .chtl
        if (!hasExtension(submodulePath)) {
            std::vector<std::string> extensions = {".cmod", ".chtl"};
            for (const auto& ext : extensions) {
                fs::path testPath = fs::path(submoduleFile.string() + ext);
                if (fs::exists(testPath) && fs::is_regular_file(testPath)) {
                    result.resolvedPath = testPath.string();
                    result.fileExtension = ext;
                    result.success = true;
                    return result;
                }
            }
            
            result.errorMessage = "Submodule '" + submodulePath + 
                                "' not found in module '" + moduleName + "'";
            return result;
        } else {
            // 有扩展名，直接查找
            if (fs::exists(submoduleFile) && fs::is_regular_file(submoduleFile)) {
                result.resolvedPath = submoduleFile.string();
                result.fileExtension = getExtension(submodulePath);
                result.success = true;
                return result;
            }
            
            result.errorMessage = "Submodule file not found: " + submoduleFile.string();
            return result;
        }
    }
}

std::string ImportResolver::getDefaultExtension(Import::ImportType type) const {
    switch (type) {
        case Import::ImportType::HTML:
            return ".html";
        case Import::ImportType::CSS:
            return ".css";
        case Import::ImportType::JS:
            return ".js";
        case Import::ImportType::CHTL:
        case Import::ImportType::CUSTOM_ELEMENT:
        case Import::ImportType::CUSTOM_STYLE:
        case Import::ImportType::CUSTOM_VAR:
        case Import::ImportType::TEMPLATE_ELEMENT:
        case Import::ImportType::TEMPLATE_STYLE:
        case Import::ImportType::TEMPLATE_VAR:
        case Import::ImportType::ALL:
            return ".cmod";  // .cmod 优先
        case Import::ImportType::CJMOD:
            return ".cjmod";
        default:
            return "";
    }
}

bool ImportResolver::fileExists(const std::string& path) const {
    return fs::exists(path) && fs::is_regular_file(path);
}

std::string ImportResolver::normalizePath(const std::string& path) const {
    std::string normalized = path;
    
    // 统一路径分隔符
    std::replace(normalized.begin(), normalized.end(), '\\', '/');
    
    return normalized;
}

bool ImportResolver::isAbsolutePath(const std::string& path) const {
    fs::path p(path);
    return p.is_absolute();
}

std::string ImportResolver::getExtension(const std::string& path) const {
    fs::path p(path);
    return p.extension().string();
}

bool ImportResolver::hasExtension(const std::string& path) const {
    std::string ext = getExtension(path);
    return !ext.empty();
}

std::string ImportResolver::findFileInDirectory(const std::string& directory,
                                               const std::string& filename,
                                               const std::string& extension) const {
    try {
        // 直接在目录中查找（不递归）
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string entryName = entry.path().stem().string();
                std::string entryExt = entry.path().extension().string();
                
                // 检查文件名匹配
                if (entryName == filename && entryExt == extension) {
                    return entry.path().string();
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        // 忽略错误
    }
    
    return "";
}

std::string ImportResolver::resolveRelativePath(const std::string& basePath,
                                               const std::string& relativePath) const {
    fs::path base(basePath);
    fs::path relative(relativePath);
    
    fs::path resolved = base / relative;
    return resolved.lexically_normal().string();
}

bool ImportResolver::validateExtension(const std::string& extension,
                                      Import::ImportType type) const {
    auto it = EXTENSION_MAP.find(type);
    if (it == EXTENSION_MAP.end()) {
        return false;
    }
    
    const auto& validExtensions = it->second;
    return std::find(validExtensions.begin(), validExtensions.end(), extension) 
           != validExtensions.end();
}

} // namespace chtl