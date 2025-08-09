#ifndef CHTL_CMOD_PACKAGER_H
#define CHTL_CMOD_PACKAGER_H

#include "CmodSystem/CmodInfo.h"
#include <string>
#include <memory>
#include <vector>

namespace chtl {

// CMOD打包器 - 将CMOD模块打包成.cmod文件
class CmodPackager {
public:
    // 打包选项
    struct PackageOptions {
        bool compress;           // 是否压缩
        bool includeSource;      // 是否包含源代码
        bool generateExports;    // 是否自动生成导出表
        bool validateBeforePack; // 打包前是否验证
        std::string outputPath;         // 输出路径
        std::string compressionLevel; // 压缩级别
        
        // 构造函数提供默认值
        PackageOptions() : 
            compress(true),
            includeSource(true),
            generateExports(true),
            validateBeforePack(true),
            compressionLevel("default") {}
    };
    
    // 打包结果
    struct PackageResult {
        bool success;
        std::string packagePath;        // 生成的.cmod文件路径
        std::string error;
        std::vector<std::string> warnings;
        size_t packageSize;            // 包大小
        
        // 包含的文件统计
        struct Statistics {
            int totalFiles;
            int chtlFiles;
            int infoFiles;
            int submodules;
        } stats;
    };
    
    CmodPackager();
    ~CmodPackager();
    
    // 打包CMOD模块
    PackageResult package(const std::string& modulePath, const PackageOptions& options = {});
    
    // 打包多个模块到一个包
    PackageResult packageMultiple(const std::vector<std::string>& modulePaths, 
                                 const PackageOptions& options = {});
    
    // 验证并打包
    PackageResult validateAndPackage(const std::string& modulePath, 
                                    const PackageOptions& options = {});
    
    // 从CmodInfo打包
    PackageResult packageFromInfo(const CmodInfo& info, 
                                 const PackageOptions& options = {});
    
    // 解包.cmod文件（用于调试或查看）
    bool unpack(const std::string& cmodFilePath, const std::string& outputPath);
    
    // 获取.cmod文件信息（不解包）
    std::unique_ptr<CmodInfo> getCmodInfo(const std::string& cmodFilePath);
    
private:
    // 打包实现
    struct PackageEntry {
        std::string relativePath;   // 相对路径
        std::string absolutePath;   // 绝对路径
        size_t size;               // 文件大小
        bool isDirectory;          // 是否为目录
    };
    
    // 收集要打包的文件
    std::vector<PackageEntry> collectFiles(const std::string& modulePath);
    
    // 过滤文件（排除不需要的文件）
    std::vector<PackageEntry> filterFiles(const std::vector<PackageEntry>& entries);
    
    // 生成导出表
    void generateExportTable(CmodInfo& info, const std::string& srcPath);
    
    // 创建包清单
    std::string createManifest(const CmodInfo& info, 
                              const std::vector<PackageEntry>& entries);
    
    // 写入.cmod文件
    bool writeCmodFile(const std::string& outputPath,
                      const std::string& manifest,
                      const std::vector<PackageEntry>& entries,
                      const PackageOptions& options);
    
    // 压缩数据
    std::vector<uint8_t> compressData(const std::vector<uint8_t>& data, 
                                     const std::string& level);
    
    // 解压数据
    std::vector<uint8_t> decompressData(const std::vector<uint8_t>& data);
    
    // 计算校验和
    std::string calculateChecksum(const std::vector<uint8_t>& data);
    
    // 验证校验和
    bool verifyChecksum(const std::vector<uint8_t>& data, const std::string& checksum);
    
    // 工具方法
    bool ensureDirectoryExists(const std::string& path);
    std::string generatePackageName(const CmodInfo& info);
    
    // 文件格式常量
    static constexpr const char* CMOD_MAGIC = "CHTLCMOD";
    static constexpr uint32_t CMOD_VERSION = 1;
};

} // namespace chtl

#endif // CHTL_CMOD_PACKAGER_H