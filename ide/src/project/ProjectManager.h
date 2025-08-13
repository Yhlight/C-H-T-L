#ifndef CHTL_IDE_PROJECT_MANAGER_H
#define CHTL_IDE_PROJECT_MANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <memory>
#include <vector>

namespace chtl {
namespace ide {

// 项目类型
enum class ProjectType {
    SingleFile,     // 单文件项目
    Application,    // 应用程序
    Module,         // 模块项目
    Website,        // 网站项目
    Custom          // 自定义项目
};

// 项目配置
struct ProjectConfig {
    QString name;
    QString version;
    QString description;
    QString author;
    QString license;
    ProjectType type;
    
    // 构建配置
    struct BuildConfig {
        bool optimize = true;
        bool minify = false;
        bool generateSourceMap = false;
        QString outputDirectory = "dist";
        QString outputFormat = "html";  // html, separate
        QStringList excludeFiles;
        QStringList includeFiles;
    } build;
    
    // 模块配置
    struct ModuleConfig {
        QStringList dependencies;
        QStringList localModules;
        QStringList modulePaths;
    } modules;
    
    // 运行配置
    struct RunConfig {
        QString serverPort = "8080";
        QString serverHost = "localhost";
        bool autoReload = true;
        bool openBrowser = true;
    } run;
    
    // 自定义配置
    QMap<QString, QString> custom;
};

// 项目文件信息
struct ProjectFile {
    QString path;           // 相对路径
    QString absolutePath;   // 绝对路径
    QString type;           // 文件类型
    bool isModified;        // 是否修改
    QDateTime lastModified; // 最后修改时间
};

// 项目
class Project {
public:
    Project();
    ~Project();
    
    // 基本信息
    QString name() const { return m_config.name; }
    QString path() const { return m_path; }
    QString rootPath() const { return m_rootPath; }
    ProjectType type() const { return m_config.type; }
    ProjectConfig& config() { return m_config; }
    const ProjectConfig& config() const { return m_config; }
    
    // 文件管理
    void addFile(const QString& filePath);
    void removeFile(const QString& filePath);
    void renameFile(const QString& oldPath, const QString& newPath);
    QList<ProjectFile> files() const;
    ProjectFile file(const QString& path) const;
    bool hasFile(const QString& path) const;
    QString mainFile() const { return m_mainFile; }
    void setMainFile(const QString& file) { m_mainFile = file; }
    
    // 加载和保存
    bool load(const QString& projectFile);
    bool save();
    bool saveAs(const QString& projectFile);
    
    // 状态
    bool isModified() const { return m_modified; }
    void setModified(bool modified) { m_modified = modified; }
    
private:
    QString m_path;         // 项目文件路径
    QString m_rootPath;     // 项目根目录
    QString m_mainFile;     // 主文件
    ProjectConfig m_config; // 项目配置
    std::vector<ProjectFile> m_files;  // 文件列表
    bool m_modified;        // 是否修改
};

class ProjectManager : public QObject
{
    Q_OBJECT

public:
    explicit ProjectManager(QObject* parent = nullptr);
    ~ProjectManager();
    
    // 项目操作
    Project* createProject(const QString& name, const QString& path, ProjectType type);
    Project* openProject(const QString& projectFile);
    void closeProject(Project* project);
    void closeAllProjects();
    
    // 当前项目
    Project* currentProject() const { return m_currentProject; }
    void setCurrentProject(Project* project);
    
    // 项目列表
    QList<Project*> openProjects() const;
    Project* findProject(const QString& path) const;
    
    // 最近项目
    QStringList recentProjects() const;
    void addRecentProject(const QString& projectFile);
    void clearRecentProjects();
    
    // 项目模板
    QStringList projectTemplates() const;
    bool createProjectFromTemplate(const QString& templateName, 
                                  const QString& projectName,
                                  const QString& projectPath);
    
    // 构建和运行
    void buildProject(Project* project);
    void runProject(Project* project);
    void cleanProject(Project* project);
    void rebuildProject(Project* project);
    
    // 文件监控
    void startFileWatcher(Project* project);
    void stopFileWatcher(Project* project);
    
signals:
    // 项目事件
    void projectCreated(Project* project);
    void projectOpened(Project* project);
    void projectClosed(Project* project);
    void projectModified(Project* project);
    void currentProjectChanged(Project* project);
    
    // 文件事件
    void fileAdded(Project* project, const QString& file);
    void fileRemoved(Project* project, const QString& file);
    void fileRenamed(Project* project, const QString& oldName, const QString& newName);
    void fileModified(Project* project, const QString& file);
    
    // 构建事件
    void buildStarted(Project* project);
    void buildProgress(Project* project, int percentage, const QString& message);
    void buildFinished(Project* project, bool success);
    
private:
    void loadRecentProjects();
    void saveRecentProjects();
    void loadProjectTemplates();
    
private:
    std::vector<std::unique_ptr<Project>> m_projects;
    Project* m_currentProject;
    QStringList m_recentProjects;
    QStringList m_projectTemplates;
    
    // 文件监控
    class FileWatcher;
    std::unique_ptr<FileWatcher> m_fileWatcher;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_PROJECT_MANAGER_H