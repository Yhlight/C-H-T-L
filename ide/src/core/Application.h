#ifndef CHTL_IDE_APPLICATION_H
#define CHTL_IDE_APPLICATION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <memory>

namespace chtl {
namespace ide {

class CompilerManager;
class ModuleManager;
class ProjectManager;
class ConfigManager;

class Application : public QObject
{
    Q_OBJECT

public:
    static Application* instance();
    static void initialize();
    static void shutdown();
    
    // 获取各种管理器
    CompilerManager* compilerManager() const { return m_compilerManager.get(); }
    ModuleManager* moduleManager() const { return m_moduleManager.get(); }
    ProjectManager* projectManager() const { return m_projectManager.get(); }
    ConfigManager* configManager() const { return m_configManager.get(); }
    
    // 获取路径
    QString applicationPath() const;
    QString modulesPath() const;
    QString templatesPath() const;
    QString settingsPath() const;
    
    // 版本信息
    QString version() const { return "1.0.0"; }
    QString buildDate() const { return __DATE__; }
    
signals:
    void initialized();
    void aboutToQuit();
    
private:
    Application(QObject* parent = nullptr);
    ~Application();
    
    void initializeManagers();
    void loadSettings();
    void saveSettings();
    
private:
    static Application* s_instance;
    
    std::unique_ptr<CompilerManager> m_compilerManager;
    std::unique_ptr<ModuleManager> m_moduleManager;
    std::unique_ptr<ProjectManager> m_projectManager;
    std::unique_ptr<ConfigManager> m_configManager;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_APPLICATION_H