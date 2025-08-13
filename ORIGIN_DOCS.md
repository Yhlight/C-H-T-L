# CHTL原始嵌入文档

## 概述

原始嵌入是CHTL的兼容性处理机制，允许在CHTL代码中直接嵌入原生的HTML、CSS或JavaScript代码，而不经过任何CHTL处理。这为处理CHTL暂不支持的特性或特殊需求提供了灵活的解决方案。

**核心特点**：
- **原原本本传递**：内容完全不经处理，直接输出
- **语法类型仅作标记**：`@Html`、`@Style`、`@JavaScript`只是语法标记，不影响内容处理
- **任意位置使用**：可以在任何CHTL节点中使用
- **支持命名复用**：增强原始嵌入支持命名和复用

## 基本语法

### 1. 嵌入HTML代码

```chtl
[Origin] @Html
{
    <div class="custom">
        <h1>原始HTML内容</h1>
        <p>这些内容不会被CHTL处理</p>
    </div>
}
```

### 2. 嵌入CSS代码

```chtl
[Origin] @Style
{
    /* 原始CSS */
    .special-effect {
        background: linear-gradient(45deg, red, blue);
        -webkit-transform: rotate(45deg);
        filter: blur(5px);
    }
}
```

### 3. 嵌入JavaScript代码

```chtl
[Origin] @JavaScript
{
    // 原始JavaScript
    const advancedFeature = () => {
        // 使用CHTL可能不支持的新特性
        const result = data?.nested?.value ?? 0;
        return result;
    };
}
```

## 增强原始嵌入（命名复用）

### 定义命名的原始嵌入

```chtl
[Origin] @Html box
{
    <div class="reusable-component">
        <header>组件头部</header>
        <main>组件内容</main>
        <footer>组件底部</footer>
    </div>
}
```

### 使用命名的原始嵌入

```chtl
body
{
    // 第一次使用
    [Origin] @Html box;
    
    // 第二次使用
    [Origin] @Html box;
}
```

## C++实现

### 基本使用

```cpp
// 创建原始嵌入
std::string declaration = "[Origin] @Html {";
std::string content = "<div>原始HTML内容</div>";

generator.processOriginBlock(declaration, content);
```

### 命名原始嵌入

```cpp
// 定义命名的原始嵌入
std::string namedDecl = "[Origin] @Style myStyles {";
std::string styles = ".custom { color: red; }";
generator.processOriginBlock(namedDecl, styles);

// 使用命名的原始嵌入
generator.useOriginBlock("myStyles");
```

### 原始嵌入管理器

```cpp
// 获取管理器
auto originManager = generator.getOriginManager();

// 注册原始嵌入
auto origin = std::make_shared<OriginDefinition>("header", "@Html", true);
origin->setContent("<header>站点头部</header>");
originManager->registerNamedOrigin("header", origin);

// 查找和使用
auto found = originManager->findNamedOrigin("header");
if (found) {
    found->generate(generator);
}
```

## 使用场景

### 1. 处理CHTL不支持的特性

```chtl
// 使用Web Components
[Origin] @Html
{
    <custom-element>
        <template slot="header">
            <h1>Shadow DOM内容</h1>
        </template>
    </custom-element>
}
```

### 2. 嵌入第三方代码

```chtl
// 嵌入第三方库的HTML结构
[Origin] @Html
{
    <div id="map" class="leaflet-container">
        <!-- Leaflet地图容器 -->
    </div>
}

// 嵌入第三方CSS
[Origin] @Style
{
    @import url('https://unpkg.com/leaflet@1.7.1/dist/leaflet.css');
}
```

### 3. 保留特定格式

```chtl
// 保留SVG的精确格式
[Origin] @Html
{
    <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 100">
        <path d="M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z"/>
    </svg>
}
```

### 4. 内联关键CSS

```chtl
[Origin] @Style
{
    /* 关键渲染路径CSS */
    body { margin: 0; padding: 0; }
    .above-fold { display: block; }
    @media (max-width: 768px) {
        .mobile-critical { display: flex; }
    }
}
```

## 混合使用

### CHTL与原始嵌入结合

```chtl
article
{
    h1
    {
        text { "CHTL生成的标题" }
    }
    
    // 嵌入复杂的HTML结构
    [Origin] @Html
    {
        <div class="chart-container">
            <canvas id="myChart"></canvas>
            <div class="chart-legend">
                <span class="legend-item" data-color="#ff0000">数据1</span>
                <span class="legend-item" data-color="#00ff00">数据2</span>
            </div>
        </div>
    }
    
    p
    {
        text { "CHTL生成的段落" }
    }
}
```

### 条件性原始嵌入

```cpp
// 根据条件决定是否使用原始嵌入
if (needsSpecialHandling) {
    generator.processOriginBlock(
        "[Origin] @Html {",
        specialHTMLContent
    );
} else {
    // 使用常规CHTL生成
    generator.generateElement("div", {{"class", "regular"}});
    // ...
}
```

## 最佳实践

### 1. 明确使用场景
- 仅在CHTL无法满足需求时使用原始嵌入
- 优先使用CHTL的原生功能
- 记录使用原始嵌入的原因

### 2. 保持一致性
- 统一原始嵌入的代码风格
- 使用有意义的命名
- 将相关的原始嵌入组织在一起

### 3. 安全考虑
- 验证原始内容的来源
- 避免直接嵌入用户输入
- 注意XSS等安全问题

### 4. 维护性
```chtl
// 好的做法：添加注释说明
[Origin] @JavaScript
{
    // 原始嵌入原因：需要使用最新的ES2022特性
    // 功能：处理异步迭代器
    async function* processData() {
        // ...
    }
}
```

## 注意事项

1. **无处理保证**：原始嵌入的内容完全绕过CHTL处理
2. **语法标记**：`@Html`、`@Style`、`@JavaScript`仅用于语法识别
3. **输出位置**：原始内容在当前位置直接输出
4. **缩进保留**：原始内容的缩进和格式完全保留
5. **不进行验证**：CHTL不验证原始内容的正确性

## 调试建议

```cpp
// 开发模式下记录原始嵌入的使用
if (isDevelopment) {
    std::cout << "使用原始嵌入: " << origin->getSyntaxType() 
              << " at " << getCurrentLocation() << std::endl;
}

// 添加标记注释
generator.generateComment("-- 开始原始嵌入: " + originType);
generator.processOriginBlock(declaration, content);
generator.generateComment("-- 结束原始嵌入 --");
```