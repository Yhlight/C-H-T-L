# Lexer API 文档

## 概述

CHTL 词法分析器负责将源代码文本转换为 token 流。

## 类层次结构

```
Lexer (抽象基类)
├── BasicLexer
└── StandardLexer
```

## Lexer 基类

```cpp
namespace chtl {

class Lexer {
public:
    virtual ~Lexer() = default;
    virtual std::vector<Token> tokenize() = 0;
    virtual void reset() = 0;
};

}
```

### 纯虚函数

#### `tokenize()`
将输入转换为 token 流。

**返回值**
- `std::vector<Token>`: Token 列表

**异常**
- `LexicalError`: 词法错误时抛出

#### `reset()`
重置词法分析器状态。

## StandardLexer

标准词法分析器实现，支持完整的 CHTL 语法。

```cpp
class StandardLexer : public Lexer {
public:
    StandardLexer(const std::string& input, 
                  std::shared_ptr<Context> context);
    
    std::vector<Token> tokenize() override;
    void reset() override;
    
    // 额外方法
    void setFile(const std::string& filename);
    size_t getCurrentLine() const;
    size_t getCurrentColumn() const;
};
```

### 构造函数

```cpp
StandardLexer(const std::string& input, 
              std::shared_ptr<Context> context)
```

**参数**
- `input`: 源代码字符串
- `context`: 编译上下文

### 公共方法

#### `setFile(filename)`
设置当前文件名（用于错误报告）。

**参数**
- `filename`: 文件名字符串

#### `getCurrentLine()`
获取当前行号（1-based）。

**返回值**
- `size_t`: 当前行号

#### `getCurrentColumn()`
获取当前列号（1-based）。

**返回值**
- `size_t`: 当前列号

## Token 结构

```cpp
struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;
    std::string filename;
};
```

### 成员说明

- `type`: Token 类型
- `value`: Token 值
- `line`: 行号（1-based）
- `column`: 列号（1-based）
- `filename`: 所在文件名

## TokenType 枚举

```cpp
enum class TokenType {
    // 字面量
    IDENTIFIER,
    STRING,
    NUMBER,
    
    // 关键字
    TEXT,
    STYLE,
    SCRIPT,
    TEMPLATE,
    CUSTOM,
    IMPORT,
    CONFIG,
    NAMESPACE,
    
    // 运算符
    COLON,
    SEMICOLON,
    COMMA,
    DOT,
    ARROW,
    
    // 括号
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    
    // CHTL-JS
    CHTL_JS_START,  // {{
    CHTL_JS_END,    // }}
    
    // 特殊
    EOF_TOKEN,
    UNKNOWN
};
```

## 使用示例

### 基本使用

```cpp
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

auto context = std::make_shared<StandardContext>();
StandardLexer lexer("div { id: \"test\"; }", context);

auto tokens = lexer.tokenize();

for (const auto& token : tokens) {
    std::cout << "Type: " << static_cast<int>(token.type)
              << ", Value: " << token.value
              << ", Line: " << token.line
              << ", Column: " << token.column
              << std::endl;
}
```

### 错误处理

```cpp
try {
    auto tokens = lexer.tokenize();
} catch (const LexicalError& e) {
    std::cerr << "Lexical error: " << e.what() << std::endl;
    std::cerr << "At line " << e.getLine() 
              << ", column " << e.getColumn() << std::endl;
}
```

### 从文件读取

```cpp
std::ifstream file("example.chtl");
std::string content((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

StandardLexer lexer(content, context);
lexer.setFile("example.chtl");

auto tokens = lexer.tokenize();
```

## 状态机

词法分析器使用状态机处理不同的语言上下文：

1. **CHTL 状态**: 处理 CHTL 语法
2. **CSS 状态**: 处理样式块
3. **JS 状态**: 处理脚本块
4. **字符串状态**: 处理字符串字面量
5. **注释状态**: 处理注释

状态转换由上下文决定，确保正确处理嵌套结构。

## 性能考虑

- 使用预分配的 token 向量减少内存分配
- 字符串使用移动语义避免拷贝
- 状态机实现优化了常见模式的识别

## 扩展

要添加新的 token 类型：

1. 在 `TokenType` 枚举中添加新类型
2. 在相应的状态处理函数中添加识别逻辑
3. 更新相关的解析器以处理新 token