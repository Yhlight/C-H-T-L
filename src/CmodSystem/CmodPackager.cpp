#include "CmodSystem/CmodPackager.h"
#include "CmodSystem/CmodValidator.h"
#include "CmodSystem/CmodExtractor.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

namespace chtl {

namespace fs = std::filesystem;

CmodPackager::CmodPackager() = default;
CmodPackager::~CmodPackager() = default;

// 打包CMOD模块
CmodPackager::PackageResult CmodPackager::package(const std::string& modulePath, 
                                                 const PackageOptions& options) {
    PackageResult result{false, "", "", {}, 0, {0, 0, 0, 0}};
    
    // 验证模块
    if (options.validateBeforePack) {
        CmodValidator validator;
        auto validationResult = validator.validateModule(modulePath);
        if (!validationResult.isValid) {
            result.error = "Module validation failed";
            for (const auto& err : validationResult.errors) {
                result.warnings.push_back("Validation error: " + err);
            }
            return result;
        }
        result.warnings = validationResult.warnings;
    }
    
    // 提取模块信息
    CmodExtractor extractor;
    auto info = extractor.extractFromDirectory(modulePath);
    if (!info) {
        result.error = "Failed to extract module information";
        return result;
    }
    
    // 生成导出表
    if (options.generateExports) {
        generateExportTable(*info, modulePath + "/src");
    }
    
    // 收集文件
    auto entries = collectFiles(modulePath);
    entries = filterFiles(entries);
    
    // 统计信息
    result.stats.totalFiles = entries.size();
    for (const auto& entry : entries) {
        const std::string& path = entry.relativePath;
        if (path.size() >= 5 && path.substr(path.size() - 5) == ".chtl") {
            result.stats.chtlFiles++;
        }
        if (entry.relativePath.find("/info/") != std::string::npos) {
            result.stats.infoFiles++;
        }
    }
    
    // 创建包清单
    std::string manifest = createManifest(*info, entries);
    
    // 确定输出路径
    std::string outputPath = options.outputPath;
    if (outputPath.empty()) {
        outputPath = generatePackageName(*info);
    }
    
    // 写入.cmod文件
    if (!writeCmodFile(outputPath, manifest, entries, options)) {
        result.error = "Failed to write .cmod file";
        return result;
    }
    
    // 获取文件大小
    if (fs::exists(outputPath)) {
        result.packageSize = fs::file_size(outputPath);
    }
    
    result.success = true;
    result.packagePath = outputPath;
    
    return result;
}

// 收集要打包的文件
std::vector<CmodPackager::PackageEntry> CmodPackager::collectFiles(const std::string& modulePath) {
    std::vector<PackageEntry> entries;
    
    if (!fs::exists(modulePath)) {
        return entries;
    }
    
    for (const auto& entry : fs::recursive_directory_iterator(modulePath)) {
        PackageEntry pe;
        pe.absolutePath = entry.path().string();
        pe.relativePath = fs::relative(entry.path(), modulePath).string();
        pe.isDirectory = entry.is_directory();
        
        if (!pe.isDirectory) {
            pe.size = entry.file_size();
        }
        
        entries.push_back(pe);
    }
    
    return entries;
}

// 过滤文件
std::vector<CmodPackager::PackageEntry> CmodPackager::filterFiles(
    const std::vector<PackageEntry>& entries) {
    
    std::vector<PackageEntry> filtered;
    
    // 排除模式
    const std::vector<std::string> excludePatterns = {
        ".git", ".svn", ".DS_Store", "Thumbs.db", 
        "*.tmp", "*.bak", "*.swp", "node_modules"
    };
    
    for (const auto& entry : entries) {
        bool exclude = false;
        
        for (const auto& pattern : excludePatterns) {
            if (entry.relativePath.find(pattern) != std::string::npos) {
                exclude = true;
                break;
            }
        }
        
        if (!exclude) {
            filtered.push_back(entry);
        }
    }
    
    return filtered;
}

// 生成导出表
void CmodPackager::generateExportTable(CmodInfo& info, const std::string& srcPath) {
    CmodExtractor extractor;
    extractor.scanExports(info, srcPath);
}

// 创建包清单
std::string CmodPackager::createManifest(const CmodInfo& info, 
                                       const std::vector<PackageEntry>& entries) {
    std::stringstream manifest;
    
    // 包头信息
    manifest << "CHTL-CMOD-MANIFEST-V1\n";
    manifest << "name=" << info.name << "\n";
    manifest << "version=" << info.version << "\n";
    manifest << "author=" << info.author << "\n";
    manifest << "files=" << entries.size() << "\n";
    manifest << "---\n";
    
    // 文件列表
    for (const auto& entry : entries) {
        manifest << entry.relativePath << "|" 
                << entry.size << "|" 
                << (entry.isDirectory ? "D" : "F") << "\n";
    }
    
    return manifest.str();
}

// 写入.cmod文件（简化实现）
bool CmodPackager::writeCmodFile(const std::string& outputPath,
                               const std::string& manifest,
                               const std::vector<PackageEntry>& entries,
                               const PackageOptions& options) {
    // TODO: 实现实际的打包逻辑
    // 这里只是创建一个简单的文本文件作为占位
    
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        return false;
    }
    
    // 写入魔数
    out << CMOD_MAGIC << "\n";
    out << "VERSION=" << CMOD_VERSION << "\n";
    out << "COMPRESSED=" << (options.compress ? "true" : "false") << "\n";
    out << "---\n";
    
    // 写入清单
    out << manifest;
    out << "---\n";
    
    // TODO: 实际实现应该包含文件内容的打包
    (void)entries; // 避免未使用警告
    
    out.close();
    return true;
}

// 生成包名
std::string CmodPackager::generatePackageName(const CmodInfo& info) {
    return info.name + "-" + info.version + ".cmod";
}

// 确保目录存在
bool CmodPackager::ensureDirectoryExists(const std::string& path) {
    return fs::create_directories(path);
}

// 其他方法的占位实现
CmodPackager::PackageResult CmodPackager::packageMultiple(
    const std::vector<std::string>& modulePaths, 
    const PackageOptions& options) {
    // TODO: 实现打包多个模块
    (void)modulePaths; // 避免未使用警告
    (void)options;     // 避免未使用警告
    return PackageResult{false, "", "Not implemented", {}, 0, {0, 0, 0, 0}};
}

CmodPackager::PackageResult CmodPackager::validateAndPackage(
    const std::string& modulePath, 
    const PackageOptions& options) {
    auto opts = options;
    opts.validateBeforePack = true;
    return package(modulePath, opts);
}

CmodPackager::PackageResult CmodPackager::packageFromInfo(
    const CmodInfo& info, 
    const PackageOptions& options) {
    if (info.modulePath.empty()) {
        return PackageResult{false, "", "Module path not specified", {}, 0, {0, 0, 0, 0}};
    }
    return package(info.modulePath, options);
}

bool CmodPackager::unpack(const std::string& cmodFilePath, const std::string& outputPath) {
    // TODO: 实现解包功能
    (void)cmodFilePath; // 避免未使用警告
    (void)outputPath;   // 避免未使用警告
    return false;
}

std::unique_ptr<CmodInfo> CmodPackager::getCmodInfo(const std::string& cmodFilePath) {
    // TODO: 实现从.cmod文件读取信息
    (void)cmodFilePath; // 避免未使用警告
    return nullptr;
}

std::vector<uint8_t> CmodPackager::compressData(const std::vector<uint8_t>& data, 
                                               const std::string& level) {
    // TODO: 实现压缩
    (void)level; // 避免未使用警告
    return data;
}

std::vector<uint8_t> CmodPackager::decompressData(const std::vector<uint8_t>& data) {
    // TODO: 实现解压
    return data;
}

std::string CmodPackager::calculateChecksum(const std::vector<uint8_t>& data) {
    // TODO: 实现校验和计算
    (void)data; // 避免未使用警告
    return "placeholder-checksum";
}

bool CmodPackager::verifyChecksum(const std::vector<uint8_t>& data, 
                                const std::string& checksum) {
    // TODO: 实现校验和验证
    (void)data;     // 避免未使用警告
    (void)checksum; // 避免未使用警告
    return true;
}

} // namespace chtl