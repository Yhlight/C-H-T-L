# CHTL 用户指南

## 目录

1. [简介](#简介)
2. [安装和配置](#安装和配置)
3. [基础教程](#基础教程)
4. [进阶功能](#进阶功能)
5. [最佳实践](#最佳实践)
6. [常见问题](#常见问题)

## 简介

CHTL (Component HTML Template Language) 是一个革命性的模板语言，它将组件化思想深入到 HTML 开发的每个环节。

### 为什么选择 CHTL？

- **真正的组件化**：不是简单的模板替换，而是完整的组件系统
- **优雅的语法**：类似 CSS 的语法，易于学习和使用
- **强大的扩展性**：通过 CJmod 系统实现无限可能
- **智能的样式隔离**：自动处理样式作用域
- **现代化的工具链**：完整的编译器、调试器和开发工具

## 安装和配置

### 系统要求

- C++ 编译器（支持 C++17）
- CMake 3.16 或更高版本
- Linux/macOS/Windows (WSL)

### 从源码安装

```bash
# 克隆仓库
git clone https://github.com/yourusername/chtl.git
cd chtl

# 创建构建目录
mkdir build && cd build

# 配置
cmake ..

# 编译
make -j$(nproc)

# 安装到系统
sudo make install
```

### 验证安装

```bash
chtl --version
# 输出: CHTL version 1.0.0
```

### VS Code 扩展

安装 CHTL 语言支持扩展以获得语法高亮和智能提示：

```bash
code --install-extension chtl-lang
```

## 基础教程

### 第一个 CHTL 文件

创建 `hello.chtl`：

```chtl
html {
    head {
        title { text { "我的第一个 CHTL 页面" } }
    }
    body {
        h1 { text { "Hello, CHTL!" } }
        p { text { "欢迎来到组件化的世界" } }
    }
}
```

编译：

```bash
chtl hello.chtl -o output/
```

### 添加样式

```chtl
html {
    head {
        style {
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 20px;
                background: #f5f5f5;
            }
            
            h1 {
                color: #333;
                border-bottom: 2px solid #007bff;
                padding-bottom: 10px;
            }
        }
    }
    body {
        h1 { text { "带样式的页面" } }
    }
}
```

### 使用属性

```chtl
div {
    id: "container";
    class: "main-content active";
    data-role: "content";
    
    img {
        src: "/images/logo.png";
        alt: "Logo";
        width: 200;
        height: 50;
    }
}
```

### 创建组件

```chtl
// 定义一个按钮组件
[Template] @Element Button {
    button {
        class: "btn";
        type: "button";
        slot;  // 内容插槽
    }
}

// 使用组件
html {
    body {
        @Element Button {
            text { "点击我" }
        }
        
        @Element Button {
            class: "btn-primary";  // 添加额外的类
            text { "主要按钮" }
        }
    }
}
```

### 变量系统

```chtl
// 定义变量组
[Template] @Var Colors {
    primary: "#007bff";
    secondary: "#6c757d";
    success: "#28a745";
    danger: "#dc3545";
}

[Template] @Var Spacing {
    small: "0.5rem";
    medium: "1rem";
    large: "2rem";
}

// 使用变量
div {
    style {
        background: Colors(primary);
        padding: Spacing(medium);
        margin-bottom: Spacing(large);
    }
}
```

## 进阶功能

### 局部样式

局部样式会自动限定作用域：

```chtl
div {
    class: "card";
    
    style {
        padding: 20px;
        border: 1px solid #ddd;
        border-radius: 8px;
        
        // & 代表当前元素
        &:hover {
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        }
        
        // 子元素样式
        h3 {
            margin-top: 0;
            color: #333;
        }
    }
    
    h3 { text { "卡片标题" } }
    p { text { "卡片内容" } }
}
```

### CHTL-JS 集成

```chtl
button {
    id: "myButton";
    text { "计数器: 0" }
    
    script {
        let count = 0;
        
        // {{&}} 引用当前元素
        {{&}}.addEventListener('click', function() {
            count++;
            this.textContent = `计数器: ${count}`;
        });
    }
}

// 全局脚本
script {
    // {{#id}} 通过 ID 获取元素
    window.addEventListener('load', function() {
        {{#myButton}}.style.background = '#007bff';
        {{#myButton}}.style.color = 'white';
    });
}
```

### 模板继承

```chtl
// 基础模板
[Template] @Element BaseCard {
    div {
        class: "card";
        style {
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: 16px;
        }
        slot;
    }
}

// 继承并扩展
[Template] @Element PrimaryCard inherit BaseCard {
    [Operate] {
        modify style {
            border-color: #007bff;
            background: #f0f8ff;
        }
    }
}

// 使用
@Element PrimaryCard {
    h3 { text { "重要内容" } }
    p { text { "这是一个主要卡片" } }
}
```

### 条件渲染（通过 CJmod）

```chtl
[Import] @CJmod conditional from "builtin:conditional";

div {
    script {
        const showContent = true;
    }
    
    @if (showContent) {
        p { text { "条件为真时显示" } }
    }
    
    @else {
        p { text { "条件为假时显示" } }
    }
}
```

### 列表渲染（通过 CJmod）

```chtl
[Import] @CJmod loops from "builtin:loops";

ul {
    script {
        const items = ['苹果', '香蕉', '橙子'];
    }
    
    @for (item of items) {
        li { text { item } }
    }
}
```

## 最佳实践

### 1. 组件设计原则

**单一职责**
```chtl
// ✅ 好：每个组件只做一件事
[Template] @Element Icon {
    i { class: "icon"; slot; }
}

[Template] @Element Button {
    button { 
        @Element Icon { slot; }
        span { slot; }
    }
}

// ❌ 差：组件职责过多
[Template] @Element ButtonWithIconAndTooltip {
    // 太复杂...
}
```

**可组合性**
```chtl
// 设计可以组合使用的小组件
[Template] @Element Flex {
    div {
        style { display: flex; }
        slot;
    }
}

[Template] @Element Grid {
    div {
        style { display: grid; }
        slot;
    }
}
```

### 2. 样式组织

**使用变量组管理主题**
```chtl
[Template] @Var Theme {
    // 颜色
    colorPrimary: "#007bff";
    colorSecondary: "#6c757d";
    colorBackground: "#ffffff";
    colorText: "#212529";
    
    // 间距
    spacingUnit: "8px";
    spacingSmall: "8px";
    spacingMedium: "16px";
    spacingLarge: "24px";
    
    // 字体
    fontFamily: "'Helvetica Neue', Arial, sans-serif";
    fontSizeBase: "16px";
    fontSizeSmall: "14px";
    fontSizeLarge: "18px";
}
```

### 3. 性能优化

**避免深层嵌套**
```chtl
// ❌ 差：过深的嵌套
div {
    div {
        div {
            div {
                div {
                    div {
                        text { "内容" }
                    }
                }
            }
        }
    }
}

// ✅ 好：扁平化结构
div {
    class: "container";
    
    div {
        class: "content";
        text { "内容" }
    }
}
```

**合理使用局部脚本**
```chtl
// ❌ 差：每个元素都有脚本
div {
    script { /* ... */ }
    
    button {
        script { /* ... */ }
    }
    
    span {
        script { /* ... */ }
    }
}

// ✅ 好：集中管理事件
div {
    id: "container";
    
    button { id: "btn1"; }
    button { id: "btn2"; }
    
    script {
        // 使用事件委托
        {{&}}.addEventListener('click', function(e) {
            if (e.target.matches('button')) {
                // 处理按钮点击
            }
        });
    }
}
```

### 4. 项目结构

推荐的项目结构：

```
my-project/
├── src/
│   ├── components/     # 可重用组件
│   │   ├── Button.chtl
│   │   ├── Card.chtl
│   │   └── Modal.chtl
│   ├── layouts/        # 布局模板
│   │   └── Default.chtl
│   ├── styles/         # 全局样式和变量
│   │   ├── theme.chtl
│   │   └── reset.chtl
│   └── pages/          # 页面文件
│       ├── index.chtl
│       └── about.chtl
├── assets/             # 静态资源
├── dist/               # 编译输出
└── chtl.config.json    # 项目配置
```

## 常见问题

### Q: 如何调试 CHTL-JS 代码？

A: CHTL-JS 代码会被编译成标准 JavaScript，可以使用浏览器开发者工具进行调试：

```chtl
script {
    // 使用 console.log 调试
    console.log('当前元素:', {{&}});
    
    // 使用断点
    debugger;
    
    // 查看变量值
    const data = { name: 'CHTL' };
    console.table(data);
}
```

### Q: 如何处理异步操作？

A: CHTL-JS 完全支持现代 JavaScript 特性：

```chtl
button {
    text { "加载数据" }
    
    script {
        {{&}}.addEventListener('click', async function() {
            try {
                const response = await fetch('/api/data');
                const data = await response.json();
                console.log(data);
            } catch (error) {
                console.error('加载失败:', error);
            }
        });
    }
}
```

### Q: 如何与现有框架集成？

A: CHTL 可以编译到不同的目标平台：

```bash
# 编译为 React 组件
chtl input.chtl -o output/ --platform=react

# 编译为 Vue 组件
chtl input.chtl -o output/ --platform=vue

# 编译为原生 Web Components
chtl input.chtl -o output/ --platform=web-components
```

### Q: 如何创建可重用的组件库？

A: 创建一个 CMOD 包：

1. 创建 `package.cmod`：
```json
{
    "name": "my-ui-library",
    "version": "1.0.0",
    "exports": {
        "Button": "./components/Button.chtl",
        "Card": "./components/Card.chtl",
        "theme": "./styles/theme.chtl"
    }
}
```

2. 发布和使用：
```chtl
[Import] @Element Button from "my-ui-library/Button";
[Import] @Var theme from "my-ui-library/theme";
```

### Q: 性能如何？

A: CHTL 编译器进行了多项优化：

- **编译时优化**：变量替换、死代码消除、样式合并
- **运行时优化**：事件委托、虚拟 DOM（可选）、懒加载
- **输出优化**：代码压缩、树摇、分块

基准测试显示，CHTL 生成的代码性能与手写优化的代码相当。

## 下一步

- 查看 [API 文档](./api/) 了解详细接口
- 浏览 [示例项目](https://github.com/chtl/examples) 学习实际应用
- 加入 [社区论坛](https://forum.chtl.dev) 获取帮助
- 贡献代码到 [GitHub](https://github.com/yourusername/chtl)