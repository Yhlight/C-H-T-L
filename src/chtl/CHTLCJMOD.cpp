#include "CHTLCJMOD.h"
#include "CHTLScript.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <dlfcn.h>  // Linux动态库加载
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <chrono>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace chtl {

namespace fs = std::filesystem;

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
    
    // 加载模块信息 - info文件必须与模块名相同
    fs::path infoFile = infoDir / (name + ".chtl");
    if (!loadInfo(infoFile)) {
        return false;
    }
    
    // 扫描源文件 - 不要求特定的主文件
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

bool CJMODModule::loadFromCJMODFile(const fs::path& cjmodFile, const fs::path& target) {
    if (!fs::exists(cjmodFile)) {
        return false;
    }
    
    // 创建临时目录
    std::string tempDirName = "cjmod_temp_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    fs::path tempDir = fs::temp_directory_path() / tempDirName;
    fs::create_directories(tempDir);
    
    // 解压tar.gz文件
    std::string extractCmd = "tar -xzf \"" + cjmodFile.string() + "\" -C \"" + tempDir.string() + "\"";
    int result = std::system(extractCmd.c_str());
    
    if (result != 0) {
        fs::remove_all(tempDir);
        return false;
    }
    
    try {
        // 查找模块目录
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
        
        // 加载元数据
        fs::path metaFile = moduleDir / ".cjmod_metadata";
        if (fs::exists(metaFile)) {
            std::ifstream meta(metaFile);
            if (meta.is_open()) {
                // 简单解析JSON格式的元数据
                std::string line;
                while (std::getline(meta, line)) {
                    if (line.find("\"package_type\"") != std::string::npos && 
                        line.find("\"CJMOD\"") == std::string::npos) {
                        fs::remove_all(tempDir);
                        return false;
                    }
                }
            }
        }
        
        // 加载info文件
        fs::path infoDir = moduleDir / "info";
        if (fs::exists(infoDir)) {
            // 查找info文件（ModuleName.chtl）
            for (const auto& entry : fs::directory_iterator(infoDir)) {
                if (entry.is_regular_file() && entry.path().extension() == ".chtl") {
                    loadInfo(entry.path());
                    break;
                }
            }
        }
        
        // 复制库文件
        fs::path libDir = moduleDir / "lib";
        if (fs::exists(libDir)) {
            for (const auto& entry : fs::directory_iterator(libDir)) {
                if (entry.is_regular_file()) {
                    auto ext = entry.path().extension();
                    if (ext == ".so" || ext == ".dll" || ext == ".dylib") {
                        fs::path destPath = target / entry.path().filename();
                        fs::create_directories(target);
                        fs::copy_file(entry.path(), destPath, 
                                    fs::copy_options::overwrite_existing);
                        libraryPath = destPath;
                    }
                }
            }
        }
        
        // 复制源文件（可选，用于调试）
        fs::path srcDir = moduleDir / "src";
        if (fs::exists(srcDir)) {
            fs::path destSrc = target / "src";
            fs::create_directories(destSrc);
            fs::copy(srcDir, destSrc, 
                    fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        }
        
        // 清理临时目录
        fs::remove_all(tempDir);
        
        return !libraryPath.empty();
        
    } catch (const std::exception& e) {
        fs::remove_all(tempDir);
        return false;
    }
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
    
    // 解析基本的[Info]块
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
            
            // 只使用基础的CMODInfo字段
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
    
    return info.isValid();
}

bool CJMODModule::unpackBinary(const fs::path& cjmodFile, const fs::path& targetDir) {
    std::ifstream file(cjmodFile, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // 读取头部
    char magic[6];
    file.read(magic, 6);
    if (std::string(magic, 6) != "CJMOD\n") {
        return false;
    }
    
    // 读取文件数量
    uint32_t fileCount;
    file.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));
    
    // 读取每个文件
    for (uint32_t i = 0; i < fileCount; ++i) {
        // 读取文件名长度
        uint32_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        
        // 读取文件名
        std::string filename(nameLength, '\0');
        file.read(&filename[0], nameLength);
        
        // 读取文件大小
        uint64_t fileSize;
        file.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
        
        // 读取文件内容
        std::vector<char> content(fileSize);
        file.read(content.data(), fileSize);
        
        // 创建目标文件
        fs::path targetFile = targetDir / filename;
        fs::create_directories(targetFile.parent_path());
        
        std::ofstream out(targetFile, std::ios::binary);
        out.write(content.data(), fileSize);
        out.close();
        
        // 如果是共享库，记录路径
        auto ext = targetFile.extension();
        if (ext == ".so" || ext == ".dll" || ext == ".dylib") {
            libraryPath = targetFile;
        }
    }
    
    file.close();
    return true;
}

bool CJMODModule::compileSources() {
    // 创建临时构建目录
    fs::path buildDir = rootPath / "build";
    fs::create_directories(buildDir);
    
    // 生成编译命令
    std::stringstream cmd;
    cmd << "g++ -std=c++17 -fPIC -shared";
    
    // 添加CHTL头文件路径
    cmd << " -I/usr/include/chtl";
    
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
    // 简单的打包实现
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }
    
    out << "CJMOD\n";
    out << "1.0\n";
    
    // TODO: 实现完整的文件打包逻辑
    
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
    
    // 检查info文件（必须与模块名相同）
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
        infoFile << "[Info]\n";
        infoFile << "{\n";
        infoFile << "    name = \"" << moduleName << "\";\n";
        infoFile << "    version = \"1.0.0\";\n";
        infoFile << "    description = \"CJMOD extension for " << extensionType << "\";\n";
        infoFile << "    author = \"Your Name\";\n";
        infoFile << "    license = \"MIT\";\n";
        infoFile << "    category = \"extension\";\n";
        infoFile << "    minCHTLVersion = \"1.0.0\";\n";
        infoFile << "    maxCHTLVersion = \"2.0.0\";\n";
        infoFile << "}\n";
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