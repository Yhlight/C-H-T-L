# CHTL编译器

基于ANTLR4实现的超文本语言（CHTL）编译器。CHTL是一种新型的标记语言，旨在提供更符合开发者习惯的HTML编写方式。

## 特性

- **简洁的语法**：类似CSS的语法风格，无需编写繁琐的尖括号
- **内置模板系统**：支持模板和自定义组件，提高代码复用性
- **增强的样式支持**：局部样式块、自动类名生成、上下文推导
- **扩展的JavaScript语法**：增强选择器、事件监听、动画支持
- **四个独立编译器**：CHTL、CSS、JavaScript、CHTL JavaScript独立工作

## 项目结构

```
/workspace/
├── grammar/              # ANTLR4语法文件
│   ├── CHTL.g4          # CHTL语法
│   ├── CSS.g4           # CSS语法
│   ├── JavaScript.g4     # JavaScript语法
│   └── CHTLJavaScript.g4 # CHTL扩展的JavaScript语法
├── include/             # 头文件
│   ├── ASTNode.h        # AST节点定义
│   ├── SymbolTable.h    # 符号表
│   ├── Scanner.h        # 代码扫描器
│   ├── CompilerDispatcher.h  # 编译器调度器
│   ├── CHTLCompiler.h   # CHTL编译器
│   ├── CSSCompiler.h    # CSS编译器
│   ├── JSCompiler.h     # JS编译器
│   ├── CHTLJSCompiler.h # CHTL JS编译器
│   └── CodeGenerator.h  # 代码生成器
├── src/                 # 源文件
│   └── ...              # 对应的实现文件
├── examples/            # 示例文件
│   └── hello.chtl       # Hello World示例
├── CMakeLists.txt       # CMake配置文件
└── README.md            # 本文件
```

## 构建项目

### 依赖项

- CMake 3.10+
- C++17编译器
- ANTLR4 C++运行时
- Java运行时（用于运行ANTLR4工具）

### 安装ANTLR4运行时

Ubuntu/Debian:
```bash
sudo apt-get install antlr4 libantlr4-runtime-dev
```

macOS:
```bash
brew install antlr4-cpp-runtime
```

### 编译步骤

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 编译
make -j$(nproc)

# 安装（可选）
sudo make install
```

## 使用方法

### 基本用法

```bash
# 编译CHTL文件，生成HTML、CSS和JS
chtl input.chtl

# 只生成HTML
chtl -h input.chtl

# 指定输出文件名
chtl -o output input.chtl

# 压缩输出
chtl --minify input.chtl
```

### CHTL语法示例

```chtl
// 定义模板
[Template] @Style TextStyle
{
    color: #333;
    font-size: 16px;
}

// HTML结构
html
{
    body
    {
        div
        {
            id: container;
            
            style
            {
                .box  // 自动添加类名
                {
                    padding: 20px;
                    background: white;
                }
            }
            
            text
            {
                "Hello, CHTL!"
            }
            
            script
            {
                // CHTL JS扩展语法
                {{#container}}->listen({
                    click: () => {
                        console.log('Clicked!');
                    }
                });
            }
        }
    }
}
```

## 主要特性详解

### 1. 简化的元素语法

```chtl
div
{
    id: myDiv;
    class: container main;
    
    span
    {
        text { "内容" }
    }
}
```

### 2. 局部样式块

```chtl
div
{
    style
    {
        // 内联样式
        margin: 10px;
        
        // 自动生成类选择器
        .card
        {
            padding: 20px;
        }
        
        // 伪类支持
        &:hover
        {
            background: #f0f0f0;
        }
    }
}
```

### 3. 模板系统

```chtl
// 定义模板
[Template] @Element Card
{
    div
    {
        style { ... }
    }
}

// 使用模板
body
{
    @Element Card;
}
```

### 4. CHTL JavaScript扩展

```chtl
script
{
    // 增强选择器
    {{.button}}->listen({
        click: handleClick
    });
    
    // 事件委托
    {{#parent}}->delegate({
        target: {{.child}},
        click: () => { ... }
    });
    
    // 动画
    animate({
        duration: 300,
        easing: ease-in-out,
        begin: { opacity: 0 },
        end: { opacity: 1 }
    });
}
```

## 开发状态

本项目仍在积极开发中。当前实现包含：

- ✅ 基础项目结构
- ✅ ANTLR4语法定义
- ✅ AST节点系统
- ✅ 符号表管理
- ✅ 代码扫描器
- ✅ 编译器框架
- ✅ 代码生成器框架
- ⏳ 完整的语法实现
- ⏳ 模板系统
- ⏳ 优化和错误处理

## 贡献

欢迎提交Issue和Pull Request。在提交代码前，请确保：

1. 代码符合项目的编码规范
2. 添加了适当的测试
3. 更新了相关文档

## 许可证

MIT License

## 联系方式

如有问题或建议，请通过GitHub Issues联系我们。