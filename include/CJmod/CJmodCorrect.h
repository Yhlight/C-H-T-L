#ifndef CHTL_CJMOD_CORRECT_H
#define CHTL_CJMOD_CORRECT_H

#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <memory>
#include <map>

namespace chtl {
namespace cjmod {

// CHTL JS 扫描切割规则
struct ScanCutRule {
    std::string name;
    std::regex pattern;        // 扫描模式
    std::string replacement;   // 替换模板或函数
    int priority;              // 优先级
    
    // 可选的验证函数
    std::function<bool(const std::string& context)> validator;
};

// JS 运行时注入
struct RuntimeInjection {
    std::string code;          // 要注入的 JS 代码
    std::string position;      // "before" 或 "after"
};

// CJmod 模块接口
class ICJmod {
public:
    virtual ~ICJmod() = default;
    
    // 模块信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::vector<std::string> getDependencies() const { return {}; }
    
    // 获取扫描切割规则
    virtual std::vector<ScanCutRule> getScanCutRules() const = 0;
    
    // 获取运行时注入代码
    virtual std::vector<RuntimeInjection> getRuntimeInjections() const = 0;
    
    // 可选：覆盖 CHTL JS 官方语法
    virtual std::map<std::string, std::string> getOverrides() const { return {}; }
};

// CHTL JS 处理器 - 这是 CJmod 唯一能访问的部分
class CHTLJSProcessor {
public:
    static CHTLJSProcessor& getInstance();
    
    // 注册 CJmod
    void registerModule(std::shared_ptr<ICJmod> module);
    
    // 处理 JS 代码（通过扫描切割）
    std::string processJavaScript(const std::string& jsCode,
                                 const std::vector<std::string>& activeModules);
    
    // 获取所有运行时代码
    std::string getCombinedRuntime(const std::vector<std::string>& activeModules);
    
private:
    std::map<std::string, std::shared_ptr<ICJmod>> modules_;
    
    // CHTL JS 官方语法规则
    std::vector<ScanCutRule> officialRules_ = {
        // {{&}} -> this
        {"self-reference", std::regex(R"(\{\{&\}\})"), "this", 1000, nullptr},
        
        // {{#id}} -> document.getElementById('id')
        {"id-selector", std::regex(R"(\{\{#([\w-]+)\}\})"), "document.getElementById('$1')", 900, nullptr},
        
        // {{.class}} -> document.getElementsByClassName('class')
        {"class-selector", std::regex(R"(\{\{\.([\w-]+)\}\})"), "document.getElementsByClassName('$1')", 900, nullptr},
        
        // obj->method() -> obj.method()
        {"method-call", std::regex(R"((\w+)->(\w+)\s*\()"), "$1.$2(", 800, nullptr},
        
        // new @Class -> new Class
        {"new-instance", std::regex(R"(new\s+@(\w+))"), "new $1", 700, nullptr},
        
        // foreach item in items -> items.forEach(item =>
        {"foreach", std::regex(R"(foreach\s+(\w+)\s+in\s+(\w+)\s*\{)"), "$2.forEach($1 => {", 600, nullptr}
    };
    
    // 应用扫描切割规则
    std::string applyScanCutRules(const std::string& code,
                                  const std::vector<ScanCutRule>& rules);
};

// 简化的宏
#define DEFINE_CJMOD(name, version) \
    class name##Module : public ICJmod { \
    public: \
        std::string getName() const override { return #name; } \
        std::string getVersion() const override { return version; }

#define END_CJMOD };

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_CORRECT_H