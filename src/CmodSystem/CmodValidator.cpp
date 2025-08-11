#include "CmodSystem/CmodValidator.h"
#include <filesystem>
#include <sstream>
#include <regex>
#include <fstream>

namespace chtl {

namespace fs = std::filesystem;

// 版本比较运算符实现
bool CmodValidator::Version::operator<(const Version& other) const {
    if (major != other.major) return major < other.major;
    if (minor != other.minor) return minor < other.minor;
    return patch < other.patch;
}

bool CmodValidator::Version::operator<=(const Version& other) const {
    return *this < other || *this == other;
}

bool CmodValidator::Version::operator>(const Version& other) const {
    return !(*this <= other);
}

bool CmodValidator::Version::operator>=(const Version& other) const {
    return !(*this < other);
}

bool CmodValidator::Version::operator==(const Version& other) const {
    return major == other.major && minor == other.minor && patch == other.patch;
}

// 验证CMOD目录结构
CmodValidator::ValidationResult CmodValidator::validateStructure(const std::string& modulePath) {
    ValidationResult result{true, {}, {}};
    
    if (!checkDirectoryExists(modulePath)) {
        result.addError("Module directory does not exist: " + modulePath);
        return result;
    }
    
    // 检查src目录
    std::string srcPath = modulePath + "/src";
    if (!checkDirectoryExists(srcPath)) {
        result.addError("Missing required 'src' directory");
    }
    
    // 检查info目录
    std::string infoPath = modulePath + "/info";
    if (!checkDirectoryExists(infoPath)) {
        result.addError("Missing required 'info' directory");
    }
    
    // 检查模块名
    std::string moduleName = fs::path(modulePath).filename().string();
    
    // 检查info文件
    std::string infoFile = infoPath + "/" + moduleName + ".chtl";
    if (!checkFileExists(infoFile)) {
        result.addError("Missing info file: " + infoFile);
    }
    
    // 检查主模块文件（如果没有子模块）
    std::string mainFile = srcPath + "/" + moduleName + ".chtl";
    bool hasSubmodules = false;
    
    // 扫描子模块
    for (const auto& entry : fs::directory_iterator(srcPath)) {
        if (entry.is_directory()) {
            hasSubmodules = true;
            
            // 验证子模块结构
            auto subResult = validateStructure(entry.path().string());
            if (!subResult.isValid) {
                result.addError("Invalid submodule: " + entry.path().filename().string());
                result.errors.insert(result.errors.end(), 
                                   subResult.errors.begin(), 
                                   subResult.errors.end());
            }
        }
    }
    
    if (!hasSubmodules && !checkFileExists(mainFile)) {
        result.addError("Missing main module file: " + mainFile);
    } else if (hasSubmodules && checkFileExists(mainFile)) {
        result.addWarning("Main module file is optional when submodules exist: " + mainFile);
    }
    
    return result;
}

CmodValidator::ValidationResult CmodValidator::validateStructure(const CmodStructure& structure) {
    ValidationResult result{true, {}, {}};
    
    if (!structure.isValid()) {
        result.addError("Invalid CMOD structure");
        
        // 详细检查各个部分
        if (!checkDirectoryExists(structure.rootPath)) {
            result.addError("Root path does not exist: " + structure.rootPath);
        }
        if (!checkDirectoryExists(structure.srcPath)) {
            result.addError("Source path does not exist: " + structure.srcPath);
        }
        if (!checkDirectoryExists(structure.infoPath)) {
            result.addError("Info path does not exist: " + structure.infoPath);
        }
        if (!checkFileExists(structure.infoFile)) {
            result.addError("Info file does not exist: " + structure.infoFile);
        }
        
        // 检查命名规则
        if (!checkNamingConvention(structure.getModuleName(), 
                                 structure.mainModuleFile, 
                                 structure.infoFile)) {
            result.addError("Naming convention violation");
        }
    }
    
    // 递归验证子模块
    for (const auto& submodule : structure.submodules) {
        auto subResult = validateStructure(submodule);
        if (!subResult.isValid) {
            result.isValid = false;
            result.errors.insert(result.errors.end(), 
                               subResult.errors.begin(), 
                               subResult.errors.end());
        }
    }
    
    return result;
}

// 验证CMOD信息
CmodValidator::ValidationResult CmodValidator::validateInfo(const CmodInfo& info) {
    ValidationResult result{true, {}, {}};
    
    // 必需字段
    if (info.name.empty()) {
        result.addError("Module name is required");
    }
    if (info.version.empty()) {
        result.addError("Module version is required");
    }
    
    // 验证版本格式
    try {
        parseVersion(info.version);
    } catch (...) {
        result.addError("Invalid version format: " + info.version);
    }
    
    // 验证版本范围
    if (!info.minCHTLVersion.empty() && !info.maxCHTLVersion.empty()) {
        try {
            auto minVer = parseVersion(info.minCHTLVersion);
            auto maxVer = parseVersion(info.maxCHTLVersion);
            if (minVer > maxVer) {
                result.addError("minCHTLVersion cannot be greater than maxCHTLVersion");
            }
        } catch (...) {
            result.addError("Invalid CHTL version range");
        }
    }
    
    // 建议字段
    if (info.description.empty()) {
        result.addWarning("Module description is recommended");
    }
    if (info.author.empty()) {
        result.addWarning("Module author is recommended");
    }
    if (info.license.empty()) {
        result.addWarning("Module license is recommended");
    }
    
    // 验证类别
    const std::vector<std::string> validCategories = {
        "theme", "component", "utility", "framework", "plugin", "other"
    };
    if (!info.category.empty() && 
        std::find(validCategories.begin(), validCategories.end(), info.category) == validCategories.end()) {
        result.addWarning("Unknown category: " + info.category);
    }
    
    return result;
}

// 验证版本兼容性
CmodValidator::ValidationResult CmodValidator::validateVersion(
    const std::string& version,
    const std::string& minVersion,
    const std::string& maxVersion) {
    
    ValidationResult result{true, {}, {}};
    
    try {
        auto ver = parseVersion(version);
        
        if (!minVersion.empty()) {
            auto minVer = parseVersion(minVersion);
            if (ver < minVer) {
                result.addError("Version " + version + " is below minimum required version " + minVersion);
            }
        }
        
        if (!maxVersion.empty()) {
            auto maxVer = parseVersion(maxVersion);
            if (ver > maxVer) {
                result.addError("Version " + version + " is above maximum supported version " + maxVersion);
            }
        }
    } catch (...) {
        result.addError("Invalid version format");
    }
    
    return result;
}

// 验证依赖
CmodValidator::ValidationResult CmodValidator::validateDependencies(const std::string& dependencies) {
    ValidationResult result{true, {}, {}};
    
    if (dependencies.empty()) {
        return result;
    }
    
    // 解析依赖列表（格式：module1@version1, module2@version2）
    std::regex depRegex(R"((\w+)@([\d\.]+))");
    std::smatch match;
    std::string::const_iterator searchStart(dependencies.cbegin());
    
    while (std::regex_search(searchStart, dependencies.cend(), match, depRegex)) {
        std::string modName = match[1];
        std::string modVersion = match[2];
        
        try {
            parseVersion(modVersion);
        } catch (...) {
            result.addError("Invalid version in dependency: " + modName + "@" + modVersion);
        }
        
        searchStart = match.suffix().first;
    }
    
    return result;
}

// 综合验证
CmodValidator::ValidationResult CmodValidator::validateModule(const std::string& modulePath) {
    ValidationResult result{true, {}, {}};
    
    // 验证结构
    auto structResult = validateStructure(modulePath);
    if (!structResult.isValid) {
        result.isValid = false;
        result.errors.insert(result.errors.end(), 
                           structResult.errors.begin(), 
                           structResult.errors.end());
    }
    result.warnings.insert(result.warnings.end(), 
                         structResult.warnings.begin(), 
                         structResult.warnings.end());
    
    // 如果结构有效，继续验证信息文件
    if (result.isValid) {
        auto infoResult = validateInfoFile(modulePath + "/info/" + 
                                         fs::path(modulePath).filename().string() + ".chtl");
        if (!infoResult.isValid) {
            result.isValid = false;
            result.errors.insert(result.errors.end(), 
                               infoResult.errors.begin(), 
                               infoResult.errors.end());
        }
        result.warnings.insert(result.warnings.end(), 
                             infoResult.warnings.begin(), 
                             infoResult.warnings.end());
    }
    
    return result;
}

// 辅助方法实现
bool CmodValidator::checkDirectoryExists(const std::string& path) {
    return fs::exists(path) && fs::is_directory(path);
}

bool CmodValidator::checkFileExists(const std::string& path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

bool CmodValidator::checkNamingConvention(const std::string& moduleName,
                                        const std::string& mainFile,
                                        const std::string& infoFile) {
    if (moduleName.empty()) {
        return false;
    }
    
    // 检查主文件名
    if (!mainFile.empty()) {
        std::string mainFileName = fs::path(mainFile).stem().string();
        if (mainFileName != moduleName) {
            return false;
        }
    }
    
    // 检查信息文件名
    std::string infoFileName = fs::path(infoFile).stem().string();
    if (infoFileName != moduleName) {
        return false;
    }
    
    return true;
}

CmodValidator::Version CmodValidator::parseVersion(const std::string& versionStr) {
    Version version{0, 0, 0};
    
    std::regex versionRegex(R"((\d+)\.(\d+)\.(\d+))");
    std::smatch match;
    
    if (std::regex_match(versionStr, match, versionRegex)) {
        version.major = std::stoi(match[1]);
        version.minor = std::stoi(match[2]);
        version.patch = std::stoi(match[3]);
    } else {
        throw std::invalid_argument("Invalid version format: " + versionStr);
    }
    
    return version;
}

CmodValidator::ValidationResult CmodValidator::validateInfoFile(const std::string& infoFilePath) {
    ValidationResult result{true, {}, {}};
    
    if (!checkFileExists(infoFilePath)) {
        result.addError("Info file does not exist: " + infoFilePath);
        return result;
    }
    
    // TODO: 实际解析info文件并验证内容
    // 这里需要使用CHTL解析器来解析文件
    
    return result;
}

CmodValidator::ValidationResult CmodValidator::validateSubmodules(const CmodStructure& structure) {
    ValidationResult result{true, {}, {}};
    
    for (const auto& submodule : structure.submodules) {
        auto subResult = validateStructure(submodule);
        if (!subResult.isValid) {
            result.isValid = false;
            result.errors.insert(result.errors.end(), 
                               subResult.errors.begin(), 
                               subResult.errors.end());
        }
        result.warnings.insert(result.warnings.end(), 
                             subResult.warnings.begin(), 
                             subResult.warnings.end());
    }
    
    return result;
}

} // namespace chtl