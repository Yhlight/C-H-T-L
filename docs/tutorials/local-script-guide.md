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

## {{&}} 上下文语法

在script块中，可以使用 `{{&}}` 来表示当前元素（包含该script块的元素）。这个语法会在解析时自动替换为 `this`。

### 基本用法

```chtl
div {
    id: "my-div"
    
    script {
        // {{&}} 会被替换为 this，指向包含此script块的div
        {{&}}.addEventListener('click', function() {
            console.log('Clicked:', {{&}}.id); // 输出: "Clicked: my-div"
        });
        
        // 等价于
        // this.addEventListener('click', function() {
        //     console.log('Clicked:', this.id);
        // });
    }
}
```

### {{&}} 的优势

1. **更清晰的语义**：`{{&}}` 明确表示"当前元素"，避免了 `this` 的歧义
2. **与style块一致**：style块中使用 `&` 表示当前选择器，script块使用 `{{&}}` 保持概念一致
3. **避免this绑定问题**：在回调函数中使用 `{{&}}` 可以避免this上下文丢失的问题

### 使用示例

```chtl
// 1. 基础事件绑定
button {
    "点击我"
    
    script {
        {{&}}.onclick = () => {
            {{&}}.textContent = "已点击！";
        };
    }
}

// 2. 操作样式和属性
div {
    class: "box"
    data-state: "inactive"
    
    script {
        // 初始化样式
        {{&}}.style.backgroundColor = '#f0f0f0';
        
        // 切换状态
        {{&}}.addEventListener('click', () => {
            if ({{&}}.dataset.state === 'inactive') {
                {{&}}.dataset.state = 'active';
                {{&}}.style.backgroundColor = '#67C3CC';
            } else {
                {{&}}.dataset.state = 'inactive';
                {{&}}.style.backgroundColor = '#f0f0f0';
            }
        });
    }
}

// 3. 与子元素交互
div {
    class: "container"
    
    button { "添加项目" }
    ul { class: "list" }
    
    script {
        const button = {{&}}.querySelector('button');
        const list = {{&}}.querySelector('.list');
        
        button.onclick = () => {
            const li = document.createElement('li');
            li.textContent = `项目 ${list.children.length + 1}`;
            list.appendChild(li);
        };
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
| 上下文引用 | 无特殊语法 | 支持 `{{&}}` 表示当前元素 |

## 使用场景

### 1. 元素行为绑定

```chtl
button {
    id: "my-button"
    "点击我"
    
    script {
        // 使用 {{&}} 直接引用当前按钮
        {{&}}.addEventListener('click', () => {
            alert('按钮被点击了！');
            {{&}}.disabled = true;
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
                // 使用 {{&}} 操作组件元素
                const btn = {{&}}.querySelector('.toggle-btn');
                const content = {{&}}.querySelector('.toggle-content');
                
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
        // 初始化数据并存储到元素
        const data = [
            { label: 'A', value: 10 },
            { label: 'B', value: 20 },
            { label: 'C', value: 15 }
        ];
        
        // 使用 {{&}} 存储数据
        {{&}}.dataset.chartData = JSON.stringify(data);
    }
}
```

### 4. 动画和效果

```chtl
div {
    class: "animated-box"
    
    "悬停查看效果"
    
    script {
        {{&}}.addEventListener('mouseenter', () => {
            {{&}}.style.transform = 'scale(1.1) rotate(5deg)';
        });
        
        {{&}}.addEventListener('mouseleave', () => {
            {{&}}.style.transform = 'scale(1) rotate(0deg)';
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
        const emailInput = {{&}}.querySelector('#email');
        const errorSpan = {{&}}.querySelector('#email-error');
        
        {{&}}.addEventListener('submit', (e) => {
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
        
        // 使用 {{&}} 将数据关联到元素
        {{&}}.dataset.count = '0';
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
        {{&}}.dataset.state = JSON.stringify(state);
    }
    
    // 事件处理
    script {
        {{&}}.addEventListener('click', handleClick);
        
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
        {{&}}.addEventListener('click', () => {
            {{&}}.classList.toggle('active');
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
            const data = JSON.parse({{&}}.dataset.config);
            processData(data);
        } catch (error) {
            console.error('Script error:', error);
            // 优雅降级
            {{&}}.textContent = '加载失败';
        }
    }
}
```

## 注意事项

1. **执行顺序**：script块按照在文档中出现的顺序执行
2. **{{&}}上下文**：`{{&}}` 始终指向包含script块的最近父元素
3. **作用域隔离**：每个script块都有独立的作用域
4. **性能考虑**：避免在循环中创建大量script块
5. **兼容性**：生成的JavaScript代码兼容现代浏览器

## {{&}} 在嵌套结构中的行为

```chtl
div {
    class: "outer"
    
    script {
        // {{&}} 指向 div.outer
        console.log({{&}}.className); // "outer"
    }
    
    div {
        class: "inner"
        
        script {
            // {{&}} 指向 div.inner
            console.log({{&}}.className); // "inner"
        }
    }
}
```

## 与[Script]块的选择

- 使用 `script {}`：
  - 元素特定的行为
  - 简单的事件处理
  - 局部状态管理
  - 组件内部逻辑
  - 需要引用当前元素（使用{{&}}）

- 使用 `[Script]`：
  - 全局功能
  - 模块化代码
  - 需要命名引用
  - 需要控制执行时机
  - 跨组件共享的逻辑

## 总结

局部script块为CHTL带来了更自然、更直观的JavaScript集成方式。通过与style块一致的语法，以及 `{{&}}` 上下文引用，开发者可以在同一个地方定义元素的结构、样式和行为，实现真正的组件化开发。