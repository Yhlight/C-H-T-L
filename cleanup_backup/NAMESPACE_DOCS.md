# CHTL命名空间文档

## 概述

CHTL命名空间系统提供了强大的模块隔离和组织功能，有效防止命名冲突和模块污染。主要特性包括：

- **命名空间隔离**：将定义组织在独立的命名空间中
- **嵌套支持**：支持多级嵌套命名空间
- **自动合并**：同名命名空间自动合并
- **冲突检测**：检测并报告命名冲突
- **文件默认命名空间**：无显式命名空间时使用文件名
- **from语法**：明确指定使用哪个命名空间的项目

## 基本语法

### 1. 定义命名空间

```chtl
// 简单命名空间
[Namespace] space

// 带花括号的命名空间
[Namespace] space
{
    // 命名空间内容
}
```

### 2. 嵌套命名空间

```chtl
// 单层嵌套（可省略花括号）
[Namespace] parent
[Namespace] child

// 多层或平级嵌套（需要花括号）
[Namespace] parent
{
    [Namespace] child1
    {
        // child1 内容
    }
    
    [Namespace] child2
    {
        // child2 内容
    }
}
```

### 3. 使用命名空间中的项目

```chtl
// 使用 from 语法
body
{
    @Element Box from space;
    @Style ButtonStyle from ui.components;
    @Var Colors from theme.dark;
}
```

## 命名空间示例

### 基本使用

```chtl
// 文件：components.chtl
[Namespace] ui

[Custom] @Element Button
{
    button
    {
        style
        {
            padding: 10px 20px;
            background: #007bff;
            color: white;
        }
        
        text { "Button" }
    }
}

// 文件：main.chtl
[Import] @Chtl from components

body
{
    // 使用ui命名空间中的Button
    @Element Button from ui;
}
```

### 嵌套命名空间

```chtl
[Namespace] app
{
    [Namespace] components
    {
        [Custom] @Element Header
        {
            header.app-header
            {
                h1 { text { "App Header" } }
            }
        }
    }
    
    [Namespace] layouts
    {
        [Template] @Element MainLayout
        {
            div.main-layout
            {
                @Element Header from app.components;
                
                main
                {
                    // 主要内容
                }
            }
        }
    }
}

// 使用嵌套命名空间
body
{
    @Element MainLayout from app.layouts;
}
```

### 文件默认命名空间

```chtl
// 文件：button.chtl
// 没有显式命名空间声明，默认使用文件名 "button" 作为命名空间

[Custom] @Element PrimaryButton
{
    button.btn-primary
    {
        // 按钮定义
    }
}

// 文件：main.chtl
[Import] @Chtl from button

body
{
    // 使用默认命名空间 "button"
    @Element PrimaryButton from button;
}
```

## 命名空间合并

同名命名空间会自动合并：

```chtl
// 第一部分定义
[Namespace] theme
{
    [Template] @Style TextStyle
    {
        font-size: 16px;
        line-height: 1.6;
    }
}

// 第二部分定义（合并到同一命名空间）
[Namespace] theme
{
    [Template] @Style ColorStyle
    {
        color: #333;
        background: #fff;
    }
}

// 使用合并后的命名空间
div
{
    style
    {
        @Style TextStyle from theme;
        @Style ColorStyle from theme;
    }
}
```

## 冲突处理

### 命名冲突检测

```chtl
[Namespace] widgets
{
    // 定义一个Box元素
    [Custom] @Element Box
    {
        div.widget-box { }
    }
    
    // 错误：同一命名空间中重复定义同类型的Box
    [Custom] @Element Box
    {
        div.another-box { }
    }
}
```

### 使用from语法解决冲突

```chtl
[Namespace] layout
{
    [Custom] @Element Header
    {
        header.layout-header { }
    }
}

[Namespace] components
{
    [Custom] @Element Header
    {
        div.component-header { }
    }
}

// 明确指定使用哪个Header
body
{
    @Element Header from layout;      // 使用layout的Header
    @Element Header from components;  // 使用components的Header
}
```

## C++实现

### 基本使用

```cpp
// 创建命名空间
generator.beginNamespace("ui");

// 在命名空间中注册项目
namespaceManager->registerItem("Button", 
                              NamespaceItemType::CUSTOM_ELEMENT, 
                              buttonDefinition);

// 结束命名空间
generator.endNamespace();

// 使用命名空间中的项目
generator.useCustomFromNamespace("Button", "ui");
```

### 嵌套命名空间

```cpp
// 创建嵌套命名空间
namespaceManager->beginNamespace("app");
namespaceManager->beginNamespace("components");

// 注册项目
namespaceManager->registerItem("Card", 
                              NamespaceItemType::TEMPLATE_ELEMENT,
                              cardTemplate);

// 结束命名空间
namespaceManager->endNamespace(); // 结束 components
namespaceManager->endNamespace(); // 结束 app

// 使用嵌套命名空间中的项目
generator.useTemplateFromNamespace("Card", "app.components");
```

### 命名空间解析

```cpp
// 创建解析器
NamespaceResolver resolver(*namespaceManager);

// 解析带命名空间的引用
auto ref = resolver.parseReference("Button from ui.components");
// ref.itemName = "Button"
// ref.namespacePath = "ui.components"
// ref.hasExplicitNamespace = true

// 查找项目
auto item = resolver.resolveItem("Button", 
                                NamespaceItemType::CUSTOM_ELEMENT,
                                "ui.components");
```

### 冲突检测

```cpp
// 检测命名空间中的冲突
auto conflicts = namespaceManager->detectConflicts("shared");
for (const auto& conflict : conflicts) {
    std::cerr << "Conflict: " << conflict << std::endl;
}

// 合并命名空间
std::vector<std::string> mergeConflicts;
bool success = namespaceManager->mergeNamespaces("target", "source");
```

## 最佳实践

### 1. 组织结构

```chtl
// 按功能组织命名空间
[Namespace] ui
{
    [Namespace] buttons { }
    [Namespace] forms { }
    [Namespace] modals { }
}

[Namespace] utils
{
    [Namespace] helpers { }
    [Namespace] validators { }
}
```

### 2. 命名约定

- 使用小写字母和下划线
- 避免使用保留名称
- 保持命名简洁明了

```chtl
// 好的命名
[Namespace] user_interface
[Namespace] data_models
[Namespace] app_components

// 避免
[Namespace] UI  // 使用小写
[Namespace] namespace  // 保留字
[Namespace] x  // 太短，不明确
```

### 3. 避免深层嵌套

```chtl
// 适度嵌套（推荐）
[Namespace] app
{
    [Namespace] components { }
    [Namespace] layouts { }
}

// 过度嵌套（避免）
[Namespace] app
{
    [Namespace] ui
    {
        [Namespace] components
        {
            [Namespace] buttons
            {
                [Namespace] primary { }
            }
        }
    }
}
```

### 4. 文档化命名空间

```chtl
// 为命名空间添加注释
// UI组件命名空间
[Namespace] ui_components
{
    // 按钮相关组件
    [Custom] @Element Button { }
    
    // 表单相关组件
    [Custom] @Element Form { }
}
```

## 高级特性

### 1. 条件命名空间

```cpp
// 根据条件创建命名空间
if (isDarkTheme) {
    generator.beginNamespace("dark_theme");
} else {
    generator.beginNamespace("light_theme");
}
```

### 2. 动态命名空间解析

```cpp
// 动态构建命名空间路径
std::vector<std::string> path = {"app", "modules", moduleName};
std::string fullPath = NamespaceHelper::joinPath(path);

// 使用动态路径
generator.useCustomFromNamespace(componentName, fullPath);
```

### 3. 命名空间别名

虽然CHTL不直接支持命名空间别名，但可以通过导入时的as语法实现类似效果：

```chtl
// 导入时重命名
[Import] [Custom] @Element Button from ui.components.buttons as UIButton

// 使用
body
{
    @Element UIButton;
}
```

## 错误处理

### 常见错误

1. **未找到命名空间**
```
Error: Namespace not found: ui.nonexistent
```

2. **命名冲突**
```
Error: Conflict in namespace 'widgets': Custom Element 'Box' already exists
```

3. **无效的命名空间名**
```
Error: Invalid namespace name: '123invalid'
```

### 调试技巧

```cpp
// 列出命名空间内容
auto ns = namespaceManager->findNamespace("ui");
if (ns) {
    auto items = ns->getAllItems();
    for (const auto& item : items) {
        std::cout << "Item: " << item.name 
                  << " Type: " << NamespaceHelper::itemTypeToString(item.type)
                  << std::endl;
    }
}

// 跟踪当前命名空间
auto current = namespaceManager->getCurrentNamespace();
std::cout << "Current namespace: " << current->getFullPath() << std::endl;
```

## 与其他系统的集成

### 与导入系统结合

```chtl
// components.chtl
[Namespace] shared_ui

[Custom] @Element Card { }

// main.chtl
[Import] @Chtl from components

// 使用导入文件中的命名空间
@Element Card from shared_ui;
```

### 与模板/自定义系统结合

命名空间为模板和自定义提供了额外的组织层：

```chtl
[Namespace] templates
{
    [Template] @Style BaseButton { }
    [Template] @Element Layout { }
}

[Namespace] customs
{
    [Custom] @Element SpecialButton
    {
        inherit @Style BaseButton from templates;
    }
}
```