# CMOD (CHTL Module) 系统文档

## 概述

CMOD是CHTL提供的模块化系统，允许开发者将CHTL代码打包成可重用的模块。CMOD支持：

- 标准化的模块结构
- 子模块嵌套
- 依赖管理
- 版本控制
- 导出表优化
- 打包和分发

## CMOD标准格式

### 基本结构

```
ModuleName/
├── src/                    # 源代码目录
│   └── ModuleName.chtl    # 主模块文件（可选）
└── info/                   # 模块信息目录
    └── ModuleName.chtl    # 模块信息文件（必需）
```

**重要规则**：
- 模块文件夹、主模块文件、模块信息文件必须同名
- 在没有子模块的情况下，主模块文件必须存在
- `src`和`info`目录都是必需的

### 模块信息文件

info目录中的CHTL文件包含两个部分：

#### 1. 模块信息 [Info]

```chtl
[Info]
{
    name = "ModuleName";
    version = "1.0.0";
    description = "模块描述";
    author = "作者名称";
    license = "MIT";
    dependencies = "Dependency1, Dependency2";  // 逗号分隔
    category = "theme";  // 模块类别
    minCHTLVersion = "1.0.0";  // 最低CHTL版本要求
    maxCHTLVersion = "2.0.0";  // 最高CHTL版本要求
}
```

#### 2. 导出表 [Export]

导出表控制模块对外暴露的内容。有两种模式：

**隐式模式（默认）**：
- 如果没有[Export]块，模块中所有定义的模板和自定义都会被导出
- 适合小型模块或完全公开的模块

**显式模式**：
- 明确定义[Export]块后，只有列出的项才会被导出
- 提供精确的访问控制
- 适合大型模块或需要隐藏内部实现的模块

```chtl
[Export]
{
    @Style StyleName1, StyleName2, StyleName3;
    
    @Element ElementName1, ElementName2;
    
    @Var VarGroupName1, VarGroupName2;
}
```

**示例：控制导出**

```chtl
// info/MyModule.chtl
[Info]
{
    name = "MyModule";
    version = "1.0.0";
    // ...
}

[Export]
{
    // 只导出这些样式
    @Style PublicStyle, SharedStyle;
    
    // 只导出这个元素
    @Element PublicComponent;
    
    // 内部使用的PrivateStyle和InternalComponent不会被导出
}
```

对应的源文件：

```chtl
// src/MyModule.chtl
[Namespace] MyModule
{
    // 会被导出
    [Template] @Style PublicStyle
    {
        color: blue;
    }
    
    // 会被导出
    [Template] @Style SharedStyle
    {
        font-size: 14px;
    }
    
    // 不会被导出（未在Export中列出）
    [Template] @Style PrivateStyle
    {
        /* 内部使用 */
    }
    
    // 会被导出
    [Template] @Element PublicComponent
    {
        div { /* ... */ }
    }
    
    // 不会被导出
    [Custom] @Element InternalComponent
    {
        /* 仅供模块内部使用 */
    }
}
```

### 子模块

子模块采用嵌套结构：

```
ParentModule/
├── src/
│   ├── (ParentModule.chtl)  # 可选
│   ├── SubModule1/
│   │   ├── src/
│   │   │   └── SubModule1.chtl
│   │   └── info/
│   │       └── SubModule1.chtl
│   └── SubModule2/
│       ├── src/
│       │   └── SubModule2.chtl
│       └── info/
│           └── SubModule2.chtl
└── info/
    └── ParentModule.chtl
```

当存在子模块时，主模块的CHTL文件可以省略。

## 使用CMOD

### 导入模块

#### 导入整个模块

```chtl
[Import] @Chtl from ModuleName
```

这会导入模块及其所有子模块。

#### 导入特定子模块

```chtl
[Import] @Chtl from ParentModule.SubModule
```

#### 导入编译后的模块

```chtl
[Import] @CJmod from ModuleName
```

`.cjmod`是编译后的CMOD文件。

### 模块搜索路径

模块按以下顺序搜索：

1. **官方模块目录**：编译器安装目录下的`module`文件夹
2. **本地模块目录**：当前目录的`module`文件夹
3. **当前目录**：直接在当前目录搜索

搜索优先级：
- `.cmod`文件优先于目录形式
- 如果只提供名称（无后缀），按上述路径搜索

### 使用模块内容

导入模块后，可以直接使用其中定义的模板和自定义：

```chtl
// 使用模块中的样式模板
div
{
    style
    {
        @Style ModuleStyleName;
    }
}

// 使用模块中的元素模板
@Element ModuleElementName;

// 使用模块中的变量组
style
{
    color: ModuleVarGroup(varName);
}
```

## C++ API

### CMODManager

模块管理的核心类：

```cpp
// 创建管理器
auto cmodManager = std::make_shared<CMODManager>(context);

// 添加模块搜索路径
cmodManager->addModulePath("/custom/module/path");

// 加载模块
auto module = cmodManager->loadModule("ModuleName");

// 获取子模块
auto subModule = cmodManager->getModule("Parent.SubModule");
```

### CMODModule

表示一个加载的模块：

```cpp
// 获取模块信息
const CMODInfo& info = module->getInfo();
std::cout << "Name: " << info.name << std::endl;
std::cout << "Version: " << info.version << std::endl;

// 获取子模块
auto subModule = module->getSubModule("SubModuleName");
std::vector<std::string> subNames = module->getSubModuleNames();

// 获取源文件
const auto& files = module->getSourceFiles();

// 验证模块
bool valid = module->validate();
bool depsOk = module->checkDependencies();
bool versionOk = module->checkCHTLVersion("1.5.0");
```

### CMODPacker

打包模块为.cmod文件：

```cpp
CMODPacker packer(context);
packer.setSourcePath("/path/to/modules");
packer.setOutputPath("/output/path");

// 打包单个模块
bool success = packer.pack("ModuleName");

// 或直接指定目录和输出文件
success = packer.packDirectory("/path/to/module", "output.cmod");
```

### CMODUnpacker

解包.cmod文件：

```cpp
CMODUnpacker unpacker(context);

// 验证CMOD文件
bool valid = unpacker.validateCMODFile("module.cmod");

// 解包到目录
bool success = unpacker.unpack("module.cmod", "/output/directory");
```

### CMODHelper

工具函数：

```cpp
// 创建模块模板
CMODHelper::createModuleTemplate("/path", "NewModule");

// 版本比较
int cmp = CMODHelper::compareVersions("1.2.0", "1.1.0"); // 返回 1

// 路径转换
std::string path = CMODHelper::moduleNameToPath("Parent.Sub"); // "Parent/Sub"

// 验证模块名
bool valid = CMODHelper::isValidModuleName("MyModule"); // true
```

### 导出控制的好处

1. **封装性**：隐藏内部实现细节
2. **稳定性**：只暴露稳定的公共API
3. **性能**：减少导入时的处理量
4. **维护性**：明确的公共接口便于版本管理

### 导出最佳实践

1. **最小化导出原则**：只导出必要的内容
2. **语义化命名**：公共API使用清晰的命名
3. **内部前缀**：内部使用的项可以加上`_`或`Internal`前缀
4. **文档化**：为导出的项提供使用说明

## 创建CMOD模块

### 步骤1：创建目录结构

```bash
mkdir -p MyModule/src MyModule/info
```

### 步骤2：编写模块信息

`MyModule/info/MyModule.chtl`:

```chtl
[Info]
{
    name = "MyModule";
    version = "1.0.0";
    description = "我的CHTL模块";
    author = "Your Name";
    license = "MIT";
    dependencies = "";
    category = "utility";
    minCHTLVersion = "1.0.0";
}
```

### 步骤3：编写模块代码

`MyModule/src/MyModule.chtl`:

```chtl
[Namespace] MyModule
{
    [Template] @Style MyStyle
    {
        color: blue;
        font-size: 16px;
    }
    
    [Template] @Element MyComponent
    {
        div
        {
            class: my-component;
            
            style
            {
                @Style MyStyle;
            }
            
            text { "My Component" }
        }
    }
}
```

### 步骤4：打包模块

使用CHTL编译器或打包脚本：

```bash
chtl-pack MyModule
```

这将生成`MyModule.cmod`文件。

## 最佳实践

### 1. 命名规范

- 模块名使用PascalCase（如`MyModule`）
- 子模块名简洁明了
- 避免使用保留字

### 2. 版本管理

- 使用语义化版本（主版本.次版本.修订版本）
- 重大更改增加主版本
- 新功能增加次版本
- 问题修复增加修订版本

### 3. 依赖管理

- 最小化依赖
- 明确指定版本要求
- 避免循环依赖

### 4. 模块组织

- 相关功能放在同一模块
- 使用子模块组织大型模块
- 保持模块的单一职责

### 5. 文档

- 在模块中包含使用说明
- 提供示例代码
- 记录API变更

## 高级特性

### 1. 条件导入

基于版本或特性的条件导入（规划中）：

```chtl
[Import] @Chtl from ModuleName where version >= "2.0.0"
```

### 2. 模块别名

导入时重命名模块（规划中）：

```chtl
[Import] @Chtl from LongModuleName as LMN
```

### 3. 部分导入

只导入需要的部分（规划中）：

```chtl
[Import] @Style StyleName from ModuleName
[Import] @Element ElementName from ModuleName
```

## 错误处理

### 常见错误

1. **模块未找到**
   - 检查模块名拼写
   - 确认模块路径正确
   - 验证模块已安装

2. **版本不兼容**
   - 检查CHTL版本要求
   - 更新模块或CHTL

3. **循环依赖**
   - 检查模块依赖关系
   - 重构模块结构

4. **无效的模块结构**
   - 确保有`src`和`info`目录
   - 检查文件命名一致性

## 示例：Chtholly主题模块

完整的主题模块示例：

```
Chtholly/
├── src/
│   ├── Chtholly.chtl       # 主题主文件
│   ├── Components/         # 组件子模块
│   │   ├── src/
│   │   └── info/
│   └── Utilities/          # 工具子模块
│       ├── src/
│       └── info/
└── info/
    └── Chtholly.chtl       # 模块信息
```

使用：

```chtl
// 导入整个主题
[Import] @Chtl from Chtholly

// 只导入组件
[Import] @Chtl from Chtholly.Components

// 使用主题
body
{
    @Element ChthollyLayout;
}
```

## 总结

CMOD系统为CHTL提供了强大的模块化能力，使得代码重用、分发和管理变得简单高效。通过标准化的结构、灵活的导出控制和完善的工具支持，开发者可以轻松创建和使用CHTL模块。