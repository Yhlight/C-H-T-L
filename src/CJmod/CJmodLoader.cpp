#include "CJmod/CJmodLoader.h"
#include "Loader/ImportResolver.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <dlfcn.h>
#include <cstdlib>

namespace chtl {
namespace cjmod {

// 编译时包含路径
#ifndef CHTL_INCLUDE_DIR
#define CHTL_INCLUDE_DIR "/workspace/include"
#endif

CJmodLoader& CJmodLoader::getInstance() {
    static CJmodLoader instance;
    return instance;
}

std::shared_ptr<ICJmod> CJmodLoader::loadModule(const std::string& path) {
    // 检查缓存
    auto it = moduleCache_.find(path);
    if (it != moduleCache_.end()) {
        return it->second;
    }
    
    std::shared_ptr<ICJmod> module;
    
    // 解析路径以检查是否为内置模块
    auto [protocol, moduleName] = parseModulePath(path);
    
    if (protocol == "builtin") {
        // 从内置模块加载
        auto builtinIt = builtinModules_.find(moduleName);
        if (builtinIt != builtinModules_.end()) {
            module = builtinIt->second;
        } else {
            std::cerr << "[CJmod] Builtin module not found: " << moduleName << std::endl;
        }
    } else {
        // 使用 ImportResolver 解析路径（与 @Chtl 相同的逻辑）
        ImportResolver resolver;
        
        // 设置官方模块路径（如果有环境变量指定）
        if (const char* compilerPath = std::getenv("CHTL_COMPILER_PATH")) {
            std::filesystem::path p(compilerPath);
            resolver.setOfficialModulePath((p.parent_path() / "module").string());
        }
        
        auto result = resolver.resolve(path, Import::ImportType::CJMOD, "");
        
        if (result.success) {
            if (result.isWildcard) {
                // 处理通配符导入（加载多个模块）
                for (const auto& filePath : result.wildcardResults) {
                    auto wildcardModule = loadFromFile(filePath);
                    if (wildcardModule) {
                        // 注册每个匹配的模块
                        CHTLJSProcessor::getInstance().registerModule(wildcardModule);
                    }
                }
                // 返回nullptr表示已处理通配符
                return nullptr;
            } else {
                module = loadFromFile(result.resolvedPath);
            }
        } else {
            std::cerr << "[CJmod] Failed to resolve module: " << result.errorMessage << std::endl;
        }
    }
    
    // 缓存模块
    if (module) {
        moduleCache_[path] = module;
        
        // 注册到处理器
        auto& processor = CHTLJSProcessor::getInstance();
        processor.registerModule(module);
    }
    
    return module;
}

void CJmodLoader::registerBuiltinModule(const std::string& name, std::shared_ptr<ICJmod> module) {
    builtinModules_[name] = module;
    std::cout << "[CJmod] Registered builtin module: " << name << std::endl;
}

void CJmodLoader::initializeBuiltins() {
    // 注册响应式模块
    class ReactiveModule : public ICJmod {
    public:
        std::string getName() const override { return "reactive"; }
        std::string getVersion() const override { return "1.0.0"; }
        
        std::vector<ScanCutRule> getScanCutRules() const override {
            return {
                // count := 0  ->  let count = reactive(0)
                {
                    "reactive-declaration",
                    std::regex(R"((\w+)\s*:=\s*([^;]+);)"),
                    "let $1 = reactive($2);",
                    100
                },
                
                // doubled => count.value * 2  ->  let doubled = computed(() => count.value * 2)
                {
                    "computed-property",
                    std::regex(R"((\w+)\s*=>\s*([^;]+);)"),
                    "let $1 = computed(() => $2);",
                    90
                },
                
                // watch count { ... }  ->  watch(count, () => { ... })
                {
                    "watch-syntax",
                    std::regex(R"(watch\s+(\w+)\s*\{)"),
                    "watch($1, () => {",
                    80
                }
            };
        }
        
        std::vector<RuntimeInjection> getRuntimeInjections() const override {
            return {
                {
                    R"(
// CJmod Reactive Runtime
window.reactive = function(initialValue) {
    let _value = initialValue;
    const subscribers = new Set();
    
    return {
        get value() { return _value; },
        set value(newValue) {
            if (_value !== newValue) {
                _value = newValue;
                subscribers.forEach(fn => fn());
            }
        },
        subscribe(fn) {
            subscribers.add(fn);
            return () => subscribers.delete(fn);
        }
    };
};

window.computed = function(computeFn) {
    let cache;
    let dirty = true;
    
    return {
        get value() {
            if (dirty) {
                cache = computeFn();
                dirty = false;
            }
            return cache;
        }
    };
};

window.watch = function(target, callback) {
    if (target && typeof target.subscribe === 'function') {
        return target.subscribe(callback);
    }
};
)",
                    "before"
                }
            };
        }
    };
    
    // 注册动画模块
    class AnimationModule : public ICJmod {
    public:
        std::string getName() const override { return "animation"; }
        std::string getVersion() const override { return "1.0.0"; }
        
        std::vector<ScanCutRule> getScanCutRules() const override {
            return {
                // element ~> fadeIn(300)  ->  element.animate().fadeIn(300)
                {
                    "animation-chain",
                    std::regex(R"(([\w\{\}#\.]+)\s*~>\s*(\w+))"),
                    "$1.animate().$2",
                    100
                },
                
                // delay(ms)
                {
                    "delay-function",
                    std::regex(R"(delay\((\d+)\))"),
                    "await new Promise(r => setTimeout(r, $1))",
                    80
                }
            };
        }
        
        std::vector<RuntimeInjection> getRuntimeInjections() const override {
            return {
                {
                    R"(
// CJmod Animation Runtime
Element.prototype.animate = function() {
    const el = this;
    const queue = [];
    
    const animator = {
        fadeIn(duration = 300) {
            queue.push(() => {
                el.style.transition = `opacity ${duration}ms`;
                el.style.opacity = '0';
                el.style.display = 'block';
                setTimeout(() => el.style.opacity = '1', 10);
                return new Promise(r => setTimeout(r, duration));
            });
            return this;
        },
        
        fadeOut(duration = 300) {
            queue.push(() => {
                el.style.transition = `opacity ${duration}ms`;
                el.style.opacity = '0';
                return new Promise(r => setTimeout(() => {
                    el.style.display = 'none';
                    r();
                }, duration));
            });
            return this;
        },
        
        async run() {
            for (const fn of queue) {
                await fn();
            }
        }
    };
    
    setTimeout(() => animator.run(), 0);
    return animator;
};
)",
                    "before"
                }
            };
        }
    };
    
    registerBuiltinModule("reactive", std::make_shared<ReactiveModule>());
    registerBuiltinModule("animation", std::make_shared<AnimationModule>());
    
    // 注册异步流控制模块
    class AsyncFlowModule : public ICJmod {
    public:
        std::string getName() const override { return "async-flow"; }
        std::string getVersion() const override { return "2.0.0"; }
        
        std::vector<ScanCutRule> getScanCutRules() const override {
            return {
                // stream 语法
                {
                    "async-stream",
                    std::regex(R"(stream\s+(\w+)\s+from\s+(\w+)\s*\{)"),
                    "async function* $1() { const _source = $2; try {",
                    150
                },
                // concurrent 语法
                {
                    "concurrent-block",
                    std::regex(R"(concurrent\s*\((\d+)\)\s*\{)"),
                    "await concurrent($1, async () => {",
                    130
                },
                // retry 语法
                {
                    "retry-block",
                    std::regex(R"(retry\s*\((\d+),\s*(\d+)\)\s*\{)"),
                    "await retry($1, $2, async () => {",
                    120
                },
                // try* 语法
                {
                    "try-star",
                    std::regex(R"(try\*\s*\{)"),
                    "await tryAsync(async () => {",
                    100
                },
                // 特殊块结束
                {
                    "special-block-end",
                    std::regex(R"(\}\s*//\s*(stream|concurrent|retry|try\*)\s*end)"),
                    "})",
                    40
                }
            };
        }
        
        std::vector<RuntimeInjection> getRuntimeInjections() const override {
            return {
                {
                    R"(
// Async Flow Runtime (Simplified)
window.concurrent = async (limit, fn) => {
    // 简化版并发控制
    return fn();
};

window.retry = async (times, delay, fn) => {
    let lastError;
    for (let i = 0; i < times; i++) {
        try {
            return await fn();
        } catch (e) {
            lastError = e;
            if (i < times - 1) await new Promise(r => setTimeout(r, delay));
        }
    }
    throw lastError;
};

window.tryAsync = async (fn) => {
    try {
        return await fn();
    } catch (e) {
        console.error('[AsyncFlow]', e);
        return { error: e };
    }
};
)",
                    "before"
                }
            };
        }
    };
    
    registerBuiltinModule("async-flow", std::make_shared<AsyncFlowModule>());
}

std::pair<std::string, std::string> CJmodLoader::parseModulePath(const std::string& path) {
    size_t colonPos = path.find(':');
    if (colonPos != std::string::npos) {
        std::string protocol = path.substr(0, colonPos);
        std::string moduleName = path.substr(colonPos + 1);
        
        // 去除版本号
        size_t atPos = moduleName.find('@');
        if (atPos != std::string::npos) {
            moduleName = moduleName.substr(0, atPos);
        }
        
        return {protocol, moduleName};
    }
    
    return {"file", path};
}

std::shared_ptr<ICJmod> CJmodLoader::loadFromFile(const std::string& filePath) {
    // 检查文件是否存在
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "[CJmod] File not found: " << filePath << std::endl;
        return nullptr;
    }
    
    // 读取文件内容
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[CJmod] Cannot open file: " << filePath << std::endl;
        return nullptr;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)), 
                       std::istreambuf_iterator<char>());
    file.close();
    
    // 检查文件扩展名
    if (filePath.ends_with(".cjmod")) {
        // .cjmod 是压缩包格式，需要解压
        return loadFromPackage(filePath);
    } else if (filePath.ends_with(".json")) {
        // 直接的 JSON 文件
        return loadFromJSON(content);
    }
    
    std::cerr << "[CJmod] Unknown file format: " << filePath << std::endl;
    return nullptr;
}

std::shared_ptr<ICJmod> CJmodLoader::loadFromPackage(const std::string& packagePath) {
    // .cjmod 是一个压缩包，包含以下结构：
    // CJmod文件夹/
    //   src/      - C++ 源文件和头文件
    //   info/     - 模块信息文件（.chtl格式）
    
    try {
        // 创建临时目录
        std::filesystem::path tempDir = std::filesystem::temp_directory_path() / "cjmod_temp";
        std::filesystem::create_directories(tempDir);
        
        // 解压文件
        std::string unzipCmd = "unzip -q -o \"" + packagePath + "\" -d \"" + tempDir.string() + "\"";
        int result = std::system(unzipCmd.c_str());
        
        if (result != 0) {
            std::cerr << "[CJmod] Failed to extract package: " << packagePath << std::endl;
            return nullptr;
        }
        
        // 查找 CJmod 根目录（通常是第一个目录）
        std::filesystem::path cjmodRoot;
        for (const auto& entry : std::filesystem::directory_iterator(tempDir)) {
            if (entry.is_directory()) {
                cjmodRoot = entry.path();
                break;
            }
        }
        
        if (cjmodRoot.empty()) {
            std::cerr << "[CJmod] No CJmod directory found in package" << std::endl;
            std::filesystem::remove_all(tempDir);
            return nullptr;
        }
        
        // 获取模块名称（目录名）
        std::string moduleName = cjmodRoot.filename().string();
        
        // 查找 info 目录中的 .chtl 文件
        std::filesystem::path infoDir = cjmodRoot / "info";
        std::filesystem::path infoChtl = infoDir / (moduleName + ".chtl");
        
        if (!std::filesystem::exists(infoChtl)) {
            std::cerr << "[CJmod] Info file not found: " << infoChtl << std::endl;
            std::filesystem::remove_all(tempDir);
            return nullptr;
        }
        
        // 读取并解析 .chtl 文件以获取模块信息
        std::ifstream infoFile(infoChtl);
        std::string infoContent((std::istreambuf_iterator<char>(infoFile)),
                               std::istreambuf_iterator<char>());
        infoFile.close();
        
        // 查找 src 目录中的 C++ 文件
        std::filesystem::path srcDir = cjmodRoot / "src";
        std::vector<std::string> cppFiles;
        std::vector<std::string> headerFiles;
        
        if (std::filesystem::exists(srcDir)) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(srcDir)) {
                if (entry.is_regular_file()) {
                    std::string ext = entry.path().extension().string();
                    if (ext == ".cpp" || ext == ".cc" || ext == ".cxx") {
                        cppFiles.push_back(entry.path().string());
                    } else if (ext == ".h" || ext == ".hpp" || ext == ".hxx") {
                        headerFiles.push_back(entry.path().string());
                    }
                }
            }
        }
        
        // 编译 C++ 文件为动态库
        if (!cppFiles.empty()) {
            std::string compileCmd = "g++ -shared -fPIC -std=c++17";
            
            // 添加包含路径
            compileCmd += " -I\"" + srcDir.string() + "\"";
            compileCmd += " -I\"" + std::string(CHTL_INCLUDE_DIR) + "\"";
            
            // 添加源文件
            for (const auto& cpp : cppFiles) {
                compileCmd += " \"" + cpp + "\"";
            }
            
            // 输出动态库
            std::filesystem::path outputLib = tempDir / (moduleName + ".so");
            compileCmd += " -o \"" + outputLib.string() + "\"";
            
            std::cout << "[CJmod] Compiling module: " << moduleName << std::endl;
            result = std::system(compileCmd.c_str());
            
            if (result == 0) {
                // 加载动态库
                void* handle = dlopen(outputLib.c_str(), RTLD_LAZY);
                if (handle) {
                    // 查找创建函数
                    typedef std::shared_ptr<ICJmod> (*CreateFunc)();
                    CreateFunc createModule = (CreateFunc)dlsym(handle, ("create" + moduleName + "Module").c_str());
                    
                    if (createModule) {
                        auto module = createModule();
                        
                        // 清理临时目录
                        std::filesystem::remove_all(tempDir);
                        
                        return module;
                    } else {
                        std::cerr << "[CJmod] Module creation function not found" << std::endl;
                    }
                } else {
                    std::cerr << "[CJmod] Failed to load dynamic library: " << dlerror() << std::endl;
                }
            } else {
                std::cerr << "[CJmod] Compilation failed" << std::endl;
            }
        } else {
            std::cerr << "[CJmod] No C++ source files found in src/ directory" << std::endl;
        }
        
        // 清理临时目录
        std::filesystem::remove_all(tempDir);
        
        return nullptr;
        
    } catch (const std::exception& e) {
        std::cerr << "[CJmod] Error loading package: " << e.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<ICJmod> CJmodLoader::loadFromJSON(const std::string& jsonContent) {
    // 简单的 JSON 解析实现
    // 注意：这是一个简化版本，实际项目中应该使用成熟的 JSON 库如 nlohmann/json
    
    class JSONCJmod : public ICJmod {
    public:
        std::string name_;
        std::string version_;
        std::vector<ScanCutRule> rules_;
        std::vector<RuntimeInjection> injections_;
        std::map<std::string, std::string> overrides_;
        
        std::string getName() const override { return name_; }
        std::string getVersion() const override { return version_; }
        std::vector<ScanCutRule> getScanCutRules() const override { return rules_; }
        std::vector<RuntimeInjection> getRuntimeInjections() const override { return injections_; }
        std::map<std::string, std::string> getOverrides() const override { return overrides_; }
    };
    
    auto module = std::make_shared<JSONCJmod>();
    
    try {
        // 简单的 JSON 解析
        // 提取 name
        size_t namePos = jsonContent.find("\"name\"");
        if (namePos != std::string::npos) {
            size_t colonPos = jsonContent.find(":", namePos);
            size_t startQuote = jsonContent.find("\"", colonPos);
            size_t endQuote = jsonContent.find("\"", startQuote + 1);
            module->name_ = jsonContent.substr(startQuote + 1, endQuote - startQuote - 1);
        }
        
        // 提取 version
        size_t versionPos = jsonContent.find("\"version\"");
        if (versionPos != std::string::npos) {
            size_t colonPos = jsonContent.find(":", versionPos);
            size_t startQuote = jsonContent.find("\"", colonPos);
            size_t endQuote = jsonContent.find("\"", startQuote + 1);
            module->version_ = jsonContent.substr(startQuote + 1, endQuote - startQuote - 1);
        }
        
        // 解析规则
        size_t rulesPos = jsonContent.find("\"rules\"");
        if (rulesPos != std::string::npos) {
            size_t arrayStart = jsonContent.find("[", rulesPos);
            size_t arrayEnd = findMatchingBracket(jsonContent, arrayStart, '[', ']');
            
            size_t ruleStart = arrayStart + 1;
            while (ruleStart < arrayEnd) {
                size_t ruleObjStart = jsonContent.find("{", ruleStart);
                if (ruleObjStart >= arrayEnd) break;
                
                size_t ruleObjEnd = findMatchingBracket(jsonContent, ruleObjStart, '{', '}');
                std::string ruleJson = jsonContent.substr(ruleObjStart, ruleObjEnd - ruleObjStart + 1);
                
                ScanCutRule rule;
                
                // 提取规则属性
                size_t pos;
                
                // name
                pos = ruleJson.find("\"name\"");
                if (pos != std::string::npos) {
                    size_t colonPos = ruleJson.find(":", pos);
                    size_t startQuote = ruleJson.find("\"", colonPos);
                    size_t endQuote = ruleJson.find("\"", startQuote + 1);
                    rule.name = ruleJson.substr(startQuote + 1, endQuote - startQuote - 1);
                }
                
                // pattern
                pos = ruleJson.find("\"pattern\"");
                if (pos != std::string::npos) {
                    size_t colonPos = ruleJson.find(":", pos);
                    size_t startQuote = ruleJson.find("\"", colonPos);
                    size_t endQuote = ruleJson.find("\"", startQuote + 1);
                    std::string pattern = ruleJson.substr(startQuote + 1, endQuote - startQuote - 1);
                    rule.pattern = std::regex(pattern);
                }
                
                // replacement
                pos = ruleJson.find("\"replacement\"");
                if (pos != std::string::npos) {
                    size_t colonPos = ruleJson.find(":", pos);
                    size_t startQuote = ruleJson.find("\"", colonPos);
                    size_t endQuote = ruleJson.find("\"", startQuote + 1);
                    rule.replacement = ruleJson.substr(startQuote + 1, endQuote - startQuote - 1);
                }
                
                // priority
                pos = ruleJson.find("\"priority\"");
                if (pos != std::string::npos) {
                    size_t colonPos = ruleJson.find(":", pos);
                    size_t numStart = colonPos + 1;
                    while (numStart < ruleJson.length() && std::isspace(ruleJson[numStart])) numStart++;
                    size_t numEnd = numStart;
                    while (numEnd < ruleJson.length() && std::isdigit(ruleJson[numEnd])) numEnd++;
                    rule.priority = std::stoi(ruleJson.substr(numStart, numEnd - numStart));
                }
                
                module->rules_.push_back(rule);
                
                ruleStart = ruleObjEnd + 1;
            }
        }
        
        // 解析 runtime
        size_t runtimePos = jsonContent.find("\"runtime\"");
        if (runtimePos != std::string::npos) {
            size_t objStart = jsonContent.find("{", runtimePos);
            size_t objEnd = findMatchingBracket(jsonContent, objStart, '{', '}');
            std::string runtimeJson = jsonContent.substr(objStart, objEnd - objStart + 1);
            
            // before
            size_t beforePos = runtimeJson.find("\"before\"");
            if (beforePos != std::string::npos) {
                size_t colonPos = runtimeJson.find(":", beforePos);
                size_t startQuote = runtimeJson.find("\"", colonPos);
                size_t endQuote = findLastQuote(runtimeJson, startQuote + 1);
                std::string code = runtimeJson.substr(startQuote + 1, endQuote - startQuote - 1);
                
                // 处理转义字符
                code = unescapeString(code);
                
                module->injections_.push_back({code, "before"});
            }
        }
        
        std::cout << "[CJmod] Loaded module from JSON: " << module->name_ << " v" << module->version_ << std::endl;
        std::cout << "[CJmod] Rules: " << module->rules_.size() << std::endl;
        
        return module;
        
    } catch (const std::exception& e) {
        std::cerr << "[CJmod] Failed to parse JSON: " << e.what() << std::endl;
        return nullptr;
    }
}

// 辅助函数：查找匹配的括号
size_t CJmodLoader::findMatchingBracket(const std::string& str, size_t start, char open, char close) {
    int depth = 1;
    for (size_t i = start + 1; i < str.length(); i++) {
        if (str[i] == open) depth++;
        else if (str[i] == close) depth--;
        if (depth == 0) return i;
    }
    return std::string::npos;
}

// 辅助函数：查找字符串的结束引号（考虑转义）
size_t CJmodLoader::findLastQuote(const std::string& str, size_t start) {
    for (size_t i = start; i < str.length(); i++) {
        if (str[i] == '"' && (i == 0 || str[i-1] != '\\')) {
            return i;
        }
    }
    return std::string::npos;
}

// 辅助函数：处理转义字符
std::string CJmodLoader::unescapeString(const std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '\\' && i + 1 < str.length()) {
            switch (str[i + 1]) {
                case 'n': result += '\n'; i++; break;
                case 't': result += '\t'; i++; break;
                case 'r': result += '\r'; i++; break;
                case '"': result += '"'; i++; break;
                case '\\': result += '\\'; i++; break;
                default: result += str[i]; break;
            }
        } else {
            result += str[i];
        }
    }
    return result;
}

// 辅助函数：转义字符串用于 JSON
std::string CJmodLoader::escapeString(const std::string& str) {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '\n': result += "\\n"; break;
            case '\t': result += "\\t"; break;
            case '\r': result += "\\r"; break;
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            default: result += c; break;
        }
    }
    return result;
}

} // namespace cjmod
} // namespace chtl