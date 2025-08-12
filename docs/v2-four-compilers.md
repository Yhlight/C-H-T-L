# CHTL 四个独立编译器架构

## 编译器职责分离

### 1. CHTL 编译器
**职责**：只处理 CHTL 语法
- 元素：`div`, `span`, `p` 等
- 属性：`#id`, `.class`, `data-*="value"`
- 块结构：`style { }`, `script { }`, `text { }`
- 声明：`[Template]`, `[Custom]`, `[Import]`
- 引用：`@Element`, `@Style`, `@Var`

**不处理**：
- CSS 语法细节
- JavaScript 语法
- CHTL-JS 扩展语法

### 2. CSS 编译器（静态分析器）
**职责**：只处理标准 CSS
- 选择器：`.class`, `#id`, `element`
- 属性：`color: red`, `margin: 10px`
- @规则：`@media`, `@import`, `@keyframes`
- 伪类/伪元素：`:hover`, `::before`

**不处理**：
- CHTL 的 `style { }` 块结构
- CHTL 变量引用 `@Var`
- 任何 CHTL 特有语法

### 3. JS 编译器（静态分析器）
**职责**：只处理标准 JavaScript
- ES6+ 语法
- 函数、类、变量声明
- import/export 语句
- 表达式和语句

**不处理**：
- CHTL 的 `script { }` 块结构
- CHTL-JS 的 `{{}}` 语法
- CHTL 特有的选择器语法

### 4. CHTL-JS 编译器
**职责**：只处理 CHTL-JS 扩展
- `{{#id}}` - 元素选择
- `{{&}}` - 当前元素引用
- `{{expression}}` - 表达式插值
- 扩展的事件绑定语法

**不处理**：
- 标准 JavaScript（交给 JS 编译器）
- CHTL 结构语法
- CSS 语法

## 工作流程

```
CHTL 源文件
    ↓
CHTL 编译器（解析结构）
    ↓
提取内容块
    ├─ CSS 内容 → CSS 编译器
    ├─ JS 内容 → JS 编译器
    └─ CHTL-JS 内容 → CHTL-JS 编译器
    ↓
各编译器独立分析
    ↓
返回分析结果
    ↓
CHTL 生成器（整合结果）
```

## 示例：各编译器的独立工作

### CHTL 文件
```chtl
[Template] @Element Card(title) {
    div .card {
        style {
            background: #fff;
            border: 1px solid #ddd;
        }
        
        h3 { text { title } }
        
        script {
            const element = {{&}};
            element.listen('click', () => {
                console.log('Clicked');
            });
        }
    }
}
```

### 各编译器处理

**1. CHTL 编译器看到的**：
```
- Template 声明: Card(title)
- 元素: div.card
- style 块（内容传递给 CSS 编译器）
- h3 元素
- text 块（包含参数引用 title）
- script 块（内容传递给 CHTL-JS 编译器）
```

**2. CSS 编译器收到的**：
```css
background: #fff;
border: 1px solid #ddd;
```
CSS 编译器只分析这段标准 CSS，不知道它来自 CHTL。

**3. CHTL-JS 编译器收到的**：
```javascript
const element = {{&}};
element.listen('click', () => {
    console.log('Clicked');
});
```
CHTL-JS 编译器处理 `{{&}}` 和 `listen` 扩展，将标准 JS 部分传递给 JS 编译器。

**4. JS 编译器收到的**：
```javascript
const element = [某个值];
element.listen('click', () => {
    console.log('Clicked');
});
```
JS 编译器只验证标准 JavaScript 语法。

## 接口设计

```cpp
// CHTL 编译器
class ChtlCompiler {
    void compile(const std::string& chtl) {
        // 解析 CHTL 结构
        // 提取 CSS/JS 内容块
        
        // 调用其他编译器
        cssResult = cssAnalyzer.analyze(cssContent);
        jsResult = jsAnalyzer.analyze(jsContent);
        chtlJsResult = chtlJsCompiler.compile(chtlJsContent);
    }
};

// 各编译器完全独立
class NativeCssAnalyzer {
    CssAnalysisResult analyze(const std::string& css);
    // 只处理标准 CSS
};

class NativeJsAnalyzer {
    JsAnalysisResult analyze(const std::string& js);
    // 只处理标准 JavaScript
};

class ChtlJsCompiler {
    ChtlJsResult compile(const std::string& chtlJs);
    // 只处理 CHTL-JS 扩展
};
```

## 优势

1. **关注点分离**：每个编译器专注于自己的语言
2. **可维护性**：修改一个编译器不影响其他
3. **可测试性**：可以独立测试每个编译器
4. **可扩展性**：容易添加新的编译器或功能
5. **性能**：可以并行运行多个编译器