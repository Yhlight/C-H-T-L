# CHTL 入门教程

本教程将带你从零开始学习 CHTL，通过实际示例逐步掌握 CHTL 的核心概念和高级特性。

## 目录

1. [环境准备](#环境准备)
2. [第一个 CHTL 页面](#第一个-chtl-页面)
3. [使用样式](#使用样式)
4. [创建组件](#创建组件)
5. [添加交互](#添加交互)
6. [组织项目](#组织项目)
7. [高级技巧](#高级技巧)

## 环境准备

### 1. 安装 VS Code 扩展

首先，确保你已经安装了 VS Code。然后安装 CHTL 扩展：

```bash
# 如果你有 .vsix 文件
code --install-extension chtl-lang-1.0.0.vsix
```

### 2. 创建项目

使用 CLI 工具创建一个新项目：

```bash
node /workspace/scripts/chtl-cli.js init
```

选择 "Basic CHTL Project" 模板，输入项目名称，例如 "my-first-chtl"。

### 3. 项目结构

创建完成后，你会看到如下结构：

```
my-first-chtl/
├── index.chtl
├── .gitignore
└── README.md
```

## 第一个 CHTL 页面

打开 `index.chtl`，让我们创建一个简单的页面：

```chtl
// index.chtl
html {
    head {
        title { text { "我的第一个 CHTL 页面" } }
        meta { charset: "UTF-8"; }
    }
    
    body {
        h1 { text { "欢迎来到 CHTL!" } }
        p { text { "这是我用 CHTL 创建的第一个页面。" } }
    }
}
```

### 编译和预览

在终端运行：

```bash
# 编译
/workspace/build/chtl index.chtl -o dist

# 查看生成的文件
ls dist/
```

用浏览器打开 `dist/index.html`，你会看到一个简单的网页。

## 使用样式

CHTL 支持多种方式添加样式。

### 1. 内联样式

```chtl
div {
    style {
        width: 200px;
        height: 100px;
        background: #f0f0f0;
        padding: 20px;
    }
    
    text { "这是一个带样式的盒子" }
}
```

### 2. 局部类样式

```chtl
div {
    // CHTL 会自动为元素添加 'container' 类
    style {
        .container {
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        
        // & 表示当前元素的类
        &:hover {
            background: #e0e0e0;
        }
    }
    
    h2 { text { "自动类名" } }
    p { text { "CHTL 会自动管理类名，避免冲突。" } }
}
```

### 3. 样式模板

创建可重用的样式：

```chtl
// 定义样式模板
[Template] @Style ButtonStyle {
    padding: 10px 20px;
    background: #007bff;
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    transition: background 0.3s;
}

// 使用样式模板
button {
    style {
        @Style ButtonStyle;
        
        &:hover {
            background: #0056b3;
        }
    }
    
    text { "点击我" }
}
```

## 创建组件

组件是 CHTL 的核心概念，让你能够创建可重用的 UI 元素。

### 1. 简单组件

```chtl
// 定义一个卡片组件
[Template] @Element Card {
    div {
        class: "card";
        
        style {
            .card {
                border: 1px solid #ddd;
                border-radius: 8px;
                padding: 20px;
                margin: 10px 0;
                box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            }
        }
        
        // 插槽用于放置内容
        slot { name: "content"; }
    }
}

// 使用组件
body {
    @Element Card {
        h3 { text { "卡片标题" } }
        p { text { "这是卡片的内容。" } }
    }
    
    @Element Card {
        h3 { text { "另一张卡片" } }
        p { text { "每个卡片都是独立的。" } }
    }
}
```

### 2. 带参数的组件

使用自定义组件可以接受参数：

```chtl
[Custom] @Element Button {
    button {
        class: "btn";
        
        style {
            .btn {
                padding: 10px 20px;
                border: none;
                border-radius: 4px;
                cursor: pointer;
                font-size: 16px;
            }
            
            .btn-primary {
                background: #007bff;
                color: white;
            }
            
            .btn-secondary {
                background: #6c757d;
                color: white;
            }
        }
        
        slot { name: "content"; }
    }
}

// 使用时可以修改
body {
    @Element Button {
        button {
            class: "btn btn-primary";
        }
        text { "主要按钮" }
    }
    
    @Element Button {
        button {
            class: "btn btn-secondary";
        }
        text { "次要按钮" }
    }
}
```

## 添加交互

CHTL 提供了增强的 JavaScript 语法，让交互更简单。

### 1. 基本事件处理

```chtl
div {
    id: "click-demo";
    
    button {
        id: "my-button";
        text { "点击计数: 0" }
    }
    
    script {
        let count = 0;
        
        // 使用增强选择器
        {{#my-button}}->listen({
            click: function() {
                count++;
                this.textContent = '点击计数: ' + count;
            }
        });
    }
}
```

### 2. 动画效果

```chtl
div {
    class: "animation-demo";
    
    style {
        .box {
            width: 100px;
            height: 100px;
            background: #ff6b6b;
            margin: 20px;
        }
    }
    
    div {
        class: "box";
    }
    
    button {
        text { "播放动画" }
    }
    
    script {
        {{button}}->listen({
            click: function() {
                {{.box}}->animate({
                    target: 'transform',
                    from: 'scale(1) rotate(0deg)',
                    to: 'scale(1.2) rotate(360deg)',
                    duration: 1000,
                    easing: 'ease-in-out'
                });
            }
        });
    }
}
```

### 3. 表单处理

```chtl
form {
    id: "contact-form";
    
    style {
        input, textarea {
            width: 100%;
            padding: 8px;
            margin: 5px 0;
            border: 1px solid #ddd;
            border-radius: 4px;
        }
        
        button {
            background: #28a745;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
    }
    
    input {
        type: "text";
        name: "name";
        placeholder: "您的姓名";
    }
    
    input {
        type: "email";
        name: "email";
        placeholder: "您的邮箱";
    }
    
    textarea {
        name: "message";
        placeholder: "留言内容";
        rows: 5;
    }
    
    button {
        type: "submit";
        text { "发送" }
    }
    
    script {
        {{&}}->listen({
            submit: function(e) {
                e.preventDefault();
                
                const formData = new FormData(this);
                const data = Object.fromEntries(formData);
                
                console.log('表单数据:', data);
                alert('表单已提交！');
                
                // 重置表单
                this.reset();
            }
        });
    }
}
```

## 组织项目

随着项目增长，良好的组织结构很重要。

### 1. 分离组件

创建 `components/Header.chtl`：

```chtl
[Template] @Element Header {
    header {
        class: "site-header";
        
        style {
            .site-header {
                background: #333;
                color: white;
                padding: 1rem;
            }
            
            .site-title {
                margin: 0;
                font-size: 1.5rem;
            }
        }
        
        h1 {
            class: "site-title";
            text { "我的 CHTL 网站" }
        }
        
        nav {
            a { href: "/"; text { "首页" } }
            a { href: "/about"; text { "关于" } }
            a { href: "/contact"; text { "联系" } }
        }
    }
}

[Export] {
    @Element Header;
}
```

### 2. 主文件中使用

更新 `index.chtl`：

```chtl
[Import] @Element Header from "./components/Header.chtl";

html {
    head {
        title { text { "我的网站" } }
    }
    
    body {
        @Element Header;
        
        main {
            // 主要内容
        }
    }
}
```

### 3. 共享样式

创建 `styles/theme.chtl`：

```chtl
[Template] @Style Colors {
    primary: #007bff;
    secondary: #6c757d;
    success: #28a745;
    danger: #dc3545;
}

[Template] @Var Spacing {
    small: 8px;
    medium: 16px;
    large: 24px;
}

[Export] {
    @Style Colors;
    @Var Spacing;
}
```

## 高级技巧

### 1. 条件渲染

使用约束条件：

```chtl
[Custom] @Element ResponsiveNav {
    // 桌面版导航
    nav {
        class: "desktop-nav";
        style {
            .desktop-nav {
                display: flex;
                gap: 20px;
            }
        }
    } except mobile;
    
    // 移动版导航
    nav {
        class: "mobile-nav";
        style {
            .mobile-nav {
                display: block;
            }
        }
    } except desktop;
}
```

### 2. 组件继承

```chtl
// 基础按钮
[Template] @Element BaseButton {
    button {
        class: "btn";
        style {
            .btn {
                padding: 10px 20px;
                border: none;
                cursor: pointer;
            }
        }
    }
}

// 扩展按钮
[Custom] @Element IconButton {
    inherit @Element BaseButton;
    
    // 添加图标
    insert at top {
        span {
            class: "icon";
            text { "🔔" }
        }
    }
    
    style {
        .icon {
            margin-right: 8px;
        }
    }
}
```

### 3. 动态内容

```chtl
div {
    id: "user-list";
    
    script {
        const users = [
            { name: "张三", age: 25 },
            { name: "李四", age: 30 },
            { name: "王五", age: 28 }
        ];
        
        const container = {{&}};
        
        users.forEach(user => {
            const userDiv = document.createElement('div');
            userDiv.className = 'user-card';
            userDiv.innerHTML = `
                <h3>${user.name}</h3>
                <p>年龄: ${user.age}</p>
            `;
            container.appendChild(userDiv);
        });
    }
    
    style {
        .user-card {
            border: 1px solid #ddd;
            padding: 10px;
            margin: 5px 0;
        }
    }
}
```

## 下一步

恭喜你完成了 CHTL 入门教程！你已经学会了：

- ✅ 创建基本的 CHTL 页面
- ✅ 使用样式和样式模板
- ✅ 创建和使用组件
- ✅ 添加交互和动画
- ✅ 组织项目结构
- ✅ 使用高级特性

### 推荐学习路径

1. 阅读[完整文档](./README.md)了解所有特性
2. 查看[快速参考](./QUICK_REFERENCE.md)作为日常开发参考
3. 探索[示例项目](../examples/)学习最佳实践
4. 加入社区，与其他开发者交流

祝你使用 CHTL 开发愉快！