#include "CJmod/CJmodCorrect.h"

namespace chtl {
namespace cjmod {

// 内置模块声明
extern std::shared_ptr<ICJmod> createReactiveModule();

void registerBuiltinModules() {
    auto& processor = CHTLJSProcessor::getInstance();
    
    // 注册内置模块
    // processor.registerModule(createReactiveModule());
    
    // 注意：实际实现中，这里会注册所有内置模块
    // 为了测试，我们暂时手动创建一个简单的响应式模块
    
    class SimpleReactiveModule : public ICJmod {
    public:
        std::string getName() const override { return "Reactive"; }
        std::string getVersion() const override { return "1.0.0"; }
        
        std::vector<ScanCutRule> getScanCutRules() const override {
            return {
                // count := 0  ->  let count = reactive(0)
                {
                    "reactive-declaration",
                    std::regex(R"((\w+)\s*:=\s*([^;]+);)"),
                    "let $1 = reactive($2);",
                    100
                },
                
                // doubled => count.value * 2  ->  let doubled = computed(() => count.value * 2)
                {
                    "computed-property",
                    std::regex(R"((\w+)\s*=>\s*([^;]+);)"),
                    "let $1 = computed(() => $2);",
                    90
                },
                
                // watch count { ... }  ->  watch(count, () => { ... })
                {
                    "watch-syntax",
                    std::regex(R"(watch\s+(\w+)\s*\{)"),
                    "watch($1, () => {",
                    80
                }
            };
        }
        
        std::vector<RuntimeInjection> getRuntimeInjections() const override {
            return {
                {
                    R"(
// CJmod Reactive Runtime
window.reactive = function(initialValue) {
    let _value = initialValue;
    const subscribers = new Set();
    
    return {
        get value() { return _value; },
        set value(newValue) {
            if (_value !== newValue) {
                _value = newValue;
                subscribers.forEach(fn => fn());
            }
        },
        subscribe(fn) {
            subscribers.add(fn);
            return () => subscribers.delete(fn);
        }
    };
};

window.computed = function(computeFn) {
    let cache;
    let dirty = true;
    
    return {
        get value() {
            if (dirty) {
                cache = computeFn();
                dirty = false;
            }
            return cache;
        }
    };
};

window.watch = function(target, callback) {
    if (target && typeof target.subscribe === 'function') {
        return target.subscribe(callback);
    }
};
)",
                    "before"
                }
            };
        }
    };
    
    processor.registerModule(std::make_shared<SimpleReactiveModule>());
}

} // namespace cjmod
} // namespace chtl