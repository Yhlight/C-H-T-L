# CHTL v2 编译器重构进度

## 已完成的工作

### 1. 架构设计 ✅
- 分析了当前架构的问题
- 设计了新的状态机驱动架构
- 创建了详细的实施计划

### 2. 状态系统 ✅
- **ChtlParseState**: 定义了所有解析状态
- **状态辅助函数**: getStateName, isDeclarationState 等
- **清晰的状态分类**: 顶层、声明、元素、样式、脚本等

### 3. 状态机核心 ✅
- **ChtlStateMachine**: 状态机核心实现
  - 状态栈管理
  - 状态转换执行
  - 进入/退出回调
  - 词法分析器集成
- **StateTransition**: 状态转换规则结构
  - 条件函数
  - 目标状态
  - 转换动作

### 4. 状态转换规则 ✅
- **TOP_LEVEL**: 处理声明和 HTML 片段
- **ELEMENT_CONTENT**: 处理元素内容
- **STYLE_BLOCK**: 区分全局/局部样式
- **TEMPLATE_DECLARATION**: 模板定义
- **SCRIPT_BLOCK**: 脚本块
- **TEXT_BLOCK**: 文本块

### 5. 上下文系统 ✅
- **ParseContext**: 解析上下文
  - 状态特定数据（CSS、模板、元素）
  - 位置跟踪
  - 作用域管理
- **Scope**: 作用域管理
  - 变量定义和查找
  - 参数管理
  - 作用域链

### 6. Token 系统 ✅
- **TokenType**: 完整的 Token 类型定义
- **Token 结构**: 包含元数据支持
- **辅助方法**: toString, getTokenTypeName

## 正在进行的工作

### 7. 词法分析器 🚧
- **ChtlLexer**: 状态感知的词法分析器（头文件已创建）
- 需要实现：
  - 状态相关的扫描逻辑
  - Token 类型的动态确定
  - CSS/JS 上下文处理

## 待完成的工作

### 8. 语法分析器 📋
- 基于状态机的递归下降解析器
- AST 构建
- 错误恢复

### 9. 代码生成器 📋
- 简化的访问者模式
- 模板展开
- 样式/脚本提取

### 10. 测试框架 📋
- 单元测试
- 集成测试
- 回归测试

## 关键改进

### 1. 状态驱动的 Token 识别
```cpp
// 旧版本：固定的 Token 类型
if (text == "style") return TokenType::STYLE;

// 新版本：根据状态确定
switch (currentState) {
    case TOP_LEVEL:
        if (text == "style") return TokenType::STYLE;  // 全局样式
        break;
    case STYLE_PROPERTY_VALUE:
        // 在属性值中，"style" 只是普通文本
        return TokenType::CSS_VALUE;
}
```

### 2. 明确的状态转换
```cpp
// TOP_LEVEL 状态下
Token: "style" -> 转换到 STYLE_BLOCK (全局)

// ELEMENT_CONTENT 状态下  
Token: "style" -> 转换到 STYLE_BLOCK (局部)
```

### 3. 上下文感知的解析
```cpp
// 在 TEMPLATE_DECLARATION 状态
"title" -> 识别为模板参数

// 在 ELEMENT_CONTENT 状态
"title" -> 识别为 HTML 元素或文本
```

## 下一步计划

1. **完成词法分析器实现**
   - 实现 scanToken 和状态相关的扫描方法
   - 实现 HTML/CSS 属性识别
   - 测试状态切换

2. **创建简单的测试程序**
   - 测试状态机的状态转换
   - 测试 Token 识别
   - 验证上下文管理

3. **开始语法分析器**
   - 设计 AST 节点结构
   - 实现基础的解析方法
   - 集成状态机

## 架构优势

1. **真正的状态机驱动**: 所有决策基于当前状态
2. **上下文感知**: Token 和解析规则随状态变化
3. **清晰的职责**: 每个组件有明确的责任
4. **易于扩展**: 添加新特性只需新状态和规则
5. **错误恢复**: 基于状态栈的恢复机制