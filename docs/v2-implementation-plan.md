# CHTL v2 编译器重构实施计划

## 核心设计原则

1. **状态机驱动**：所有解析决策都基于当前状态
2. **上下文感知**：Token 识别和解析规则随状态变化
3. **清晰的职责分离**：状态机、词法分析器、语法分析器各司其职
4. **可扩展性**：添加新特性只需添加新状态和转换规则

## 实施步骤

### 第一阶段：基础架构（当前）
- [x] 设计新的状态系统 (`ChtlParseState`)
- [x] 设计上下文管理 (`ParseContext`, `Scope`)
- [x] 设计新的 Token 系统
- [x] 设计状态感知的词法分析器
- [ ] 实现状态机核心功能
- [ ] 实现基础词法分析

### 第二阶段：核心功能
- [ ] 实现状态转换规则
- [ ] 实现上下文管理
- [ ] 实现新的语法分析器
- [ ] 实现 AST 构建

### 第三阶段：特性完善
- [ ] 模板定义和引用
- [ ] 样式块（全局/局部）
- [ ] 脚本块（全局/局部）
- [ ] 变量系统
- [ ] CHTL-JS 支持

### 第四阶段：代码生成
- [ ] 重写代码生成器
- [ ] 模板展开
- [ ] 样式提取
- [ ] 脚本管理

### 第五阶段：测试和优化
- [ ] 单元测试
- [ ] 集成测试
- [ ] 性能优化
- [ ] 错误处理完善

## 关键改进点

### 1. 状态机改进
**旧版本问题**：
```cpp
// 使用布尔标志跟踪状态
bool inStyleBlock_;
bool inScriptBlock_;
```

**新版本方案**：
```cpp
// 明确的状态枚举
enum class ChtlParseState {
    TOP_LEVEL,
    STYLE_BLOCK,
    SCRIPT_BLOCK,
    // ...
};
```

### 2. Token 识别改进
**旧版本问题**：
```cpp
// Token 类型固定，不考虑上下文
if (text == "style") return TokenType::STYLE;
```

**新版本方案**：
```cpp
// Token 类型依赖当前状态
TokenType determineType(const std::string& text, ChtlParseState state) {
    switch (state) {
        case TOP_LEVEL:
            if (text == "style") return TokenType::STYLE;
            break;
        case STYLE_PROPERTY_VALUE:
            // 在属性值中，"style" 只是普通文本
            return TokenType::CSS_VALUE;
    }
}
```

### 3. 解析器改进
**旧版本问题**：
```cpp
// 顶层允许任何元素
if (currentToken_.type == TokenType::IDENTIFIER) {
    return parseNode();  // 可能是任何东西
}
```

**新版本方案**：
```cpp
// 基于状态的解析
switch (getCurrentState()) {
    case TOP_LEVEL:
        // 顶层只允许声明和 HTML 片段
        if (token.is(TokenType::LEFT_BRACKET)) {
            return parseDeclaration();
        }
        if (token.metadata.isHtmlTag) {
            return parseHtmlFragment();
        }
        break;
        
    case ELEMENT_CONTENT:
        // 元素内部允许引用
        if (token.is(TokenType::AT_ELEMENT)) {
            return parseElementReference();
        }
        break;
}
```

### 4. 模板系统改进
**旧版本问题**：
- 模板定义和引用的区分不清晰
- 参数作用域管理混乱

**新版本方案**：
- `TEMPLATE_DECLARATION` 状态用于定义
- `ELEMENT_REFERENCE` 状态用于引用
- 清晰的作用域栈管理参数

## 示例：新架构如何解决现有问题

### 问题1：CSS 属性值中的 # 被误解析
```css
color: #ff0000;  /* 旧版本可能解析为 COLON + ff0000 */
```

**解决方案**：
在 `STYLE_PROPERTY_VALUE` 状态下，`#` 被识别为值的一部分，而不是独立的 token。

### 问题2：模板无法正确展开
```chtl
[Template] @Element Card(title) { ... }
div { @Element Card("Hello") }  /* 旧版本无法区分定义和引用 */
```

**解决方案**：
- 在 `TOP_LEVEL` 状态，`[Template]` 触发进入 `TEMPLATE_DECLARATION`
- 在 `ELEMENT_CONTENT` 状态，`@Element` 触发进入 `ELEMENT_REFERENCE`

### 问题3：顶层 style 被错误处理
```chtl
style { text { "..." } }  /* 旧版本可能被当作局部样式 */
```

**解决方案**：
- 在 `TOP_LEVEL` 状态，`style` 创建全局样式节点
- 在 `ELEMENT_CONTENT` 状态，`style` 创建局部样式节点

## 下一步行动

1. 实现 `ChtlStateMachine` 的核心功能
2. 实现基础的状态转换规则
3. 实现 `ChtlLexer` 的状态感知扫描
4. 创建简单的测试用例验证新架构