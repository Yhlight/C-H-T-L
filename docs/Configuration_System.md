# CHTL配置驱动体系

## 概述

CHTL的配置驱动体系允许开发者通过配置文件自定义语言的关键字，而无需修改编译器源代码。这种设计使得CHTL可以适应不同的语言环境和编码习惯。

## 核心概念

### 1. 配置组（Configuration）

配置组是CHTL源文件中的特殊块，用于定义编译行为：

```chtl
[Configuration]
{
    // 配置项
}
```

### 2. 名称组（Name Group）

当`DISABLE_NAME_GROUP = false`时，可以在配置中定义Name组来自定义关键字：

```chtl
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        // 关键字定义
    }
}
```

## 配置项详解

### 核心配置项

| 配置项 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| `INDEX_INITIAL_COUNT` | int | 0 | 自动生成索引的起始值 |
| `DISABLE_NAME_GROUP` | bool | true | 是否禁用名称组（自定义关键字） |
| `DEBUG_MODE` | bool | false | 是否启用调试模式 |

### 名称组配置项

#### 样式相关
- `CUSTOM_STYLE` - 自定义样式关键字（支持数组）
- `CUSTOM_ELEMENT` - 自定义元素关键字
- `CUSTOM_VAR` - 自定义变量关键字
- `TEMPLATE_STYLE` - 模板样式关键字
- `TEMPLATE_ELEMENT` - 模板元素关键字
- `TEMPLATE_VAR` - 模板变量关键字

#### 原始嵌入
- `ORIGIN_HTML` - HTML原始嵌入关键字
- `ORIGIN_STYLE` - CSS原始嵌入关键字
- `ORIGIN_JAVASCRIPT` - JavaScript原始嵌入关键字

#### 导入
- `IMPORT_HTML` - HTML导入关键字
- `IMPORT_STYLE` - 样式导入关键字
- `IMPORT_JAVASCRIPT` - JavaScript导入关键字
- `IMPORT_CHTL` - CHTL模块导入关键字
- `IMPORT_CJMOD` - CJMOD扩展导入关键字

#### 操作关键字
- `KEYWORD_INHERIT` - 继承
- `KEYWORD_DELETE` - 删除
- `KEYWORD_INSERT` - 插入
- `KEYWORD_AFTER` - 之后
- `KEYWORD_BEFORE` - 之前
- `KEYWORD_REPLACE` - 替换
- `KEYWORD_ATTOP` - 顶部
- `KEYWORD_ATBOTTOM` - 底部
- `KEYWORD_FROM` - 来自
- `KEYWORD_AS` - 作为
- `KEYWORD_EXCEPT` - 除外

#### 节点关键字
- `KEYWORD_TEXT` - 文本节点
- `KEYWORD_STYLE` - 样式块
- `KEYWORD_SCRIPT` - 脚本块

#### 声明关键字
- `KEYWORD_CUSTOM` - 自定义声明
- `KEYWORD_TEMPLATE` - 模板声明
- `KEYWORD_ORIGIN` - 原始嵌入声明
- `KEYWORD_IMPORT` - 导入声明
- `KEYWORD_NAMESPACE` - 命名空间声明

#### 其他
- `OPTION_COUNT` - 组选项的最大数量（用于限制数组类型的关键字变体数）

## 使用示例

### 示例1：英文关键字（默认）

```chtl
// 使用默认英文关键字
[Template] @Style Card
{
    padding: 20px;
    border: 1px solid #ccc;
}

[Template] @Element Card
{
    div
    {
        style { @Style Card; }
        text { "This is a card" }
    }
}
```

### 示例2：中文关键字

```chtl
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        TEMPLATE_STYLE = @样式;
        TEMPLATE_ELEMENT = @组件;
        KEYWORD_TEMPLATE = [模板];
        KEYWORD_TEXT = 文本;
        KEYWORD_STYLE = 样式;
    }
}

// 使用中文关键字
[模板] @样式 卡片
{
    padding: 20px;
    border: 1px solid #ccc;
}

[模板] @组件 卡片
{
    div
    {
        样式 { @样式 卡片; }
        文本 { "这是一个卡片" }
    }
}
```

### 示例3：多语言支持

```chtl
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        // 支持多个关键字变体
        CUSTOM_STYLE = [@Style, @样式, @スタイル];
        KEYWORD_TEXT = [text, 文本, テキスト];
        OPTION_COUNT = 5;  // 允许最多5个变体
    }
}

// 可以混合使用不同语言的关键字
div
{
    @Style Card;     // 英文
    @样式 主题;      // 中文
    @スタイル ベース; // 日文
}
```

## 实现原理

### 1. 配置解析流程

1. **扫描阶段**：扫描源文件中的`[Configuration]`块
2. **解析阶段**：解析配置项和Name组
3. **验证阶段**：验证配置的有效性
4. **应用阶段**：将配置应用到Lexer和Parser

### 2. 动态关键字替换

当`DISABLE_NAME_GROUP = false`时：

1. **Lexer层**：`ConfigurableLexer`拦截Token生成，将配置的关键字映射到正确的Token类型
2. **Parser层**：`ConfigurableParser`提供便捷方法来匹配配置的关键字

### 3. 性能优化

- 使用哈希表存储关键字映射，O(1)查找
- 配置在编译开始时一次性加载
- 仅在启用Name组时才进行关键字替换

## 最佳实践

### 1. 关键字选择

- 选择清晰、不易混淆的关键字
- 避免使用常见的标识符作为关键字
- 保持关键字风格一致

### 2. 性能考虑

- 限制组选项数量（通过`OPTION_COUNT`）
- 避免过多的关键字变体
- 在生产环境考虑使用`DISABLE_NAME_GROUP = true`

### 3. 团队协作

- 在团队项目中统一配置
- 将配置文件纳入版本控制
- 文档化自定义关键字的含义

## 配置文件格式

除了内嵌配置，还可以使用独立的配置文件：

```chtl
// config.chtl
[Configuration]
{
    // 配置内容
}
```

然后在编译时指定：

```bash
chtlc source.chtl --config config.chtl
```

## 错误处理

### 常见错误

1. **关键字冲突**：多个关键字类型使用相同的值
2. **空关键字**：必需的关键字字段为空
3. **超出限制**：组选项数量超过`OPTION_COUNT`

### 错误示例

```chtl
[Configuration]
{
    DISABLE_NAME_GROUP = false;
    
    [Name]
    {
        CUSTOM_STYLE = [@Style, @Style];  // 错误：重复的关键字
        CUSTOM_ELEMENT = ;                // 错误：空关键字
        OPTION_COUNT = 3;
        TEMPLATE_STYLE = [@A, @B, @C, @D]; // 错误：超出限制
    }
}
```

## 扩展性

配置系统设计为可扩展的：

1. **添加新配置项**：在`ConfigurationSystem`中注册
2. **添加新关键字类型**：在`KeywordRegistry`中注册
3. **自定义验证规则**：扩展`NameGroup::validate()`

## 总结

CHTL的配置驱动体系提供了强大的灵活性，使得：

- 不同团队可以使用适合自己的关键字
- 支持国际化和本地化
- 无需修改编译器即可调整语言特性
- 保持与标准CHTL的兼容性

通过合理使用配置系统，可以让CHTL更好地适应各种开发场景和需求。