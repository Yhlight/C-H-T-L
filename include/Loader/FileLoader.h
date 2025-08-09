#ifndef CHTL_FILE_LOADER_H
#define CHTL_FILE_LOADER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <ctime>

namespace chtl {

// 前向声明
class BasicParser;
class Node;

// 文件加载器 - 负责加载和管理CHTL文件
class FileLoader {
public:
    // 文件信息
    struct FileInfo {
        std::string path;
        std::string content;
        std::shared_ptr<Node> ast;
        bool isLoaded;
        bool isParsed;
        std::vector<std::string> dependencies;
        std::string error;
    };
    
    FileLoader();
    ~FileLoader();
    
    // 加载文件
    bool loadFile(const std::string& filePath);
    bool loadFiles(const std::vector<std::string>& filePaths);
    
    // 加载目录中的所有CHTL文件
    bool loadDirectory(const std::string& dirPath, bool recursive = true);
    
    // 解析文件
    bool parseFile(const std::string& filePath);
    bool parseAllFiles();
    
    // 获取文件信息
    const FileInfo* getFileInfo(const std::string& filePath) const;
    std::shared_ptr<Node> getAST(const std::string& filePath) const;
    std::string getContent(const std::string& filePath) const;
    
    // 检查文件状态
    bool isFileLoaded(const std::string& filePath) const;
    bool isFileParsed(const std::string& filePath) const;
    bool hasErrors() const;
    
    // 获取错误信息
    std::vector<std::string> getErrors() const;
    std::string getFileError(const std::string& filePath) const;
    
    // 依赖管理
    std::vector<std::string> getDependencies(const std::string& filePath) const;
    std::vector<std::string> getAllDependencies() const;
    bool resolveDependencies();
    
    // 文件监控
    bool hasFileChanged(const std::string& filePath) const;
    std::vector<std::string> getChangedFiles() const;
    bool reloadChangedFiles();
    
    // 清理
    void clearFile(const std::string& filePath);
    void clearAllFiles();
    
    // 设置选项
    void setEncoding(const std::string& encoding) { encoding_ = encoding; }
    void setMaxFileSize(size_t maxSize) { maxFileSize_ = maxSize; }
    void setFollowSymlinks(bool follow) { followSymlinks_ = follow; }
    
    // 获取统计信息
    size_t getLoadedFileCount() const;
    size_t getParsedFileCount() const;
    size_t getTotalFileSize() const;
    
private:
    // 读取文件内容
    std::string readFile(const std::string& filePath);
    
    // 扫描依赖
    std::vector<std::string> scanDependencies(const std::string& content);
    
    // 检查文件
    bool isValidChtlFile(const std::string& filePath) const;
    bool checkFileSize(const std::string& filePath) const;
    
    // 递归加载目录
    void loadDirectoryRecursive(const std::string& dirPath, 
                               std::vector<std::string>& files);
    
    // 存储
    std::unordered_map<std::string, FileInfo> files_;
    
    // 解析器
    std::unique_ptr<BasicParser> parser_;
    
    // 选项
    std::string encoding_ = "UTF-8";
    size_t maxFileSize_ = 10 * 1024 * 1024; // 10MB
    bool followSymlinks_ = false;
    
    // 文件修改时间缓存
    std::unordered_map<std::string, std::time_t> fileModTimes_;
};

} // namespace chtl

#endif // CHTL_FILE_LOADER_H