# CHTL编译器开发记录

## 项目概述
CHTL（C++ Hypertext Language）是基于C++语言实现的超文本语言，使用MIT开源协议。

## 开发环境
- 编程语言：C++17
- 开发环境：VSCode + CMake
- 构建系统：CMake

## 用户请求记录

### 第一阶段：基础架构搭建

1. **初始请求**
   - 全程使用中文模式，使用锚点进行记忆
   - 目的：实现足够完美的CHTL编译器

2. **创建基础结构**
   - 创建common文件夹（后改为Common）
   - 创建GlobalMap全局静态表和Token
   - 要求：将Token和GlobalMap分成不同文件，使用类封装
   - GlobalMap使用static const map实现枚举表和字符串映射

3. **状态机系统**
   - 创建state文件夹（后改为State）
   - 创建：BasicState, ChtlState, CssState, JsState, Chtl_JsState
   - 完成BasicState和ChtlState，其他占位

4. **上下文管理**
   - 创建Context文件夹
   - 创建：BasicContext, ChtlContext, CssContext, JsContext, Chtl_JsState
   - 实现BasicContext和ChtlContext，其他预留

5. **词法分析器**
   - 创建Lexer文件夹
   - 创建BasicLexer和ConfigLexer
   - 在Lexer体系中集成状态机和上下文

6. **自动化管理**
   - 在State文件夹创建StateFactory（自动化管理状态）
   - 在Context创建ContextFactory（自动化标记上下文）
   - 将两者集成至Lexer体系

7. **节点系统**
   - 创建Node文件夹
   - 创建Node文件，直接包含Element和Text

### 第二阶段：CHTL特定节点

8. **节点扩展**
   - 修正：Lexer文件夹应该大写
   - 不是ChtlLexer，而是ConfigLexer
   - 在Node文件夹创建独立文件：
     - Comment注释节点
     - Template（3种类型）
     - Custom（3种类型）
     - Style（局部和全局）
     - Config节点
     - Import节点
     - Namespace节点
     - Operate节点

9. **注释语法修正**
   - Comment节点是"--"节点（CHTL特有）
   - "//"和"/* */"不应该作为节点
   - 完成原始嵌入（Origin节点）

### 第三阶段：解析器和生成器

10. **文件夹重命名**
    - 将所有顶级文件夹改为大写开头
    - context → Context
    - node → Node
    - state → State
    - lexer → Lexer
    - 等等

11. **解析器系统**
    - 创建Parser文件夹
    - 创建BasicParser, ConfigParser

12. **生成器系统**
    - 创建Generator文件夹
    - 创建BasicGenerator, ConfigGenerator

13. **其他模块**
    - 创建Css, Js, Chtl_Js, Scanner文件夹
    - 后续创建Optimize, Utils（不是Util）, Predefine文件夹

### 第四阶段：功能实现

14. **注释功能实现**
    - 实现"--"注释语法
    - 被生成器识别并保留在输出中

15. **架构调整**
    - **重要修正**："注意！不存在ChtlLexer，CHTL编译器只使用BasicLexer和ConfigLexer"
    - **进一步说明**："BasicLexer是标准语法分析器，而ConfigLexer是配置驱动语法分析器"

16. **Standard类体系**
    - 用户建议："如果你不喜欢这样的命名方式，你可以为所有使用这样的结构的类创建Standard类"
    - **最终指示**："所有使用Basic的都需要更新一个Standard"
    - 创建的Standard类：
      - StandardLexer（继承BasicLexer）
      - StandardState（继承ChtlState）
      - StandardContext（继承ChtlContext）
      - StandardParser（继承BasicParser）
      - StandardGenerator（继承HtmlGenerator）

### 第五阶段：全权开发
17. **最新请求**："接下来我将全权交给你，如何？"

18. **暂停整理**："请先暂停一下，整理一下之前我的请求信息，创建一个md文件，我有用"
    - 创建了本开发记录文件

19. **继续开发**："继续你的开发即可"

## 当前项目结构

```
/workspace/
├── include/
│   ├── Common/
│   │   ├── GlobalMap.h
│   │   ├── Token.h
│   │   └── TokenType.h
│   ├── Context/
│   │   ├── BasicContext.h
│   │   ├── ChtlContext.h
│   │   ├── ContextFactory.h
│   │   └── StandardContext.h
│   ├── Lexer/
│   │   ├── BasicLexer.h
│   │   ├── ConfigLexer.h
│   │   └── StandardLexer.h
│   ├── State/
│   │   ├── BasicState.h
│   │   ├── ChtlState.h
│   │   ├── CssState.h
│   │   ├── JsState.h
│   │   ├── ChtlJsState.h
│   │   ├── StateFactory.h
│   │   └── StandardState.h
│   ├── Node/
│   │   ├── Node.h (包含Element和Text)
│   │   ├── Comment.h
│   │   ├── Template.h
│   │   ├── Custom.h
│   │   ├── Style.h
│   │   ├── Config.h
│   │   ├── Import.h
│   │   ├── Namespace.h
│   │   ├── Operate.h
│   │   └── Origin.h
│   ├── Parser/
│   │   ├── BasicParser.h
│   │   ├── ConfigParser.h
│   │   └── StandardParser.h
│   ├── Generator/
│   │   ├── BasicGenerator.h
│   │   ├── ConfigGenerator.h
│   │   ├── HtmlGenerator.h
│   │   └── StandardGenerator.h
│   └── Scanner/
│       ├── Segment.h
│       └── BridgeScanner.h
├── src/
│   └── (对应的实现文件)
├── examples/
│   ├── simple.chtl
│   ├── test.chtl
│   ├── complete_demo.chtl
│   └── basic_demo.chtl
├── tests/
├── docs/
├── CMakeLists.txt
└── CHTL语法文档.md
```

## 关键设计决策

1. **类层次结构**
   - Basic系列：抽象基类
   - Standard系列：标准实现
   - 特定实现：如ChtlState, ConfigLexer等

2. **CHTL特性**
   - 使用"--"作为会被保留的注释
   - 支持模板、自定义元素、样式、配置等
   - 原始嵌入功能（Origin节点）

3. **编译器架构**
   - Lexer → Parser → AST → Generator
   - 状态机驱动的词法分析
   - 上下文管理的符号表和作用域

## 当前进展

1. **已完成**
   - ✅ 基础架构搭建
   - ✅ 词法分析器（StandardLexer）
   - ✅ 状态机系统
   - ✅ 上下文管理
   - ✅ 所有CHTL节点类型定义
   - ✅ "--"注释功能（词法分析和生成）
   - ✅ 基础解析器（StandardParser）
   - ✅ HTML生成器（HtmlGenerator）
   - ✅ 基本元素、文本、属性解析
   - ✅ DOCTYPE声明生成
   - ✅ 解决了html元素丢失问题
   - ✅ style块解析（局部样式）
   - ✅ 修复了token重复读取问题
   - ✅ 模板定义解析（[Template] @Style/Element/Var）
   - ✅ 自定义定义解析（[Custom] @Style/Element/Var）
   - ✅ 模板继承（inherit关键字）
   - ✅ 模板使用（在元素中使用@Style等）
   - ✅ 配置块解析（[Configuration]及嵌套的[Name]等）

2. **正在进行**
   - 🔄 完善StandardParser的CHTL特性支持
   - 🔄 实现Configuration块解析
   - 🔄 实现Import和Namespace解析

3. **待完成**
   - ⏳ CSS状态机（CssState）
   - ⏳ JavaScript状态机（JsState）
   - ⏳ 导入系统
   - ⏳ 命名空间支持
   - ⏳ 优化系统
   - ⏳ 完整测试套件

## 当前成果总结

经过本阶段的开发，CHTL编译器已具备以下核心功能：

### 词法分析器（Lexer）
- StandardLexer：完整的CHTL词法分析
- 支持所有CHTL特殊标记（@Style, @Element, [Template]等）
- 正确处理注释（`--`保留，`//`和`/* */`跳过）

### 语法分析器（Parser）
- StandardParser：核心CHTL语法解析
- 支持的语法结构：
  - HTML元素、属性、文本
  - style块（局部样式）
  - 模板定义（[Template]）
  - 自定义定义（[Custom]）  
  - 配置块（[Configuration]）
  - 模板使用（@Style等）
  - CHTL注释（--）

### 代码生成器（Generator）
- HtmlGenerator：基础HTML生成
- 支持DOCTYPE声明
- 内联样式处理

### 节点系统（AST）
- 完整的节点类型定义
- 支持所有CHTL特性节点

## 技术要点

1. **注释处理**
   - `//` 和 `/* */` 在解析时被跳过
   - `--` 被保留并转换为HTML注释 `<!-- -->`

2. **Standard类的作用**
   - StandardLexer：标准CHTL词法分析器
   - StandardParser：标准CHTL语法分析器
   - StandardGenerator：标准HTML生成器
   - 这些是用户实际使用的具体类

3. **配置驱动**
   - ConfigLexer：专门解析[Configuration]块
   - ConfigParser：处理配置语法
   - ConfigGenerator：生成各种配置格式

4. **解析器实现细节**
   - 使用peekNextToken()而不是getNextToken()开始解析
   - parseDocument会创建document节点，但如果只有一个html元素，直接返回html
   - parseElement处理嵌套元素和属性的识别
   - parseAttribute同时处理属性和嵌套元素的情况

5. **已解决的问题**
   - html元素丢失：原因是多调用了一次getNextToken()
   - DOCTYPE不生成：需要在HtmlGenerator::generate中检查根节点
   - style内容包含额外元素：parseInlineStyle中使用advance()而不是currentToken()导致token被重复读取
   - #符号被分离：词法分析器将#作为独立token（待优化）

## 下一步计划

根据用户的"全权交给你"指示，计划如下：

1. **继续完善解析器**
   - ✅ 实现模板解析
   - ✅ 实现自定义元素解析
   - ✅ 实现样式块的完整解析
   - ✅ 实现配置块解析
   - ⏳ 实现Import和Namespace解析
   - ⏳ 实现Operate节点（DOM操作）
   - ⏳ 实现Origin节点（原始代码嵌入）

2. **增强生成器**
   - ⏳ 实现模板展开机制
   - ⏳ 优化HTML输出格式
   - ⏳ 实现样式收集和优化
   - ⏳ 支持脚本整合

3. **实现高级特性**
   - ⏳ 导入系统（多文件编译）
   - ⏳ 命名空间支持
   - ⏳ 操作节点（DOM操作）
   - ⏳ CSS和JavaScript状态机

4. **测试和优化**
   - ⏳ 创建完整测试套件
   - ⏳ 性能优化
   - ⏳ 错误恢复机制
   - ⏳ 编写API文档
   - ⏳ 创建用户指南