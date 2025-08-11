# CHTL Script块使用指南

## 概述

Script块是CHTL的重大新特性，允许在CHTL文件中直接嵌入JavaScript代码。与Style块类似，Script块提供了局部作用域的JavaScript执行环境，支持模块化、异步执行和依赖管理。

## 基本语法

```chtl
[Script] {
    // JavaScript代码
    console.log("Hello from CHTL!");
}
```

## Script块类型

### 1. 内联脚本（默认）
```chtl
[Script] {
    // 立即执行的内联脚本，封装在IIFE中
    const localVar = "只在此作用域内可见";
}
```

### 2. 命名脚本
```chtl
[Script] @MyScript {
    // 可以被引用和调用的命名脚本
    function doSomething() {
        console.log("Doing something...");
    }
}
```

### 3. 模块脚本
```chtl
[Script] @Utils type="module" {
    // ES6模块风格，支持导出
    function helper() { 
        return "helped!"; 
    }
    
    exports.helper = helper;
}
```

### 4. 作用域脚本
```chtl
[Script] @ComponentLogic scope="MyComponent" {
    // 在特定作用域内执行
    // $scope 参数自动注入
    $scope.data = [];
    $scope.methods = {};
}
```

### 5. 全局脚本（慎用）
```chtl
[Script] type="global" {
    // 在全局作用域执行，没有封装
    window.globalVar = "可全局访问";
}
```

## 执行时机

### 立即执行（默认）
```chtl
[Script] {
    console.log("立即执行");
}
```

### 延迟执行
```chtl
[Script] defer {
    console.log("其他脚本执行完后执行");
}
```

### DOM加载后执行
```chtl
[Script] onmount {
    // 等同于 DOMContentLoaded
    document.querySelector('#app').classList.add('ready');
}
```

### 页面加载完成后执行
```chtl
[Script] onload {
    // 等同于 window.onload
    console.log("所有资源加载完成");
}
```

### 按需执行
```chtl
[Script] @Validator ondemand {
    // 不会自动执行，需要手动调用
    return {
        validate: (value) => value.length > 0
    };
}

// 调用方式
[Script] {
    const validator = window.CHTL.executeScript('Validator');
}
```

## 高级特性

### 1. 异步执行
```chtl
[Script] @DataLoader async {
    const response = await fetch('/api/data');
    const data = await response.json();
    return data;
}
```

### 2. 依赖管理
```chtl
[Script] @App depends="Utils,Config" {
    // 依赖Utils和Config脚本
    // 确保它们先执行
}
```

### 3. 在组件中使用
```chtl
[Custom] @Element MyComponent {
    // 组件级Script
    [Script] {
        let state = { count: 0 };
        
        this.increment = () => {
            state.count++;
            this.update();
        };
    }
    
    render: {
        div {
            // 元素级Script
            [Script] {
                this.addEventListener('click', () => {
                    console.log('Clicked!');
                });
            }
        }
    }
}
```

## 最佳实践

### 1. 使用命名空间
```chtl
[Script] @MyModule type="module" {
    // 避免全局污染
    const privateVar = "hidden";
    
    exports.publicAPI = {
        method: () => privateVar
    };
}
```

### 2. 错误处理
```chtl
[Script] {
    try {
        // 可能出错的代码
        riskyOperation();
    } catch (error) {
        console.error('Script error:', error);
    }
}
```

### 3. 性能优化
```chtl
// 使用defer避免阻塞
[Script] @HeavyComputation defer {
    // 复杂计算
}

// 按需加载
[Script] @LazyFeature ondemand {
    // 只在需要时执行
}
```

### 4. 模块化组织
```chtl
// 工具模块
[Script] @Utils type="module" {
    exports.debounce = (fn, delay) => {
        let timeoutId;
        return (...args) => {
            clearTimeout(timeoutId);
            timeoutId = setTimeout(() => fn(...args), delay);
        };
    };
}

// 业务逻辑
[Script] @Business depends="Utils" {
    const utils = window.CHTL.modules.Utils;
    const debouncedSave = utils.debounce(saveData, 1000);
}
```

## Script执行环境

所有Script块都在CHTL执行环境中运行，该环境提供：

- `window.CHTL` - 全局CHTL命名空间
- `window.CHTL.modules` - 模块存储
- `window.CHTL.scripts` - 脚本注册表
- `window.CHTL.executeScript(name)` - 执行命名脚本
- `window.CHTL.loadModule(name)` - 加载模块

## 与其他特性的集成

### 与Style块配合
```chtl
[Style] @AnimationStyles {
    .fade-in {
        opacity: 0;
        transition: opacity 0.3s ease;
    }
    .visible { opacity: 1; }
}

[Script] @AnimationController {
    function fadeIn(element) {
        element.classList.add('fade-in');
        setTimeout(() => {
            element.classList.add('visible');
        }, 10);
    }
    
    exports.fadeIn = fadeIn;
}
```

### 与Template配合
```chtl
[Template] @DataList(items) {
    ul {
        [Script] {
            // 模板内的脚本
            this.renderItems = (items) => {
                this.innerHTML = items.map(item => 
                    `<li>${item.name}</li>`
                ).join('');
            };
            
            this.renderItems(items);
        }
    }
}
```

## 注意事项

1. **作用域隔离**：除非使用`type="global"`，否则所有变量都是局部的
2. **执行顺序**：遵循依赖关系和执行时机设置
3. **错误处理**：Script错误不会影响其他Script的执行
4. **性能考虑**：大量Script可能影响页面性能，合理使用defer和ondemand
5. **安全性**：避免直接执行用户输入的代码

## 总结

Script块为CHTL带来了强大的动态能力，使其成为一个完整的前端开发语言。通过合理使用Script块的各种特性，可以构建功能丰富、结构清晰的Web应用。