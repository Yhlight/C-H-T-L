#ifndef CHTL_CJMOD_BUILDER_H
#define CHTL_CJMOD_BUILDER_H

#include "CJmodInterface.h"
#include <map>
#include <memory>

namespace chtl {
namespace cjmod {

// 流式 API 构建器
class CJmodBuilder {
public:
    CJmodBuilder(const std::string& name, const std::string& version = "1.0.0")
        : name_(name), version_(version) {}
    
    // 基本信息
    CJmodBuilder& description(const std::string& desc) {
        description_ = desc;
        return *this;
    }
    
    // 添加语法转换 - 简化版
    CJmodBuilder& syntax(const std::string& pattern, const std::string& replacement) {
        return syntax(pattern, [replacement](const std::smatch&) { return replacement; });
    }
    
    // 添加语法转换 - 带捕获组
    CJmodBuilder& syntax(const std::string& pattern, 
                        std::function<std::string(const std::smatch&)> transformer,
                        int priority = 50) {
        rules_.push_back({
            "rule_" + std::to_string(rules_.size()),
            std::regex(pattern),
            priority,
            transformer,
            nullptr
        });
        return *this;
    }
    
    // 添加条件语法转换
    CJmodBuilder& syntaxWhen(const std::string& pattern,
                            std::function<std::string(const std::smatch&)> transformer,
                            std::function<bool(const std::string&)> condition,
                            int priority = 50) {
        rules_.push_back({
            "rule_" + std::to_string(rules_.size()),
            std::regex(pattern),
            priority,
            transformer,
            condition
        });
        return *this;
    }
    
    // 添加方法注入 - 简化版
    CJmodBuilder& method(const std::string& target, 
                        const std::string& methodName,
                        const std::string& implementation) {
        methods_.push_back({target, methodName, implementation, false});
        return *this;
    }
    
    // 添加异步方法
    CJmodBuilder& asyncMethod(const std::string& target,
                             const std::string& methodName,
                             const std::string& implementation) {
        methods_.push_back({target, methodName, implementation, true});
        return *this;
    }
    
    // 添加运算符
    CJmodBuilder& operator_(const std::string& symbol,
                           const std::string& jsOperator,
                           int precedence = 10) {
        operators_.push_back({
            symbol,
            jsOperator,
            precedence,
            false,
            nullptr
        });
        return *this;
    }
    
    // 添加运行时代码
    CJmodBuilder& runtime(const std::string& code) {
        runtimeCode_ += code + "\n";
        return *this;
    }
    
    // 添加运行时文件
    CJmodBuilder& runtimeFile(const std::string& filePath) {
        // 实现会读取文件内容
        // runtimeCode_ += readFile(filePath);
        return *this;
    }
    
    // 覆写官方语法
    CJmodBuilder& override(const std::string& officialSyntax,
                          std::function<std::string(const std::smatch&)> transformer) {
        overrides_[officialSyntax] = transformer;
        return *this;
    }
    
    // 添加钩子
    CJmodBuilder& onInit(std::function<void()> hook) {
        initHook_ = hook;
        return *this;
    }
    
    CJmodBuilder& preprocess(std::function<std::string(const std::string&)> hook) {
        preprocessHook_ = hook;
        return *this;
    }
    
    CJmodBuilder& postprocess(std::function<std::string(const std::string&)> hook) {
        postprocessHook_ = hook;
        return *this;
    }
    
    // 构建最终的 CJmod
    std::unique_ptr<ICJmod> build();
    
private:
    std::string name_;
    std::string version_;
    std::string description_;
    std::vector<TransformRule> rules_;
    std::vector<MethodInjection> methods_;
    std::vector<OperatorDefinition> operators_;
    std::string runtimeCode_;
    std::map<std::string, std::function<std::string(const std::smatch&)>> overrides_;
    
    std::function<void()> initHook_;
    std::function<std::string(const std::string&)> preprocessHook_;
    std::function<std::string(const std::string&)> postprocessHook_;
};

// 快捷创建函数
inline CJmodBuilder createModule(const std::string& name, const std::string& version = "1.0.0") {
    return CJmodBuilder(name, version);
}

// 预定义的常用转换
namespace transforms {
    // 箭头函数转换器
    inline std::function<std::string(const std::smatch&)> arrowFunction() {
        return [](const std::smatch& m) {
            return m[1].str() + " => " + m[2].str();
        };
    }
    
    // 模板字符串转换器
    inline std::function<std::string(const std::smatch&)> template_(const std::string& tmpl) {
        return [tmpl](const std::smatch& m) {
            std::string result = tmpl;
            for (size_t i = 1; i < m.size(); ++i) {
                result = std::regex_replace(result, 
                    std::regex("\\$" + std::to_string(i)), 
                    m[i].str());
            }
            return result;
        };
    }
    
    // 方法调用转换器
    inline std::function<std::string(const std::smatch&)> methodCall(const std::string& newMethod) {
        return [newMethod](const std::smatch& m) {
            return m[1].str() + "." + newMethod + "(" + m[2].str() + ")";
        };
    }
}

// 预定义的方法模板
namespace methods {
    inline std::string eventHandler(const std::string& eventName) {
        return R"(function(handler) {
            return this.addEventListener(')" + eventName + R"(', handler);
        })";
    }
    
    inline std::string propertyGetter(const std::string& propName) {
        return R"(function() {
            return this.)" + propName + R"(;
        })";
    }
    
    inline std::string propertySetter(const std::string& propName) {
        return R"(function(value) {
            this.)" + propName + R"( = value;
            return this;
        })";
    }
}

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_BUILDER_H