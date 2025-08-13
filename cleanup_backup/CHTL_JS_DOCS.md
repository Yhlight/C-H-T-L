# CHTL JS文档 - 局部Script与增强选择器

## 概述

CHTL JS是CHTL的扩展语法，提供了局部script块和增强选择器功能。重要的是要理解：

- **CHTL JS不是JavaScript的超集**，它是一个独立的语法扩展
- **JS编译器**处理标准JavaScript代码
- **CHTL JS编译器**处理CHTL特有的扩展语法
- 两者通过扫描器精准切割，可以在同一个script块中混合使用

## 局部Script

局部script允许在元素内部编写JavaScript代码，这些代码会被自动隔离在不会造成全局污染的作用域中。

### 基本语法

```chtl
div
{
    style
    {
        .box
        {
            width: 100px;
            height: 100px;
            background-color: red;
        }
    }

    script
    {
        {{.box}}.addEventListener('click', () => {
            console.log('Box clicked!');
        });
    }
}
```

### 特点

1. **作用域隔离**：每个局部script都在独立的作用域中执行
2. **自动作用域绑定**：增强选择器自动限定在当前元素范围内
3. **高优先级**：局部script会被添加到高优先级的全局script块中
4. **混合语法支持**：可以同时使用JS和CHTL JS语法

## 增强选择器

增强选择器使用`{{选择器}}`语法，提供了更直观的DOM元素选择方式。

### 选择器类型

#### 1. 标签选择器
```chtl
script
{
    {{button}}  // 选择所有button元素
    {{div}}     // 选择所有div元素
}
```

#### 2. 类选择器
```chtl
script
{
    {{.box}}        // 选择所有class="box"的元素
    {{.container}}  // 选择所有class="container"的元素
}
```

#### 3. ID选择器
```chtl
script
{
    {{#myButton}}   // 选择id="myButton"的元素
    {{#submitForm}} // 选择id="submitForm"的元素
}
```

#### 4. 自动推断选择器
```chtl
script
{
    {{box}}  // 自动推断：先找id="box"，然后class="box"，最后标签名box
}
```

推断顺序：
1. ID选择器 (`#box`)
2. 类选择器 (`.box`)
3. 标签选择器 (`box`)

#### 5. 后代选择器
```chtl
script
{
    {{.box button}}      // 选择.box内的所有button
    {{#nav a}}          // 选择#nav内的所有a标签
    {{.container .item}} // 选择.container内的所有.item
}
```

#### 6. 索引选择器
```chtl
script
{
    {{button[0]}}    // 第一个button元素
    {{.item[2]}}     // 第三个class="item"的元素
    {{li[4]}}        // 第五个li元素
}
```

### 选择器转换

增强选择器会被转换为标准的JavaScript代码：

| CHTL JS语法 | 转换后的JavaScript |
|------------|------------------|
| `{{#myId}}` | `chtl_queryOne('#myId', scope)` |
| `{{.myClass}}` | `chtl_query('.myClass', scope)` |
| `{{button}}` | `chtl_query('button', scope)` |
| `{{box}}` | `(chtl_queryOne('#box', scope) \|\| chtl_queryOne('.box', scope) \|\| chtl_queryOne('box', scope))` |
| `{{.nav a}}` | `chtl_query('.nav a', scope)` |
| `{{li[2]}}` | `chtl_query('li', scope)[2]` |

## 作用域管理

### data-chtl-scope属性

当元素包含局部script时，会自动添加`data-chtl-scope`属性：

```html
<div data-chtl-scope="chtl_scope_1">
    <!-- 元素内容 -->
</div>
```

### 作用域隔离

每个局部script都在独立的IIFE（立即执行函数）中执行：

```javascript
(function() {
    const __scope = 'chtl_scope_1';
    // 局部script代码
})();
```

## C++实现

### 处理局部script

```cpp
// 开始script块
generator.beginScriptBlock();

// 添加script内容
generator.addScriptContent(R"(
    {{.myClass}}.addEventListener('click', function() {
        console.log('Clicked!');
    });
)");

// 结束script块
generator.endScriptBlock();
```

### 脚本管理器

```cpp
// 获取脚本管理器
auto scriptManager = generator.getScriptManager();

// 添加局部脚本
scriptManager->addLocalScript(elementPath, scriptBlock);

// 生成最终的JavaScript
std::string js = scriptManager->generateJavaScript();
```

## 最佳实践

### 1. 使用具体的选择器

优先使用明确的选择器类型：

```chtl
// 推荐
{{#submitBtn}}    // 明确的ID选择器
{{.item}}         // 明确的类选择器

// 避免（除非必要）
{{submitBtn}}     // 需要自动推断
```

### 2. 合理使用索引选择器

```chtl
script
{
    // 给第一个和最后一个元素特殊样式
    const items = {{.item}};
    {{.item[0]}}.classList.add('first');
    items[items.length - 1].classList.add('last');
}
```

### 3. 局部script的事件委托

```chtl
div
{
    class: list-container;
    
    script
    {
        // 使用事件委托处理动态元素
        {{.list-container}}.addEventListener('click', function(e) {
            if (e.target.matches('.item')) {
                console.log('Item clicked:', e.target);
            }
        });
    }
}
```

### 4. 避免全局污染

```chtl
script
{
    // 局部变量，不会污染全局
    const config = {
        apiUrl: '/api/data',
        timeout: 5000
    };
    
    // 使用增强选择器，自动限定作用域
    {{.btn-load}}.addEventListener('click', async () => {
        const data = await fetch(config.apiUrl).then(r => r.json());
        {{.result}}.textContent = JSON.stringify(data);
    });
}
```

## 高级用法

### 1. 混合选择器使用

```chtl
div
{
    class: dashboard;
    
    script
    {
        // 组合多种选择器
        const dashboard = {{.dashboard}};
        const buttons = {{button}};
        const primaryBtn = {{#primary}};
        const navLinks = {{.nav a}};
        
        // 统一处理
        buttons.forEach(btn => {
            btn.classList.add('styled-button');
        });
    }
}
```

### 2. 动态元素处理

```chtl
script
{
    // 创建元素并添加到DOM
    const newItem = document.createElement('div');
    newItem.className = 'dynamic-item';
    {{.container}}.appendChild(newItem);
    
    // 立即可以使用增强选择器访问
    {{.dynamic-item}}.textContent = 'Dynamically created!';
}
```

### 3. 异步操作

```chtl
script
{
    // 异步加载数据
    async function loadData() {
        {{.loader}}.style.display = 'block';
        
        try {
            const response = await fetch('/api/items');
            const items = await response.json();
            
            items.forEach((item, index) => {
                const el = document.createElement('div');
                el.className = 'item';
                el.textContent = item.name;
                {{.item-list}}.appendChild(el);
            });
            
            // 使用索引选择器高亮第一个
            {{.item[0]}}.classList.add('highlight');
        } finally {
            {{.loader}}.style.display = 'none';
        }
    }
    
    {{#loadBtn}}.addEventListener('click', loadData);
}
```

## 性能考虑

1. **选择器缓存**：对于频繁使用的元素，缓存选择结果
2. **事件委托**：对于大量相似元素，使用事件委托而非独立绑定
3. **作用域查询**：增强选择器自动限定在作用域内，提高查询效率

## 限制和注意事项

1. **不支持复杂CSS选择器**：为了性能考虑，不支持如`.box.active`这样的交集选择器
2. **后代选择器限制**：只支持简单的后代关系，不支持`>`、`+`、`~`等组合器
3. **作用域边界**：局部script只能访问当前作用域及其子元素

## 调试技巧

### 查看生成的JavaScript

```cpp
// 获取转换后的JavaScript代码
std::string js = generator.getJS();
std::cout << js << std::endl;
```

### 作用域调试

生成的JavaScript包含作用域映射信息：

```javascript
const CHTL_SCOPES = {
    'chtl_scope_1': 'div/container',
    'chtl_scope_2': 'form',
    // ...
};
```

这有助于理解每个作用域对应的元素路径。