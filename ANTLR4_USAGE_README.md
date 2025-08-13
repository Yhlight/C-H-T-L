# ANTLR4代码生成和使用说明

## 概述

本文档说明如何使用ANTLR4工具生成CHTL、CSS、JavaScript和CHTL JS的解析器代码，以及如何在项目中使用这些生成的代码。

## 已生成的代码

### 1. 简化语法文件

为了确保代码生成成功，我们创建了简化版本的语法文件：

- **CHTL**: `grammars/chtl/CHTL_simple.g4`
- **CSS**: `grammars/css/CSS_simple.g4`
- **JavaScript**: `grammars/js/JavaScript_simple.g4`
- **CHTL JS**: `grammars/chtljs/CHTLJS_simple.g4`

### 2. 生成的代码位置

所有生成的代码都位于 `generated_simple/` 目录下：

```
generated_simple/
├── chtl/grammars/chtl/          # CHTL解析器代码
├── css/grammars/css/            # CSS解析器代码
├── js/grammars/js/              # JavaScript解析器代码
└── chtljs/grammars/chtljs/      # CHTL JS解析器代码
```

### 3. 生成的文件类型

每个语法都会生成以下文件：

- **词法分析器**: `*Lexer.h`, `*Lexer.cpp`
- **语法分析器**: `*Parser.h`, `*Parser.cpp`
- **访问者基类**: `*BaseVisitor.h`, `*BaseVisitor.cpp`
- **监听器基类**: `*BaseListener.h`, `*BaseListener.cpp`
- **访问者接口**: `*Visitor.h`, `*Visitor.cpp`
- **监听器接口**: `*Listener.h`, `*Listener.cpp`
- **其他支持文件**: `*.tokens`, `*.interp`

## 使用方法

### 1. 基本使用流程

```cpp
#include "generated_simple/chtl/grammars/chtl/CHTL_simpleLexer.h"
#include "generated_simple/chtl/grammars/chtl/CHTL_simpleParser.h"
#include "generated_simple/chtl/grammars/chtl/CHTL_simpleBaseVisitor.h"

// 创建输入流
std::istringstream inputStream(sourceCode);
antlr4::ANTLRInputStream input(inputStream);

// 创建词法分析器
CHTL_simpleLexer lexer(&input);

// 创建词法标记流
antlr4::CommonTokenStream tokens(&lexer);

// 创建语法分析器
CHTL_simpleParser parser(&tokens);

// 解析程序
CHTL_simpleParser::ProgramContext* tree = parser.program();

// 使用访问者模式遍历语法树
CHTLVisitor visitor;
visitor.visit(tree);
```

### 2. 自定义访问者

继承生成的基类访问者来添加自定义逻辑：

```cpp
class CHTLVisitor : public CHTL_simpleBaseVisitor {
public:
    std::any visitElementStatement(CHTL_simpleParser::ElementStatementContext *ctx) override {
        std::string elementName = ctx->IDENTIFIER()->getText();
        std::cout << "发现元素: " << elementName << std::endl;
        
        // 访问子节点
        if (ctx->attributes()) {
            visit(ctx->attributes());
        }
        
        if (ctx->elementContent()) {
            visit(ctx->elementContent());
        }
        
        return nullptr;
    }
    
    // 实现其他访问方法...
};
```

### 3. 错误处理

```cpp
// 检查语法错误
if (parser.getNumberOfSyntaxErrors() > 0) {
    std::cout << "语法错误数量: " << parser.getNumberOfSyntaxErrors() << std::endl;
    // 处理错误...
}
```

## 依赖要求

### 1. ANTLR4运行时库

要使用生成的代码，需要安装ANTLR4运行时库：

**Ubuntu/Debian:**
```bash
sudo apt-get install antlr4-runtime
```

**macOS:**
```bash
brew install antlr4-runtime
```

**Windows:**
```bash
vcpkg install antlr4-runtime
```

### 2. 编译选项

确保使用C++17或更高版本：

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### 3. 链接库

```cmake
target_link_libraries(your_target antlr4-runtime)
```

## 语法特性

### 1. CHTL语法

支持的基本结构：

```chtl
[Template] Button
{
    class: primary;
    
    text
    {
        "点击我"
    }
    
    style
    {
        "background-color: blue;"
    }
    
    script
    {
        "console.log('按钮被点击');"
    }
}

div
{
    id: container;
    class: main;
    
    text
    {
        "这是一个测试div"
    }
}
```

### 2. CSS语法

支持的基本结构：

```css
.container {
    width: 100%;
    max-width: 800px;
    margin: 0 auto;
}

.button {
    padding: 10px 20px;
    background-color: blue;
    color: white;
}
```

### 3. JavaScript语法

支持的基本结构：

```javascript
function greet(name) {
    return "Hello, " + name + "!";
}

const button = document.getElementById('button');
button.addEventListener('click', function() {
    console.log('按钮被点击');
});
```

### 4. CHTL JS语法

支持的基本结构：

```javascript
script
{
    {{.button}}.listen({
        click: "handleClick"
    });
    
    {{#container}}.delegate({
        target: {{.item}},
        click: "handleItemClick"
    });
    
    animate({
        duration: 300,
        easing: "ease-in-out",
        begin: {
            opacity: 0
        },
        end: {
            opacity: 1
        }
    });
}
```

## 扩展语法

### 1. 添加新的语法规则

在 `.g4` 文件中添加新规则：

```antlr4
// 新规则
newRule: IDENTIFIER LBRACE content RBRACE;
content: (STRING | IDENTIFIER)*;
```

### 2. 重新生成代码

```bash
./generate_simple_antlr.sh
```

### 3. 更新访问者

在自定义访问者中添加新方法：

```cpp
std::any visitNewRule(CHTL_simpleParser::NewRuleContext *ctx) override {
    // 处理新规则...
    return nullptr;
}
```

## 性能优化

### 1. 内存管理

- 使用智能指针管理语法树节点
- 避免不必要的字符串拷贝
- 使用引用传递大对象

### 2. 解析优化

- 启用错误恢复模式
- 使用访问者模式而不是监听器模式（性能更好）
- 缓存频繁访问的节点

## 调试技巧

### 1. 启用调试输出

```cpp
// 启用词法分析器调试
lexer.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

// 启用语法分析器调试
parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());
```

### 2. 查看语法树

```cpp
// 打印语法树
std::cout << tree->toStringTree(&parser) << std::endl;
```

### 3. 检查标记流

```cpp
// 查看所有标记
for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
}
```

## 常见问题

### 1. 编译错误

**问题**: 找不到ANTLR4头文件
**解决**: 确保正确包含生成的代码目录

**问题**: 链接错误
**解决**: 确保链接了ANTLR4运行时库

### 2. 运行时错误

**问题**: 语法解析失败
**解决**: 检查语法文件是否正确，确保输入代码符合语法规则

**问题**: 访问者方法未调用
**解决**: 确保正确继承基类并重写相应方法

## 总结

ANTLR4为CHTL编译器提供了强大的语法解析能力：

1. **自动生成**: 从语法文件自动生成词法分析器和语法分析器
2. **类型安全**: 生成的代码提供类型安全的语法树访问
3. **易于扩展**: 可以轻松添加新的语法规则
4. **高性能**: 生成的解析器性能优秀
5. **错误处理**: 内置错误检测和恢复机制

通过使用生成的代码，CHTL编译器可以准确解析复杂的语法结构，为后续的代码生成和优化提供坚实的基础。