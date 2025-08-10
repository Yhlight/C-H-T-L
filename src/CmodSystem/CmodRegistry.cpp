#include "CmodSystem/CmodRegistry.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace chtl {

namespace fs = std::filesystem;

CmodRegistry::CmodRegistry() : isDirty_(false) {}

CmodRegistry::~CmodRegistry() {
    // 如果有未保存的更改，自动保存
    if (isDirty_) {
        save();
    }
}

// 初始化注册表
bool CmodRegistry::initialize(const std::string& registryPath) {
    if (registryPath.empty()) {
        // 使用默认路径
        registryPath_ = fs::current_path() / ".chtl" / "registry.json";
    } else {
        registryPath_ = registryPath;
    }
    
    // 确保目录存在
    fs::create_directories(fs::path(registryPath_).parent_path());
    
    // 设置默认搜索路径
    searchPaths_ = getDefaultSearchPaths();
    
    // 尝试加载现有注册表
    if (fs::exists(registryPath_)) {
        return load();
    }
    
    return true;
}

// 注册模块
bool CmodRegistry::registerModule(const CmodInfo& info, const std::string& installPath) {
    ModuleRecord record;
    record.info = info;
    record.installPath = installPath;
    record.isBuiltin = false;
    record.isEnabled = true;
    
    // 获取当前时间作为安装时间
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    record.installTime = ss.str();
    
    // 解析依赖
    record.dependencies = parseDependencies(info.dependencies);
    
    return registerModule(record);
}

bool CmodRegistry::registerModule(const ModuleRecord& record) {
    modules_[record.info.name] = record;
    
    // 更新依赖关系
    buildDependencyGraph();
    
    isDirty_ = true;
    return true;
}

// 注销模块
bool CmodRegistry::unregisterModule(const std::string& moduleName) {
    auto it = modules_.find(moduleName);
    if (it == modules_.end()) {
        return false;
    }
    
    // 检查是否有其他模块依赖此模块
    auto dependents = getDependents(moduleName);
    if (!dependents.empty()) {
        // TODO: 可以选择强制卸载或返回错误
        return false;
    }
    
    modules_.erase(it);
    buildDependencyGraph();
    
    isDirty_ = true;
    return true;
}

// 查询模块
const CmodRegistry::ModuleRecord* CmodRegistry::getModule(const std::string& moduleName) const {
    auto it = modules_.find(moduleName);
    if (it != modules_.end()) {
        return &it->second;
    }
    return nullptr;
}

CmodRegistry::ModuleRecord* CmodRegistry::getModule(const std::string& moduleName) {
    auto it = modules_.find(moduleName);
    if (it != modules_.end()) {
        return &it->second;
    }
    return nullptr;
}

// 查询模块（支持子模块路径）
const CmodRegistry::ModuleRecord* CmodRegistry::getModuleByPath(const std::string& modulePath) const {
    // 首先尝试直接查找
    auto record = getModule(modulePath);
    if (record) {
        return record;
    }
    
    // 解析路径（如 "Chtholly.Space"）
    size_t dotPos = modulePath.find('.');
    if (dotPos != std::string::npos) {
        std::string parentName = modulePath.substr(0, dotPos);
        std::string submoduleName = modulePath.substr(dotPos + 1);
        
        // TODO: 实现子模块查找逻辑
        // 这需要遍历父模块的子模块
    }
    
    return nullptr;
}

// 检查模块是否存在
bool CmodRegistry::hasModule(const std::string& moduleName) const {
    return modules_.find(moduleName) != modules_.end();
}

// 查询所有模块
CmodRegistry::QueryResult CmodRegistry::getAllModules() const {
    QueryResult result;
    result.totalCount = modules_.size();
    
    for (const auto& [name, record] : modules_) {
        result.modules.push_back(&record);
    }
    
    return result;
}

// 按类别查询
CmodRegistry::QueryResult CmodRegistry::getModulesByCategory(const std::string& category) const {
    QueryResult result;
    
    for (const auto& [name, record] : modules_) {
        if (record.info.category == category) {
            result.modules.push_back(&record);
        }
    }
    
    result.totalCount = result.modules.size();
    return result;
}

// 按作者查询
CmodRegistry::QueryResult CmodRegistry::getModulesByAuthor(const std::string& author) const {
    QueryResult result;
    
    for (const auto& [name, record] : modules_) {
        if (record.info.author == author) {
            result.modules.push_back(&record);
        }
    }
    
    result.totalCount = result.modules.size();
    return result;
}

// 查询依赖关系
std::vector<std::string> CmodRegistry::getDependencies(const std::string& moduleName) const {
    auto it = modules_.find(moduleName);
    if (it != modules_.end()) {
        return it->second.dependencies;
    }
    return {};
}

std::vector<std::string> CmodRegistry::getDependents(const std::string& moduleName) const {
    auto it = modules_.find(moduleName);
    if (it != modules_.end()) {
        return it->second.dependents;
    }
    return {};
}

// 检查依赖
bool CmodRegistry::checkDependencies(const std::string& moduleName) const {
    auto deps = getDependencies(moduleName);
    
    for (const auto& dep : deps) {
        if (!hasModule(dep)) {
            return false;
        }
    }
    
    return true;
}

// 启用/禁用模块
bool CmodRegistry::enableModule(const std::string& moduleName) {
    auto module = getModule(moduleName);
    if (module) {
        module->isEnabled = true;
        isDirty_ = true;
        return true;
    }
    return false;
}

bool CmodRegistry::disableModule(const std::string& moduleName) {
    auto module = getModule(moduleName);
    if (module) {
        module->isEnabled = false;
        isDirty_ = true;
        return true;
    }
    return false;
}

// 获取模块路径
std::string CmodRegistry::getModulePath(const std::string& moduleName) const {
    auto module = getModule(moduleName);
    if (module) {
        return module->installPath;
    }
    return "";
}

// 添加搜索路径
void CmodRegistry::addSearchPath(const std::string& path) {
    if (std::find(searchPaths_.begin(), searchPaths_.end(), path) == searchPaths_.end()) {
        searchPaths_.push_back(path);
        isDirty_ = true;
    }
}

// 移除搜索路径
void CmodRegistry::removeSearchPath(const std::string& path) {
    auto it = std::find(searchPaths_.begin(), searchPaths_.end(), path);
    if (it != searchPaths_.end()) {
        searchPaths_.erase(it);
        isDirty_ = true;
    }
}

// 扫描目录查找模块
std::vector<CmodInfo> CmodRegistry::scanDirectory(const std::string& dirPath) {
    std::vector<CmodInfo> found;
    
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        return found;
    }
    
    // TODO: 实现目录扫描逻辑
    // 查找符合CMOD结构的目录
    
    return found;
}

// 刷新注册表
void CmodRegistry::refresh() {
    // 重新扫描所有搜索路径
    for (const auto& path : searchPaths_) {
        auto modules = scanDirectory(path);
        for (const auto& info : modules) {
            if (!hasModule(info.name)) {
                registerModule(info, path + "/" + info.name);
            }
        }
    }
    
    // 验证现有模块
    validate();
}

// 保存注册表
bool CmodRegistry::save() {
    if (registryPath_.empty()) {
        return false;
    }
    return saveAs(registryPath_);
}

bool CmodRegistry::saveAs(const std::string& path) {
    std::ofstream out(path);
    if (!out.is_open()) {
        return false;
    }
    
    out << exportToJson();
    out.close();
    
    if (path == registryPath_) {
        isDirty_ = false;
    }
    
    return true;
}

// 加载注册表
bool CmodRegistry::load() {
    if (registryPath_.empty()) {
        return false;
    }
    return loadFrom(registryPath_);
}

bool CmodRegistry::loadFrom(const std::string& path) {
    // TODO: 实现从文件加载注册表
    (void)path; // 暂时忽略未使用的参数
    return false;
}

// 导出注册表信息
std::string CmodRegistry::exportToJson() const {
    std::stringstream json;
    json << "{\n";
    json << "  \"version\": 1,\n";
    json << "  \"modules\": [\n";
    
    bool first = true;
    for (const auto& [name, record] : modules_) {
        if (!first) json << ",\n";
        first = false;
        
        json << "    {\n";
        json << "      \"name\": \"" << record.info.name << "\",\n";
        json << "      \"version\": \"" << record.info.version << "\",\n";
        json << "      \"path\": \"" << record.installPath << "\",\n";
        json << "      \"enabled\": " << (record.isEnabled ? "true" : "false") << "\n";
        json << "    }";
    }
    
    json << "\n  ],\n";
    json << "  \"searchPaths\": [\n";
    
    first = true;
    for (const auto& path : searchPaths_) {
        if (!first) json << ",\n";
        first = false;
        json << "    \"" << path << "\"";
    }
    
    json << "\n  ]\n";
    json << "}\n";
    
    return json.str();
}

std::string CmodRegistry::exportToXml() const {
    // TODO: 实现XML导出
    return "";
}

// 验证注册表完整性
bool CmodRegistry::validate() {
    bool valid = true;
    
    // 检查所有模块的安装路径
    for (auto& [name, record] : modules_) {
        if (!fs::exists(record.installPath)) {
            record.isEnabled = false;
            valid = false;
        }
    }
    
    // 检查循环依赖
    std::vector<std::string> visited;
    for (const auto& [name, record] : modules_) {
        visited.clear();
        if (checkCircularDependency(name, visited)) {
            valid = false;
        }
    }
    
    if (!valid) {
        isDirty_ = true;
    }
    
    return valid;
}

// 清理无效记录
int CmodRegistry::cleanup() {
    int removed = 0;
    
    auto it = modules_.begin();
    while (it != modules_.end()) {
        if (!fs::exists(it->second.installPath)) {
            it = modules_.erase(it);
            removed++;
        } else {
            ++it;
        }
    }
    
    if (removed > 0) {
        buildDependencyGraph();
        isDirty_ = true;
    }
    
    return removed;
}

// 构建依赖图
void CmodRegistry::buildDependencyGraph() {
    // 清空所有dependents
    for (auto& [name, record] : modules_) {
        record.dependents.clear();
    }
    
    // 重建dependents列表
    for (const auto& [name, record] : modules_) {
        for (const auto& dep : record.dependencies) {
            auto depModule = getModule(dep);
            if (depModule) {
                const_cast<ModuleRecord*>(depModule)->dependents.push_back(name);
            }
        }
    }
}

// 检查循环依赖
bool CmodRegistry::checkCircularDependency(const std::string& moduleName,
                                          std::vector<std::string>& visited) const {
    if (std::find(visited.begin(), visited.end(), moduleName) != visited.end()) {
        return true; // 发现循环
    }
    
    visited.push_back(moduleName);
    
    auto deps = getDependencies(moduleName);
    for (const auto& dep : deps) {
        if (checkCircularDependency(dep, visited)) {
            return true;
        }
    }
    
    visited.pop_back();
    return false;
}

// 解析依赖字符串
std::vector<std::string> CmodRegistry::parseDependencies(const std::string& depStr) const {
    std::vector<std::string> deps;
    
    if (depStr.empty()) {
        return deps;
    }
    
    // 简单的逗号分隔解析
    std::stringstream ss(depStr);
    std::string dep;
    
    while (std::getline(ss, dep, ',')) {
        // 去除空格
        dep.erase(0, dep.find_first_not_of(" \t"));
        dep.erase(dep.find_last_not_of(" \t") + 1);
        
        // 去除版本信息（如果有）
        size_t atPos = dep.find('@');
        if (atPos != std::string::npos) {
            dep = dep.substr(0, atPos);
        }
        
        if (!dep.empty()) {
            deps.push_back(dep);
        }
    }
    
    return deps;
}

// 生成唯一键
std::string CmodRegistry::generateKey(const std::string& name, const std::string& version) const {
    return name + "@" + version;
}

// 默认模块路径
std::vector<std::string> CmodRegistry::getDefaultSearchPaths() const {
    std::vector<std::string> paths;
    
    // 当前目录的module文件夹
    paths.push_back("./module");
    
    // 用户目录
    if (const char* home = std::getenv("HOME")) {
        paths.push_back(std::string(home) + "/.chtl/modules");
    }
    
    // 系统目录
    paths.push_back("/usr/local/share/chtl/modules");
    paths.push_back("/usr/share/chtl/modules");
    
    return paths;
}

// 序列化/反序列化
std::string CmodRegistry::serializeRecord(const ModuleRecord& record) const {
    // TODO: 实现序列化
    (void)record; // 暂时忽略未使用的参数
    return "";
}

CmodRegistry::ModuleRecord CmodRegistry::deserializeRecord(const std::string& data) const {
    // TODO: 实现反序列化
    (void)data; // 暂时忽略未使用的参数
    return ModuleRecord{};
}

} // namespace chtl