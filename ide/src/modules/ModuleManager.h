#ifndef CHTL_IDE_MODULE_MANAGER_H
#define CHTL_IDE_MODULE_MANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <memory>
#include <vector>
#include <unordered_map>

namespace chtl {
namespace ide {

// 模块类型
enum class ModuleType {
    CMOD,       // CHTL模块
    CJMOD,      // CHTL JavaScript模块
    Unknown
};

// 模块信息
struct ModuleInfo {
    QString name;
    QString version;
    QString author;
    QString description;
    QString license;
    QString homepage;
    QStringList dependencies;
    QString category;
    QString minCHTLVersion;
    QString maxCHTLVersion;
    ModuleType type;
    QString path;           // 模块文件路径
    bool isOfficial;        // 是否官方模块
    bool isInstalled;       // 是否已安装
    QDateTime installDate;  // 安装日期
    
    // 导出信息
    struct ExportItem {
        QString name;
        QString type;  // @Style, @Element, @Var
        QString category;  // Template, Custom
    };
    std::vector<ExportItem> exports;
};

// 模块仓库项
struct ModuleRepositoryItem {
    ModuleInfo info;
    QString downloadUrl;
    qint64 fileSize;
    QString checksum;
    int downloadCount;
    double rating;
    QDateTime publishDate;
    QDateTime updateDate;
};

class ModuleManager : public QObject
{
    Q_OBJECT

public:
    explicit ModuleManager(QObject* parent = nullptr);
    ~ModuleManager();
    
    // 初始化
    void initialize();
    void setModulePaths(const QStringList& paths);
    void addModulePath(const QString& path);
    
    // 扫描和加载
    void scanModules();
    void loadModule(const QString& moduleFile);
    void unloadModule(const QString& moduleName);
    void reloadModule(const QString& moduleName);
    
    // 查询
    QList<ModuleInfo> installedModules() const;
    QList<ModuleInfo> officialModules() const;
    QList<ModuleInfo> userModules() const;
    ModuleInfo moduleInfo(const QString& moduleName) const;
    bool isModuleLoaded(const QString& moduleName) const;
    
    // 安装和卸载
    bool installModule(const QString& moduleFile);
    bool uninstallModule(const QString& moduleName);
    bool updateModule(const QString& moduleName);
    
    // 导入/导出
    bool importModule(const QString& moduleFile, const QString& targetPath);
    bool exportModule(const QString& moduleName, const QString& outputFile);
    
    // 创建模块
    bool createModule(const QString& name, const QString& path, ModuleType type);
    bool createModuleFromTemplate(const QString& templateName, const QString& name, const QString& path);
    
    // 打包
    bool packModule(const QString& modulePath, const QString& outputFile);
    bool unpackModule(const QString& moduleFile, const QString& outputPath);
    
    // 验证
    bool validateModule(const QString& moduleFile);
    QStringList checkDependencies(const QString& moduleName);
    
    // 仓库功能
    void setRepositoryUrl(const QString& url);
    void refreshRepository();
    QList<ModuleRepositoryItem> searchModules(const QString& query, const QString& category = QString());
    bool downloadModule(const QString& moduleName);
    
    // 获取模块内容
    QString getModuleContent(const QString& moduleName, const QString& file);
    QStringList getModuleFiles(const QString& moduleName);
    
signals:
    // 模块事件
    void moduleLoaded(const QString& moduleName);
    void moduleUnloaded(const QString& moduleName);
    void moduleInstalled(const QString& moduleName);
    void moduleUninstalled(const QString& moduleName);
    void moduleUpdated(const QString& moduleName);
    
    // 扫描进度
    void scanStarted();
    void scanProgress(int current, int total);
    void scanFinished();
    
    // 下载进度
    void downloadStarted(const QString& moduleName);
    void downloadProgress(const QString& moduleName, qint64 received, qint64 total);
    void downloadFinished(const QString& moduleName, bool success);
    
    // 错误
    void error(const QString& message);
    
private:
    // 内部方法
    ModuleInfo parseModuleInfo(const QString& infoFile);
    bool extractModuleExports(ModuleInfo& info);
    QString findModuleFile(const QString& moduleName);
    bool verifyModuleStructure(const QString& path);
    void loadOfficialModules();
    
    // 缓存管理
    void saveCache();
    void loadCache();
    
private:
    // 模块路径
    QStringList m_modulePaths;
    QString m_officialModulePath;
    QString m_userModulePath;
    
    // 已加载的模块
    std::unordered_map<QString, ModuleInfo> m_loadedModules;
    
    // 模块缓存
    std::unordered_map<QString, ModuleInfo> m_moduleCache;
    
    // 仓库
    QString m_repositoryUrl;
    std::vector<ModuleRepositoryItem> m_repositoryCache;
    
    // 下载管理
    class DownloadManager;
    std::unique_ptr<DownloadManager> m_downloadManager;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_MODULE_MANAGER_H