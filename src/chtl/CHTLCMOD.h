#ifndef CHTL_CMOD_H
#define CHTL_CMOD_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>
#include <filesystem>
#include "CHTLContext.h"

namespace chtl {

// 前向声明
class CHTLGenerator;
class ImportManager;

// 模块信息结构
struct CMODInfo {
    std::string name;
    std::string version;
    std::string description;
    std::string author;
    std::string license;
    std::string dependencies;
    std::string category;
    std::string minCHTLVersion;
    std::string maxCHTLVersion;
    
    // 验证信息完整性
    bool isValid() const;
    std::string toString() const;
};

// 导出项
struct CMODExportItem {
    std::string type;      // @Style, @Element, @Var
    std::string category;  // [Template] or [Custom]
    std::string name;
};

// 导出表
struct CMODExportTable {
    std::vector<CMODExportItem> styles;
    std::vector<CMODExportItem> elements;
    std::vector<CMODExportItem> variables;
    
    // 是否显式定义（如果为true，只导出明确列出的项）
    bool isExplicit = false;
    
    // 添加导出项
    void addExport(const std::string& type, const std::string& category, const std::string& name);
    
    // 查找导出项
    bool hasExport(const std::string& type, const std::string& name) const;
    
    // 检查是否允许导出
    bool isExported(const std::string& type, const std::string& category, const std::string& name) const;
    
    // 生成导出表字符串
    std::string toString() const;
    
    // 从字符串解析导出表
    static CMODExportTable parse(const std::string& exportBlock);
    
    // 设置为显式导出模式
    void setExplicitMode(bool explicit_mode) { isExplicit = explicit_mode; }
};

// 模块结构
class CMODModule : public std::enable_shared_from_this<CMODModule> {
private:
    std::string name;
    std::filesystem::path rootPath;
    CMODInfo info;
    CMODExportTable exportTable;
    std::map<std::string, std::shared_ptr<CMODModule>> subModules;
    std::vector<std::filesystem::path> sourceFiles;
    bool isSubModule;
    std::weak_ptr<CMODModule> parent;
    
    // 所有定义的项（用于自动生成导出表）
    std::vector<CMODExportItem> allDefinitions;
    
    // 加载信息文件
    bool loadInfo(const std::filesystem::path& infoFile);
    
    // 从文本存档加载（备用方案）
    bool loadFromTextArchive(const std::filesystem::path& archiveFile);
    
    // 解析导出表
    void parseExportTable(const std::string& content);
    
    // 生成导出表
    void generateExportTable();
    
public:
    CMODModule(const std::string& name, const std::filesystem::path& path, bool isSub = false);
    
    // 加载模块
    bool load();
    bool loadFromDirectory(const std::filesystem::path& dir);
    bool loadFromCMODFile(const std::filesystem::path& cmodFile);
    
    // 信息和导出表
    bool loadInfo(const std::filesystem::path& infoFile);
    bool generateExportTable();
    void scanSourceFiles();
    
    // 加载导出表
    bool loadExportTable(const std::filesystem::path& infoFile);
    
    // 扫描定义
    void scanDefinitions();
    
    // 检查项是否可导出
    bool canExport(const std::string& type, const std::string& category, const std::string& name) const;
    
    // 子模块管理
    void addSubModule(std::shared_ptr<CMODModule> subModule);
    std::shared_ptr<CMODModule> getSubModule(const std::string& name) const;
    std::vector<std::string> getSubModuleNames() const;
    bool hasSubModule(const std::string& name) const;
    
    // 获取器
    const std::string& getName() const { return name; }
    const CMODInfo& getInfo() const { return info; }
    const CMODExportTable& getExportTable() const { return exportTable; }
    const std::filesystem::path& getRootPath() const { return rootPath; }
    const std::vector<std::filesystem::path>& getSourceFiles() const { return sourceFiles; }
    std::string getFullName() const;
    
    // 验证
    bool validate() const;
    bool checkDependencies() const;
    bool checkCHTLVersion(const std::string& currentVersion) const;
};

// CMOD管理器
class CMODManager {
private:
    std::unordered_map<std::string, std::shared_ptr<CMODModule>> loadedModules;
    std::vector<std::filesystem::path> modulePaths;
    std::shared_ptr<CHTLContext> context;
    std::shared_ptr<ImportManager> importManager;
    
    // 模块缓存
    std::unordered_map<std::string, std::filesystem::path> moduleCache;
    
public:
    CMODManager(std::shared_ptr<CHTLContext> ctx);
    
    // 设置导入管理器
    void setImportManager(std::shared_ptr<ImportManager> mgr) { importManager = mgr; }
    
    // 路径管理
    void addModulePath(const std::filesystem::path& path);
    void addDefaultModulePaths();
    
    // 模块加载
    std::shared_ptr<CMODModule> loadModule(const std::string& moduleName);
    std::shared_ptr<CMODModule> loadModuleFromPath(const std::filesystem::path& path);
    
    // 模块查找
    std::filesystem::path findModule(const std::string& moduleName);
    std::filesystem::path findInDirectory(const std::filesystem::path& dir, const std::string& moduleName);
    
    // 子模块访问
    std::shared_ptr<CMODModule> getModule(const std::string& fullModuleName);
    
    // 缓存管理
    void clearCache();
    void buildCache();
    
    // 验证
    bool validateModule(const CMODModule& module) const;
    
    // 清理
    void clear();
};

// CMOD打包器
class CMODPacker {
private:
    std::filesystem::path sourcePath;
    std::filesystem::path outputPath;
    CMODInfo moduleInfo;
    std::shared_ptr<CHTLContext> context;
    
public:
    CMODPacker(std::shared_ptr<CHTLContext> ctx);
    
    // 设置路径
    void setSourcePath(const std::filesystem::path& path) { sourcePath = path; }
    void setOutputPath(const std::filesystem::path& path) { outputPath = path; }
    
    // 打包
    bool pack(const std::string& moduleName);
    bool packDirectory(const std::filesystem::path& dir, const std::string& outputFile);
    
    // 验证模块结构
    bool validateStructure(const std::filesystem::path& moduleDir) const;
    bool hasValidSrcFolder(const std::filesystem::path& moduleDir) const;
    bool hasValidInfoFolder(const std::filesystem::path& moduleDir) const;
    
    // 生成导出表
    bool generateExportTable(const std::filesystem::path& moduleDir, CMODExportTable& exportTable);
    
    // 压缩和归档
    bool createArchive(const std::filesystem::path& moduleDir, const std::filesystem::path& outputFile);
    
private:
    // 扫描源文件
    void scanSourceFiles(const std::filesystem::path& srcDir, std::vector<std::string>& files);
    
    // 解析CHTL文件提取导出
    void extractExports(const std::filesystem::path& chtlFile, CMODExportTable& exportTable);
};

// CMOD解包器
class CMODUnpacker {
private:
    std::shared_ptr<CHTLContext> context;
    
public:
    CMODUnpacker(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}
    
    // 解包
    bool unpack(const std::filesystem::path& cmodFile, const std::filesystem::path& outputDir);
    
    // 验证CMOD文件
    bool validateCMODFile(const std::filesystem::path& cmodFile) const;
    
    // 提取信息
    bool extractInfo(const std::filesystem::path& cmodFile, CMODInfo& info);
};

// CMOD工具函数
namespace CMODHelper {
    // 版本比较
    bool isVersionCompatible(const std::string& required, const std::string& current);
    int compareVersions(const std::string& v1, const std::string& v2);
    
    // 路径处理
    std::string moduleNameToPath(const std::string& moduleName);
    std::string pathToModuleName(const std::filesystem::path& path);
    
    // 验证模块名
    bool isValidModuleName(const std::string& name);
    
    // 文件类型检查
    bool isCMODFile(const std::filesystem::path& path);
    bool isCHTLFile(const std::filesystem::path& path);
    
    // 标准路径
    std::filesystem::path getOfficialModulePath();
    std::filesystem::path getLocalModulePath();
    
    // 生成模块模板
    bool createModuleTemplate(const std::filesystem::path& path, const std::string& moduleName);
}

// CMOD处理器 - 与ImportManager集成
class CMODProcessor {
private:
    CMODManager& manager;
    CHTLGenerator& generator;
    
    // 过滤导出内容
    std::string filterExportedContent(std::shared_ptr<CMODModule> module, 
                                    const std::string& content);
    
public:
    CMODProcessor(CMODManager& mgr, CHTLGenerator& gen)
        : manager(mgr), generator(gen) {}
    
    // 处理CMOD导入
    bool processCMODImport(const std::string& moduleName);
    
    // 处理子模块导入
    bool processSubModuleImport(const std::string& fullModuleName);
    
    // 导入模块内容
    bool importModuleContent(std::shared_ptr<CMODModule> module);
    
    // 处理依赖
    bool processDependencies(const CMODModule& module);
};

} // namespace chtl

#endif // CHTL_CMOD_H