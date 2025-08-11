# CJmod 完整示例集合

## 1. 动画模块 (AnimateModule)

### C++ 实现

```cpp
#include "CJmod/CJmodInterface.h"

namespace chtl {
namespace cjmod {

class AnimateModule : public ICJmod {
public:
    std::string getName() const override {
        return "animate";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::string getDescription() const override {
        return "Smooth animations with chaining support";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 动画链语法: element ~> fadeIn(300) ~> slideDown(500)
        rules.push_back({
            "animation-chain",
            std::regex(R"((\w+|\{\{[^}]+\}\})\s*~>\s*(\w+)\s*\()"),
            100,
            [](const std::smatch& match) {
                return match[1].str() + ".animate()." + match[2].str() + "(";
            },
            nullptr
        });
        
        // 并行动画: element ~~ { opacity: 0, height: 0 }
        rules.push_back({
            "parallel-animation",
            std::regex(R"((\w+|\{\{[^}]+\}\})\s*~~\s*\{)"),
            95,
            [](const std::smatch& match) {
                return match[1].str() + ".animateParallel({";
            },
            nullptr
        });
        
        // 延迟语法: delay(500)
        rules.push_back({
            "delay-syntax",
            std::regex(R"(delay\s*\(\s*(\d+)\s*\))"),
            90,
            [](const std::smatch& match) {
                return "await new Promise(r => setTimeout(r, " + match[1].str() + "))";
            },
            nullptr
        });
        
        return rules;
    }
    
    std::vector<MethodInjection> getMethodInjections() const override {
        return {
            {
                "Element",
                "animate",
                R"(function() {
                    const element = this;
                    const queue = [];
                    
                    const animator = {
                        fadeIn(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                element.style.opacity = '0';
                                element.style.display = 'block';
                                element.style.transition = `opacity ${duration}ms`;
                                
                                requestAnimationFrame(() => {
                                    element.style.opacity = '1';
                                    setTimeout(resolve, duration);
                                });
                            }));
                            return this;
                        },
                        
                        fadeOut(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                element.style.transition = `opacity ${duration}ms`;
                                element.style.opacity = '0';
                                setTimeout(() => {
                                    element.style.display = 'none';
                                    resolve();
                                }, duration);
                            }));
                            return this;
                        },
                        
                        slideDown(duration = 300) {
                            queue.push(() => new Promise(resolve => {
                                const height = element.scrollHeight;
                                element.style.height = '0';
                                element.style.overflow = 'hidden';
                                element.style.display = 'block';
                                element.style.transition = `height ${duration}ms`;
                                
                                requestAnimationFrame(() => {
                                    element.style.height = height + 'px';
                                    setTimeout(() => {
                                        element.style.height = '';
                                        element.style.overflow = '';
                                        resolve();
                                    }, duration);
                                });
                            }));
                            return this;
                        },
                        
                        async execute() {
                            for (const animation of queue) {
                                await animation();
                            }
                        }
                    };
                    
                    setTimeout(() => animator.execute(), 0);
                    return animator;
                })",
                false
            }
        };
    }
};

} // namespace cjmod
} // namespace chtl
```

### CHTL 使用示例

```chtl
[Import] @CJmod animate

body {
    nav {
        id: "menu";
        style { display: none; }
        
        script {
            // 使用动画链
            window.showMenu = () => {
                {{&}} ~> fadeIn(300) ~> slideDown(500);
            };
            
            window.hideMenu = () => {
                {{&}} ~> slideUp(300) ~> fadeOut(200);
            };
        }
    }
    
    div {
        class: "card";
        script {
            {{&}}->listen("click", async () => {
                // 并行动画
                await {{&}} ~~ { 
                    opacity: 0.5, 
                    transform: "scale(0.8)"
                };
                
                delay(200);  // CJmod 提供的延迟语法
                
                await {{&}} ~~ { 
                    opacity: 1, 
                    transform: "scale(1)"
                };
            });
        }
    }
}
```

### 生成的 JavaScript

```javascript
// CJmod Runtime Generated Code
(function() {
  'use strict';

  // Module: animate
  Element.prototype.animate = function() {
    const element = this;
    const queue = [];
    
    const animator = {
        fadeIn(duration = 300) {
            queue.push(() => new Promise(resolve => {
                element.style.opacity = '0';
                element.style.display = 'block';
                element.style.transition = `opacity ${duration}ms`;
                
                requestAnimationFrame(() => {
                    element.style.opacity = '1';
                    setTimeout(resolve, duration);
                });
            }));
            return this;
        },
        // ... 其他方法
        
        async execute() {
            for (const animation of queue) {
                await animation();
            }
        }
    };
    
    setTimeout(() => animator.execute(), 0);
    return animator;
  };
})();

// 用户代码
window.showMenu = () => {
    document.getElementById('menu').animate().fadeIn(300).slideDown(500);
};

this.addEventListener("click", async () => {
    await this.animateParallel({ 
        opacity: 0.5, 
        transform: "scale(0.8)"
    });
    
    await new Promise(r => setTimeout(r, 200));  // delay 被转换
    
    await this.animateParallel({ 
        opacity: 1, 
        transform: "scale(1)"
    });
});
```

## 2. 查询增强模块 (QueryModule)

### C++ 实现

```cpp
class QueryModule : public ICJmod {
public:
    std::string getName() const override {
        return "query";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 扩展选择器: {{:visible}} -> 所有可见元素
        rules.push_back({
            "visible-selector",
            std::regex(R"(\{\{:visible\}\})"),
            110,
            [](const std::smatch& match) {
                return "document.querySelectorAll(':not([style*=\"display: none\"]):not([hidden])')";
            },
            nullptr
        });
        
        // 父元素选择器: {{^}} -> 当前元素的父元素
        rules.push_back({
            "parent-selector",
            std::regex(R"(\{\{\^\}\})"),
            105,
            [](const std::smatch& match) {
                return "this.parentElement";
            },
            nullptr
        });
        
        // 查询语法: $(".class") -> 返回 NodeList 包装器
        rules.push_back({
            "query-syntax",
            std::regex(R"(\$\s*\(\s*["']([^"']+)["']\s*\))"),
            95,
            [](const std::smatch& match) {
                return "new QueryList('" + match[1].str() + "')";
            },
            nullptr
        });
        
        return rules;
    }
    
    std::vector<MethodInjection> getMethodInjections() const override {
        return {
            {
                "Element",
                "find",
                R"(function(selector) {
                    return this.querySelector(selector);
                })",
                false
            },
            {
                "Element",
                "closest",
                R"(function(selector) {
                    let element = this;
                    while (element && element !== document) {
                        if (element.matches(selector)) {
                            return element;
                        }
                        element = element.parentElement;
                    }
                    return null;
                })",
                false
            }
        };
    }
};
```

### CHTL 使用示例

```chtl
[Import] @CJmod query

body {
    div {
        class: "item";
        script {
            // 使用新的选择器
            {{:visible}}.forEach(el => {
                el.style.border = "1px solid blue";
            });
            
            // 使用父元素选择器
            {{&}}->listen("click", () => {
                {{^}}.classList.add("has-active-child");
            });
            
            // 使用增强的查询方法
            const child = {{&}}->find(".child");
            const parent = {{&}}->closest(".container");
        }
    }
    
    script {
        // 使用 jQuery 风格的查询
        $(".item")
            .addClass("initialized")
            .on("click", function() {
                console.log("Item clicked");
            });
    }
}
```

## 3. 响应式模块 (ReactiveModule)

### C++ 实现

```cpp
class ReactiveModule : public ICJmod {
public:
    std::string getName() const override {
        return "reactive";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 响应式变量声明: count := 0
        rules.push_back({
            "reactive-declaration",
            std::regex(R"((\w+)\s*:=\s*(.+);)"),
            100,
            [](const std::smatch& match) {
                return "const " + match[1].str() + " = reactive(" + match[2].str() + ");";
            },
            nullptr
        });
        
        // 计算属性: doubled => count.value * 2
        rules.push_back({
            "computed-property",
            std::regex(R"((\w+)\s*=>\s*(.+);)"),
            90,
            [](const std::smatch& match) {
                return "const " + match[1].str() + " = computed(() => " + match[2].str() + ");";
            },
            nullptr
        });
        
        // 监听器: watch count -> { ... }
        rules.push_back({
            "watch-statement",
            std::regex(R"(watch\s+(\w+)\s*->\s*\{)"),
            80,
            [](const std::smatch& match) {
                return "watch(" + match[1].str() + ", () => {";
            },
            nullptr
        });
        
        return rules;
    }
    
    std::string getRuntimeCode() const override {
        return R"(
  function reactive(initialValue) {
    const subscribers = new Set();
    let value = initialValue;
    
    return {
      get value() { return value; },
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
    let cachedValue;
    let dirty = true;
    
    return {
      get value() {
        if (dirty) {
          cachedValue = computeFn();
          dirty = false;
        }
        return cachedValue;
      }
    };
  }
  
  function watch(target, callback) {
    if (target && target.subscribe) {
      return target.subscribe(callback);
    }
  }
)";
    }
};
```

### CHTL 使用示例

```chtl
[Import] @CJmod reactive

body {
    div {
        id: "app";
        
        script {
            // 响应式变量
            count := 0;
            name := "World";
            
            // 计算属性
            doubled => count.value * 2;
            greeting => `Hello, ${name.value}!`;
            
            // 监听变化
            watch count -> {
                {{#count-display}}.textContent = count.value;
                {{#doubled-display}}.textContent = doubled.value;
            };
            
            watch name -> {
                {{#greeting}}.textContent = greeting.value;
            };
        }
        
        button {
            text { "+" }
            script {
                {{&}}->listen("click", () => {
                    count.value++;
                });
            }
        }
        
        input {
            type: "text";
            script {
                {{&}}->bindModel("name");
            }
        }
    }
}
```

## 4. 语法覆写示例

### C++ 实现 - 覆写 {{&}} 语法

```cpp
class EnhancedSelfReference : public ICJmod {
public:
    std::string getName() const override {
        return "enhanced-self";
    }
    
    void initialize() override {
        // 覆写官方的 {{&}} 语法
        TransformRule rule {
            "enhanced-self-reference",
            std::regex(R"(\{\{&\}\})"),
            1000,  // 最高优先级
            [](const std::smatch& match) {
                return "$(this)";  // 返回 jQuery 包装的对象
            },
            nullptr
        };
        
        CJmodProcessor::getInstance().overrideCHTLSyntax("self-reference", rule);
    }
    
    std::string getRuntimeCode() const override {
        return R"(
  function $(element) {
    if (typeof element === 'string') {
      return document.querySelector(element);
    }
    
    const wrapper = {
      el: element,
      addClass(className) {
        this.el.classList.add(className);
        return this;
      },
      removeClass(className) {
        this.el.classList.remove(className);
        return this;
      },
      on(event, handler) {
        this.el.addEventListener(event, handler);
        return this;
      }
    };
    
    return wrapper;
  }
)";
    }
};
```

### 使用示例

```chtl
[Import] @CJmod enhanced-self

body {
    div {
        script {
            // 现在 {{&}} 返回 jQuery 风格对象
            {{&}}
                .addClass("active")
                .on("click", () => console.log("Clicked!"))
                .on("mouseenter", () => {{&}}.addClass("hover"));
        }
    }
}
```

## 5. 组合使用多个模块

```chtl
[Import] @CJmod animate
[Import] @CJmod query
[Import] @CJmod reactive

body {
    div {
        id: "todo-app";
        
        script {
            // 响应式数据
            todos := [];
            filter := "all";
            
            // 计算属性
            filteredTodos => {
                if (filter.value === "active") {
                    return todos.value.filter(t => !t.completed);
                } else if (filter.value === "completed") {
                    return todos.value.filter(t => t.completed);
                }
                return todos.value;
            };
            
            // 监听变化
            watch filteredTodos -> {
                renderTodos();
            };
            
            // 渲染函数
            function renderTodos() {
                const list = {{#todo-list}};
                list.innerHTML = "";
                
                filteredTodos.value.forEach((todo, index) => {
                    const item = document.createElement("li");
                    item.textContent = todo.text;
                    
                    // 使用动画添加
                    list.appendChild(item);
                    $(item) ~> fadeIn(200);
                });
            }
            
            // 添加新 TODO
            window.addTodo = (text) => {
                todos.value = [...todos.value, { text, completed: false }];
                
                // 显示通知
                {{#notification}} ~> fadeIn() ~> delay(2000) ~> fadeOut();
            };
        }
        
        // 使用查询模块功能
        script {
            // 批量操作所有可见的 TODO 项
            $(".todo-item:visible")
                .addClass("processed")
                .on("click", function() {
                    $(this) ~~ { 
                        opacity: 0.5,
                        textDecoration: "line-through"
                    };
                });
        }
    }
}
```

## 6. 工厂类使用示例

```cpp
// 在 main.cpp 中
#include "CJmod/CJmodProcessor.h"
#include "examples/CJmod/AnimateModule.cpp"
#include "examples/CJmod/QueryModule.cpp"
#include "examples/CJmod/ReactiveModule.cpp"

int main() {
    // 获取 CJmod 处理器实例
    auto& processor = CJmodProcessor::getInstance();
    
    // 注册内置模块
    processor.registerModule(std::make_unique<AnimateModule>());
    processor.registerModule(std::make_unique<QueryModule>());
    processor.registerModule(std::make_unique<ReactiveModule>());
    
    // 注册模块工厂（延迟加载）
    processor.registerFactory(std::make_unique<AnimateModuleFactory>());
    
    // 从动态库加载模块
    #ifdef __linux__
    loadCJmodFromLibrary("/usr/local/lib/cjmod/custom-module.so");
    #endif
    
    // 编译 CHTL 文件...
}
```

## 7. 创建自定义 CJmod

### 步骤 1: 实现接口

```cpp
#include "CJmod/CJmodInterface.h"

class MyCustomModule : public ICJmod {
public:
    std::string getName() const override {
        return "my-custom";
    }
    
    std::string getVersion() const override {
        return "1.0.0";
    }
    
    std::vector<TransformRule> getTransformRules() const override {
        std::vector<TransformRule> rules;
        
        // 添加自定义语法
        rules.push_back({
            "custom-syntax",
            std::regex(R"(myFunction\s*\()"),
            100,
            [](const std::smatch& match) {
                return "window.myCustomFunction(";
            },
            nullptr
        });
        
        return rules;
    }
    
    // 实现其他必需方法...
};
```

### 步骤 2: 编译为共享库

```bash
# 编译为共享库
g++ -shared -fPIC -o my-custom.so MyCustomModule.cpp -I/path/to/chtl/include

# 安装到系统目录
sudo cp my-custom.so /usr/local/lib/cjmod/
```

### 步骤 3: 在 CHTL 中使用

```chtl
[Import] @CJmod my-custom

body {
    script {
        // 使用自定义语法
        myFunction("Hello from custom module!");
    }
}
```

## 总结

CJmod 系统提供了强大而灵活的扩展机制：

1. **语法转换** - 通过正则表达式和转换函数添加新语法
2. **方法注入** - 向 DOM 对象添加新方法
3. **运行时代码** - 注入必要的支持函数
4. **语法覆写** - 可以覆写官方语法行为
5. **模块组合** - 多个模块可以协同工作
6. **动态加载** - 支持从共享库加载模块

开发者可以轻松创建自己的 CJmod 来扩展 CHTL JS 的功能！