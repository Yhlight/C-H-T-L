#include "CHTLModuleBundler.h"
#include "CHTLJSOptimizer.h"
#include "CHTLContext.h"
#include "scanner/ScannerParserIntegration.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <queue>
#include <chrono>
#include <iostream>

namespace chtl {

// DependencyResolver 实现

DependencyResolver::DependencyResolver(const BundleOptions& options) : options(options) {}

std::vector<std::string> DependencyResolver::resolveDependencies(const ModuleInfo& module) {
    switch (module.type) {
        case ModuleType::CHTL:
            return extractCHTLImports(module.content);
        case ModuleType::JavaScript:
            return extractJSImports(module.content);
        case ModuleType::CSS:
            return extractCSSImports(module.content);
        default:
            return {};
    }
}

fs::path DependencyResolver::resolveModulePath(const std::string& request, const fs::path& from) {
    // 处理别名
    for (const auto& [alias, replacement] : options.alias) {
        if (request.find(alias) == 0) {
            std::string newRequest = replacement + request.substr(alias.length());
            return resolveModulePath(newRequest, from);
        }
    }
    
    // 绝对路径
    if (request[0] == '/') {
        return resolveAsFile(request);
    }
    
    // 相对路径
    if (request.find("./") == 0 || request.find("../") == 0) {
        fs::path basePath = from.parent_path();
        fs::path resolved = basePath / request;
        return resolveAsFile(resolved);
    }
    
    // 模块路径
    return resolveNodeModules(request, from);
}

fs::path DependencyResolver::resolveAsFile(const fs::path& path) {
    // 尝试直接路径
    if (fs::exists(path)) {
        return fs::canonical(path);
    }
    
    // 尝试添加扩展名
    static const std::vector<std::string> extensions = {".chtl", ".js", ".css", ".json"};
    for (const auto& ext : extensions) {
        fs::path withExt = path.string() + ext;
        if (fs::exists(withExt)) {
            return fs::canonical(withExt);
        }
    }
    
    return {};
}

fs::path DependencyResolver::resolveAsDirectory(const fs::path& path) {
    if (!fs::is_directory(path)) {
        return {};
    }
    
    // 查找 index 文件
    static const std::vector<std::string> indexFiles = {
        "index.chtl", "index.js", "index.css"
    };
    
    for (const auto& indexFile : indexFiles) {
        fs::path indexPath = path / indexFile;
        if (fs::exists(indexPath)) {
            return fs::canonical(indexPath);
        }
    }
    
    return {};
}

fs::path DependencyResolver::resolveNodeModules(const std::string& request, const fs::path& from) {
    fs::path current = from.parent_path();
    
    while (!current.empty()) {
        // 检查配置的模块路径
        for (const auto& modulePath : options.modulePaths) {
            fs::path fullPath = current / modulePath / request;
            
            // 尝试作为文件
            auto resolved = resolveAsFile(fullPath);
            if (!resolved.empty()) {
                return resolved;
            }
            
            // 尝试作为目录
            resolved = resolveAsDirectory(fullPath);
            if (!resolved.empty()) {
                return resolved;
            }
        }
        
        // 检查 node_modules
        fs::path nodeModules = current / "node_modules" / request;
        
        auto resolved = resolveAsFile(nodeModules);
        if (!resolved.empty()) {
            return resolved;
        }
        
        resolved = resolveAsDirectory(nodeModules);
        if (!resolved.empty()) {
            return resolved;
        }
        
        // 向上一级
        if (current.has_parent_path()) {
            current = current.parent_path();
        } else {
            break;
        }
    }
    
    return {};
}

std::vector<std::string> DependencyResolver::extractCHTLImports(const std::string& content) {
    std::vector<std::string> imports;
    
    // [Import] 语法
    std::regex importRegex(R"(\[Import\]\s*@\w+\s+(\S+))");
    auto begin = std::sregex_iterator(content.begin(), content.end(), importRegex);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        imports.push_back((*it)[1]);
    }
    
    return imports;
}

std::vector<std::string> DependencyResolver::extractJSImports(const std::string& content) {
    std::vector<std::string> imports;
    
    // ES6 import
    std::regex es6ImportRegex(R"(import\s+(?:.*\s+from\s+)?['"](.*?)['"])");
    auto begin = std::sregex_iterator(content.begin(), content.end(), es6ImportRegex);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        imports.push_back((*it)[1]);
    }
    
    // CommonJS require
    std::regex requireRegex(R"(require\s*\(\s*['"](.*?)['"]\s*\))");
    begin = std::sregex_iterator(content.begin(), content.end(), requireRegex);
    
    for (auto it = begin; it != end; ++it) {
        imports.push_back((*it)[1]);
    }
    
    return imports;
}

std::vector<std::string> DependencyResolver::extractCSSImports(const std::string& content) {
    std::vector<std::string> imports;
    
    // @import
    std::regex importRegex(R"(@import\s+(?:url\s*\(\s*)?['"](.*?)['"])");
    auto begin = std::sregex_iterator(content.begin(), content.end(), importRegex);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        imports.push_back((*it)[1]);
    }
    
    return imports;
}

// ModuleBundler 实现

ModuleBundler::ModuleBundler(const BundleOptions& options) 
    : options(options), resolver(std::make_unique<DependencyResolver>(options)) {
    
    // 注册内置转换器
    addTransform(ModuleType::CHTL, BuiltinTransforms::transformCHTL);
    addTransform(ModuleType::JavaScript, BuiltinTransforms::optimizeJS);
    addTransform(ModuleType::CSS, BuiltinTransforms::processCSS);
    addTransform(ModuleType::Asset, BuiltinTransforms::processAsset);
}

BundleResult ModuleBundler::bundle() {
    auto startTime = std::chrono::steady_clock::now();
    BundleResult result;
    result.success = true;
    
    try {
        reportProgress("Loading entry points...", 0.1);
        loadEntryPoints();
        
        reportProgress("Resolving dependencies...", 0.3);
        resolveAllDependencies();
        
        reportProgress("Sorting modules...", 0.4);
        performTopologicalSort();
        
        reportProgress("Applying transforms...", 0.5);
        applyTransforms();
        
        // 优化
        if (options.treeShaking) {
            reportProgress("Tree shaking...", 0.6);
            performTreeShaking();
        }
        
        if (options.scopeHoisting) {
            reportProgress("Scope hoisting...", 0.7);
            performScopeHoisting();
        }
        
        if (options.codeSpitting) {
            reportProgress("Code splitting...", 0.8);
            performCodeSplitting();
        }
        
        reportProgress("Generating output...", 0.9);
        generateOutput();
        
        // 统计信息
        result.stats.totalModules = modules.size();
        result.stats.totalSize = 0;
        result.stats.outputSize = 0;
        
        for (const auto& [id, module] : modules) {
            result.stats.totalSize += module->content.size();
            result.stats.modulesByType[module->type]++;
        }
        
        // 计算输出大小（简化：使用所有模块的转换后大小）
        for (const auto& [id, module] : modules) {
            if (!module->isExternal) {
                result.stats.outputSize += module->content.size();
            }
        }
        
        auto endTime = std::chrono::steady_clock::now();
        result.stats.buildTime = std::chrono::duration<double>(endTime - startTime).count();
        
        reportProgress("Bundle complete!", 1.0);
        
    } catch (const std::exception& e) {
        result.success = false;
        result.errorMessage = e.what();
    }
    
    return result;
}

void ModuleBundler::addTransform(ModuleType type, TransformFunction transform) {
    transforms[type].push_back(transform);
}

void ModuleBundler::setProgressCallback(ProgressCallback callback) {
    progressCallback = callback;
}

void ModuleBundler::loadEntryPoints() {
    for (const auto& entry : options.entryPoints) {
        if (!fs::exists(entry)) {
            throw std::runtime_error("Entry point not found: " + entry.string());
        }
        loadModule(entry, true);
    }
}

void ModuleBundler::loadModule(const fs::path& path, bool isEntry) {
    std::string moduleId = generateModuleId(path);
    
    // 检查是否已处理
    if (modules.find(moduleId) != modules.end()) {
        return;
    }
    
    // 检查是否是外部模块
    bool isExternal = false;
    for (const auto& external : options.externals) {
        if (moduleId.find(external) != std::string::npos) {
            isExternal = true;
            break;
        }
    }
    
    auto module = std::make_unique<ModuleInfo>();
    module->id = moduleId;
    module->absolutePath = fs::canonical(path);
    module->relativePath = fs::relative(path);
    module->type = detectModuleType(path);
    module->isEntry = isEntry;
    module->isExternal = isExternal;
    
    if (!isExternal) {
        module->content = readModuleContent(path);
    }
    
    modules[moduleId] = std::move(module);
}

void ModuleBundler::resolveAllDependencies() {
    std::queue<std::string> toProcess;
    
    // 从入口模块开始
    for (const auto& [id, module] : modules) {
        if (module->isEntry) {
            toProcess.push(id);
        }
    }
    
    while (!toProcess.empty()) {
        std::string currentId = toProcess.front();
        toProcess.pop();
        
        if (processedModules.find(currentId) != processedModules.end()) {
            continue;
        }
        
        processedModules.insert(currentId);
        
        auto& module = modules[currentId];
        if (module->isExternal) {
            continue;
        }
        
        // 解析依赖
        auto deps = resolver->resolveDependencies(*module);
        
        for (const auto& dep : deps) {
            fs::path resolvedPath = resolver->resolveModulePath(dep, module->absolutePath);
            
            if (resolvedPath.empty()) {
                std::cerr << "Warning: Cannot resolve dependency '" << dep 
                         << "' from " << module->id << std::endl;
                continue;
            }
            
            std::string depId = generateModuleId(resolvedPath);
            module->dependencies.push_back(depId);
            
            // 加载依赖模块
            if (modules.find(depId) == modules.end()) {
                loadModule(resolvedPath, false);
                toProcess.push(depId);
            }
        }
    }
}

void ModuleBundler::performTopologicalSort() {
    // 构建依赖图
    std::unordered_map<std::string, std::unordered_set<std::string>> graph;
    std::unordered_map<std::string, int> inDegree;
    
    for (const auto& [id, module] : modules) {
        if (module->isExternal) continue;
        
        inDegree[id] = 0;
        graph[id] = std::unordered_set<std::string>();
    }
    
    for (const auto& [id, module] : modules) {
        if (module->isExternal) continue;
        
        for (const auto& dep : module->dependencies) {
            if (modules[dep]->isExternal) continue;
            
            graph[dep].insert(id);
            inDegree[id]++;
        }
    }
    
    // 拓扑排序
    std::queue<std::string> queue;
    
    for (const auto& [id, degree] : inDegree) {
        if (degree == 0) {
            queue.push(id);
        }
    }
    
    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        
        moduleOrder.push_back(current);
        
        for (const auto& neighbor : graph[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                queue.push(neighbor);
            }
        }
    }
    
    // 检查循环依赖
    if (moduleOrder.size() != inDegree.size()) {
        throw std::runtime_error("Circular dependency detected");
    }
}

void ModuleBundler::applyTransforms() {
    for (const auto& moduleId : moduleOrder) {
        auto& module = modules[moduleId];
        module->content = transformModule(*module);
    }
}

void ModuleBundler::generateOutput() {
    switch (options.format) {
        case BundleOptions::SingleFile: {
            BundleResult::OutputFile file;
            file.path = options.outputPath / options.outputName;
            file.content = generateSingleFileOutput();
            
            // 写入文件
            fs::create_directories(file.path.parent_path());
            std::ofstream out(file.path);
            out << file.content;
            out.close();
            
            break;
        }
        
        case BundleOptions::MultiFile: {
            auto files = generateMultiFileOutput();
            for (auto& file : files) {
                fs::create_directories(file.path.parent_path());
                std::ofstream out(file.path);
                out << file.content;
                out.close();
                
            }
            break;
        }
        
        default:
            throw std::runtime_error("Unsupported output format");
    }
}

ModuleType ModuleBundler::detectModuleType(const fs::path& path) {
    std::string ext = path.extension().string();
    
    if (ext == ".chtl") return ModuleType::CHTL;
    if (ext == ".js" || ext == ".mjs") return ModuleType::JavaScript;
    if (ext == ".css") return ModuleType::CSS;
    
    // 检查是否是资源文件
    static const std::unordered_set<std::string> assetExts = {
        ".png", ".jpg", ".jpeg", ".gif", ".svg", ".webp",
        ".woff", ".woff2", ".ttf", ".eot",
        ".mp3", ".mp4", ".webm"
    };
    
    if (assetExts.find(ext) != assetExts.end()) {
        return ModuleType::Asset;
    }
    
    return ModuleType::Unknown;
}

std::string ModuleBundler::readModuleContent(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot read file: " + path.string());
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string ModuleBundler::transformModule(const ModuleInfo& module) {
    std::string content = module.content;
    
    // 应用该类型的所有转换
    auto it = transforms.find(module.type);
    if (it != transforms.end()) {
        for (const auto& transform : it->second) {
            content = transform(module, content);
        }
    }
    
    return content;
}

std::string ModuleBundler::generateSingleFileOutput() {
    std::stringstream output;
    
    // 生成运行时
    output << "(function() {\n";
    output << "  'use strict';\n\n";
    
    // 模块系统
    output << "  const __modules = {};\n";
    output << "  const __cache = {};\n\n";
    
    output << "  function __require(id) {\n";
    output << "    if (__cache[id]) return __cache[id].exports;\n";
    output << "    const module = __cache[id] = { exports: {} };\n";
    output << "    __modules[id].call(module.exports, module, module.exports, __require);\n";
    output << "    return module.exports;\n";
    output << "  }\n\n";
    
    // 添加所有模块
    for (const auto& moduleId : moduleOrder) {
        const auto& module = modules[moduleId];
        if (module->isExternal) continue;
        
        output << "  __modules['" << moduleId << "'] = function(module, exports, require) {\n";
        output << wrapModule(*module, module->content);
        output << "  };\n\n";
    }
    
    // 执行入口模块
    for (const auto& [id, module] : modules) {
        if (module->isEntry) {
            output << "  __require('" << id << "');\n";
        }
    }
    
    output << "})();\n";
    
    return output.str();
}

std::vector<BundleResult::OutputFile> ModuleBundler::generateMultiFileOutput() {
    std::vector<BundleResult::OutputFile> files;
    
    // 按类型分组
    std::unordered_map<ModuleType, std::stringstream> typeOutputs;
    
    for (const auto& moduleId : moduleOrder) {
        const auto& module = modules[moduleId];
        if (module->isExternal) continue;
        
        typeOutputs[module->type] << module->content << "\n\n";
    }
    
    // 生成文件
    for (const auto& [type, stream] : typeOutputs) {
        BundleResult::OutputFile file;
        
        switch (type) {
            case ModuleType::JavaScript:
                file.path = options.outputPath / (options.outputName + ".js");
                break;
            case ModuleType::CSS:
                file.path = options.outputPath / (options.outputName + ".css");
                break;
            default:
                continue;
        }
        
        file.content = stream.str();
        files.push_back(file);
    }
    
    return files;
}

std::string ModuleBundler::wrapModule(const ModuleInfo& module, const std::string& content) {
    std::stringstream wrapped;
    
    // 添加模块元信息注释
    wrapped << "    // Module: " << module.id << "\n";
    
    // 包装内容
    switch (module.type) {
        case ModuleType::JavaScript:
            // JS模块直接使用
            wrapped << "    " << content << "\n";
            break;
            
        case ModuleType::CSS:
            // CSS作为字符串导出
            wrapped << "    const css = `" << content << "`;\n";
            wrapped << "    const style = document.createElement('style');\n";
            wrapped << "    style.textContent = css;\n";
            wrapped << "    document.head.appendChild(style);\n";
            wrapped << "    module.exports = css;\n";
            break;
            
        case ModuleType::CHTL:
            // CHTL已经被转换为HTML/CSS/JS
            wrapped << "    " << content << "\n";
            break;
            
        default:
            wrapped << "    module.exports = null;\n";
    }
    
    return wrapped.str();
}

void ModuleBundler::performTreeShaking() {
    // 简化实现：标记未使用的导出
    // 实际实现需要AST分析
    reportProgress("Analyzing unused exports...", 0.65);
}

void ModuleBundler::performScopeHoisting() {
    // 简化实现：合并模块作用域
    // 实际实现需要AST转换
    reportProgress("Merging module scopes...", 0.75);
}

void ModuleBundler::performCodeSplitting() {
    // 简化实现：基于大小分割
    // 实际实现需要动态导入分析
    reportProgress("Splitting code chunks...", 0.85);
}

void ModuleBundler::reportProgress(const std::string& message, double progress) {
    if (progressCallback) {
        progressCallback(message, progress);
    }
}

std::string ModuleBundler::generateModuleId(const fs::path& path) {
    // 使用相对路径作为模块ID
    fs::path relative = fs::relative(path);
    return relative.string();
}

// BuiltinTransforms 实现

std::string BuiltinTransforms::transformCHTL(const ModuleInfo& module, const std::string& content) {
    // 使用CHTL编译器编译
    auto context = std::make_shared<CHTLContext>();
    scanner::ScannerParserIntegration integration(context);
    
    auto parseResult = integration.parse(content);
    if (!parseResult.success) {
        throw std::runtime_error("CHTL compilation failed: " + parseResult.errorMessage);
    }
    
    // 生成输出
    std::stringstream output;
    
    // TODO: 使用CHTLTreeVisitor生成代码
    output << "// Compiled from " << module.id << "\n";
    output << "// CHTL compilation output placeholder\n";
    
    return output.str();
}

std::string BuiltinTransforms::optimizeJS(const ModuleInfo& module, const std::string& content) {
    JSOptimizationOptions options;
    options.minifyCode = true;
    options.removeComments = true;
    options.renameVariables = true;
    
    JSOptimizer optimizer(options);
    return optimizer.optimize(content);
}

std::string BuiltinTransforms::processCSS(const ModuleInfo& module, const std::string& content) {
    // 简单的CSS处理
    std::string processed = content;
    
    // 移除注释
    std::regex commentRegex(R"(/\*[\s\S]*?\*/)");
    processed = std::regex_replace(processed, commentRegex, "");
    
    // 压缩空白
    std::regex whitespaceRegex(R"(\s+)");
    processed = std::regex_replace(processed, whitespaceRegex, " ");
    
    // 移除不必要的分号和空格
    std::regex cleanupRegex(R"(\s*([{}:;,])\s*)");
    processed = std::regex_replace(processed, cleanupRegex, "$1");
    
    return processed;
}

std::string BuiltinTransforms::processAsset(const ModuleInfo& module, const std::string& content) {
    // 资源文件处理（base64编码等）
    // 简化实现：返回资源URL
    return "module.exports = '" + module.relativePath.string() + "';";
}

} // namespace chtl