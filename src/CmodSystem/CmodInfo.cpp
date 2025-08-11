#include "CmodSystem/CmodInfo.h"
#include <filesystem>
#include <algorithm>

namespace chtl {

namespace fs = std::filesystem;

bool CmodStructure::isValid() const {
    // 检查基本路径是否存在
    if (rootPath.empty() || !fs::exists(rootPath)) {
        return false;
    }
    
    // 检查src和info目录
    if (!fs::exists(srcPath) || !fs::exists(infoPath)) {
        return false;
    }
    
    // 检查信息文件
    if (!fs::exists(infoFile)) {
        return false;
    }
    
    // 如果没有子模块，必须有主模块文件
    if (submodules.empty() && !fs::exists(mainModuleFile)) {
        return false;
    }
    
    // 验证命名规则：模块名、主文件名、信息文件名必须一致
    std::string moduleName = getModuleName();
    
    if (!mainModuleFile.empty()) {
        std::string mainFileName = fs::path(mainModuleFile).stem().string();
        if (mainFileName != moduleName) {
            return false;
        }
    }
    
    std::string infoFileName = fs::path(infoFile).stem().string();
    if (infoFileName != moduleName) {
        return false;
    }
    
    // 递归验证子模块
    for (const auto& submodule : submodules) {
        if (!submodule.isValid()) {
            return false;
        }
    }
    
    return true;
}

std::string CmodStructure::getModuleName() const {
    if (rootPath.empty()) {
        return "";
    }
    
    // 从根路径获取模块名
    fs::path path(rootPath);
    return path.filename().string();
}

} // namespace chtl