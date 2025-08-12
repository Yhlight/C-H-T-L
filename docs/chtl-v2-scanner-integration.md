# CHTL v2 扫描器架构与 CHTL-JS 集成

## 概述

CHTL v2 的扫描器架构基于**代码切割**的设计理念，而不是传统的 AST 修改。这种设计带来了：

1. **高性能**：通过宽判/严判模式实现快速代码分块
2. **高准确性**：精确提取 CHTL-JS 语法，不影响原生 JS
3. **易维护**：无需跟踪 JS 语法更新，只关注 CHTL-JS 特有语法
4. **可扩展**：CJMOD 系统可以基于此架构轻松添加新语法

## 核心设计

### 1. 扫描模式

```cpp
enum class ScanMode {
    LOOSE,      // 宽判 - 快速分块，提高并行处理能力
    STRICT,     // 严判 - 精确提取 CHTL-JS 语法
    HYBRID      // 混合 - 先宽判分块，再严判处理
};
```

- **宽判模式**：基于语法结构（函数边界、大括号深度）快速将代码分成可并行处理的块
- **严判模式**：精确查找和提取 `{{}}` 表达式
- **混合模式**：结合两者优势，先分块再精确处理

### 2. 代码段结构

```cpp
struct CodeSegment {
    SegmentType type;        // JS 或 CHTL_JS
    std::string content;     // 代码内容
    size_t startLine;        // 起始位置
    size_t startColumn;
    
    // CHTL-JS 特有信息
    struct {
        size_t originalStart;
        size_t originalEnd;
        std::string placeholder;  // 替换占位符
    } chtlJsInfo;
};
```

### 3. CHTL-JS 编译流程

```
原始 JS 代码
    ↓
扫描器切割
    ↓
[JS段] [CHTL-JS段] [JS段] [CHTL-JS段] ...
    ↓
CHTL-JS 编译器处理每个 CHTL-JS 段
    ↓
生成替换内容
    ↓
代码合并器重组
    ↓
最终 JS 代码
```

## CHTL-JS 语法支持

### 1. 元素选择器
```javascript
{{#elementId}} → document.getElementById('elementId')
```

### 2. 当前元素引用
```javascript
{{&}} → (动态确定的当前元素)
```

### 3. 方法调用
```javascript
{{#button}}.listen('click', handler) → 
document.getElementById('button').addEventListener('click', handler)
```

## 实现亮点

### 1. 智能占位符系统

每个 CHTL-JS 表达式在切割时生成唯一占位符：

```cpp
// 切割时
segment.chtlJsInfo.placeholder = "__CHTL_JS_0__";

// 编译后替换
replacements["__CHTL_JS_0__"] = "document.getElementById('app')";
```

### 2. 上下文感知编译

```cpp
// 编译时传入上下文
std::map<std::string, std::string> context;
context["currentElement"] = "this";

// {{&}} 根据上下文编译为 this
```

### 3. 性能优化

- **并行处理**：宽判模式产生的代码块可以并行编译
- **增量编译**：只处理包含 CHTL-JS 的代码段
- **缓存机制**：相同的 CHTL-JS 表达式可以缓存编译结果

## 与 JS 静态分析器的集成

```cpp
// 1. 编译 CHTL-JS
ChtlJsCompiler compiler;
auto result = compiler.compile(jsCode, context);

// 2. 分析编译后的代码
NativeJsAnalyzer analyzer;
auto analysis = analyzer.analyze(result.javascript);

// 3. 综合结果
if (analysis.valid && result.success) {
    // 代码有效，可以安全使用
}
```

## CJMOD 扩展点

基于此架构，CJMOD 可以：

1. **注册新的表达式类型**
```cpp
scanner.registerCJMODPattern("@{", "}@", cjmodHandler);
```

2. **自定义编译逻辑**
```cpp
cjmodCompiler.registerHandler("customSyntax", [](expr) {
    return generateCustomCode(expr);
});
```

3. **扩展运行时**
```javascript
window.chtl.extensions.custom = function() { ... };
```

## 总结

CHTL v2 的扫描器架构通过代码切割实现了高效、准确的 CHTL-JS 语法扩展。这种设计：

- ✅ 不依赖 JS 语法解析，维护成本低
- ✅ 性能优秀，支持并行处理
- ✅ 扩展性强，CJMOD 可以轻松添加新语法
- ✅ 与现有工具链兼容，生成标准 JavaScript

这为 CHTL 的"无限语法扩展"愿景奠定了坚实基础。