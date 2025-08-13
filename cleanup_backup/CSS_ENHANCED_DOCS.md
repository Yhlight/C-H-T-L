# CHTL增强CSS功能文档

## 概述

CHTL通过上下文推导、状态管理和扫描器技术，为全局样式块提供了样式组（Style Group）和变量组（Variable Group）的支持。这使得CSS的编写更加模块化、可维护和可重用。

## 核心特性

### 1. 样式组（Style Groups）

样式组允许您定义一组可重用的CSS属性，然后在全局样式块中通过`@Style`指令使用。

#### 定义样式组

```chtl
// 模板样式组
[Template] @Style ButtonBase
{
    display: inline-block;
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    transition: all 0.3s ease;
}

// 自定义样式组（支持继承）
[Custom] @Style PrimaryButton
{
    @Style ButtonBase;  // 继承
    background-color: #3498db;
    color: white;
}
```

#### 在全局CSS中使用

```css
/* 在<style>标签内 */
.btn {
    @Style ButtonBase;
    margin-right: 10px;
}

.btn-primary {
    @Style PrimaryButton;
}
```

### 2. 变量组（Variable Groups）

变量组提供了集中管理CSS值的机制，支持主题化和一致性维护。

#### 定义变量组

```chtl
[Template] @Var ThemeColors
{
    primary: #3498db;
    secondary: #2ecc71;
    danger: #e74c3c;
    warning: #f39c12;
    info: #16a085;
    light: #ecf0f1;
    dark: #34495e;
}

[Template] @Var Spacing
{
    xs: 5px;
    sm: 10px;
    md: 20px;
    lg: 30px;
    xl: 40px;
}
```

#### 在CSS中使用

```css
/* 使用VarGroup(varName)语法 */
body {
    color: ThemeColors(dark);
    padding: Spacing(md);
}

.button {
    background-color: ThemeColors(primary);
    padding: Spacing(sm) Spacing(md);
}

/* 可以在CSS变量中使用 */
:root {
    --primary-color: ThemeColors(primary);
    --base-spacing: Spacing(md);
}
```

### 3. 上下文推导

CSS预处理器会智能推导当前上下文，提供相应的建议和验证。

#### 属性类型推导

```css
.element {
    /* 颜色属性 - 推荐颜色相关的变量组 */
    color: ThemeColors(primary);
    background-color: ThemeColors(light);
    
    /* 尺寸属性 - 推荐尺寸相关的变量组 */
    padding: Spacing(md);
    margin-bottom: Spacing(lg);
    
    /* 字体属性 - 推荐字体相关的变量组 */
    font-family: Typography(bodyFont);
    font-size: Typography(baseSize);
}
```

### 4. 状态管理

预处理器维护解析状态，确保正确处理嵌套和复杂的CSS结构。

#### 状态类型

- **Normal**: 普通CSS上下文
- **InStyleGroup**: 处理@Style使用
- **InVarGroup**: 处理变量组使用
- **InSelector**: 在选择器中
- **InDeclaration**: 在属性声明中
- **InValue**: 在属性值中

### 5. 扫描器技术

专门的CSS扫描器能够：

- 识别`@Style`指令
- 解析`VarGroup(varName)`模式
- 保持注释和格式
- 提供准确的错误位置信息

## 实现架构

### 组件结构

```
CHTLEnhancedCSSCompiler
    ├── CSSPreprocessor（预处理器）
    │   ├── CSSPreprocessScanner（扫描器）
    │   ├── CSSPreprocessContext（上下文）
    │   └── 样式组/变量组解析器
    └── CSSCompiler（标准CSS编译器）
```

### 处理流程

1. **扫描阶段**: 识别CHTL特定语法（@Style, VarGroup）
2. **解析阶段**: 查找并展开样式组和变量组
3. **预处理阶段**: 替换为实际的CSS代码
4. **编译阶段**: 使用标准CSS编译器处理
5. **优化阶段**: 合并规则、优化输出

## 高级功能

### 1. 继承链解析

```css
/* 支持多级继承 */
[Custom] @Style ExtendedButton
{
    @Style PrimaryButton;  // 继承PrimaryButton，间接继承ButtonBase
    font-weight: bold;
}
```

### 2. 条件样式组

```css
/* 在媒体查询中使用 */
@media (max-width: 768px) {
    .container {
        padding: Spacing(sm);  /* 响应式间距 */
    }
}
```

### 3. 嵌套支持

```css
.card {
    @Style CardStyle;
    
    h3 {
        color: ThemeColors(primary);
    }
    
    p {
        margin-bottom: Spacing(md);
    }
}
```

### 4. 错误检测

- 未定义的样式组警告
- 未找到的变量提示
- 循环继承检测
- 类型不匹配警告

## 集成API

### 在CHTLGenerator中使用

```cpp
// 创建生成器
CHTLGenerator generator(context, options);

// 处理带有样式组和变量组的全局CSS
std::string cssWithGroups = R"(
    body {
        @Style DefaultText;
        background: ThemeColors(light);
    }
)";

generator.processGlobalStyleBlock(cssWithGroups);
```

### 配置选项

```cpp
// 获取CSS处理器
auto cssProcessor = generator.getCSSProcessor();

// 启用/禁用增强功能
cssProcessor->setEnhancedMode(true);

// 设置管理器
cssProcessor->setTemplateManager(templateManager);
cssProcessor->setCustomManager(customManager);
```

## 最佳实践

### 1. 组织结构

```chtl
// 基础样式组
[Template] @Style BaseComponent
{
    box-sizing: border-box;
    position: relative;
}

// 特定组件样式
[Template] @Style Card
{
    @Style BaseComponent;
    background: white;
    border-radius: 8px;
}
```

### 2. 命名约定

- 样式组：PascalCase（如 `ButtonStyle`）
- 变量组：PascalCase（如 `ThemeColors`）
- 变量名：camelCase（如 `primaryColor`）

### 3. 模块化设计

```chtl
// 颜色系统
[Template] @Var ColorPalette
{
    // 基础颜色
    blue: #3498db;
    green: #2ecc71;
    red: #e74c3c;
    
    // 语义颜色
    primary: #3498db;
    success: #2ecc71;
    danger: #e74c3c;
}

// 间距系统
[Template] @Var SpacingScale
{
    base: 8px;
    xs: 4px;
    sm: 8px;
    md: 16px;
    lg: 24px;
    xl: 32px;
}
```

### 4. 性能优化

- 缓存已解析的样式组和变量组
- 避免深层嵌套继承
- 合理使用样式组粒度

## 示例：完整主题系统

```chtl
// 定义主题
[Template] @Var LightTheme
{
    background: #ffffff;
    text: #333333;
    border: #e0e0e0;
    shadow: rgba(0,0,0,0.1);
}

[Template] @Var DarkTheme
{
    background: #1a1a1a;
    text: #ffffff;
    border: #333333;
    shadow: rgba(255,255,255,0.1);
}

// 组件样式
[Template] @Style ThemedCard
{
    background: var(--theme-background);
    color: var(--theme-text);
    border: 1px solid var(--theme-border);
    box-shadow: 0 2px 4px var(--theme-shadow);
}
```

```css
/* 使用主题 */
:root {
    --theme-background: LightTheme(background);
    --theme-text: LightTheme(text);
    --theme-border: LightTheme(border);
    --theme-shadow: LightTheme(shadow);
}

@media (prefers-color-scheme: dark) {
    :root {
        --theme-background: DarkTheme(background);
        --theme-text: DarkTheme(text);
        --theme-border: DarkTheme(border);
        --theme-shadow: DarkTheme(shadow);
    }
}

.card {
    @Style ThemedCard;
    padding: Spacing(md);
}
```

这个增强的CSS系统为CHTL带来了强大的样式管理能力，使得大型项目的CSS维护变得更加简单和高效。