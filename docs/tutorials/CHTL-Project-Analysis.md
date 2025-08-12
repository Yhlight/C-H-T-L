# CHTL 项目全面分析

## 项目概述

CHTL (Compact HTML Template Language) 是一个基于 C++ 实现的超文本模板语言，旨在提供更符合开发者直觉的 HTML/CSS/JavaScript 编写方式。

### 核心特点
- **统一语法**：使用类似编程语言的块结构替代 HTML 标签
- **模板系统**：支持元素、样式和变量的复用
- **增强功能**：内置约束、继承、操作等高级特性
- **模块化**：支持 CMOD 和 CJmod 模块系统
- **可扩展**：通过 CJmod 支持 JavaScript 语法扩展

## 项目架构

### 1. 编译流程

```
源文件(.chtl) → 词法分析(Lexer) → 语法分析(Parser) → AST → 代码生成(Generator) → 输出(HTML/CSS/JS)
```

### 2. 核心组件

#### 2.1 词法分析器 (Lexer)
- **位置**: `src/Lexer/`, `include/Lexer/`
- **主要类**:
  - `BasicLexer`: 基础词法分析器
  - `StandardLexer`: CHTL 标准词法分析器
- **功能**: 将源代码转换为 Token 流

#### 2.2 语法分析器 (Parser)
- **位置**: `src/Parser/`, `include/Parser/`
- **主要类**:
  - `BasicParser`: 基础解析器
  - `StandardParser`: CHTL 标准解析器
  - `ConfigParser`: 配置块解析器
- **功能**: 将 Token 流转换为 AST

#### 2.3 AST 节点 (Node)
- **位置**: `src/Node/`, `include/Node/`
- **节点类型**:
  - `Element`: HTML 元素节点
  - `Template`: 模板定义节点
  - `Custom`: 自定义定义节点
  - `Style`: 样式节点
  - `Script`: 脚本节点
  - `Comment`: 注释节点
  - `Import/Export`: 导入导出节点
  - `Config`: 配置节点
  - `Namespace`: 命名空间节点
  - `Operate`: 操作节点(insert/delete)
  - `Origin`: 原始嵌入节点

#### 2.4 代码生成器 (Generator)
- **位置**: `src/Generator/`, `include/Generator/`
- **主要类**:
  - `Generator`: 基础生成器
  - `WebGenerator`: Web 代码生成器
  - `HtmlGenerator`: HTML 生成器
  - `ConfigManager`: 配置管理器
- **功能**: 将 AST 转换为目标代码

#### 2.5 上下文管理 (Context)
- **位置**: `src/Context/`, `include/Context/`
- **主要类**:
  - `BasicContext`: 基础上下文
  - `ChtlContext`: CHTL 上下文
  - `StandardContext`: 标准上下文
  - `CssContext`: CSS 上下文
  - `JsContext`: JavaScript 上下文

### 3. 模块系统

#### 3.1 CMOD (CHTL Module)
- **用途**: CHTL 原生模块格式
- **结构**:
  ```
  ModuleName/
  ├── src/
  │   └── ModuleName.chtl
  └── info/
      └── ModuleName.chtl
  ```

#### 3.2 CJmod (CHTL JavaScript Module)
- **位置**: `src/CJmod/`, `include/CJmod/`
- **主要类**:
  - `CJmodLoader`: 模块加载器
  - `CJmodProcessor`: 模块处理器
  - `ICJmod`: 模块接口
- **功能**: 扩展 CHTL JS 的语法和功能

### 4. 辅助系统

#### 4.1 状态机 (State)
- **位置**: `src/State/`, `include/State/`
- **用途**: 处理不同语法上下文的词法分析

#### 4.2 工具类 (Utils)
- **位置**: `src/Utils/`, `include/Utils/`
- **功能**: 各种辅助功能

#### 4.3 加载器 (Loader)
- **位置**: `src/Loader/`, `include/Loader/`
- **主要类**:
  - `ImportResolver`: 导入路径解析
  - `ModuleLoader`: 模块加载
  - `FileLoader`: 文件加载

## 语法特性

### 1. 基础语法
- **注释**: `//`, `/* */`, `--`
- **文本**: `text { "内容" }`
- **元素**: `div { }`
- **属性**: `id: "main"` 或 `id = "main"`

### 2. 高级特性
- **模板**: `[Template] @Element Card { }`
- **自定义**: `[Custom] @Style Theme { }`
- **继承**: `inherit @Style Base;`
- **操作**: `delete`, `insert`
- **约束**: `except span, @Html;`
- **导入**: `[Import] @Chtl from "module";`

### 3. 样式系统
- **内联样式**: 元素内的 `style { }`
- **自动类名**: `.box { }` 自动添加 class
- **上下文推导**: `&:hover` 

### 4. JavaScript 增强
- **由 CHTL JS 处理**:
  - `{{}}` 选择器
  - `->` 操作符
  - `listen`, `delegate`, `animate` API

## 编译器实现细节

### 1. Token 类型 (TokenType)
- 定义在 `include/Common/TokenType.h`
- 包括关键字、操作符、特殊标记等

### 2. 全局映射 (GlobalMap)
- 定义在 `src/Common/GlobalMap.cpp`
- 管理关键字、HTML 标签、CSS 属性等映射

### 3. 错误处理
- 多层错误收集机制
- 上下文相关的错误信息

### 4. 性能优化
- 流式处理
- 缓存机制
- 单次扫描（CJmod）

## 构建和使用

### 构建命令
```bash
make        # 构建编译器
make clean  # 清理构建文件
```

### 使用方式
```bash
./chtl input.chtl -o output.html
```

## 项目状态

### 已完成功能
- ✅ 核心语法解析和生成
- ✅ 模板和自定义系统
- ✅ 继承机制
- ✅ 删除/插入操作
- ✅ 约束系统
- ✅ 导入/导出
- ✅ 配置系统
- ✅ CJmod 基础框架

### 待完善功能
- ⚠️ 变量组函数调用的完整实现
- ⚠️ 槽位系统 (slot)
- ⚠️ 某些复杂文件的解析
- ⚠️ 性能优化

## 开发建议

1. **扩展新语法**：
   - 在 `TokenType.h` 添加新 Token
   - 在 `GlobalMap.cpp` 添加映射
   - 在 `StandardParser.cpp` 添加解析逻辑
   - 在 `WebGenerator.cpp` 添加生成逻辑

2. **添加新节点类型**：
   - 继承 `Node` 基类
   - 实现必要的虚函数
   - 在解析器和生成器中添加处理

3. **CJmod 开发**：
   - 实现 `ICJmod` 接口
   - 定义扫描规则
   - 提供运行时代码