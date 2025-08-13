#include "CHTLImport.h"
#include "CHTLGenerator.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"
#include "CHTLOrigin.h"
#include "CHTLCMOD.h"
#include "scanner/ScannerParserIntegration.h"
#include "CHTLImportVisitor.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include "CHTLCJMOD.h"

namespace chtl {

// ImportManager 实现
ImportManager::ImportManager(std::shared_ptr<CHTLContext> ctx) : context(ctx) {
    // 默认路径配置
    pathConfig.currentDirectory = std::filesystem::current_path();
    pathConfig.moduleDirectory = pathConfig.currentDirectory / "src" / "module";
    pathConfig.searchOfficialFirst = true;
}

void ImportManager::configurePaths(const ImportPathConfig& config) {
    pathConfig = config;
}

bool ImportManager::processImport(const ImportDeclaration& decl, CHTLGenerator& generator) {
    // 规范化路径
    std::string normalizedPath = normalizePath(decl.sourcePath);
    
    // 检查循环依赖
    if (!checkCircularDependency(normalizedPath)) {
        context->reportError("Circular dependency detected: " + normalizedPath);
        return false;
    }
    
    // 标记正在导入
    currentlyImporting.insert(normalizedPath);
    
    // 查找文件
    FileSearcher searcher(pathConfig);
    std::filesystem::path filePath = searcher.searchFile(decl.sourcePath, decl.type);
    
    if (filePath.empty()) {
        currentlyImporting.erase(normalizedPath);
        context->reportError("Import file not found: " + decl.sourcePath);
        return false;
    }
    
    // 检查是否已导入
    std::string absolutePath = std::filesystem::absolute(filePath).string();
    if (importedFiles.find(absolutePath) != importedFiles.end()) {
        currentlyImporting.erase(normalizedPath);
        return true; // 已导入，跳过
    }
    
    // 读取文件内容
    std::string content = readFileContent(filePath);
    if (content.empty() && !std::filesystem::is_empty(filePath)) {
        currentlyImporting.erase(normalizedPath);
        context->reportError("Failed to read import file: " + filePath.string());
        return false;
    }
    
    // 创建导入文件信息
    auto importedFile = std::make_shared<ImportedFile>();
    importedFile->absolutePath = std::filesystem::absolute(filePath);
    importedFile->relativePath = filePath;
    importedFile->type = decl.type;
    importedFile->content = content;
    importedFile->asName = decl.asName;
    importedFile->isProcessed = false;
    
    // 记录导入的文件
    importedFiles[absolutePath] = importedFile;
    
    // 处理导入内容
    ImportProcessor processor(*this, generator);
    bool success = false;
    
    switch (decl.type) {
        case ImportType::HTML:
            success = processor.processHtmlImport(decl);
            break;
        case ImportType::STYLE:
            success = processor.processStyleImport(decl);
            break;
        case ImportType::JAVASCRIPT:
            success = processor.processJavaScriptImport(decl);
            break;
        case ImportType::CHTL:
            success = processor.processChtlImport(decl.sourcePath);
            break;
        case ImportType::CJMOD:
            success = processor.processCjmodImport(decl.sourcePath);
            break;
        case ImportType::CUSTOM_ELEMENT:
        case ImportType::CUSTOM_STYLE:
        case ImportType::CUSTOM_VAR:
            success = processor.processCustomImport(decl);
            break;
        case ImportType::TEMPLATE_ELEMENT:
        case ImportType::TEMPLATE_STYLE:
        case ImportType::TEMPLATE_VAR:
            success = processor.processTemplateImport(decl);
            break;
    }
    
    importedFile->isProcessed = success;
    currentlyImporting.erase(normalizedPath);
    
    return success;
}

bool ImportManager::processImports(const std::vector<ImportDeclaration>& declarations, CHTLGenerator& generator) {
    bool allSuccess = true;
    
    for (const auto& decl : declarations) {
        if (!processImport(decl, generator)) {
            allSuccess = false;
        }
    }
    
    return allSuccess;
}

std::string ImportManager::readFileContent(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool ImportManager::checkCircularDependency(const std::string& path) {
    return currentlyImporting.find(path) == currentlyImporting.end();
}

std::string ImportManager::normalizePath(const std::string& path) {
    // 检查缓存
    auto it = normalizedPaths.find(path);
    if (it != normalizedPaths.end()) {
        return it->second;
    }
    
    // 规范化路径
    std::string normalized = PathProcessor::normalize(path);
    normalizedPaths[path] = normalized;
    
    return normalized;
}

std::shared_ptr<ImportedFile> ImportManager::getImportedFile(const std::string& path) const {
    auto it = importedFiles.find(path);
    if (it != importedFiles.end()) {
        return it->second;
    }
    return nullptr;
}

void ImportManager::clear() {
    importedFiles.clear();
    importedItems.clear();
    currentlyImporting.clear();
    normalizedPaths.clear();
}

// ImportProcessor 实现
ImportDeclaration ImportProcessor::parseImportStatement(const std::string& statement) {
    ImportDeclaration decl;
    decl.hasAsClause = false;
    decl.isWildcard = false;
    
    // 正则表达式匹配各种导入格式
    // [Import] @Type from path
    // [Import] @Type from path as name
    // [Import] [Modifier] @Type name from path
    // [Import] [Modifier] @Type name from path as alias
    
    std::regex simpleImport(R"(\[Import\]\s+(@\w+)\s+from\s+([^\s]+)(?:\s+as\s+(\w+))?)");
    std::regex modifiedImport(R"(\[Import\]\s+\[(Custom|Template)\]\s+(@\w+)\s+(\w+)\s+from\s+([^\s]+)(?:\s+as\s+(\w+))?)");
    
    std::smatch match;
    
    if (std::regex_match(statement, match, modifiedImport)) {
        // 带修饰符的导入
        std::string modifier = match[1];
        std::string type = match[2];
        decl.itemName = match[3];
        decl.sourcePath = match[4];
        if (match[5].matched) {
            decl.asName = match[5];
            decl.hasAsClause = true;
        }
        
        // 确定导入类型
        if (modifier == "Custom") {
            if (type == "@Element") decl.type = ImportType::CUSTOM_ELEMENT;
            else if (type == "@Style") decl.type = ImportType::CUSTOM_STYLE;
            else if (type == "@Var") decl.type = ImportType::CUSTOM_VAR;
        } else if (modifier == "Template") {
            if (type == "@Element") decl.type = ImportType::TEMPLATE_ELEMENT;
            else if (type == "@Style") decl.type = ImportType::TEMPLATE_STYLE;
            else if (type == "@Var") decl.type = ImportType::TEMPLATE_VAR;
        }
    } else if (std::regex_match(statement, match, simpleImport)) {
        // 简单导入
        std::string type = match[1];
        decl.sourcePath = match[2];
        if (match[3].matched) {
            decl.asName = match[3];
            decl.hasAsClause = true;
        }
        
        decl.type = ImportHelper::parseImportType(type);
    }
    
    // 检查通配符
    if (decl.sourcePath.find('*') != std::string::npos) {
        decl.isWildcard = true;
        decl.wildcardPattern = decl.sourcePath.substr(decl.sourcePath.find_last_of("/\\") + 1);
    }
    
    return decl;
}

std::string ImportProcessor::searchChtlFile(const std::string& path) {
    FileSearcher searcher;
    
    // 如果是具体文件路径
    if (path.find('/') != std::string::npos || path.find('\\') != std::string::npos) {
        std::filesystem::path filePath(path);
        if (std::filesystem::exists(filePath)) {
            return filePath.string();
        }
        return "";
    }
    
    // 搜索文件
    std::vector<std::string> extensions = {".chtl", ".cmod"};
    for (const auto& ext : extensions) {
        std::string found = searcher.searchFile(path + ext, ImportType::CHTL);
        if (!found.empty()) {
            return found;
        }
    }
    
    // 尝试不带扩展名
    return searcher.searchFile(path, ImportType::CHTL);
}

bool ImportProcessor::processHtmlImport(const ImportDeclaration& decl) {
    if (!decl.hasAsClause) {
        // 没有as子句，直接跳过
        return true;
    }
    
    // 读取HTML内容
    auto importedFile = manager.getImportedFile(decl.sourcePath);
    if (!importedFile) {
        return false;
    }
    
    // 创建命名的原始嵌入
    auto origin = std::make_shared<OriginDefinition>(decl.asName, "@Html", true);
    origin->setContent(importedFile->content);
    
    if (manager.originManager) {
        manager.originManager->registerNamedOrigin(decl.asName, origin);
    }
    
    return true;
}

bool ImportProcessor::processStyleImport(const ImportDeclaration& decl) {
    if (!decl.hasAsClause) {
        // 没有as子句，直接跳过
        return true;
    }
    
    auto importedFile = manager.getImportedFile(decl.sourcePath);
    if (!importedFile) {
        return false;
    }
    
    // 创建命名的原始嵌入
    auto origin = std::make_shared<OriginDefinition>(decl.asName, "@Style", true);
    origin->setContent(importedFile->content);
    
    if (manager.originManager) {
        manager.originManager->registerNamedOrigin(decl.asName, origin);
    }
    
    return true;
}

bool ImportProcessor::processJavaScriptImport(const ImportDeclaration& decl) {
    if (!decl.hasAsClause) {
        // 没有as子句，直接跳过
        return true;
    }
    
    auto importedFile = manager.getImportedFile(decl.sourcePath);
    if (!importedFile) {
        return false;
    }
    
    // 创建命名的原始嵌入
    auto origin = std::make_shared<OriginDefinition>(decl.asName, "@JavaScript", true);
    origin->setContent(importedFile->content);
    
    if (manager.originManager) {
        manager.originManager->registerNamedOrigin(decl.asName, origin);
    }
    
    return true;
}

bool ImportProcessor::processChtlImport(const std::string& path) {
    // 处理模块导入（不含路径分隔符的情况）
    if (path.find('/') == std::string::npos && path.find('\\') == std::string::npos && !path.ends_with(".chtl")) {
        // 这是一个模块引用，如 Chtholly
        if (manager.cmodManager) {
            // 在module目录中查找模块
            std::filesystem::path moduleBase = manager.pathConfig.moduleDirectory / path;
            
            // 检查是否是混合模块结构
            std::filesystem::path cmodPath = moduleBase / "CMOD" / path;
            if (std::filesystem::exists(cmodPath) && std::filesystem::is_directory(cmodPath)) {
                // 混合模块，加载CMOD部分
                CMODProcessor cmodProcessor(*manager.cmodManager, generator);
                return cmodProcessor.processCMODImport(cmodPath.string());
            }
            
            // 检查是否是直接的CMOD模块
            if (std::filesystem::exists(moduleBase / "src") && std::filesystem::exists(moduleBase / "info")) {
                CMODProcessor cmodProcessor(*manager.cmodManager, generator);
                return cmodProcessor.processCMODImport(moduleBase.string());
            }
            
            // 尝试查找已打包的.cmod文件
            std::filesystem::path cmodFile = manager.pathConfig.moduleDirectory / (path + ".cmod");
            if (std::filesystem::exists(cmodFile)) {
                CMODProcessor cmodProcessor(*manager.cmodManager, generator);
                return cmodProcessor.processCMODImport(cmodFile.string());
            }
        }
    }
    
    // 处理子模块导入（使用点号分隔）
    if (path.find('.') != std::string::npos && !path.ends_with(".chtl")) {
        // 将点号转换为路径分隔符
        std::string modulePath = path;
        std::replace(modulePath.begin(), modulePath.end(), '.', '/');
        
        if (manager.cmodManager) {
            std::filesystem::path moduleBase = manager.pathConfig.moduleDirectory / modulePath;
            
            // 检查子模块路径
            if (std::filesystem::exists(moduleBase / "src") && std::filesystem::exists(moduleBase / "info")) {
                CMODProcessor cmodProcessor(*manager.cmodManager, generator);
                return cmodProcessor.processCMODImport(moduleBase.string());
            }
        }
    }
    
    // 查找CHTL文件
    std::string filePath = searchChtlFile(path);
    if (filePath.empty()) {
        manager.context->reportError("CHTL file not found: " + path);
        return false;
    }
    
    // 读取文件内容
    std::string content = manager.readFileContent(filePath);
    if (content.empty()) {
        return false;
    }
    
    // 使用扫描器处理CHTL文件
    auto scanner = std::make_shared<ScannerParserIntegration>();
    CHTLImportVisitor visitor(manager);
    
    try {
        scanner->parseFile(filePath, content);
        scanner->accept(&visitor);
        
        // 将解析的内容添加到生成器
        if (visitor.hasContent()) {
            generator.addImportedContent(visitor.getGeneratedContent());
        }
        
        // 处理嵌套的导入
        for (const auto& nestedImport : visitor.getImports()) {
            ImportDeclaration nestedDecl = ImportHelper::parseImportStatement(nestedImport);
            if (!manager.processImport(nestedDecl, generator)) {
                return false;
            }
        }
    } catch (const std::exception& e) {
        manager.context->reportError("Failed to parse imported CHTL file: " + std::string(e.what()));
        return false;
    }
    
    return true;
}

bool ImportProcessor::processCjmodImport(const std::string& path) {
    // 处理CJMOD模块导入
    if (path.find('/') == std::string::npos && path.find('\\') == std::string::npos && !path.ends_with(".cjmod")) {
        // 这是一个模块引用，如 Chtholly
        if (manager.cjmodManager) {
            // 在module目录中查找模块
            std::filesystem::path moduleBase = manager.pathConfig.moduleDirectory / path;
            
            // 检查是否是混合模块结构
            std::filesystem::path cjmodPath = moduleBase / "CJMOD" / path;
            if (std::filesystem::exists(cjmodPath) && std::filesystem::is_directory(cjmodPath)) {
                // 混合模块，加载CJMOD部分
                // 使用CJMOD管理器直接加载模块
                auto module = std::make_shared<CJMODModule>(path, cjmodPath);
                if (manager.cjmodManager->loadModule(module)) {
                    manager.cjmodManager->registerModule(path, module);
                    return true;
                }
                return false;
            }
            
            // 检查是否是直接的CJMOD模块（包含C++源文件）
            if (std::filesystem::exists(moduleBase / "src")) {
                bool hasCppFiles = false;
                for (const auto& entry : std::filesystem::directory_iterator(moduleBase / "src")) {
                    if (entry.path().extension() == ".cpp" || 
                        entry.path().extension() == ".cc" ||
                        entry.path().extension() == ".cxx") {
                        hasCppFiles = true;
                        break;
                    }
                }
                
                if (hasCppFiles && std::filesystem::exists(moduleBase / "info")) {
                    auto module = std::make_shared<CJMODModule>(path, moduleBase);
                    if (manager.cjmodManager->loadModule(module)) {
                        manager.cjmodManager->registerModule(path, module);
                        return true;
                    }
                    return false;
                }
            }
            
            // 尝试查找已打包的.cjmod文件
            std::filesystem::path cjmodFile = manager.pathConfig.moduleDirectory / (path + ".cjmod");
            if (std::filesystem::exists(cjmodFile)) {
                auto module = std::make_shared<CJMODModule>(path, cjmodFile);
                if (module->loadFromCJMODFile(cjmodFile, manager.pathConfig.moduleDirectory / "cjmod_extracted" / path)) {
                    manager.cjmodManager->registerModule(path, module);
                    return true;
                }
                return false;
            }
        }
    }
    
    // 处理子模块导入（使用点号分隔）
    if (path.find('.') != std::string::npos && !path.ends_with(".cjmod")) {
        // 将点号转换为路径分隔符
        std::string modulePath = path;
        std::replace(modulePath.begin(), modulePath.end(), '.', '/');
        
        if (manager.cjmodManager) {
            std::filesystem::path moduleBase = manager.pathConfig.moduleDirectory / modulePath;
            
            // 检查子模块路径（CJMOD）
            bool hasCppFiles = false;
            if (std::filesystem::exists(moduleBase / "src")) {
                for (const auto& entry : std::filesystem::directory_iterator(moduleBase / "src")) {
                    if (entry.path().extension() == ".cpp" || 
                        entry.path().extension() == ".cc" ||
                        entry.path().extension() == ".cxx") {
                        hasCppFiles = true;
                        break;
                    }
                }
            }
            
            if (hasCppFiles && std::filesystem::exists(moduleBase / "info")) {
                // 使用原始路径作为模块名（保留点号）
                auto module = std::make_shared<CJMODModule>(path, moduleBase);
                if (manager.cjmodManager->loadModule(module)) {
                    manager.cjmodManager->registerModule(path, module);
                    return true;
                }
                return false;
            }
        }
    }
    
    // 处理直接的.cjmod文件路径
    if (path.ends_with(".cjmod")) {
        if (manager.cjmodManager) {
            std::string moduleName = std::filesystem::path(path).stem().string();
            auto module = std::make_shared<CJMODModule>(moduleName, path);
            if (module->loadFromCJMODFile(path, manager.pathConfig.moduleDirectory / "cjmod_extracted" / moduleName)) {
                manager.cjmodManager->registerModule(moduleName, module);
                return true;
            }
            return false;
        }
    }
    
    manager.context->reportError("CJMOD module not found: " + path);
    return false;
}

bool ImportProcessor::processCustomImport(const ImportDeclaration& decl) {
    // 从CHTL文件中提取特定的自定义项
    return extractFromChtlFile(decl.sourcePath, decl.itemName, decl.type);
}

bool ImportProcessor::processTemplateImport(const ImportDeclaration& decl) {
    // 从CHTL文件中提取特定的模板
    return extractFromChtlFile(decl.sourcePath, decl.itemName, decl.type);
}

bool ImportProcessor::extractFromChtlFile(const std::string& filePath, 
                                        const std::string& itemName,
                                        ImportType itemType) {
    // 读取文件内容
    std::string content = readFileContent(filePath);
    if (content.empty()) {
        return false;
    }
    
    // 使用Scanner-Parser集成解析CHTL文件
    scanner::ScannerParserIntegration integration(context);
    auto parseResult = integration.parse(content);
    
    if (!parseResult.success) {
        std::cerr << "Failed to parse CHTL file: " << filePath << std::endl;
        std::cerr << parseResult.errorMessage << std::endl;
        return false;
    }
    
    // 创建选择性访问器
    CHTLSelectiveImportVisitor visitor(context, itemName, itemType);
    
    if (parseResult.chtlTree) {
        visitor.visit(parseResult.chtlTree);
        
        if (visitor.hasFoundItem()) {
            // 根据类型注册找到的项目
            switch (itemType) {
                case ImportType::CustomElement:
                case ImportType::CustomStyle:
                case ImportType::CustomVar:
                    if (auto custom = visitor.getFoundCustom()) {
                        context->getCustomManager().registerCustom(itemName, custom);
                        return true;
                    }
                    break;
                    
                case ImportType::TemplateElement:
                case ImportType::TemplateStyle:
                case ImportType::TemplateVar:
                    if (auto tmpl = visitor.getFoundTemplate()) {
                        context->getTemplateManager().registerTemplate(itemName, tmpl);
                        return true;
                    }
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    return false;
}

// FileSearcher 实现
std::filesystem::path FileSearcher::searchFile(const std::string& name, ImportType type) {
    // 解析路径
    auto components = PathProcessor::parsePath(name);
    
    // 如果是绝对路径
    if (components.isAbsolute) {
        std::filesystem::path path(name);
        if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
            return path;
        }
        return "";
    }
    
    // 获取可能的扩展名
    auto extensions = getExtensionsForType(type);
    
    // 搜索顺序
    std::vector<std::filesystem::path> searchDirs;
    
    if (type == ImportType::CHTL || type == ImportType::CJMOD) {
        // 模块搜索顺序
        if (config.searchOfficialFirst && !config.officialModulePath.empty()) {
            searchDirs.push_back(config.officialModulePath);
        }
        searchDirs.push_back(config.moduleDirectory);
        searchDirs.push_back(config.currentDirectory);
    } else {
        // 其他文件只在当前目录搜索
        searchDirs.push_back(config.currentDirectory);
    }
    
    // 在每个目录中搜索
    for (const auto& dir : searchDirs) {
        auto found = searchInDirectory(dir, name, extensions);
        if (!found.empty()) {
            return found;
        }
    }
    
    return "";
}

std::filesystem::path FileSearcher::searchInDirectory(const std::filesystem::path& dir,
                                                    const std::string& name,
                                                    const std::vector<std::string>& extensions) {
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        return "";
    }
    
    // 处理路径
    std::string searchName = PathProcessor::dotToSlash(name);
    
    // 如果已经有扩展名
    auto components = PathProcessor::parsePath(searchName);
    if (components.hasExtension) {
        std::filesystem::path fullPath = dir / searchName;
        if (std::filesystem::exists(fullPath) && std::filesystem::is_regular_file(fullPath)) {
            return fullPath;
        }
        return "";
    }
    
    // 尝试各种扩展名
    for (const auto& ext : extensions) {
        std::filesystem::path fullPath = dir / (searchName + ext);
        if (std::filesystem::exists(fullPath) && std::filesystem::is_regular_file(fullPath)) {
            return fullPath;
        }
    }
    
    return "";
}

std::vector<std::string> FileSearcher::getExtensionsForType(ImportType type) {
    switch (type) {
        case ImportType::HTML:
            return {".html", ".htm"};
        case ImportType::STYLE:
            return {".css"};
        case ImportType::JAVASCRIPT:
            return {".js", ".mjs"};
        case ImportType::CHTL:
            return {".cmod", ".chtl"};  // cmod优先
        case ImportType::CJMOD:
            return {".cjmod"};
        default:
            return {".chtl"};  // 自定义和模板从chtl文件中提取
    }
}

// PathProcessor 实现
std::string PathProcessor::dotToSlash(const std::string& path) {
    std::string result = path;
    std::replace(result.begin(), result.end(), '.', '/');
    return result;
}

std::string PathProcessor::normalize(const std::string& path) {
    // 转换点号为斜杠
    std::string normalized = dotToSlash(path);
    
    // 规范化路径分隔符
    std::replace(normalized.begin(), normalized.end(), '\\', '/');
    
    // 处理相对路径
    std::filesystem::path p(normalized);
    return p.lexically_normal().string();
}

PathProcessor::PathComponents PathProcessor::parsePath(const std::string& path) {
    PathComponents components;
    
    std::filesystem::path p(path);
    
    components.directory = p.parent_path().string();
    components.filename = p.stem().string();
    components.extension = p.extension().string();
    components.hasExtension = !components.extension.empty();
    components.isAbsolute = p.is_absolute();
    components.isWildcard = path.find('*') != std::string::npos;
    
    return components;
}

// CircularDependencyDetector 实现
void CircularDependencyDetector::addDependency(const std::string& from, const std::string& to) {
    dependencyGraph[from].push_back(to);
}

bool CircularDependencyDetector::hasCircularDependency() {
    visited.clear();
    recursionStack.clear();
    
    for (const auto& [node, _] : dependencyGraph) {
        if (visited.find(node) == visited.end()) {
            std::vector<std::string> path;
            if (hasCycleUtil(node, path)) {
                return true;
            }
        }
    }
    
    return false;
}

bool CircularDependencyDetector::hasCycleUtil(const std::string& node, std::vector<std::string>& path) {
    visited.insert(node);
    recursionStack.insert(node);
    path.push_back(node);
    
    auto it = dependencyGraph.find(node);
    if (it != dependencyGraph.end()) {
        for (const auto& neighbor : it->second) {
            if (recursionStack.find(neighbor) != recursionStack.end()) {
                path.push_back(neighbor);
                return true;
            }
            
            if (visited.find(neighbor) == visited.end() && hasCycleUtil(neighbor, path)) {
                return true;
            }
        }
    }
    
    path.pop_back();
    recursionStack.erase(node);
    return false;
}

// ImportHelper 实现
namespace ImportHelper {

ImportType parseImportType(const std::string& typeStr) {
    if (typeStr == "@Html") return ImportType::HTML;
    if (typeStr == "@Style") return ImportType::STYLE;
    if (typeStr == "@JavaScript") return ImportType::JAVASCRIPT;
    if (typeStr == "@Chtl") return ImportType::CHTL;
    if (typeStr == "@CJmod") return ImportType::CJMOD;
    
    throw std::invalid_argument("Unknown import type: " + typeStr);
}

bool shouldCreateOriginNode(ImportType type, bool hasAsClause) {
    // 对于@Html, @Style, @JavaScript，只有在有as子句时才创建原始嵌入
    return (type == ImportType::HTML || type == ImportType::STYLE || type == ImportType::JAVASCRIPT) 
           && hasAsClause;
}

std::string getDefaultExtension(ImportType type) {
    switch (type) {
        case ImportType::HTML: return ".html";
        case ImportType::STYLE: return ".css";
        case ImportType::JAVASCRIPT: return ".js";
        case ImportType::CHTL: return ".chtl";
        case ImportType::CJMOD: return ".cjmod";
        default: return "";
    }
}

} // namespace ImportHelper

} // namespace chtl