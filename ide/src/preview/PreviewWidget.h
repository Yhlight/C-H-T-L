#ifndef CHTL_IDE_PREVIEW_WIDGET_H
#define CHTL_IDE_PREVIEW_WIDGET_H

#include <QWidget>
#include <QString>
#include <memory>

class QWebEngineView;
class QWebEngineProfile;
class QToolBar;
class QComboBox;
class QLabel;
class QSplitter;

namespace chtl {
namespace ide {

class DevToolsWidget;

class PreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget* parent = nullptr);
    ~PreviewWidget();
    
    // 设置内容
    void setHtml(const QString& html, const QString& baseUrl = QString());
    void setContent(const QString& html, const QString& css, const QString& js);
    void clear();
    
    // 刷新
    void refresh();
    void reload();
    
    // 导航
    void back();
    void forward();
    void home();
    
    // 缩放
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void setZoomFactor(qreal factor);
    
    // 设备模拟
    void setDeviceEmulation(const QString& device);
    void setViewportSize(int width, int height);
    void setUserAgent(const QString& userAgent);
    
    // 开发者工具
    void toggleDevTools();
    bool isDevToolsVisible() const;
    
    // 截图
    void captureScreenshot(const QString& fileName);
    
    // 获取当前URL
    QString currentUrl() const;
    
signals:
    void urlChanged(const QUrl& url);
    void loadStarted();
    void loadProgress(int progress);
    void loadFinished(bool success);
    void titleChanged(const QString& title);
    void consoleMessage(const QString& message, int lineNumber);
    
private slots:
    void onLoadStarted();
    void onLoadProgress(int progress);
    void onLoadFinished(bool success);
    void onUrlChanged(const QUrl& url);
    void onDeviceChanged(int index);
    void onConsoleMessage(int level, const QString& message, int lineNumber, const QString& sourceId);
    
private:
    void setupUi();
    void createToolBar();
    void createDeviceProfiles();
    void applyDeviceProfile(const QString& device);
    
    // 生成完整的HTML页面
    QString generateFullHtml(const QString& body, const QString& css, const QString& js);
    
private:
    // UI组件
    QSplitter* m_splitter;
    QWebEngineView* m_webView;
    std::unique_ptr<DevToolsWidget> m_devTools;
    QToolBar* m_toolBar;
    
    // 工具栏控件
    QAction* m_backAction;
    QAction* m_forwardAction;
    QAction* m_refreshAction;
    QAction* m_homeAction;
    QAction* m_zoomInAction;
    QAction* m_zoomOutAction;
    QAction* m_devToolsAction;
    QAction* m_screenshotAction;
    QComboBox* m_deviceCombo;
    QLabel* m_statusLabel;
    
    // Web引擎配置
    QWebEngineProfile* m_profile;
    
    // 设备配置
    struct DeviceProfile {
        QString name;
        int width;
        int height;
        qreal pixelRatio;
        QString userAgent;
        bool isMobile;
    };
    
    std::vector<DeviceProfile> m_deviceProfiles;
    
    // 当前内容
    QString m_currentHtml;
    QString m_currentCss;
    QString m_currentJs;
    
    // 基础模板
    static const QString s_htmlTemplate;
};

// 开发者工具面板
class DevToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DevToolsWidget(QWidget* parent = nullptr);
    
    void setWebView(QWebEngineView* webView);
    void addConsoleMessage(const QString& message, int lineNumber = -1);
    void clearConsole();
    
private:
    void setupUi();
    
private:
    QWebEngineView* m_devToolsView;
    QTextEdit* m_consoleOutput;
    QTabWidget* m_tabWidget;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_PREVIEW_WIDGET_H