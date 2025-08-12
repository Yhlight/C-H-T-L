#include "CJmod/CJmodProcessor.h"
#include "CJmod/CJmodCore.h"
#include <sstream>

namespace chtl {
namespace cjmod {

// 内置的 reactive 模块
class BuiltinReactiveModule : public CJmodModule {
public:
    std::vector<SyntaxBuilder> syntax() override {
        std::vector<SyntaxBuilder> rules;
        
        // 响应式赋值 :=
        rules.push_back(
            SyntaxBuilder("reactive-assignment")
                .priority(200)
                .pattern(R"((\w+)\s*:=\s*([^;]+);?)")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string varName = result.captures.at("1");
                    std::string value = result.captures.at("2");
                    
                    std::stringstream code;
                    code << "const " << varName << " = CHTL.reactive(" << value << ")";
                    
                    return code.str();
                })
        );
        
        // 计算属性 =>
        rules.push_back(
            SyntaxBuilder("computed-property")
                .priority(190)
                .pattern(R"((\w+)\s*=>\s*\{([^}]+)\})")
                .generate([](const ScanResult& result, GenerateContext* ctx) {
                    std::string varName = result.captures.at("1");
                    std::string body = result.captures.at("2");
                    
                    std::stringstream code;
                    code << "const " << varName << " = CHTL.computed(() => {" << body << "})";
                    
                    return code.str();
                })
        );
        
        return rules;
    }
    
    void runtime(RuntimeBuilder& builder) override {
        // 响应式系统运行时
        builder.addFunction("reactive", R"(function(initialValue) {
            let value = initialValue;
            const listeners = new Set();
            
            const reactive = {
                get value() {
                    return value;
                },
                set value(newValue) {
                    const oldValue = value;
                    value = newValue;
                    listeners.forEach(fn => fn(newValue, oldValue));
                },
                subscribe(fn) {
                    listeners.add(fn);
                    return () => listeners.delete(fn);
                }
            };
            
            return reactive;
        })");
        
        // 计算属性
        builder.addFunction("computed", R"(function(computeFn) {
            const result = CHTL.reactive(computeFn());
            // TODO: 依赖追踪
            return result;
        })");
        
        // 模块信息
        builder.addInitCode("CHTL.modules.reactive = { version: '1.0.0', builtin: true };");
    }
};

// 注册内置模块
void registerBuiltinModules() {
    static bool registered = false;
    if (registered) return;
    
    auto& processor = CJmodProcessor::getInstance();
    
    // 注册 reactive 模块
    processor.loadModuleFromMemory(std::make_unique<BuiltinReactiveModule>());
    
    registered = true;
}

namespace integration {

// 在 initializeCJmod 中调用
void initializeBuiltinModules() {
    registerBuiltinModules();
}

} // namespace integration

} // namespace cjmod
} // namespace chtl