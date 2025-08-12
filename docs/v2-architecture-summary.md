# CHTL v2 架构总结

## 核心改进

### 1. 状态机驱动架构
- **主状态 + 子状态系统**：更精确的语法控制
- **全局/局部上下文**：明确区分定义和引用
- **状态决定一切**：Token 类型、解析规则都由状态决定

### 2. 四个独立编译器
```
CHTL 编译器 ─┬─> CSS 分析器（只处理标准 CSS）
             ├─> JS 分析器（只处理标准 JavaScript）
             └─> CHTL-JS 编译器（只处理扩展语法）
```

### 3. 简化的设计原则
- **全局定义，局部引用**
- **CSS/JS 整块传递**，不做细粒度解析
- **状态机处理所有上下文切换**

## 已完成的组件

### ✅ 状态机系统
- `ChtlParseState`：主状态（INITIAL, ELEMENT, STYLE, SCRIPT, TEXT 等）
- `ChtlSubState`：子状态（ELEMENT_ID, CSS_SELECTOR, DECLARATION_TYPE 等）
- `ChtlContext`：上下文（GLOBAL, LOCAL）
- `ChtlStateMachine`：状态管理和转换

### ✅ 词法分析器
- 状态感知的 Token 扫描
- 元数据支持（isHtmlTag, isCssProperty）
- 不同状态下的不同扫描策略

### ✅ 语法分析器
- 基于状态机的递归下降解析
- 自动调用 CSS/JS 分析器
- 错误恢复机制

### ✅ CSS/JS 分析器
- `NativeCssAnalyzer`：只分析标准 CSS
- `NativeJsAnalyzer`：只分析标准 JavaScript
- 简单但有效的语法验证

## 关键文件结构

```
/workspace/
├── include/v2/
│   ├── State/
│   │   ├── ChtlParseState.h    # 状态定义
│   │   └── ChtlStateMachine.h  # 状态机
│   ├── Lexer/
│   │   ├── Token.h              # Token 定义
│   │   └── ChtlLexer.h          # 词法分析器
│   ├── Parser/
│   │   └── ChtlParser.h         # 语法分析器
│   ├── Node/
│   │   └── Node.h               # AST 节点
│   ├── Context/
│   │   └── ParseContext.h       # 解析上下文
│   ├── Css/
│   │   └── NativeCssAnalyzer.h # CSS 分析器
│   └── Js/
│       └── NativeJsAnalyzer.h   # JS 分析器
└── src/v2/
    └── ... (对应的实现文件)
```

## 示例：状态机如何工作

```chtl
div #main {         // 状态：ELEMENT + ELEMENT_TAG
                    // # 触发子状态：ELEMENT_ID
    style {         // 进入 LOCAL 上下文
                    // 状态：STYLE
        color: red; // 状态：STYLE_CONTENT
    }               // 整块传递给 CSS 分析器
}
```

## 待完成

1. **代码生成器**：基于新 AST 的 HTML/CSS/JS 生成
2. **CHTL-JS 编译器**：处理 `{{}}` 语法
3. **集成测试**：验证所有功能
4. **迁移旧代码**：将 v1 的功能迁移到 v2

## 优势

1. **清晰的职责分离**：每个编译器只处理自己的语言
2. **状态驱动**：减少了条件判断和特殊处理
3. **易于扩展**：添加新状态或子状态很简单
4. **更好的错误处理**：状态机提供了明确的错误恢复点
5. **性能提升**：CSS/JS 可以并行分析