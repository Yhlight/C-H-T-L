# CHTL v2 简化设计

## 核心原则

### 1. 全局 vs 局部
- **全局状态**：顶层，所有声明都是定义
- **局部状态**：在任何块内部，所有声明都是引用/使用

### 2. CSS 简化处理
- **属性值**：整块传递，不解析
- **局部样式块**：通过状态机处理，选择器也可以整块传递
- **只需要特殊处理**：元素上的 `#id` 语法

### 3. 模板/自定义组件
```chtl
// 全局状态 - 定义
[Template] @Element Card(title) { ... }

// 局部状态 - 引用
div {
    @Element Card("Hello")  // 这是引用，不是定义
    
    // 即使有 [Template] 标记，在局部状态也是引用
    [Template] @Element Card  // 引用名为 "[Template] @Element Card" 的组件
}
```

## 简化的状态设计

```cpp
enum class ChtlContext {
    GLOBAL,    // 全局上下文（顶层）
    LOCAL      // 局部上下文（任何块内）
};

enum class ChtlParseState {
    // 基础状态
    INITIAL,           // 初始状态
    ELEMENT,           // 元素（标签、属性、内容）
    STYLE,             // 样式块
    SCRIPT,            // 脚本块
    TEXT,              // 文本块
    
    // CSS 相关（简化）
    CSS_CONTENT,       // CSS 内容（整块传递）
    
    // JS 相关
    JS_CONTENT,        // JS 内容（交给扫描器）
    
    // 声明相关
    DECLARATION,       // [] 声明块
    REFERENCE,         // @ 引用
};
```

## 状态转换规则（简化）

### GLOBAL 上下文
- `[` → DECLARATION（定义）
- `style` → STYLE（全局样式）
- `script` → SCRIPT（全局脚本）
- 标识符 → ELEMENT（HTML 片段）

### LOCAL 上下文（元素内部）
- `[` → REFERENCE（即使语法像声明，也是引用）
- `@` → REFERENCE（明确的引用）
- `style` → STYLE（局部样式）
- `script` → SCRIPT（局部脚本）
- `text` → TEXT
- 标识符 → ELEMENT（嵌套元素）

### STYLE 状态
- `{` → CSS_CONTENT
- CSS_CONTENT 中：整块收集到 `}` 或 `text {`

### 元素上的 ID
- 只在 ELEMENT 状态特殊处理 `#id` 语法
- 其他地方 `#` 都是普通字符

## 优势

1. **简单明了**：全局定义，局部引用
2. **避免歧义**：不依赖语法标记判断语义
3. **CSS 处理简化**：不需要解析 CSS 细节
4. **易于实现**：状态机逻辑大大简化

## 示例

```chtl
// === 全局上下文 ===

// 定义模板
[Template] @Element Card(title) {
    div .card { text { title } }
}

// 定义样式
style {
    // 这里的内容整块传递给 CSS 分析器
    .card { 
        background: #fff;
        border: 1px solid #ddd;
    }
}

// HTML 片段
div #app {
    // === 局部上下文 ===
    
    // 引用模板
    @Element Card("Hello")
    
    // 即使写了 [Template]，也是引用
    [Template] @Element Card("World")
    
    // 局部样式
    style {
        // 整块传递，不解析
        color: #333;
        margin: 10px;
    }
}
```

## 处理继承问题

通过全局/局部区分，继承变得简单：

```chtl
// 全局定义基础组件
[Template] @Element BaseCard { ... }

// 全局定义继承组件
[Template] @Element MyCard {
    inherit @Element BaseCard  // 在局部上下文，这是引用
    // ...
}
```