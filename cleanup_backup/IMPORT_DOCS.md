# CHTL导入系统文档

## 概述

CHTL导入系统提供了强大的模块化支持，允许导入各种类型的文件和资源：

- **原生文件导入**：HTML、CSS、JavaScript文件
- **CHTL模块导入**：CHTL文件及其定义的组件
- **CJMOD模块导入**：编译后的CHTL模块
- **选择性导入**：从CHTL文件中导入特定的自定义或模板
- **别名支持**：使用`as`子句为导入指定别名
- **智能路径搜索**：自动在多个位置查找文件
- **循环依赖检测**：防止导入循环
- **重复导入保护**：同一文件只导入一次

## 导入语法

### 1. 导入HTML文件

```chtl
// 不带as子句 - 直接跳过
[Import] @Html from index.html

// 带as子句 - 创建命名的原始嵌入
[Import] @Html from header.html as siteHeader

// 使用导入的HTML
body
{
    [Origin] @Html siteHeader;
}
```

### 2. 导入CSS文件

```chtl
// 带as子句才会创建原始嵌入
[Import] @Style from styles.css as mainStyles

// 使用导入的样式
head
{
    style
    {
        [Origin] @Style mainStyles;
    }
}
```

### 3. 导入JavaScript文件

```chtl
// 带as子句才会创建原始嵌入
[Import] @JavaScript from utils.js as utilsScript

// 使用导入的脚本
script
{
    [Origin] @JavaScript utilsScript;
}
```

### 4. 导入自定义元素

```chtl
// 从CHTL文件导入特定的自定义元素
[Import] [Custom] @Element Card from components.chtl
[Import] [Custom] @Element Card from components.chtl as ProductCard

// 使用导入的自定义元素
body
{
    @Element Card;
    @Element ProductCard;
}
```

### 5. 导入模板

```chtl
// 导入样式组模板
[Import] [Template] @Style ButtonStyle from ui.chtl

// 导入元素模板
[Import] [Template] @Element Header from layout.chtl

// 导入变量组模板
[Import] [Template] @Var ThemeColors from theme.chtl
```

### 6. 导入整个CHTL文件

```chtl
// 导入文件中的所有定义
[Import] @Chtl from components

// 从特定路径导入
[Import] @Chtl from ./lib/ui-kit.chtl
```

### 7. 导入CJMOD文件

```chtl
// 导入编译后的模块
[Import] @CJmod from ui-framework

// 带具体路径
[Import] @CJmod from ./dist/components.cjmod
```

## 路径搜索规则

### HTML、CSS、JavaScript文件
- 只在当前目录搜索（不递归）
- 支持省略扩展名（自动补全）
- 支持点号路径转换（`.` → `/`）

### CHTL文件搜索顺序
1. 官方模块目录（如果配置）
2. 当前目录的`module`文件夹
3. 当前目录
4. 优先级：`.cmod` > `.chtl`

### CJMOD文件搜索顺序
1. 官方模块目录
2. 当前目录的`module`文件夹
3. 当前目录

## 通配符导入

```chtl
// 导入目录下所有CHTL文件
[Import] @Chtl from ./components/*
[Import] @Chtl from ./components/*.chtl

// 只导入cmod文件
[Import] @Chtl from ./dist/*.cmod

// 使用点号语法
[Import] @Chtl from components.*
[Import] @Chtl from Chtholly.Space.*
```

## C++实现

### 基本导入

```cpp
// 创建生成器并配置路径
CHTLGenerator generator(context, options);

ImportPathConfig pathConfig;
pathConfig.currentDirectory = std::filesystem::current_path();
pathConfig.moduleDirectory = pathConfig.currentDirectory / "module";
pathConfig.officialModulePath = "/usr/local/chtl/modules";
pathConfig.searchOfficialFirst = true;

generator.configureImportPaths(pathConfig);

// 处理导入语句
generator.processImportStatement("[Import] @Html from page.html as pageContent");
```

### 批量导入

```cpp
std::vector<std::string> imports = {
    "[Import] @Style from theme.css as theme",
    "[Import] [Custom] @Element Button from ui.chtl",
    "[Import] @Chtl from utils"
};

generator.processImports(imports);
```

### 导入管理器

```cpp
// 获取导入管理器
auto importManager = generator.getImportManager();

// 手动处理导入
ImportDeclaration decl;
decl.type = ImportType::HTML;
decl.sourcePath = "template.html";
decl.asName = "mainTemplate";
decl.hasAsClause = true;

importManager->processImport(decl, generator);
```

## 高级特性

### 1. 循环依赖检测

系统自动检测并防止循环导入：

```
文件A导入文件B
文件B导入文件C
文件C导入文件A  // 错误：循环依赖
```

### 2. 路径规范化

自动处理不同的路径表示：

```chtl
// 以下导入等价
[Import] @Chtl from utils.ui.button
[Import] @Chtl from utils/ui/button
[Import] @Chtl from ./utils/ui/button
```

### 3. 重复导入保护

同一文件只会被导入一次：

```chtl
// 第一次导入 - 处理文件
[Import] @Chtl from common

// 后续导入 - 自动跳过
[Import] @Chtl from common
[Import] @Chtl from ./common.chtl
```

### 4. 智能扩展名推断

```chtl
// 自动查找 styles.css
[Import] @Style from styles as myStyles

// 按优先级查找：button.cmod > button.chtl
[Import] @Chtl from button
```

## 最佳实践

### 1. 组织结构

```
project/
├── src/
│   ├── main.chtl
│   ├── components/
│   │   ├── header.chtl
│   │   └── footer.chtl
│   └── styles/
│       └── theme.css
├── module/        # 本地模块
│   ├── ui.cmod
│   └── utils.chtl
└── dist/          # 编译输出
    └── app.cjmod
```

### 2. 导入顺序

```chtl
// 1. 导入外部依赖
[Import] @CJmod from ui-framework

// 2. 导入本地模块
[Import] @Chtl from ./module/utils

// 3. 导入样式
[Import] @Style from ./styles/theme.css as theme

// 4. 导入组件
[Import] [Custom] @Element Header from ./components/header.chtl
```

### 3. 命名约定

- 使用描述性的as名称
- 避免命名冲突
- 保持一致的命名风格

```chtl
// 好的命名
[Import] @Html from header.html as siteHeader
[Import] @Style from button.css as buttonStyles

// 避免
[Import] @Html from h.html as h
[Import] @Style from s.css as s
```

### 4. 性能优化

- 只导入需要的组件（选择性导入）
- 避免通配符导入大量文件
- 合理组织模块结构

## 错误处理

### 常见错误

1. **文件未找到**
```
Error: Import file not found: components/missing.chtl
```

2. **循环依赖**
```
Error: Circular dependency detected: a.chtl -> b.chtl -> a.chtl
```

3. **无效路径**
```
Error: Invalid import path: ../../../outside-project
```

### 调试技巧

```cpp
// 检查导入的文件
auto importedFile = importManager->getImportedFile("components.chtl");
if (importedFile) {
    std::cout << "File path: " << importedFile->absolutePath << std::endl;
    std::cout << "Content: " << importedFile->content << std::endl;
}

// 清理导入缓存
importManager->clear();
```

## 示例：完整项目

```chtl
// main.chtl

// 导入框架
[Import] @CJmod from chtl-ui

// 导入工具
[Import] @Chtl from utils.*

// 导入样式
[Import] @Style from theme.css as globalTheme

// 导入组件
[Import] [Custom] @Element Navigation from ./components/nav.chtl
[Import] [Template] @Element PageLayout from ./layouts/default.chtl

// 使用导入的资源
html
{
    head
    {
        style
        {
            [Origin] @Style globalTheme;
        }
    }
    
    body
    {
        @Element PageLayout
        {
            // 页面内容
            @Element Navigation;
        }
    }
}
```