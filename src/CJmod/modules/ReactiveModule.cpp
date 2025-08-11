#include "CJmod/CJmodCorrect.h"

namespace chtl {
namespace cjmod {

DEFINE_CJMOD(Reactive, "1.0.0")

std::vector<std::string> getDependencies() const override {
    return {};  // 无依赖
}

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
        },
        
        // 响应式赋值: count = 5  ->  count.value = 5
        {
            "reactive-assignment",
            std::regex(R"((\w+)\s*=\s*([^;=]+);)"),
            "$1.value = $2;",
            60,
            // 验证函数：只对已声明的响应式变量生效
            [](const std::string& context) {
                // 简单检查：是否存在 reactive 声明
                return context.find("reactive(") != std::string::npos ||
                       context.find(":=") != std::string::npos;
            }
        }
    };
}

std::vector<RuntimeInjection> getRuntimeInjections() const override {
    return {
        {
            R"(
// CJmod Reactive System Runtime
window.reactive = function(initialValue) {
    let _value = initialValue;
    const subscribers = new Set();
    
    return {
        get value() {
            return _value;
        },
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
    const subscribers = new Set();
    
    const recompute = () => {
        dirty = true;
        subscribers.forEach(fn => fn());
    };
    
    // 简单的依赖收集（生产版本需要更复杂的实现）
    let deps = [];
    
    return {
        get value() {
            if (dirty) {
                cache = computeFn();
                dirty = false;
            }
            return cache;
        },
        subscribe(fn) {
            subscribers.add(fn);
            return () => subscribers.delete(fn);
        }
    };
};

window.watch = function(target, callback) {
    if (target && typeof target.subscribe === 'function') {
        return target.subscribe(callback);
    }
    console.warn('[CJmod Reactive] Cannot watch non-reactive value');
};

window.effect = function(fn) {
    // 立即执行并收集依赖
    fn();
    // 简化版本：实际需要更复杂的依赖追踪
};
)",
            "before"  // 在用户代码之前注入
        }
    };
}

std::map<std::string, std::string> getOverrides() const override {
    // 不覆盖任何官方语法
    return {};
}

END_CJMOD

} // namespace cjmod
} // namespace chtl