#ifndef CHTL_CJMOD_REALISTIC_H
#define CHTL_CJMOD_REALISTIC_H

#include <string>
#include <vector>
#include <functional>
#include <regex>
#include <memory>

namespace chtl {
namespace cjmod {

// CHTL JS 转换规则
struct JSTransformRule {
    std::string name;
    std::regex pattern;
    std::function<std::string(const std::smatch&)> replacer;
    int priority;  // 优先级，越高越先执行
};

// JS 方法注入
struct JSMethodInjection {
    std::string target;      // Element, Document, Window 等
    std::string methodName;
    std::string implementation;
};

// CJmod 接口 - 专注于 CHTL JS 扩展
class ICJmodJS {
public:
    virtual ~ICJmodJS() = default;
    
    // 基本信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::string getDescription() const = 0;
    
    // 获取 JS 转换规则
    virtual std::vector<JSTransformRule> getTransformRules() const = 0;
    
    // 获取方法注入
    virtual std::vector<JSMethodInjection> getMethodInjections() const = 0;
    
    // 获取运行时代码
    virtual std::string getRuntimeCode() const = 0;
    
    // 预处理钩子（在应用转换规则前）
    virtual std::string preprocessJS(const std::string& jsCode) { return jsCode; }
    
    // 后处理钩子（在应用转换规则后）
    virtual std::string postprocessJS(const std::string& jsCode) { return jsCode; }
};

// CHTL JS 处理器
class CHTLJSProcessor {
public:
    // 处理 script 块中的 JS 代码
    std::string processScriptContent(const std::string& jsCode,
                                   const std::vector<std::string>& activeModules);
    
    // 注册模块
    void registerModule(std::shared_ptr<ICJmodJS> module);
    
    // 获取组合的运行时代码
    std::string getCombinedRuntime(const std::vector<std::string>& activeModules);
    
private:
    std::map<std::string, std::shared_ptr<ICJmodJS>> modules_;
    
    // 应用转换规则
    std::string applyTransforms(const std::string& code, 
                               const std::vector<JSTransformRule>& rules);
    
    // 处理 CHTL JS 核心语法
    std::string processCoreJSSyntax(const std::string& code);
};

// 简化的创建宏
#define CJMOD_JS(name, version) \
    class name##JSModule : public ICJmodJS { \
    public: \
        std::string getName() const override { return #name; } \
        std::string getVersion() const override { return version; }

#define CJMOD_JS_END() };

// 辅助函数
namespace helpers {
    // 创建简单替换规则
    inline JSTransformRule simpleReplace(const std::string& pattern, 
                                        const std::string& replacement,
                                        int priority = 50) {
        return {
            pattern,
            std::regex(pattern),
            [replacement](const std::smatch&) { return replacement; },
            priority
        };
    }
    
    // 创建模板替换规则
    inline JSTransformRule templateReplace(const std::string& pattern,
                                          const std::string& template_,
                                          int priority = 50) {
        return {
            pattern,
            std::regex(pattern),
            [template_](const std::smatch& match) {
                std::string result = template_;
                for (size_t i = 0; i < match.size(); ++i) {
                    result = std::regex_replace(result, 
                        std::regex("\\$" + std::to_string(i)), 
                        match[i].str());
                }
                return result;
            },
            priority
        };
    }
}

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_REALISTIC_H