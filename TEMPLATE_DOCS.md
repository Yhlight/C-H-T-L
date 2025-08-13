# CHTL模板系统文档

## 概述

CHTL模板系统提供了三种模板类型：
- **样式组模板** (`@Style`)：复用CSS样式集合
- **元素模板** (`@Element`)：复用HTML元素结构
- **变量组模板** (`@Var`)：定义可复用的变量值

模板系统还支持：
- **继承机制**：模板可以继承其他同类型模板
- **全缀名**：使用完整或部分限定名访问模板，解决命名冲突
- **状态管理**：Definition（定义）和Use（使用）两种状态

## 核心组件

### 1. 模板定义和使用状态

```cpp
enum class TemplateState {
    DEFINITION,  // 定义状态 - 可以创建新模板
    USE         // 使用状态 - 可以使用已定义的模板
};
```

### 2. 全缀名系统

支持三种命名方式：
- **简单名称**：`Box`
- **部分限定名**：`@Element Box`
- **完全限定名**：`[Template] @Element Box`

```cpp
QualifiedNameResolver resolver;
resolver.parse("[Template] @Style DefaultText");
// 结果：
// prefix = "Template"
// type = "@Style"  
// name = "DefaultText"
```

## 样式组模板

### 定义
```chtl
[Template] @Style DefaultText
{
    color: "black";
    line-height: 1.6;
    font-family: "Arial, sans-serif";
}
```

### 使用
```chtl
div
{
    style
    {
        @Style DefaultText;  // 应用所有样式
        font-size: 16px;     // 额外添加的样式
    }
}
```

### C++实现
```cpp
// 定义
auto style = std::make_shared<StyleTemplate>("DefaultText");
style->addStyle("color", "black");
style->addStyle("line-height", "1.6");
templateManager->registerStyleTemplate("DefaultText", style);

// 使用
templateManager->useStyleTemplate("DefaultText", generator);
```

## 元素模板

### 定义
```chtl
[Template] @Element Box
{
    div
    {
        style
        {
            width: 200px;
            height: 200px;
            background-color: red;
        }
    }
    
    span
    {
        text
        {
            "Box内容"
        }
    }
}
```

### 使用
```chtl
body
{
    @Element Box;  // 展开整个模板结构
}
```

### C++实现
```cpp
// 定义
auto element = std::make_shared<ElementTemplate>("Box");
// 添加元素节点...
templateManager->registerElementTemplate("Box", element);

// 使用
templateManager->useElementTemplate("Box", generator);
```

## 变量组模板

### 定义
```chtl
[Template] @Var ThemeColor
{
    primaryColor: "rgb(255, 192, 203)";
    secondaryColor: "rgba(253, 144, 162, 1)";
    textColor: "#333";
}
```

### 使用
```chtl
div
{
    style
    {
        color: ThemeColor(textColor);
        background-color: ThemeColor(primaryColor);
    }
}
```

### C++实现
```cpp
// 定义
auto vars = std::make_shared<VarTemplate>("ThemeColor");
vars->addVariable("primaryColor", "rgb(255, 192, 203)");
vars->addVariable("textColor", "#333");
templateManager->registerVarTemplate("ThemeColor", vars);

// 使用
std::string color = templateManager->useVarTemplate("ThemeColor", "textColor");
```

## 模板继承

### 组合式继承
```chtl
[Template] @Style ThemeColor
{
    color: rgba(255, 192, 203, 1);
    background-color: rgba(253, 144, 162, 1);
}

[Template] @Style ThemeColor2
{
    background-color: yellow;  // 覆盖父模板的值
    @Style ThemeColor;         // 继承ThemeColor的所有属性
}
```

### 显式继承
```chtl
[Template] @Style ThemeColor2
{
    background-color: yellow;
    inherit @Style ThemeColor;  // 使用inherit关键字
}
```

### C++实现
```cpp
auto child = std::make_shared<StyleTemplate>("ThemeColor2");
child->addStyle("background-color", "yellow");
child->inheritFrom("ThemeColor");  // 继承父模板

// 获取所有样式时会自动合并继承的属性
auto allStyles = child->getAllStyles(styleTemplates);
```

## 全缀名访问

### 解决命名冲突
```chtl
// 可以使用不同形式访问同一个模板
@Element Box;                    // 简单形式
[Template] @Element Box;         // 完全限定形式

// 当存在同名的Template和Custom时
[Template] @Element Box;         // 明确访问Template版本
[Custom] @Element Box;           // 明确访问Custom版本
```

### C++实现
```cpp
// 模板管理器自动注册多个别名
templateManager->registerStyleTemplate("DefaultText", style);
// 自动注册：
// - "DefaultText"
// - "@Style DefaultText"  
// - "[Template] @Style DefaultText"

// 查找时支持所有形式
auto found1 = templateManager->findStyleTemplate("DefaultText");
auto found2 = templateManager->findStyleTemplate("@Style DefaultText");
auto found3 = templateManager->findStyleTemplate("[Template] @Style DefaultText");
// found1 == found2 == found3
```

## 高级特性

### 1. 循环继承检测
```cpp
bool hasCircular = styleTemplate->hasCircularInheritance("TemplateName", templateMap);
```

### 2. 变量引用解析
```cpp
// 解析 "ThemeColor(primaryColor)" 格式
auto varRef = TemplateHelper::parseVarReference("ThemeColor(primaryColor)");
if (varRef.isValid) {
    std::string value = templateManager->useVarTemplate(varRef.templateName, varRef.varName);
}
```

### 3. 继承链解析
```cpp
// 获取完整的继承链
auto chain = processor.resolveInheritanceChain("ChildTemplate", templates);
// 返回: ["ChildTemplate", "ParentTemplate", "GrandParentTemplate"]
```

### 4. 属性合并策略
继承时，后定义的属性会覆盖先定义的：
```cpp
// Parent: { color: "red", size: "10px" }
// Child:  { color: "blue", weight: "bold" }
// 结果:   { color: "blue", size: "10px", weight: "bold" }
```

## 最佳实践

1. **命名规范**
   - 使用有意义的模板名：`PrimaryButton`、`CardLayout`
   - 变量组使用描述性名称：`ThemeColors`、`Spacing`

2. **组织结构**
   - 将相关模板分组定义
   - 基础模板在前，派生模板在后
   - 变量组模板集中定义

3. **继承使用**
   - 避免过深的继承层级（建议不超过3层）
   - 使用显式继承提高可读性
   - 定期检查循环继承

4. **全缀名使用**
   - 默认使用简单名称
   - 仅在命名冲突时使用全缀名
   - 在模块边界使用完全限定名

5. **性能优化**
   - 模板展开是在生成时进行的
   - 变量替换使用缓存机制
   - 继承链只在定义时解析一次