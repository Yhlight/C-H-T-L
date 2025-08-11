#include "CJmod/CJmodLoader.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace chtl {
namespace cjmod {

CJmodLoader& CJmodLoader::getInstance() {
    static CJmodLoader instance;
    return instance;
}

std::shared_ptr<ICJmod> CJmodLoader::loadModule(const std::string& path) {
    // 检查缓存
    auto it = moduleCache_.find(path);
    if (it != moduleCache_.end()) {
        return it->second;
    }
    
    // 解析路径
    auto [protocol, moduleName] = parseModulePath(path);
    
    std::shared_ptr<ICJmod> module;
    
    if (protocol == "builtin") {
        // 从内置模块加载
        auto builtinIt = builtinModules_.find(moduleName);
        if (builtinIt != builtinModules_.end()) {
            module = builtinIt->second;
        } else {
            std::cerr << "[CJmod] Builtin module not found: " << moduleName << std::endl;
        }
    } else if (protocol == "cjmod") {
        // 从包管理器加载
        module = loadFromPackage(moduleName);
    } else {
        // 从文件系统加载
        module = loadFromFile(path);
    }
    
    // 缓存模块
    if (module) {
        moduleCache_[path] = module;
        
        // 注册到处理器
        auto& processor = CHTLJSProcessor::getInstance();
        processor.registerModule(module);
    }
    
    return module;
}

void CJmodLoader::registerBuiltinModule(const std::string& name, std::shared_ptr<ICJmod> module) {
    builtinModules_[name] = module;
    std::cout << "[CJmod] Registered builtin module: " << name << std::endl;
}

void CJmodLoader::initializeBuiltins() {
    // 注册响应式模块
    class ReactiveModule : public ICJmod {
    public:
        std::string getName() const override { return "reactive"; }
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
    
    // 注册动画模块
    class AnimationModule : public ICJmod {
    public:
        std::string getName() const override { return "animation"; }
        std::string getVersion() const override { return "1.0.0"; }
        
        std::vector<ScanCutRule> getScanCutRules() const override {
            return {
                // element ~> fadeIn(300)  ->  element.animate().fadeIn(300)
                {
                    "animation-chain",
                    std::regex(R"(([\w\{\}#\.]+)\s*~>\s*(\w+))"),
                    "$1.animate().$2",
                    100
                },
                
                // delay(ms)
                {
                    "delay-function",
                    std::regex(R"(delay\((\d+)\))"),
                    "await new Promise(r => setTimeout(r, $1))",
                    80
                }
            };
        }
        
        std::vector<RuntimeInjection> getRuntimeInjections() const override {
            return {
                {
                    R"(
// CJmod Animation Runtime
Element.prototype.animate = function() {
    const el = this;
    const queue = [];
    
    const animator = {
        fadeIn(duration = 300) {
            queue.push(() => {
                el.style.transition = `opacity ${duration}ms`;
                el.style.opacity = '0';
                el.style.display = 'block';
                setTimeout(() => el.style.opacity = '1', 10);
                return new Promise(r => setTimeout(r, duration));
            });
            return this;
        },
        
        fadeOut(duration = 300) {
            queue.push(() => {
                el.style.transition = `opacity ${duration}ms`;
                el.style.opacity = '0';
                return new Promise(r => setTimeout(() => {
                    el.style.display = 'none';
                    r();
                }, duration));
            });
            return this;
        },
        
        async run() {
            for (const fn of queue) {
                await fn();
            }
        }
    };
    
    setTimeout(() => animator.run(), 0);
    return animator;
};
)",
                    "before"
                }
            };
        }
    };
    
    registerBuiltinModule("reactive", std::make_shared<ReactiveModule>());
    registerBuiltinModule("animation", std::make_shared<AnimationModule>());
    
    // 注册异步流控制模块
    class AsyncFlowModule : public ICJmod {
    public:
        std::string getName() const override { return "async-flow"; }
        std::string getVersion() const override { return "2.0.0"; }
        
        std::vector<ScanCutRule> getScanCutRules() const override {
            return {
                // stream 语法
                {
                    "async-stream",
                    std::regex(R"(stream\s+(\w+)\s+from\s+(\w+)\s*\{)"),
                    "async function* $1() { const _source = $2; try {",
                    150
                },
                // concurrent 语法
                {
                    "concurrent-block",
                    std::regex(R"(concurrent\s*\((\d+)\)\s*\{)"),
                    "await concurrent($1, async () => {",
                    130
                },
                // retry 语法
                {
                    "retry-block",
                    std::regex(R"(retry\s*\((\d+),\s*(\d+)\)\s*\{)"),
                    "await retry($1, $2, async () => {",
                    120
                },
                // try* 语法
                {
                    "try-star",
                    std::regex(R"(try\*\s*\{)"),
                    "await tryAsync(async () => {",
                    100
                },
                // 特殊块结束
                {
                    "special-block-end",
                    std::regex(R"(\}\s*//\s*(stream|concurrent|retry|try\*)\s*end)"),
                    "})",
                    40
                }
            };
        }
        
        std::vector<RuntimeInjection> getRuntimeInjections() const override {
            return {
                {
                    R"(
// Async Flow Runtime (Simplified)
window.concurrent = async (limit, fn) => {
    // 简化版并发控制
    return fn();
};

window.retry = async (times, delay, fn) => {
    let lastError;
    for (let i = 0; i < times; i++) {
        try {
            return await fn();
        } catch (e) {
            lastError = e;
            if (i < times - 1) await new Promise(r => setTimeout(r, delay));
        }
    }
    throw lastError;
};

window.tryAsync = async (fn) => {
    try {
        return await fn();
    } catch (e) {
        console.error('[AsyncFlow]', e);
        return { error: e };
    }
};
)",
                    "before"
                }
            };
        }
    };
    
    registerBuiltinModule("async-flow", std::make_shared<AsyncFlowModule>());
}

std::pair<std::string, std::string> CJmodLoader::parseModulePath(const std::string& path) {
    size_t colonPos = path.find(':');
    if (colonPos != std::string::npos) {
        std::string protocol = path.substr(0, colonPos);
        std::string moduleName = path.substr(colonPos + 1);
        
        // 去除版本号
        size_t atPos = moduleName.find('@');
        if (atPos != std::string::npos) {
            moduleName = moduleName.substr(0, atPos);
        }
        
        return {protocol, moduleName};
    }
    
    return {"file", path};
}

std::shared_ptr<ICJmod> CJmodLoader::loadFromFile(const std::string& filePath) {
    // TODO: 实现从文件加载 CJmod
    // 这需要动态加载或者解释执行
    std::cerr << "[CJmod] Loading from file not yet implemented: " << filePath << std::endl;
    return nullptr;
}

std::shared_ptr<ICJmod> CJmodLoader::loadFromPackage(const std::string& packageName) {
    // TODO: 实现从包管理器加载 CJmod
    std::cerr << "[CJmod] Loading from package not yet implemented: " << packageName << std::endl;
    return nullptr;
}

} // namespace cjmod
} // namespace chtl