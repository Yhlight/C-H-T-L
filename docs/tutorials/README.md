# CHTL 文档

欢迎使用 CHTL（Chtholly Template Language）！CHTL 是一个现代化的模板语言，专为构建高效、可维护的 Web 应用而设计。

## 目录

- [快速开始](#快速开始)
- [语言特性](#语言特性)
- [核心概念](#核心概念)
- [语法参考](#语法参考)
- [高级特性](#高级特性)
- [工具链](#工具链)
- [最佳实践](#最佳实践)
- [API 参考](#api-参考)

## 快速开始

### 安装

1. **安装 VS Code 扩展**
   ```bash
   code --install-extension chtl-lang-*.vsix
   ```

2. **使用 CLI 创建项目**
   ```bash
   node /workspace/scripts/chtl-cli.js init
   ```

3. **编译你的第一个 CHTL 文件**
   ```bash
   chtl compile index.chtl -o dist
   ```

### 第一个示例

```chtl
html {
    head {
        title { text { "我的第一个 CHTL 页面" } }
    }
    
    body {
        h1 { text { "Hello, CHTL!" } }
        p { text { "欢迎使用 CHTL 模板语言。" } }
    }
}
```

## 语言特性

### 1. 组件化开发

CHTL 支持创建可重用的组件：

```chtl
[Template] @Element Button {
    button {
        class: "btn";
        style {
            .btn {
                padding: 0.5rem 1rem;
                background: #007bff;
                color: white;
                border: none;
                border-radius: 4px;
                cursor: pointer;
            }
        }
        slot { name: "content"; }
    }
}

// 使用组件
body {
    @Element Button {
        text { "点击我" }
    }
}
```

### 2. 局部样式作用域

样式可以局部作用于元素：

```chtl
div {
    style {
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        &:hover {
            background: #f0f0f0;
        }
    }
}
```

### 3. 增强的 JavaScript

CHTL 提供了增强的 JavaScript 语法：

```chtl
script {
    // 增强选择器
    {{#app}}->addEventListener('click', function() {
        console.log('Clicked!');
    });
    
    // 事件委托
    {{.button}}->delegate('click', {
        click: function(e) {
            {{&}}->toggleClass('active');
        }
    });
    
    // 动画
    {{.box}}->animate({
        target: 'opacity',
        from: 0,
        to: 1,
        duration: 1000
    });
}
```

## 核心概念

### 元素和属性

```chtl
div {
    id: "container";
    class: "main-content";
    data-value: "123";
    
    // 子元素
    h1 { text { "标题" } }
}
```

### 模板系统

CHTL 提供三种模板类型：

1. **元素模板** - 可重用的 UI 组件
2. **样式模板** - 可重用的样式集合
3. **变量模板** - 可重用的变量组

```chtl
// 样式模板
[Template] @Style Theme {
    primaryColor: #007bff;
    secondaryColor: #6c757d;
}

// 变量模板
[Template] @Var Spacing {
    small: 8px;
    medium: 16px;
    large: 24px;
}

// 使用
div {
    style {
        padding: Spacing(medium);
        background: Theme(primaryColor);
    }
}
```

### 自定义组件

自定义组件提供更高的灵活性：

```chtl
[Custom] @Element Card {
    div {
        class: "card";
        
        // 可以被特例化
        style {
            border-radius: 8px;
            padding: 20px;
        }
    }
}

// 特例化使用
@Element Card {
    delete style;  // 删除默认样式
    
    style {
        border: 1px solid #ddd;
        padding: 30px;
    }
}
```

## 语法参考

### 注释

```chtl
// 单行注释

/* 
   多行注释
*/

-- 生成器识别的注释（会出现在输出中）
```

### 导入导出

```chtl
// 导入
[Import] @Element Button from "./components/Button.chtl";
[Import] @Style * from "./styles/theme.chtl";
[Import] @Element Card as MyCard from "./Card.chtl";

// 导出
[Export] {
    @Element Button;
    @Style Theme;
    @Var Spacing as SpacingVars;
}
```

### 命名空间

```chtl
[Namespace] MyApp {
    [Template] @Element Header {
        // ...
    }
}

// 使用命名空间
@Element MyApp.Header;
```

### 配置

```chtl
[Configuration] {
    INDEX_INITIAL_COUNT = 0;
    DEBUG_MODE = false;
    
    [Name] {
        CUSTOM_STYLE = [@Style, @样式];
        CUSTOM_ELEMENT = [@Element, @元素];
    }
}
```

## 高级特性

### 继承

```chtl
[Template] @Element BaseButton {
    button {
        class: "btn";
    }
}

[Custom] @Element PrimaryButton {
    inherit @Element BaseButton;
    
    button {
        class: "btn btn-primary";
    }
}
```

### 删除和插入操作

```chtl
[Custom] @Element ExtendedCard {
    inherit @Element Card;
    
    // 删除继承的元素
    delete div[0];
    
    // 插入新元素
    insert after header {
        div {
            class: "card-body";
        }
    }
}
```

### 约束条件

```chtl
[Custom] @Element ConditionalElement {
    div {
        class: "box";
    } except mobile;
    
    div {
        class: "mobile-box";
    } except desktop;
}
```

### 原始嵌入

```chtl
[Origin] @Html rawContent {
    <svg>
        <circle cx="50" cy="50" r="40" />
    </svg>
}

[Origin] @JavaScript tracking {
    // 第三方脚本
    ga('send', 'pageview');
}

// 使用
body {
    [Origin] @Html rawContent;
}
```

## 工具链

### VS Code 扩展

功能包括：

- **语法高亮** - 完整的 CHTL 语法支持
- **智能补全** - 上下文感知的代码补全
- **错误诊断** - 实时语法检查
- **代码重构** - 提取组件、重命名等
- **调试支持** - 断点调试 CHTL 代码
- **格式化** - 自动代码格式化

### CLI 工具

```bash
# 创建新项目
chtl init

# 创建新组件
chtl new component Button

# 编译文件
chtl compile index.chtl -o dist

# 监视模式
chtl watch src -o dist

# 打包模块
chtl pack-cmod src -o module.cmod
```

### 编译器选项

```bash
chtl compile [options] <input>

选项：
  -o, --output <dir>      输出目录
  -m, --source-map        生成源映射
  -w, --watch             监视文件变化
  --minify                压缩输出
  --debug                 调试模式
  --module-path <paths>   模块搜索路径
```

## 最佳实践

### 1. 项目结构

```
my-chtl-app/
├── index.chtl           # 入口文件
├── components/          # 组件目录
│   ├── Header.chtl
│   ├── Footer.chtl
│   └── Button.chtl
├── styles/              # 样式目录
│   ├── theme.chtl
│   └── variables.chtl
├── modules/             # CMOD 模块
├── dist/                # 输出目录
└── chtl.config.json     # 配置文件
```

### 2. 命名约定

- **组件名称**：使用 PascalCase（如 `MyButton`）
- **样式类名**：使用 kebab-case（如 `my-button`）
- **变量名**：使用 camelCase（如 `primaryColor`）

### 3. 性能优化

- 使用模板而不是重复代码
- 合理使用继承层级
- 避免深层嵌套
- 使用 CMOD 打包共享组件

### 4. 代码组织

```chtl
// 1. 配置和导入
[Configuration] { /* ... */ }
[Import] /* ... */

// 2. 命名空间定义
[Namespace] MyApp { /* ... */ }

// 3. 全局模板
[Template] @Style GlobalStyles { /* ... */ }

// 4. 主要内容
html { /* ... */ }

// 5. 导出
[Export] { /* ... */ }
```

## API 参考

### 节点类型

- `Element` - HTML 元素节点
- `Text` - 文本节点
- `Style` - 样式节点
- `Script` - 脚本节点
- `Template` - 模板定义
- `Custom` - 自定义组件
- `Import` - 导入声明
- `Export` - 导出声明
- `Configuration` - 配置块
- `Namespace` - 命名空间

### CHTL JS API

```javascript
// 选择器增强
{{selector}}         // 增强选择器
{{&}}                // 当前元素引用

// 方法
element->listen(events)      // 添加事件监听
element->delegate(selector, events)  // 事件委托
element->animate(options)    // 动画
element->addClass(className) // 添加类
element->removeClass(className) // 移除类
element->toggleClass(className) // 切换类
```

### 编译器 API

```javascript
const { ChtlCompiler } = require('chtl-compiler');

const compiler = new ChtlCompiler({
    outputDirectory: 'dist',
    sourceMaps: true,
    moduleSearchPaths: ['./modules']
});

// 编译文件
const result = await compiler.compile('index.chtl');

// 监视模式
compiler.watch('src', (event, file) => {
    console.log(`File ${file} was ${event}`);
});
```

## 更多资源

- [GitHub 仓库](https://github.com/chtl/chtl)
- [示例项目](https://github.com/chtl/examples)
- [社区论坛](https://forum.chtl.dev)
- [更新日志](./CHANGELOG.md)

---

© 2024 CHTL 项目。使用 MIT 许可证发布。