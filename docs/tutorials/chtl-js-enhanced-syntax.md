# CHTL JS增强语法指南

## 概述

CHTL JS是对JavaScript的增强，提供了更便捷的语法来处理DOM操作和事件管理。所有局部script块的代码都会被收集到一个统一的运行时环境中，避免全局污染。

## 核心特性

### 1. 选择器语法

使用 `{{selector}}` 语法来快速选择DOM元素：

```chtl
script {
    // 相当于 document.querySelector('#myDiv')
    {{"#myDiv"}}.style.color = 'red';
    
    // 相当于 document.querySelector('.my-class')
    {{".my-class"}}.addEventListener('click', handler);
}
```

### 2. 上下文引用

在局部script块中，`{{&}}` 表示包含该script块的元素：

```chtl
div {
    id: "container"
    
    script {
        // {{&}} 指向 div#container
        {{&}}.classList.add('initialized');
        
        // 等价于
        // document.getElementById('container').classList.add('initialized');
    }
}
```

### 3. 事件委托语法

使用 `->delegate()` 语法实现事件委托，解决SPA中动态元素的事件绑定问题：

```chtl
script {
    {{父元素选择器}}->delegate({
        target: 子元素选择器 | [选择器数组],
        事件名: 处理函数,
        // 可以定义多个事件
    });
}
```

## 事件委托详解

### 基本用法

```chtl
script {
    // 单个目标选择器
    {{"#list"}}->delegate({
        target: ".item",
        click: function(e) {
            // this 指向触发事件的 .item 元素
            this.classList.toggle('selected');
        }
    });
}
```

### 多目标选择器

```chtl
script {
    // 多个目标选择器
    {{"#container"}}->delegate({
        target: [".btn-primary", ".btn-secondary"],
        click: function(e) {
            console.log('Button clicked:', this.className);
        }
    });
}
```

### 多事件处理

```chtl
script {
    {{"#grid"}}->delegate({
        target: ".grid-item",
        mouseenter: function(e) {
            this.style.backgroundColor = '#f0f0f0';
        },
        mouseleave: function(e) {
            this.style.backgroundColor = '';
        },
        click: function(e) {
            this.classList.toggle('active');
        }
    });
}
```

### 使用{{&}}进行委托

```chtl
div {
    id: "card-container"
    
    script {
        // 使用 {{&}} 作为委托父元素
        {{&}}->delegate({
            target: ".card",
            click: function(e) {
                // 处理卡片点击
            }
        });
    }
}
```

## 运行时环境

### 全局命名空间

所有CHTL JS代码都在 `window.CHTL` 命名空间下运行：

```javascript
window.CHTL = {
    runtime: {},     // 运行时管理
    modules: {},     // 模块存储
    scripts: {},     // 脚本注册表
    delegate: fn,    // 事件委托函数
    $: fn,          // 选择器辅助函数
    $$: fn          // 选择所有元素
}
```

### 局部脚本收集

所有局部script块的代码会被自动收集并包装在IIFE中执行：

```chtl
div {
    script {
        // 这段代码会被包装成：
        // (function() {
        //   'use strict';
        //   const element = document.getElementById('生成的ID');
        //   const {{&}} = element;
        //   // 你的代码
        // })();
    }
}
```

### 事件委托优化

事件委托会自动检查并避免重复绑定：

- 相同父元素、相同目标选择器、相同事件类型的委托只会绑定一次
- 委托信息存储在父元素的 `__delegations` 属性中
- 支持动态添加的元素，无需重新绑定

## 最佳实践

### 1. 使用事件委托处理动态内容

```chtl
ul {
    id: "todo-list"
    
    script {
        // 使用委托处理所有todo项，包括未来添加的
        {{&}}->delegate({
            target: ".todo-item",
            click: function(e) {
                this.classList.toggle('completed');
            }
        });
        
        // 动态添加项目无需重新绑定事件
        function addTodo(text) {
            const li = document.createElement('li');
            li.className = 'todo-item';
            li.textContent = text;
            {{&}}.appendChild(li);
        }
    }
}
```

### 2. 合理使用选择器语法

```chtl
script {
    // 好的做法：缓存选择结果
    const container = {{"#container"}};
    const items = container.querySelectorAll('.item');
    
    // 避免重复选择
    items.forEach(item => {
        // 处理每个项目
    });
}
```

### 3. 组织事件处理

```chtl
script {
    // 将相关的事件委托组织在一起
    const containerEl = {{"#app"}};
    
    // 按钮事件
    containerEl->delegate({
        target: ".btn",
        click: handleButtonClick,
        mouseenter: handleButtonHover,
        mouseleave: handleButtonLeave
    });
    
    // 表单事件
    containerEl->delegate({
        target: "input, textarea",
        focus: handleFocus,
        blur: handleBlur,
        input: handleInput
    });
    
    // 定义处理函数
    function handleButtonClick(e) {
        // ...
    }
}
```

### 4. 错误处理

```chtl
script {
    try {
        const element = {{"#may-not-exist"}};
        if (element) {
            // 安全操作
        }
    } catch (error) {
        console.error('Element operation failed:', error);
    }
}
```

## 注意事项

1. **选择器性能**：`{{selector}}` 语法会转换为 `document.querySelector`，频繁使用时应缓存结果
2. **事件冒泡**：事件委托依赖事件冒泡，不支持不冒泡的事件（如 focus、blur）
3. **this上下文**：在委托的事件处理函数中，`this` 指向触发事件的目标元素
4. **内存管理**：事件委托绑定在父元素上，父元素被移除时委托会自动清理

## 与原生JavaScript的对比

| CHTL JS语法 | 等价的JavaScript |
|------------|-----------------|
| `{{"#id"}}` | `document.querySelector("#id")` |
| `{{&}}` | 当前元素引用 |
| `->delegate({...})` | 手动实现的事件委托 |

## 总结

CHTL JS增强语法通过简化DOM操作和提供强大的事件委托机制，让开发者能够更轻松地构建动态、交互丰富的Web应用。所有增强功能都建立在标准JavaScript之上，确保了兼容性和性能。