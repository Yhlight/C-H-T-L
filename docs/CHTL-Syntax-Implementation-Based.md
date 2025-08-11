# CHTL 语法参考文档（基于实现）

本文档基于CHTL编译器的C++代码实现，准确反映当前支持的语法特性。

## 目录

1. [注释系统](#1-注释系统)
2. [文本内容](#2-文本内容)
3. [元素和属性](#3-元素和属性)
4. [样式系统](#4-样式系统)
5. [脚本系统](#5-脚本系统)
6. [模板系统](#6-模板系统)
7. [自定义系统](#7-自定义系统)
8. [继承系统](#8-继承系统)
9. [操作系统](#9-操作系统)
10. [约束系统](#10-约束系统)
11. [原始嵌入](#11-原始嵌入)
12. [导入系统](#12-导入系统)
13. [命名空间](#13-命名空间)
14. [配置系统](#14-配置系统)
15. [特殊块](#15-特殊块)

---

## 1. 注释系统

根据`TokenType`和解析器实现，支持三种注释：

```chtl
// 单行注释 (SINGLE_LINE_COMMENT) - 不会生成到输出
/* 多行注释 (MULTI_LINE_COMMENT) - 不会生成到输出 */
-- HTML注释 (HTML_COMMENT) - 会生成到输出
```

## 2. 文本内容

### text块语法
根据`StandardParser::parseText()`实现：

```chtl
text {
    "双引号字符串"
    '单引号字符串'  
    无引号字面量
}
```

注意：元素内的直接字符串（如`div { "文本" }`）在当前实现中**不支持**。必须使用`text { }`块。

## 3. 元素和属性

### 元素定义
根据`StandardParser::parseElement()`：

```chtl
div { }
div.className { }      # 类选择器
div#idName { }         # ID选择器
div.class1.class2 { }  # 多个类
```

### 属性赋值
根据`checkAttribute()`和CE对等式：

```chtl
div {
    id: "main";        # 使用冒号
    class = "box";     # 使用等号（完全等价）
    data-value: "123";
}
```

## 4. 样式系统

### 局部样式块
根据`parseStyleBlock()`和`parseStyleContent()`：

```chtl
div {
    style {
        # 内联样式
        width: 100px;
        color: red;
        
        # 类选择器（自动添加class）
        .box {
            padding: 20px;
        }
        
        # ID选择器（自动添加id）
        #main {
            background: white;
        }
        
        # & 符号（用于伪类/伪元素）
        &:hover {
            opacity: 0.8;
        }
        
        # 样式引用
        @Style ThemeColors;
        @Var Colors;
    }
}
```

### 全局样式
```chtl
style {
    # 这是全局样式块
    body {
        margin: 0;
    }
}

style .container {
    # 带选择器的全局样式
    width: 100%;
}
```

## 5. 脚本系统

### 脚本块
根据`parseScriptBlock()`实现：

```chtl
# 局部脚本（在元素内）
div {
    script {
        console.log("局部脚本");
    }
}

# 全局脚本
script {
    # 脚本内容原样保留，由 CHTL JS 处理
    # CHTL JS 会处理以下增强语法：
    # - {{}} 选择器
    # - -> 操作符
    # - listen/delegate/animate API
}
```

## 6. 模板系统

根据`parseTemplate()`实现，支持三种模板类型：

### 样式模板
```chtl
[Template] @Style DefaultText {
    color: black;
    font-size: 14px;
    line-height: 1.6;
}
```

### 元素模板
```chtl
[Template] @Element Card {
    div {
        class: "card";
        h3 { text { "标题" } }
        p { text { "内容" } }
    }
}
```

### 变量组模板
```chtl
[Template] @Var ThemeColors {
    primary: #007bff;
    secondary: #6c757d;
}
```

## 7. 自定义系统

根据`parseCustom()`实现，与模板类似但支持特例化：

```chtl
[Custom] @Style FlexBox {
    display: flex;
    align-items: center;
}

[Custom] @Element Button {
    button {
        class: "btn";
        text { "按钮" }
    }
}

[Custom] @Var Spacing {
    small: 8px;
    medium: 16px;
    large: 24px;
}
```

## 8. 继承系统

根据`parseInherit()`实现：

```chtl
# 显式继承
[Template] @Style Extended {
    inherit @Style Base;
    font-weight: bold;
}

# 在元素中继承
div {
    inherit @Element BaseDiv;
}
```

## 9. 操作系统

### 删除操作
根据`parseDelete()`和`parseDeleteTarget()`：

```chtl
# 在元素内删除
div {
    delete span;          # 删除元素
    delete div[0];        # 索引删除
    delete @Element Box;  # 删除引用
}

# 在特例化中删除
@Style MyStyle {
    delete margin, padding;  # 逗号分隔的多项删除
}

# 删除带连字符的CSS属性
style {
    delete line-height, background-color;
}
```

### 插入操作
根据`parseInsert()`：

```chtl
div {
    insert at top {
        h1 { text { "顶部" } }
    }
    
    insert at bottom {
        p { text { "底部" } }
    }
    
    insert before span {
        hr { }
    }
    
    insert after div[0] {
        p { text { "在第一个div后" } }
    }
    
    insert replace span {
        strong { text { "替换内容" } }
    }
}
```

## 10. 约束系统

根据`parseExceptConstraints()`：

```chtl
div {
    except span, p;                    # 禁止特定元素
    except [Custom] @Element Box;      # 禁止特定自定义元素
    except @Html;                      # 禁止所有HTML元素
    except [Template] @Var;            # 禁止变量组模板
    except [Custom];                   # 禁止所有自定义类型
}

# 命名空间中的全局约束
[Namespace] RestrictedSpace {
    except [Template];
}
```

## 11. 原始嵌入

根据`parseOrigin()`：

```chtl
# 块式定义
[Origin] @Html widgetName {
    <div>原始HTML</div>
}

[Origin] @Style resetCSS {
    * { margin: 0; padding: 0; }
}

[Origin] @JavaScript utils {
    function helper() { return true; }
}

# 内联定义（带分号）
[Origin] @Html inline: "<span>内联HTML</span>";

# 使用原始嵌入
body {
    @Html widgetName;
}
```

## 12. 导入系统

根据`parseImport()`和`parseImportStatement()`：

```chtl
# 导入CHTL模块
[Import] @Chtl from "module";
[Import] @Chtl from "ui-kit" as UI;

# 导入CJmod（检查 @CJmod 标识符）
[Import] @CJmod from "reactive";

# 导入其他资源
[Import] @Html from "template.html" as header;
[Import] @Style from "theme.css";
[Import] @JavaScript from "utils.js";

# 导入特定项
[Import] [Custom] @Element Button from "ui.chtl";
[Import] [Template] @Style Theme from "styles.chtl";

# 通配符导入
[Import] * from "modules/*";
```

## 13. 命名空间

根据`parseNamespace()`：

```chtl
[Namespace] UIComponents {
    [Custom] @Element Button { }
    [Template] @Style Theme { }
}

# 使用命名空间（from语法）
@Element Button from UIComponents;
```

## 14. 配置系统

根据`parseConfiguration()`：

```chtl
[Configuration] {
    DEBUG_MODE = true;
    INDEX_INITIAL_COUNT = 0;
    
    [Name] {
        CUSTOM_STYLE = [@Style, @样式];
        KEYWORD_DELETE = [delete, 删除];
        OPTION_COUNT = 3;
    }
}

# 命名配置块
[Configuration] Development {
    DEBUG_MODE = true;
}
```

## 15. 特殊块

根据`parseSpecialBlock()`，支持以下特殊块：

- `[Template]` - 模板定义
- `[Custom]` - 自定义定义
- `[Origin]` - 原始嵌入
- `[Configuration]` - 配置
- `[Import]` - 导入
- `[Namespace]` - 命名空间
- `[Info]` - 模块信息（用于CMOD）
- `[Export]` - 导出
- `[Script]` - 脚本块

## 实现差异总结

### 已实现但与文档不同：
1. **文本必须使用text块** - 不支持`div { "文本" }`直接语法
2. **@CJmod已修正为正式Token** - 现在是 AT_CJMOD 类型

### CHTL 与 CHTL JS 的职责划分：

#### CHTL 编译器负责：
- HTML/CSS/JS 的基本结构生成
- 模板和自定义系统的解析和展开
- 样式块的处理和CSS生成
- 脚本块内容的原样保留（传递给CHTL JS）

#### CHTL JS 编译器负责：
- `{{}}` 选择器语法的解析和转换
- `->` 操作符的处理
- `listen`、`delegate`、`animate` 等增强API的实现
- 所有JavaScript增强语法的处理

### 文档中提到但属于CHTL JS范畴的功能：
1. **{{}}选择器** - CHTL JS功能
2. **->操作符** - CHTL JS功能
3. **listen/delegate/animate** - CHTL JS API

### 官方语法但实现不完整：
1. **变量组函数调用** - `ThemeColor(primary)` - 解析器已实现，但生成器处理不完整
2. **Custom关键字** - `Custom @Element Name;` 使用语法未实现（只支持定义）
3. **槽位系统（slot）** - 未见实现

### 建议确认的功能：
1. 元素内直接字符串支持
2. 变量组的实际使用方式
3. JavaScript增强API的实现位置
4. Custom @Element的使用语法