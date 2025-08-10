# CHTL 局部Script块使用指南

## 概述

CHTL现在支持局部script块，语法与style块完全一致。使用 `script {}` 即可在任何元素或组件内嵌入JavaScript代码。

## 基本语法

```chtl
div {
    // 局部script块
    script {
        console.log("Hello from local script!");
    }
    
    // 局部style块
    style {
        div { color: blue; }
    }
}
```

## 特性对比

| 特性 | [Script] 块 | script {} 块 |
|------|------------|-------------|
| 语法 | `[Script] { ... }` | `script { ... }` |
| 位置 | 顶层或特定位置 | 任何元素内部 |
| 作用域 | 全局或指定作用域 | 元素局部作用域 |
| 执行时机 | 可配置（defer、async等） | 立即执行 |
| 命名 | 支持 `[Script] @Name` | 不支持命名 |
| 类型 | 可配置（module、global等） | 始终为内联类型 |

## 使用场景

### 1. 元素行为绑定

```chtl
button {
    id: "my-button"
    "点击我"
    
    script {
        // 直接在元素内绑定行为
        document.getElementById('my-button').addEventListener('click', () => {
            alert('按钮被点击了！');
        });
    }
}
```

### 2. 组件逻辑

```chtl
[Custom] @Element Toggle {
    props: {
        label: string = "Toggle"
    }
    
    render: {
        div {
            class: "toggle-component"
            
            button {
                class: "toggle-btn"
                props.label
            }
            
            div {
                class: "toggle-content"
                style: "display: none;"
                [children]
            }
            
            script {
                // 组件的交互逻辑
                const btn = this.querySelector('.toggle-btn');
                const content = this.querySelector('.toggle-content');
                
                btn.addEventListener('click', () => {
                    content.style.display = 
                        content.style.display === 'none' ? 'block' : 'none';
                });
            }
        }
    }
}
```

### 3. 数据初始化

```chtl
div {
    class: "data-container"
    id: "chart"
    
    script {
        // 初始化数据
        const data = [
            { label: 'A', value: 10 },
            { label: 'B', value: 20 },
            { label: 'C', value: 15 }
        ];
        
        // 存储到元素的dataset中
        const container = document.getElementById('chart');
        container.dataset.chartData = JSON.stringify(data);
    }
}
```

### 4. 动画和效果

```chtl
div {
    class: "animated-box"
    
    "悬停查看效果"
    
    script {
        const box = document.querySelector('.animated-box');
        
        box.addEventListener('mouseenter', () => {
            box.style.transform = 'scale(1.1) rotate(5deg)';
        });
        
        box.addEventListener('mouseleave', () => {
            box.style.transform = 'scale(1) rotate(0deg)';
        });
    }
    
    style {
        .animated-box {
            width: 200px;
            height: 100px;
            background: #67C3CC;
            color: white;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: transform 0.3s ease;
            cursor: pointer;
        }
    }
}
```

### 5. 表单验证

```chtl
form {
    id: "user-form"
    
    input {
        type: "email"
        id: "email"
        placeholder: "请输入邮箱"
    }
    
    span {
        id: "email-error"
        class: "error-message"
        style: "color: red; display: none;"
    }
    
    button {
        type: "submit"
        "提交"
    }
    
    script {
        const form = document.getElementById('user-form');
        const emailInput = document.getElementById('email');
        const errorSpan = document.getElementById('email-error');
        
        form.addEventListener('submit', (e) => {
            e.preventDefault();
            
            const email = emailInput.value;
            const isValid = /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email);
            
            if (!isValid) {
                errorSpan.textContent = '请输入有效的邮箱地址';
                errorSpan.style.display = 'block';
            } else {
                errorSpan.style.display = 'none';
                console.log('表单提交成功');
            }
        });
    }
}
```

## 最佳实践

### 1. 保持作用域清晰

```chtl
div {
    class: "scope-example"
    
    script {
        // 使用 const/let 避免污染全局作用域
        const localData = { count: 0 };
        
        // 如果需要跨script块通信，使用元素的dataset
        this.dataset.count = '0';
    }
}
```

### 2. 合理组织代码

```chtl
// ❌ 不推荐：在一个script块中写太多逻辑
div {
    script {
        // 100行代码...
    }
}

// ✅ 推荐：将复杂逻辑拆分
div {
    // 初始化
    script {
        const state = { items: [] };
        this.dataset.state = JSON.stringify(state);
    }
    
    // 事件处理
    script {
        this.addEventListener('click', handleClick);
        
        function handleClick(e) {
            // 处理逻辑
        }
    }
}
```

### 3. 与style块配合

```chtl
div {
    class: "interactive"
    
    // 定义样式
    style {
        .interactive {
            cursor: pointer;
            transition: all 0.3s;
        }
        .interactive.active {
            background: #67C3CC;
            color: white;
        }
    }
    
    // 定义行为
    script {
        this.addEventListener('click', () => {
            this.classList.toggle('active');
        });
    }
}
```

### 4. 错误处理

```chtl
div {
    script {
        try {
            // 可能出错的代码
            const data = JSON.parse(this.dataset.config);
            processData(data);
        } catch (error) {
            console.error('Script error:', error);
            // 优雅降级
            this.textContent = '加载失败';
        }
    }
}
```

## 注意事项

1. **执行顺序**：script块按照在文档中出现的顺序执行
2. **this上下文**：在script块中，`this`通常指向包含它的元素
3. **作用域隔离**：每个script块都有独立的作用域
4. **性能考虑**：避免在循环中创建大量script块
5. **兼容性**：生成的JavaScript代码兼容现代浏览器

## 与[Script]块的选择

- 使用 `script {}`：
  - 元素特定的行为
  - 简单的事件处理
  - 局部状态管理
  - 组件内部逻辑

- 使用 `[Script]`：
  - 全局功能
  - 模块化代码
  - 需要命名引用
  - 需要控制执行时机
  - 跨组件共享的逻辑

## 总结

局部script块为CHTL带来了更自然、更直观的JavaScript集成方式。通过与style块一致的语法，开发者可以在同一个地方定义元素的结构、样式和行为，实现真正的组件化开发。