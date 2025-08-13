#ifndef CHTL_IMPORT_H
#define CHTL_IMPORT_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include "CHTLContext.h"

namespace chtl {

// 前向声明
class CHTLGenerator;
class TemplateManager;
class CustomManager;
class OriginManager;
class CMODManager;

// 导入类型
enum class ImportType {
    HTML,           // @Html
    STYLE,          // @Style
    JAVASCRIPT,     // @JavaScript
    CHTL,           // @Chtl
    CJMOD,          // @CJmod
    CUSTOM_ELEMENT, // [Custom] @Element
    CUSTOM_STYLE,   // [Custom] @Style
    CUSTOM_VAR,     // [Custom] @Var
    TEMPLATE_ELEMENT, // [Template] @Element
    TEMPLATE_STYLE,   // [Template] @Style
    TEMPLATE_VAR      // [Template] @Var
};

// 导入声明
struct ImportDeclaration {
    ImportType type;
    std::string itemName;      // 要导入的具体项目名（对于Custom和Template）
    std::string sourcePath;    // 源文件路径
    std::string asName;        // as语法指定的别名
    bool hasAsClause;          // 是否有as子句
    bool isWildcard;           // 是否是通配符导入（*）
    std::string wildcardPattern; // 通配符模式（*.cmod, *.chtl等）
};

// 文件搜索路径配置
struct ImportPathConfig {
    std::filesystem::path officialModulePath;  // 官方模块路径
    std::filesystem::path currentDirectory;    // 当前目录
    std::filesystem::path moduleDirectory;     // 当前目录的module文件夹
    bool searchOfficialFirst;                  // 是否优先搜索官方模块
};

// 导入的文件信息
struct ImportedFile {
    std::filesystem::path absolutePath;
    std::filesystem::path relativePath;
    ImportType type;
    std::string content;
    std::string asName;
    bool isProcessed;
    std::vector<ImportDeclaration> dependencies; // 该文件的依赖
};

// 导入管理器
class ImportManager {
private:
    // 已导入的文件（避免重复导入）
    std::unordered_set<std::string> importedFiles;
    
    // 导入的项目映射（名称 -> 文件路径）
    std::unordered_map<std::string, std::string> importedItems;
    
    // 导入路径配置
    ImportPathConfig pathConfig;
    
    // 路径规范化缓存
    std::unordered_map<std::string, std::string> normalizedPaths;
    
    // 循环依赖检测
    std::unordered_set<std::string> currentlyImporting;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
    // 其他管理器的引用
    std::shared_ptr<TemplateManager> templateManager;
    std::shared_ptr<CustomManager> customManager;
    std::shared_ptr<OriginManager> originManager;
    std::shared_ptr<CMODManager> cmodManager;
    
    // 循环依赖检测器
    CircularDependencyDetector dependencyDetector;
    
public:
    ImportManager(std::shared_ptr<CHTLContext> ctx);
    
    // 设置其他管理器
    void setTemplateManager(std::shared_ptr<TemplateManager> mgr) { templateManager = mgr; }
    void setCustomManager(std::shared_ptr<CustomManager> mgr) { customManager = mgr; }
    void setOriginManager(std::shared_ptr<OriginManager> mgr) { originManager = mgr; }
    void setCMODManager(std::shared_ptr<CMODManager> mgr) { cmodManager = mgr; }
    
    // 配置路径
    void configurePaths(const ImportPathConfig& config);
    
    // 处理导入语句
    bool processImport(const ImportDeclaration& decl, CHTLGenerator& generator);
    
    // 批量处理导入
    bool processImports(const std::vector<ImportDeclaration>& declarations, CHTLGenerator& generator);
    
    // 查找文件
    std::filesystem::path findFile(const std::string& path, ImportType type);
    
    // 读取文件内容
    std::string readFileContent(const std::filesystem::path& path);
    
    // 检查循环依赖
    bool checkCircularDependency(const std::string& path);
    
    // 规范化路径
    std::string normalizePath(const std::string& path);
    
    // 获取已导入的文件
    std::shared_ptr<ImportedFile> getImportedFile(const std::string& path) const;
    
    // 清理
    void clear();
};

// 导入处理器
class ImportProcessor {
private:
    ImportManager& manager;
    CHTLGenerator& generator;
    
    // 搜索CHTL文件
    std::string searchChtlFile(const std::string& path);
    
public:
    ImportProcessor(ImportManager& mgr, CHTLGenerator& gen)
        : manager(mgr), generator(gen) {}
    
    // 解析导入语句
    ImportDeclaration parseImportStatement(const std::string& statement);
    
    // 处理不同类型的导入
    bool processHtmlImport(const ImportDeclaration& decl);
    bool processStyleImport(const ImportDeclaration& decl);
    bool processJavaScriptImport(const ImportDeclaration& decl);
    bool processChtlImport(const std::string& path);
    bool processCjmodImport(const std::string& path);
    bool processCustomImport(const ImportDeclaration& decl);
    bool processTemplateImport(const ImportDeclaration& decl);
    
    // 从CHTL文件提取特定项
    bool extractFromChtlFile(const std::string& filePath, 
                           const std::string& itemType, 
                           const std::string& itemName,
                           const std::string& alias = "");
};

// 文件搜索器
class FileSearcher {
private:
    const ImportPathConfig& config;
    
public:
    FileSearcher(const ImportPathConfig& cfg) : config(cfg) {}
    
    // 搜索文件
    std::filesystem::path searchFile(const std::string& name, ImportType type);
    
    // 搜索特定扩展名的文件
    std::filesystem::path searchWithExtension(const std::string& name, 
                                             const std::string& extension);
    
    // 搜索目录中的文件
    std::filesystem::path searchInDirectory(const std::filesystem::path& dir,
                                          const std::string& name,
                                          const std::vector<std::string>& extensions);
    
    // 获取通配符匹配的文件
    std::vector<std::filesystem::path> getWildcardMatches(
        const std::filesystem::path& dir,
        const std::string& pattern);
    
    // 确定文件扩展名
    std::vector<std::string> getExtensionsForType(ImportType type);
    
    // 验证文件路径
    bool isValidFilePath(const std::filesystem::path& path);
};

// 路径处理器
class PathProcessor {
public:
    // 转换点号路径为斜杠路径
    static std::string dotToSlash(const std::string& path);
    
    // 规范化路径（处理不同的表示方式）
    static std::string normalize(const std::string& path);
    
    // 解析路径组件
    struct PathComponents {
        std::string directory;
        std::string filename;
        std::string extension;
        bool hasExtension;
        bool isAbsolute;
        bool isWildcard;
    };
    
    static PathComponents parsePath(const std::string& path);
    
    // 构建完整路径
    static std::filesystem::path buildPath(const std::filesystem::path& base,
                                         const std::string& relative);
    
    // 检查是否是模块名
    static bool isModuleName(const std::string& name);
};

// 循环依赖检测器
class CircularDependencyDetector {
private:
    std::unordered_map<std::string, std::vector<std::string>> dependencyGraph;
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> recursionStack;
    
public:
    // 添加依赖关系
    void addDependency(const std::string& from, const std::string& to);
    
    // 检测循环依赖
    bool hasCircularDependency();
    
    // 获取循环路径
    std::vector<std::string> getCircularPath(const std::string& start);
    
private:
    bool hasCycleUtil(const std::string& node, std::vector<std::string>& path);
};

// 导入解析器辅助函数
namespace ImportHelper {
    // 解析导入类型
    ImportType parseImportType(const std::string& typeStr);
    
    // 解析修饰符（[Custom] 或 [Template]）
    std::pair<std::string, std::string> parseModifier(const std::string& statement);
    
    // 提取as子句
    std::pair<std::string, std::string> extractAsClause(const std::string& statement);
    
    // 验证导入路径
    bool validateImportPath(const std::string& path);
    
    // 判断是否需要创建原始嵌入
    bool shouldCreateOriginNode(ImportType type, bool hasAsClause);
    
    // 获取默认扩展名
    std::string getDefaultExtension(ImportType type);
}

} // namespace chtl

#endif // CHTL_IMPORT_H