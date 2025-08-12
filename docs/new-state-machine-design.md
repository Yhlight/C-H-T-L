# CHTL 新状态机设计

## 状态定义

```cpp
enum class ChtlParseState {
    // 顶层状态
    TOP_LEVEL,              // 文件顶层，可以有声明或 HTML 片段
    
    // 声明状态
    TEMPLATE_DECLARATION,   // [Template] 声明内部
    CUSTOM_DECLARATION,     // [Custom] 声明内部
    IMPORT_DECLARATION,     // [Import] 声明
    CONFIG_DECLARATION,     // [Configuration] 声明
    
    // 元素状态
    ELEMENT_TAG,            // 解析元素标签和属性
    ELEMENT_CONTENT,        // 元素内容
    
    // 样式状态
    STYLE_BLOCK,            // style { } 块
    STYLE_SELECTOR,         // CSS 选择器
    STYLE_PROPERTY_NAME,    // CSS 属性名
    STYLE_PROPERTY_VALUE,   // CSS 属性值
    
    // 脚本状态
    SCRIPT_BLOCK,           // script { } 块
    SCRIPT_CONTENT,         // JavaScript 内容
    
    // 文本状态
    TEXT_BLOCK,             // text { } 块
    TEXT_CONTENT,           // 文本内容
    
    // 引用状态
    ELEMENT_REFERENCE,      // @Element 引用
    STYLE_REFERENCE,        // @Style 引用
    VAR_REFERENCE,          // @Var 引用
    
    // 表达式状态
    EXPRESSION,             // 参数表达式
    STRING_LITERAL,         // 字符串字面量
    
    // CHTL-JS 状态
    CHTL_JS_EXPRESSION,     // {{ }} 内的表达式
};
```

## 状态转换规则

### TOP_LEVEL 状态
- `[` → 检查声明类型，转到相应的 DECLARATION 状态
- `style` → STYLE_BLOCK
- `script` → SCRIPT_BLOCK
- 标识符 → ELEMENT_TAG（HTML 元素）
- `@` → 检查引用类型（应该报错，顶层不允许引用）

### TEMPLATE_DECLARATION 状态
- `@Element` → 期待模板名称和参数
- `{` → ELEMENT_CONTENT（模板体）
- `}` → 返回 TOP_LEVEL

### ELEMENT_CONTENT 状态
- `style` → STYLE_BLOCK（局部样式）
- `script` → SCRIPT_BLOCK（局部脚本）
- `text` → TEXT_BLOCK
- `@` → 检查引用类型，转到相应的 REFERENCE 状态
- 标识符 → ELEMENT_TAG（子元素）
- `}` → 返回上一状态

### STYLE_BLOCK 状态
- `{` → 进入样式内容
- 标识符 → STYLE_SELECTOR（选择器）或 STYLE_PROPERTY_NAME（属性）
- `.` → STYLE_SELECTOR（类选择器）
- `#` → STYLE_SELECTOR（ID 选择器）
- `text` → TEXT_BLOCK（全局样式的文本内容）
- `}` → 返回上一状态

### STYLE_PROPERTY_VALUE 状态
- 任意字符 → 收集属性值，直到 `;` 或 `}`
- `#` → 作为颜色值的一部分
- `;` → 返回 STYLE_BLOCK
- `}` → 返回上一状态

## Token 识别规则

Token 类型应该根据当前状态动态确定：

```cpp
TokenType determineTokenType(const std::string& text, ChtlParseState state) {
    switch (state) {
        case ChtlParseState::TOP_LEVEL:
            if (text == "style") return TokenType::STYLE;
            if (text == "script") return TokenType::SCRIPT;
            if (isHtmlTag(text)) return TokenType::HTML_TAG;
            break;
            
        case ChtlParseState::ELEMENT_CONTENT:
            if (text == "style") return TokenType::STYLE;
            if (text == "script") return TokenType::SCRIPT;
            if (text == "text") return TokenType::TEXT;
            break;
            
        case ChtlParseState::STYLE_PROPERTY_VALUE:
            // 在属性值中，所有内容都是值的一部分
            return TokenType::VALUE;
            
        // ... 其他状态
    }
    
    return TokenType::IDENTIFIER;
}
```

## 上下文栈

```cpp
struct ParseContext {
    ChtlParseState state;
    std::shared_ptr<Node> currentNode;
    std::map<std::string, std::string> localVariables;  // 模板参数等
    int braceDepth;
    
    // 状态特定的数据
    union {
        struct {
            std::string propertyName;
        } cssContext;
        
        struct {
            std::string templateName;
            std::vector<std::string> parameters;
        } templateContext;
    };
};

class ContextStack {
    std::vector<ParseContext> stack;
    
public:
    void push(ChtlParseState state);
    void pop();
    ParseContext& current();
    bool inState(ChtlParseState state) const;
};
```

## 示例：解析流程

输入：
```chtl
[Template] @Element Card(title) {
    div .card {
        h1 { text { title } }
    }
}

div {
    @Element Card("Hello")
}
```

状态转换：
1. TOP_LEVEL: 遇到 `[` 
2. 识别 `Template`，进入 TEMPLATE_DECLARATION
3. 解析 `@Element Card(title)`，存储模板定义
4. 遇到 `{`，进入 ELEMENT_CONTENT
5. 在模板内部，`title` 被识别为参数引用
6. 遇到 `}`，返回 TOP_LEVEL
7. TOP_LEVEL: 遇到 `div`，进入 ELEMENT_TAG
8. 进入 ELEMENT_CONTENT
9. 遇到 `@Element`，进入 ELEMENT_REFERENCE
10. 查找并展开模板 `Card`

## 优势

1. **明确的状态管理**：每个状态都有清晰的职责
2. **上下文感知**：Token 识别和解析规则随状态变化
3. **错误恢复**：可以根据状态栈恢复到合理的位置
4. **扩展性**：添加新特性只需添加新状态和转换规则
5. **可维护性**：状态机的逻辑集中且清晰