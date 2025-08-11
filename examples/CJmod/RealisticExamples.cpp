#include "CJmod/CJmodRealistic.h"

using namespace chtl::cjmod;

// 示例 1: 响应式语法扩展
CJMOD_JS(Reactive, "1.0.0")

std::string getDescription() const override {
    return "Adds reactive programming syntax to CHTL JS";
}

std::vector<JSTransformRule> getTransformRules() const override {
    return {
        // count := 0  →  const count = reactive(0)
        helpers::templateReplace(
            R"((\w+)\s*:=\s*([^;]+);)",
            "const $1 = reactive($2);",
            100
        ),
        
        // doubled => count.value * 2  →  const doubled = computed(() => count.value * 2)
        helpers::templateReplace(
            R"((\w+)\s*=>\s*([^;]+);)",
            "const $1 = computed(() => $2);",
            90
        ),
        
        // watch count -> { ... }  →  watch(count, () => { ... })
        helpers::templateReplace(
            R"(watch\s+(\w+)\s*->\s*\{)",
            "watch($1, () => {",
            80
        ),
        
        // effect { ... }  →  effect(() => { ... })
        helpers::simpleReplace(
            R"(effect\s*\{)",
            "effect(() => {",
            70
        )
    };
}

std::vector<JSMethodInjection> getMethodInjections() const override {
    return {
        {
            "Element",
            "bindModel",
            R"(function(varName) {
                const element = this;
                const variable = window[varName];
                
                element.addEventListener('input', (e) => {
                    if (variable && variable.value !== undefined) {
                        variable.value = e.target.value;
                    }
                });
                
                if (variable && variable.subscribe) {
                    variable.subscribe(() => {
                        element.value = variable.value;
                    });
                }
            })"
        }
    };
}

std::string getRuntimeCode() const override {
    return R"(
// Reactive System Runtime
function reactive(initialValue) {
    let value = initialValue;
    const subscribers = new Set();
    
    return {
        get value() {
            return value;
        },
        set value(newValue) {
            if (value !== newValue) {
                value = newValue;
                subscribers.forEach(fn => fn());
            }
        },
        subscribe(fn) {
            subscribers.add(fn);
            return () => subscribers.delete(fn);
        }
    };
}

function computed(computeFn) {
    let cache;
    let dirty = true;
    
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
        }
    };
}

function watch(target, callback) {
    if (target && target.subscribe) {
        return target.subscribe(callback);
    }
}

function effect(fn) {
    fn();
    // 简化版：实际应该追踪依赖
}
)";
}

CJMOD_JS_END()

// 示例 2: 动画语法扩展
CJMOD_JS(Animation, "1.0.0")

std::string getDescription() const override {
    return "Animation chain syntax for CHTL JS";
}

std::vector<JSTransformRule> getTransformRules() const override {
    return {
        // element ~> fadeIn(300)  →  element.animate().fadeIn(300)
        {
            "animation-chain",
            std::regex(R"(([\w\{\}#\.]+)\s*~>\s*(\w+)\s*\()"),
            [](const std::smatch& match) {
                return match[1].str() + ".animate()." + match[2].str() + "(";
            },
            100
        },
        
        // element ~~ { opacity: 0.5 }  →  element.animateProps({ opacity: 0.5 })
        helpers::templateReplace(
            R"(([\w\{\}#\.]+)\s*~~\s*\{)",
            "$1.animateProps({",
            90
        ),
        
        // delay(500)  →  await new Promise(r => setTimeout(r, 500))
        helpers::templateReplace(
            R"(delay\s*\(\s*(\d+)\s*\))",
            "await new Promise(r => setTimeout(r, $1))",
            80
        ),
        
        // parallel { ... }  →  await Promise.all([...])
        helpers::simpleReplace(
            R"(parallel\s*\{)",
            "await Promise.all([",
            70
        )
    };
}

std::vector<JSMethodInjection> getMethodInjections() const override {
    return {
        {
            "Element",
            "animate",
            R"(function() {
                const element = this;
                const queue = [];
                
                const animator = {
                    fadeIn(duration = 300) {
                        queue.push(async () => {
                            element.style.opacity = '0';
                            element.style.display = 'block';
                            await element.animateProps({ opacity: 1 }, duration);
                        });
                        return this;
                    },
                    
                    fadeOut(duration = 300) {
                        queue.push(async () => {
                            await element.animateProps({ opacity: 0 }, duration);
                            element.style.display = 'none';
                        });
                        return this;
                    },
                    
                    slideDown(duration = 300) {
                        queue.push(async () => {
                            const height = element.scrollHeight;
                            element.style.height = '0';
                            element.style.overflow = 'hidden';
                            element.style.display = 'block';
                            await element.animateProps({ height: height + 'px' }, duration);
                            element.style.height = '';
                            element.style.overflow = '';
                        });
                        return this;
                    },
                    
                    async run() {
                        for (const animation of queue) {
                            await animation();
                        }
                    }
                };
                
                // 自动执行队列
                setTimeout(() => animator.run(), 0);
                return animator;
            })"
        },
        {
            "Element",
            "animateProps",
            R"(async function(props, duration = 300) {
                const transitions = Object.keys(props)
                    .map(prop => `${prop} ${duration}ms ease`)
                    .join(', ');
                
                this.style.transition = transitions;
                
                // 强制重排
                this.offsetHeight;
                
                // 应用属性
                Object.assign(this.style, props);
                
                // 等待动画完成
                await new Promise(resolve => setTimeout(resolve, duration));
                
                // 清理
                this.style.transition = '';
            })"
        }
    };
}

std::string getRuntimeCode() const override {
    return R"(
// Animation helpers
window.Easing = {
    linear: 'linear',
    ease: 'ease',
    easeIn: 'ease-in',
    easeOut: 'ease-out',
    easeInOut: 'ease-in-out'
};
)";
}

CJMOD_JS_END()

// 示例 3: 语法糖模块
CJMOD_JS(SyntaxSugar, "1.0.0")

std::string getDescription() const override {
    return "Convenient syntax shortcuts";
}

std::vector<JSTransformRule> getTransformRules() const override {
    return {
        // 日志简写
        helpers::simpleReplace(R"(log\s+)", "console.log(", 100),
        helpers::simpleReplace(R"(warn\s+)", "console.warn(", 100),
        helpers::simpleReplace(R"(error\s+)", "console.error(", 100),
        
        // 快速选择器
        helpers::simpleReplace(R"(\$\$)", "document.querySelector", 90),
        helpers::simpleReplace(R"(\$\$all)", "document.querySelectorAll", 90),
        
        // 空值合并
        helpers::simpleReplace(R"(\?\?)", "||", 80),
        
        // 类型检查
        helpers::simpleReplace(R"(is\s+null)", "=== null", 70),
        helpers::simpleReplace(R"(is\s+not\s+null)", "!== null", 70),
        helpers::simpleReplace(R"(is\s+undefined)", "=== undefined", 70),
        
        // try 简写
        helpers::templateReplace(
            R"(try!\s*(.+);)",
            "try { $1; } catch(e) { console.error(e); }",
            60
        ),
        
        // assert
        helpers::templateReplace(
            R"(assert\s+([^,]+),\s*(.+);)",
            "if (!($1)) throw new Error($2);",
            50
        )
    };
}

std::vector<JSMethodInjection> getMethodInjections() const override {
    return {
        {
            "Element",
            "show",
            "function() { this.style.display = ''; return this; }"
        },
        {
            "Element",
            "hide",
            "function() { this.style.display = 'none'; return this; }"
        },
        {
            "Element",
            "toggle",
            R"(function() {
                this.style.display = this.style.display === 'none' ? '' : 'none';
                return this;
            })"
        }
    };
}

std::string getRuntimeCode() const override {
    return "";  // 这个模块不需要运行时代码
}

CJMOD_JS_END()

// 示例 4: 异步增强模块
CJMOD_JS(AsyncEnhanced, "1.0.0")

std::string getDescription() const override {
    return "Enhanced async/await syntax";
}

std::vector<JSTransformRule> getTransformRules() const override {
    return {
        // async { ... }  →  (async () => { ... })()
        helpers::templateReplace(
            R"(async\s*\{)",
            "(async () => {",
            100
        ),
        {
            "async-block-end",
            std::regex(R"(\}\s*;?\s*//\s*async\s*end)"),
            [](const std::smatch&) { return "})();"; },
            99
        },
        
        // await* [p1, p2, p3]  →  await Promise.all([p1, p2, p3])
        helpers::templateReplace(
            R"(await\*\s*\[)",
            "await Promise.all([",
            90
        ),
        
        // await? promise  →  await promise.catch(() => null)
        helpers::templateReplace(
            R"(await\?\s+([^;]+))",
            "await ($1).catch(() => null)",
            80
        ),
        
        // timeout 1000 { ... }  →  setTimeout(() => { ... }, 1000)
        helpers::templateReplace(
            R"(timeout\s+(\d+)\s*\{)",
            "setTimeout(() => {",
            70
        ),
        
        // interval 1000 { ... }  →  setInterval(() => { ... }, 1000)
        helpers::templateReplace(
            R"(interval\s+(\d+)\s*\{)",
            "setInterval(() => {",
            60
        )
    };
}

std::string getRuntimeCode() const override {
    return R"(
// Async utilities
window.sleep = ms => new Promise(resolve => setTimeout(resolve, ms));

window.retry = async (fn, times = 3, delay = 1000) => {
    for (let i = 0; i < times; i++) {
        try {
            return await fn();
        } catch (e) {
            if (i === times - 1) throw e;
            await sleep(delay);
        }
    }
};

window.race = async (promises, timeout = 5000) => {
    return Promise.race([
        Promise.all(promises),
        sleep(timeout).then(() => {
            throw new Error('Timeout');
        })
    ]);
};
)";
}

std::string postprocessJS(const std::string& jsCode) override {
    // 自动添加 async 到包含 await 的函数
    std::regex functionPattern(R"(function\s+(\w+)\s*\([^)]*\)\s*\{[^}]*\bawait\b)");
    std::string result = std::regex_replace(jsCode, functionPattern, "async function $1(");
    
    // 箭头函数
    std::regex arrowPattern(R"(\(([^)]*)\)\s*=>\s*\{[^}]*\bawait\b)");
    result = std::regex_replace(result, arrowPattern, "async ($1) => {");
    
    return result;
}

CJMOD_JS_END()