# CHTL 语法参考文档

基于编译器实际实现的完整语法文档。

## 目录

1. [基础语法](#1-基础语法)
2. [HTML元素](#2-html元素)
3. [样式系统](#3-样式系统)
4. [脚本系统](#4-脚本系统)
5. [模板系统](#5-模板系统)
6. [自定义系统](#6-自定义系统)
7. [继承系统](#7-继承系统)
8. [操作系统](#8-操作系统)
9. [约束系统](#9-约束系统)
10. [原始嵌入](#10-原始嵌入)
11. [导入系统](#11-导入系统)
12. [命名空间](#12-命名空间)
13. [配置系统](#13-配置系统)
14. [注释系统](#14-注释系统)
15. [导出系统](#15-导出系统)

---

## 1. 基础语法

### 1.1 文件结构
```chtl
# .chtl 文件
# UTF-8 编码
# 支持多个顶层声明

[Configuration] { }
[Import] @Chtl from "module";
[Namespace] MySpace { }
[Template] @Element Card { }
[Custom] @Style Theme { }
```

### 1.2 标识符
- 字母、数字、下划线
- 必须以字母或下划线开头
- 区分大小写

### 1.3 属性赋值
```chtl
element {
    class: "container";    # 冒号赋值
    id = "main";          # 等号赋值（等价）
}
```

---

## 2. HTML元素

### 2.1 基本元素
```chtl
# 空元素
div { }

# 带文本的元素
h1 { "标题文本" }

# 多个文本节点
p {
    "第一段文本"
    "第二段文本"
}
```

### 2.2 元素属性
```chtl
div {
    class: "container";
    id: "main";
    data-value: "123";
}
```

### 2.3 选择器语法
```chtl
# 类选择器
div.container { }
div.class1.class2 { }

# ID选择器
div#main { }

# 组合
div#main.container { }
```

### 2.4 文本内容
```chtl
# text 关键字（显式）
p {
    text { "显式文本内容" }
}

# 直接字符串（隐式）
p { "隐式文本内容" }
```

---

## 3. 样式系统

### 3.1 内联样式
```chtl
div {
    style {
        color: red;
        font-size: 16px;
        margin: 10px;
    }
}
```

### 3.2 全局样式块
```chtl
# 元素选择器
style p {
    line-height: 1.6;
}

# 类选择器
style .container {
    width: 100%;
}

# ID选择器
style #header {
    height: 60px;
}

# 组合选择器
style div.card > h2 {
    color: blue;
}
```

### 3.3 媒体查询
```chtl
style @media (max-width: 768px) {
    .container {
        padding: 10px;
    }
}
```

---

## 4. 脚本系统

### 4.1 内联脚本（局部）
```chtl
div {
    id: "button";
    script {
        # 局部脚本，作用于父元素
        console.log("Local script");
    }
}
```

### 4.2 全局脚本
```chtl
script {
    # JavaScript 代码
    function init() {
        console.log("Global script");
    }
}
```

### 4.3 CHTL JS 增强语法
```chtl
script {
    # select 语法
    select #button {
        on click {
            console.log("Button clicked");
        }
    }
    
    # 箭头函数简写
    select .item {
        on mouseenter => this.classList.add('hover');
        on mouseleave => this.classList.remove('hover');
    }
}
```

---

## 5. 模板系统

### 5.1 元素模板
```chtl
[Template] @Element Card {
    div {
        class: "card";
        h3 { "标题" }
        p { "内容" }
    }
}

# 使用模板
@Element Card;
```

### 5.2 样式模板
```chtl
[Template] @Style BaseText {
    font-family: Arial, sans-serif;
    line-height: 1.6;
    color: #333;
}

# 在样式中使用
div {
    style {
        @Style BaseText;
        font-size: 14px;
    }
}
```

### 5.3 变量组模板
```chtl
[Template] @Var Colors {
    primary: #007bff;
    secondary: #6c757d;
    success: #28a745;
}

# 使用变量（通过样式）
style {
    .btn-primary {
        background-color: #007bff;  # 需要手动引用值
    }
}
```

---

## 6. 自定义系统

### 6.1 自定义元素
```chtl
[Custom] @Element Button {
    button {
        class: "btn";
        "点击我"
    }
}

# 使用自定义元素
Custom @Element Button;
```

### 6.2 自定义样式
```chtl
[Custom] @Style ButtonStyle {
    padding: 10px 20px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
}

# 使用自定义样式
button {
    style {
        @Style ButtonStyle;
        background-color: blue;
    }
}
```

### 6.3 自定义变量组
```chtl
[Custom] @Var Spacing {
    small: 8px;
    medium: 16px;
    large: 24px;
}
```

---

## 7. 继承系统

### 7.1 样式继承
```chtl
[Template] @Style Base {
    color: #333;
    font-size: 14px;
}

[Custom] @Style Extended {
    inherit @Style Base;
    font-weight: bold;
}
```

### 7.2 元素继承
```chtl
[Template] @Element BaseCard {
    div.card {
        padding: 20px;
    }
}

[Custom] @Element PrimaryCard {
    inherit @Element BaseCard;
    # 添加或覆盖内容
}
```

### 7.3 变量组继承
```chtl
[Template] @Var BaseColors {
    black: #000;
    white: #fff;
}

[Custom] @Var ExtendedColors {
    inherit @Var BaseColors;
    red: #ff0000;
}
```

---

## 8. 操作系统

### 8.1 删除操作
```chtl
# 删除特定元素
div {
    p { "段落1" }
    span { "文本" }
    delete span;  # 删除所有span
}

# 删除属性
div {
    class: "container";
    id: "main";
    delete id;
}

# 删除样式属性
[Custom] @Style MyStyle {
    inherit @Style BaseStyle;
    style {
        delete margin, padding;
    }
}

# 索引删除
div {
    p { "1" }
    p { "2" }
    p { "3" }
    delete p[1];  # 删除第二个p
}

# 删除引用元素
div {
    delete @Element Card;
    delete Custom @Element Button[0];
}
```

### 8.2 插入操作
```chtl
# 在顶部插入
div {
    insert at top {
        h1 { "新标题" }
    }
}

# 在底部插入
div {
    insert at bottom {
        p { "页脚" }
    }
}

# 在元素前插入
div {
    p { "现有段落" }
    insert before p {
        hr { }
    }
}

# 在元素后插入
div {
    h1 { "标题" }
    insert after h1 {
        p { "副标题" }
    }
}

# 替换元素
div {
    span { "旧文本" }
    insert replace span {
        strong { "新文本" }
    }
}

# 插入到索引位置
div {
    insert p[0] {
        "插入到第一个p"
    }
}

# 插入引用元素
div {
    insert after @Element Header {
        hr { }
    }
}
```

---

## 9. 约束系统

### 9.1 元素内约束
```chtl
# 精确约束 - 禁止特定元素
div {
    except span, p;  # 禁止span和p
    
    h1 { "允许" }
    # span { "不允许" }  # 错误
}

# 禁止特定自定义元素
div {
    except [Custom] @Element Modal;
}
```

### 9.2 类型约束
```chtl
# 禁止所有HTML元素
div {
    except @Html;
    
    # 只允许自定义元素
    Custom @Element MyComponent;
}

# 禁止特定类型
div {
    except [Custom];           # 禁止所有自定义
    except [Template] @Var;    # 禁止变量组模板
}
```

### 9.3 命名空间全局约束
```chtl
[Namespace] Restricted {
    except [Template];  # 禁止定义模板
    
    # [Template] @Element X { }  # 错误
    [Custom] @Element Y { }      # 允许
}
```

---

## 10. 原始嵌入

### 10.1 命名的原始嵌入
```chtl
# CSS原始嵌入
[Origin] @Style reset {
* {
    margin: 0;
    padding: 0;
}
}

# JavaScript原始嵌入
[Origin] @JavaScript utils {
function helper() {
    return true;
}
}

# HTML原始嵌入
[Origin] @Html widget {
<div id="legacy">旧代码</div>
}
```

### 10.2 使用原始嵌入
```chtl
# 在样式中使用
style {
    @Style reset;
}

# 在脚本中使用
script {
    @JavaScript utils;
}

# 在body中使用
body {
    @Html widget;
}
```

### 10.3 内联原始嵌入
```chtl
# 内联定义（带分号）
[Origin] @Style inline: "body { margin: 0; }";
[Origin] @JavaScript code: "console.log('hello');";
```

---

## 11. 导入系统

### 11.1 CHTL模块导入
```chtl
# 导入单个模块
[Import] @Chtl from "components";

# 导入并重命名
[Import] @Chtl from "ui-kit" as UI;

# 导入多个
[Import] @Chtl from "utils", "helpers";

# 通配符导入
[Import] @Chtl from "modules/*";
[Import] @Chtl from "modules/*.cmod";
```

### 11.2 CJmod导入
```chtl
# 导入CJmod模块
[Import] @CJmod from "reactive";

# 导入内置模块
[Import] @CJmod from "builtin:async-flow";
```

### 11.3 其他资源导入
```chtl
# 导入HTML
[Import] @Html from "./template.html" as header;

# 导入CSS
[Import] @Style from "./theme.css";

# 导入JavaScript
[Import] @JavaScript from "./utils.js";
```

---

## 12. 命名空间

### 12.1 基本命名空间
```chtl
[Namespace] UI {
    [Custom] @Element Button { }
    [Template] @Style Theme { }
}

# 使用命名空间成员
UI::@Element Button;
```

### 12.2 嵌套命名空间
```chtl
[Namespace] App {
    [Namespace] Components {
        [Custom] @Element Header { }
    }
}

# 使用
App::Components::@Element Header;
```

---

## 13. 配置系统

### 13.1 基本配置
```chtl
[Configuration] {
    # 调试模式
    DEBUG_MODE = true;
    
    # 索引起始值
    INDEX_INITIAL_COUNT = 0;
    
    # 禁用名称组
    DISABLE_NAME_GROUP = false;
}
```

### 13.2 名称配置（关键字别名）
```chtl
[Configuration] {
    [Name] {
        # 自定义关键字别名
        CUSTOM_STYLE = [@Style, @样式, @CSS];
        CUSTOM_ELEMENT = [@Element, @元素];
        KEYWORD_DELETE = [delete, 删除];
        KEYWORD_TEXT = [text, 文本];
        
        # 限制选项数量
        OPTION_COUNT = 3;
    }
}
```

### 13.3 命名配置块
```chtl
[Configuration] Development {
    DEBUG_MODE = true;
}

[Configuration] Production {
    DEBUG_MODE = false;
}
```

---

## 14. 注释系统

### 14.1 单行注释
```chtl
# 这是单行注释
// 这也是单行注释

div {
    # 元素内注释
    class: "test";  # 行尾注释
}
```

### 14.2 生成注释
```chtl
-- 这个注释会生成到输出中

div {
    -- HTML注释
}

style {
    -- CSS注释
}

script {
    -- JavaScript注释
}
```

---

## 15. 导出系统

### 15.1 从命名空间导出
```chtl
[Export] from UI {
    [Custom] @Element Button;
    [Template] @Style Theme;
}
```

### 15.2 导出所有
```chtl
[Export] from MyNamespace {
    [Custom] *;
    [Template] *;
}
```

---

## 语法速查表

### 块声明
- `[Configuration]` - 配置块
- `[Namespace]` - 命名空间
- `[Template]` - 模板定义
- `[Custom]` - 自定义定义
- `[Origin]` - 原始嵌入
- `[Import]` - 导入
- `[Export]` - 导出
- `[Info]` - 模块信息
- `[Script]` - 脚本块

### 引用前缀
- `@Element` - 元素引用
- `@Style` - 样式引用
- `@Var` - 变量引用
- `@Html` - HTML引用
- `@JavaScript` - JS引用
- `@Chtl` - CHTL模块引用
- `@CJmod` - CJmod模块引用

### 操作关键字
- `inherit` - 继承
- `delete` - 删除
- `insert` - 插入
- `except` - 约束

### 位置关键字
- `at top` - 顶部
- `at bottom` - 底部
- `before` - 之前
- `after` - 之后
- `replace` - 替换

### 特殊关键字
- `text` - 文本内容
- `style` - 样式块
- `script` - 脚本块
- `from` - 来源
- `as` - 别名
- `Custom` - 自定义实例
- `::` - 命名空间访问

### 注释
- `#` - 单行注释
- `//` - 单行注释
- `--` - 生成注释