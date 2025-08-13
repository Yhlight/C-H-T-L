# CHTL 模块结构说明

## 模块类型

CHTL 支持三种模块类型：

### 1. 纯 CMOD 模块（CHTL 组件）
```
ModuleName/
├── src/
│   └── ModuleName.chtl    # 主模块文件
└── info/
    └── ModuleName.chtl    # 模块信息
```

### 2. 纯 CJMOD 模块（JavaScript 扩展）
```
ModuleName/
├── src/
│   └── modulename.cpp     # C++ 实现
└── info/
    └── ModuleName.chtl    # 模块信息
```

### 3. 混合模块（CMOD + CJMOD）
```
ModuleName/
├── CMOD/                  # CHTL 组件部分
│   └── ModuleName/
│       ├── src/
│       │   └── ModuleName.chtl
│       └── info/
│           └── ModuleName.chtl
└── CJMOD/                 # JavaScript 扩展部分
    └── ModuleName/
        ├── src/
        │   └── modulename.cpp
        └── info/
            └── ModuleName.chtl
```

## 导入语法

### 基本导入

```chtl
-- 导入 CMOD（CHTL 组件）
[Import] @Chtl from ModuleName

-- 导入 CJMOD（JavaScript 扩展）
[Import] @CJmod from ModuleName

-- 导入子模块（使用点号分隔）
[Import] @Chtl from UIKit.Button
[Import] @CJmod from Utils.Math

-- 导入嵌套文件夹的模块（使用斜杠）
[Import] @Chtl from Chtl/Core
[Import] @CJmod from Tools/Parser
```

### 导入规则

1. **模块名解析**：
   - 不带路径分隔符的名称（如 `Chtholly`）被视为模块名
   - 系统会在 `module/` 目录下查找对应的模块

2. **混合模块处理**：
   - 使用 `@Chtl` 导入时，只加载 CMOD 部分
   - 使用 `@CJmod` 导入时，只加载 CJMOD 部分
   - 不会自动同时加载两部分

3. **子模块支持**：
   - 使用点号（`.`）表示子模块关系
   - 例如：`UIKit.Button` 会查找 `module/UIKit/Button/`

4. **路径转换**：
   - 点号（`.`）会转换为路径分隔符
   - 例如：`Chtl.Core` → `module/Chtl/Core/`

## 模块示例

### 示例 1：珂朵莉模块（混合模块）

```
module/Chtholly/
├── CMOD/Chtholly/         # UI 组件
│   ├── src/
│   │   └── Chtholly.chtl  # 样式、元素定义
│   └── info/
│       └── Chtholly.chtl
└── CJMOD/Chtholly/        # JS 扩展
    ├── src/
    │   └── chtholly.cpp   # 动画函数实现
    └── info/
        └── Chtholly.chtl
```

使用方式：
```chtl
-- 只导入 UI 组件
[Import] @Chtl from Chtholly

-- 只导入 JS 扩展
[Import] @CJmod from Chtholly

-- 在 CHTL 中使用
body {
    @Element ChthollysCard from Chtholly;
}

-- 在 script 中使用
script {
    // CJMOD 函数自动可用
    fadeIn({{.card}}, 500);
}
```

### 示例 2：带子模块的结构

```
module/UIKit/
└── CMOD/
    ├── Button/
    │   ├── src/
    │   │   └── Button.chtl
    │   └── info/
    │       └── Button.chtl
    ├── Form/
    │   ├── src/
    │   │   └── Form.chtl
    │   └── info/
    │       └── Form.chtl
    └── Layout/
        ├── src/
        │   └── Layout.chtl
        └── info/
            └── Layout.chtl
```

使用方式：
```chtl
-- 导入特定子模块
[Import] @Chtl from UIKit.Button
[Import] @Chtl from UIKit.Form
[Import] @Chtl from UIKit.Layout

-- 使用导入的组件
@Element Button from UIKit.Button;
@Element Form from UIKit.Form;
@Style FlexLayout from UIKit.Layout;
```

## 最佳实践

1. **模块命名**：
   - 使用 PascalCase 命名模块
   - 子模块名应该反映其功能

2. **目录结构**：
   - 保持 CMOD 和 CJMOD 分离
   - 每个模块都应有完整的 info 文件

3. **导入策略**：
   - 只导入需要的部分（CMOD 或 CJMOD）
   - 避免循环依赖
   - 使用明确的模块路径

4. **版本兼容**：
   - 在 info 文件中指定兼容的 CHTL 版本
   - 保持向后兼容性