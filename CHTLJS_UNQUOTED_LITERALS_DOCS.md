# CHTL JS 无修饰字面量文档

## 概述

CHTL JS 支持无修饰字面量（Unquoted Literals），允许在特定上下文中省略引号，使代码更简洁、更接近CSS的书写习惯。这个特性通过状态机和上下文管理实现智能的字面量处理。

## 核心特性

### 1. 支持的上下文

无修饰字面量可以在以下上下文中使用：

- **对象属性值**：对象字面量中的属性值
- **样式属性值**：CSS样式相关的值
- **动画配置**：animate函数的配置对象
- **事件配置**：listen和delegate的配置对象

### 2. 有效的无修饰值

以下类型的值可以作为无修饰字面量：

- **颜色名称**：`red`, `blue`, `white`, `black` 等
- **CSS单位值**：`100px`, `2em`, `50%`, `10rem`
- **CSS关键字**：`bold`, `italic`, `center`, `flex`
- **标识符**：`myVariable`, `configName`
- **布尔值**：`true`, `false`
- **数字**：`100`, `3.14`
- **null和undefined**：`null`, `undefined`

### 3. 验证规则

无修饰字面量必须满足以下规则：

1. 不能以数字开头（除非是纯数字）
2. 只能包含字母、数字、下划线、连字符
3. 不能是JavaScript保留字（在非预期上下文中）
4. 不能包含空格或特殊字符

## 使用示例

### 基本用法

```chtl
script
{
    // 对象字面量中的无修饰值
    const config = {
        color: red,              // 等同于 'red'
        fontSize: 16px,          // 等同于 '16px'
        display: flex,           // 等同于 'flex'
        isActive: true,          // 布尔值不需要引号
        count: 42                // 数字不需要引号
    };
}
```

### 动画配置

```chtl
script
{
    const slideIn = animate({
        duration: 1000,          // 数字
        easing: ease-in-out,     // 缓动函数名
        
        begin: {
            opacity: 0,
            transform: translateX(-100px)  // CSS函数
        },
        
        end: {
            opacity: 1,
            transform: translateX(0)
        },
        
        direction: alternate,    // 动画方向
        loop: infinite          // 特殊值
    });
}
```

### 样式对象

```chtl
script
{
    const styles = {
        // 颜色
        color: darkblue,
        backgroundColor: lightgray,
        borderColor: transparent,
        
        // 字体
        fontFamily: Arial,
        fontSize: 14px,
        fontWeight: bold,
        fontStyle: italic,
        
        // 布局
        display: flex,
        position: relative,
        flexDirection: column,
        alignItems: center,
        
        // 尺寸
        width: 100%,
        height: auto,
        padding: 10px,
        margin: 0
    };
    
    {{#myElement}}->style = styles;
}
```

### 事件配置

```chtl
script
{
    {{button}}->listen({
        // 事件处理器
        click: handleClick,      // 函数引用
        mouseenter: onHover,
        mouseleave: onLeave,
        
        // 选项
        capture: false,          // 布尔值
        once: true,
        passive: true
    });
}
```

## 状态机支持

CHTL JS 使用状态机来追踪当前上下文，确定何时允许无修饰字面量：

### 状态转换

```
Default -> InScript -> InObjectLiteral -> InObjectProperty -> InObjectValue
                   |
                   -> InAnimateCall -> InObjectLiteral
                   |
                   -> InListenCall -> InObjectLiteral
```

### 上下文检测

状态机会自动检测以下情况：

1. 当前是否在对象字面量内
2. 当前属性名是什么
3. 该属性是否允许无修饰值
4. 值的类型和有效性

## 自动处理

### 1. 智能引号添加

系统会自动为无修饰字面量添加合适的引号：

```javascript
// 输入
color: red

// 输出
color: 'red'
```

### 2. 特殊值保留

某些值不需要引号，系统会保持原样：

```javascript
// 输入
isActive: true
count: 42

// 输出（保持不变）
isActive: true
count: 42
```

### 3. 无效值处理

对于无效的无修饰字面量，系统会：

1. 发出警告
2. 自动添加引号（如果启用了autoQuoteUnquoted）
3. 记录转换映射

## 配置选项

```cpp
// 启用/禁用无修饰字面量
jsContext->setAllowUnquotedLiterals(true);

// 自动为无效值添加引号
jsContext->setAutoQuoteUnquoted(true);

// 启用验证
jsContext->setValidateUnquoted(true);
```

## 最佳实践

### 1. 合理使用

无修饰字面量适合用于：
- CSS属性值
- 配置对象
- 简单标识符

不适合用于：
- 包含空格的字符串
- 特殊字符
- 动态生成的值

### 2. 保持一致性

在同一个项目中保持一致的风格：

```chtl
// 好的做法 - 一致的风格
const styles = {
    color: red,
    backgroundColor: blue,
    fontSize: 16px
};

// 避免混用
const styles = {
    color: red,
    backgroundColor: 'blue',  // 混用引号
    fontSize: 16px
};
```

### 3. 复杂值使用引号

对于复杂的CSS值，仍然使用引号：

```chtl
const styles = {
    // 简单值 - 无需引号
    color: red,
    display: flex,
    
    // 复杂值 - 需要引号
    border: "1px solid black",
    boxShadow: "0 2px 4px rgba(0,0,0,0.1)",
    fontFamily: "'Helvetica Neue', Arial, sans-serif"
};
```

## 错误处理

### 常见错误

1. **以数字开头**
   ```javascript
   // 错误
   className: 123abc  // 无效
   
   // 正确
   className: "123abc"
   ```

2. **包含空格**
   ```javascript
   // 错误
   title: Hello World  // 无效
   
   // 正确
   title: "Hello World"
   ```

3. **保留字冲突**
   ```javascript
   // 在某些上下文中可能有问题
   type: function  // 保留字
   
   // 更安全
   type: "function"
   ```

## 调试

### 查看转换结果

```cpp
// 转储所有无修饰字面量的转换
jsContext->dumpUnquotedLiterals();
```

### 验证特定值

```cpp
bool isValid = jsContext->validateUnquotedLiteral("myValue");
std::string processed = jsContext->processUnquotedLiteral("myValue");
```

## 与其他特性的集成

无修饰字面量与其他CHTL JS特性无缝集成：

### 增强选择器

```chtl
script
{
    {{.box}}->style = {
        backgroundColor: lightblue,
        padding: 20px
    };
}
```

### 箭头语法

```chtl
script
{
    {{#button}}->addEventListener(click, () => {
        this->style->color = red;
    });
}
```

### CJMOD扩展

CJMOD扩展可以定义自己的无修饰字面量规则和验证逻辑。

## 总结

无修饰字面量使CHTL JS代码更加简洁和易读，特别是在处理CSS相关的配置时。通过智能的上下文感知和自动处理，开发者可以享受类似CSS的书写体验，同时保持JavaScript的强大功能。