# CHTL模块结构说明

## 模块类型

CHTL支持两种模块类型：

### 1. CMOD (CHTL Module)
纯CHTL模块，只包含`.chtl`文件，用于提供：
- UI组件
- 样式定义
- 模板
- 变量组

### 2. CJMOD (CHTL JavaScript Module)
C++扩展模块，包含`.cpp`和`.h`文件，用于：
- 扩展CHTL JS语法
- 提供高性能功能
- 实现底层操作

## 模块结构规范

### 单一类型模块

#### CMOD结构
```
ModuleName/
├── src/
│   └── ModuleName.chtl    # 主模块文件
└── info/
    └── ModuleName.chtl    # 模块信息文件
```

#### CJMOD结构
```
ModuleName/
├── src/
│   ├── *.cpp             # C++源文件
│   └── *.h               # C++头文件
└── info/
    └── ModuleName.chtl    # 模块信息文件
```

### 混合模块（CMOD + CJMOD）

当模块需要同时提供CHTL组件和JS扩展时：

```
ModuleName/
├── CMOD/
│   └── ModuleName/
│       ├── src/
│       │   └── ModuleName.chtl
│       └── info/
│           └── ModuleName.chtl
└── CJMOD/
    └── ModuleName/
        ├── src/
        │   ├── *.cpp
        │   └── *.h
        └── info/
            └── ModuleName.chtl
```

### 带子模块的结构

```
UIKit/
└── CMOD/
    ├── Button/
    │   ├── src/
    │   │   └── Button.chtl
    │   └── info/
    │       └── Button.chtl
    ├── Card/
    │   ├── src/
    │   │   └── Card.chtl
    │   └── info/
    │       └── Card.chtl
    └── Modal/
        ├── src/
        │   └── Modal.chtl
        └── info/
            └── Modal.chtl
```

## 使用方式

### 导入CMOD
```chtl
// 导入整个CMOD模块
[Import] @Chtl ModuleName

// 导入子模块（使用点号分隔）
[Import] @Chtl UIKit.Button

// 导入嵌套文件夹的模块
[Import] @Chtl Chtl/Core
```

### 导入CJMOD
```chtl
// 导入CJMOD模块
[Import] @CJmod ModuleName

// 导入混合模块的CJMOD部分
[Import] @CJmod Chtholly
```

## 重要说明

1. **命名一致性**：模块文件夹、主文件、info文件必须同名
2. **类型分离**：CHTL不会统一处理CMOD和CJMOD，需要分别导入
3. **info文件中的name字段**：不决定实际使用的名称，实际名称由文件夹/文件名决定
4. **导入语法**：支持无修饰字符串，不需要引号
5. **路径分隔**：使用 `/` 表示文件夹嵌套，使用 `.` 表示子模块

## 示例

### Chtl/Core（纯CMOD）
提供CHTL标准库功能：
- 基础样式重置
- 布局工具
- 常用组件

使用方式：
```chtl
[Import] @Chtl Chtl/Core
```

### Chtholly（混合模块）
- **CMOD部分**：提供珂朵莉主题UI组件
- **CJMOD部分**：提供动画和交互的JS扩展

### UIKit（带子模块的CMOD）
包含多个独立的UI组件：
- Button
- Card  
- Modal
等等