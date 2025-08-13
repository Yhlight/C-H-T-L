#include <QApplication>
#include <QStyleFactory>
#include <QSplashScreen>
#include <QTimer>
#include "ui/MainWindow.h"
#include "core/Application.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("CHTL IDE");
    app.setApplicationDisplayName("CHTL IDE");
    app.setOrganizationName("CHTL Team");
    app.setOrganizationDomain("chtl.dev");
    
    // 设置应用程序样式
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // 创建启动画面
    QPixmap pixmap(400, 300);
    pixmap.fill(QColor(135, 206, 235)); // 天蓝色，致敬珂朵莉
    
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("CHTL IDE v1.0.0\nInitializing...", 
                      Qt::AlignBottom | Qt::AlignCenter, 
                      Qt::white);
    
    app.processEvents();
    
    // 初始化应用程序核心
    chtl::ide::Application::initialize();
    
    // 创建主窗口
    splash.showMessage("Loading main window...", 
                      Qt::AlignBottom | Qt::AlignCenter, 
                      Qt::white);
    
    chtl::ide::MainWindow window;
    
    // 延迟显示主窗口
    QTimer::singleShot(1500, [&]() {
        splash.close();
        window.show();
    });
    
    return app.exec();
}