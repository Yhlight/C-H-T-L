#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace chtl::v2 {

/**
 * 导入类型
 */
enum class ImportType {
    HTML,        // @Html - HTML 片段
    STYLE,       // @Style - CSS 文件
    JAVASCRIPT,  // @JavaScript - JS 文件
    CHTL,        // @Chtl - CHTL 文件
    CJMOD,       // @CJMOD - CHTL-JS 模块
    ELEMENT      // @Element - CMOD 组件
};

/**
 * 导入项
 */
struct ImportItem {
    ImportType type;
    std::string path;           // 导入路径
    std::string resolvedPath;   // 解析后的完整路径
    std::string alias;          // 别名（如果有）
    bool isOfficial = false;    // 是否是官方模块（CHTL:: 前缀）
    
    // 元数据
    std::map<std::string, std::string> metadata;
};

/**
 * 导入解析结果
 */
struct ImportResolveResult {
    bool success = false;
    std::string resolvedPath;
    std::string content;
    std::string error;
};

/**
 * 导入系统
 * 负责解析和加载各种类型的导入
 */
class ImportSystem {
public:
    ImportSystem();
    ~ImportSystem();
    
    /**
     * 添加搜索路径
     */
    void addSearchPath(const std::string& path);
    
    /**
     * 设置项目根目录
     */
    void setProjectRoot(const std::string& root);
    
    /**
     * 解析导入路径
     * 根据导入类型和规则解析路径
     */
    ImportResolveResult resolve(const ImportItem& item);
    
    /**
     * 加载导入内容
     */
    std::string loadContent(const std::string& path);
    
    /**
     * 检查是否是官方模块
     */
    static bool isOfficialModule(const std::string& path);
    
    /**
     * 获取官方模块路径
     */
    std::string getOfficialModulePath(const std::string& moduleName);
    
private:
    /**
     * 解析 @Html 导入
     */
    ImportResolveResult resolveHtml(const ImportItem& item);
    
    /**
     * 解析 @Style 导入
     */
    ImportResolveResult resolveStyle(const ImportItem& item);
    
    /**
     * 解析 @JavaScript 导入
     */
    ImportResolveResult resolveJavaScript(const ImportItem& item);
    
    /**
     * 解析 @Chtl 导入
     */
    ImportResolveResult resolveChtl(const ImportItem& item);
    
    /**
     * 解析 @CJMOD 导入
     */
    ImportResolveResult resolveCJMOD(const ImportItem& item);
    
    /**
     * 解析 @Element 导入（CMOD）
     */
    ImportResolveResult resolveElement(const ImportItem& item);
    
    /**
     * 尝试不同的文件扩展名
     */
    std::string tryExtensions(const std::string& basePath, 
                             const std::vector<std::string>& extensions);
    
    /**
     * 规范化路径
     */
    std::string normalizePath(const std::string& path);
    
private:
    std::string projectRoot_;
    std::vector<std::string> searchPaths_;
    std::string officialModulesPath_;
};

/**
 * 导入处理器
 * 处理导入声明并集成到编译流程
 */
class ImportProcessor {
public:
    ImportProcessor(ImportSystem* importSystem);
    
    /**
     * 处理导入声明
     */
    void processImport(const ImportItem& item);
    
    /**
     * 获取所有已处理的导入
     */
    const std::vector<ImportItem>& getProcessedImports() const {
        return processedImports_;
    }
    
    /**
     * 获取导入的内容
     */
    std::string getImportedContent(ImportType type) const;
    
    /**
     * 获取错误信息
     */
    const std::vector<std::string>& getErrors() const {
        return errors_;
    }
    
private:
    ImportSystem* importSystem_;
    std::vector<ImportItem> processedImports_;
    std::map<ImportType, std::vector<std::string>> importedContent_;
    std::vector<std::string> errors_;
};

} // namespace chtl::v2