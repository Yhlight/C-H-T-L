# CHTL v2 子状态示例

## 1. 元素子状态

### 解析元素标签和属性

```chtl
div #main .container data-role="wrapper" { ... }
```

状态转换：
```
INITIAL -> ELEMENT (子状态: ELEMENT_TAG)
  读取 "div" -> 设置标签名

ELEMENT + ELEMENT_TAG -> 遇到 "#" -> 子状态: ELEMENT_ID
  读取 "main" -> 设置 ID

ELEMENT + ELEMENT_ID -> 遇到 "." -> 子状态: ELEMENT_CLASS
  读取 "container" -> 添加类名

ELEMENT + ELEMENT_CLASS -> 遇到标识符 -> 子状态: ELEMENT_ATTR_NAME
  读取 "data-role" -> 准备属性

ELEMENT + ELEMENT_ATTR_NAME -> 遇到 "=" -> 子状态: ELEMENT_ATTR_VALUE
  读取 "wrapper" -> 设置属性值

ELEMENT + ELEMENT_ATTR_VALUE -> 遇到 "{" -> ELEMENT_CONTENT
```

## 2. CSS 选择器子状态（局部样式）

```chtl
div {
    style {
        .active:hover > span::before {
            content: "→";
        }
    }
}
```

在局部样式块中的子状态：
```
STYLE_CONTENT -> 遇到 "." -> 子状态: CSS_SELECTOR
  收集 ".active"

CSS_SELECTOR -> 遇到 ":" -> 子状态: CSS_PSEUDO
  收集 ":hover"

CSS_PSEUDO -> 遇到 ">" -> 子状态: CSS_COMBINATOR
  处理子选择器

CSS_COMBINATOR -> 遇到标识符 -> 子状态: CSS_SELECTOR
  收集 "span"

CSS_SELECTOR -> 遇到 "::" -> 子状态: CSS_PSEUDO
  收集 "::before"
```

## 3. 声明子状态

```chtl
[Template] @Element Card(title, content = "default") { ... }
```

状态转换：
```
DECLARATION -> 子状态: DECLARATION_TYPE
  读取 "Template"

DECLARATION_TYPE -> 遇到 "@Element" -> 子状态: DECLARATION_NAME
  读取 "Card"

DECLARATION_NAME -> 遇到 "(" -> 子状态: DECLARATION_PARAMS
  解析参数列表
```

## 4. 引用子状态

```chtl
div {
    @Element Card("Hello", "World")
}
```

状态转换：
```
ELEMENT_CONTENT + LOCAL -> 遇到 "@" -> REFERENCE
REFERENCE -> 子状态: REFERENCE_TYPE
  读取 "Element"

REFERENCE_TYPE -> 子状态: REFERENCE_NAME
  读取 "Card"

REFERENCE_NAME -> 遇到 "(" -> 子状态: REFERENCE_ARGS
  解析参数
```

## 5. 状态机处理逻辑

```cpp
// 元素属性值的处理
void handleElementAttributeValue(Token& token) {
    switch (getCurrentSubState()) {
        case ELEMENT_ATTR_VALUE:
            // 属性值可以包含任意内容，包括 #
            collectAttributeValue(token);
            break;
    }
}

// CSS 选择器的处理
void handleCssSelector(Token& token) {
    if (token.value == "#") {
        // 在 CSS 选择器中，# 表示 ID 选择器
        switchSubState(CSS_SELECTOR);
        expectIdentifier();  // 期待 ID 名称
    }
}

// 全局样式 vs 局部样式
void handleStyleBlock() {
    if (getCurrentContext() == GLOBAL) {
        // 全局样式：整块传递给 CSS 分析器
        std::string css = collectUntilCloseBrace();
        cssAnalyzer.analyze(css);
    } else {
        // 局部样式：可能需要处理 CHTL 特有语法
        enterState(STYLE_CONTENT, CSS_SELECTOR);
    }
}
```

## 6. 优势

1. **精确控制**：子状态让我们能精确控制每个语法元素的解析
2. **上下文清晰**：`#` 的含义由当前子状态决定
3. **错误恢复**：可以根据子状态更精确地恢复
4. **扩展性**：添加新语法只需添加新的子状态

## 7. CSS/JS 分析器的集成

```cpp
// CHTL 编译器
void processStyleContent(const std::string& css) {
    // 对于全局样式，直接传递给原生 CSS 分析器
    auto result = nativeCssAnalyzer.analyze(css);
    
    // 处理分析结果
    for (const auto& rule : result.rules) {
        // 提取选择器、属性等信息
    }
}

// 原生 CSS 分析器只处理标准 CSS
// 不需要知道 CHTL 的存在
```

这样的设计保持了关注点分离：
- CHTL 状态机处理 CHTL 语法
- CSS 分析器只处理标准 CSS
- JS 分析器只处理标准 JavaScript