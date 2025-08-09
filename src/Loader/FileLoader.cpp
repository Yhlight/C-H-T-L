#include "Loader/FileLoader.h"
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Node.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <chrono>

namespace chtl {

namespace fs = std::filesystem;

FileLoader::FileLoader() {
    // 初始化解析器将在需要时进行
}

FileLoader::~FileLoader() = default;

// 加载文件
bool FileLoader::loadFile(const std::string& filePath) {
    // 检查文件是否已加载
    if (isFileLoaded(filePath)) {
        return true;
    }
    
    // 检查文件是否存在
    if (!fs::exists(filePath)) {
        FileInfo info;
        info.path = filePath;
        info.isLoaded = false;
        info.isParsed = false;
        info.error = "File not found: " + filePath;
        files_[filePath] = info;
        return false;
    }
    
    // 检查是否为CHTL文件
    if (!isValidChtlFile(filePath)) {
        FileInfo info;
        info.path = filePath;
        info.isLoaded = false;
        info.isParsed = false;
        info.error = "Not a CHTL file: " + filePath;
        files_[filePath] = info;
        return false;
    }
    
    // 检查文件大小
    if (!checkFileSize(filePath)) {
        FileInfo info;
        info.path = filePath;
        info.isLoaded = false;
        info.isParsed = false;
        info.error = "File too large: " + filePath;
        files_[filePath] = info;
        return false;
    }
    
    // 读取文件内容
    std::string content = readFile(filePath);
    if (content.empty() && fs::file_size(filePath) > 0) {
        FileInfo info;
        info.path = filePath;
        info.isLoaded = false;
        info.isParsed = false;
        info.error = "Failed to read file: " + filePath;
        files_[filePath] = info;
        return false;
    }
    
    // 创建文件信息
    FileInfo info;
    info.path = filePath;
    info.content = content;
    info.isLoaded = true;
    info.isParsed = false;
    info.dependencies = scanDependencies(content);
    
    // 记录文件修改时间
    auto ftime = fs::last_write_time(filePath);
    fileModTimes_[filePath] = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    
    files_[filePath] = info;
    return true;
}

bool FileLoader::loadFiles(const std::vector<std::string>& filePaths) {
    bool allSuccess = true;
    for (const auto& path : filePaths) {
        if (!loadFile(path)) {
            allSuccess = false;
        }
    }
    return allSuccess;
}

bool FileLoader::loadDirectory(const std::string& dirPath, bool recursive) {
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        return false;
    }
    
    std::vector<std::string> files;
    if (recursive) {
        loadDirectoryRecursive(dirPath, files);
    } else {
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            if (entry.is_regular_file() && isValidChtlFile(entry.path().string())) {
                files.push_back(entry.path().string());
            }
        }
    }
    
    return loadFiles(files);
}

// 解析文件
bool FileLoader::parseFile(const std::string& filePath) {
    auto it = files_.find(filePath);
    if (it == files_.end() || !it->second.isLoaded) {
        return false;
    }
    
    auto& info = it->second;
    if (info.isParsed) {
        return true;
    }
    
    // 创建解析器组件
    auto context = std::make_shared<StandardContext>();
    auto lexer = std::make_shared<StandardLexer>();
    parser_ = std::make_unique<StandardParser>(lexer, context);
    
    // TODO: 设置lexer输入并解析
    // 暂时标记为已解析
    info.isParsed = true;
    info.ast = std::make_shared<Element>("document");
    
    return true;
}

bool FileLoader::parseAllFiles() {
    bool allSuccess = true;
    for (auto& [path, info] : files_) {
        if (info.isLoaded && !info.isParsed) {
            if (!parseFile(path)) {
                allSuccess = false;
            }
        }
    }
    return allSuccess;
}

// 获取文件信息
const FileLoader::FileInfo* FileLoader::getFileInfo(const std::string& filePath) const {
    auto it = files_.find(filePath);
    return it != files_.end() ? &it->second : nullptr;
}

std::shared_ptr<Node> FileLoader::getAST(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->ast : nullptr;
}

std::string FileLoader::getContent(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->content : "";
}

// 检查文件状态
bool FileLoader::isFileLoaded(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info && info->isLoaded;
}

bool FileLoader::isFileParsed(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info && info->isParsed;
}

bool FileLoader::hasErrors() const {
    for (const auto& [path, info] : files_) {
        if (!info.error.empty()) {
            return true;
        }
    }
    return false;
}

// 获取错误信息
std::vector<std::string> FileLoader::getErrors() const {
    std::vector<std::string> errors;
    for (const auto& [path, info] : files_) {
        if (!info.error.empty()) {
            errors.push_back(path + ": " + info.error);
        }
    }
    return errors;
}

std::string FileLoader::getFileError(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->error : "";
}

// 依赖管理
std::vector<std::string> FileLoader::getDependencies(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->dependencies : std::vector<std::string>{};
}

std::vector<std::string> FileLoader::getAllDependencies() const {
    std::vector<std::string> allDeps;
    for (const auto& [path, info] : files_) {
        allDeps.insert(allDeps.end(), info.dependencies.begin(), info.dependencies.end());
    }
    
    // 去重
    std::sort(allDeps.begin(), allDeps.end());
    allDeps.erase(std::unique(allDeps.begin(), allDeps.end()), allDeps.end());
    
    return allDeps;
}

bool FileLoader::resolveDependencies() {
    auto deps = getAllDependencies();
    bool allResolved = true;
    
    for (const auto& dep : deps) {
        if (!isFileLoaded(dep)) {
            if (!loadFile(dep)) {
                allResolved = false;
            }
        }
    }
    
    return allResolved;
}

// 文件监控
bool FileLoader::hasFileChanged(const std::string& filePath) const {
    if (!fs::exists(filePath)) {
        return false;
    }
    
    auto it = fileModTimes_.find(filePath);
    if (it == fileModTimes_.end()) {
        return false;
    }
    
    auto currentTime = fs::last_write_time(filePath);
    auto recordedTime = it->second;
    
    // TODO: 实际比较文件修改时间
    return false;
}

std::vector<std::string> FileLoader::getChangedFiles() const {
    std::vector<std::string> changed;
    for (const auto& [path, info] : files_) {
        if (hasFileChanged(path)) {
            changed.push_back(path);
        }
    }
    return changed;
}

bool FileLoader::reloadChangedFiles() {
    auto changed = getChangedFiles();
    bool allSuccess = true;
    
    for (const auto& path : changed) {
        clearFile(path);
        if (!loadFile(path)) {
            allSuccess = false;
        }
    }
    
    return allSuccess;
}

// 清理
void FileLoader::clearFile(const std::string& filePath) {
    files_.erase(filePath);
    fileModTimes_.erase(filePath);
}

void FileLoader::clearAllFiles() {
    files_.clear();
    fileModTimes_.clear();
}

// 获取统计信息
size_t FileLoader::getLoadedFileCount() const {
    size_t count = 0;
    for (const auto& [path, info] : files_) {
        if (info.isLoaded) {
            count++;
        }
    }
    return count;
}

size_t FileLoader::getParsedFileCount() const {
    size_t count = 0;
    for (const auto& [path, info] : files_) {
        if (info.isParsed) {
            count++;
        }
    }
    return count;
}

size_t FileLoader::getTotalFileSize() const {
    size_t totalSize = 0;
    for (const auto& [path, info] : files_) {
        totalSize += info.content.size();
    }
    return totalSize;
}

// 私有方法实现
std::string FileLoader::readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> FileLoader::scanDependencies(const std::string& content) {
    std::vector<std::string> deps;
    
    // 扫描[Import]语句
    std::regex importRegex(R"(\[Import\]\s*@\w+\s+from\s+([^\s;]+))");
    std::smatch match;
    std::string::const_iterator searchStart(content.cbegin());
    
    while (std::regex_search(searchStart, content.cend(), match, importRegex)) {
        std::string moduleName = match[1];
        // 将模块名转换为文件路径
        std::string filePath = moduleName + ".chtl";
        deps.push_back(filePath);
        searchStart = match.suffix().first;
    }
    
    return deps;
}

bool FileLoader::isValidChtlFile(const std::string& filePath) const {
    fs::path path(filePath);
    return path.extension() == ".chtl";
}

bool FileLoader::checkFileSize(const std::string& filePath) const {
    if (!fs::exists(filePath)) {
        return false;
    }
    
    size_t fileSize = fs::file_size(filePath);
    return fileSize <= maxFileSize_;
}

void FileLoader::loadDirectoryRecursive(const std::string& dirPath, 
                                       std::vector<std::string>& files) {
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            
            // 处理符号链接
            if (entry.is_symlink() && !followSymlinks_) {
                continue;
            }
            
            if (isValidChtlFile(path)) {
                files.push_back(path);
            }
        }
    }
}

} // namespace chtl