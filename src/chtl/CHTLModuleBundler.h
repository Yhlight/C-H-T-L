#ifndef CHTL_MODULE_BUNDLER_H
#define CHTL_MODULE_BUNDLER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

namespace chtl {

// 模块类型
enum class ModuleType {
    CHTL,       // CHTL文件
    JavaScript, // JavaScript文件
    CSS,        // CSS文件
    Asset,      // 静态资源（图片、字体等）
    Unknown
};

// 模块信息
struct ModuleInfo {
    std::string id;                  // 模块ID（通常是路径）
    std::string content;             // 模块内容
    ModuleType type;                 // 模块类型
    fs::path absolutePath;           // 绝对路径
    fs::path relativePath;           // 相对路径
    std::vector<std::string> dependencies;  // 依赖的其他模块
    bool isEntry;                    // 是否是入口模块
    bool isExternal;                 // 是否是外部模块（不打包）
};

// 打包选项
struct BundleOptions {
    // 基本选项
    std::vector<fs::path> entryPoints;     // 入口文件
    fs::path outputPath;                   // 输出路径
    std::string outputName;                // 输出文件名
    bool minify = true;                    // 是否压缩
    bool sourceMaps = true;                // 是否生成source map
    
    // 模块解析选项
    std::vector<fs::path> modulePaths;     // 模块搜索路径
    std::unordered_map<std::string, std::string> alias;  // 路径别名
    std::vector<std::string> externals;    // 外部模块（不打包）
    
    // 输出格式
    enum OutputFormat {
        SingleFile,    // 单文件输出
        MultiFile,     // 多文件输出（保持目录结构）
        ESModule,      // ES模块格式
        CommonJS,      // CommonJS格式
        IIFE          // 立即执行函数格式
    } format = SingleFile;
    
    // 高级选项
    bool treeShaking = true;               // 移除未使用代码
    bool scopeHoisting = true;             // 作用域提升
    bool codeSpitting = false;             // 代码分割
    size_t chunkSizeLimit = 500 * 1024;   // 分块大小限制（字节）
};

// 打包结果
struct BundleResult {
    bool success;
    std::string errorMessage;
    
    // 输出文件
    struct OutputFile {
        fs::path path;
        std::string content;
        std::string sourceMapContent;  // 如果有source map
    };
    std::vector<OutputFile> files;
    
    // 统计信息
    struct Stats {
        size_t totalModules;
        size_t totalSize;
        size_t outputSize;
        std::unordered_map<ModuleType, size_t> modulesByType;
        double buildTime;  // 秒
    } stats;
};

// 依赖解析器
class DependencyResolver {
public:
    explicit DependencyResolver(const BundleOptions& options);
    
    // 解析模块依赖
    std::vector<std::string> resolveDependencies(const ModuleInfo& module);
    
    // 解析模块路径
    fs::path resolveModulePath(const std::string& request, const fs::path& from);
    
private:
    const BundleOptions& options;
    
    // 解析策略
    fs::path resolveAsFile(const fs::path& path);
    fs::path resolveAsDirectory(const fs::path& path);
    fs::path resolveNodeModules(const std::string& request, const fs::path& from);
    
    // 从内容提取依赖
    std::vector<std::string> extractCHTLImports(const std::string& content);
    std::vector<std::string> extractJSImports(const std::string& content);
    std::vector<std::string> extractCSSImports(const std::string& content);
};

// 模块打包器
class ModuleBundler {
public:
    explicit ModuleBundler(const BundleOptions& options);
    
    // 执行打包
    BundleResult bundle();
    
    // 添加插件
    using TransformFunction = std::function<std::string(const ModuleInfo&, const std::string&)>;
    void addTransform(ModuleType type, TransformFunction transform);
    
    // 进度回调
    using ProgressCallback = std::function<void(const std::string& message, double progress)>;
    void setProgressCallback(ProgressCallback callback);
    
private:
    BundleOptions options;
    std::unique_ptr<DependencyResolver> resolver;
    std::unordered_map<std::string, std::unique_ptr<ModuleInfo>> modules;
    std::unordered_set<std::string> processedModules;
    std::vector<std::string> moduleOrder;  // 拓扑排序后的模块顺序
    
    // 转换函数
    std::unordered_map<ModuleType, std::vector<TransformFunction>> transforms;
    
    // 进度回调
    ProgressCallback progressCallback;
    
    // 内部方法
    void loadEntryPoints();
    void loadModule(const fs::path& path, bool isEntry = false);
    void resolveAllDependencies();
    void performTopologicalSort();
    void applyTransforms();
    void generateOutput();
    
    // 模块处理
    ModuleType detectModuleType(const fs::path& path);
    std::string readModuleContent(const fs::path& path);
    std::string transformModule(const ModuleInfo& module);
    
    // 输出生成
    std::string generateSingleFileOutput();
    std::vector<BundleResult::OutputFile> generateMultiFileOutput();
    std::string wrapModule(const ModuleInfo& module, const std::string& content);
    
    // 优化
    void performTreeShaking();
    void performScopeHoisting();
    void performCodeSplitting();
    
    // 工具方法
    void reportProgress(const std::string& message, double progress);
    std::string generateModuleId(const fs::path& path);
};

// 内置转换器
class BuiltinTransforms {
public:
    // CHTL转换（编译为HTML/CSS/JS）
    static std::string transformCHTL(const ModuleInfo& module, const std::string& content);
    
    // JS优化
    static std::string optimizeJS(const ModuleInfo& module, const std::string& content);
    
    // CSS处理
    static std::string processCSS(const ModuleInfo& module, const std::string& content);
    
    // 资源处理
    static std::string processAsset(const ModuleInfo& module, const std::string& content);
};

} // namespace chtl

#endif // CHTL_MODULE_BUNDLER_H