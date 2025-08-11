#ifndef CHTL_FILE_UTILS_H
#define CHTL_FILE_UTILS_H

#include <string>
#include <filesystem>

namespace chtl {

class FileUtils {
public:
    // 检查文件是否是CMOD文件
    static bool isCmodFile(const std::string& filePath) {
        std::filesystem::path path(filePath);
        
        // 检查文件扩展名
        if (path.extension() == ".cmod") {
            return true;
        }
        
        // 检查是否在CMOD目录结构中（包含info文件夹）
        auto parent = path.parent_path();
        if (parent.filename() == "src") {
            auto grandParent = parent.parent_path();
            auto infoPath = grandParent / "info";
            return std::filesystem::exists(infoPath) && std::filesystem::is_directory(infoPath);
        }
        
        // 检查同级是否有info文件夹
        auto infoPath = parent / "info";
        return std::filesystem::exists(infoPath) && std::filesystem::is_directory(infoPath);
    }
    
    // 获取文件扩展名
    static std::string getExtension(const std::string& filePath) {
        std::filesystem::path path(filePath);
        return path.extension().string();
    }
    
    // 获取文件名（不含扩展名）
    static std::string getBaseName(const std::string& filePath) {
        std::filesystem::path path(filePath);
        return path.stem().string();
    }
    
    // 检查是否是CHTL文件
    static bool isChtlFile(const std::string& filePath) {
        return getExtension(filePath) == ".chtl";
    }
};

} // namespace chtl

#endif // CHTL_FILE_UTILS_H