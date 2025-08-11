# CHTL 快速参考

## 基本语法

### 元素和文本
```chtl
div { }                          // 元素
text { "内容" }                  // 文本
div { id: "app"; class: "main"; } // 属性
```

### 注释
```chtl
// 单行注释
/* 多行注释 */
-- 生成器注释（会出现在输出中）
```

## 模板

### 定义模板
```chtl
[Template] @Element Button { }    // 元素模板
[Template] @Style Theme { }       // 样式模板  
[Template] @Var Colors { }        // 变量模板
```

### 使用模板
```chtl
@Element Button;                  // 使用元素
@Style Theme;                     // 使用样式
color: Colors(primary);           // 使用变量
```

## 自定义组件

### 定义
```chtl
[Custom] @Element Card {
    div { class: "card"; }
}
```

### 特例化
```chtl
@Element Card {
    delete class;                 // 删除属性
    style { padding: 20px; }      // 添加样式
}
```

## 操作

### 继承
```chtl
inherit @Element BaseComponent;
inherit @Style BaseStyle;
```

### 删除
```chtl
delete elementName;               // 删除元素
delete @Style StyleName;          // 删除样式引用
delete div[0];                    // 删除第一个 div
```

### 插入
```chtl
insert after div[0] { }           // 在后面插入
insert before span { }            // 在前面插入
insert replace p { }              // 替换
insert at top { }                 // 在顶部插入
insert at bottom { }              // 在底部插入
```

## 局部样式

### 内联样式
```chtl
div {
    style {
        width: 100px;
        height: 100px;
    }
}
```

### 类和 ID
```chtl
div {
    style {
        .box {                    // 自动添加类名
            padding: 10px;
        }
        #main {                   // 自动添加 ID
            margin: 0 auto;
        }
        &:hover {                 // 伪类
            opacity: 0.8;
        }
    }
}
```

## 局部脚本（CHTL JS）

### 增强选择器
```chtl
script {
    {{#id}}                       // ID 选择器
    {{.class}}                    // 类选择器
    {{tag}}                       // 标签选择器
    {{&}}                         // 当前元素
}
```

### 增强方法
```chtl
{{selector}}->listen({            // 事件监听
    click: function(e) { }
});

{{selector}}->animate({           // 动画
    target: "opacity",
    from: 0, to: 1,
    duration: 1000
});

{{selector}}->delegate(".child", { // 事件委托
    click: function(e) { }
});
```

## 导入导出

### 导入
```chtl
[Import] @Element Button from "./Button.chtl";
[Import] * from "./utils.chtl";
[Import] @Style Theme as MyTheme from "./theme.chtl";
[Import] from namespace Components;
```

### 导出
```chtl
[Export] {
    @Element Button;
    @Style Theme as DefaultTheme;
    namespace MyComponents;
}
```

## 命名空间

### 定义
```chtl
[Namespace] MyApp {
    [Template] @Element Header { }
    [Template] @Style Colors { }
}
```

### 使用
```chtl
@Element MyApp.Header;
color: MyApp.Colors(primary);
```

## 配置

```chtl
[Configuration] {
    INDEX_INITIAL_COUNT = 0;
    DEBUG_MODE = false;
    
    [Name] {
        CUSTOM_ELEMENT = [@Element, @元素];
        CUSTOM_STYLE = [@Style, @样式];
    }
}
```

## 原始嵌入

```chtl
[Origin] @Html svgIcon {
    <svg>...</svg>
}

[Origin] @JavaScript tracking {
    // 第三方脚本
}

[Origin] @Style legacyCss {
    /* 旧版 CSS */
}

// 使用
body {
    [Origin] @Html svgIcon;
}
```

## 变量组调用

```chtl
[Template] @Var Theme {
    primary: blue;
    secondary: green;
}

// 使用
color: Theme(primary);
background: Theme(secondary = red);  // 覆盖值
```

## 约束

```chtl
div {
    class: "desktop";
} except mobile;

div {
    class: "mobile";  
} except desktop;
```

## 常用模式

### 响应式组件
```chtl
[Custom] @Element ResponsiveBox {
    div {
        class: "box";
        style {
            .box {
                width: 100%;
                max-width: 1200px;
                margin: 0 auto;
                padding: 20px;
                
                @media (max-width: 768px) {
                    padding: 10px;
                }
            }
        }
    }
}
```

### 带插槽的组件
```chtl
[Template] @Element Modal {
    div {
        class: "modal";
        
        slot { name: "header"; }
        slot { name: "content"; }
        slot { name: "footer"; }
    }
}
```

### 事件处理
```chtl
button {
    id: "submit-btn";
    text { "提交" }
    
    script {
        {{&}}->listen({
            click: function(e) {
                e.preventDefault();
                // 处理提交
            }
        });
    }
}
```

---

更多详细信息，请参阅[完整文档](./README.md)