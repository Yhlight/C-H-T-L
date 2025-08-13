#ifndef CHTL_JS_EXTENSION_H
#define CHTL_JS_EXTENSION_H

#include <any>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>

namespace chtl {
namespace js {

// 基础类型定义
using Value = std::any;
using Array = std::vector<Value>;
using Object = std::unordered_map<std::string, Value>;
using Function = std::function<Value(const Array&)>;

// 类型安全的参数获取
template<typename T>
T getArg(const Array& args, size_t index, const T& defaultValue = T{}) {
    if (index >= args.size()) {
        return defaultValue;
    }
    
    try {
        return std::any_cast<T>(args[index]);
    } catch (const std::bad_any_cast&) {
        // 尝试一些常见的类型转换
        if constexpr (std::is_same_v<T, std::string>) {
            if (args[index].type() == typeid(const char*)) {
                return std::any_cast<const char*>(args[index]);
            }
        }
        return defaultValue;
    }
}

// CJMOD扩展基类
class Extension {
public:
    Extension(const std::string& name) : name_(name) {}
    virtual ~Extension() = default;
    
    // 子类需要实现这个方法来注册功能
    virtual void initialize() = 0;
    
    // 获取扩展名称
    const std::string& getName() const { return name_; }
    
    // 获取所有注册的函数
    const std::unordered_map<std::string, Function>& getFunctions() const {
        return functions_;
    }
    
protected:
    // 注册函数供子类使用
    void registerFunction(const std::string& name, Function func) {
        functions_[name] = std::move(func);
    }
    
    // 便捷的注册方法，支持lambda
    template<typename Func>
    void function(const std::string& name, Func&& func) {
        registerFunction(name, std::forward<Func>(func));
    }
    
private:
    std::string name_;
    std::unordered_map<std::string, Function> functions_;
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
        ext->initialize();
        extensions_[ext->getName()] = ext;
    }
    
    // 获取扩展
    std::shared_ptr<Extension> getExtension(const std::string& name) {
        auto it = extensions_.find(name);
        return it != extensions_.end() ? it->second : nullptr;
    }
    
    // 调用扩展函数
    Value callFunction(const std::string& extName, const std::string& funcName, const Array& args) {
        auto ext = getExtension(extName);
        if (!ext) {
            throw std::runtime_error("Extension not found: " + extName);
        }
        
        auto& functions = ext->getFunctions();
        auto it = functions.find(funcName);
        if (it == functions.end()) {
            throw std::runtime_error("Function not found: " + funcName);
        }
        
        return it->second(args);
    }
    
private:
    ExtensionManager() = default;
    std::unordered_map<std::string, std::shared_ptr<Extension>> extensions_;
};

// C接口导出辅助类
class CJMODExporter {
public:
    using InitFunc = std::function<void()>;
    using CleanupFunc = std::function<void()>;
    
    static void setHandlers(InitFunc init, CleanupFunc cleanup = nullptr) {
        init_ = init;
        cleanup_ = cleanup;
    }
    
    static void doInit() {
        if (init_) init_();
    }
    
    static void doCleanup() {
        if (cleanup_) cleanup_();
    }
    
private:
    static InitFunc init_;
    static CleanupFunc cleanup_;
};

// 静态成员定义
inline CJMODExporter::InitFunc CJMODExporter::init_ = nullptr;
inline CJMODExporter::CleanupFunc CJMODExporter::cleanup_ = nullptr;

} // namespace js
} // namespace chtl

// C接口（必需的）
extern "C" {
    inline void cjmod_init() {
        chtl::js::CJMODExporter::doInit();
    }
    
    inline void cjmod_cleanup() {
        chtl::js::CJMODExporter::doCleanup();
    }
}

#endif // CHTL_JS_EXTENSION_H