# CHTL编译器系统 - ANTLR4语法定义

本项目使用ANTLR4完整实现了CHTL（超文本语言）的编译器系统。CHTL是基于C++语言实现的超文本语言，旨在提供一种更符合开发者编写HTML代码的方式。

## 系统架构

CHTL编译器系统包含4个独立的编译器和1个代码扫描器：

### 1. CHTL编译器 (CHTL.g4)
负责处理CHTL核心语法，包括：
- **元素定义**：HTML元素的CHTL语法表示
- **属性语法**：使用`:`或`=`定义属性
- **文本节点**：`text { }` 语法
- **模板系统**：`[Template]` 定义样式组、元素、变量组模板
- **自定义系统**：`[Custom]` 支持特例化操作
- **命名空间**：`[Namespace]` 防止模块污染
- **导入机制**：`[Import]` 导入外部资源
- **约束系统**：`except` 关键字实现定义域约束
- **配置组**：`[Configuration]` 自定义编译行为

### 2. CSS编译器 (CSS.g4)
处理原生CSS语法，支持：
- 所有CSS选择器（类、ID、属性、伪类、伪元素等）
- CSS属性和值
- @规则（@media、@keyframes、@import等）
- CSS函数和calc表达式
- CSS变量
- 完整的CSS3+特性

### 3. JavaScript编译器 (JavaScript.g4)
处理原生JavaScript语法，支持：
- ES6+所有语法特性
- 类、模块、异步函数
- 解构赋值、箭头函数
- 模板字符串
- import/export模块系统
- 完整的表达式和语句

### 4. CHTL JavaScript编译器 (CHTLJavaScript.g4)
在原生JavaScript基础上扩展CHTL特性：
- **增强选择器**：`{{selector}}` 语法
- **箭头操作符**：`->` 替代 `.` 明确使用CHTL扩展
- **listen方法**：简化事件监听器绑定
- **delegate方法**：事件委托机制
- **animate函数**：动画API封装

### 5. 代码扫描器 (Scanner.g4)
负责精准切割代码并分发给对应编译器：
- 识别CHTL、CSS、JS、CHTL JS代码块
- 处理嵌套结构
- 管理编译模式切换
- 实现代码分发逻辑

## 使用方法

### 1. 生成解析器
```bash
# 生成Java目标代码
antlr4 -o output/java CHTL.g4
antlr4 -o output/java CSS.g4
antlr4 -o output/java JavaScript.g4
antlr4 -o output/java CHTLJavaScript.g4
antlr4 -o output/java Scanner.g4

# 生成C++目标代码（推荐，因为CHTL基于C++实现）
antlr4 -Dlanguage=Cpp -o output/cpp CHTL.g4
antlr4 -Dlanguage=Cpp -o output/cpp CSS.g4
antlr4 -Dlanguage=Cpp -o output/cpp JavaScript.g4
antlr4 -Dlanguage=Cpp -o output/cpp CHTLJavaScript.g4
antlr4 -Dlanguage=Cpp -o output/cpp Scanner.g4
```

### 2. 编译流程
1. **扫描阶段**：Scanner扫描源文件，识别不同类型的代码块
2. **分发阶段**：根据代码类型分发给对应编译器
3. **解析阶段**：各编译器独立解析各自负责的代码
4. **生成阶段**：生成目标HTML/CSS/JS代码

### 3. 示例代码
```chtl
[Configuration]
{
    INDEX_INITIAL_COUNT = 0;
    DEBUG_MODE = false;
}

[Template] @Style DefaultText
{
    color: black;
    font-size: 16px;
}

body
{
    div
    {
        style
        {
            @Style DefaultText;
            .container {
                width: 100%;
                max-width: 1200px;
            }
        }
        
        script
        {
            {{.container}}->listen({
                click: () => {
                    console.log("Container clicked");
                }
            });
        }
        
        text
        {
            "Hello CHTL!"
        }
    }
}
```

## 特性支持

### CHTL核心特性
- ✅ 元素和属性
- ✅ 文本节点
- ✅ 字面量（有引号/无引号）
- ✅ CE对等式（: 与 = 等价）
- ✅ 局部样式块
- ✅ 自动化类名/ID
- ✅ 上下文推导（&符号）
- ✅ 模板系统（样式组/元素/变量组）
- ✅ 继承机制
- ✅ 自定义和特例化
- ✅ 导入/导出
- ✅ 命名空间
- ✅ 约束系统
- ✅ 原始嵌入

### CHTL JavaScript扩展
- ✅ 增强选择器 `{{selector}}`
- ✅ 箭头操作符 `->`
- ✅ listen事件监听
- ✅ delegate事件委托
- ✅ animate动画API

## 注意事项

1. **编译器独立性**：4个编译器完全独立，互不干扰
2. **精准切割**：Scanner必须准确识别代码边界
3. **模式切换**：在style和script块中正确切换解析模式
4. **CHTL JS识别**：通过特征（{{、->、listen等）判断是否使用CHTL JS编译器

## 后续开发

1. 实现语义分析和代码生成
2. 添加错误处理和恢复机制  
3. 优化性能和内存使用
4. 支持源码映射（Source Map）
5. 实现CMOD和CJMOD模块系统