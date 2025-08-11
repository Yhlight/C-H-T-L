# CJmod 构建器 API 使用示例

## 1. 使用构建器创建动画模块

```cpp
#include "CJmod/CJmodBuilder.h"

// 使用流式 API 创建动画模块
auto animateModule = cjmod::createModule("animate", "2.0.0")
    .description("Enhanced animation module with builder API")
    
    // 添加动画链语法: element ~> fadeIn(300)
    .syntax(R"((\w+|\{\{[^}]+\}\})\s*~>\s*(\w+)\s*\()", 
            cjmod::transforms::template_("$1.animate().$2("))
    
    // 添加并行动画语法: element ~~ { ... }
    .syntax(R"((\w+|\{\{[^}]+\}\})\s*~~\s*\{)", "$1.animateParallel({")
    
    // 添加延迟语法
    .syntax(R"(delay\s*\(\s*(\d+)\s*\))", 
            [](const std::smatch& m) {
                return "await new Promise(r => setTimeout(r, " + m[1].str() + "))";
            })
    
    // 添加方法
    .method("Element", "fadeIn", R"(
        function(duration = 300) {
            this.style.opacity = '0';
            this.style.display = 'block';
            this.style.transition = `opacity ${duration}ms`;
            
            requestAnimationFrame(() => {
                this.style.opacity = '1';
            });
            
            return new Promise(resolve => setTimeout(resolve, duration));
        }
    )")
    
    .method("Element", "fadeOut", R"(
        function(duration = 300) {
            this.style.transition = `opacity ${duration}ms`;
            this.style.opacity = '0';
            
            return new Promise(resolve => {
                setTimeout(() => {
                    this.style.display = 'none';
                    resolve();
                }, duration);
            });
        }
    )")
    
    // 添加链式动画支持
    .runtime(R"(
        Element.prototype.animate = function() {
            const element = this;
            const queue = [];
            
            const animator = {
                fadeIn: function(duration) {
                    queue.push(() => element.fadeIn(duration));
                    return this;
                },
                fadeOut: function(duration) {
                    queue.push(() => element.fadeOut(duration));
                    return this;
                },
                execute: async function() {
                    for (const fn of queue) {
                        await fn();
                    }
                }
            };
            
            setTimeout(() => animator.execute(), 0);
            return animator;
        };
    )")
    
    .build();

// 注册模块
CJmodProcessor::getInstance().registerModule(std::move(animateModule));
```

## 2. 创建响应式模块的简化版本

```cpp
// 更简洁的响应式模块
auto reactiveModule = cjmod::createModule("reactive-simple")
    .description("Simplified reactive programming")
    
    // 响应式赋值: count := 0
    .syntax(R"((\w+)\s*:=\s*(.+);)", "const $1 = reactive($2);")
    
    // 计算属性: doubled => count * 2
    .syntax(R"((\w+)\s*=>\s*(.+);)", "const $1 = computed(() => $2);")
    
    // 监听器: watch count { ... }
    .syntax(R"(watch\s+(\w+)\s*\{)", "watch($1, () => {")
    
    // 运行时代码从文件加载
    .runtimeFile("reactive-runtime.js")
    
    // 添加双向绑定方法
    .method("Element", "model", R"(
        function(varName) {
            const variable = window[varName];
            
            this.addEventListener('input', e => {
                if (variable && variable.set) {
                    variable.set(e.target.value);
                }
            });
            
            if (variable && variable.subscribe) {
                variable.subscribe(val => {
                    this.value = val;
                });
            }
            
            return this;
        }
    )")
    
    .build();
```

## 3. 创建 jQuery 风格的查询模块

```cpp
// 使用预定义的转换器
auto jqueryModule = cjmod::createModule("jquery-lite")
    .description("jQuery-style DOM manipulation")
    
    // $ 函数
    .syntax(R"(\$\s*\(\s*["']([^"']+)["']\s*\))", "new QueryWrapper('$1')")
    
    // 扩展选择器
    .syntax(R"(\{\{:first\}\})", "document.querySelector")
    .syntax(R"(\{\{:last\}\})", "Array.from(document.querySelectorAll('*')).pop()")
    .syntax(R"(\{\{:even\}\})", "Array.from(document.querySelectorAll('*')).filter((_, i) => i % 2 === 0)")
    
    // 添加链式方法
    .method("QueryWrapper", "each", R"(
        function(callback) {
            this.elements.forEach((el, index) => {
                callback.call(el, index, el);
            });
            return this;
        }
    )")
    
    .method("QueryWrapper", "css", R"(
        function(prop, value) {
            if (typeof prop === 'object') {
                this.each(function() {
                    Object.assign(this.style, prop);
                });
            } else if (value !== undefined) {
                this.each(function() {
                    this.style[prop] = value;
                });
            } else {
                return this.elements[0]?.style[prop];
            }
            return this;
        }
    )")
    
    // 事件处理快捷方法
    .method("QueryWrapper", "click", cjmod::methods::eventHandler("click"))
    .method("QueryWrapper", "hover", R"(
        function(enterFn, leaveFn) {
            return this
                .on('mouseenter', enterFn)
                .on('mouseleave', leaveFn || enterFn);
        }
    )")
    
    .runtime(R"(
        class QueryWrapper {
            constructor(selector) {
                if (typeof selector === 'string') {
                    this.elements = Array.from(document.querySelectorAll(selector));
                } else if (selector instanceof NodeList) {
                    this.elements = Array.from(selector);
                } else {
                    this.elements = [selector];
                }
            }
            
            get length() { return this.elements.length; }
            get(index) { return this.elements[index]; }
        }
        
        window.$ = function(selector) {
            return new QueryWrapper(selector);
        };
    )")
    
    .build();
```

## 4. 创建异步操作模块

```cpp
auto asyncModule = cjmod::createModule("async-helpers")
    .description("Async/await helpers and utilities")
    
    // async 块语法: async { ... }
    .syntax(R"(async\s*\{)", "(async () => {")
    .syntax(R"(\}\s*;)", "})();")
    
    // await 链式调用: await* promises
    .syntax(R"(await\*\s*\[)", "await Promise.all([")
    
    // 超时语法: timeout(1000) { ... }
    .syntax(R"(timeout\s*\(\s*(\d+)\s*\)\s*\{)", 
            [](const std::smatch& m) {
                return "setTimeout(() => {";
            })
    
    // 异步方法
    .asyncMethod("Element", "waitFor", R"(
        async function(condition, timeout = 5000) {
            const start = Date.now();
            
            while (!condition()) {
                if (Date.now() - start > timeout) {
                    throw new Error('Timeout waiting for condition');
                }
                await new Promise(r => setTimeout(r, 100));
            }
            
            return this;
        }
    )")
    
    .asyncMethod("Element", "animateAsync", R"(
        async function(props, duration = 300) {
            const transitions = Object.keys(props)
                .map(prop => `${prop} ${duration}ms`)
                .join(', ');
            
            this.style.transition = transitions;
            
            Object.assign(this.style, props);
            
            await new Promise(r => setTimeout(r, duration));
            this.style.transition = '';
            
            return this;
        }
    )")
    
    // 工具函数
    .runtime(R"(
        window.sleep = ms => new Promise(r => setTimeout(r, ms));
        
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
        
        window.throttle = (fn, ms) => {
            let timeout;
            return (...args) => {
                clearTimeout(timeout);
                timeout = setTimeout(() => fn(...args), ms);
            };
        };
    )")
    
    .build();
```

## 5. 创建表单验证模块

```cpp
auto validationModule = cjmod::createModule("form-validation")
    .description("Form validation with custom syntax")
    
    // 验证规则语法: @validate required, email
    .syntax(R"(@validate\s+([^;]+);)", 
            [](const std::smatch& m) {
                std::string rules = m[1].str();
                return "this.validation = new Validator(this, '" + rules + "');";
            })
    
    // 条件验证: @validate-if condition { ... }
    .syntaxWhen(R"(@validate-if\s+([^{]+)\s*\{)",
                [](const std::smatch& m) {
                    return "if (" + m[1].str() + ") { this.validation = {";
                },
                [](const std::string& context) {
                    // 只在 script 块中应用
                    return context.find("script") != std::string::npos;
                })
    
    // 验证方法
    .method("Element", "validate", R"(
        function(rules) {
            if (!this.validation) {
                this.validation = new Validator(this, rules);
            }
            return this.validation.check();
        }
    )")
    
    .method("Element", "isValid", R"(
        function() {
            return this.validation ? this.validation.isValid() : true;
        }
    )")
    
    .method("Element", "getErrors", R"(
        function() {
            return this.validation ? this.validation.errors : [];
        }
    )")
    
    .runtime(R"(
        class Validator {
            constructor(element, rules) {
                this.element = element;
                this.rules = this.parseRules(rules);
                this.errors = [];
                
                // 自动绑定事件
                element.addEventListener('blur', () => this.check());
                element.addEventListener('input', () => {
                    if (this.errors.length > 0) {
                        this.check();
                    }
                });
            }
            
            parseRules(rulesStr) {
                return rulesStr.split(',').map(r => r.trim());
            }
            
            check() {
                this.errors = [];
                const value = this.element.value;
                
                for (const rule of this.rules) {
                    if (rule === 'required' && !value) {
                        this.errors.push('This field is required');
                    } else if (rule === 'email' && value) {
                        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
                        if (!emailRegex.test(value)) {
                            this.errors.push('Invalid email address');
                        }
                    } else if (rule.startsWith('min:')) {
                        const min = parseInt(rule.split(':')[1]);
                        if (value.length < min) {
                            this.errors.push(`Minimum ${min} characters required`);
                        }
                    }
                }
                
                this.updateUI();
                return this.errors.length === 0;
            }
            
            isValid() {
                return this.errors.length === 0;
            }
            
            updateUI() {
                if (this.errors.length > 0) {
                    this.element.classList.add('error');
                    this.element.classList.remove('valid');
                } else {
                    this.element.classList.add('valid');
                    this.element.classList.remove('error');
                }
            }
        }
    )")
    
    .build();
```

## 6. 使用构建器 API 的完整示例

```cpp
#include "CJmod/CJmodBuilder.h"
#include "CJmod/CJmodProcessor.h"

void registerCustomModules() {
    auto& processor = CJmodProcessor::getInstance();
    
    // 1. 创建状态管理模块
    auto stateModule = cjmod::createModule("state-management")
        .description("Simple state management")
        
        // 状态定义: state AppState { ... }
        .syntax(R"(state\s+(\w+)\s*\{)", "const $1 = createState({")
        
        // 动作定义: action increment() { ... }
        .syntax(R"(action\s+(\w+)\s*\(\)\s*\{)", "$1: function() {")
        
        // 获取器定义: getter total => ...
        .syntax(R"(getter\s+(\w+)\s*=>\s*(.+);)", "$1: function() { return $2; },")
        
        // 订阅语法: subscribe(state) { ... }
        .syntax(R"(subscribe\s*\(\s*(\w+)\s*\)\s*\{)", "$1.subscribe(() => {")
        
        .runtime(R"(
            function createState(config) {
                const state = { ...config };
                const subscribers = new Set();
                
                const proxy = new Proxy(state, {
                    set(target, prop, value) {
                        if (target[prop] !== value) {
                            target[prop] = value;
                            subscribers.forEach(fn => fn());
                        }
                        return true;
                    }
                });
                
                proxy.subscribe = fn => {
                    subscribers.add(fn);
                    return () => subscribers.delete(fn);
                };
                
                return proxy;
            }
        )")
        
        .build();
    
    // 2. 创建调试模块
    auto debugModule = cjmod::createModule("debug-tools")
        .description("Development debugging tools")
        
        // 日志语法: log "message", variable
        .syntax(R"(log\s+(.+);)", "console.log($1);")
        
        // 断言语法: assert condition, "message"
        .syntax(R"(assert\s+([^,]+),\s*(.+);)", 
                "console.assert($1, $2);")
        
        // 性能测量: measure { ... }
        .syntax(R"(measure\s*\{)", 
                "const __start = performance.now(); try {")
        .syntax(R"(\}\s*//\s*endmeasure)", 
                "} finally { console.log('Execution time:', performance.now() - __start, 'ms'); }")
        
        // 条件日志
        .syntaxWhen(R"(logif\s+([^,]+),\s*(.+);)",
                    [](const std::smatch& m) {
                        return "if (" + m[1].str() + ") console.log(" + m[2].str() + ");";
                    },
                    [](const std::string&) { return true; },
                    100)
        
        .method("Element", "debug", R"(
            function() {
                console.group('Element Debug:', this);
                console.log('Tag:', this.tagName);
                console.log('ID:', this.id);
                console.log('Classes:', this.className);
                console.log('Attributes:', Array.from(this.attributes));
                console.log('Children:', this.children.length);
                console.log('Parent:', this.parentElement);
                console.groupEnd();
                return this;
            }
        )")
        
        .build();
    
    // 3. 创建网络请求模块
    auto httpModule = cjmod::createModule("http-enhanced")
        .description("Enhanced HTTP requests")
        
        // GET 请求: get "url" -> response
        .syntax(R"(get\s+["']([^"']+)["']\s*->\s*(\w+))", 
                "const $2 = await fetch('$1').then(r => r.json())")
        
        // POST 请求: post "url" with data -> response
        .syntax(R"(post\s+["']([^"']+)["']\s+with\s+(\w+)\s*->\s*(\w+))",
                [](const std::smatch& m) {
                    return "const " + m[3].str() + " = await fetch('" + m[1].str() + 
                           "', { method: 'POST', body: JSON.stringify(" + m[2].str() + 
                           "), headers: { 'Content-Type': 'application/json' } }).then(r => r.json())";
                })
        
        .asyncMethod("Window", "api", R"(
            async function(endpoint, options = {}) {
                const baseURL = window.API_BASE_URL || '';
                const url = baseURL + endpoint;
                
                const defaultOptions = {
                    headers: {
                        'Content-Type': 'application/json',
                        ...options.headers
                    }
                };
                
                const response = await fetch(url, { ...defaultOptions, ...options });
                
                if (!response.ok) {
                    throw new Error(`HTTP ${response.status}: ${response.statusText}`);
                }
                
                return response.json();
            }
        )")
        
        .build();
    
    // 注册所有模块
    processor.registerModule(std::move(stateModule));
    processor.registerModule(std::move(debugModule));
    processor.registerModule(std::move(httpModule));
}

// 使用示例
int main() {
    registerCustomModules();
    
    // 也可以动态创建和注册
    auto customModule = cjmod::createModule("my-custom", "1.0.0")
        .description("My custom module")
        .syntax("foo", "bar")
        .method("Element", "myMethod", "function() { return 'Hello!'; }")
        .build();
    
    CJmodProcessor::getInstance().registerModule(std::move(customModule));
    
    return 0;
}
```

## 7. CHTL 中使用这些模块

```chtl
[Import] @CJmod state-management
[Import] @CJmod debug-tools
[Import] @CJmod http-enhanced

body {
    // 使用状态管理
    script {
        state AppState {
            count: 0,
            items: [],
            
            action increment() {
                this.count++;
            },
            
            action addItem(item) {
                this.items.push(item);
            },
            
            getter total => this.items.length
        }
        
        subscribe(AppState) {
            log "State changed:", AppState;
            {{#counter}}.textContent = AppState.count;
        };
    }
    
    div {
        id: "app";
        
        button {
            text { "增加" }
            script {
                {{&}}->listen("click", () => {
                    measure {
                        AppState.increment();
                        logif AppState.count > 10, "Count is high!";
                    } // endmeasure
                });
                
                // 调试元素
                {{&}}->debug();
            }
        }
        
        button {
            text { "加载数据" }
            script {
                {{&}}->listen("click", async () => {
                    // 使用增强的 HTTP 语法
                    get "/api/users" -> users;
                    
                    users.forEach(user => {
                        AppState.addItem(user);
                    });
                    
                    // 或使用 API 方法
                    const data = await window.api('/posts', {
                        method: 'GET'
                    });
                    
                    log "Loaded posts:", data;
                });
            }
        }
        
        div {
            id: "counter";
            text { "0" }
        }
    }
}
```

## 总结

CJmod 构建器 API 提供了：

1. **流式接口** - 链式调用，代码更优雅
2. **简化的语法定义** - 支持简单字符串替换和复杂转换
3. **预定义的转换器** - 常用模式的快速实现
4. **方法模板** - 快速创建标准方法
5. **条件转换** - 根据上下文应用不同的转换
6. **运行时代码管理** - 支持内联代码和文件加载

这让创建 CJmod 变得更加简单和直观！