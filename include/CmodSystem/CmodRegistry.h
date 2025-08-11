#ifndef CHTL_CMOD_REGISTRY_H
#define CHTL_CMOD_REGISTRY_H

#include "CmodSystem/CmodInfo.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace chtl {

// CMOD注册表 - 管理已安装的CMOD模块
class CmodRegistry {
public:
    // 模块记录
    struct ModuleRecord {
        CmodInfo info;
        std::string installPath;      // 安装路径
        std::string packagePath;      // .cmod文件路径（如果是从包安装的）
        std::string installTime;      // 安装时间
        bool isBuiltin;              // 是否为内置模块
        bool isEnabled;              // 是否启用
        
        // 依赖关系
        std::vector<std::string> dependencies;    // 依赖的模块
        std::vector<std::string> dependents;      // 依赖此模块的模块
    };
    
    // 查询结果
    struct QueryResult {
        std::vector<const ModuleRecord*> modules;
        int totalCount;
        
        bool empty() const { return modules.empty(); }
        size_t size() const { return modules.size(); }
    };
    
    CmodRegistry();
    ~CmodRegistry();
    
    // 初始化注册表
    bool initialize(const std::string& registryPath = "");
    
    // 注册模块
    bool registerModule(const CmodInfo& info, const std::string& installPath);
    bool registerModule(const ModuleRecord& record);
    
    // 注销模块
    bool unregisterModule(const std::string& moduleName);
    
    // 查询模块
    const ModuleRecord* getModule(const std::string& moduleName) const;
    ModuleRecord* getModule(const std::string& moduleName);
    
    // 查询模块（支持子模块路径，如 "Chtholly.Space"）
    const ModuleRecord* getModuleByPath(const std::string& modulePath) const;
    
    // 检查模块是否存在
    bool hasModule(const std::string& moduleName) const;
    
    // 查询所有模块
    QueryResult getAllModules() const;
    
    // 按类别查询
    QueryResult getModulesByCategory(const std::string& category) const;
    
    // 按作者查询
    QueryResult getModulesByAuthor(const std::string& author) const;
    
    // 查询依赖关系
    std::vector<std::string> getDependencies(const std::string& moduleName) const;
    std::vector<std::string> getDependents(const std::string& moduleName) const;
    
    // 检查依赖
    bool checkDependencies(const std::string& moduleName) const;
    
    // 启用/禁用模块
    bool enableModule(const std::string& moduleName);
    bool disableModule(const std::string& moduleName);
    
    // 获取模块路径
    std::string getModulePath(const std::string& moduleName) const;
    
    // 获取模块搜索路径
    std::vector<std::string> getSearchPaths() const { return searchPaths_; }
    void addSearchPath(const std::string& path);
    void removeSearchPath(const std::string& path);
    
    // 扫描目录查找模块
    std::vector<CmodInfo> scanDirectory(const std::string& dirPath);
    
    // 刷新注册表
    void refresh();
    
    // 保存注册表
    bool save();
    bool saveAs(const std::string& path);
    
    // 加载注册表
    bool load();
    bool loadFrom(const std::string& path);
    
    // 导出注册表信息
    std::string exportToJson() const;
    std::string exportToXml() const;
    
    // 验证注册表完整性
    bool validate();
    
    // 清理无效记录
    int cleanup();
    
private:
    // 模块存储
    std::unordered_map<std::string, ModuleRecord> modules_;
    
    // 搜索路径
    std::vector<std::string> searchPaths_;
    
    // 注册表文件路径
    std::string registryPath_;
    
    // 是否已修改
    bool isDirty_;
    
    // 构建依赖图
    void buildDependencyGraph();
    
    // 检查循环依赖
    bool checkCircularDependency(const std::string& moduleName, 
                                std::vector<std::string>& visited) const;
    
    // 解析依赖字符串
    std::vector<std::string> parseDependencies(const std::string& depStr) const;
    
    // 生成唯一键
    std::string generateKey(const std::string& name, const std::string& version) const;
    
    // 默认模块路径
    std::vector<std::string> getDefaultSearchPaths() const;
    
    // 序列化/反序列化
    std::string serializeRecord(const ModuleRecord& record) const;
    ModuleRecord deserializeRecord(const std::string& data) const;
};

} // namespace chtl

#endif // CHTL_CMOD_REGISTRY_H