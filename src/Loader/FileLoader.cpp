#include "Loader/FileLoader.h"
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/ChtlContext.h"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <sstream>

namespace chtl {

namespace fs = std::filesystem;

FileLoader::FileLoader() {
    // 默认构造函数
}

FileLoader::~FileLoader() {
    // 默认析构函数
}

bool FileLoader::loadFile(const std::string& filePath) {
    // 检查文件是否已加载
    if (isFileLoaded(filePath)) {
        return true;
    }
    
    // 检查文件是否存在
    if (!fs::exists(filePath)) {
        return false;
    }
    
    // 检查是否是有效的CHTL文件
    if (!isValidChtlFile(filePath)) {
        return false;
    }
    
    // 检查文件大小
    if (!checkFileSize(filePath)) {
        return false;
    }
    
    // 读取文件内容
    std::string content = readFile(filePath);
    if (content.empty() && fs::file_size(filePath) > 0) {
        return false;
    }
    
    // 创建文件信息
    FileInfo info;
    info.path = filePath;
    info.content = content;
    info.isLoaded = true;
    info.isParsed = false;
    info.dependencies = scanDependencies(content);
    
    // 存储文件信息
    files_[filePath] = info;
    
    // 记录文件修改时间
    // auto ftime = fs::last_write_time(filePath);
    // Store the time_point directly instead of converting to time_t
    // fileModTimes_[filePath] = decltype(ftime)::clock::to_time_t(ftime);
    // For now, just mark as loaded
    fileModTimes_[filePath] = 0;
    
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

bool FileLoader::parseFile(const std::string& filePath) {
    auto it = files_.find(filePath);
    if (it == files_.end()) {
        return false;
    }
    
    FileInfo& info = it->second;
    
    // 创建解析器
    auto lexer = std::make_shared<StandardLexer>();
    auto stream = std::make_unique<std::istringstream>(info.content);
    lexer->initialize(std::move(stream), filePath);
    
    auto context = std::make_shared<ChtlContext>();
    StandardParser parser(lexer, context);
    
    try {
        info.ast = parser.parse();
        info.isParsed = true;
        
        // 收集错误
        auto errors = parser.getErrors();
        if (!errors.empty()) {
            std::stringstream ss;
            for (const auto& error : errors) {
                ss << "Line " << error.line << ": " << error.message << "\n";
            }
            info.error = ss.str();
        }
    } catch (const std::exception& e) {
        info.error = std::string("Parse error: ") + e.what();
        info.isParsed = false;
        return false;
    }
    
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

const FileLoader::FileInfo* FileLoader::getFileInfo(const std::string& filePath) const {
    auto it = files_.find(filePath);
    return (it != files_.end()) ? &it->second : nullptr;
}

std::shared_ptr<Node> FileLoader::getAST(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->ast : nullptr;
}

std::string FileLoader::getContent(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->content : "";
}

std::vector<std::string> FileLoader::getLoadedFiles() const {
    std::vector<std::string> result;
    for (const auto& [path, info] : files_) {
        if (info.isLoaded) {
            result.push_back(path);
        }
    }
    return result;
}

bool FileLoader::isFileLoaded(const std::string& filePath) const {
    auto it = files_.find(filePath);
    return (it != files_.end()) && it->second.isLoaded;
}

bool FileLoader::isFileParsed(const std::string& filePath) const {
    auto it = files_.find(filePath);
    return (it != files_.end()) && it->second.isParsed;
}

bool FileLoader::hasErrors() const {
    for (const auto& [path, info] : files_) {
        if (!info.error.empty()) {
            return true;
        }
    }
    return false;
}

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

std::vector<std::string> FileLoader::getDependencies(const std::string& filePath) const {
    auto info = getFileInfo(filePath);
    return info ? info->dependencies : std::vector<std::string>{};
}

std::vector<std::string> FileLoader::getAllDependencies() const {
    std::set<std::string> allDeps;
    for (const auto& [path, info] : files_) {
        allDeps.insert(info.dependencies.begin(), info.dependencies.end());
    }
    return std::vector<std::string>(allDeps.begin(), allDeps.end());
}

bool FileLoader::resolveDependencies() {
    // 简单实现：加载所有依赖文件
    auto deps = getAllDependencies();
    return loadFiles(deps);
}

bool FileLoader::hasFileChanged(const std::string& filePath) const {
    auto it = fileModTimes_.find(filePath);
    if (it == fileModTimes_.end()) {
        return false;
    }
    
    try {
        // auto currentTime = fs::last_write_time(filePath);
        // auto storedTime = it->second;
        // Simplified check - always consider changed for now
        // return decltype(currentTime)::clock::to_time_t(currentTime) != storedTime;
        return true;
    } catch (...) {
        return false;
    }
}

std::vector<std::string> FileLoader::getChangedFiles() const {
    std::vector<std::string> changed;
    for (const auto& [path, modTime] : fileModTimes_) {
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

void FileLoader::clearFile(const std::string& filePath) {
    files_.erase(filePath);
    fileModTimes_.erase(filePath);
}

void FileLoader::clearAllFiles() {
    files_.clear();
    fileModTimes_.clear();
}

size_t FileLoader::getLoadedFileCount() const {
    return std::count_if(files_.begin(), files_.end(),
        [](const auto& pair) { return pair.second.isLoaded; });
}

size_t FileLoader::getParsedFileCount() const {
    return std::count_if(files_.begin(), files_.end(),
        [](const auto& pair) { return pair.second.isParsed; });
}

size_t FileLoader::getTotalFileSize() const {
    size_t total = 0;
    for (const auto& [path, info] : files_) {
        total += info.content.size();
    }
    return total;
}

std::string FileLoader::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> FileLoader::scanDependencies(const std::string& content) {
    std::vector<std::string> deps;
    
    // 简单扫描Import语句
    size_t pos = 0;
    while ((pos = content.find("Import", pos)) != std::string::npos) {
        // 查找 from 后的路径
        size_t fromPos = content.find("from", pos);
        if (fromPos != std::string::npos) {
            size_t pathStart = content.find_first_of("\"'", fromPos);
            if (pathStart != std::string::npos) {
                size_t pathEnd = content.find_first_of("\"'", pathStart + 1);
                if (pathEnd != std::string::npos) {
                    std::string path = content.substr(pathStart + 1, pathEnd - pathStart - 1);
                    deps.push_back(path);
                }
            }
        }
        pos += 6; // "Import"的长度
    }
    
    return deps;
}

bool FileLoader::isValidChtlFile(const std::string& filePath) const {
    // 检查文件扩展名
    // C++17 doesn't have ends_with, use alternative
    return (filePath.size() >= 5 && filePath.substr(filePath.size() - 5) == ".chtl") ||
           (filePath.size() >= 5 && filePath.substr(filePath.size() - 5) == ".chtm") ||
           (filePath.size() >= 5 && filePath.substr(filePath.size() - 5) == ".cmod");
}

bool FileLoader::checkFileSize(const std::string& filePath) const {
    try {
        return fs::file_size(filePath) <= maxFileSize_;
    } catch (...) {
        return false;
    }
}

void FileLoader::loadDirectoryRecursive(const std::string& dirPath, 
                                       std::vector<std::string>& files) {
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            if (isValidChtlFile(path)) {
                if (!followSymlinks_ && entry.is_symlink()) {
                    continue;
                }
                files.push_back(path);
            }
        }
    }
}

} // namespace chtl