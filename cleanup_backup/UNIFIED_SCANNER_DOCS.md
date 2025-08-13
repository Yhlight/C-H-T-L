# CHTL统一扫描器文档

## 概述

CHTL统一扫描器是一个高性能的单次扫描解决方案，它通过状态机和上下文推导技术，能够：
1. 支持`--`生成性注释的三种语言（HTML、CSS、JavaScript）注释生成
2. 一次扫描完成所有处理（避免CSS预处理器的两次扫描性能问题）
3. 支持样式组和变量组的实时展开
4. 准确识别和处理CHTL的所有语法特性

## 核心特性

### 1. 生成性注释（--）

生成性注释会根据当前语言上下文自动生成相应格式的注释：

```chtl
-- 在CHTL/HTML上下文中
<!-- 在CHTL/HTML上下文中 -->

style {
    -- 在CSS上下文中
    /* 在CSS上下文中 */
}

script {
    -- 在JavaScript上下文中
    // 在JavaScript上下文中
    
    -- 多行注释
    -- 会自动格式化
    /* 
     * 多行注释
     * 会自动格式化
     */
}
```

### 2. 状态管理

扫描器维护以下状态：

- **Normal** - 普通文本状态
- **InElement** - 在CHTL元素中
- **InAttribute** - 在属性中
- **InStyleBlock** - 在style块中
- **InScriptBlock** - 在script块中
- **InComment** - 在注释中
- **InGenerativeComment** - 在生成性注释中
- **InString** - 在字符串中
- **InTemplate** - 在模板定义中
- **InImport** - 在导入语句中
- **InOrigin** - 在原始嵌入中

### 3. 语言上下文

扫描器能够准确识别四种语言上下文：

- **CHTL** - CHTL语法上下文
- **HTML** - HTML上下文
- **CSS** - CSS上下文
- **JavaScript** - JavaScript上下文

### 4. 一次扫描处理

统一扫描器在单次扫描中完成：

```
输入 → 扫描器 → 令牌流
         ↓
    同时处理：
    - 生成性注释转换
    - 样式组展开
    - 变量组替换
    - 上下文推导
    - 语法验证
```

## 实现架构

### 组件结构

```
CHTLUnifiedScanner
├── 状态机管理
│   ├── 状态栈
│   └── 上下文切换
├── 令牌生成器
│   ├── 令牌类型识别
│   └── 上下文标记
├── 扫描器方法
│   ├── scanNormal()
│   ├── scanStyleBlock()
│   ├── scanScriptBlock()
│   └── scanGenerativeComment()
└── 处理器集成
    ├── GenerativeCommentProcessor
    ├── 样式组展开
    └── 变量组展开
```

### 扫描流程

1. **初始化**：设置初始状态和上下文
2. **字符扫描**：逐字符读取输入
3. **状态转换**：根据当前字符和状态决定转换
4. **令牌生成**：创建带上下文信息的令牌
5. **实时处理**：展开样式组、变量组，转换注释

## API使用

### 基本使用

```cpp
// 创建扫描器
CHTLUnifiedScanner scanner(chtlCode, context);
scanner.setTemplateManager(templateManager);
scanner.setCustomManager(customManager);

// 配置
ScannerConfig config;
config.processGenerativeComments = true;
config.expandStyleGroups = true;
config.expandVarGroups = true;
scanner.setConfig(config);

// 执行扫描
scanner.scan();

// 获取令牌
const auto& tokens = scanner.getTokens();
```

### 令牌结构

```cpp
struct Token {
    TokenType type;          // 令牌类型
    std::string value;       // 令牌值
    size_t line;            // 行号
    size_t column;          // 列号
    size_t position;        // 位置
    LanguageContext context; // 语言上下文
};
```

### 生成性注释处理

```cpp
GenerativeCommentProcessor processor(context);

// 自动根据上下文生成注释
std::string htmlComment = processor.processComment("comment", LanguageContext::HTML);
// 结果: <!-- comment -->

std::string cssComment = processor.processComment("comment", LanguageContext::CSS);
// 结果: /* comment */

std::string jsComment = processor.processComment("comment", LanguageContext::JavaScript);
// 结果: // comment
```

### 上下文推导

```cpp
ScannerContextInferencer inferencer;

// 元素上下文推导
inferencer.enterElement("style");  // 切换到CSS上下文
inferencer.enterElement("script"); // 切换到JavaScript上下文

// 内容推导
LanguageContext ctx = ScannerHelper::inferContextFromContent(content);
```

## 高级特性

### 1. 实时样式组展开

```css
style {
    .button {
        @Style ButtonStyle;  /* 扫描时立即展开 */
        color: white;
    }
}
```

扫描结果：
```css
style {
    .button {
        display: inline-block;
        padding: 10px 20px;
        border-radius: 5px;
        cursor: pointer;
        color: white;
    }
}
```

### 2. 实时变量组替换

```css
style {
    body {
        background: Colors(primary);    /* 扫描时立即替换 */
        padding: Spacing(md);          /* 扫描时立即替换 */
    }
}
```

扫描结果：
```css
style {
    body {
        background: #3498db;
        padding: 20px;
    }
}
```

### 3. 嵌套上下文处理

扫描器能正确处理嵌套的语言上下文：

```chtl
div {                    // CHTL上下文
    style {              // 切换到CSS上下文
        -- CSS注释      // 生成 /* CSS注释 */
    }
    
    script {             // 切换到JavaScript上下文
        -- JS注释       // 生成 // JS注释
    }
}                        // 返回CHTL上下文
```

### 4. 智能注释格式化

生成性注释处理器会智能格式化长注释：

```chtl
-- 这是一个非常长的注释，它会被自动换行并格式化，以确保生成的注释符合各种语言的最佳实践
```

在CSS中生成：
```css
/* 
 * 这是一个非常长的注释，它会被自动换行并格式化，
 * 以确保生成的注释符合各种语言的最佳实践
 */
```

## 性能优化

### 1. 单次扫描

- 避免了CSS预处理器的两次扫描问题
- 所有处理在一次遍历中完成
- 减少了内存分配和字符串操作

### 2. 缓存机制

- 展开的样式组会被缓存
- 解析的变量组会被缓存
- 避免重复查找和展开

### 3. 流式处理

- 支持大文件的流式扫描
- 令牌按需生成
- 内存使用可控

## 错误处理

扫描器提供详细的错误信息：

```
Scanner Error at line 10:15 - Style group 'UnknownStyle' not found
Scanner Warning at line 20:8 - Variable 'unknownVar' not found in group 'Colors'
```

## 配置选项

```cpp
struct ScannerConfig {
    bool processGenerativeComments = true;  // 处理--注释
    bool expandStyleGroups = true;          // 展开样式组
    bool expandVarGroups = true;            // 展开变量组
    bool validateSyntax = true;             // 验证语法
    bool preserveWhitespace = true;         // 保留空白
    bool trackContext = true;               // 跟踪上下文
};
```

## 最佳实践

### 1. 配置优化

```cpp
// 生产环境配置
ScannerConfig prodConfig;
prodConfig.processGenerativeComments = true;
prodConfig.expandStyleGroups = true;
prodConfig.expandVarGroups = true;
prodConfig.preserveWhitespace = false;  // 移除不必要的空白

// 开发环境配置
ScannerConfig devConfig;
devConfig.validateSyntax = true;
devConfig.preserveWhitespace = true;    // 保留格式
```

### 2. 错误处理

```cpp
scanner.scan();

// 检查扫描错误
auto errors = context->getErrors();
if (!errors.empty()) {
    for (const auto& error : errors) {
        std::cerr << error << std::endl;
    }
    return false;
}
```

### 3. 自定义注释生成器

```cpp
GenerativeCommentProcessor processor(context);

// 注册自定义生成器
processor.registerGenerator(LanguageContext::CSS, 
    [](const std::string& content, LanguageContext) {
        return "/** " + content + " **/";  // 自定义CSS注释格式
    });
```

## 示例：完整扫描流程

```chtl
-- CHTL统一扫描器示例

[Template] @Style ButtonStyle {
    padding: 10px 20px;
    border-radius: 5px;
}

html {
    head {
        style {
            -- 全局样式
            .button {
                @Style ButtonStyle;
                background: Colors(primary);
            }
        }
    }
    
    body {
        script {
            -- 初始化应用
            const app = new App();
            app.init();
        }
    }
}
```

扫描器会生成准确的令牌流，每个令牌都带有正确的语言上下文，样式组和变量组被实时展开，生成性注释被转换为相应的格式。

这个统一扫描器为CHTL提供了高效、准确的代码处理能力，是整个编译系统的基础组件。