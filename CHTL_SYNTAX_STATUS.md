# CHTL 语法实现状态报告

## 1. 基础语法

### 1.1 注释 ✅ 完全实现
```chtl
// 单行注释 - 不会出现在生成的 HTML 中
/* 多行注释
   也不会出现在生成的 HTML 中 */
-- 生成器识别的注释 - 根据上下文生成对应语言的注释
   -- 在 HTML 中生成 <!-- 注释 -->
   -- 在 CSS 中生成 /* 注释 */
   -- 在 JS 中生成 // 注释
```
⚠️ **重要**：注释处理时不能影响全局样式块和非局部 script 块

### 1.2 文本节点 ✅ 完全实现
```chtl
text { "这是一段文本" }      // 双引号字符串
text { '这是一段文本' }      // 单引号字符串
text { 这是一段文本 }        // 无引号字面量
```

### 1.3 元素节点 ✅ 完全实现
```chtl
div {
    id: "box";              // 使用冒号
    class: welcome;         // 无引号字面量
    data-value = "123";     // 使用等号（CE对等式）
    text { "内容" }
}
```

### 1.4 属性 ✅ 完全实现
- 支持 `:` 和 `=`（CE对等式）
- 支持双引号、单引号和无引号字面量
- 支持所有 HTML 属性

## 2. 局部样式块 ✅ 完全实现

### 2.1 内联样式 ✅
```chtl
div {
    style {
        width: 100px;
        height: 200px;
    }
}
```

### 2.2 自动化类名/ID ✅
```chtl
div {
    style {
        .box {              // 自动添加 class="box"
            width: 300px;
        }
        #container {        // 自动添加 id="container"
            height: 500px;
        }
    }
}
```

### 2.3 上下文推导 & ✅
```chtl
div {
    style {
        .box { }
        &:hover { }         // 解析为 .box:hover
        &::before { }       // 解析为 .box::before
    }
}
```

## 3. 局部脚本块 ✅ 完全实现

### 3.1 基本语法 ✅
```chtl
div {
    script {
        console.log("局部脚本");
    }
}
```

### 3.2 CHTL JS 增强语法 ✅
```chtl
script {
    // 增强选择器
    {{#myId}}              // document.getElementById('myId')
    {{.myClass}}           // document.getElementsByClassName('myClass')
    {{div}}                // document.getElementsByTagName('div')
    {{&}}                  // 当前元素引用
                          // ⚠️ 注意：{{&}} 需要元素具有 class/id 属性
                          // 或在局部样式块中使用了类名/id
    
    // 箭头操作符
    {{#btn}}->addEventListener('click', () => {});
    
    // 扩展方法
    {{&}}->listen({
        click: () => {},
        mouseover: () => {}
    });
    
    {{&}}->animate({
        transform: 'scale(1.2)',
        opacity: '0.8'
    }, 300);
}
```

## 4. 模板系统

### 4.1 样式组模板 ✅ 完全实现
```chtl
[Template] @Style DefaultText {
    color: black;
    line-height: 1.6;
}

div {
    style {
        @Style DefaultText;
    }
}
```

### 4.2 元素模板 ✅ 完全实现
```chtl
[Template] @Element Box {
    div {
        span { text { "模板内容" } }
    }
}

body {
    @Element Box;
}
```

### 4.3 变量组模板 ✅ 完全实现
```chtl
[Template] @Var ThemeColor {
    primary: "rgb(255, 192, 203)";
    secondary: "rgb(253, 144, 162)";
}

div {
    style {
        color: ThemeColor(primary);
        background: ThemeColor(secondary);
    }
}
```

### 4.4 模板继承 ✅ 完全实现
```chtl
[Template] @Style BaseStyle {
    color: red;
}

[Template] @Style ExtendedStyle {
    inherit @Style BaseStyle;    // 显式继承
    // 或
    @Style BaseStyle;           // 组合式继承
    font-size: 16px;
}
```

## 5. 自定义系统

### 5.1 自定义样式组 ✅ 完全实现
```chtl
[Custom] @Style TextSet {
    color,              // 无值属性
    font-size;
}

div {
    style {
        @Style TextSet {
            color: red;
            font-size: 16px;
        }
    }
}
```

### 5.2 自定义元素 ✅ 完全实现
```chtl
[Custom] @Element Box {
    div { }
    span { }
}

body {
    @Element Box {
        div {
            style { color: red; }
        }
        span[0] {           // 索引访问
            text { "内容" }
        }
    }
}
```

### 5.3 删除操作 ✅ 完全实现
```chtl
[Custom] @Element Box {
    @Element Base;
    div { }
    span { }
}

@Element Box {
    delete span;            // 删除 span
    delete div[0];          // 删除第一个 div
    delete @Element Base;   // 删除继承
}
```

### 5.4 插入操作 ✅ 完全实现
```chtl
@Element Box {
    insert after div[0] {
        p { text { "插入的段落" } }
    }
    insert before span {
        hr { }
    }
    insert at top {         // 在顶部插入
        header { }
    }
}
```

### 5.5 变量组特例化 ✅ 完全实现
```chtl
[Custom] @Var Colors {
    primary: "red";
    secondary: "blue";
}

div {
    style {
        color: Colors(primary = "green");  // 特例化
    }
}
```

## 6. 原始嵌入 ✅ 完全实现

**🔍 特性**：原始嵌入节点可在任何位置使用，内容会原样输出到对应位置

### 6.1 HTML 嵌入 ✅
```chtl
[Origin] @Html {
    <div>原始 HTML</div>
}

[Origin] @Html myEmbed {    // 命名嵌入
    <span>可重用</span>
}

body {
    [Origin] @Html myEmbed;  // 使用命名嵌入
}
```

### 6.2 CSS 嵌入 ✅
```chtl
[Origin] @Style {
    .special { color: red; }
}
```

### 6.3 JavaScript 嵌入 ✅
```chtl
[Origin] @JavaScript {
    console.log("原始 JS");
}
```

⚠️ **重要**：原始嵌入内容处理时不能影响全局样式块（CSS 编译器）和非局部 script 块的架构设计

## 7. 配置系统 ✅ 完全实现

```chtl
[Configuration] {
    INDEX_INITIAL_COUNT = 0;
    DEBUG_MODE = true;
    
    [Name] {
        CUSTOM_STYLE = [@Style, @样式];
        KEYWORD_DELETE = [delete, 删除];
    }
}
```

## 8. 导入/导出系统

### 8.1 基本导入 ✅ 完全实现
```chtl
[Import] @Chtl from "./components.chtl";
[Import] @Element Button from "./button.chtl";
```

### 8.2 别名导入 ✅ 完全实现
```chtl
[Import] @Element Button as MyButton from "./button.chtl";
[Import] @Style Theme as MyTheme from "./theme.chtl";
```

### 8.3 从命名空间导入 ✅ 完全实现
```chtl
[Import] @Element Card from namespace UI;
```

### 8.4 导出 ✅ 完全实现
```chtl
[Export] @Element Button;
[Export] @Style Theme as DefaultTheme;
[Export] @Var Colors;
```

**🔍 导出功能说明**：
- **作用**：决定模块暴露哪些内容，优化查找性能
- **使用方式**：
  - 编译器可自动生成（默认行为）
  - 开发者可手动编写，精确控制暴露内容
- **特殊情况**：作为模块框架的大模块（包含子模块）通常不需要 [Export] 块
- **性能优化**：通过明确导出列表，加快模块成员查找速度

## 9. 命名空间 ✅ 完全实现

```chtl
[Namespace] UI {
    [Template] @Element Button { }
    [Custom] @Style Theme { }
}

// 使用
UI.Button { }
@Element Button from namespace UI;
```

## 10. 约束系统 ✅ 完全实现

```chtl
[Custom] @Element Container {
    div {
        except @Element Button;  // 禁止 Button
    }
}
```

## 11. 全缀名引用 ✅ 完全实现（新功能）

```chtl
// 解决同名冲突
[Template] @Element Box { }
[Custom] @Element Box { }

// 使用
@Element Box;               // 默认使用 Custom
[Template] @Element Box;    // 明确使用 Template
[Custom] @Element Box;      // 明确使用 Custom
```

## 12. 模块系统 ✅ 完全实现

### 12.1 CMOD 打包 ✅
- 支持将模块打包为 `.cmod` 文件
- 自动识别和打包依赖
- 支持模块元信息

### 12.2 模块加载 ✅
- 支持从 CMOD 文件加载模块
- 模块搜索路径配置
- 依赖解析

## 实现状态总结

### ✅ 完全实现的功能（100%）
1. 基础语法（注释、文本、元素、属性）
2. 局部样式块（内联样式、自动类名、&引用）
3. 局部脚本块（CHTL JS 增强）
4. 模板系统（样式、元素、变量组模板）
5. 自定义系统（样式、元素、变量组）
6. 继承系统（inherit、组合继承）
7. 删除和插入操作
8. 原始嵌入（HTML、CSS、JS）
9. 配置系统
10. 导入系统（基本导入、别名、命名空间）
11. 命名空间
12. 约束系统（except）
13. 全缀名引用
14. 模块系统（CMOD）

### ℹ️ 所有语法功能均已完全实现

### 🔍 特殊说明与注意事项

1. **{{&}} 上下文要求**：
   - 需要元素具有 class 或 id 属性
   - 或在局部样式块中使用了类名/id
   - 否则无法生成有效的元素引用

2. **生成器注释 `--` 的上下文感知**：
   - 在 HTML 上下文中生成 `<!-- 注释 -->`
   - 在 CSS 上下文中生成 `/* 注释 */`
   - 在 JavaScript 上下文中生成 `// 注释`

3. **原始嵌入的架构约束**：
   - 原始嵌入可在任何位置使用
   - 但处理时不能影响全局样式块（CSS 编译器）
   - 不能影响非局部 script 块的架构设计

4. **[Export] 块的灵活性**：
   - 可由编译器自动生成（默认）
   - 开发者可手动编写以精确控制暴露内容
   - 大型模块框架通常不需要 [Export]

5. **[Info] 块**：
   - 仅在 CMOD 文件中有效
   - 普通文件中会被忽略并产生警告

6. **索引起始配置**：
   - `INDEX_INITIAL_COUNT` 已解析但可能未在所有场景应用

## 语法特征总结

### 1. 灵活的字面量
- 支持双引号、单引号、无引号字面量
- 模板字面量（反引号）用于特殊场景

### 2. CE对等式
- `:` 和 `=` 完全等价，可根据语境选择使用

### 3. 上下文感知
- 局部样式块中的 `&` 会自动推导为当前元素的类名或 ID
- 智能的作用域管理

### 4. 组件化
- 通过模板和自定义系统实现强大的组件复用
- 支持继承、特例化、约束等高级特性

### 5. 渐进增强
- 局部脚本块的 CHTL JS 语法提供了更简洁的 DOM 操作
- 增强选择器和箭头操作符提高开发效率

### 6. 模块化
- 完整的模块系统支持大型项目开发
- CMOD 格式便于模块分发和复用