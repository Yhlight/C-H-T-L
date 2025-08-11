# CHTL 语法参考文档

CHTL是基于C++语言实现的超文本语言，其本质是为了提供一种更符合开发者编写HTML代码的方式，使用MIT开源协议。

## 目录

1. [注释系统](#注释系统)
2. [文本节点](#文本节点)
3. [字面量](#字面量)
4. [CE对等式](#ce对等式)
5. [元素节点](#元素节点)
6. [属性](#属性)
7. [局部样式块](#局部样式块)
8. [模板系统](#模板系统)
9. [自定义系统](#自定义系统)
10. [原始嵌入](#原始嵌入)
11. [配置组](#配置组)
12. [导入系统](#导入系统)
13. [命名空间](#命名空间)
14. [约束系统](#约束系统)
15. [JavaScript增强](#javascript增强)
16. [CMOD模块系统](#cmod模块系统)

---

## 注释系统

CHTL支持三种注释方式：

```chtl
// 单行注释 - 不会出现在生成的HTML中

/*
多行注释
也不会出现在生成的HTML中
*/

-- 生成器识别的注释 - 会出现在生成的HTML中
```

---

## 文本节点

使用 `text { }` 表示文本内容：

```chtl
text {
    "这是一段文本"
}
```

---

## 字面量

CHTL支持多种字面量形式：

```chtl
// 无引号字面量（推荐用于CSS属性）
text {
    这是一段文本
}

style {
    color: red;
    font-size: 16px;
}

// 双引号字符串
text {
    "这是双引号字符串"
}

// 单引号字符串
text {
    '这是单引号字符串'
}
```

---

## CE对等式

Colon = Equal - 冒号和等号完全等价：

```chtl
div {
    id: "main";      // 使用冒号
    class = "box";   // 使用等号 - 完全等价
}
```

---

## 元素节点

支持所有HTML元素：

```chtl
html {
    head {
        title {
            text { "页面标题" }
        }
    }
    
    body {
        div {
            text { "块级元素" }
        }
        
        span {
            text { "行内元素" }
        }
        
        // 自闭合元素
        img {
            src: "image.png";
            alt: "图片描述";
        }
    }
}
```

---

## 属性

使用 `属性名: "属性值";` 的形式：

```chtl
div {
    id: box;          // 无引号字面量
    class: "welcome"; // 带引号字符串
    data-value: "123";
    
    text {
        HelloWorld
    }
}
```

---

## 局部样式块

CHTL增强了样式系统，允许在元素内部使用 `style {}`：

### 内联样式
直接在元素的 `style {}` 中写CSS属性：

```chtl
body {
    div {
        style {
            width: 100px;
            height: 200px;
            background-color: #f0f0f0;
        }
    }
}
```

### 自动化类名/ID
在局部样式块中使用选择器，CHTL会自动添加对应的class或id：

```chtl
div {
    style {
        .box {  // 自动为元素添加class="box"
            width: 300px;
            padding: 20px;
        }
        
        #main {  // 自动为元素添加id="main"
            background: white;
        }
    }
}
```

### 上下文推导（&符号）
使用 `&` 简化伪类和伪元素的使用：

```chtl
div {
    style {
        .card {  // 自动添加class="card"
            padding: 20px;
            border: 1px solid #ddd;
        }
        
        &:hover {  // 解析为 .card:hover
            background-color: #f5f5f5;
        }
        
        &::before {  // 解析为 .card::before
            content: "→";
            margin-right: 5px;
        }
    }
}
```

---

## 模板系统

使用 `[Template]` 创建可复用的模板。

### 样式组模板

```chtl
[Template] @Style DefaultText {
    color: black;
    line-height: 1.6;
    font-size: 14px;
}

// 使用样式组模板
div {
    style {
        @Style DefaultText;
        font-weight: bold;  // 可以添加额外样式
    }
}
```

### 元素模板

```chtl
[Template] @Element Card {
    div {
        class: "card";
        
        h3 {
            text { "卡片标题" }
        }
        
        div {
            class: "card-body";
            text { "卡片内容" }
        }
    }
}

// 使用元素模板
body {
    @Element Card;
}
```

### 变量组模板

```chtl
[Template] @Var ThemeColor {
    primary: rgb(0, 123, 255);
    secondary: rgb(108, 117, 125);
    danger: rgb(220, 53, 69);
}

// 使用变量组
div {
    style {
        color: ThemeColor(primary);
        border-color: ThemeColor(secondary);
    }
}
```

### 模板继承

#### 组合式继承
```chtl
[Template] @Style BaseTheme {
    color: #333;
    font-size: 14px;
}

[Template] @Style ExtendedTheme {
    @Style BaseTheme;  // 继承BaseTheme的所有属性
    font-weight: bold;
    background-color: #f0f0f0;
}
```

#### 显式继承（inherit关键字）
```chtl
[Template] @Style ExtendedTheme {
    inherit @Style BaseTheme;
    font-weight: bold;
}
```

---

## 自定义系统

`[Custom]` 提供比模板更高的灵活性，支持特例化操作。

### 自定义样式组

#### 无值样式组
```chtl
[Custom] @Style TextSet {
    color,
    font-size;  // 声明属性但不赋值
}

// 使用时填入值
div {
    style {
        @Style TextSet {
            color: red;
            font-size: 16px;
        }
    }
}
```

#### 删除属性
```chtl
[Template] @Style FullStyle {
    color: white;
    font-size: 16px;
    line-height: 1.6;
    border: 1px solid black;
}

[Custom] @Style SimpleStyle {
    @Style FullStyle {
        delete line-height, border;  // 删除特定属性
    }
}
```

### 自定义元素

#### 特例化 - 添加样式
```chtl
[Custom] @Element Box {
    div { }
    div { }
    span { }
}

body {
    @Element Box {
        span {
            style {
                color: red;
            }
        }
        
        div[1] {  // 索引访问第二个div
            style {
                background: blue;
            }
        }
    }
}
```

#### 插入元素
```chtl
body {
    @Element Box {
        insert after div[0] {
            p { "插入的段落" }
        }
        
        insert before span {
            hr { }
        }
        
        insert at top {
            h2 { "顶部标题" }
        }
        
        insert replace div[1] {
            section { "替换内容" }
        }
    }
}
```

#### 删除元素
```chtl
body {
    @Element Box {
        delete span;      // 删除所有span
        delete div[1];    // 删除第二个div
        delete @Element Line;  // 删除元素引用
    }
}
```

### 自定义变量组

```chtl
[Custom] @Var ThemeColor {
    tableColor: rgb(255, 192, 203);
    textColor: black;
}

// 特例化使用
div {
    style {
        color: ThemeColor(tableColor = rgb(145, 155, 200));
    }
}
```

---

## 原始嵌入

使用 `[Origin]` 嵌入原始代码，不经CHTL处理。

### HTML嵌入
```chtl
[Origin] @Html legacyCode {
    <div class="legacy">
        <p>原始HTML代码</p>
    </div>
}

body {
    [Origin] @Html legacyCode;
}
```

### CSS嵌入
```chtl
[Origin] @Style animations {
    @keyframes fadeIn {
        from { opacity: 0; }
        to { opacity: 1; }
    }
}
```

### JavaScript嵌入
```chtl
[Origin] @JavaScript utils {
    function debounce(fn, delay) {
        let timer;
        return function() {
            clearTimeout(timer);
            timer = setTimeout(fn, delay);
        };
    }
}
```

---

## 配置组

使用 `[Configuration]` 自定义编译器行为：

```chtl
[Configuration] {
    // 基本配置
    INDEX_INITIAL_COUNT = 0;
    DISABLE_NAME_GROUP = false;
    DEBUG_MODE = true;
    
    // 自定义关键字
    [Name] {
        CUSTOM_STYLE = [@Style, @样式, @CSS];
        CUSTOM_ELEMENT = [@Element, @元素];
        CUSTOM_VAR = [@Var, @变量];
        KEYWORD_DELETE = [delete, 删除];
        KEYWORD_INSERT = [insert, 插入];
        KEYWORD_TEXT = [text, 文本];
        OPTION_COUNT = 3;  // 限制组选项数量
    }
}
```

---

## 导入系统

使用 `[Import]` 导入各种资源：

### 导入外部文件
```chtl
// HTML文件
[Import] @Html from "template.html" as header;

// CSS文件
[Import] @Style from "theme.css";

// JavaScript文件
[Import] @JavaScript from "utils.js";
```

### 导入CHTL模块
```chtl
// 导入整个CHTL文件
[Import] @Chtl from "components.chtl";

// 导入特定的自定义元素
[Import] [Custom] @Element Button from "ui.chtl" as UIButton;

// 导入模板
[Import] [Template] @Style Theme from "styles.chtl";

// 通配符导入
[Import] * from "modules/*";
```

---

## 命名空间

使用 `[Namespace]` 防止模块污染：

### 基本命名空间
```chtl
[Namespace] UIComponents {
    [Custom] @Element Button {
        button { "按钮" }
    }
}

// 使用命名空间
body {
    @Element Button from UIComponents;
}
```

### 嵌套命名空间
```chtl
[Namespace] App {
    [Namespace] Components {
        [Custom] @Element Header { }
    }
    
    [Namespace] Styles {
        [Template] @Style Theme { }
    }
}

// 使用嵌套命名空间
body {
    @Element Header from App.Components;
    style {
        @Style Theme from App.Styles;
    }
}
```

---

## 约束系统

使用 `except` 关键字定义约束：

### 精确约束
```chtl
div {
    except span, [Custom] @Element Box;  // 禁止span和Box
    
    p { "允许的段落" }
    // span { "错误" }  // 不允许
}
```

### 类型约束
```chtl
div {
    except @Html;  // 禁止所有HTML元素
    except [Template] @Var;  // 禁止变量组模板
    except [Custom];  // 禁止所有自定义类型
}
```

### 全局约束
```chtl
[Namespace] RestrictedSpace {
    except [Template];  // 命名空间内禁止定义模板
    
    // [Template] @Element X { }  // 错误
    [Custom] @Element Y { }  // 允许
}
```

---

## JavaScript增强

CHTL为JavaScript提供了增强语法。

### 增强选择器（双花括号）
```chtl
script {
    {{.box}}      // 类选择器
    {{#main}}     // ID选择器
    {{button}}    // 元素选择器
    {{.box button}}  // 后代选择器
    {{button[0]}} // 索引访问
}
```

### 箭头操作符
使用 `->` 明确表示使用CHTL增强语法：

```chtl
script {
    {{.box}}->textContent = "新内容";
    {{#button}}->style->backgroundColor = "red";
}
```

### 增强监听器
```chtl
script {
    {{.button}}->listen({
        click: () => {
            console.log("点击");
        },
        mouseenter: function() {
            this.classList.add('hover');
        },
        mouseleave: () => {
            {{.button}}->classList->remove('hover');
        }
    });
}
```

### 事件委托
```chtl
script {
    {{body}}->delegate({
        target: {{.dynamic-button}},  // 或 [{{.btn1}}, {{.btn2}}]
        click: (event) => {
            console.log("委托点击");
        },
        mouseenter: function(event) {
            event.target.style.opacity = "0.8";
        }
    });
}
```

### 动画API
```chtl
script {
    animate({
        duration: 1000,  // 毫秒
        easing: "ease-in-out",
        
        begin: {
            opacity: 0,
            transform: "scale(0.8)"
        },
        
        when: [
            {
                at: 0.5,
                opacity: 0.8,
                transform: "scale(1.1)"
            }
        ],
        
        end: {
            opacity: 1,
            transform: "scale(1)"
        },
        
        loop: 2,
        direction: "alternate",
        delay: 200,
        callback: () => console.log("动画完成")
    });
}
```

---

## CMOD模块系统

CMOD是CHTL的模块化打包格式。

### 标准目录结构

```
ModuleName/
├── src/
│   ├── ModuleName.chtl    # 主模块文件（有子模块时可选）
│   └── Other.chtl         # 其他文件
└── info/
    └── ModuleName.chtl    # 模块信息文件
```

### 模块信息文件
```chtl
[Info] {
    name = "chtholly";
    version = "1.0.0";
    description = "珂朵莉主题模块";
    author = "CHTL Team";
    license = "MIT";
    dependencies = "";
    category = "theme";
    minCHTLVersion = "1.0.0";
    maxCHTLVersion = "2.0.0";
}

// 外部查询表（系统自动生成）
[Export] {
    @Style ChthollyStyle, ChthollyCard;
    @Element ChthollyPage, ChthollySection;
    @Var ChthollyColors, ChthollyFonts;
}
```

### 子模块结构

```
Chtholly/
├── src/
│   ├── (Chtholly.chtl)    # 主模块可选
│   ├── Space/
│   │   ├── src/
│   │   │   └── Space.chtl
│   │   └── info/
│   │       └── Space.chtl
│   └── Other/
│       ├── src/
│       │   └── Other.chtl
│       └── info/
│           └── Other.chtl
└── info/
    └── Chtholly.chtl
```

### CMOD使用

```chtl
// 导入整个模块（包括所有子模块）
[Import] @Chtl from "Chtholly";

// 导入特定子模块
[Import] @Chtl from "Chtholly.Space";

// 使用方法：
// 1. 在项目目录创建 module 文件夹
// 2. 将 .cmod 文件放入 module 文件夹
// 3. 使用 [Import] 导入
```

---

## 语法速查表

### 注释
- `//` - 单行注释（不生成）
- `/* */` - 多行注释（不生成）
- `--` - 生成注释

### 声明块
- `[Template]` - 模板定义
- `[Custom]` - 自定义定义
- `[Origin]` - 原始嵌入
- `[Configuration]` - 配置
- `[Import]` - 导入
- `[Namespace]` - 命名空间
- `[Info]` - 模块信息

### 引用前缀
- `@Style` - 样式引用
- `@Element` - 元素引用
- `@Var` - 变量引用
- `@Html` - HTML引用
- `@JavaScript` - JS引用
- `@Chtl` - CHTL模块引用

### 操作关键字
- `inherit` - 继承
- `delete` - 删除
- `insert` - 插入
- `except` - 约束
- `text` - 文本内容
- `style` - 样式块

### JavaScript增强
- `{{ }}` - 增强选择器
- `->` - CHTL操作符
- `listen` - 事件监听
- `delegate` - 事件委托
- `animate` - 动画API