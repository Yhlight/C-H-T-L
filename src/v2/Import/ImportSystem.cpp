#include "v2/Import/ImportSystem.h"
// #include "v2/Cmod/CmodSystem.h"  // 暂时禁用
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

namespace chtl::v2 {

ImportSystem::ImportSystem() {
    // 设置默认的官方模块路径
    // TODO: 从环境变量或配置文件读取
    officialModulesPath_ = "/usr/local/share/chtl/modules";
}

ImportSystem::~ImportSystem() = default;

void ImportSystem::addSearchPath(const std::string& path) {
    searchPaths_.push_back(normalizePath(path));
}

void ImportSystem::setProjectRoot(const std::string& root) {
    projectRoot_ = normalizePath(root);
}

ImportResolveResult ImportSystem::resolve(const ImportItem& item) {
    switch (item.type) {
        case ImportType::HTML:
            return resolveHtml(item);
        case ImportType::STYLE:
            return resolveStyle(item);
        case ImportType::JAVASCRIPT:
            return resolveJavaScript(item);
        case ImportType::CHTL:
            return resolveChtl(item);
        case ImportType::CJMOD:
            return resolveCJMOD(item);
        case ImportType::ELEMENT:
            return resolveElement(item);
        default:
            return {false, "", "", "Unknown import type"};
    }
}

std::string ImportSystem::loadContent(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool ImportSystem::isOfficialModule(const std::string& path) {
    return path.find("CHTL::") == 0;
}

std::string ImportSystem::getOfficialModulePath(const std::string& moduleName) {
    // 移除 CHTL:: 前缀
    std::string name = moduleName;
    if (isOfficialModule(name)) {
        name = name.substr(6); // 长度 "CHTL::"
    }
    
    // 替换 :: 为路径分隔符
    std::replace(name.begin(), name.end(), ':', '/');
    
    return officialModulesPath_ + "/" + name;
}

ImportResolveResult ImportSystem::resolveHtml(const ImportItem& item) {
    ImportResolveResult result;
    std::string basePath = item.path;
    
    // 处理官方模块
    if (isOfficialModule(basePath)) {
        basePath = getOfficialModulePath(basePath);
    }
    
    // @Html: 搜索 .html 文件或目录下的 index.html
    std::vector<std::string> candidates;
    
    // 如果没有扩展名，尝试添加
    if (basePath.find('.') == std::string::npos) {
        candidates.push_back(basePath + ".html");
        candidates.push_back(basePath + "/index.html");
    } else {
        candidates.push_back(basePath);
    }
    
    // 在搜索路径中查找
    for (const auto& searchPath : searchPaths_) {
        for (const auto& candidate : candidates) {
            fs::path fullPath = fs::path(searchPath) / candidate;
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                result.success = true;
                result.resolvedPath = fullPath.string();
                result.content = loadContent(result.resolvedPath);
                return result;
            }
        }
    }
    
    // 在项目根目录查找
    if (!projectRoot_.empty()) {
        for (const auto& candidate : candidates) {
            fs::path fullPath = fs::path(projectRoot_) / candidate;
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                result.success = true;
                result.resolvedPath = fullPath.string();
                result.content = loadContent(result.resolvedPath);
                return result;
            }
        }
    }
    
    result.error = "HTML file not found: " + item.path;
    return result;
}

ImportResolveResult ImportSystem::resolveStyle(const ImportItem& item) {
    ImportResolveResult result;
    std::string basePath = item.path;
    
    // 处理官方模块
    if (isOfficialModule(basePath)) {
        basePath = getOfficialModulePath(basePath);
    }
    
    // @Style: 只查找 .css 文件
    std::vector<std::string> extensions = {".css"};
    std::string resolved = tryExtensions(basePath, extensions);
    
    if (!resolved.empty()) {
        result.success = true;
        result.resolvedPath = resolved;
        result.content = loadContent(resolved);
    } else {
        result.error = "Style file not found: " + item.path;
    }
    
    return result;
}

ImportResolveResult ImportSystem::resolveJavaScript(const ImportItem& item) {
    ImportResolveResult result;
    std::string basePath = item.path;
    
    // 处理官方模块
    if (isOfficialModule(basePath)) {
        basePath = getOfficialModulePath(basePath);
    }
    
    // @JavaScript: 查找 .js 或 .mjs 文件
    std::vector<std::string> extensions = {".js", ".mjs"};
    std::string resolved = tryExtensions(basePath, extensions);
    
    if (!resolved.empty()) {
        result.success = true;
        result.resolvedPath = resolved;
        result.content = loadContent(resolved);
    } else {
        result.error = "JavaScript file not found: " + item.path;
    }
    
    return result;
}

ImportResolveResult ImportSystem::resolveChtl(const ImportItem& item) {
    ImportResolveResult result;
    std::string basePath = item.path;
    
    // 处理官方模块
    if (isOfficialModule(basePath)) {
        basePath = getOfficialModulePath(basePath);
    }
    
    // @Chtl: 查找 .chtl 文件或目录下的 index.chtl
    std::vector<std::string> candidates;
    
    if (basePath.find('.') == std::string::npos) {
        candidates.push_back(basePath + ".chtl");
        candidates.push_back(basePath + "/index.chtl");
    } else {
        candidates.push_back(basePath);
    }
    
    // 在搜索路径中查找
    for (const auto& searchPath : searchPaths_) {
        for (const auto& candidate : candidates) {
            fs::path fullPath = fs::path(searchPath) / candidate;
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                result.success = true;
                result.resolvedPath = fullPath.string();
                result.content = loadContent(result.resolvedPath);
                return result;
            }
        }
    }
    
    // 在项目根目录查找
    if (!projectRoot_.empty()) {
        for (const auto& candidate : candidates) {
            fs::path fullPath = fs::path(projectRoot_) / candidate;
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                result.success = true;
                result.resolvedPath = fullPath.string();
                result.content = loadContent(result.resolvedPath);
                return result;
            }
        }
    }
    
    result.error = "CHTL file not found: " + item.path;
    return result;
}

ImportResolveResult ImportSystem::resolveCJMOD(const ImportItem& item) {
    ImportResolveResult result;
    std::string basePath = item.path;
    
    // 处理官方模块
    if (isOfficialModule(basePath)) {
        basePath = getOfficialModulePath(basePath);
    }
    
    // @CJMOD: 查找 .so 或 .dll 文件（动态库）
    std::vector<std::string> extensions;
    #ifdef _WIN32
        extensions = {".dll"};
    #elif __APPLE__
        extensions = {".dylib", ".so"};
    #else
        extensions = {".so"};
    #endif
    
    std::string resolved = tryExtensions(basePath, extensions);
    
    if (!resolved.empty()) {
        result.success = true;
        result.resolvedPath = resolved;
        // CJMOD 是二进制文件，不加载内容
    } else {
        result.error = "CJMOD library not found: " + item.path;
    }
    
    return result;
}

ImportResolveResult ImportSystem::resolveElement(const ImportItem& item) {
    ImportResolveResult result;
    std::string basePath = item.path;
    
    // 处理官方模块
    if (isOfficialModule(basePath)) {
        basePath = getOfficialModulePath(basePath);
    }
    
    // @Element (CMOD): 查找 cmod.json 或 package.json
    std::vector<std::string> candidates = {
        basePath + "/cmod.json",
        basePath + "/package.json",
        basePath + ".cmod/cmod.json"
    };
    
    for (const auto& candidate : candidates) {
        if (fs::exists(candidate) && fs::is_regular_file(candidate)) {
            result.success = true;
            result.resolvedPath = fs::path(candidate).parent_path().string();
            // TODO: 解析 CMOD 包
            return result;
        }
    }
    
    result.error = "CMOD package not found: " + item.path;
    return result;
}

std::string ImportSystem::tryExtensions(const std::string& basePath, 
                                       const std::vector<std::string>& extensions) {
    // 如果已经有扩展名，直接查找
    for (const auto& ext : extensions) {
        if (basePath.size() > ext.size() && 
            basePath.substr(basePath.size() - ext.size()) == ext) {
            // 在搜索路径中查找
            for (const auto& searchPath : searchPaths_) {
                fs::path fullPath = fs::path(searchPath) / basePath;
                if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                    return fullPath.string();
                }
            }
            
            // 在项目根目录查找
            if (!projectRoot_.empty()) {
                fs::path fullPath = fs::path(projectRoot_) / basePath;
                if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                    return fullPath.string();
                }
            }
            
            return "";
        }
    }
    
    // 尝试添加扩展名
    for (const auto& ext : extensions) {
        std::string pathWithExt = basePath + ext;
        
        // 在搜索路径中查找
        for (const auto& searchPath : searchPaths_) {
            fs::path fullPath = fs::path(searchPath) / pathWithExt;
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                return fullPath.string();
            }
        }
        
        // 在项目根目录查找
        if (!projectRoot_.empty()) {
            fs::path fullPath = fs::path(projectRoot_) / pathWithExt;
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                return fullPath.string();
            }
        }
    }
    
    return "";
}

std::string ImportSystem::normalizePath(const std::string& path) {
    return fs::path(path).lexically_normal().string();
}

// ImportProcessor 实现

ImportProcessor::ImportProcessor(ImportSystem* importSystem) 
    : importSystem_(importSystem) {
}

void ImportProcessor::processImport(const ImportItem& item) {
    auto result = importSystem_->resolve(item);
    
    if (result.success) {
        ImportItem processed = item;
        processed.resolvedPath = result.resolvedPath;
        processedImports_.push_back(processed);
        
        if (!result.content.empty()) {
            importedContent_[item.type].push_back(result.content);
        }
    } else {
        errors_.push_back(result.error);
    }
}

std::string ImportProcessor::getImportedContent(ImportType type) const {
    auto it = importedContent_.find(type);
    if (it == importedContent_.end()) {
        return "";
    }
    
    std::stringstream combined;
    for (const auto& content : it->second) {
        combined << content << "\n";
    }
    return combined.str();
}

} // namespace chtl::v2