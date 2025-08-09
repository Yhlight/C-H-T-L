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

### 第六阶段：CSS/JS静态分析器
20. **实现CSS和JS编译器**："下一步是实现CSS编译器和JS编译器"
    - 用户说明：CSS和JS编译器不是真的编译器，而是静态分析器
    - 不需要能够运行，也不需要能够读懂
    - 但要能够做到静态分析

21. **现代语法支持**：
    - CSS编译器和JS编译器需要较现代支持
    - 例如至少支持ES2022的语法
    - CSS和JS编译器不会处理CHTL的内容，而是处理原生的CSS和JS

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
├── Css/
│   ├── CMakeLists.txt
│   ├── CssTypes.h
│   ├── CssAnalyzer.h
│   ├── CssAnalyzer.cpp
│   ├── CssTokenizer.h
│   ├── CssTokenizer.cpp
│   └── CssBlockExtractor.h
├── Js/
│   ├── CMakeLists.txt
│   ├── JsTypes.h
│   ├── JsAnalyzer.h
│   ├── JsAnalyzer.cpp
│   ├── JsTokenizer.h
│   └── JsBlockExtractor.h
├── Chtl_Js/
│   └── (待实现)
├── examples/
│   ├── simple.chtl
│   ├── test.chtl
│   ├── complete_demo.chtl
│   ├── basic_demo.chtl
│   └── showcase.chtl
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
   - ✅ Import语句解析（支持各种导入类型和别名）
   - ✅ Namespace定义和使用（支持嵌套命名空间）
   - ✅ Operate节点解析（insert、delete、replace操作）
   - ✅ Origin节点解析（原始HTML、CSS、JavaScript嵌入）
   - ✅ CSS静态分析器（支持现代CSS特性）
   - ✅ JS静态分析器（支持ES2022+）

2. **正在进行**
   - 🔄 实现模板展开机制
   - 🔄 实现Scanner系统（代码分段）
   - 🔄 优化代码生成器

3. **待完成**
   - ⏳ CHTL-JS编译器（Chtl_Js）
   - ⏳ CSS/JS的完整tokenizer实现
   - ⏳ CSS/JS的block extractor实现
   - ⏳ 导入系统的完整实现
   - ⏳ 优化系统
   - ⏳ 完整测试套件

## 当前成果总结

经过本阶段的开发，CHTL编译器已实现了完整的语法解析功能：

### 词法分析器（Lexer）
- StandardLexer：完整的CHTL词法分析
- 支持所有CHTL特殊标记（@Style, @Element, [Template]等）
- 正确处理注释（`--`保留，`//`和`/* */`跳过）

### 语法分析器（Parser）✅ 已完成
- StandardParser：完整的CHTL语法解析实现
- 支持的语法结构：
  - **基础HTML**：元素、属性、文本
  - **样式系统**：style块（局部样式）、内联样式
  - **模板系统**：[Template] @Style/Element/Var
  - **自定义系统**：[Custom] @Style/Element/Var  
  - **配置系统**：[Configuration]及嵌套配置组
  - **模块系统**：[Import]各种导入、[Namespace]命名空间
  - **操作系统**：insert/delete/replace操作
  - **原始嵌入**：[Origin] @Html/Style/JavaScript
  - **模板使用**：@Style等在元素中的使用，支持from命名空间
  - **CHTL注释**：-- 注释保留

### 代码生成器（Generator）
- HtmlGenerator：基础HTML生成
- 支持DOCTYPE声明
- 内联样式处理

### 节点系统（AST）✅ 已完成
- 完整的节点类型定义
- 支持所有CHTL语法特性的节点类型
- 实现了完整的AST构建

## 里程碑成就

### 第一阶段：基础架构（已完成）
- ✅ 建立项目结构（include/src分离）
- ✅ 实现Token和TokenType系统
- ✅ 创建GlobalMap全局静态表
- ✅ 实现状态机系统（BasicState、ChtlState等）
- ✅ 实现上下文管理（BasicContext、ChtlContext等）

### 第二阶段：词法分析（已完成）
- ✅ 实现BasicLexer抽象基类
- ✅ 实现StandardLexer（CHTL标准词法分析器）
- ✅ 实现ConfigLexer（配置驱动词法分析器）
- ✅ 正确处理所有CHTL特殊语法标记

### 第三阶段：语法分析（已完成）
- ✅ 实现完整的AST节点系统（15+种节点类型）
- ✅ 实现StandardParser，支持：
  - 基础HTML结构解析
  - CHTL注释（--）保留
  - style块和内联样式
  - 模板定义和使用
  - 自定义元素、样式、变量
  - 配置块和嵌套配置
  - Import和Namespace
  - DOM操作（insert/delete/replace）
  - 原始代码嵌入（[Origin]）

### 第四阶段：代码生成（基础完成）
- ✅ 实现HtmlGenerator基础功能
- ✅ 支持DOCTYPE生成
- ✅ 支持基本HTML输出

### 第五阶段：CSS/JS静态分析器（已完成）
- ✅ CSS静态分析器设计和实现
- ✅ JS静态分析器设计和实现
- ✅ 支持现代语法特性

## CSS/JS静态分析器实现

### CSS静态分析器
位置：`/workspace/Css/`

**设计目标**：
- 支持现代CSS语法（CSS3+）
- 静态分析CSS结构，不执行
- 检测现代CSS特性使用情况
- 提取关键信息供CHTL编译器使用

**实现的功能**：
1. **现代CSS特性检测**：
   - CSS Variables（自定义属性）
   - Grid Layout
   - Flexbox
   - Container Queries (@container)
   - Cascade Layers (@layer)
   - :has() 选择器
   - :is()/:where() 选择器
   - Logical Properties
   - aspect-ratio
   - color() 函数
   - subgrid

2. **CSS结构分析**：
   - 选择器提取和分析
   - 类名和ID提取
   - @规则处理（@media, @layer, @container等）
   - CSS变量定义和使用分析
   - 属性值对提取

3. **语法验证**：
   - 括号平衡检查
   - 基础语法验证
   - 注释处理

4. **代码质量分析**：
   - 规则统计
   - 选择器复杂度
   - 嵌套深度分析

关键文件：
- `CssTypes.h`：定义CSS相关类型、现代特性枚举
- `CssAnalyzer.h/cpp`：主分析器实现
- `CssTokenizer.h/cpp`：CSS词法分析（基础实现）
- `CssBlockExtractor.h`：CSS块提取器（接口）

### JS静态分析器
位置：`/workspace/Js/`

**设计目标**：
- 支持ES2022+语法
- 静态分析JavaScript结构
- 检测现代JS特性使用情况
- 提供代码质量指标

**实现的功能**：
1. **ES版本检测**：
   - ES6/ES2015：箭头函数、类、模板字符串、解构、let/const、模块等
   - ES2017：async/await
   - ES2020：可选链（?.）、空值合并（??）、BigInt、动态import
   - ES2022：顶层await、私有字段（#）、静态块、Error.cause、Array.at()
   - ESNext：装饰器等提案特性

2. **代码结构分析**：
   - 函数提取（普通函数、箭头函数、async函数、生成器）
   - 类分析（字段、方法、继承）
   - 变量和常量声明
   - import/export分析
   - 依赖关系提取

3. **代码质量分析**：
   - 圈复杂度计算
   - 嵌套深度分析
   - 代码行统计
   - 潜在问题检测

4. **语法验证**：
   - 括号平衡检查
   - 字符串和模板字符串处理
   - 注释处理（单行//和多行/* */）

关键文件：
- `JsTypes.h`：定义JS相关类型、ES版本枚举、现代特性结构
- `JsAnalyzer.h/cpp`：主分析器实现
- `JsTokenizer.h`：JS词法分析（接口）
- `JsBlockExtractor.h`：JS块提取器（接口）

### 技术特点
1. **纯静态分析**：不执行代码，只分析语法结构
2. **现代语法支持**：完整支持最新的CSS和JavaScript特性
3. **模块化设计**：分析器、tokenizer、块提取器分离
4. **可扩展性**：易于添加新的语法特性检测
5. **正则表达式驱动**：使用regex进行模式匹配和特性检测

### 与CHTL集成
- CSS分析器可用于分析Style节点中的CSS内容
- JS分析器可用于分析script标签中的JavaScript
- 为CHTL-JS扩展提供基础
- 支持代码优化和验证

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

1. **完善CSS/JS分析器**
   - ⏳ 实现CssTokenizer的完整功能
   - ⏳ 实现CssBlockExtractor
   - ⏳ 实现JsTokenizer
   - ⏳ 实现JsBlockExtractor
   - ⏳ 添加更多现代特性检测

2. **CHTL-JS编译器**
   - ⏳ 设计CHTL的JavaScript扩展语法
   - ⏳ 实现CHTL-JS词法分析
   - ⏳ 实现CHTL-JS语法分析
   - ⏳ 与标准JS分析器集成

3. **增强生成器**
   - ⏳ 实现模板展开机制
   - ⏳ 优化HTML输出格式
   - ⏳ 实现样式收集和优化
   - ⏳ 支持脚本整合

4. **集成和测试**
   - ⏳ 将CSS/JS分析器集成到主编译流程
   - ⏳ 创建综合测试用例
   - ⏳ 性能优化
   - ⏳ 文档编写