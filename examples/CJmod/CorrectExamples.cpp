#include "CJmod/CJmodCorrect.h"

using namespace chtl::cjmod;

// 示例 1: 响应式语法 - 通过 JS 文本转换实现
DEFINE_CJMOD(Reactive, "1.0.0")

std::vector<ScanCutRule> getScanCutRules() const override {
    return {
        // count := 0  转换为  let count = reactive(0)
        {
            "reactive-declaration",
            std::regex(R"((\w+)\s*:=\s*([^;]+);)"),
            "let $1 = reactive($2);",
            100
        },
        
        // doubled => count * 2  转换为  let doubled = computed(() => count.value * 2)
        {
            "computed-property",
            std::regex(R"((\w+)\s*=>\s*([^;]+);)"),
            "let $1 = computed(() => $2);",
            90
        },
        
        // .value 访问响应式变量
        {
            "reactive-access",
            std::regex(R"(\b(\w+)\.value\b)"),
            "$1.value",
            50  // 低优先级，避免影响其他语法
        },
        
        // watch count { ... }
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
// 响应式系统运行时
const reactive = (value) => {
    let _value = value;
    const listeners = new Set();
    
    return {
        get value() { return _value; },
        set value(newValue) {
            if (_value !== newValue) {
                _value = newValue;
                listeners.forEach(fn => fn());
            }
        },
        subscribe(fn) {
            listeners.add(fn);
            return () => listeners.delete(fn);
        }
    };
};

const computed = (getter) => {
    let cache;
    let dirty = true;
    
    return {
        get value() {
            if (dirty) {
                cache = getter();
                dirty = false;
            }
            return cache;
        }
    };
};

const watch = (target, callback) => {
    if (target && target.subscribe) {
        return target.subscribe(callback);
    }
};
)",
            "before"  // 在其他代码之前注入
        }
    };
}

END_CJMOD

// 示例 2: 动画链式语法
DEFINE_CJMOD(AnimationChain, "1.0.0")

std::vector<ScanCutRule> getScanCutRules() const override {
    return {
        // element ~> fadeIn(300)  转换为  element.chain().fadeIn(300)
        {
            "animation-chain",
            std::regex(R"(([\w\{\}#\.]+)\s*~>\s*(\w+))"),
            "$1.chain().$2",
            100
        },
        
        // ~~ 并行动画
        {
            "parallel-animation",
            std::regex(R"(([\w\{\}#\.]+)\s*~~\s*\[)"),
            "$1.parallel([",
            90
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
// 动画链扩展
Element.prototype.chain = function() {
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

Element.prototype.parallel = function(animations) {
    return Promise.all(animations.map(a => typeof a === 'function' ? a() : a));
};
)",
            "before"
        }
    };
}

END_CJMOD

// 示例 3: DOM 查询增强
DEFINE_CJMOD(QueryEnhanced, "1.0.0")

std::vector<ScanCutRule> getScanCutRules() const override {
    return {
        // $('selector')  类似 jQuery
        {
            "dollar-query",
            std::regex(R"(\$\('([^']+)'\))"),
            "document.querySelector('$1')",
            100
        },
        
        // $$('selector')  查询所有
        {
            "dollar-query-all",
            std::regex(R"(\$\$\('([^']+)'\))"),
            "Array.from(document.querySelectorAll('$1'))",
            100
        },
        
        // element.find('selector')
        {
            "element-find",
            std::regex(R"(\.find\('([^']+)'\))"),
            ".querySelector('$1')",
            90
        },
        
        // element.findAll('selector')
        {
            "element-find-all",
            std::regex(R"(\.findAll\('([^']+)'\))"),
            ".querySelectorAll('$1')",
            90
        }
    };
}

std::vector<RuntimeInjection> getRuntimeInjections() const override {
    return {
        {
            R"(
// 查询增强
window.$ = (selector) => document.querySelector(selector);
window.$$ = (selector) => Array.from(document.querySelectorAll(selector));

// Element 扩展
Element.prototype.find = function(selector) {
    return this.querySelector(selector);
};

Element.prototype.findAll = function(selector) {
    return Array.from(this.querySelectorAll(selector));
};

Element.prototype.parent = function() {
    return this.parentElement;
};

Element.prototype.siblings = function() {
    return Array.from(this.parentElement?.children || [])
        .filter(child => child !== this);
};
)",
            "before"
        }
    };
}

// 覆盖官方语法示例
std::map<std::string, std::string> getOverrides() const override {
    return {
        // 修改 {{#id}} 的行为，返回 jQuery 风格的包装对象
        {"id-selector", "$('#$1')"}
    };
}

END_CJMOD

// 示例 4: 异步语法糖
DEFINE_CJMOD(AsyncSugar, "1.0.0")

std::vector<ScanCutRule> getScanCutRules() const override {
    return {
        // async { ... }  立即执行的异步块
        {
            "async-block",
            std::regex(R"(async\s*\{)"),
            "(async () => {",
            100
        },
        
        // 对应的结束
        {
            "async-block-end",
            std::regex(R"(\}\s*//\s*async\s*end)"),
            "})();",
            99
        },
        
        // await* [promises]  等待所有
        {
            "await-all",
            std::regex(R"(await\*\s*\[)"),
            "await Promise.all([",
            90
        },
        
        // await? expr  忽略错误的 await
        {
            "await-optional",
            std::regex(R"(await\?\s+([^;]+))"),
            "await ($1).catch(() => null)",
            80
        },
        
        // retry 3 times { ... }
        {
            "retry-block",
            std::regex(R"(retry\s+(\d+)\s+times\s*\{)"),
            "await retry($1, async () => {",
            70
        }
    };
}

std::vector<RuntimeInjection> getRuntimeInjections() const override {
    return {
        {
            R"(
// 异步工具函数
window.sleep = (ms) => new Promise(resolve => setTimeout(resolve, ms));

window.retry = async (times, fn, delay = 1000) => {
    let lastError;
    for (let i = 0; i < times; i++) {
        try {
            return await fn();
        } catch (error) {
            lastError = error;
            if (i < times - 1) {
                await sleep(delay);
            }
        }
    }
    throw lastError;
};

window.timeout = async (promise, ms) => {
    return Promise.race([
        promise,
        sleep(ms).then(() => {
            throw new Error('Timeout after ' + ms + 'ms');
        })
    ]);
};
)",
            "before"
        }
    };
}

END_CJMOD

// 示例 5: 调试增强
DEFINE_CJMOD(DebugEnhanced, "1.0.0")

std::vector<std::string> getDependencies() const override {
    return { "QueryEnhanced" };  // 依赖查询增强模块
}

std::vector<ScanCutRule> getScanCutRules() const override {
    return {
        // log variable  简化日志
        {
            "simple-log",
            std::regex(R"(log\s+(\w+))"),
            "console.log('$1:', $1)",
            100
        },
        
        // debug { ... }  调试块
        {
            "debug-block",
            std::regex(R"(debug\s*\{)"),
            "if (window.DEBUG) {",
            90
        },
        
        // assert condition, "message"
        {
            "assert",
            std::regex(R"(assert\s+([^,]+),\s*"([^"]+)")"),
            "console.assert($1, '$2')",
            80
        },
        
        // trace()  打印调用栈
        {
            "trace",
            std::regex(R"(trace\(\))"),
            "console.trace()",
            70
        }
    };
}

std::vector<RuntimeInjection> getRuntimeInjections() const override {
    return {
        {
            R"(
// 调试工具
window.DEBUG = localStorage.getItem('debug') === 'true';

window.enableDebug = () => {
    window.DEBUG = true;
    localStorage.setItem('debug', 'true');
    console.log('Debug mode enabled');
};

window.disableDebug = () => {
    window.DEBUG = false;
    localStorage.removeItem('debug');
    console.log('Debug mode disabled');
};

// 性能测量
window.measure = async (name, fn) => {
    const start = performance.now();
    const result = await fn();
    const end = performance.now();
    console.log(`${name} took ${(end - start).toFixed(2)}ms`);
    return result;
};

// 元素调试
Element.prototype.debug = function() {
    console.group('Element Debug');
    console.log('Tag:', this.tagName);
    console.log('ID:', this.id);
    console.log('Classes:', this.className);
    console.log('Attributes:', Array.from(this.attributes).map(a => `${a.name}="${a.value}"`));
    console.log('Inner HTML:', this.innerHTML);
    console.log('Computed Styles:', getComputedStyle(this));
    console.groupEnd();
    return this;
};
)",
            "before"
        }
    };
}

END_CJMOD