#include "Module/CmodFormat.h"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <cstring>

namespace chtl {

namespace fs = std::filesystem;

bool CmodHandler::load(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // 读取文件头
    file.read(reinterpret_cast<char*>(&header_), sizeof(cmod::FileHeader));
    
    // 验证魔数
    if (header_.magic != cmod::MAGIC_NUMBER) {
        return false;
    }
    
    // 验证版本
    if (header_.versionMajor > cmod::VERSION_MAJOR) {
        return false;
    }
    
    // 读取元数据
    file.seekg(header_.metadataOffset);
    // TODO: 实现元数据的序列化/反序列化
    
    // 读取文件条目
    // TODO: 实现文件条目的读取
    
    // 读取内容
    file.seekg(header_.contentOffset);
    content_.resize(file.tellg());
    file.read(reinterpret_cast<char*>(content_.data()), content_.size());
    
    return true;
}

bool CmodHandler::save(const std::string& filepath) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // 准备文件头
    header_.magic = cmod::MAGIC_NUMBER;
    header_.versionMajor = cmod::VERSION_MAJOR;
    header_.versionMinor = cmod::VERSION_MINOR;
    header_.flags = 0;
    header_.timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    header_.fileCount = entries_.size();
    
    // 预留文件头空间
    file.write(reinterpret_cast<const char*>(&header_), sizeof(cmod::FileHeader));
    
    // 写入文件条目
    // TODO: 实现文件条目的序列化
    
    // 记录元数据偏移
    header_.metadataOffset = file.tellp();
    
    // 写入元数据
    // TODO: 实现元数据的序列化
    
    // 记录内容偏移
    header_.contentOffset = file.tellp();
    
    // 写入内容
    file.write(reinterpret_cast<const char*>(content_.data()), content_.size());
    
    // 计算校验和
    header_.checksum = calculateChecksum(content_.data(), content_.size());
    
    // 回写文件头
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&header_), sizeof(cmod::FileHeader));
    
    return true;
}

void CmodHandler::addFile(const std::string& path, const std::vector<uint8_t>& data) {
    cmod::FileEntry entry;
    entry.path = path;
    entry.offset = content_.size();
    entry.size = data.size();
    entry.compressedSize = 0; // 未压缩
    entry.checksum = calculateChecksum(data.data(), data.size());
    entry.flags = 0;
    
    // 判断文件类型
    if (path.ends_with(".chtl")) {
        entry.flags |= cmod::FILE_CHTL;
    }
    
    entries_.push_back(entry);
    
    // 添加到内容
    content_.insert(content_.end(), data.begin(), data.end());
}

void CmodHandler::addFile(const std::string& path, const std::string& content) {
    std::vector<uint8_t> data(content.begin(), content.end());
    addFile(path, data);
}

std::vector<uint8_t> CmodHandler::extractFile(const std::string& path) {
    for (const auto& entry : entries_) {
        if (entry.path == path) {
            std::vector<uint8_t> data;
            data.resize(entry.size);
            std::memcpy(data.data(), content_.data() + entry.offset, entry.size);
            return data;
        }
    }
    return {};
}

std::string CmodHandler::extractFileAsString(const std::string& path) {
    auto data = extractFile(path);
    return std::string(data.begin(), data.end());
}

bool CmodHandler::extractAll(const std::string& outputDir) {
    fs::create_directories(outputDir);
    
    for (const auto& entry : entries_) {
        fs::path filepath = fs::path(outputDir) / entry.path;
        fs::create_directories(filepath.parent_path());
        
        std::ofstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        file.write(reinterpret_cast<const char*>(content_.data() + entry.offset), entry.size);
    }
    
    return true;
}

std::vector<std::string> CmodHandler::listFiles() const {
    std::vector<std::string> files;
    for (const auto& entry : entries_) {
        files.push_back(entry.path);
    }
    return files;
}

bool CmodHandler::verify() const {
    // 验证魔数
    if (header_.magic != cmod::MAGIC_NUMBER) {
        return false;
    }
    
    // 验证校验和
    uint32_t checksum = calculateChecksum(content_.data(), content_.size());
    if (checksum != header_.checksum) {
        return false;
    }
    
    // 验证每个文件的校验和
    for (const auto& entry : entries_) {
        uint32_t fileChecksum = calculateChecksum(
            content_.data() + entry.offset, entry.size);
        if (fileChecksum != entry.checksum) {
            return false;
        }
    }
    
    return true;
}

uint32_t CmodHandler::calculateChecksum(const uint8_t* data, size_t size) {
    // 简单的CRC32实现（可以替换为更复杂的算法）
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < size; ++i) {
        crc ^= data[i];
        for (int j = 0; j < 8; ++j) {
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
        }
    }
    return ~crc;
}

std::vector<uint8_t> CmodHandler::compress(const std::vector<uint8_t>& data) {
    // TODO: 实现压缩算法（如zlib）
    return data;
}

std::vector<uint8_t> CmodHandler::decompress(const std::vector<uint8_t>& data) {
    // TODO: 实现解压缩算法
    return data;
}

} // namespace chtl