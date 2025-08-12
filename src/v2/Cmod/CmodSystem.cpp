#include "v2/Cmod/CmodSystem.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <iostream>

namespace fs = std::filesystem;

namespace chtl::v2::cmod {

CmodSystem::CmodSystem() {
    // 设置默认仓库路径
    repositoryPath_ = fs::path(getenv("HOME") ? getenv("HOME") : ".") / ".chtl" / "cmod";
    
    // 添加默认搜索路径
    addPackagePath("./cmod_modules");
    addPackagePath("./node_modules/@chtl");
}

CmodSystem::~CmodSystem() = default;

void CmodSystem::setRepositoryPath(const std::string& path) {
    repositoryPath_ = path;
}

void CmodSystem::addPackagePath(const std::string& path) {
    packagePaths_.push_back(path);
}

CmodResolveResult CmodSystem::resolvePackage(const std::string& packageName) {
    CmodResolveResult result;
    
    // 检查缓存
    auto cached = packageCache_.find(packageName);
    if (cached != packageCache_.end()) {
        result.success = true;
        result.package = cached->second;
        result.packagePath = getPackageInstallPath(packageName);
        result.components = scanComponents(result.packagePath, result.package);
        return result;
    }
    
    // 在搜索路径中查找包
    for (const auto& searchPath : packagePaths_) {
        fs::path packagePath = fs::path(searchPath) / packageName;
        
        // 尝试加载 cmod.json
        fs::path cmodJsonPath = packagePath / "cmod.json";
        if (fs::exists(cmodJsonPath)) {
            CmodPackage package;
            if (loadPackageConfig(cmodJsonPath.string(), package)) {
                result.success = true;
                result.package = package;
                result.packagePath = packagePath.string();
                result.components = scanComponents(packagePath.string(), package);
                
                // 缓存结果
                packageCache_[packageName] = package;
                return result;
            }
        }
        
        // 尝试加载 package.json（兼容 npm）
        fs::path packageJsonPath = packagePath / "package.json";
        if (fs::exists(packageJsonPath)) {
            CmodPackage package;
            if (loadPackageConfig(packageJsonPath.string(), package)) {
                result.success = true;
                result.package = package;
                result.packagePath = packagePath.string();
                result.components = scanComponents(packagePath.string(), package);
                
                // 缓存结果
                packageCache_[packageName] = package;
                return result;
            }
        }
    }
    
    result.error = "Package not found: " + packageName;
    return result;
}

bool CmodSystem::loadPackageConfig(const std::string& configPath, CmodPackage& package) {
    std::ifstream file(configPath);
    if (!file) {
        return false;
    }
    
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errors;
    
    if (!Json::parseFromStream(builder, file, &root, &errors)) {
        std::cerr << "Failed to parse package config: " << errors << std::endl;
        return false;
    }
    
    // 判断是 cmod.json 还是 package.json
    if (configPath.find("cmod.json") != std::string::npos) {
        return parseCmodJson(root, package);
    } else {
        return parsePackageJson(root, package);
    }
}

bool CmodSystem::parseCmodJson(const Json::Value& json, CmodPackage& package) {
    // 基本信息
    package.name = json.get("name", "").asString();
    package.version = json.get("version", "").asString();
    package.description = json.get("description", "").asString();
    package.author = json.get("author", "").asString();
    package.license = json.get("license", "MIT").asString();
    
    // 入口文件
    package.main = json.get("main", "index.chtl").asString();
    package.style = json.get("style", "").asString();
    package.script = json.get("script", "").asString();
    
    // 依赖
    const Json::Value& deps = json["dependencies"];
    if (deps.isObject()) {
        for (const auto& key : deps.getMemberNames()) {
            package.dependencies[key] = deps[key].asString();
        }
    }
    
    const Json::Value& devDeps = json["devDependencies"];
    if (devDeps.isObject()) {
        for (const auto& key : devDeps.getMemberNames()) {
            package.devDependencies[key] = devDeps[key].asString();
        }
    }
    
    // 导出的组件
    const Json::Value& exports = json["exports"];
    if (exports.isArray()) {
        for (const auto& exp : exports) {
            package.exports.push_back(exp.asString());
        }
    }
    
    // 元数据
    package.metadata = json;
    
    return validatePackage(package);
}

bool CmodSystem::parsePackageJson(const Json::Value& json, CmodPackage& package) {
    // 基本信息
    package.name = json.get("name", "").asString();
    package.version = json.get("version", "").asString();
    package.description = json.get("description", "").asString();
    
    // 作者信息可能是字符串或对象
    const Json::Value& author = json["author"];
    if (author.isString()) {
        package.author = author.asString();
    } else if (author.isObject()) {
        package.author = author.get("name", "").asString();
    }
    
    package.license = json.get("license", "MIT").asString();
    
    // CHTL 特定字段
    const Json::Value& chtl = json["chtl"];
    if (chtl.isObject()) {
        package.main = chtl.get("main", "index.chtl").asString();
        package.style = chtl.get("style", "").asString();
        package.script = chtl.get("script", "").asString();
        
        const Json::Value& exports = chtl["exports"];
        if (exports.isArray()) {
            for (const auto& exp : exports) {
                package.exports.push_back(exp.asString());
            }
        }
    } else {
        // 默认值
        package.main = "index.chtl";
    }
    
    // 依赖
    const Json::Value& deps = json["dependencies"];
    if (deps.isObject()) {
        for (const auto& key : deps.getMemberNames()) {
            package.dependencies[key] = deps[key].asString();
        }
    }
    
    const Json::Value& devDeps = json["devDependencies"];
    if (devDeps.isObject()) {
        for (const auto& key : devDeps.getMemberNames()) {
            package.devDependencies[key] = devDeps[key].asString();
        }
    }
    
    // 元数据
    package.metadata = json;
    
    return validatePackage(package);
}

bool CmodSystem::validatePackage(const CmodPackage& package) {
    // 检查必需字段
    if (package.name.empty()) {
        std::cerr << "Package name is required" << std::endl;
        return false;
    }
    
    if (package.version.empty()) {
        std::cerr << "Package version is required" << std::endl;
        return false;
    }
    
    // 验证包名格式
    std::regex nameRegex("^[a-z0-9-_.]+$");
    if (!std::regex_match(package.name, nameRegex)) {
        std::cerr << "Invalid package name format" << std::endl;
        return false;
    }
    
    return true;
}

std::vector<CmodComponent> CmodSystem::scanComponents(const std::string& packagePath, 
                                                     const CmodPackage& package) {
    std::vector<CmodComponent> components;
    
    // 如果有显式导出列表，使用它
    if (!package.exports.empty()) {
        for (const auto& exportName : package.exports) {
            fs::path componentPath = fs::path(packagePath) / exportName;
            
            // 尝试不同的扩展名
            std::vector<std::string> extensions = {".chtl", ".element.chtl", ".style.chtl"};
            for (const auto& ext : extensions) {
                fs::path fullPath = fs::path(componentPath.string() + ext);
                if (fs::exists(fullPath)) {
                    auto component = parseComponentFile(fullPath.string());
                    if (!component.name.empty()) {
                        components.push_back(component);
                    }
                    break;
                }
            }
        }
    } else {
        // 扫描 components 目录
        fs::path componentsDir = fs::path(packagePath) / "components";
        if (fs::exists(componentsDir) && fs::is_directory(componentsDir)) {
            for (const auto& entry : fs::directory_iterator(componentsDir)) {
                if (entry.is_regular_file()) {
                    std::string filename = entry.path().filename().string();
                    if (filename.ends_with(".chtl")) {
                        auto component = parseComponentFile(entry.path().string());
                        if (!component.name.empty()) {
                            components.push_back(component);
                        }
                    }
                }
            }
        }
        
        // 扫描根目录的 .chtl 文件
        for (const auto& entry : fs::directory_iterator(packagePath)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.ends_with(".chtl") && filename != "index.chtl") {
                    auto component = parseComponentFile(entry.path().string());
                    if (!component.name.empty()) {
                        components.push_back(component);
                    }
                }
            }
        }
    }
    
    return components;
}

CmodComponent CmodSystem::parseComponentFile(const std::string& filePath) {
    CmodComponent component;
    component.path = filePath;
    
    std::ifstream file(filePath);
    if (!file) {
        return component;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    
    // 简单的正则匹配来提取组件信息
    // 查找 [Template] @Element ComponentName(params)
    std::regex templateRegex(R"(\[Template\]\s*@(Element|Style|Var)\s+(\w+)\s*(?:\(([^)]*)\))?)");
    std::smatch match;
    
    if (std::regex_search(content, match, templateRegex)) {
        component.type = match[1];
        component.name = match[2];
        
        // 解析参数
        std::string params = match[3];
        if (!params.empty()) {
            std::regex paramRegex(R"(\w+)");
            std::sregex_iterator it(params.begin(), params.end(), paramRegex);
            std::sregex_iterator end;
            
            for (; it != end; ++it) {
                component.parameters.push_back(it->str());
            }
        }
    }
    
    // 提取文档注释
    std::regex docRegex(R"(/\*\*(.*?)\*/)", std::regex::dotall);
    if (std::regex_search(content, match, docRegex)) {
        component.documentation = match[1];
    }
    
    return component;
}

bool CmodSystem::installPackage(const std::string& packageName, const std::string& version) {
    // TODO: 实现包安装逻辑
    // 1. 从仓库下载包
    // 2. 解压到本地
    // 3. 安装依赖
    return false;
}

std::vector<CmodPackage> CmodSystem::getInstalledPackages() {
    std::vector<CmodPackage> packages;
    
    for (const auto& searchPath : packagePaths_) {
        if (!fs::exists(searchPath) || !fs::is_directory(searchPath)) {
            continue;
        }
        
        for (const auto& entry : fs::directory_iterator(searchPath)) {
            if (entry.is_directory()) {
                CmodPackage package;
                fs::path configPath = entry.path() / "cmod.json";
                if (!fs::exists(configPath)) {
                    configPath = entry.path() / "package.json";
                }
                
                if (fs::exists(configPath) && loadPackageConfig(configPath.string(), package)) {
                    packages.push_back(package);
                }
            }
        }
    }
    
    return packages;
}

bool CmodSystem::isPackageInstalled(const std::string& packageName) {
    for (const auto& searchPath : packagePaths_) {
        fs::path packagePath = fs::path(searchPath) / packageName;
        if (fs::exists(packagePath) && fs::is_directory(packagePath)) {
            return true;
        }
    }
    return false;
}

std::string CmodSystem::getPackageInstallPath(const std::string& packageName) {
    for (const auto& searchPath : packagePaths_) {
        fs::path packagePath = fs::path(searchPath) / packageName;
        if (fs::exists(packagePath) && fs::is_directory(packagePath)) {
            return packagePath.string();
        }
    }
    return "";
}

// CmodLoader 实现

CmodLoader::CmodLoader(CmodSystem* cmodSystem) 
    : cmodSystem_(cmodSystem) {
}

std::string CmodLoader::loadComponent(const std::string& packageName, 
                                     const std::string& componentName) {
    // 检查缓存
    std::string cacheKey = packageName + "::" + componentName;
    auto cached = componentCache_.find(cacheKey);
    if (cached != componentCache_.end()) {
        return cached->second;
    }
    
    // 解析包
    auto result = cmodSystem_->resolvePackage(packageName);
    if (!result.success) {
        return "";
    }
    
    // 查找组件
    for (const auto& component : result.components) {
        if (component.name == componentName) {
            // 加载组件文件
            std::ifstream file(component.path);
            if (file) {
                std::string content((std::istreambuf_iterator<char>(file)),
                                   std::istreambuf_iterator<char>());
                componentCache_[cacheKey] = content;
                return content;
            }
        }
    }
    
    return "";
}

std::map<std::string, std::string> CmodLoader::loadPackageComponents(const std::string& packageName) {
    std::map<std::string, std::string> components;
    
    auto result = cmodSystem_->resolvePackage(packageName);
    if (!result.success) {
        return components;
    }
    
    for (const auto& component : result.components) {
        std::string content = loadComponent(packageName, component.name);
        if (!content.empty()) {
            components[component.name] = content;
        }
    }
    
    return components;
}

std::string CmodLoader::getComponentChtl(const std::string& packageName,
                                        const std::string& componentName) {
    return loadComponent(packageName, componentName);
}

} // namespace chtl::v2::cmod