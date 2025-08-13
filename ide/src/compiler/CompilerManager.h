#ifndef CHTL_IDE_COMPILER_MANAGER_H
#define CHTL_IDE_COMPILER_MANAGER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <memory>
#include <vector>

namespace chtl {

// 前向声明CHTL编译器相关类
class CHTLContext;
class CHTLGenerator;
class CHTLUnifiedScanner;

namespace ide {

// 编译选项
struct CompileOptions {
    bool optimize = true;
    bool generateSourceMap = false;
    bool minifyOutput = false;
    bool generateComments = true;
    bool validateOnly = false;
    QString outputFormat = "html";  // html, separate (分离的HTML/CSS/JS)
    QString moduleSearchPath;
    QStringList additionalModulePaths;
};

// 编译结果
struct CompileResult {
    bool success = false;
    QString html;
    QString css;
    QString js;
    QString errorMessage;
    QStringList warnings;
    
    // 错误信息
    struct Error {
        int line;
        int column;
        QString message;
        QString file;
        bool isWarning;
    };
    std::vector<Error> errors;
    
    // 生成的文件
    QStringList generatedFiles;
    
    // 编译统计
    int elapsedTime = 0;  // 毫秒
    int linesProcessed = 0;
};

class CompilerManager : public QObject
{
    Q_OBJECT

public:
    explicit CompilerManager(QObject* parent = nullptr);
    ~CompilerManager();
    
    // 编译功能
    CompileResult compile(const QString& sourceCode, const CompileOptions& options = CompileOptions());
    CompileResult compileFile(const QString& fileName, const CompileOptions& options = CompileOptions());
    CompileResult compileProject(const QString& projectPath, const CompileOptions& options = CompileOptions());
    
    // 实时编译（用于预览）
    void startRealtimeCompilation(const QString& sourceCode);
    void stopRealtimeCompilation();
    bool isRealtimeCompiling() const { return m_realtimeCompiling; }
    
    // 验证
    CompileResult validate(const QString& sourceCode);
    
    // 格式化
    QString formatCode(const QString& sourceCode);
    
    // 模块打包
    bool packModule(const QString& modulePath, const QString& outputPath);
    bool unpackModule(const QString& moduleFile, const QString& outputPath);
    
    // 获取编译器信息
    QString compilerVersion() const;
    QStringList supportedFeatures() const;
    
    // 清理
    void clearCache();
    
signals:
    // 编译进度
    void compilationStarted();
    void compilationProgress(int percentage, const QString& status);
    void compilationFinished(const CompileResult& result);
    
    // 实时编译
    void realtimeResult(const CompileResult& result);
    
    // 错误和警告
    void error(const QString& message, int line = -1, int column = -1);
    void warning(const QString& message, int line = -1, int column = -1);
    
private:
    // 内部编译实现
    CompileResult compileInternal(const QString& sourceCode, const CompileOptions& options);
    
    // 解析错误信息
    void parseCompilerOutput(const QString& output, CompileResult& result);
    
    // 使用外部编译器进程
    CompileResult compileWithProcess(const QString& sourceCode, const CompileOptions& options);
    
    // 使用内嵌编译器
    CompileResult compileWithEmbedded(const QString& sourceCode, const CompileOptions& options);
    
    // 实时编译定时器
    void onRealtimeTimeout();
    
private:
    // 编译器进程
    std::unique_ptr<QProcess> m_compilerProcess;
    
    // 内嵌编译器组件
    std::shared_ptr<CHTLContext> m_context;
    std::unique_ptr<CHTLGenerator> m_generator;
    std::unique_ptr<CHTLUnifiedScanner> m_scanner;
    
    // 实时编译
    bool m_realtimeCompiling;
    QString m_realtimeSource;
    QTimer* m_realtimeTimer;
    
    // 缓存
    struct CacheEntry {
        QString sourceHash;
        CompileResult result;
        QDateTime timestamp;
    };
    std::unordered_map<QString, CacheEntry> m_cache;
};

} // namespace ide
} // namespace chtl

#endif // CHTL_IDE_COMPILER_MANAGER_H