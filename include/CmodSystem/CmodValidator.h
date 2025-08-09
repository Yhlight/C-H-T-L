#ifndef CHTL_CMOD_VALIDATOR_H
#define CHTL_CMOD_VALIDATOR_H

#include "CmodSystem/CmodInfo.h"
#include <string>
#include <vector>
#include <memory>

namespace chtl {

// CMOD验证器 - 验证CMOD模块的有效性
class CmodValidator {
public:
    // 验证结果
    struct ValidationResult {
        bool isValid;
        std::vector<std::string> errors;
        std::vector<std::string> warnings;
        
        void addError(const std::string& error) { 
            errors.push_back(error); 
            isValid = false; 
        }
        void addWarning(const std::string& warning) { warnings.push_back(warning); }
    };
    
    CmodValidator() = default;
    ~CmodValidator() = default;
    
    // 验证CMOD目录结构
    ValidationResult validateStructure(const std::string& modulePath);
    ValidationResult validateStructure(const CmodStructure& structure);
    
    // 验证CMOD信息文件
    ValidationResult validateInfo(const CmodInfo& info);
    ValidationResult validateInfoFile(const std::string& infoFilePath);
    
    // 验证主模块文件
    ValidationResult validateMainModule(const std::string& modulePath);
    
    // 验证导出声明
    ValidationResult validateExports(const CmodInfo& info, const std::string& srcPath);
    
    // 验证版本兼容性
    ValidationResult validateVersion(const std::string& version, 
                                   const std::string& minVersion, 
                                   const std::string& maxVersion);
    
    // 验证依赖
    ValidationResult validateDependencies(const std::string& dependencies);
    
    // 综合验证
    ValidationResult validateModule(const std::string& modulePath);
    
private:
    // 检查目录结构
    bool checkDirectoryExists(const std::string& path);
    bool checkFileExists(const std::string& path);
    
    // 检查命名规则
    bool checkNamingConvention(const std::string& moduleName, 
                              const std::string& mainFile, 
                              const std::string& infoFile);
    
    // 解析版本号
    struct Version {
        int major;
        int minor;
        int patch;
        
        bool operator<(const Version& other) const;
        bool operator<=(const Version& other) const;
        bool operator>(const Version& other) const;
        bool operator>=(const Version& other) const;
        bool operator==(const Version& other) const;
    };
    
    Version parseVersion(const std::string& versionStr);
    
    // 验证子模块
    ValidationResult validateSubmodules(const CmodStructure& structure);
};

} // namespace chtl

#endif // CHTL_CMOD_VALIDATOR_H