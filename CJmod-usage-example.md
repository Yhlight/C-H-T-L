# CJmod 使用示例

## 理解 CJmod 的工作原理

CJmod **只能**在 CHTL JS 编译器层面工作，通过扫描切割机制转换 JavaScript 代码。

### 工作流程

```
CHTL 源文件
    ↓
CHTL 编译器 (C++)
    ↓
生成 HTML + CSS + JavaScript
    ↓
CHTL JS 编译器（扫描切割）← CJmod 在这里工作
    ↓
最终 JavaScript 输出
```

## 示例 1: 响应式编程

### CHTL 代码
```chtl
[Import] @CJmod Reactive;

div {
    script {
        // 响应式变量
        count := 0;
        doubled => count.value * 2;
        
        // 监听变化
        watch count {
            console.log("Count changed:", count.value);
        }
        
        // 使用
        {{#increment}}->onclick = () => {
            count.value++;
        };
    }
}
```

### CJmod 转换后的 JavaScript
```javascript
// 响应式系统运行时
const reactive = (value) => { /* ... */ };
const computed = (getter) => { /* ... */ };
const watch = (target, callback) => { /* ... */ };

// 转换后的代码
let count = reactive(0);
let doubled = computed(() => count.value * 2);

watch(count, () => {
    console.log("Count changed:", count.value);
});

document.getElementById('increment').onclick = () => {
    count.value++;
};
```

## 示例 2: 动画链

### CHTL 代码
```chtl
[Import] @CJmod AnimationChain;

div {
    script {
        // 链式动画
        {{#box}} ~> fadeIn(300) ~> slideDown(500);
        
        // 并行动画
        {{#box}} ~~ [
            fadeIn(300),
            slideDown(500)
        ];
        
        // 带延迟
        async {
            {{#box}} ~> fadeOut();
            delay(1000);
            {{#box}} ~> fadeIn();
        } // async end
    }
}
```

### CJmod 转换后
```javascript
// 动画链扩展
Element.prototype.chain = function() { /* ... */ };

// 转换后的代码
document.getElementById('box').chain().fadeIn(300).slideDown(500);

document.getElementById('box').parallel([
    fadeIn(300),
    slideDown(500)
]);

(async () => {
    document.getElementById('box').chain().fadeOut();
    await new Promise(r => setTimeout(r, 1000));
    document.getElementById('box').chain().fadeIn();
})();
```

## 示例 3: 查询增强

### CHTL 代码
```chtl
[Import] @CJmod QueryEnhanced;

div {
    script {
        // jQuery 风格查询
        let button = $('.btn-primary');
        let allButtons = $$('.btn');
        
        // 元素方法
        let parent = button.parent();
        let siblings = button.siblings();
        let child = button.find('.icon');
    }
}
```

### CJmod 转换后
```javascript
// 查询增强运行时
window.$ = (selector) => document.querySelector(selector);
window.$$ = (selector) => Array.from(document.querySelectorAll(selector));

// 转换后的代码
let button = document.querySelector('.btn-primary');
let allButtons = Array.from(document.querySelectorAll('.btn'));

let parent = button.parentElement;
let siblings = button.siblings();
let child = button.querySelector('.icon');
```

## 示例 4: 异步语法糖

### CHTL 代码
```chtl
[Import] @CJmod AsyncSugar;

div {
    script {
        // 立即执行异步块
        async {
            let data = await? fetch('/api/data');
            if (data) {
                console.log(data);
            }
        } // async end
        
        // 等待多个 Promise
        let results = await* [
            fetch('/api/user'),
            fetch('/api/posts'),
            fetch('/api/comments')
        ];
        
        // 重试机制
        retry 3 times {
            return await fetch('/api/flaky-endpoint');
        }
    }
}
```

## 示例 5: 调试增强

### CHTL 代码
```chtl
[Import] @CJmod DebugEnhanced;

div {
    script {
        let user = { name: "John", age: 30 };
        
        // 简化日志
        log user;
        
        // 调试块（只在调试模式下执行）
        debug {
            console.log("Detailed info:", user);
            trace();
        }
        
        // 断言
        assert user.age > 0, "Age must be positive";
        
        // 元素调试
        {{#myDiv}}.debug();
    }
}
```

## CJmod 的限制

1. **只能处理 JavaScript 代码**
   - 不能修改 HTML 结构
   - 不能修改 CSS 样式
   - 不能添加新的 CHTL 语法（如 `[Template]`）

2. **只能通过文本替换工作**
   - 使用正则表达式扫描
   - 简单的字符串替换
   - 不能访问 AST

3. **只能在 script 块内工作**
   - 不能处理属性中的 JS 代码
   - 不能处理事件处理器

## 创建自定义 CJmod

```cpp
#include "CJmod/CJmodCorrect.h"

DEFINE_CJMOD(MyModule, "1.0.0")

std::vector<ScanCutRule> getScanCutRules() const override {
    return {
        {
            "my-syntax",
            std::regex(R"(my_pattern)"),
            "replacement",
            100  // 优先级
        }
    };
}

std::vector<RuntimeInjection> getRuntimeInjections() const override {
    return {
        {
            "// My runtime code",
            "before"  // 或 "after"
        }
    };
}

END_CJMOD
```

## 最佳实践

1. **保持简单** - CJmod 最适合简单的语法糖和运行时扩展
2. **避免复杂的正则** - 过于复杂的模式可能导致意外匹配
3. **使用优先级** - 合理设置优先级避免冲突
4. **测试充分** - 确保转换不会破坏现有代码
5. **文档清晰** - 明确说明新语法的用法和限制