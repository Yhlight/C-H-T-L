# CHTL JavaScript编译器文档

## 概述

CHTL JavaScript编译器提供了完整的JavaScript解析、编译、优化和模块处理功能。它支持ES6+语法，并与CHTL的局部脚本块系统无缝集成，提供了增强的JavaScript开发体验。

## 核心功能

### 1. JavaScript解析和编译

基于ANTLR4语法，支持完整的ES6+语法：

- **声明**：var、let、const、函数、类、async/await
- **模块**：import/export语句
- **语法糖**：箭头函数、解构、模板字符串、展开运算符
- **高级特性**：Promise、Generator、Proxy、Symbol
- **作用域管理**：块级作用域、函数作用域、模块作用域

### 2. 全局脚本块

在CHTL中，可以在`head`或`body`元素内使用`script`标签：

```chtl
html
{
    head
    {
        script
        {
            // 全局JavaScript
            'use strict';
            
            class App {
                constructor() {
                    this.name = 'CHTL App';
                }
                
                init() {
                    console.log(`Initializing ${this.name}`);
                }
            }
            
            const app = new App();
            app.init();
        }
    }
}
```

### 3. JavaScript优化

优化器提供多种优化选项：

- **死代码删除**：移除永远不会执行的代码
- **常量内联**：将const变量直接替换为其值
- **调试代码移除**：移除console.log和debugger语句
- **表达式简化**：优化复杂表达式
- **变量名混淆**：压缩变量名以减小文件大小
- **循环优化**：优化循环结构

### 4. 模块系统支持

支持多种模块格式：

- **ES6 Modules**：原生import/export
- **CommonJS**：require/module.exports
- **AMD**：异步模块定义
- **模块打包**：将多个模块合并为单个文件
- **依赖分析**：自动分析模块依赖关系

### 5. 语法验证和错误检查

- **语法错误检测**：准确的错误位置和消息
- **未定义变量检查**：检测使用未声明的变量
- **未使用变量检查**：找出声明但未使用的变量
- **重复声明检查**：检测重复的变量声明
- **类型推断**：基本的类型检查（可选）

## API使用

### JSCompiler

```cpp
// 创建编译器
auto compiler = std::make_shared<JSCompiler>(context);

// 设置选项
compiler->setMinify(true);              // 压缩输出
compiler->setStrictMode(true);          // 添加'use strict'
compiler->setSourceMap(true);           // 生成source map
compiler->setModernize(true);           // ES5转ES6+

// 编译JavaScript
std::string compiledJS = compiler->compile(jsContent);

// 编译并获取详细分析
auto result = compiler->compileWithAnalysis(jsContent);
// result.code - 编译后的代码
// result.errors - 错误列表
// result.warnings - 警告列表
// result.imports - import语句
// result.exports - export语句
// result.symbols - 符号表

// 验证JavaScript
std::vector<std::string> errors;
bool isValid = compiler->validate(jsContent, errors);
```

### JSOptimizer

```cpp
// 创建优化器
JSOptimizer::Options options;
options.removeDeadCode = true;
options.inlineConstants = true;
options.removeConsoleLog = true;
options.removeDebugger = true;
options.mangleVariables = false;

JSOptimizer optimizer(options);

// 优化代码
std::string optimizedJS = optimizer.optimize(jsCode);

// 压缩代码
std::string minifiedJS = optimizer.minify(jsCode);
```

### JSModuleProcessor

```cpp
// 创建模块处理器
auto moduleProcessor = std::make_shared<JSModuleProcessor>(context);

// 解析模块
auto imports = moduleProcessor->parseImports(jsCode);
auto exports = moduleProcessor->parseExports(jsCode);

// 转换模块格式
std::string commonJS = moduleProcessor->convertToCommonJS(es6Module);
std::string amd = moduleProcessor->convertToAMD(es6Module);

// 打包模块
std::vector<std::string> entryPoints = {"main.js"};
std::string bundle = moduleProcessor->bundleModules(entryPoints);
```

### CHTLJSProcessor

```cpp
// 创建JS处理器
auto jsProcessor = std::make_shared<CHTLJSProcessor>(context);

// 添加全局脚本
jsProcessor->addGlobalScript(jsCode, "text/javascript");

// 添加局部脚本（自动作用域隔离）
jsProcessor->addLocalScript(jsCode, "component-scope");

// 添加模块
jsProcessor->addModule("utils", utilsModule);
jsProcessor->addModule("api", apiModule);

// 生成最终JavaScript
std::string finalJS = jsProcessor->generateFinalJS();

// 验证引用
jsProcessor->validateReferences();

// 生成source map
std::string sourceMap = jsProcessor->generateSourceMap();
```

## 与CHTL集成

### 在CHTLGenerator中使用

```cpp
// 处理全局脚本块
generator.processGlobalScriptBlock(jsContent);

// 获取JS处理器
auto jsProcessor = generator.getJSProcessor();

// 获取最终JavaScript
std::string js = generator.getJS();
```

### 局部脚本块 vs 全局脚本块

| 特性 | 局部脚本块 | 全局脚本块 |
|------|-----------|-----------|
| 位置 | 元素内部 | head/body内 |
| 语法 | CHTL JS增强语法 | 标准JavaScript |
| 作用域 | 自动隔离 | 全局 |
| 功能 | 增强选择器、动画等 | 完整JS功能 |

## 高级功能

### 1. 作用域分析

```javascript
// 编译器会追踪作用域链
function outer() {
    const x = 10;  // 函数作用域
    
    {
        let y = 20;  // 块级作用域
        const inner = () => {
            return x + y;  // 闭包访问
        };
    }
    
    // y在这里不可访问
}
```

### 2. 模块依赖图

```javascript
// main.js
import { utils } from './utils';
import api from './api';

// 编译器会构建依赖图：
// main.js -> utils.js
// main.js -> api.js
```

### 3. 自动Polyfill

```cpp
// 根据目标环境自动添加polyfill
std::vector<std::string> features = {"Promise", "fetch", "Array.from"};
std::string polyfills = JSRuntime::generatePolyfills(features);
```

### 4. 运行时代码

CHTL提供了内置的运行时函数：

```javascript
// CHTL运行时
CHTL.$ = function(selector) {
    return document.querySelector(selector);
};

CHTL.$$ = function(selector) {
    return document.querySelectorAll(selector);
};

CHTL.on = function(element, event, handler) {
    element.addEventListener(event, handler);
};

CHTL.ajax = function(options) {
    return fetch(options.url, options);
};
```

## 错误处理

JavaScript编译器提供详细的错误信息：

```
JavaScript Syntax Error at line 5:12 - mismatched input ')' expecting ':'
JavaScript Syntax Error at line 10:1 - missing ';' at '}'
Warning at line 15:5 - Unused variable: tempVar
Warning at line 20:10 - Undefined variable: unknownVar
```

## 性能优化

1. **增量编译**：只重新编译修改的模块
2. **并行处理**：多个模块并行编译
3. **缓存机制**：缓存编译结果
4. **懒加载**：按需加载模块

## 最佳实践

1. **模块化设计**：将代码分割为小模块
2. **使用严格模式**：始终启用'use strict'
3. **避免全局变量**：使用模块作用域
4. **异步优先**：使用async/await而不是回调
5. **错误处理**：正确处理Promise rejection

## 示例

### 完整示例

```chtl
html
{
    head
    {
        script
        {
            // ES6+模块
            import { Component } from './component.js';
            
            // 异步函数
            async function loadData() {
                try {
                    const response = await fetch('/api/data');
                    const data = await response.json();
                    return data;
                } catch (error) {
                    console.error('Failed to load data:', error);
                }
            }
            
            // 类定义
            class App extends Component {
                constructor() {
                    super();
                    this.data = null;
                }
                
                async init() {
                    this.data = await loadData();
                    this.render();
                }
                
                render() {
                    // 使用模板字符串
                    document.body.innerHTML = `
                        <div class="app">
                            <h1>${this.data?.title || 'Loading...'}</h1>
                        </div>
                    `;
                }
            }
            
            // 初始化应用
            document.addEventListener('DOMContentLoaded', () => {
                const app = new App();
                app.init();
            });
        }
    }
    
    body
    {
        div
        {
            id: app;
            
            // 局部CHTL JS脚本
            script
            {
                // 使用增强选择器
                const container = {{#app}};
                
                // 动画和事件
                {{button}}->listen({
                    click: function() {
                        animate({
                            duration: 300,
                            easing: ease-out,
                            begin: { opacity: 0, transform: scale(0.8) },
                            end: { opacity: 1, transform: scale(1) }
                        })(this);
                    }
                });
            }
        }
    }
}
```

这个例子展示了全局JavaScript和局部CHTL JS的结合使用，充分利用了两种脚本系统的优势。