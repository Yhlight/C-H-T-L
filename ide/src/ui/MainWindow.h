#ifndef CHTL_IDE_MAINWINDOW_H
#define CHTL_IDE_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class QSplitter;
class QTabWidget;
class QDockWidget;
class QToolBar;
class QStatusBar;
class QMenu;
class QAction;

namespace chtl {
namespace ide {

class EditorWidget;
class ProjectExplorer;
class ModuleBrowser;
class PreviewWidget;
class OutputPanel;
class SymbolOutline;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    // 文件菜单
    void onNewFile();
    void onNewProject();
    void onOpenFile();
    void onOpenProject();
    void onSave();
    void onSaveAs();
    void onSaveAll();
    void onExit();
    
    // 编辑菜单
    void onUndo();
    void onRedo();
    void onCut();
    void onCopy();
    void onPaste();
    void onFind();
    void onReplace();
    void onGoToLine();
    
    // 视图菜单
    void onToggleProjectExplorer();
    void onToggleModuleBrowser();
    void onTogglePreview();
    void onToggleOutput();
    void onToggleSymbolOutline();
    void onToggleFullScreen();
    
    // 构建菜单
    void onBuild();
    void onRun();
    void onBuildAndRun();
    void onClean();
    void onRebuild();
    void onPackModule();
    
    // 工具菜单
    void onPreferences();
    void onCHTLDocumentation();
    void onModuleManager();
    void onTemplateManager();
    
    // 帮助菜单
    void onAbout();
    void onAboutQt();
    void onCheckForUpdates();
    void onReportBug();
    
    // 编辑器相关
    void onCurrentEditorChanged(int index);
    void onEditorModified();
    void onEditorRequestClose(int index);
    
    // 输出相关
    void onCompilerOutput(const QString& output);
    void onCompilerError(const QString& error);
    
private:
    void setupUi();
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createStatusBar();
    void createConnections();
    void loadSettings();
    void saveSettings();
    
    // 中央部件
    QSplitter* m_centralSplitter;
    QTabWidget* m_editorTabs;
    
    // Dock窗口
    QDockWidget* m_projectExplorerDock;
    QDockWidget* m_moduleBrowserDock;
    QDockWidget* m_previewDock;
    QDockWidget* m_outputDock;
    QDockWidget* m_symbolOutlineDock;
    
    // 面板
    std::unique_ptr<ProjectExplorer> m_projectExplorer;
    std::unique_ptr<ModuleBrowser> m_moduleBrowser;
    std::unique_ptr<PreviewWidget> m_preview;
    std::unique_ptr<OutputPanel> m_output;
    std::unique_ptr<SymbolOutline> m_symbolOutline;
    
    // 菜单
    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_viewMenu;
    QMenu* m_buildMenu;
    QMenu* m_toolsMenu;
    QMenu* m_helpMenu;
    
    // 工具栏
    QToolBar* m_fileToolBar;
    QToolBar* m_editToolBar;
    QToolBar* m_buildToolBar;
    
    // 动作
    // 文件动作
    QAction* m_newFileAction;
    QAction* m_newProjectAction;
    QAction* m_openFileAction;
    QAction* m_openProjectAction;
    QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_saveAllAction;
    QAction* m_exitAction;
    
    // 编辑动作
    QAction* m_undoAction;
    QAction* m_redoAction;
    QAction* m_cutAction;
    QAction* m_copyAction;
    QAction* m_pasteAction;
    QAction* m_findAction;
    QAction* m_replaceAction;
    QAction* m_goToLineAction;
    
    // 视图动作
    QAction* m_toggleProjectExplorerAction;
    QAction* m_toggleModuleBrowserAction;
    QAction* m_togglePreviewAction;
    QAction* m_toggleOutputAction;
    QAction* m_toggleSymbolOutlineAction;
    QAction* m_toggleFullScreenAction;
    
    // 构建动作
    QAction* m_buildAction;
    QAction* m_runAction;
    QAction* m_buildAndRunAction;
    QAction* m_cleanAction;
    QAction* m_rebuildAction;
    QAction* m_packModuleAction;
    
    // 工具动作
    QAction* m_preferencesAction;
    QAction* m_chtlDocumentationAction;
    QAction* m_moduleManagerAction;
    QAction* m_templateManagerAction;
    
    // 帮助动作
    QAction* m_aboutAction;
    QAction* m_aboutQtAction;
    QAction* m_checkForUpdatesAction;
    QAction* m_reportBugAction;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_MAINWINDOW_H