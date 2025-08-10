#include "Loader/ImportResolver.h"
#include <algorithm>
#include <iostream>

namespace chtl {

// 静态成员定义
const std::unordered_map<Import::ImportType, std::vector<std::string>> ImportResolver::EXTENSION_MAP = {
    {Import::ImportType::HTML, {".html", ".htm", ".xhtml"}},
    {Import::ImportType::CSS, {".css", ".scss", ".sass", ".less"}},
    {Import::ImportType::JS, {".js", ".mjs", ".jsx", ".ts", ".tsx"}},
    {Import::ImportType::CHTL, {".chtl"}},
    {Import::ImportType::CUSTOM_ELEMENT, {".chtl"}},
    {Import::ImportType::CUSTOM_STYLE, {".chtl"}},
    {Import::ImportType::CUSTOM_VAR, {".chtl"}},
    {Import::ImportType::TEMPLATE_ELEMENT, {".chtl"}},
    {Import::ImportType::TEMPLATE_STYLE, {".chtl"}},
    {Import::ImportType::TEMPLATE_VAR, {".chtl"}},
    {Import::ImportType::ALL, {".chtl"}}
};

ImportResolver::ImportResolver() {
    // 默认使用当前工作目录作为项目根目录
    projectRoot_ = fs::current_path().string();
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
    
    // 规范化导入路径（处理.表示/的情况）
    std::string normalizedPath = normalizePath(importPath);
    
    // 判断是否为绝对路径
    if (isAbsolutePath(normalizedPath)) {
        result.isRelative = false;
        
        // 检查文件是否存在
        if (fileExists(normalizedPath)) {
            result.resolvedPath = normalizedPath;
            result.fileExtension = getExtension(normalizedPath);
            
            // 验证扩展名
            if (!validateExtension(result.fileExtension, type)) {
                result.errorMessage = "File extension '" + result.fileExtension + 
                                    "' does not match import type";
                return result;
            }
            
            result.success = true;
            return result;
        } else {
            result.errorMessage = "File not found: " + normalizedPath;
            return result;
        }
    }
    
    // 处理相对路径
    result.isRelative = true;
    
    // 检查是否有扩展名
    bool hasExt = hasExtension(normalizedPath);
    
    if (hasExt) {
        // 有扩展名，直接在当前目录查找
        fs::path fullPath = currentDir / normalizedPath;
        std::string resolvedPath = fullPath.string();
        
        if (fileExists(resolvedPath)) {
            result.resolvedPath = resolvedPath;
            result.fileExtension = getExtension(resolvedPath);
            
            // 验证扩展名
            if (!validateExtension(result.fileExtension, type)) {
                result.errorMessage = "File extension '" + result.fileExtension + 
                                    "' does not match import type";
                return result;
            }
            
            result.success = true;
            return result;
        } else {
            result.errorMessage = "File not found: " + resolvedPath;
            return result;
        }
    } else {
        // 没有扩展名，需要根据类型查找
        std::string defaultExt = getDefaultExtension(type);
        
        // 首先尝试添加默认扩展名
        fs::path fullPath = currentDir / (normalizedPath + defaultExt);
        std::string resolvedPath = fullPath.string();
        
        if (fileExists(resolvedPath)) {
            result.resolvedPath = resolvedPath;
            result.fileExtension = defaultExt;
            result.success = true;
            return result;
        }
        
        // 如果默认扩展名不存在，尝试其他支持的扩展名
        auto it = EXTENSION_MAP.find(type);
        if (it != EXTENSION_MAP.end()) {
            for (const auto& ext : it->second) {
                fullPath = currentDir / (normalizedPath + ext);
                resolvedPath = fullPath.string();
                
                if (fileExists(resolvedPath)) {
                    result.resolvedPath = resolvedPath;
                    result.fileExtension = ext;
                    result.success = true;
                    return result;
                }
            }
        }
        
        // 如果是纯文件名（如"main"），在当前目录中查找
        if (normalizedPath.find('/') == std::string::npos && 
            normalizedPath.find('\\') == std::string::npos) {
            std::string foundFile = findFileInDirectory(currentDir.string(), 
                                                       normalizedPath, 
                                                       defaultExt);
            if (!foundFile.empty()) {
                result.resolvedPath = foundFile;
                result.fileExtension = getExtension(foundFile);
                result.success = true;
                return result;
            }
        }
        
        result.errorMessage = "File not found: " + normalizedPath + 
                            " (tried extensions: " + defaultExt;
        if (it != EXTENSION_MAP.end()) {
            for (const auto& ext : it->second) {
                if (ext != defaultExt) {
                    result.errorMessage += ", " + ext;
                }
            }
        }
        result.errorMessage += ")";
    }
    
    return result;
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
            return ".chtl";
        default:
            return "";
    }
}

bool ImportResolver::fileExists(const std::string& path) const {
    return fs::exists(path) && fs::is_regular_file(path);
}

std::string ImportResolver::normalizePath(const std::string& path) const {
    std::string normalized = path;
    
    // 替换所有的.为/（除了文件扩展名中的.）
    size_t lastDot = normalized.rfind('.');
    size_t lastSlash = normalized.rfind('/');
    size_t lastBackslash = normalized.rfind('\\');
    
    // 如果最后一个.在最后一个路径分隔符之后，且前面还有其他字符，可能是扩展名
    bool hasExtension = false;
    if (lastDot != std::string::npos) {
        size_t lastSep = std::string::npos;
        if (lastSlash != std::string::npos) lastSep = lastSlash;
        if (lastBackslash != std::string::npos && 
            (lastSep == std::string::npos || lastBackslash > lastSep)) {
            lastSep = lastBackslash;
        }
        
        if (lastSep == std::string::npos || lastDot > lastSep) {
            // 检查是否是有效的扩展名（.后面有字符）
            if (lastDot + 1 < normalized.length()) {
                hasExtension = true;
            }
        }
    }
    
    // 替换路径中的.为/，但保留扩展名
    if (hasExtension) {
        // 只替换扩展名之前的.
        for (size_t i = 0; i < lastDot; ++i) {
            if (normalized[i] == '.') {
                // 确保不是相对路径的开头（如./或../）
                if (i == 0 || (i > 0 && normalized[i-1] != '.')) {
                    if (i + 1 >= normalized.length() || normalized[i+1] != '.') {
                        normalized[i] = '/';
                    }
                }
            }
        }
    } else {
        // 没有扩展名，替换所有的.
        for (size_t i = 0; i < normalized.length(); ++i) {
            if (normalized[i] == '.') {
                // 确保不是相对路径的开头（如./或../）
                if (i == 0 || (i > 0 && normalized[i-1] != '.')) {
                    if (i + 1 >= normalized.length() || normalized[i+1] != '.') {
                        normalized[i] = '/';
                    }
                }
            }
        }
    }
    
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