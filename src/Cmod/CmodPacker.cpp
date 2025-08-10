#include "Cmod/CmodPacker.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <regex>

namespace chtl {

CmodPacker::CmodPacker(const CmodPackOptions& options) : options_(options) {}

CmodPackResult CmodPacker::pack(const std::filesystem::path& moduleDir,
                                const std::filesystem::path& outputFile) {
    CmodPackResult result;
    
    // 验证输入目录
    if (!std::filesystem::exists(moduleDir)) {
        result.errorMessage = "Module directory does not exist: " + moduleDir.string();
        return result;
    }
    
    if (!std::filesystem::is_directory(moduleDir)) {
        result.errorMessage = "Path is not a directory: " + moduleDir.string();
        return result;
    }
    
    // 获取模块名称
    std::string moduleName = moduleDir.filename().string();
    
    // 验证目录结构
    if (!validateStructure(moduleDir, result.warnings)) {
        result.errorMessage = "Invalid CMOD structure";
        return result;
    }
    
    // 生成导出列表
    if (options_.generateExports) {
        generateExportList(moduleDir);
    }
    
    // 确定输出文件名
    std::filesystem::path outFile = outputFile;
    if (outFile.empty()) {
        outFile = moduleName + ".cmod";
    } else if (outFile.extension() != ".cmod") {
        outFile += ".cmod";
    }
    
    // 获取绝对路径
    outFile = std::filesystem::absolute(outFile);
    
    // 收集文件
    auto files = collectFiles(moduleDir);
    result.fileCount = files.size();
    
    // 创建压缩包
    bool packSuccess = false;
    switch (options_.format) {
        case CmodPackOptions::Format::TAR_GZ:
            packSuccess = packWithTar(moduleDir, outFile);
            break;
        case CmodPackOptions::Format::ZIP:
            packSuccess = packWithZip(moduleDir, outFile);
            break;
    }
    
    if (!packSuccess) {
        result.errorMessage = "Failed to create archive";
        return result;
    }
    
    // 获取文件大小
    if (std::filesystem::exists(outFile)) {
        result.compressedSize = std::filesystem::file_size(outFile);
        result.outputFile = outFile.string();
        result.success = true;
    }
    
    return result;
}

bool CmodPacker::validateStructure(const std::filesystem::path& moduleDir,
                                   std::vector<std::string>& warnings) {
    std::filesystem::path infoDir = moduleDir / "info";
    
    // 检查info目录
    if (!std::filesystem::exists(infoDir)) {
        // 尝试创建默认info
        std::filesystem::create_directories(infoDir);
        std::string moduleName = moduleDir.filename().string();
        
        if (!createDefaultInfo(moduleDir, moduleName)) {
            return false;
        }
        warnings.push_back("Created default info file");
    }
    
    // 检查info文件
    std::string moduleName = moduleDir.filename().string();
    std::filesystem::path infoFile = infoDir / (moduleName + ".chtl");
    
    if (!std::filesystem::exists(infoFile)) {
        if (!createDefaultInfo(moduleDir, moduleName)) {
            return false;
        }
        warnings.push_back("Created default info file");
    }
    
    // src目录是可选的
    std::filesystem::path srcDir = moduleDir / "src";
    if (!std::filesystem::exists(srcDir)) {
        warnings.push_back("No src directory found (optional)");
    }
    
    return true;
}

bool CmodPacker::createDefaultInfo(const std::filesystem::path& moduleDir,
                                   const std::string& moduleName) {
    std::filesystem::path infoDir = moduleDir / "info";
    std::filesystem::create_directories(infoDir);
    
    std::filesystem::path infoFile = infoDir / (moduleName + ".chtl");
    std::ofstream out(infoFile);
    
    if (!out) {
        return false;
    }
    
    out << "[Info] {\n";
    out << "    name = \"" << moduleName << "\";\n";
    out << "    version = \"1.0.0\";\n";
    out << "    description = \"CMOD module\";\n";
    out << "    author = \"Unknown\";\n";
    out << "    license = \"MIT\";\n";
    out << "    dependencies = \"\";\n";
    out << "    minCHTLVersion = \"1.0.0\";\n";
    out << "}\n\n";
    out << "[Export] {\n";
    out << "    // Auto-generated export list\n";
    out << "}\n";
    
    return out.good();
}

std::vector<std::filesystem::path> CmodPacker::collectFiles(
    const std::filesystem::path& moduleDir) {
    std::vector<std::filesystem::path> files;
    
    for (const auto& entry : std::filesystem::recursive_directory_iterator(moduleDir)) {
        if (entry.is_regular_file() && !shouldExclude(entry.path())) {
            files.push_back(entry.path());
        }
    }
    
    return files;
}

bool CmodPacker::shouldExclude(const std::filesystem::path& path) {
    std::string filename = path.filename().string();
    std::string pathname = path.string();
    
    for (const auto& pattern : options_.excludePatterns) {
        // 简单的通配符匹配
        if (pattern.find('*') != std::string::npos) {
            std::string regexPattern = pattern;
            // 转换通配符到正则表达式
            regexPattern = std::regex_replace(regexPattern, std::regex("\\."), "\\.");
            regexPattern = std::regex_replace(regexPattern, std::regex("\\*"), ".*");
            
            if (std::regex_match(filename, std::regex(regexPattern))) {
                return true;
            }
        } else {
            // 直接匹配
            if (pathname.find(pattern) != std::string::npos) {
                return true;
            }
        }
    }
    
    return false;
}

bool CmodPacker::generateExportList(const std::filesystem::path& moduleDir) {
    // TODO: 实现自动扫描和生成导出列表
    // 这需要解析CHTL文件并提取可导出的定义
    return true;
}

bool CmodPacker::packWithTar(const std::filesystem::path& moduleDir,
                             const std::filesystem::path& outputFile) {
    // 进入父目录
    std::string parentDir = moduleDir.parent_path().string();
    std::string moduleName = moduleDir.filename().string();
    
    // 构建tar命令
    std::stringstream cmd;
    cmd << "cd \"" << parentDir << "\" && ";
    cmd << "tar -czf \"" << outputFile.string() << "\" \"" << moduleName << "\"";
    
    if (!options_.verbose) {
        cmd << " 2>/dev/null";
    }
    
    // 执行命令
    int result = std::system(cmd.str().c_str());
    return (result == 0);
}

bool CmodPacker::packWithZip(const std::filesystem::path& moduleDir,
                             const std::filesystem::path& outputFile) {
    // 进入父目录
    std::string parentDir = moduleDir.parent_path().string();
    std::string moduleName = moduleDir.filename().string();
    
    // 构建zip命令
    std::stringstream cmd;
    cmd << "cd \"" << parentDir << "\" && ";
    cmd << "zip -r";
    
    if (!options_.verbose) {
        cmd << "q";
    }
    
    cmd << " \"" << outputFile.string() << "\" \"" << moduleName << "\"";
    
    if (!options_.verbose) {
        cmd << " >/dev/null";
    }
    
    // 执行命令
    int result = std::system(cmd.str().c_str());
    return (result == 0);
}

} // namespace chtl