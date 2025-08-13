# CHTL自定义系统文档

## 概述

CHTL自定义系统是模板系统的扩展，提供了更高的灵活性和特例化操作能力：

- **无值样式组**：定义属性但不指定值，使用时填充
- **特例化操作**：删除、插入、替换特定内容
- **索引访问**：精确定位和修改元素
- **运行时覆盖**：动态改变变量值
- **模板互操作**：自定义和模板相互继承

## 核心特性

### 1. 无值样式组

定义样式属性但不提供值，使用时必须提供：

```chtl
[Custom] @Style TextSet
{
    color,           // 无值属性
    font-size;       // 需要使用时提供
}

// 使用时提供值
div
{
    style
    {
        @Style TextSet
        {
            color: red;
            font-size: 16px;
        }
    }
}
```

### C++实现
```cpp
// 定义无值样式组
auto custom = std::make_shared<CustomStyleGroup>("TextSet");
custom->addValuelessProperty("color");
custom->addValuelessProperty("font-size");

// 使用时提供值
std::unordered_map<std::string, std::string> values = {
    {"color", "red"},
    {"font-size", "16px"}
};
generator.useCustom("@Style TextSet", values);
```

### 2. 删除操作

#### 删除属性
```chtl
[Custom] @Style YellowText
{
    @Style WhiteText
    {
        delete line-height, border;  // 删除继承的属性
    }
    color: yellow;
}
```

#### 删除继承
```chtl
div
{
    style
    {
        @Style YellowText
        {
            delete @Style WhiteText;  // 删除整个继承
        }
    }
}
```

#### 删除元素
```chtl
@Element Box
{
    delete span;         // 删除所有span
    delete div[1];       // 删除第二个div
}
```

### C++实现
```cpp
// 删除属性
custom->addDeleteOperation({"line-height", "border"});

// 删除继承
custom->addDeleteInheritance("WhiteText");

// 删除元素
CustomElement::DeleteOperation deleteOp;
deleteOp.selectors.push_back(ElementSelector("span"));
deleteOp.selectors.push_back(ElementSelector("div", 1));
custom->addDeleteOperation(deleteOp);
```

### 3. 索引访问

精确访问特定位置的元素：

```chtl
[Custom] @Element Box
{
    div { }    // div[0]
    div { }    // div[1]
    span { }   // span[0]
}

body
{
    @Element Box
    {
        div[1]    // 访问第二个div
        {
            style
            {
                background: blue;
            }
        }
    }
}
```

### C++实现
```cpp
// 解析索引选择器
ElementSelector selector = ElementSelector::parse("div[1]");

// 获取特定元素
auto element = custom->getElementByIndex("div", 1);

// 匹配检查
bool matches = selector.matches("div", 1);  // true
```

### 4. 插入操作

在指定位置插入新内容：

```chtl
@Element Box
{
    insert after div[0] {
        div
        {
            text { "新插入的div" }
        }
    }
    
    insert before span {
        hr;
    }
    
    insert at top {
        h1 { text { "标题" } }
    }
    
    insert at bottom {
        footer { }
    }
    
    insert replace div[1] {
        section { }
    }
}
```

### 插入位置说明
- `before`：在目标元素之前
- `after`：在目标元素之后
- `replace`：替换目标元素
- `at top`：在最顶部
- `at bottom`：在最底部

### C++实现
```cpp
// 创建插入操作
CustomElement::InsertOperation insertOp;
insertOp.position = InsertPosition::AFTER;
insertOp.targetSelector = ElementSelector("div", 0);

// 创建要插入的元素
auto newDiv = std::make_shared<ElementTemplate::ElementNode>();
newDiv->name = "div";
newDiv->textContent = "新插入的内容";
insertOp.elementsToInsert.push_back(newDiv);

custom->addInsertOperation(insertOp);
```

### 5. 变量组特例化

运行时覆盖变量值：

```chtl
[Custom] @Var ThemeColor
{
    tableColor: "rgb(255, 192, 203)";
    textColor: "black";
}

// 使用时覆盖
div
{
    style
    {
        // 使用新值覆盖tableColor
        color: ThemeColor(tableColor = rgb(145, 155, 200));
    }
}
```

### C++实现
```cpp
// 定义可覆盖的变量
auto varGroup = std::make_shared<CustomVarGroup>("ThemeColor");
varGroup->addVariable("tableColor", "rgb(255, 192, 203)");
varGroup->markAsOverridable("tableColor");

// 使用时覆盖
std::string color = customManager->useCustomVar(
    "ThemeColor", 
    "tableColor", 
    "rgb(145, 155, 200)"  // 运行时值
);
```

### 6. 特例化链

多层特例化的组合：

```chtl
// 基础自定义
[Custom] @Element Card
{
    div.card
    {
        div.header { }
        div.body { }
        div.footer { }
    }
}

// 继承并特例化
[Custom] @Element SimpleCard
{
    @Element Card
    {
        delete div.footer;  // 删除footer
        
        div.header
        {
            style { font-weight: bold; }
        }
    }
}

// 使用时进一步特例化
body
{
    @Element SimpleCard
    {
        insert after div.header {
            hr;
        }
        
        div.body
        {
            style { padding: 20px; }
        }
    }
}
```

## 高级特性

### 1. 元素选择器系统

```cpp
// 基本选择器
ElementSelector("div");        // 匹配所有div
ElementSelector("div", 0);     // 匹配第一个div
ElementSelector("div", -1);    // 匹配所有div（显式）

// 解析字符串选择器
auto selector = ElementSelector::parse("span[2]");
```

### 2. 特例化操作合并

```cpp
// 合并多个特例化操作
auto merged = CustomHelper::mergeSpecializations(
    baseSpecializations,
    overrideSpecializations
);
```

### 3. 验证系统

```cpp
// 验证插入位置
bool valid = CustomHelper::isValidInsertPosition(
    InsertPosition::AFTER,
    ElementSelector("div", 0)
);

// 验证特例化语句
bool valid = SpecializationProcessor::validateSpecialization(spec);
```

### 4. 模板和自定义互操作

```cpp
// 从模板创建自定义
auto custom = interop.createCustomFromTemplate(
    "MyCustom",     // 新自定义名
    "MyTemplate"    // 源模板名
);

// 从自定义创建模板
auto template = interop.createTemplateFromCustom(
    "MyTemplate",   // 新模板名
    "MyCustom"      // 源自定义名
);

// 处理相互继承
interop.processInterInheritance("CustomA", "TemplateB");
```

## 最佳实践

### 1. 无值样式组使用
- 用于创建可复用的样式框架
- 明确标记哪些属性需要值
- 提供清晰的文档说明

### 2. 特例化操作
- 谨慎使用删除操作
- 保持特例化链的可追踪性
- 避免过度复杂的特例化

### 3. 索引访问
- 优先使用语义化的类名或ID
- 索引访问用于精确控制
- 注意元素顺序的变化

### 4. 插入操作
- 使用清晰的插入位置
- 考虑对现有布局的影响
- 测试不同场景下的插入结果

### 5. 变量特例化
- 明确标记可覆盖的变量
- 提供合理的默认值
- 验证运行时提供的值

## 性能考虑

1. **特例化解析**：在定义时完成，不影响运行时
2. **元素匹配**：使用索引缓存加速查找
3. **操作合并**：批量处理特例化操作
4. **延迟展开**：仅在使用时展开自定义内容

## 错误处理

```cpp
// 检查自定义是否存在
if (!customManager->findCustomStyle("MyStyle")) {
    // 处理错误
}

// 验证特例化操作
try {
    custom->applySpecialization(op);
} catch (const std::exception& e) {
    // 处理特例化错误
}

// 检查元素选择器有效性
if (!selector.matches(elementName, index)) {
    // 选择器不匹配
}
```