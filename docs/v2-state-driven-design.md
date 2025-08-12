# CHTL v2 状态驱动设计

## 核心理念：状态决定一切

不依赖标记（如 `[Template]`、`@Element`），而是通过状态机的当前状态来决定语义。

## 状态转换示例

### 1. 元素内的 ID 处理

```chtl
div #main { ... }
```

状态转换：
```
INITIAL -> 识别 "div" -> ELEMENT
ELEMENT -> 识别 "#" -> ELEMENT_ID (特殊子状态)
ELEMENT_ID -> 识别 "main" -> 收集ID -> ELEMENT
ELEMENT -> 识别 "{" -> ELEMENT_CONTENT
```

### 2. CSS 中的 # 处理

```chtl
style {
    color: #ff0000;
}
```

状态转换：
```
INITIAL -> 识别 "style" -> STYLE
STYLE -> 识别 "{" -> STYLE_CONTENT
STYLE_CONTENT -> 收集所有内容直到 "}" -> 整块传递
```

在 `STYLE_CONTENT` 状态下，`#` 只是普通字符，不需要特殊处理。

### 3. 全局 vs 局部的区分

```chtl
// 全局上下文
[Template] @Element Card { ... }  // 定义

div {
    // 局部上下文
    [Template] @Element Card  // 引用（查找名为 "[Template] @Element Card" 的组件）
    @Element Card            // 引用（查找名为 "Card" 的组件）
}
```

状态机处理：
```
// 全局上下文
INITIAL + GLOBAL -> 遇到 "[" -> DECLARATION (定义模式)

// 局部上下文  
ELEMENT_CONTENT + LOCAL -> 遇到 "[" -> REFERENCE (引用模式)
ELEMENT_CONTENT + LOCAL -> 遇到 "@" -> REFERENCE (引用模式)
```

### 4. text 块的处理

```chtl
// 在元素内
div {
    text { "Hello" }
}

// 在 style 内（全局样式）
style {
    text {
        "body { margin: 0; }"
    }
}
```

状态机根据父状态决定：
```
ELEMENT_CONTENT -> "text" -> TEXT -> "{" -> TEXT_CONTENT
STYLE_CONTENT -> "text" -> TEXT -> "{" -> TEXT_CONTENT (标记为CSS文本)
```

## 状态机的优势

### 1. 简化词法分析

```cpp
Token scanToken() {
    switch (currentState) {
        case STYLE_CONTENT:
            // CSS 内容整块扫描
            return scanUntilBrace();
            
        case ELEMENT:
            // 只在元素状态处理 #
            if (peek() == '#') {
                return scanElementId();
            }
            break;
            
        case TEXT_CONTENT:
            // 文本内容整块扫描
            return scanTextContent();
    }
    
    // 默认扫描
    return scanDefault();
}
```

### 2. 简化语法分析

```cpp
void parseElement() {
    // 状态机自动处理上下文
    stateMachine.enterState(ELEMENT);
    stateMachine.enterLocalContext();  // 进入局部上下文
    
    // 解析元素内容
    while (!isEnd()) {
        // 状态机会根据当前上下文处理 token
        stateMachine.processToken(nextToken());
    }
    
    stateMachine.exitLocalContext();   // 退出局部上下文
    stateMachine.exitState();
}
```

### 3. 自然的错误处理

```cpp
// 在全局上下文不允许 @ 引用
if (context == GLOBAL && token.type == AT) {
    error("References (@) are not allowed at top level");
}

// 在 STYLE_CONTENT 中，任何内容都是合法的
if (state == STYLE_CONTENT) {
    // 不需要验证，整块传递
}
```

## 实际应用

### 1. 模板定义和引用

```chtl
// parser.cpp
void parseDeclaration() {
    if (stateMachine.getCurrentContext() == GLOBAL) {
        // 全局：这是定义
        createTemplateDefinition();
    } else {
        // 局部：这是引用，即使语法看起来像定义
        createTemplateReference();
    }
}
```

### 2. 样式块处理

```chtl
// 不需要区分选择器、属性等
void parseStyleContent() {
    std::string css;
    int braceCount = 1;
    
    while (braceCount > 0) {
        Token token = nextToken();
        if (token.type == LEFT_BRACE) braceCount++;
        if (token.type == RIGHT_BRACE) braceCount--;
        
        css += token.value;
    }
    
    // 整块传递给 CSS 分析器
    cssAnalyzer.analyze(css);
}
```

### 3. 继承处理

```chtl
[Template] @Element Card {
    inherit BaseCard    // 状态机知道这是局部上下文，所以是引用
    div { ... }
}
```

## 总结

**让状态机驱动一切**：

1. **词法分析**：根据状态决定如何扫描
2. **语法分析**：根据状态和上下文决定语义
3. **错误处理**：根据状态决定什么是合法的
4. **代码生成**：根据状态决定如何生成

这样的设计更简单、更一致、更易维护。