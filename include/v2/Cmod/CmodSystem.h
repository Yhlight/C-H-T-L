#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <json/json.h>

namespace chtl::v2::cmod {

/**
 * CMOD 包信息
 */
struct CmodPackage {
    // 基本信息
    std::string name;           // 包名
    std::string version;        // 版本号
    std::string description;    // 描述
    std::string author;         // 作者
    std::string license;        // 许可证
    
    // 入口文件
    std::string main;           // 主入口文件
    std::string style;          // 样式入口
    std::string script;         // 脚本入口
    
    // 依赖
    std::map<std::string, std::string> dependencies;      // 运行时依赖
    std::map<std::string, std::string> devDependencies;   // 开发依赖
    
    // 导出的组件
    std::vector<std::string> exports;
    
    // 元数据
    Json::Value metadata;
};

/**
 * CMOD 组件信息
 */
struct CmodComponent {
    std::string name;           // 组件名
    std::string path;           // 组件路径
    std::string type;           // 组件类型（Element, Style, Var）
    std::vector<std::string> parameters;  // 参数列表
    std::string documentation;  // 文档
};

/**
 * CMOD 解析结果
 */
struct CmodResolveResult {
    bool success = false;
    CmodPackage package;
    std::string packagePath;
    std::vector<CmodComponent> components;
    std::string error;
};

/**
 * CMOD 系统
 * 管理组件包的加载、解析和使用
 */
class CmodSystem {
public:
    CmodSystem();
    ~CmodSystem();
    
    /**
     * 设置包仓库路径
     */
    void setRepositoryPath(const std::string& path);
    
    /**
     * 添加包搜索路径
     */
    void addPackagePath(const std::string& path);
    
    /**
     * 解析 CMOD 包
     */
    CmodResolveResult resolvePackage(const std::string& packageName);
    
    /**
     * 加载包配置文件
     */
    bool loadPackageConfig(const std::string& configPath, CmodPackage& package);
    
    /**
     * 扫描包中的组件
     */
    std::vector<CmodComponent> scanComponents(const std::string& packagePath, 
                                             const CmodPackage& package);
    
    /**
     * 安装 CMOD 包
     */
    bool installPackage(const std::string& packageName, const std::string& version = "");
    
    /**
     * 获取已安装的包列表
     */
    std::vector<CmodPackage> getInstalledPackages();
    
    /**
     * 检查包是否已安装
     */
    bool isPackageInstalled(const std::string& packageName);
    
    /**
     * 获取包的安装路径
     */
    std::string getPackageInstallPath(const std::string& packageName);
    
private:
    /**
     * 解析 cmod.json 文件
     */
    bool parseCmodJson(const Json::Value& json, CmodPackage& package);
    
    /**
     * 解析 package.json 文件（兼容 npm 格式）
     */
    bool parsePackageJson(const Json::Value& json, CmodPackage& package);
    
    /**
     * 验证包的完整性
     */
    bool validatePackage(const CmodPackage& package);
    
    /**
     * 解析组件文件
     */
    CmodComponent parseComponentFile(const std::string& filePath);
    
private:
    std::string repositoryPath_;
    std::vector<std::string> packagePaths_;
    std::map<std::string, CmodPackage> packageCache_;
};

/**
 * CMOD 组件加载器
 * 负责加载和实例化 CMOD 组件
 */
class CmodLoader {
public:
    CmodLoader(CmodSystem* cmodSystem);
    
    /**
     * 加载组件
     */
    std::string loadComponent(const std::string& packageName, 
                             const std::string& componentName);
    
    /**
     * 加载包的所有组件
     */
    std::map<std::string, std::string> loadPackageComponents(const std::string& packageName);
    
    /**
     * 获取组件的 CHTL 代码
     */
    std::string getComponentChtl(const std::string& packageName,
                                const std::string& componentName);
    
private:
    CmodSystem* cmodSystem_;
    std::map<std::string, std::string> componentCache_;
};

/**
 * CMOD 包管理器
 * 提供命令行风格的包管理功能
 */
class CmodPackageManager {
public:
    CmodPackageManager(CmodSystem* cmodSystem);
    
    /**
     * 初始化新的 CMOD 项目
     */
    bool init(const std::string& projectPath);
    
    /**
     * 添加依赖
     */
    bool addDependency(const std::string& packageName, 
                      const std::string& version = "latest");
    
    /**
     * 移除依赖
     */
    bool removeDependency(const std::string& packageName);
    
    /**
     * 更新依赖
     */
    bool updateDependencies();
    
    /**
     * 发布包
     */
    bool publish(const std::string& packagePath);
    
    /**
     * 创建新组件
     */
    bool createComponent(const std::string& componentName,
                        const std::string& componentType);
    
private:
    CmodSystem* cmodSystem_;
    std::string projectPath_;
};

} // namespace chtl::v2::cmod