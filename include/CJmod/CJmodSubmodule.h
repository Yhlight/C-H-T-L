#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include "CJmod/CJmodCorrect.h"

namespace chtl {
namespace cjmod {

// 子模块信息
struct SubmoduleInfo {
    std::string name;               // 子模块名称
    std::string path;               // 子模块路径
    std::string version;            // 子模块版本
    std::vector<std::string> dependencies;  // 依赖的其他子模块
    bool autoLoad;                  // 是否随主模块自动加载
};

// 带子模块支持的 CJmod 接口
class ICJmodWithSubmodules : public ICJmod {
public:
    virtual ~ICJmodWithSubmodules() = default;
    
    // 获取所有子模块信息
    virtual std::vector<SubmoduleInfo> getSubmodules() const = 0;
    
    // 加载特定子模块
    virtual std::shared_ptr<ICJmod> loadSubmodule(const std::string& name) = 0;
    
    // 检查是否有子模块
    virtual bool hasSubmodule(const std::string& name) const = 0;
    
    // 获取自动加载的子模块列表
    virtual std::vector<std::string> getAutoLoadSubmodules() const {
        std::vector<std::string> result;
        for (const auto& sub : getSubmodules()) {
            if (sub.autoLoad) {
                result.push_back(sub.name);
            }
        }
        return result;
    }
};

// 组合模块（主模块 + 子模块）
class CompositeModule : public ICJmod {
private:
    std::shared_ptr<ICJmod> mainModule_;
    std::unordered_map<std::string, std::shared_ptr<ICJmod>> submodules_;
    std::string compositeName_;
    
public:
    CompositeModule(std::shared_ptr<ICJmod> mainModule, 
                   const std::string& name = "")
        : mainModule_(mainModule), compositeName_(name) {}
    
    // 添加子模块
    void addSubmodule(const std::string& name, std::shared_ptr<ICJmod> submodule) {
        submodules_[name] = submodule;
    }
    
    // 实现 ICJmod 接口
    std::string getName() const override {
        return compositeName_.empty() ? mainModule_->getName() : compositeName_;
    }
    
    std::string getVersion() const override {
        return mainModule_->getVersion();
    }
    
    std::vector<ScanCutRule> getScanCutRules() const override {
        std::vector<ScanCutRule> rules = mainModule_->getScanCutRules();
        
        // 合并所有子模块的规则
        for (const auto& [name, submodule] : submodules_) {
            auto subRules = submodule->getScanCutRules();
            rules.insert(rules.end(), subRules.begin(), subRules.end());
        }
        
        return rules;
    }
    
    std::vector<RuntimeInjection> getRuntimeInjections() const override {
        std::vector<RuntimeInjection> injections = mainModule_->getRuntimeInjections();
        
        // 合并所有子模块的运行时注入
        for (const auto& [name, submodule] : submodules_) {
            auto subInjections = submodule->getRuntimeInjections();
            injections.insert(injections.end(), subInjections.begin(), subInjections.end());
        }
        
        return injections;
    }
    
    std::map<std::string, std::string> getOverrides() const override {
        std::map<std::string, std::string> overrides = mainModule_->getOverrides();
        
        // 子模块的覆盖可能会覆盖主模块的
        for (const auto& [name, submodule] : submodules_) {
            auto subOverrides = submodule->getOverrides();
            for (const auto& [key, value] : subOverrides) {
                overrides[key] = value;
            }
        }
        
        return overrides;
    }
};

// 基础子模块实现
class SubmoduleBase : public ICJmod {
protected:
    std::string parentModule_;
    std::string submoduleName_;
    std::string fullName_;
    std::string version_;
    
public:
    SubmoduleBase(const std::string& parent, const std::string& name, const std::string& version)
        : parentModule_(parent), submoduleName_(name), version_(version) {
        fullName_ = parent + "." + name;
    }
    
    std::string getName() const override { return fullName_; }
    std::string getVersion() const override { return version_; }
    
    // 子类需要实现具体的规则和注入
    virtual std::vector<ScanCutRule> getScanCutRules() const override = 0;
    virtual std::vector<RuntimeInjection> getRuntimeInjections() const override = 0;
    virtual std::map<std::string, std::string> getOverrides() const override {
        return {};
    }
};

} // namespace cjmod
} // namespace chtl