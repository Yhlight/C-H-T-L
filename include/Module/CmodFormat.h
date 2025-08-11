#ifndef CHTL_CMOD_FORMAT_H
#define CHTL_CMOD_FORMAT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace chtl {

// CMOD文件格式定义
// CMOD = CHTL Module，是CHTL的打包模块格式
namespace cmod {

// CMOD文件魔数
constexpr uint32_t MAGIC_NUMBER = 0x434D4F44; // "CMOD" in hex

// CMOD版本号
constexpr uint16_t VERSION_MAJOR = 1;
constexpr uint16_t VERSION_MINOR = 0;

// 文件头结构
struct FileHeader {
    uint32_t magic;           // 魔数 "CMOD"
    uint16_t versionMajor;    // 主版本号
    uint16_t versionMinor;    // 次版本号
    uint32_t flags;           // 标志位
    uint64_t timestamp;       // 创建时间戳
    uint32_t fileCount;       // 文件数量
    uint32_t metadataOffset;  // 元数据偏移
    uint32_t contentOffset;   // 内容区偏移
    uint32_t checksum;        // 校验和
};

// 文件条目
struct FileEntry {
    std::string path;         // 文件路径（相对路径）
    uint32_t offset;          // 在CMOD中的偏移
    uint32_t size;            // 文件大小
    uint32_t compressedSize;  // 压缩后大小（0表示未压缩）
    uint32_t checksum;        // 文件校验和
    uint32_t flags;           // 文件标志
};

// 元数据
struct Metadata {
    std::string name;         // 模块名称
    std::string version;      // 版本号
    std::string description;  // 描述
    std::string author;       // 作者
    std::string license;      // 许可证
    std::vector<std::string> dependencies;  // 依赖列表
    std::unordered_map<std::string, std::string> custom;  // 自定义元数据
};

// 标志位定义
enum Flags : uint32_t {
    FLAG_COMPRESSED = 0x01,   // 是否压缩
    FLAG_ENCRYPTED = 0x02,    // 是否加密
    FLAG_SIGNED = 0x04,       // 是否签名
    FLAG_DEBUG = 0x08         // 调试模式
};

// 文件类型
enum FileType : uint32_t {
    FILE_CHTL = 0x01,         // .chtl文件
    FILE_RESOURCE = 0x02,     // 资源文件
    FILE_CONFIG = 0x04,       // 配置文件
    FILE_METADATA = 0x08      // 元数据文件
};

} // namespace cmod

// CMOD文件处理器
class CmodHandler {
private:
    cmod::FileHeader header_;
    cmod::Metadata metadata_;
    std::vector<cmod::FileEntry> entries_;
    std::vector<uint8_t> content_;
    
public:
    CmodHandler() = default;
    
    // 读取CMOD文件
    bool load(const std::string& filepath);
    
    // 保存CMOD文件
    bool save(const std::string& filepath);
    
    // 添加文件
    void addFile(const std::string& path, const std::vector<uint8_t>& data);
    void addFile(const std::string& path, const std::string& content);
    
    // 提取文件
    std::vector<uint8_t> extractFile(const std::string& path);
    std::string extractFileAsString(const std::string& path);
    
    // 提取所有文件
    bool extractAll(const std::string& outputDir);
    
    // 元数据管理
    cmod::Metadata& getMetadata() { return metadata_; }
    const cmod::Metadata& getMetadata() const { return metadata_; }
    void setMetadata(const cmod::Metadata& metadata) { metadata_ = metadata; }
    
    // 文件列表
    std::vector<std::string> listFiles() const;
    
    // 验证文件
    bool verify() const;
    
private:
    // 计算校验和
    uint32_t calculateChecksum(const uint8_t* data, size_t size) const;
    
    // 压缩/解压缩（未来实现）
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& data);
};

} // namespace chtl

#endif // CHTL_CMOD_FORMAT_H