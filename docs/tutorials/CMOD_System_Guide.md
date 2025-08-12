# CMOD系统使用指南

## 概述

CMOD（CHTL Module）是CHTL编译器提供的模块化系统，允许开发者创建、打包、分发和管理可重用的CHTL代码模块。

## CMOD模块结构

一个标准的CMOD模块具有以下目录结构：

```
ModuleName/
├── src/                    # 源代码目录
│   └── ModuleName.chtl    # 主模块文件（可选）
├── info/                   # 模块信息目录
│   └── ModuleName.chtl    # 模块信息文件（必需）
└── submodules/            # 子模块（可选）
    └── SubModule/
        ├── src/
        └── info/
```

### 命名规则

- 模块文件夹名称、主模块文件名、信息文件名必须一致
- 子模块遵循相同的命名规则

## 模块信息文件

模块信息文件位于`info/`目录中，包含两个主要部分：

### [Info]块

定义模块的基本信息：

```chtl
[Info]
{
    name = "MyModule";
    version = "1.0.0";
    description = "一个示例CHTL模块";
    author = "作者名称";
    license = "MIT";
    dependencies = "BaseModule@1.0.0, UtilModule@2.1.0";
    category = "component";
    minCHTLVersion = "1.0.0";
    maxCHTLVersion = "2.0.0";
}
```

### [Export]块

声明模块导出的元素（由系统自动生成）：

```chtl
[Export]
{
    @Style MyStyle, CardStyle, ButtonStyle;
    @Element MyComponent, Card, Button;
    @Var MyColors, MySizes, MyBreakpoints;
}
```

## 使用CMOD系统

### 1. 验证模块

```cpp
#include "CmodSystem/CmodValidator.h"

chtl::CmodValidator validator;
auto result = validator.validateModule("path/to/module");

if (result.isValid) {
    std::cout << "模块验证通过" << std::endl;
} else {
    for (const auto& error : result.errors) {
        std::cerr << "错误: " << error << std::endl;
    }
}
```

### 2. 提取模块信息

```cpp
#include "CmodSystem/CmodExtractor.h"

chtl::CmodExtractor extractor;
auto info = extractor.extractFromDirectory("path/to/module");

if (info) {
    std::cout << "模块名: " << info->name << std::endl;
    std::cout << "版本: " << info->version << std::endl;
    std::cout << "描述: " << info->description << std::endl;
}
```

### 3. 打包模块

```cpp
#include "CmodSystem/CmodPackager.h"

chtl::CmodPackager packager;
chtl::CmodPackager::PackageOptions options;
options.compress = true;
options.generateExports = true;
options.outputPath = "MyModule-1.0.0.cmod";

auto result = packager.package("path/to/module", options);

if (result.success) {
    std::cout << "打包成功: " << result.packagePath << std::endl;
    std::cout << "包大小: " << result.packageSize << " 字节" << std::endl;
} else {
    std::cerr << "打包失败: " << result.error << std::endl;
}
```

### 4. 管理模块注册表

```cpp
#include "CmodSystem/CmodRegistry.h"

// 初始化注册表
chtl::CmodRegistry registry;
registry.initialize();

// 注册模块
chtl::CmodInfo moduleInfo;
moduleInfo.name = "MyModule";
moduleInfo.version = "1.0.0";
registry.registerModule(moduleInfo, "/path/to/installed/module");

// 查询模块
if (registry.hasModule("MyModule")) {
    auto module = registry.getModule("MyModule");
    std::cout << "模块路径: " << module->installPath << std::endl;
}

// 按类别查询
auto components = registry.getModulesByCategory("component");
for (const auto* module : components.modules) {
    std::cout << module->info.name << " - " << module->info.description << std::endl;
}

// 检查依赖
if (registry.checkDependencies("MyModule")) {
    std::cout << "所有依赖都已满足" << std::endl;
}
```

## 在CHTL中使用模块

### 导入模块

```chtl
-- 导入整个模块
[Import] @Chtl from MyModule;

-- 导入特定子模块
[Import] @Chtl from MyModule.SubModule;

-- 使用别名
[Import] @Chtl from MyModule as MM;
```

### 使用模块中的元素

```chtl
-- 使用导入的样式
<div @Style MyModule.CardStyle>
    内容
</div>

-- 使用导入的元素
<@Element MyModule.Card title="标题">
    卡片内容
</@Element>

-- 使用导入的变量
style {
    color: @Var MyModule.MyColors.primary;
    font-size: @Var MyModule.MySizes.large;
}
```

## 创建CMOD模块示例

### 1. 创建目录结构

```bash
mkdir -p MyTheme/src MyTheme/info
```

### 2. 编写模块信息

`MyTheme/info/MyTheme.chtl`:

```chtl
[Info]
{
    name = "MyTheme";
    version = "1.0.0";
    description = "自定义主题模块";
    author = "Your Name";
    license = "MIT";
    category = "theme";
}
```

### 3. 编写模块代码

`MyTheme/src/MyTheme.chtl`:

```chtl
-- 定义颜色变量
[Template] @Var ThemeColors {
    primary = "#007bff";
    secondary = "#6c757d";
    success = "#28a745";
    danger = "#dc3545";
    warning = "#ffc107";
    info = "#17a2b8";
    light = "#f8f9fa";
    dark = "#343a40";
}

-- 定义按钮样式
[Template] @Style ButtonStyle {
    display: inline-block;
    padding: 0.375rem 0.75rem;
    font-size: 1rem;
    line-height: 1.5;
    border-radius: 0.25rem;
    text-align: center;
    vertical-align: middle;
    cursor: pointer;
    user-select: none;
    border: 1px solid transparent;
    transition: all 0.15s ease-in-out;
    
    &:hover {
        opacity: 0.8;
    }
    
    &.primary {
        color: white;
        background-color: @Var ThemeColors.primary;
        border-color: @Var ThemeColors.primary;
    }
}

-- 定义卡片元素
[Template] @Element Card {
    <div class="card" @Style CardStyle>
        <div class="card-header" if="$title">
            $title
        </div>
        <div class="card-body">
            @content
        </div>
        <div class="card-footer" if="$footer">
            $footer
        </div>
    </div>
}

[Template] @Style CardStyle {
    position: relative;
    display: flex;
    flex-direction: column;
    min-width: 0;
    word-wrap: break-word;
    background-color: white;
    background-clip: border-box;
    border: 1px solid rgba(0,0,0,.125);
    border-radius: 0.25rem;
    
    .card-header {
        padding: 0.75rem 1.25rem;
        margin-bottom: 0;
        background-color: rgba(0,0,0,.03);
        border-bottom: 1px solid rgba(0,0,0,.125);
    }
    
    .card-body {
        flex: 1 1 auto;
        padding: 1.25rem;
    }
    
    .card-footer {
        padding: 0.75rem 1.25rem;
        background-color: rgba(0,0,0,.03);
        border-top: 1px solid rgba(0,0,0,.125);
    }
}
```

### 4. 验证和打包

```cpp
// 验证模块
chtl::CmodValidator validator;
auto validationResult = validator.validateModule("MyTheme");

if (validationResult.isValid) {
    // 打包模块
    chtl::CmodPackager packager;
    auto packageResult = packager.package("MyTheme");
    
    if (packageResult.success) {
        std::cout << "模块打包成功: " << packageResult.packagePath << std::endl;
    }
}
```

## 最佳实践

1. **模块命名**：使用清晰、描述性的名称
2. **版本管理**：遵循语义化版本规范（SemVer）
3. **依赖管理**：明确声明所有依赖，避免循环依赖
4. **文档编写**：在模块中包含详细的使用说明
5. **测试覆盖**：为模块编写完整的测试用例
6. **向后兼容**：主版本升级时保持向后兼容

## 故障排除

### 常见问题

1. **模块验证失败**
   - 检查目录结构是否正确
   - 确认文件命名是否一致
   - 验证info文件格式

2. **依赖解析错误**
   - 检查依赖版本是否正确
   - 确认依赖模块已安装
   - 检查是否存在循环依赖

3. **打包失败**
   - 确保有写入权限
   - 检查磁盘空间
   - 验证模块结构完整性

## 总结

CMOD系统提供了完整的模块化解决方案，使CHTL代码的重用和分发变得简单高效。通过遵循标准的模块结构和最佳实践，开发者可以创建高质量的可重用组件库。