# CHTL语法完整指南

## 基础语法

### 注释
```chtl
// 单行注释
/* 多行注释 */
-- 生成性注释（会被转换为HTML/CSS/JS注释）
```

### 文本节点
```chtl
text { "这是文本内容" }
text { 无引号文本也支持 }
```

### 元素节点
```chtl
div {
    id: "container";  // 或 id = "container";
    class: "main-content";
    
    span { text { "嵌套内容" } }
}
```

### 局部样式块
```chtl
div {
    style {
        // 内联样式
        width: 100px;
        height: 200px;
        
        // 自动添加类名
        .box {
            background: red;
        }
        
        // 使用&引用当前元素
        &:hover {
            opacity: 0.8;
        }
    }
}
```

## 模板系统

### 样式组模板
```chtl
[Template] @Style ButtonStyle {
    padding: 10px 20px;
    border-radius: 5px;
    cursor: pointer;
}

button {
    style { @Style ButtonStyle; }
}
```

### 元素模板
```chtl
[Template] @Element Card {
    div {
        class: "card";
        style { /* ... */ }
    }
}

body { @Element Card; }
```

### 变量组模板
```chtl
[Template] @Var Colors {
    primary: "#007bff";
    secondary: "#6c757d";
}

div {
    style {
        color: Colors(primary);
    }
}
```

## 自定义系统

### 无值样式组
```chtl
[Custom] @Style FlexBox {
    display,
    flex-direction,
    justify-content;
}

div {
    style {
        @Style FlexBox {
            display: flex;
            flex-direction: row;
            justify-content: center;
        }
    }
}
```

### 特例化操作
```chtl
[Custom] @Element Box {
    div { /* ... */ }
    span { /* ... */ }
}

body {
    @Element Box {
        // 删除元素
        delete span;
        
        // 插入元素
        insert after div[0] {
            p { text { "新内容" } }
        }
        
        // 索引访问
        div[1] {
            style { color: red; }
        }
    }
}
```

## 原始嵌入
```chtl
[Origin] @Html {
    <div class="raw-html">原始HTML</div>
}

[Origin] @Style {
    .raw-css { color: blue; }
}

[Origin] @JavaScript {
    console.log('原始JavaScript');
}
```

## 导入系统
```chtl
// 导入HTML/CSS/JS
[Import] @Html from "path/to/file.html" as htmlContent
[Import] @Style from "path/to/styles.css"
[Import] @JavaScript from "path/to/script.js"

// 导入CHTL文件
[Import] @Chtl from "components.chtl"

// 导入特定项
[Import] [Template] @Style ButtonStyle from "ui.chtl"
[Import] [Custom] @Element Card from "components.chtl" as MyCard

// 导入模块
[Import] @Chtl from Chtholly  // 从module文件夹
[Import] @CJmod from MyExtension
```

## 命名空间
```chtl
[Namespace] UI {
    [Template] @Element Button { /* ... */ }
}

// 使用命名空间
body {
    @Element Button from UI;
}
```

## 约束系统
```chtl
// 精确约束
div {
    except span, [Custom] @Element Box;
}

// 类型约束
body {
    except @Html;  // 禁止HTML元素
    except [Template];  // 禁止模板
}

// 全局约束
[Namespace] Strict {
    except [Custom];  // 命名空间内禁止自定义
}
```

## CHTL JS扩展

### 局部脚本块
```chtl
div {
    style {
        .box { /* ... */ }
    }
    
    script {
        // CHTL JS代码
        {{.box}}.addEventListener('click', () => {
            console.log('Clicked!');
        });
    }
}
```

### 增强选择器
```chtl
script {
    {{button}}        // 自动推断（标签/类/ID）
    {{.className}}    // 类选择器
    {{#idName}}       // ID选择器
    {{div[0]}}        // 索引访问
    {{.parent .child}} // 后代选择器
}
```

### CHTL JS特有语法
```chtl
script {
    // 使用->明确CHTL语法
    {{.button}}->listen({
        click: () => { /* ... */ },
        mouseenter: handleHover
    });
    
    // 事件委托
    {{.container}}->delegate({
        target: {{.dynamic-item}},
        click: handleItemClick
    });
    
    // 动画
    let fadeIn = animate({
        duration: 300,
        easing: 'ease-in-out',
        begin: { opacity: 0 },
        end: { opacity: 1 }
    });
    
    fadeIn({{.element}});
}
```

## 配置组
```chtl
[Configuration] {
    INDEX_INITIAL_COUNT = 0;
    DEBUG_MODE = false;
    
    [Name] {
        CUSTOM_STYLE = [@Style, @style];
        KEYWORD_TEXT = text;
        // 更多自定义关键字...
    }
}
```

## 最佳实践

### 1. 模块化设计
```chtl
// components/Button.chtl
[Namespace] Components

[Template] @Element Button {
    button {
        style { @Style ButtonBase; }
        slot;  // 插槽内容
    }
}

// main.chtl
[Import] @Chtl from "components/Button.chtl"

body {
    @Element Button from Components {
        text { "点击我" }
    }
}
```

### 2. 主题系统
```chtl
[Template] @Var Theme {
    // 颜色
    primary: "#007bff";
    secondary: "#6c757d";
    success: "#28a745";
    
    // 间距
    spacing-xs: "4px";
    spacing-sm: "8px";
    spacing-md: "16px";
    
    // 字体
    font-primary: "'Helvetica', sans-serif";
}

[Template] @Style ThemedButton {
    background: Theme(primary);
    padding: Theme(spacing-sm) Theme(spacing-md);
    font-family: Theme(font-primary);
}
```

### 3. 响应式设计
```chtl
div {
    style {
        .container {
            width: 100%;
            max-width: 1200px;
            margin: 0 auto;
            
            @media (max-width: 768px) {
                padding: 0 20px;
            }
        }
    }
}
```

### 4. 组件组合
```chtl
[Template] @Element Card {
    div {
        style { @Style CardStyle; }
        
        [slot header] div {
            style { @Style CardHeader; }
        }
        
        [slot content] div {
            style { @Style CardContent; }
        }
        
        [slot footer] div {
            style { @Style CardFooter; }
        }
    }
}

// 使用
@Element Card {
    [header] { h3 { text { "标题" } } }
    [content] { p { text { "内容" } } }
    [footer] { button { text { "操作" } } }
}
```

## 高级技巧

### 1. 条件渲染
```chtl
div {
    [if condition] {
        span { text { "条件为真" } }
    }
    [else] {
        span { text { "条件为假" } }
    }
}
```

### 2. 循环生成
```chtl
ul {
    [for item in items] {
        li { text { item.name } }
    }
}
```

### 3. 动态样式
```chtl
div {
    style {
        .dynamic {
            color: {{dynamicColor}};
            transform: rotate({{rotation}}deg);
        }
    }
}
```

### 4. 混合使用
```chtl
[Import] @Chtl from Chtholly

html {
    head {
        title: "CHTL高级示例";
        
        style {
            @import url('https://fonts.googleapis.com/css2?family=Noto+Sans');
            
            * {
                @Style Chtholly.ChthollysBase;
            }
        }
    }
    
    body {
        [Origin] @Html {
            <div id="app"></div>
        }
        
        script {
            // Vue.js集成示例
            {{#app}}->mount({
                data: () => ({
                    message: 'Hello CHTL!'
                }),
                template: `<h1>{{ message }}</h1>`
            });
        }
    }
}
```