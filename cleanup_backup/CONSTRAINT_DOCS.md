# CHTL约束文档

## 概述

CHTL约束系统使用`except`关键字提供了强大的定义域限制功能，可以精确控制在特定作用域内允许使用的元素和对象类型。约束分为三个级别：

- **精确约束**：禁止特定的HTML元素或具体的自定义/模板对象
- **类型约束**：禁止整个类别的对象（如所有HTML元素、所有自定义、所有模板）
- **全局约束**：在命名空间级别应用的约束，影响整个命名空间

## 基本语法

### 1. 精确约束

禁止特定的元素或对象：

```chtl
div
{
    except span, [Custom] @Element Box;  // 禁止使用span元素和Box自定义元素
    
    // 这里不能使用span或Box
    p { text { "允许的段落" } }  // ✓ 允许
    span { }  // ✗ 错误：被约束禁止
}
```

### 2. 类型约束

禁止整个类别：

```chtl
section
{
    except @Html;  // 禁止所有HTML元素
    
    // 只能使用自定义元素或模板
    @Element CustomCard;  // ✓ 允许
    div { }  // ✗ 错误：HTML元素被禁止
}

main
{
    except [Template] @Var;  // 禁止使用变量组模板
    
    @Style ButtonStyle;  // ✓ 允许（样式模板）
    @Var ThemeColors;   // ✗ 错误：变量组模板被禁止
}

article
{
    except [Custom];  // 禁止所有自定义类型
    
    h1 { }  // ✓ 允许（HTML元素）
    @Element CustomHeader;  // ✗ 错误：自定义被禁止
}
```

### 3. 全局约束

在命名空间级别应用约束：

```chtl
[Namespace] restricted
{
    except [Template];  // 在此命名空间中禁止定义模板
    
    [Custom] @Element MyElement { }  // ✓ 允许
    [Template] @Style MyStyle { }    // ✗ 错误：模板被全局禁止
}
```

## 约束类型详解

### 精确约束目标

1. **HTML元素**
```chtl
except div, span, p;  // 禁止特定的HTML元素
```

2. **自定义对象**
```chtl
except [Custom] @Element Card;     // 禁止Card自定义元素
except [Custom] @Style TextStyle;  // 禁止TextStyle自定义样式组
except [Custom] @Var Colors;       // 禁止Colors自定义变量组
```

3. **模板对象**
```chtl
except [Template] @Element Layout;    // 禁止Layout元素模板
except [Template] @Style ButtonStyle; // 禁止ButtonStyle样式模板
except [Template] @Var ThemeVars;     // 禁止ThemeVars变量组模板
```

### 类型约束目标

1. **@Html** - 所有HTML元素
2. **[Custom]** - 所有自定义类型
3. **[Template]** - 所有模板类型
4. **[Template] @Var** - 特定类型的模板
5. **[Template] @Style** - 样式组模板
6. **[Template] @Element** - 元素模板

## 约束继承

子元素会继承父元素的约束：

```chtl
outer
{
    except span;  // outer中禁止span
    
    inner
    {
        except div;  // inner中禁止div，同时继承了禁止span
        
        // 这里既不能用span也不能用div
        p { text { "允许的内容" } }
    }
}
```

## C++实现

### 添加元素约束

```cpp
// 为特定元素路径添加约束
generator.addElementConstraint("div", "except span, [Custom] @Element Box;");
generator.addElementConstraint("form/fieldset", "except table;");
```

### 添加命名空间约束

```cpp
// 为命名空间添加全局约束
generator.addNamespaceConstraint("ui", "except [Template];");
```

### 处理except语句

```cpp
// 在当前作用域处理except语句
generator.processExceptStatement("except @Html, [Custom] @Style;");
```

### 约束检查

```cpp
// 检查是否可以使用某个元素或类型
if (generator.checkConstraint("span")) {
    // 可以使用span
}

// 使用约束检查器
ConstraintChecker checker(*constraintManager);
checker.setCurrentElement("div");

if (checker.canUseHtmlElement("p")) {
    generator.generateElement("p", {});
}

if (checker.canUseCustom("@Element", "Card")) {
    generator.useCustom("@Element Card");
}
```

## 高级用法

### 1. 组合约束

同时禁止多种类型：

```chtl
container
{
    except span, div, [Custom] @Element Card, [Template] @Style;
    
    // 这里禁止了：
    // - span和div HTML元素
    // - Card自定义元素
    // - 所有样式组模板
}
```

### 2. 条件约束

根据条件动态添加约束：

```cpp
if (isStrictMode) {
    generator.addElementConstraint("body", "except script, style;");
}
```

### 3. 约束验证

在生成前验证约束：

```cpp
ConstraintChecker checker(*constraintManager);
checker.setCurrentElement(currentPath);

// 获取详细的约束错误信息
ConstraintTarget target(ConstraintTargetType::HTML_ELEMENT, "iframe");
std::string error = checker.getConstraintError(target);
if (!error.empty()) {
    std::cerr << "约束错误: " << error << std::endl;
}
```

## 最佳实践

### 1. 语义化约束

使用约束来表达语义限制：

```chtl
nav
{
    except section, article, main;  // 导航中不应包含主要内容区域
    
    ul { /* 导航链接 */ }
}

table
{
    except table;  // 防止表格嵌套
}
```

### 2. 安全约束

使用约束增强安全性：

```chtl
[Namespace] user_content
{
    except script, iframe, object, embed;  // 禁止潜在危险的元素
}
```

### 3. 模块化约束

为不同模块定义不同的约束策略：

```chtl
[Namespace] components
{
    // 组件命名空间只允许定义自定义，不允许模板
    except [Template];
}

[Namespace] templates
{
    // 模板命名空间只允许定义模板，不允许自定义
    except [Custom];
}
```

## 错误处理

### 常见错误

1. **约束违反**
```
Error: Constraint violation: Constraint in element 'div' prohibits use of HTML element 'span'
```

2. **全局约束违反**
```
Error: Constraint violation: Global constraint in namespace 'restricted' prohibits use of any templates ([Template])
```

3. **继承的约束违反**
```
Error: Constraint violation: Inherited constraint prohibits use of Custom Element 'Box'
```

### 调试技巧

```cpp
// 获取当前作用域的所有约束
auto constraints = constraintManager->getCurrentConstraints();
for (const auto& rule : constraints) {
    std::cout << "约束类型: " << ConstraintHelper::constraintTypeToString(rule->getType()) << std::endl;
    std::cout << "作用域: " << rule->getScope() << std::endl;
    
    for (const auto& target : rule->getTargets()) {
        std::cout << "  禁止: " << target.fullName << std::endl;
    }
}

// 检查特定路径的约束
auto violations = constraintManager->getViolations(target, "div/section");
for (const auto& violation : violations) {
    std::cout << violation << std::endl;
}
```

## 与其他系统的交互

### 与命名空间结合

```chtl
[Namespace] secure
{
    except script, [Custom] @Element DangerousWidget;
    
    [Custom] @Element SafeWidget
    {
        // 在安全命名空间中定义的组件
    }
}
```

### 与模板/自定义结合

约束会影响模板和自定义的使用：

```chtl
[Template] @Element RestrictedLayout
{
    div
    {
        except iframe, object;  // 模板内部的约束
        
        // 使用此模板的地方也会继承这些约束
    }
}
```

## 性能考虑

1. **约束检查时机**：约束在元素创建时检查，不影响已创建的元素
2. **继承优化**：约束继承通过栈机制实现，性能开销小
3. **缓存策略**：路径规范化结果会被缓存以提高性能

## 注意事项

1. **约束不可撤销**：一旦添加约束，在该作用域内无法移除
2. **约束累加**：子作用域会累加父作用域的约束，不会覆盖
3. **类型优先级**：类型约束（如`@Html`）会覆盖该类型的所有精确约束
4. **命名空间约束**：全局约束影响整个命名空间，包括所有子命名空间