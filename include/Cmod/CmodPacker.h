#ifndef CHTL_CMOD_PACKER_H
#define CHTL_CMOD_PACKER_H

#include <string>
#include <vector>
#include <filesystem>
#include <memory>

namespace chtl {

// CMOD打包选项
struct CmodPackOptions {
    enum class Format {
        TAR_GZ,
        ZIP
    };
    
    Format format = Format::TAR_GZ;
    bool verbose = false;
    bool generateExports = true;
    std::vector<std::string> excludePatterns = {
        ".git", "__pycache__", ".DS_Store", "Thumbs.db",
        "*.o", "*.tmp", "*.swp", "*.bak"
    };
};

// CMOD打包结果
struct CmodPackResult {
    bool success = false;
    std::string outputFile;
    std::string errorMessage;
    std::vector<std::string> warnings;
    size_t fileCount = 0;
    size_t compressedSize = 0;
};

class CmodPacker {
private:
    CmodPackOptions options_;
    
    // 验证CMOD目录结构
    bool validateStructure(const std::filesystem::path& moduleDir,
                          std::vector<std::string>& warnings);
    
    // 创建默认info文件
    bool createDefaultInfo(const std::filesystem::path& moduleDir,
                          const std::string& moduleName);
    
    // 收集要打包的文件
    std::vector<std::filesystem::path> collectFiles(
        const std::filesystem::path& moduleDir);
    
    // 检查文件是否应该被排除
    bool shouldExclude(const std::filesystem::path& path);
    
    // 生成导出列表
    bool generateExportList(const std::filesystem::path& moduleDir);
    
    // 使用tar创建压缩包
    bool packWithTar(const std::filesystem::path& moduleDir,
                     const std::filesystem::path& outputFile);
    
    // 使用zip创建压缩包
    bool packWithZip(const std::filesystem::path& moduleDir,
                     const std::filesystem::path& outputFile);
    
public:
    CmodPacker(const CmodPackOptions& options = {});
    
    // 打包模块目录
    CmodPackResult pack(const std::filesystem::path& moduleDir,
                       const std::filesystem::path& outputFile = "");
    
    // 设置选项
    void setOptions(const CmodPackOptions& options) { options_ = options; }
    const CmodPackOptions& getOptions() const { return options_; }
};

} // namespace chtl

#endif // CHTL_CMOD_PACKER_H