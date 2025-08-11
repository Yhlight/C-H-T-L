#ifndef CHTL_MODULE_INFO_H
#define CHTL_MODULE_INFO_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace chtl {

// 模块信息类
class ModuleInfo {
public:
    // 模块类型
    enum class ModuleType {
        OFFICIAL,   // 官方模块
        LOCAL,      // 本地模块（module文件夹）
        CURRENT,    // 当前目录模块
        EMBEDDED    // 嵌入式模块
    };
    
private:
    std::string name_;                      // 模块名称，如 "Chtholly.Space"
    std::string version_;                   // 版本号
    std::string description_;               // 描述
    std::string author_;                    // 作者
    std::string license_;                   // 许可证
    std::string path_;                      // 模块路径
    ModuleType type_;                       // 模块类型
    std::vector<std::string> submodules_;   // 子模块列表
    std::unordered_map<std::string, std::string> metadata_;  // 其他元数据
    
public:
    ModuleInfo(const std::string& name) : name_(name), type_(ModuleType::LOCAL) {}
    
    // Getter/Setter
    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }
    
    const std::string& getVersion() const { return version_; }
    void setVersion(const std::string& version) { version_ = version; }
    
    const std::string& getDescription() const { return description_; }
    void setDescription(const std::string& desc) { description_ = desc; }
    
    const std::string& getAuthor() const { return author_; }
    void setAuthor(const std::string& author) { author_ = author; }
    
    const std::string& getLicense() const { return license_; }
    void setLicense(const std::string& license) { license_ = license; }
    
    const std::string& getPath() const { return path_; }
    void setPath(const std::string& path) { path_ = path; }
    
    ModuleType getType() const { return type_; }
    void setType(ModuleType type) { type_ = type; }
    
    // 子模块管理
    void addSubmodule(const std::string& submodule) {
        submodules_.push_back(submodule);
    }
    
    const std::vector<std::string>& getSubmodules() const {
        return submodules_;
    }
    
    bool hasSubmodule(const std::string& name) const {
        for (const auto& sub : submodules_) {
            if (sub == name) return true;
        }
        return false;
    }
    
    // 元数据管理
    void setMetadata(const std::string& key, const std::string& value) {
        metadata_[key] = value;
    }
    
    std::string getMetadata(const std::string& key) const {
        auto it = metadata_.find(key);
        return (it != metadata_.end()) ? it->second : "";
    }
    
    // 解析模块名称（支持子模块）
    static std::pair<std::string, std::string> parseModuleName(const std::string& fullName) {
        size_t dotPos = fullName.find('.');
        if (dotPos != std::string::npos) {
            return {fullName.substr(0, dotPos), fullName.substr(dotPos + 1)};
        }
        return {fullName, ""};
    }
    
    // 检查是否是子模块名称
    static bool isSubmodule(const std::string& name) {
        return name.find('.') != std::string::npos;
    }
};

} // namespace chtl

#endif // CHTL_MODULE_INFO_H