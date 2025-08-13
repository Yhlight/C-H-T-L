#include "CHTLCMOD.h"
#include "CHTLGenerator.h"
#include "CHTLImport.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <chrono>

namespace chtl {

namespace fs = std::filesystem;

// CMODInfo 实现
bool CMODInfo::isValid() const {
    return !name.empty() && !version.empty() && !author.empty();
}

std::string CMODInfo::toString() const {
    std::stringstream ss;
    ss << "[Info]\n{\n";
    ss << "    name = \"" << name << "\";\n";
    ss << "    version = \"" << version << "\";\n";
    ss << "    description = \"" << description << "\";\n";
    ss << "    author = \"" << author << "\";\n";
    ss << "    license = \"" << license << "\";\n";
    ss << "    dependencies = \"" << dependencies << "\";\n";
    ss << "    category = \"" << category << "\";\n";
    ss << "    minCHTLVersion = \"" << minCHTLVersion << "\";\n";
    ss << "    maxCHTLVersion = \"" << maxCHTLVersion << "\";\n";
    ss << "}\n";
    return ss.str();
}

// CMODExportTable 实现
void CMODExportTable::addExport(const std::string& type, const std::string& category, const std::string& name) {
    CMODExportItem item{type, category, name};
    
    if (type == "@Style") {
        styles.push_back(item);
    } else if (type == "@Element") {
        elements.push_back(item);
    } else if (type == "@Var") {
        variables.push_back(item);
    }
}

bool CMODExportTable::hasExport(const std::string& type, const std::string& name) const {
    const auto& items = (type == "@Style") ? styles : 
                       (type == "@Element") ? elements : variables;
    
    return std::any_of(items.begin(), items.end(),
        [&name](const CMODExportItem& item) { return item.name == name; });
}

bool CMODExportTable::isExported(const std::string& type, const std::string& category, const std::string& name) const {
    // 如果不是显式模式，默认全部导出
    if (!isExplicit) {
        return true;
    }
    
    // 在显式模式下，只导出明确列出的项
    const auto& items = (type == "@Style") ? styles : 
                       (type == "@Element") ? elements : variables;
    
    return std::any_of(items.begin(), items.end(),
        [&](const CMODExportItem& item) { 
            return item.name == name && 
                   (category.empty() || item.category == category);
        });
}

CMODExportTable CMODExportTable::parse(const std::string& exportBlock) {
    CMODExportTable table;
    
    // 检查是否有[Export]块
    std::regex exportRegex(R"(\[Export\]\s*\{([^}]*)\})");
    std::smatch exportMatch;
    
    if (!std::regex_search(exportBlock, exportMatch, exportRegex)) {
        // 没有显式导出表，使用默认（导出所有）
        table.isExplicit = false;
        return table;
    }
    
    table.isExplicit = true;
    std::string content = exportMatch[1];
    
    // 解析@Style导出
    std::regex styleRegex(R"(@Style\s+([^;]+);)");
    std::smatch styleMatch;
    if (std::regex_search(content, styleMatch, styleRegex)) {
        std::string styleList = styleMatch[1];
        std::regex itemRegex(R"((\w+))");
        std::sregex_iterator it(styleList.begin(), styleList.end(), itemRegex);
        std::sregex_iterator end;
        
        while (it != end) {
            table.addExport("@Style", "", (*it)[1]);
            ++it;
        }
    }
    
    // 解析@Element导出
    std::regex elementRegex(R"(@Element\s+([^;]+);)");
    std::smatch elementMatch;
    if (std::regex_search(content, elementMatch, elementRegex)) {
        std::string elementList = elementMatch[1];
        std::regex itemRegex(R"((\w+))");
        std::sregex_iterator it(elementList.begin(), elementList.end(), itemRegex);
        std::sregex_iterator end;
        
        while (it != end) {
            table.addExport("@Element", "", (*it)[1]);
            ++it;
        }
    }
    
    // 解析@Var导出
    std::regex varRegex(R"(@Var\s+([^;]+);)");
    std::smatch varMatch;
    if (std::regex_search(content, varMatch, varRegex)) {
        std::string varList = varMatch[1];
        std::regex itemRegex(R"((\w+))");
        std::sregex_iterator it(varList.begin(), varList.end(), itemRegex);
        std::sregex_iterator end;
        
        while (it != end) {
            table.addExport("@Var", "", (*it)[1]);
            ++it;
        }
    }
    
    return table;
}

std::string CMODExportTable::toString() const {
    std::stringstream ss;
    ss << "[Export]\n{\n";
    
    // 导出样式
    if (!styles.empty()) {
        ss << "    @Style ";
        for (size_t i = 0; i < styles.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << styles[i].name;
        }
        ss << ";\n\n";
    }
    
    // 导出元素
    if (!elements.empty()) {
        ss << "    @Element ";
        for (size_t i = 0; i < elements.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << elements[i].name;
        }
        ss << ";\n\n";
    }
    
    // 导出变量
    if (!variables.empty()) {
        ss << "    @Var ";
        for (size_t i = 0; i < variables.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << variables[i].name;
        }
        ss << ";\n";
    }
    
    ss << "}\n";
    return ss.str();
}

// CMODModule 实现
CMODModule::CMODModule(const std::string& n, const fs::path& path, bool isSub)
    : name(n), rootPath(path), isSubModule(isSub) {}

bool CMODModule::load() {
    if (fs::exists(rootPath) && fs::is_directory(rootPath)) {
        return loadFromDirectory(rootPath);
    } else if (fs::exists(rootPath) && CMODHelper::isCMODFile(rootPath)) {
        return loadFromCMODFile(rootPath);
    }
    return false;
}

bool CMODModule::loadFromDirectory(const fs::path& dir) {
    // 验证目录结构
    fs::path srcDir = dir / "src";
    fs::path infoDir = dir / "info";
    
    if (!fs::exists(srcDir) || !fs::is_directory(srcDir)) {
        return false;
    }
    
    if (!fs::exists(infoDir) || !fs::is_directory(infoDir)) {
        return false;
    }
    
    // 加载模块信息
    fs::path infoFile = infoDir / (name + ".chtl");
    if (!loadInfo(infoFile)) {
        return false;
    }
    
    // 扫描源文件
    scanSourceFiles();
    
    // 查找子模块
    for (const auto& entry : fs::directory_iterator(srcDir)) {
        if (fs::is_directory(entry)) {
            std::string subModuleName = entry.path().filename().string();
            
            // 检查是否是有效的子模块
            fs::path subSrcDir = entry.path() / "src";
            fs::path subInfoDir = entry.path() / "info";
            
            if (fs::exists(subSrcDir) && fs::exists(subInfoDir)) {
                auto subModule = std::make_shared<CMODModule>(subModuleName, entry.path(), true);
                subModule->parent = std::weak_ptr<CMODModule>(shared_from_this());
                
                if (subModule->load()) {
                    addSubModule(subModule);
                }
            }
        }
    }
    
    // 生成导出表
    generateExportTable();
    
    return true;
}

bool CMODModule::loadFromCMODFile(const fs::path& file) {
    if (!fs::exists(file) || !CMODHelper::isCMODFile(file)) {
        return false;
    }
    
    // 创建临时目录
    std::string tempDirName = "cmod_temp_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    fs::path tempDir = fs::temp_directory_path() / tempDirName;
    fs::create_directories(tempDir);
    
    // 解压tar.gz文件
    std::string extractCmd = "tar -xzf \"" + file.string() + "\" -C \"" + tempDir.string() + "\"";
    int result = std::system(extractCmd.c_str());
    
    if (result != 0) {
        fs::remove_all(tempDir);
        return false;
    }
    
    // 查找模块目录（应该只有一个）
    fs::path moduleDir;
    for (const auto& entry : fs::directory_iterator(tempDir)) {
        if (entry.is_directory()) {
            moduleDir = entry.path();
            break;
        }
    }
    
    if (moduleDir.empty()) {
        fs::remove_all(tempDir);
        return false;
    }
    
    // 从解压的目录加载
    bool success = loadFromDirectory(moduleDir);
    
    // 清理临时目录
    fs::remove_all(tempDir);
    
    return success;
}

bool CMODModule::loadInfo(const fs::path& infoFile) {
    if (!fs::exists(infoFile)) {
        return false;
    }
    
    std::ifstream file(infoFile);
    if (!file.is_open()) {
        return false;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();
    
    // 解析[Info]块
    std::regex infoRegex(R"(\[Info\]\s*\{([^}]+)\})");
    std::smatch infoMatch;
    
    if (std::regex_search(content, infoMatch, infoRegex)) {
        std::string infoBlock = infoMatch[1];
        
        // 解析各个字段
        std::regex fieldRegex(R"((\w+)\s*=\s*"([^"]*)")");
        std::sregex_iterator it(infoBlock.begin(), infoBlock.end(), fieldRegex);
        std::sregex_iterator end;
        
        while (it != end) {
            std::string key = (*it)[1];
            std::string value = (*it)[2];
            
            if (key == "name") info.name = value;
            else if (key == "version") info.version = value;
            else if (key == "description") info.description = value;
            else if (key == "author") info.author = value;
            else if (key == "license") info.license = value;
            else if (key == "dependencies") info.dependencies = value;
            else if (key == "category") info.category = value;
            else if (key == "minCHTLVersion") info.minCHTLVersion = value;
            else if (key == "maxCHTLVersion") info.maxCHTLVersion = value;
            
            ++it;
        }
    }
    
    // 加载导出表
    exportTable = CMODExportTable::parse(content);
    
    return info.isValid();
}

bool CMODModule::loadFromTextArchive(const fs::path& archiveFile) {
    std::ifstream file(archiveFile);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    std::string currentFile;
    std::stringstream currentContent;
    bool inFileSection = false;
    
    while (std::getline(file, line)) {
        if (line.starts_with("=== FILE: ")) {
            // 保存前一个文件
            if (!currentFile.empty()) {
                sourceFiles[currentFile] = currentContent.str();
                currentContent.str("");
                currentContent.clear();
            }
            
            // 开始新文件
            currentFile = line.substr(10);  // 跳过 "=== FILE: "
            if (currentFile.ends_with(" ===")) {
                currentFile = currentFile.substr(0, currentFile.length() - 4);
            }
            inFileSection = true;
        } else if (line == "=== END ===" && inFileSection) {
            // 保存当前文件
            if (!currentFile.empty()) {
                sourceFiles[currentFile] = currentContent.str();
                currentContent.str("");
                currentContent.clear();
                currentFile.clear();
            }
            inFileSection = false;
        } else if (inFileSection) {
            currentContent << line << "\n";
        } else if (line.starts_with("Name: ")) {
            info.name = line.substr(6);
        } else if (line.starts_with("Version: ")) {
            info.version = line.substr(9);
        } else if (line.starts_with("Author: ")) {
            info.author = line.substr(8);
        } else if (line.starts_with("Description: ")) {
            info.description = line.substr(13);
        }
    }
    
    // 保存最后一个文件
    if (!currentFile.empty()) {
        sourceFiles[currentFile] = currentContent.str();
    }
    
    // 生成导出表
    generateExportTable();
    
    return !sourceFiles.empty();
}

void CMODModule::parseExportTable(const std::string& content) {
    std::istringstream stream(content);
    std::string line;
    
    exportTable.clear();
    
    while (std::getline(stream, line)) {
        // 跳过空行和注释
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // 解析格式: Type Name Path Exported
        std::istringstream lineStream(line);
        std::string type, name, path, exported;
        
        if (lineStream >> type >> name >> path >> exported) {
            CMODExportItem item;
            item.name = name;
            item.path = path;
            item.exported = (exported == "true");
            
            // 解析类型
            if (type == "Template.Style") {
                item.type = CMODExportType::TemplateStyle;
            } else if (type == "Template.Element") {
                item.type = CMODExportType::TemplateElement;
            } else if (type == "Template.Var") {
                item.type = CMODExportType::TemplateVar;
            } else if (type == "Custom.Style") {
                item.type = CMODExportType::CustomStyle;
            } else if (type == "Custom.Element") {
                item.type = CMODExportType::CustomElement;
            } else if (type == "Custom.Var") {
                item.type = CMODExportType::CustomVar;
            }
            
            exportTable[name] = item;
        }
    }
}

bool CMODModule::loadExportTable(const fs::path& infoFile) {
    // 如果infoFile是路径，读取内容
    std::string content;
    if (fs::is_regular_file(infoFile)) {
        std::ifstream file(infoFile);
        if (file.is_open()) {
            content = std::string((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
            file.close();
        }
    } else {
        // 假设infoFile实际上是内容字符串
        content = infoFile.string();
    }
    
    exportTable = CMODExportTable::parse(content);
    return true;
}

void CMODModule::scanSourceFiles() {
    fs::path srcDir = rootPath / "src";
    
    if (!fs::exists(srcDir)) {
        return;
    }
    
    for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
        if (fs::is_regular_file(entry) && CMODHelper::isCHTLFile(entry.path())) {
            // 跳过子模块的文件
            bool isSubModuleFile = false;
            for (const auto& [subName, subModule] : subModules) {
                if (entry.path().string().find(subModule->getRootPath().string()) != std::string::npos) {
                    isSubModuleFile = true;
                    break;
                }
            }
            
            if (!isSubModuleFile) {
                sourceFiles.push_back(entry.path());
            }
        }
    }
}

void CMODModule::scanDefinitions() {
    allDefinitions.clear();
    
    for (const auto& srcFile : sourceFiles) {
        std::ifstream file(srcFile);
        if (!file.is_open()) continue;
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        
        // 扫描[Template]定义
        std::regex templateRegex(R"(\[Template\]\s*@(Style|Element|Var)\s+(\w+))");
        std::sregex_iterator templateIt(content.begin(), content.end(), templateRegex);
        std::sregex_iterator end;
        
        while (templateIt != end) {
            CMODExportItem item;
            item.type = "@" + std::string((*templateIt)[1]);
            item.category = "[Template]";
            item.name = (*templateIt)[2];
            allDefinitions.push_back(item);
            ++templateIt;
        }
        
        // 扫描[Custom]定义
        std::regex customRegex(R"(\[Custom\]\s*@(Style|Element|Var)\s+(\w+))");
        std::sregex_iterator customIt(content.begin(), content.end(), customRegex);
        
        while (customIt != end) {
            CMODExportItem item;
            item.type = "@" + std::string((*customIt)[1]);
            item.category = "[Custom]";
            item.name = (*customIt)[2];
            allDefinitions.push_back(item);
            ++customIt;
        }
    }
}

bool CMODModule::generateExportTable() {
    // 如果已经有显式导出表，不需要生成
    if (exportTable.isExplicit) {
        return true;
    }
    
    // 扫描所有定义
    scanDefinitions();
    
    // 将所有定义添加到导出表（自动模式）
    for (const auto& def : allDefinitions) {
        exportTable.addExport(def.type, def.category, def.name);
    }
    
    return true;
}

void CMODModule::addSubModule(std::shared_ptr<CMODModule> subModule) {
    subModules[subModule->getName()] = subModule;
}

std::shared_ptr<CMODModule> CMODModule::getSubModule(const std::string& name) const {
    auto it = subModules.find(name);
    return (it != subModules.end()) ? it->second : nullptr;
}

std::vector<std::string> CMODModule::getSubModuleNames() const {
    std::vector<std::string> names;
    for (const auto& [name, module] : subModules) {
        names.push_back(name);
    }
    return names;
}

bool CMODModule::hasSubModule(const std::string& name) const {
    return subModules.find(name) != subModules.end();
}

std::string CMODModule::getFullName() const {
    if (auto p = parent.lock()) {
        return p->getFullName() + "." + name;
    }
    return name;
}

bool CMODModule::validate() const {
    return info.isValid() && !sourceFiles.empty();
}

bool CMODModule::checkDependencies() const {
    // TODO: 实现依赖检查
    return true;
}

bool CMODModule::checkCHTLVersion(const std::string& currentVersion) const {
    if (!info.minCHTLVersion.empty()) {
        if (CMODHelper::compareVersions(currentVersion, info.minCHTLVersion) < 0) {
            return false;
        }
    }
    
    if (!info.maxCHTLVersion.empty()) {
        if (CMODHelper::compareVersions(currentVersion, info.maxCHTLVersion) > 0) {
            return false;
        }
    }
    
    return true;
}

bool CMODModule::canExport(const std::string& type, const std::string& category, const std::string& name) const {
    return exportTable.isExported(type, category, name);
}

// CMODManager 实现
CMODManager::CMODManager(std::shared_ptr<CHTLContext> ctx) : context(ctx) {
    addDefaultModulePaths();
}

void CMODManager::addModulePath(const fs::path& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        modulePaths.push_back(path);
    }
}

void CMODManager::addDefaultModulePaths() {
    // 添加官方模块路径
    fs::path officialPath = CMODHelper::getOfficialModulePath();
    if (fs::exists(officialPath)) {
        modulePaths.push_back(officialPath);
    }
    
    // 添加当前目录的module文件夹
    fs::path localModulePath = fs::current_path() / "module";
    if (fs::exists(localModulePath)) {
        modulePaths.push_back(localModulePath);
    }
}

std::shared_ptr<CMODModule> CMODManager::loadModule(const std::string& moduleName) {
    // 检查是否已加载
    auto it = loadedModules.find(moduleName);
    if (it != loadedModules.end()) {
        return it->second;
    }
    
    // 查找模块
    fs::path modulePath = findModule(moduleName);
    if (modulePath.empty()) {
        context->reportError("Module not found: " + moduleName);
        return nullptr;
    }
    
    return loadModuleFromPath(modulePath);
}

std::shared_ptr<CMODModule> CMODManager::loadModuleFromPath(const fs::path& path) {
    std::string moduleName = path.filename().string();
    
    // 如果是.cmod文件，去掉扩展名
    if (moduleName.ends_with(".cmod")) {
        moduleName = moduleName.substr(0, moduleName.length() - 5);
    }
    
    auto module = std::make_shared<CMODModule>(moduleName, path);
    if (module->load()) {
        loadedModules[moduleName] = module;
        return module;
    }
    
    return nullptr;
}

fs::path CMODManager::findModule(const std::string& moduleName) {
    // 首先检查缓存
    auto cacheIt = moduleCache.find(moduleName);
    if (cacheIt != moduleCache.end()) {
        return cacheIt->second;
    }
    
    // 在所有模块路径中查找
    for (const auto& modulePath : modulePaths) {
        fs::path found = findInDirectory(modulePath, moduleName);
        if (!found.empty()) {
            moduleCache[moduleName] = found;
            return found;
        }
    }
    
    return fs::path();
}

fs::path CMODManager::findInDirectory(const fs::path& dir, const std::string& moduleName) {
    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        return fs::path();
    }
    
    // 查找.cmod文件
    fs::path cmodFile = dir / (moduleName + ".cmod");
    if (fs::exists(cmodFile) && fs::is_regular_file(cmodFile)) {
        return cmodFile;
    }
    
    // 查找目录形式的模块
    fs::path moduleDir = dir / moduleName;
    if (fs::exists(moduleDir) && fs::is_directory(moduleDir)) {
        // 验证是否是有效的模块目录
        if (fs::exists(moduleDir / "src") && fs::exists(moduleDir / "info")) {
            return moduleDir;
        }
    }
    
    return fs::path();
}

std::shared_ptr<CMODModule> CMODManager::getModule(const std::string& fullModuleName) {
    // 处理子模块路径，如 "Chtholly.Space"
    size_t dotPos = fullModuleName.find('.');
    if (dotPos != std::string::npos) {
        std::string mainModule = fullModuleName.substr(0, dotPos);
        std::string subPath = fullModuleName.substr(dotPos + 1);
        
        auto module = loadModule(mainModule);
        if (!module) {
            return nullptr;
        }
        
        // 递归查找子模块
        size_t nextDot = subPath.find('.');
        while (nextDot != std::string::npos) {
            std::string subName = subPath.substr(0, nextDot);
            module = module->getSubModule(subName);
            if (!module) {
                return nullptr;
            }
            subPath = subPath.substr(nextDot + 1);
            nextDot = subPath.find('.');
        }
        
        return module->getSubModule(subPath);
    }
    
    return loadModule(fullModuleName);
}

void CMODManager::buildCache() {
    moduleCache.clear();
    
    for (const auto& modulePath : modulePaths) {
        if (!fs::exists(modulePath) || !fs::is_directory(modulePath)) {
            continue;
        }
        
        for (const auto& entry : fs::directory_iterator(modulePath)) {
            std::string name = entry.path().filename().string();
            
            if (entry.is_regular_file() && name.ends_with(".cmod")) {
                name = name.substr(0, name.length() - 5);
                moduleCache[name] = entry.path();
            } else if (entry.is_directory()) {
                if (fs::exists(entry.path() / "src") && fs::exists(entry.path() / "info")) {
                    moduleCache[name] = entry.path();
                }
            }
        }
    }
}

void CMODManager::clearCache() {
    moduleCache.clear();
}

bool CMODManager::validateModule(const CMODModule& module) const {
    return module.validate() && module.checkDependencies();
}

void CMODManager::clear() {
    loadedModules.clear();
    moduleCache.clear();
}

// CMODHelper 实现
namespace CMODHelper {

bool isVersionCompatible(const std::string& required, const std::string& current) {
    return compareVersions(current, required) >= 0;
}

int compareVersions(const std::string& v1, const std::string& v2) {
    std::vector<int> parts1, parts2;
    
    // 解析版本号
    std::stringstream ss1(v1), ss2(v2);
    std::string part;
    
    while (std::getline(ss1, part, '.')) {
        parts1.push_back(std::stoi(part));
    }
    
    while (std::getline(ss2, part, '.')) {
        parts2.push_back(std::stoi(part));
    }
    
    // 比较
    size_t maxSize = std::max(parts1.size(), parts2.size());
    for (size_t i = 0; i < maxSize; ++i) {
        int p1 = (i < parts1.size()) ? parts1[i] : 0;
        int p2 = (i < parts2.size()) ? parts2[i] : 0;
        
        if (p1 < p2) return -1;
        if (p1 > p2) return 1;
    }
    
    return 0;
}

std::string moduleNameToPath(const std::string& moduleName) {
    std::string path = moduleName;
    std::replace(path.begin(), path.end(), '.', '/');
    return path;
}

std::string pathToModuleName(const fs::path& path) {
    std::string name = path.string();
    std::replace(name.begin(), name.end(), '/', '.');
    std::replace(name.begin(), name.end(), '\\', '.');
    return name;
}

bool isValidModuleName(const std::string& name) {
    std::regex validName("^[A-Za-z][A-Za-z0-9_]*$");
    return std::regex_match(name, validName);
}

bool isCMODFile(const fs::path& path) {
    return path.extension() == ".cmod";
}

bool isCHTLFile(const fs::path& path) {
    return path.extension() == ".chtl";
}

fs::path getOfficialModulePath() {
    // TODO: 从配置或环境变量获取
    return fs::path("/usr/local/share/chtl/modules");
}

fs::path getLocalModulePath() {
    return fs::current_path() / "module";
}

bool createModuleTemplate(const fs::path& path, const std::string& moduleName) {
    try {
        // 创建目录结构
        fs::create_directories(path / moduleName / "src");
        fs::create_directories(path / moduleName / "info");
        
        // 创建主模块文件
        std::ofstream mainFile(path / moduleName / "src" / (moduleName + ".chtl"));
        mainFile << "// Main module file for " << moduleName << "\n\n";
        mainFile << "[Namespace] " << moduleName << "\n{\n";
        mainFile << "    // Add your module content here\n";
        mainFile << "}\n";
        mainFile.close();
        
        // 创建信息文件
        std::ofstream infoFile(path / moduleName / "info" / (moduleName + ".chtl"));
        CMODInfo info;
        info.name = moduleName;
        info.version = "1.0.0";
        info.description = "Description for " + moduleName;
        info.author = "Your Name";
        info.license = "MIT";
        info.minCHTLVersion = "1.0.0";
        
        infoFile << info.toString();
        infoFile.close();
        
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

} // namespace CMODHelper

// CMODProcessor 实现
bool CMODProcessor::processCMODImport(const std::string& moduleName) {
    // 处理子模块导入
    if (moduleName.find('.') != std::string::npos) {
        return processSubModuleImport(moduleName);
    }
    
    // 加载主模块
    auto module = manager.loadModule(moduleName);
    if (!module) {
        return false;
    }
    
    // 处理依赖
    if (!processDependencies(*module)) {
        return false;
    }
    
    // 导入模块内容
    return importModuleContent(module);
}

bool CMODProcessor::processSubModuleImport(const std::string& fullModuleName) {
    auto module = manager.getModule(fullModuleName);
    if (!module) {
        return false;
    }
    
    return importModuleContent(module);
}

bool CMODProcessor::importModuleContent(std::shared_ptr<CMODModule> module) {
    // 导入所有源文件
    for (const auto& srcFile : module->getSourceFiles()) {
        // 读取文件内容
        std::ifstream file(srcFile);
        if (!file.is_open()) continue;
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        
        // 过滤内容：只导入允许导出的项
        std::string filteredContent = filterExportedContent(module, content);
        
        // 使用过滤后的内容
        // generator.processImportStatement("@Chtl from " + srcFile.string());
        // 实际应该处理filteredContent
    }
    
    // 导入所有子模块
    for (const auto& subModuleName : module->getSubModuleNames()) {
        auto subModule = module->getSubModule(subModuleName);
        if (subModule) {
            importModuleContent(subModule);
        }
    }
    
    return true;
}

std::string CMODProcessor::filterExportedContent(std::shared_ptr<CMODModule> module, 
                                                const std::string& content) {
    if (!module->getExportTable().isExplicit) {
        // 非显式模式，返回全部内容
        return content;
    }
    
    // 显式模式，过滤内容
    std::stringstream filtered;
    std::istringstream stream(content);
    std::string line;
    bool inDefinition = false;
    std::string currentType, currentCategory, currentName;
    std::stringstream currentBlock;
    
    while (std::getline(stream, line)) {
        // 检查是否是定义开始
        std::regex defRegex(R"(\[(Template|Custom)\]\s*@(Style|Element|Var)\s+(\w+))");
        std::smatch match;
        
        if (std::regex_search(line, match, defRegex)) {
            // 如果之前在定义中，先检查是否应该包含
            if (inDefinition) {
                if (module->canExport(currentType, currentCategory, currentName)) {
                    filtered << currentBlock.str();
                }
                currentBlock.str("");
            }
            
            // 开始新定义
            inDefinition = true;
            currentCategory = "[" + std::string(match[1]) + "]";
            currentType = "@" + std::string(match[2]);
            currentName = match[3];
        }
        
        if (inDefinition) {
            currentBlock << line << "\n";
            
            // 检查是否是定义结束（简单检查大括号匹配）
            static int braceCount = 0;
            for (char c : line) {
                if (c == '{') braceCount++;
                else if (c == '}') braceCount--;
            }
            
            if (braceCount == 0 && line.find('}') != std::string::npos) {
                // 定义结束
                if (module->canExport(currentType, currentCategory, currentName)) {
                    filtered << currentBlock.str();
                }
                currentBlock.str("");
                inDefinition = false;
            }
        } else {
            // 不在定义中，直接包含（如命名空间等）
            filtered << line << "\n";
        }
    }
    
    // 处理最后一个定义
    if (inDefinition && module->canExport(currentType, currentCategory, currentName)) {
        filtered << currentBlock.str();
    }
    
    return filtered.str();
}

bool CMODProcessor::processDependencies(const CMODModule& module) {
    if (module.getInfo().dependencies.empty()) {
        return true;
    }
    
    // 解析依赖列表
    std::stringstream ss(module.getInfo().dependencies);
    std::string dep;
    
    while (std::getline(ss, dep, ',')) {
        // 去除空格
        dep.erase(0, dep.find_first_not_of(" \t"));
        dep.erase(dep.find_last_not_of(" \t") + 1);
        
        if (!dep.empty()) {
            if (!processCMODImport(dep)) {
                return false;
            }
        }
    }
    
    return true;
}

// CMODPacker 实现
CMODPacker::CMODPacker(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}

bool CMODPacker::pack(const std::string& moduleName) {
    fs::path moduleDir = sourcePath / moduleName;
    
    if (!validateStructure(moduleDir)) {
        context->reportError("Invalid module structure: " + moduleDir.string());
        return false;
    }
    
    fs::path outputFile = outputPath / (moduleName + ".cmod");
    return packDirectory(moduleDir, outputFile);
}

bool CMODPacker::packDirectory(const fs::path& dir, const std::string& outputFile) {
    // 简单的打包实现：创建一个包含所有文件内容的文本格式
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    
    // 写入魔术数字和版本
    out << "CMOD\n";
    out << "1.0\n";
    
    // 收集所有文件
    std::vector<std::pair<fs::path, fs::path>> files; // relative_path, absolute_path
    
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (fs::is_regular_file(entry)) {
            fs::path relativePath = fs::relative(entry.path(), dir);
            files.push_back({relativePath, entry.path()});
        }
    }
    
    // 写入文件数量
    out << files.size() << "\n";
    
    // 写入每个文件
    for (const auto& [relPath, absPath] : files) {
        // 写入文件路径
        out << relPath.string() << "\n";
        
        // 写入文件大小
        size_t fileSize = fs::file_size(absPath);
        out << fileSize << "\n";
        
        // 写入文件内容
        std::ifstream in(absPath, std::ios::binary);
        if (in.is_open()) {
            out << in.rdbuf();
            in.close();
        }
        out << "\n";
    }
    
    out.close();
    return true;
}

bool CMODPacker::validateStructure(const fs::path& moduleDir) const {
    return hasValidSrcFolder(moduleDir) && hasValidInfoFolder(moduleDir);
}

bool CMODPacker::hasValidSrcFolder(const fs::path& moduleDir) const {
    fs::path srcDir = moduleDir / "src";
    return fs::exists(srcDir) && fs::is_directory(srcDir);
}

bool CMODPacker::hasValidInfoFolder(const fs::path& moduleDir) const {
    fs::path infoDir = moduleDir / "info";
    if (!fs::exists(infoDir) || !fs::is_directory(infoDir)) {
        return false;
    }
    
    // 检查info文件是否存在
    std::string moduleName = moduleDir.filename().string();
    fs::path infoFile = infoDir / (moduleName + ".chtl");
    
    return fs::exists(infoFile) && fs::is_regular_file(infoFile);
}

bool CMODPacker::generateExportTable(const fs::path& moduleDir, CMODExportTable& exportTable) {
    fs::path srcDir = moduleDir / "src";
    
    // 扫描所有源文件
    for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
        if (fs::is_regular_file(entry) && CMODHelper::isCHTLFile(entry.path())) {
            extractExports(entry.path(), exportTable);
        }
    }
    
    return true;
}

void CMODPacker::scanSourceFiles(const fs::path& srcDir, std::vector<std::string>& files) {
    for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
        if (fs::is_regular_file(entry) && CMODHelper::isCHTLFile(entry.path())) {
            files.push_back(fs::relative(entry.path(), srcDir).string());
        }
    }
}

void CMODPacker::extractExports(const fs::path& chtlFile, CMODExportTable& exportTable) {
    std::ifstream file(chtlFile);
    if (!file.is_open()) {
        return;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();
    
    // 查找[Template]定义
    std::regex templateRegex(R"(\[Template\]\s*@(Style|Element|Var)\s+(\w+))");
    std::sregex_iterator templateIt(content.begin(), content.end(), templateRegex);
    std::sregex_iterator end;
    
    while (templateIt != end) {
        std::string type = "@" + std::string((*templateIt)[1]);
        std::string name = (*templateIt)[2];
        exportTable.addExport(type, "[Template]", name);
        ++templateIt;
    }
    
    // 查找[Custom]定义
    std::regex customRegex(R"(\[Custom\]\s*@(Style|Element|Var)\s+(\w+))");
    std::sregex_iterator customIt(content.begin(), content.end(), customRegex);
    
    while (customIt != end) {
        std::string type = "@" + std::string((*customIt)[1]);
        std::string name = (*customIt)[2];
        exportTable.addExport(type, "[Custom]", name);
        ++customIt;
    }
}

// CMODUnpacker 实现
bool CMODUnpacker::unpack(const fs::path& cmodFile, const fs::path& outputDir) {
    std::ifstream in(cmodFile, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    
    // 读取魔术数字
    std::string magic;
    std::getline(in, magic);
    if (magic != "CMOD") {
        return false;
    }
    
    // 读取版本
    std::string version;
    std::getline(in, version);
    
    // 读取文件数量
    size_t fileCount;
    in >> fileCount;
    in.ignore(); // 忽略换行符
    
    // 创建输出目录
    fs::create_directories(outputDir);
    
    // 读取每个文件
    for (size_t i = 0; i < fileCount; ++i) {
        // 读取文件路径
        std::string relPath;
        std::getline(in, relPath);
        
        // 读取文件大小
        size_t fileSize;
        in >> fileSize;
        in.ignore(); // 忽略换行符
        
        // 创建文件路径
        fs::path filePath = outputDir / relPath;
        fs::create_directories(filePath.parent_path());
        
        // 读取并写入文件内容
        std::vector<char> buffer(fileSize);
        in.read(buffer.data(), fileSize);
        in.ignore(); // 忽略换行符
        
        std::ofstream out(filePath, std::ios::binary);
        if (out.is_open()) {
            out.write(buffer.data(), fileSize);
            out.close();
        }
    }
    
    in.close();
    return true;
}

bool CMODUnpacker::validateCMODFile(const fs::path& cmodFile) const {
    std::ifstream in(cmodFile, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    
    std::string magic;
    std::getline(in, magic);
    in.close();
    
    return magic == "CMOD";
}

bool CMODUnpacker::extractInfo(const fs::path& cmodFile, CMODInfo& info) {
    // 临时解包到内存或临时目录来读取info
    // TODO: 实现更高效的方式直接从.cmod文件读取info
    return false;
}

} // namespace chtl