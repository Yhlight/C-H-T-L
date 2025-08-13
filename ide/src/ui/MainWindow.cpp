#include "MainWindow.h"
#include "editor/EditorWidget.h"
#include "preview/PreviewWidget.h"
#include "compiler/CompilerManager.h"
#include "modules/ModuleManager.h"
#include "project/ProjectManager.h"
#include "core/Application.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QSplitter>
#include <QTreeWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QSettings>

namespace chtl {
namespace ide {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_realtimeTimer(nullptr)
{
    setupUi();
    createMenus();
    createToolBars();
    createDockWidgets();
    createStatusBar();
    createConnections();
    loadSettings();
    
    // 设置窗口标题
    setWindowTitle("CHTL IDE - 致敬珂朵莉");
    
    // 创建一个新文件开始
    onNewFile();
}

MainWindow::~MainWindow()
{
    saveSettings();
}

void MainWindow::setupUi()
{
    // 创建中央分割器
    m_centralSplitter = new QSplitter(Qt::Horizontal, this);
    
    // 创建编辑器标签页
    m_editorTabs = new QTabWidget(this);
    m_editorTabs->setTabsClosable(true);
    m_editorTabs->setMovable(true);
    
    m_centralSplitter->addWidget(m_editorTabs);
    m_centralSplitter->setStretchFactor(0, 1);
    
    setCentralWidget(m_centralSplitter);
    
    // 设置窗口大小
    resize(1400, 900);
}

void MainWindow::createMenus()
{
    // 文件菜单
    m_fileMenu = menuBar()->addMenu("文件(&F)");
    
    m_newFileAction = m_fileMenu->addAction("新建文件(&N)", this, &MainWindow::onNewFile);
    m_newFileAction->setShortcut(QKeySequence::New);
    
    m_openFileAction = m_fileMenu->addAction("打开文件(&O)...", this, &MainWindow::onOpenFile);
    m_openFileAction->setShortcut(QKeySequence::Open);
    
    m_fileMenu->addSeparator();
    
    m_saveAction = m_fileMenu->addAction("保存(&S)", this, &MainWindow::onSave);
    m_saveAction->setShortcut(QKeySequence::Save);
    
    m_saveAsAction = m_fileMenu->addAction("另存为(&A)...", this, &MainWindow::onSaveAs);
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    
    m_fileMenu->addSeparator();
    
    m_exitAction = m_fileMenu->addAction("退出(&X)", this, &MainWindow::onExit);
    m_exitAction->setShortcut(QKeySequence::Quit);
    
    // 构建菜单
    m_buildMenu = menuBar()->addMenu("构建(&B)");
    
    m_buildAction = m_buildMenu->addAction("构建(&B)", this, &MainWindow::onBuild);
    m_buildAction->setShortcut(Qt::CTRL + Qt::Key_B);
    
    m_runAction = m_buildMenu->addAction("运行(&R)", this, &MainWindow::onRun);
    m_runAction->setShortcut(Qt::Key_F5);
    
    m_buildAndRunAction = m_buildMenu->addAction("构建并运行(&U)", this, &MainWindow::onBuildAndRun);
    m_buildAndRunAction->setShortcut(Qt::Key_F6);
    
    // 视图菜单
    m_viewMenu = menuBar()->addMenu("视图(&V)");
    
    // 帮助菜单
    m_helpMenu = menuBar()->addMenu("帮助(&H)");
    
    m_aboutAction = m_helpMenu->addAction("关于 CHTL IDE(&A)", this, &MainWindow::onAbout);
}

void MainWindow::createToolBars()
{
    // 文件工具栏
    m_fileToolBar = addToolBar("文件");
    m_fileToolBar->addAction(m_newFileAction);
    m_fileToolBar->addAction(m_openFileAction);
    m_fileToolBar->addAction(m_saveAction);
    
    // 构建工具栏
    m_buildToolBar = addToolBar("构建");
    m_buildToolBar->addAction(m_buildAction);
    m_buildToolBar->addAction(m_runAction);
    m_buildToolBar->addAction(m_buildAndRunAction);
}

void MainWindow::createDockWidgets()
{
    // 项目浏览器
    m_projectExplorerDock = new QDockWidget("项目浏览器", this);
    m_projectExplorer = new QTreeWidget(this);
    m_projectExplorer->setHeaderLabel("项目文件");
    m_projectExplorerDock->setWidget(m_projectExplorer);
    addDockWidget(Qt::LeftDockWidgetArea, m_projectExplorerDock);
    
    // 模块浏览器
    m_moduleBrowserDock = new QDockWidget("模块浏览器", this);
    m_moduleBrowser = new QListWidget(this);
    
    // 添加Chtholly模块到列表
    QListWidgetItem* chthollyItem = new QListWidgetItem("Chtholly - 珂朵莉主题模块");
    chthollyItem->setToolTip("基于《末日时在做什么？》的珂朵莉主题UI模块");
    m_moduleBrowser->addItem(chthollyItem);
    
    m_moduleBrowserDock->setWidget(m_moduleBrowser);
    addDockWidget(Qt::LeftDockWidgetArea, m_moduleBrowserDock);
    
    // 预览面板
    m_previewDock = new QDockWidget("预览", this);
    m_preview = new PreviewWidget(this);
    m_previewDock->setWidget(m_preview);
    addDockWidget(Qt::RightDockWidgetArea, m_previewDock);
    
    // 输出面板
    m_outputDock = new QDockWidget("输出", this);
    m_output = new QTextEdit(this);
    m_output->setReadOnly(true);
    m_outputDock->setWidget(m_output);
    addDockWidget(Qt::BottomDockWidgetArea, m_outputDock);
    
    // 标签化左侧dock
    tabifyDockWidget(m_projectExplorerDock, m_moduleBrowserDock);
    m_projectExplorerDock->raise();
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("就绪");
    
    // 添加位置标签
    m_positionLabel = new QLabel("行 1, 列 1", this);
    statusBar()->addPermanentWidget(m_positionLabel);
}

void MainWindow::createConnections()
{
    // 编辑器标签页信号
    connect(m_editorTabs, &QTabWidget::currentChanged, 
            this, &MainWindow::onCurrentEditorChanged);
    connect(m_editorTabs, &QTabWidget::tabCloseRequested,
            this, &MainWindow::onEditorRequestClose);
    
    // 实时编译定时器
    m_realtimeTimer = new QTimer(this);
    m_realtimeTimer->setSingleShot(true);
    m_realtimeTimer->setInterval(500); // 500ms延迟
    connect(m_realtimeTimer, &QTimer::timeout, this, &MainWindow::performRealtimeCompile);
}

void MainWindow::onNewFile()
{
    // 创建新的编辑器
    EditorWidget* editor = new EditorWidget(this);
    editor->newFile();
    
    // 添加到标签页
    int index = m_editorTabs->addTab(editor, "未命名.chtl");
    m_editorTabs->setCurrentIndex(index);
    
    // 连接信号
    connect(editor, &EditorWidget::textChanged, [this]() {
        if (m_realtimeTimer) {
            m_realtimeTimer->stop();
            m_realtimeTimer->start();
        }
    });
    
    connect(editor, &EditorWidget::cursorPositionChanged,
            [this](int line, int column) {
        m_positionLabel->setText(QString("行 %1, 列 %2").arg(line).arg(column));
    });
    
    // 设置示例代码
    QString exampleCode = R"(// CHTL IDE 示例代码
// 使用Chtholly模块创建美观的页面

[Import] @Chtl from Chtholly

html
{
    head
    {
        meta { charset: "UTF-8"; }
        title: "CHTL IDE 示例";
        
        style
        {
            body {
                @Style Chtholly.ChthollysBase;
                background: Chtholly.ChthollysColors(backgroundColor);
                padding: Chtholly.ChthollysSpacing(xl);
            }
        }
    }
    
    body
    {
        div
        {
            style
            {
                @Style Chtholly.FairyCard;
                max-width: 800px;
                margin: 0 auto;
                padding: Chtholly.ChthollysSpacing(xl);
            }
            
            h1
            {
                style { @Style Chtholly.ChthollysH1; }
                text { "欢迎使用 CHTL IDE" }
            }
            
            p
            {
                style
                {
                    font-size: Chtholly.ChthollysTypography(largeFontSize);
                    color: Chtholly.ChthollysColors(melancholyBlue);
                    margin-bottom: Chtholly.ChthollysSpacing(lg);
                }
                text { "这是一个支持所有CHTL语法特性的集成开发环境" }
            }
            
            -- 使用珂朵莉主题的按钮
            button
            {
                style { @Style Chtholly.SenioriousPrimaryButton; }
                text { "开始探索" }
                
                script
                {
                    {{button}}->listen({
                        click: () => {
                            alert('欢迎来到CHTL的世界！');
                        }
                    });
                }
            }
        }
    }
})";
    
    editor->setPlainText(exampleCode);
}

void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "打开CHTL文件", "", "CHTL文件 (*.chtl);;所有文件 (*)");
    
    if (!fileName.isEmpty()) {
        EditorWidget* editor = new EditorWidget(this);
        if (editor->loadFile(fileName)) {
            int index = m_editorTabs->addTab(editor, QFileInfo(fileName).fileName());
            m_editorTabs->setCurrentIndex(index);
            
            // 连接信号
            connect(editor, &EditorWidget::textChanged, [this]() {
                if (m_realtimeTimer) {
                    m_realtimeTimer->stop();
                    m_realtimeTimer->start();
                }
            });
        } else {
            delete editor;
            QMessageBox::warning(this, "错误", "无法打开文件");
        }
    }
}

void MainWindow::onSave()
{
    EditorWidget* editor = qobject_cast<EditorWidget*>(m_editorTabs->currentWidget());
    if (editor) {
        if (!editor->saveFile()) {
            onSaveAs();
        }
    }
}

void MainWindow::onSaveAs()
{
    EditorWidget* editor = qobject_cast<EditorWidget*>(m_editorTabs->currentWidget());
    if (editor) {
        QString fileName = QFileDialog::getSaveFileName(this,
            "保存CHTL文件", "", "CHTL文件 (*.chtl)");
        
        if (!fileName.isEmpty()) {
            if (editor->saveAs(fileName)) {
                m_editorTabs->setTabText(m_editorTabs->currentIndex(), 
                                        QFileInfo(fileName).fileName());
            }
        }
    }
}

void MainWindow::onBuild()
{
    EditorWidget* editor = qobject_cast<EditorWidget*>(m_editorTabs->currentWidget());
    if (!editor) return;
    
    // 清空输出
    m_output->clear();
    m_output->append("开始构建...\n");
    
    // 获取编译器管理器
    CompilerManager* compiler = Application::instance()->compilerManager();
    
    // 编译选项
    CompileOptions options;
    options.optimize = true;
    options.generateComments = false;
    
    // 编译
    CompileResult result = compiler->compile(editor->toPlainText(), options);
    
    if (result.success) {
        m_output->append("构建成功！\n");
        
        // 更新预览
        m_preview->setContent(result.html, result.css, result.js);
        
        // 显示统计信息
        m_output->append(QString("处理行数: %1\n").arg(result.linesProcessed));
        m_output->append(QString("耗时: %1 ms\n").arg(result.elapsedTime));
    } else {
        m_output->append("构建失败！\n");
        m_output->append(result.errorMessage + "\n");
        
        // 显示错误
        for (const auto& error : result.errors) {
            QString errorMsg = QString("[%1:%2] %3")
                .arg(error.line)
                .arg(error.column)
                .arg(error.message);
            m_output->append(errorMsg + "\n");
            
            // 在编辑器中标记错误
            editor->addError(error.line, error.column, error.message, error.isWarning);
        }
    }
    
    statusBar()->showMessage(result.success ? "构建成功" : "构建失败", 3000);
}

void MainWindow::onRun()
{
    // 如果预览中没有内容，先构建
    if (m_preview->currentUrl().isEmpty()) {
        onBuild();
    }
    
    // 刷新预览
    m_preview->refresh();
}

void MainWindow::onBuildAndRun()
{
    onBuild();
    if (m_preview->currentUrl().isEmpty()) {
        onRun();
    }
}

void MainWindow::performRealtimeCompile()
{
    EditorWidget* editor = qobject_cast<EditorWidget*>(m_editorTabs->currentWidget());
    if (!editor) return;
    
    // 获取编译器管理器
    CompilerManager* compiler = Application::instance()->compilerManager();
    
    // 快速编译选项
    CompileOptions options;
    options.optimize = false;
    options.validateOnly = false;
    
    // 编译
    CompileResult result = compiler->compile(editor->toPlainText(), options);
    
    if (result.success) {
        // 更新预览
        m_preview->setContent(result.html, result.css, result.js);
        
        // 清除错误标记
        editor->clearErrors();
    } else {
        // 显示错误
        editor->clearErrors();
        for (const auto& error : result.errors) {
            editor->addError(error.line, error.column, error.message, error.isWarning);
        }
    }
}

void MainWindow::onCurrentEditorChanged(int index)
{
    if (index >= 0) {
        // 触发实时编译
        if (m_realtimeTimer) {
            m_realtimeTimer->stop();
            m_realtimeTimer->start();
        }
    }
}

void MainWindow::onEditorRequestClose(int index)
{
    EditorWidget* editor = qobject_cast<EditorWidget*>(m_editorTabs->widget(index));
    if (editor && editor->isModified()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
            "保存文件",
            "文件已修改，是否保存？",
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (reply == QMessageBox::Save) {
            if (!editor->saveFile()) {
                return;
            }
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    
    m_editorTabs->removeTab(index);
    delete editor;
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "关于 CHTL IDE",
        "<h2>CHTL IDE v1.0.0</h2>"
        "<p>一个功能完整的CHTL集成开发环境</p>"
        "<p>支持所有CHTL语法特性：</p>"
        "<ul>"
        "<li>完整的语法高亮和代码补全</li>"
        "<li>实时编译和错误提示</li>"
        "<li>内置官方模块（包括珂朵莉主题）</li>"
        "<li>实时预览和设备模拟</li>"
        "<li>项目管理和模块打包</li>"
        "</ul>"
        "<p>致敬《末日时在做什么？》中最幸福的女孩 —— 珂朵莉</p>"
        "<p>© 2024 CHTL Team</p>");
}

void MainWindow::onExit()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    // 检查所有编辑器是否有未保存的更改
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        EditorWidget* editor = qobject_cast<EditorWidget*>(m_editorTabs->widget(i));
        if (editor && editor->isModified()) {
            m_editorTabs->setCurrentIndex(i);
            
            QMessageBox::StandardButton reply = QMessageBox::question(this,
                "保存文件",
                QString("文件 %1 已修改，是否保存？").arg(m_editorTabs->tabText(i)),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            
            if (reply == QMessageBox::Save) {
                if (!editor->saveFile()) {
                    event->ignore();
                    return;
                }
            } else if (reply == QMessageBox::Cancel) {
                event->ignore();
                return;
            }
        }
    }
    
    event->accept();
}

void MainWindow::loadSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

} // namespace ide
} // namespace chtl