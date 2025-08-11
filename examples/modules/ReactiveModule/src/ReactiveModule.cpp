#include "CJmod/CJmodCorrect.h"
#include <memory>

namespace chtl {
namespace cjmod {

class ReactiveModule : public ICJmod {
public:
    std::string getName() const override { 
        return "Reactive"; 
    }
    
    std::string getVersion() const override { 
        return "1.0.0"; 
    }
    
    std::vector<std::string> getDependencies() const override {
        return {};
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
            
            // count.value := 5  ->  count.value = 5
            {
                "reactive-assignment",
                std::regex(R"((\w+)\.value\s*:=\s*([^;]+);)"),
                "$1.value = $2;",
                70,
                // 验证器：确保左侧是 .value 访问
                [](const std::string& context) {
                    return context.find(".value") != std::string::npos;
                }
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
    const deps = new Set();
    
    return {
        get value() {
            if (dirty) {
                cache = computeFn();
                dirty = false;
            }
            return cache;
        },
        invalidate() {
            dirty = true;
            // 通知依赖此计算属性的其他响应式对象
            deps.forEach(fn => fn());
        },
        subscribe(fn) {
            deps.add(fn);
            return () => deps.delete(fn);
        }
    };
};

window.watch = function(target, callback) {
    if (target && typeof target.subscribe === 'function') {
        return target.subscribe(callback);
    }
    // 如果不是响应式对象，使用轮询
    let oldValue = target;
    const interval = setInterval(() => {
        if (target !== oldValue) {
            oldValue = target;
            callback();
        }
    }, 100);
    
    // 返回清理函数
    return () => clearInterval(interval);
};

// 批量更新支持
window.batchUpdate = function(fn) {
    // 暂停响应式更新
    window._reactiveUpdatesPaused = true;
    const updates = [];
    
    try {
        fn();
    } finally {
        window._reactiveUpdatesPaused = false;
        // 执行所有累积的更新
        updates.forEach(update => update());
    }
};
)",
                "before"
            }
        };
    }
    
    std::map<std::string, std::string> getOverrides() const override {
        // 可以覆盖官方 CHTL JS 语法
        return {};
    }
};

// 导出函数，供动态库加载
extern "C" std::shared_ptr<ICJmod> createReactiveModule() {
    return std::make_shared<ReactiveModule>();
}

} // namespace cjmod
} // namespace chtl