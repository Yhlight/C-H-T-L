#ifndef CHTL_CJMOD_PROCESSOR_H
#define CHTL_CJMOD_PROCESSOR_H

#include "CJmodInterface.h"
#include <map>
#include <set>

namespace chtl {
namespace cjmod {

// CJmod 处理器 - 管理和执行 CJmod
class CJmodProcessor {
public:
    static CJmodProcessor& getInstance();
    
    // 注册 CJmod
    void registerModule(std::unique_ptr<ICJmod> module);
    void registerFactory(std::unique_ptr<ICJmodFactory> factory);
    
    // 处理 JavaScript 代码
    std::string processJavaScript(const std::string& code, 
                                 const std::set<std::string>& activeModules = {});
    
    // 生成运行时代码
    std::string generateRuntime(const std::set<std::string>& activeModules = {});
    
    // 获取所有已注册模块
    std::vector<std::string> getRegisteredModules() const;
    
    // 启用/禁用模块
    void enableModule(const std::string& name);
    void disableModule(const std::string& name);
    
    // 覆写官方语法
    void overrideCHTLSyntax(const std::string& syntax, const TransformRule& rule);
    
private:
    CJmodProcessor() = default;
    ~CJmodProcessor() = default;
    CJmodProcessor(const CJmodProcessor&) = delete;
    CJmodProcessor& operator=(const CJmodProcessor&) = delete;
    
    // 模块存储
    std::map<std::string, std::unique_ptr<ICJmod>> modules_;
    std::map<std::string, std::unique_ptr<ICJmodFactory>> factories_;
    std::set<std::string> enabledModules_;
    
    // 语法覆写
    std::map<std::string, TransformRule> syntaxOverrides_;
    
    // 处理单个模块的转换
    std::string applyModuleTransforms(const std::string& code, ICJmod* module);
    
    // 应用 CHTL 基础语法转换
    std::string applyCHTLSyntax(const std::string& code);
    
    // 排序转换规则
    std::vector<TransformRule> getSortedRules();
};

// CHTL JS 语法处理器 - 处理官方语法
class CHTLJSSyntaxProcessor {
public:
    struct SyntaxRule {
        std::string name;
        std::regex pattern;
        std::function<std::string(const std::smatch&)> transformer;
        bool canBeOverridden;
    };
    
    static CHTLJSSyntaxProcessor& getInstance();
    
    // 注册官方语法规则
    void registerSyntax(const SyntaxRule& rule);
    
    // 处理代码
    std::string process(const std::string& code);
    
    // 获取可覆写的语法列表
    std::vector<std::string> getOverridableSyntax() const;
    
    // 设置语法覆写
    void setSyntaxOverride(const std::string& syntaxName, 
                          const std::function<std::string(const std::smatch&)>& override);
    
private:
    CHTLJSSyntaxProcessor();
    
    std::vector<SyntaxRule> syntaxRules_;
    std::map<std::string, std::function<std::string(const std::smatch&)>> overrides_;
    
    void initializeOfficialSyntax();
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_PROCESSOR_H