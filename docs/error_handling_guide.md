# CHTL 错误处理指南

## 概述

CHTL 使用分层的错误处理系统，确保所有错误都能被正确捕获、报告和处理。

## 错误类型

### 1. 词法错误 (Lexical Errors)
- 无效字符
- 未终止的字符串
- 无效的数字格式

### 2. 语法错误 (Syntax Errors)
- 缺少分号
- 不匹配的括号
- 无效的语法结构

### 3. 语义错误 (Semantic Errors)
- 未定义的变量
- 类型不匹配
- 重复定义

### 4. 运行时错误 (Runtime Errors)
- 文件读取失败
- 内存分配失败
- 系统调用失败

## 错误处理架构

### 1. ErrorHandler（核心）
```cpp
class ErrorHandler {
    void reportError(ErrorType type, const std::string& message, const ErrorContext& context);
    void reportWarning(const std::string& message, const ErrorContext& context);
};
```

### 2. ErrorCollector（单例）
```cpp
ErrorCollector::getInstance().syntaxError("Invalid syntax", line, col);
```

### 3. 错误上下文
```cpp
struct ErrorContext {
    std::string fileName;
    int line;
    int column;
    std::string sourceCode;
    std::string contextLines;
};
```

## 使用示例

### 在词法分析器中
```cpp
void Lexer::handleInvalidCharacter(char ch) {
    ErrorContext ctx;
    ctx.fileName = currentFile_;
    ctx.line = currentLine_;
    ctx.column = currentColumn_;
    ctx.sourceCode = getCurrentLine();
    
    ErrorCollector::getInstance().reportError(
        ErrorType::LEXICAL_ERROR,
        fmt::format("Invalid character '{}' found", ch),
        ctx
    );
}
```

### 在解析器中
```cpp
void Parser::expectToken(TokenType expected) {
    if (currentToken_.type != expected) {
        CHTL_SYNTAX_ERROR(
            fmt::format("Expected {}, but got {}", 
                tokenTypeToString(expected),
                tokenTypeToString(currentToken_.type)),
            currentToken_.line,
            currentToken_.column
        );
    }
}
```

### 在生成器中
```cpp
void Generator::processReference(const std::string& name) {
    if (!isDefined(name)) {
        CHTL_SEMANTIC_ERROR(
            fmt::format("Undefined reference '{}'", name),
            currentNode_->getLine(),
            currentNode_->getColumn()
        );
    }
}
```

## 错误恢复策略

### 1. 词法级恢复
- 跳过无效字符
- 尝试重新同步到下一个有效token

### 2. 语法级恢复
- Panic模式：跳到下一个同步点（如分号）
- 短语级恢复：尝试修复常见错误

### 3. 语义级恢复
- 使用默认值
- 创建占位符定义

## 错误格式化

### 控制台输出
```
error[CHTL001]: Syntax Error
  --> example.chtl:10:15
   |
10 | div { class: "test" 
   |               ^^^^^ Expected ';' after attribute value
   |
help: Add a semicolon after the attribute value
```

### JSON输出
```json
{
  "type": "SYNTAX_ERROR",
  "code": "CHTL001",
  "message": "Expected ';' after attribute value",
  "location": {
    "file": "example.chtl",
    "line": 10,
    "column": 15
  },
  "fixes": [{
    "description": "Add semicolon",
    "replacement": ";",
    "position": {"line": 10, "column": 20}
  }]
}
```

## 最佳实践

### 1. 始终提供上下文
```cpp
// ❌ 不好
reportError("Invalid syntax");

// ✅ 好
ErrorContext ctx;
ctx.fileName = currentFile_;
ctx.line = line;
ctx.column = column;
ctx.contextLines = getContextLines(line);
reportError(ErrorType::SYNTAX_ERROR, "Invalid syntax", ctx);
```

### 2. 提供有用的错误信息
```cpp
// ❌ 不好
"Error"

// ✅ 好
"Unexpected token '}'. Did you forget to close the previous block?"
```

### 3. 提供修复建议
```cpp
ErrorFix fix;
fix.description = "Add missing semicolon";
fix.replacement = ";";
fix.startLine = error.line;
fix.startColumn = error.column;
errorDetail.addFix(fix);
```

### 4. 错误分级
- **错误**：必须修复，阻止编译
- **警告**：应该修复，但不阻止编译
- **信息**：建议性的改进

### 5. 批量报告
收集所有错误后一次性报告，而不是遇到第一个错误就停止。

## 测试错误处理

### 单元测试
```cpp
TEST(ErrorHandling, ReportsInvalidSyntax) {
    auto errorHandler = std::make_shared<ErrorHandler>();
    ErrorCollector::getInstance().setErrorHandler(errorHandler);
    
    Lexer lexer("invalid @#$ syntax");
    lexer.tokenize();
    
    EXPECT_TRUE(errorHandler->hasErrors());
    EXPECT_EQ(errorHandler->getErrors().size(), 1);
}
```

### 集成测试
创建包含各种错误的测试文件，确保所有错误都被正确捕获和报告。

## 性能考虑

1. **延迟格式化**：只在需要显示时格式化错误信息
2. **错误限制**：设置最大错误数量，避免错误爆炸
3. **内存管理**：定期清理已处理的错误

## 国际化

支持多语言错误信息：
```cpp
errorHandler->setLocale("zh_CN");
// 输出：语法错误：缺少分号
```