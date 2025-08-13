#include "CHTLCJMOD.h"
#include "CHTLScript.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <dlfcn.h>  // Linux动态库加载
#include <cstdlib>

namespace chtl {

namespace fs = std::filesystem;

// CJMODInfo 实现
std::string CJMODInfo::toString() const {
    std::stringstream ss;
    
    // 首先输出基类信息
    ss << CMODInfo::toString();
    
    // 添加CJMOD特定信息
    ss << "\n// CJMOD Specific Info\n";
    ss << "jsVersion = \"" << jsVersion << "\";\n";
    ss << "syntaxExtensions = \"" << syntaxExtensions << "\";\n";
    ss << "requiredHeaders = \"" << requiredHeaders << "\";\n";
    
    return ss.str();
}

// CJMODExportTable 实现
void CJMODExportTable::addExport(const CJMODExport& exp) {
    if (exp.type == "function") {
        functions.push_back(exp);
    } else if (exp.type == "operator") {
        operators.push_back(exp);
    } else if (exp.type == "syntax") {
        syntaxes.push_back(exp);
    } else if (exp.type == "transformer") {
        transformers.push_back(exp);
    }
}

bool CJMODExportTable::isExported(const std::string& type, const std::string& name) const {
    if (!isExplicit) {
        return true;
    }
    
    const std::vector<CJMODExport>* exports = nullptr;
    if (type == "function") exports = &functions;
    else if (type == "operator") exports = &operators;
    else if (type == "syntax") exports = &syntaxes;
    else if (type == "transformer") exports = &transformers;
    
    if (!exports) return false;
    
    return std::any_of(exports->begin(), exports->end(),
        [&name](const CJMODExport& exp) { return exp.name == name; });
}

std::string CJMODExportTable::toString() const {
    std::stringstream ss;
    ss << "[JSExport]\n{\n";
    
    // 导出函数
    if (!functions.empty()) {
        ss << "    functions {\n";
        for (const auto& func : functions) {
            ss << "        " << func.name << ": \"" << func.signature << "\"";
            if (!func.description.empty()) {
                ss << " // " << func.description;
            }
            ss << ";\n";
        }
        ss << "    }\n\n";
    }
    
    // 导出操作符
    if (!operators.empty()) {
        ss << "    operators {\n";
        for (const auto& op : operators) {
            ss << "        " << op.name << ": \"" << op.signature << "\";\n";
        }
        ss << "    }\n\n";
    }
    
    // 导出语法
    if (!syntaxes.empty()) {
        ss << "    syntaxes {\n";
        for (const auto& syn : syntaxes) {
            ss << "        " << syn.name << ": \"" << syn.signature << "\";\n";
        }
        ss << "    }\n";
    }
    
    ss << "}\n";
    return ss.str();
}

CJMODExportTable CJMODExportTable::parse(const std::string& exportBlock) {
    CJMODExportTable table;
    
    // 检查是否有[JSExport]块
    std::regex exportRegex(R"(\[JSExport\]\s*\{([^}]*)\})");
    std::smatch exportMatch;
    
    if (!std::regex_search(exportBlock, exportMatch, exportRegex)) {
        table.isExplicit = false;
        return table;
    }
    
    table.isExplicit = true;
    std::string content = exportMatch[1];
    
    // 解析各种导出类型
    // TODO: 实现详细的解析逻辑
    
    return table;
}

// CJMODModule 实现
CJMODModule::CJMODModule(const std::string& n, const fs::path& path, bool isSub)
    : name(n), rootPath(path), isSubModule(isSub) {}

CJMODModule::~CJMODModule() {
    // 卸载动态库
    if (libraryHandle) {
        dlclose(libraryHandle);
    }
}

bool CJMODModule::load() {
    if (fs::exists(rootPath) && fs::is_directory(rootPath)) {
        return loadFromDirectory(rootPath);
    } else if (fs::exists(rootPath) && rootPath.extension() == ".cjmod") {
        return loadFromCJMODFile(rootPath);
    }
    return false;
}

bool CJMODModule::loadFromDirectory(const fs::path& dir) {
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
    for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
        if (fs::is_regular_file(entry)) {
            std::string ext = entry.path().extension().string();
            if (ext == ".cpp" || ext == ".cc" || ext == ".cxx" || ext == ".h" || ext == ".hpp") {
                sourceFiles.push_back(entry.path());
            }
        }
    }
    
    // 查找子模块
    for (const auto& entry : fs::directory_iterator(srcDir)) {
        if (fs::is_directory(entry)) {
            std::string subModuleName = entry.path().filename().string();
            
            // 检查是否是有效的子模块
            fs::path subSrcDir = entry.path() / "src";
            fs::path subInfoDir = entry.path() / "info";
            
            if (fs::exists(subSrcDir) && fs::exists(subInfoDir)) {
                auto subModule = std::make_shared<CJMODModule>(subModuleName, entry.path(), true);
                subModule->parent = std::weak_ptr<CJMODModule>(shared_from_this());
                
                if (subModule->load()) {
                    addSubModule(subModule);
                }
            }
        }
    }
    
    // 编译并加载扩展
    if (!sourceFiles.empty()) {
        if (compileSources()) {
            loadExtensions();
        }
    }
    
    return true;
}

bool CJMODModule::loadFromCJMODFile(const fs::path& cjmodFile) {
    // TODO: 实现从.cjmod文件加载
    return false;
}

bool CJMODModule::loadInfo(const fs::path& infoFile) {
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
    
    // 解析基本信息（使用CMODInfo的解析）
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
            
            // 基类字段
            if (key == "name") info.name = value;
            else if (key == "version") info.version = value;
            else if (key == "description") info.description = value;
            else if (key == "author") info.author = value;
            else if (key == "license") info.license = value;
            else if (key == "dependencies") info.dependencies = value;
            else if (key == "category") info.category = value;
            else if (key == "minCHTLVersion") info.minCHTLVersion = value;
            else if (key == "maxCHTLVersion") info.maxCHTLVersion = value;
            // CJMOD特定字段
            else if (key == "jsVersion") info.jsVersion = value;
            else if (key == "syntaxExtensions") info.syntaxExtensions = value;
            else if (key == "requiredHeaders") info.requiredHeaders = value;
            
            ++it;
        }
    }
    
    // 加载导出表
    exportTable = CJMODExportTable::parse(content);
    
    return info.isValid();
}

bool CJMODModule::compileSources() {
    // 创建临时构建目录
    fs::path buildDir = rootPath / "build";
    fs::create_directories(buildDir);
    
    // 生成编译命令
    std::stringstream cmd;
    cmd << "g++ -std=c++17 -fPIC -shared";
    
    // 添加源文件
    for (const auto& src : sourceFiles) {
        if (src.extension() == ".cpp" || src.extension() == ".cc" || src.extension() == ".cxx") {
            cmd << " " << src.string();
        }
    }
    
    // 输出文件
    fs::path outputFile = buildDir / (name + ".so");
    cmd << " -o " << outputFile.string();
    
    // 执行编译
    int result = std::system(cmd.str().c_str());
    if (result != 0) {
        return false;
    }
    
    // 记录编译后的动态库路径
    libraryHandle = dlopen(outputFile.c_str(), RTLD_NOW | RTLD_LOCAL);
    return libraryHandle != nullptr;
}

bool CJMODModule::loadExtensions() {
    if (!libraryHandle) {
        return false;
    }
    
    // 查找工厂函数
    typedef std::unique_ptr<ICJMODExtension> (*ExtensionFactory)();
    ExtensionFactory factory = (ExtensionFactory)dlsym(libraryHandle, "createExtension");
    
    if (!factory) {
        return false;
    }
    
    // 创建扩展实例
    auto extension = factory();
    if (extension) {
        extensions.push_back(std::move(extension));
        return true;
    }
    
    return false;
}

bool CJMODModule::loadExtensionFromFile(const fs::path& soFile) {
    void* handle = dlopen(soFile.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!handle) {
        return false;
    }
    
    typedef std::unique_ptr<ICJMODExtension> (*ExtensionFactory)();
    ExtensionFactory factory = (ExtensionFactory)dlsym(handle, "createExtension");
    
    if (!factory) {
        dlclose(handle);
        return false;
    }
    
    auto extension = factory();
    if (extension) {
        extensions.push_back(std::move(extension));
        return true;
    }
    
    dlclose(handle);
    return false;
}

ICJMODExtension* CJMODModule::getExtension(const std::string& name) const {
    for (const auto& ext : extensions) {
        if (ext->getName() == name) {
            return ext.get();
        }
    }
    return nullptr;
}

void CJMODModule::addSubModule(std::shared_ptr<CJMODModule> subModule) {
    subModules[subModule->getName()] = subModule;
}

std::shared_ptr<CJMODModule> CJMODModule::getSubModule(const std::string& name) const {
    auto it = subModules.find(name);
    return (it != subModules.end()) ? it->second : nullptr;
}

std::vector<std::string> CJMODModule::getSubModuleNames() const {
    std::vector<std::string> names;
    for (const auto& [name, module] : subModules) {
        names.push_back(name);
    }
    return names;
}

std::string CJMODModule::getFullName() const {
    if (auto p = parent.lock()) {
        return p->getFullName() + "." + name;
    }
    return name;
}

bool CJMODModule::canExport(const std::string& type, const std::string& name) const {
    return exportTable.isExported(type, name);
}

// CJMODManager 实现
CJMODManager::CJMODManager(std::shared_ptr<CHTLContext> ctx) : context(ctx) {
    // 添加默认包含路径
    addIncludePath("/usr/include");
    addIncludePath("/usr/local/include");
    
    // 添加默认库路径
    addLibraryPath("/usr/lib");
    addLibraryPath("/usr/local/lib");
}

void CJMODManager::addModulePath(const fs::path& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        modulePaths.push_back(path);
    }
}

void CJMODManager::addIncludePath(const fs::path& path) {
    includePaths.push_back(path.string());
}

void CJMODManager::addLibraryPath(const fs::path& path) {
    libraryPaths.push_back(path.string());
}

std::shared_ptr<CJMODModule> CJMODManager::loadModule(const std::string& moduleName) {
    // 检查是否已加载
    auto it = loadedModules.find(moduleName);
    if (it != loadedModules.end()) {
        return it->second;
    }
    
    // 在模块路径中查找
    for (const auto& path : modulePaths) {
        fs::path modulePath = path / moduleName;
        if (fs::exists(modulePath) && fs::is_directory(modulePath)) {
            auto module = std::make_shared<CJMODModule>(moduleName, modulePath);
            if (module->load()) {
                loadedModules[moduleName] = module;
                return module;
            }
        }
        
        // 也检查.cjmod文件
        fs::path cjmodFile = path / (moduleName + ".cjmod");
        if (fs::exists(cjmodFile)) {
            auto module = std::make_shared<CJMODModule>(moduleName, cjmodFile);
            if (module->load()) {
                loadedModules[moduleName] = module;
                return module;
            }
        }
    }
    
    return nullptr;
}

std::shared_ptr<CJMODModule> CJMODManager::loadModuleFromPath(const fs::path& path) {
    std::string moduleName = path.filename().string();
    if (moduleName.ends_with(".cjmod")) {
        moduleName = moduleName.substr(0, moduleName.length() - 6);
    }
    
    auto module = std::make_shared<CJMODModule>(moduleName, path);
    if (module->load()) {
        loadedModules[moduleName] = module;
        return module;
    }
    
    return nullptr;
}

void CJMODManager::registerExtensionFactory(const std::string& name, CJMODExtensionFactory factory) {
    extensionFactories[name] = factory;
}

std::unique_ptr<ICJMODExtension> CJMODManager::createExtension(const std::string& name) {
    auto it = extensionFactories.find(name);
    if (it != extensionFactories.end()) {
        return it->second();
    }
    return nullptr;
}

std::string CJMODManager::preprocessScript(const std::string& script) {
    std::string result = script;
    
    // 应用所有加载的扩展的预处理
    for (const auto& [name, module] : loadedModules) {
        for (const auto& ext : module->getExtensions()) {
            result = ext->preprocess(result);
        }
    }
    
    return result;
}

std::string CJMODManager::transformScript(const std::string& script) {
    std::string result = script;
    
    // 应用所有加载的扩展的转换
    for (const auto& [name, module] : loadedModules) {
        for (const auto& ext : module->getExtensions()) {
            result = ext->transform(result);
        }
    }
    
    return result;
}

void CJMODManager::clear() {
    loadedModules.clear();
    extensionFactories.clear();
}

// CJMODBuilder 实现
CJMODBuilder::CJMODBuilder(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}

bool CJMODBuilder::build(const std::string& moduleName) {
    fs::path moduleDir = sourcePath / moduleName;
    
    if (!validate(moduleDir)) {
        context->reportError("Invalid CJMOD structure: " + moduleDir.string());
        return false;
    }
    
    // 编译源码
    fs::path srcDir = moduleDir / "src";
    fs::path outputFile = outputPath / (moduleName + ".so");
    
    if (!compile(srcDir, outputFile)) {
        return false;
    }
    
    // 打包成.cjmod
    fs::path cjmodFile = outputPath / (moduleName + ".cjmod");
    return package(moduleDir, cjmodFile);
}

bool CJMODBuilder::buildFromTemplate(const std::string& moduleName, const std::string& templateType) {
    // 创建模块结构
    if (!CJMODHelper::createExtensionTemplate(sourcePath, moduleName, templateType)) {
        return false;
    }
    
    // 构建模块
    return build(moduleName);
}

bool CJMODBuilder::compile(const fs::path& srcDir, const fs::path& outputFile) {
    std::stringstream cmd;
    cmd << "g++ -std=c++17 -fPIC -shared";
    
    // 添加所有cpp文件
    for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
        if (fs::is_regular_file(entry)) {
            std::string ext = entry.path().extension().string();
            if (ext == ".cpp" || ext == ".cc" || ext == ".cxx") {
                cmd << " " << entry.path().string();
            }
        }
    }
    
    cmd << " -o " << outputFile.string();
    
    int result = std::system(cmd.str().c_str());
    return result == 0;
}

bool CJMODBuilder::package(const fs::path& moduleDir, const fs::path& outputFile) {
    // 简单的打包实现（类似CMOD）
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    
    out << "CJMOD\n";
    out << "1.0\n";
    
    // TODO: 实现文件打包逻辑
    
    out.close();
    return true;
}

bool CJMODBuilder::validate(const fs::path& moduleDir) {
    // 验证目录结构
    fs::path srcDir = moduleDir / "src";
    fs::path infoDir = moduleDir / "info";
    
    if (!fs::exists(srcDir) || !fs::is_directory(srcDir)) {
        return false;
    }
    
    if (!fs::exists(infoDir) || !fs::is_directory(infoDir)) {
        return false;
    }
    
    // 检查info文件
    std::string moduleName = moduleDir.filename().string();
    fs::path infoFile = infoDir / (moduleName + ".chtl");
    
    return fs::exists(infoFile);
}

// CJMODProcessor 实现
bool CJMODProcessor::loadCJMODExtensions(const std::string& moduleName) {
    auto module = manager.loadModule(moduleName);
    if (!module) {
        return false;
    }
    
    return applyExtensions(module);
}

bool CJMODProcessor::applyExtensions(std::shared_ptr<CJMODModule> module) {
    for (const auto& ext : module->getExtensions()) {
        // 初始化扩展
        if (!ext->initialize(std::dynamic_pointer_cast<CHTLJSContext>(scriptProcessor->getContext()))) {
            continue;
        }
        
        // 注册扩展函数
        registerExtensionFunctions(ext.get());
    }
    
    return true;
}

void CJMODProcessor::registerExtensionFunctions(ICJMODExtension* extension) {
    extension->registerFunctions(scriptProcessor);
}

// CJMODHelper 实现
namespace CJMODHelper {

bool createExtensionTemplate(const fs::path& path, 
                            const std::string& moduleName,
                            const std::string& extensionType) {
    try {
        // 创建目录结构
        fs::create_directories(path / moduleName / "src");
        fs::create_directories(path / moduleName / "info");
        
        // 创建信息文件
        std::ofstream infoFile(path / moduleName / "info" / (moduleName + ".chtl"));
        CJMODInfo info;
        info.name = moduleName;
        info.version = "1.0.0";
        info.description = "CJMOD extension for " + extensionType;
        info.author = "Your Name";
        info.license = "MIT";
        info.jsVersion = "ES6+";
        info.syntaxExtensions = extensionType;
        
        infoFile << info.toString();
        infoFile.close();
        
        // 创建源文件
        std::string className = moduleName + "Extension";
        
        // 头文件
        std::ofstream headerFile(path / moduleName / "src" / (moduleName + ".h"));
        headerFile << "#ifndef " << moduleName << "_H\n";
        headerFile << "#define " << moduleName << "_H\n\n";
        headerFile << "#include <chtl/CHTLCJMOD.h>\n\n";
        headerFile << generateExtensionSkeleton(className, extensionType);
        headerFile << "\n#endif // " << moduleName << "_H\n";
        headerFile.close();
        
        // 实现文件
        std::ofstream cppFile(path / moduleName / "src" / (moduleName + ".cpp"));
        cppFile << "#include \"" << moduleName << ".h\"\n\n";
        cppFile << "// Implementation of " << className << "\n\n";
        cppFile << "// Export factory function\n";
        cppFile << "CJMOD_EXTENSION_FACTORY(" << className << ")\n";
        cppFile.close();
        
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::string generateExtensionSkeleton(const std::string& className,
                                     const std::string& extensionType) {
    std::stringstream ss;
    
    ss << "class " << className << " : public chtl::CJMODExtensionBase {\n";
    ss << "public:\n";
    ss << "    " << className << "()\n";
    ss << "        : CJMODExtensionBase(\"" << className << "\", \"1.0.0\", ";
    ss << "\"" << extensionType << " extension\") {}\n\n";
    
    if (extensionType == "function") {
        ss << "    void registerFunctions(std::shared_ptr<chtl::ScriptProcessor> processor) override {\n";
        ss << "        // Register custom functions here\n";
        ss << "        // Example: processor->registerFunction(\"myFunc\", ...);\n";
        ss << "    }\n";
    } else if (extensionType == "syntax") {
        ss << "    std::string preprocess(const std::string& script) override {\n";
        ss << "        // Preprocess script to handle custom syntax\n";
        ss << "        return script;\n";
        ss << "    }\n\n";
        ss << "    std::string transform(const std::string& script) override {\n";
        ss << "        // Transform custom syntax to standard JavaScript\n";
        ss << "        return script;\n";
        ss << "    }\n";
    }
    
    ss << "};\n";
    
    return ss.str();
}

std::string generateCMakeFile(const std::string& moduleName,
                             const std::vector<std::string>& sources) {
    std::stringstream ss;
    
    ss << "cmake_minimum_required(VERSION 3.10)\n";
    ss << "project(" << moduleName << ")\n\n";
    ss << "set(CMAKE_CXX_STANDARD 17)\n";
    ss << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n";
    ss << "# Find CHTL\n";
    ss << "find_package(CHTL REQUIRED)\n\n";
    ss << "# Create shared library\n";
    ss << "add_library(" << moduleName << " SHARED\n";
    
    for (const auto& src : sources) {
        ss << "    " << src << "\n";
    }
    
    ss << ")\n\n";
    ss << "target_link_libraries(" << moduleName << " CHTL::Core)\n";
    ss << "target_include_directories(" << moduleName << " PUBLIC ${CHTL_INCLUDE_DIRS})\n";
    
    return ss.str();
}

bool validateCppCode(const fs::path& sourceFile) {
    // 简单的语法检查
    std::stringstream cmd;
    cmd << "g++ -std=c++17 -fsyntax-only " << sourceFile.string();
    
    int result = std::system(cmd.str().c_str());
    return result == 0;
}

std::vector<std::string> extractExportedSymbols(const fs::path& soFile) {
    std::vector<std::string> symbols;
    
    // 使用nm命令提取符号
    std::stringstream cmd;
    cmd << "nm -D " << soFile.string() << " | grep ' T ' | awk '{print $3}'";
    
    FILE* pipe = popen(cmd.str().c_str(), "r");
    if (pipe) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), pipe)) {
            std::string symbol(buffer);
            if (!symbol.empty() && symbol.back() == '\n') {
                symbol.pop_back();
            }
            symbols.push_back(symbol);
        }
        pclose(pipe);
    }
    
    return symbols;
}

} // namespace CJMODHelper

} // namespace chtl