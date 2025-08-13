# CHTL CSS编译器文档

## 概述

CHTL CSS编译器提供了完整的CSS解析、编译、优化和验证功能。它支持原生CSS语法，并与CHTL的局部样式块系统无缝集成。

## 核心功能

### 1. CSS解析和编译

CSS编译器基于ANTLR4语法，支持完整的CSS3语法：

- 选择器（类型、类、ID、属性、伪类、伪元素）
- 组合器（后代、子元素、相邻兄弟、通用兄弟）
- 声明（属性和值）
- @规则（@media、@keyframes、@import等）
- CSS变量和calc()函数
- 注释处理

### 2. 全局样式块

在CHTL中，可以在`head`元素内使用`style`标签创建全局样式块：

```chtl
html
{
    head
    {
        style
        {
            /* 这里写原生CSS */
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 0;
            }
            
            .container {
                max-width: 1200px;
                margin: 0 auto;
            }
        }
    }
}
```

### 3. CSS优化

优化器提供多种优化选项：

- **合并规则**：相同选择器的规则自动合并
- **移除空规则**：自动删除没有声明的规则
- **简写属性**：将margin/padding等展开属性转换为简写形式
- **颜色优化**：#RRGGBB转换为#RGB，常见颜色值转换为名称
- **单位优化**：移除0值的单位

### 4. CSS验证

编译器提供语法验证功能：

- 检测语法错误
- 验证属性名和值的有效性
- 检查选择器语法
- 报告具体的错误位置和信息

### 5. 引用验证

CSS处理器可以验证CSS和HTML之间的引用关系：

- 检测未定义的类和ID
- 检测未使用的CSS规则
- 提供详细的警告信息

## API使用

### CSSCompiler

```cpp
// 创建编译器
auto compiler = std::make_shared<CSSCompiler>(context);

// 设置选项
compiler->setMinify(true);           // 压缩输出
compiler->setPreserveComments(false); // 不保留注释

// 编译CSS
std::string compiledCSS = compiler->compile(cssContent);

// 编译并获取规则分析
auto [css, rules] = compiler->compileWithAnalysis(cssContent);

// 验证CSS
std::vector<std::string> errors;
bool isValid = compiler->validate(cssContent, errors);
```

### CSSOptimizer

```cpp
// 创建优化器
CSSOptimizer::Options options;
options.mergeRules = true;
options.shorthandProperties = true;
options.optimizeColors = true;

CSSOptimizer optimizer(options);

// 优化规则
auto optimizedRules = optimizer.optimize(rules);
```

### CHTLCSSProcessor

```cpp
// 创建CSS处理器
auto cssProcessor = std::make_shared<CHTLCSSProcessor>(context);

// 添加全局样式
cssProcessor->addGlobalStyleBlock(globalCSS);

// 添加局部样式（带作用域）
cssProcessor->addLocalStyleBlock(localCSS, ".component");

// 生成最终CSS
std::string finalCSS = cssProcessor->generateFinalCSS();

// 验证引用
cssProcessor->validateReferences(usedClasses, usedIds);
```

## 与CHTL集成

### 在CHTLGenerator中使用

```cpp
// 处理全局样式块
generator.processGlobalStyleBlock(cssContent);

// 获取CSS处理器
auto cssProcessor = generator.getCSSProcessor();

// 获取最终CSS
std::string css = generator.getCSS();
```

### 局部样式块 vs 全局样式块

| 特性 | 局部样式块 | 全局样式块 |
|------|-----------|-----------|
| 位置 | 元素内部 | head元素内 |
| 语法 | CHTL增强语法 | 原生CSS |
| 作用域 | 自动作用域 | 全局 |
| 功能 | 自动类名、上下文推导 | 完整CSS功能 |

## 高级功能

### 1. 响应式设计支持

```css
@media (max-width: 768px) {
    .container {
        padding: 10px;
    }
}
```

### 2. 动画支持

```css
@keyframes fadeIn {
    from { opacity: 0; }
    to { opacity: 1; }
}

.fade-in {
    animation: fadeIn 0.3s ease-in;
}
```

### 3. CSS变量

```css
:root {
    --primary-color: #3498db;
    --secondary-color: #2ecc71;
}

.button {
    background-color: var(--primary-color);
}
```

### 4. 高级选择器

```css
/* 属性选择器 */
input[type="text"] { }

/* 伪类 */
a:hover { }
li:nth-child(2n) { }

/* 伪元素 */
p::first-line { }
h1::before { }

/* 组合器 */
.parent > .child { }
.element + .sibling { }
```

## 错误处理

CSS编译器提供详细的错误信息：

```
CSS Syntax Error at line 5:12 - mismatched input ';' expecting ':'
CSS Syntax Error at line 10:1 - extraneous input '}' expecting {<EOF>, ...}
```

## 性能优化

1. **批量处理**：将多个CSS块合并后统一处理
2. **缓存机制**：重复使用的CSS规则会被缓存
3. **延迟优化**：只在最终输出时进行优化
4. **并行处理**：大型CSS文件支持并行解析

## 最佳实践

1. **组织结构**：将全局样式放在head中，组件样式使用局部样式块
2. **命名规范**：使用BEM或其他命名规范避免冲突
3. **优化设置**：生产环境启用压缩和优化
4. **验证集成**：开发时启用引用验证
5. **渐进增强**：先写基础样式，再添加高级特性

## 示例

### 完整示例

```chtl
html
{
    head
    {
        style
        {
            /* Reset */
            * {
                margin: 0;
                padding: 0;
                box-sizing: border-box;
            }
            
            /* Typography */
            body {
                font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
                line-height: 1.6;
                color: #333;
            }
            
            /* Layout */
            .container {
                max-width: 1200px;
                margin: 0 auto;
                padding: 0 20px;
            }
            
            /* Components */
            .card {
                background: white;
                border-radius: 8px;
                padding: 24px;
                box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            }
        }
    }
    
    body
    {
        div
        {
            class: container;
            
            // 局部样式块
            style
            {
                .hero {
                    padding: 80px 0;
                    text-align: center;
                }
                
                &:hover {
                    background-color: #f5f5f5;
                }
            }
        }
    }
}
```

这个例子展示了全局样式块和局部样式块的配合使用，实现了完整的样式系统。