#ifndef CHTL_JS_EXTENSION_H
#define CHTL_JS_EXTENSION_H

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <any>
#include <unordered_map>

namespace chtl {
namespace js {

// 简化的值类型
using Value = std::any;
using Array = std::vector<Value>;
using Object = std::unordered_map<std::string, Value>;
using Function = std::function<Value(const Array&)>;

// 类型转换助手
template<typename T>
T value_cast(const Value& v) {
    return std::any_cast<T>(v);
}

// JavaScript扩展模块基类
class Extension {
public:
    Extension(const std::string& name) : name_(name) {}
    virtual ~Extension() = default;
    
    // 获取模块名称
    const std::string& getName() const { return name_; }
    
    // 初始化模块
    virtual void initialize() = 0;
    
    // 清理模块
    virtual void cleanup() {}
    
protected:
    // 注册函数
    void registerFunction(const std::string& name, Function func) {
        functions_[name] = func;
    }
    
    // 注册属性
    void registerProperty(const std::string& name, const Value& value) {
        properties_[name] = value;
    }
    
    // 注册类
    template<typename T>
    void registerClass(const std::string& name) {
        classes_[name] = std::make_shared<ClassWrapper<T>>();
    }
    
private:
    std::string name_;
    std::unordered_map<std::string, Function> functions_;
    std::unordered_map<std::string, Value> properties_;
    std::unordered_map<std::string, std::shared_ptr<void>> classes_;
    
    template<typename T>
    struct ClassWrapper {
        // 类包装器实现
    };
    
    friend class ExtensionManager;
};

// 扩展管理器
class ExtensionManager {
public:
    static ExtensionManager& getInstance() {
        static ExtensionManager instance;
        return instance;
    }
    
    // 注册扩展
    void registerExtension(std::shared_ptr<Extension> ext) {
        extensions_[ext->getName()] = ext;
        ext->initialize();
    }
    
    // 获取扩展
    std::shared_ptr<Extension> getExtension(const std::string& name) {
        auto it = extensions_.find(name);
        return (it != extensions_.end()) ? it->second : nullptr;
    }
    
    // 调用函数
    Value callFunction(const std::string& module, const std::string& func, const Array& args) {
        auto ext = getExtension(module);
        if (!ext) throw std::runtime_error("Module not found: " + module);
        
        auto& functions = ext->functions_;
        auto it = functions.find(func);
        if (it == functions.end()) throw std::runtime_error("Function not found: " + func);
        
        return it->second(args);
    }
    
private:
    std::unordered_map<std::string, std::shared_ptr<Extension>> extensions_;
};

// 便捷宏定义
#define CJMOD_BEGIN(name) \
    class name##Extension : public chtl::js::Extension { \
    public: \
        name##Extension() : Extension(#name) {} \
        void initialize() override {

#define CJMOD_END() \
        } \
    };

#define CJMOD_FUNCTION(name, body) \
    registerFunction(#name, [this](const chtl::js::Array& args) -> chtl::js::Value { \
        body \
    });

#define CJMOD_EXPORT(name) \
    extern "C" { \
        void cjmod_init() { \
            auto ext = std::make_shared<name##Extension>(); \
            chtl::js::ExtensionManager::getInstance().registerExtension(ext); \
        } \
        void cjmod_cleanup() { \
            /* 清理代码 */ \
        } \
    }

// 参数获取助手
template<typename T>
T getArg(const Array& args, size_t index, const T& defaultValue = T{}) {
    if (index >= args.size()) return defaultValue;
    try {
        return value_cast<T>(args[index]);
    } catch (...) {
        return defaultValue;
    }
}

// 字符串参数特化
template<>
inline std::string getArg<std::string>(const Array& args, size_t index, const std::string& defaultValue) {
    if (index >= args.size()) return defaultValue;
    try {
        // 尝试直接转换
        return value_cast<std::string>(args[index]);
    } catch (...) {
        // 尝试从const char*转换
        try {
            return std::string(value_cast<const char*>(args[index]));
        } catch (...) {
            return defaultValue;
        }
    }
}

} // namespace js
} // namespace chtl

#endif // CHTL_JS_EXTENSION_H