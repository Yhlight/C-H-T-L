# CHTL Scripts 目录结构

本目录包含了CHTL项目的所有脚本，按功能和平台分类组织。

## 目录结构

```
scripts/
├── build/              # 构建相关脚本
│   ├── build_all.sh        # 构建所有组件
│   ├── build_compiler.sh   # 构建编译器
│   └── build_ide.sh        # 构建IDE
│
├── pack/               # 打包相关脚本
│   ├── pack_all.sh         # 打包所有模块
│   ├── pack_cmod.sh        # 打包CMOD模块
│   ├── pack_cjmod.sh       # 打包CJMOD模块
│   └── pack_modules.sh     # 打包多个模块
│
├── clean/              # 清理脚本
│   └── clean_project.sh    # 清理项目
│
├── setup/              # 环境设置脚本
│   └── (待添加)
│
├── utils/              # 工具脚本
│   └── extract_antlr_runtime.sh  # 提取ANTLR运行时
│
├── platform/           # 平台特定脚本
│   ├── windows/            # Windows批处理脚本
│   │   ├── build.bat
│   │   ├── pack.bat
│   │   └── setup-windows.bat
│   ├── linux/              # Linux特定脚本
│   └── macos/              # macOS特定脚本
│
└── cross-platform/     # 跨平台Python脚本
    ├── build.py            # 跨平台构建脚本
    ├── pack.py             # 跨平台打包脚本
    └── test_cross_platform.py  # 跨平台测试脚本
```

## 使用方法

### 推荐方式（使用根目录的入口脚本）

在项目根目录下，我们提供了便捷的入口脚本：

**跨平台（Python）：**
```bash
# 构建
python build.py --type Release

# 打包
python pack.py --all
```

**Windows：**
```cmd
build.bat --type Release
pack.bat --all
```

**Linux/macOS：**
```bash
./build.sh --type Release
./pack.sh --all
```

### 直接使用脚本

如果需要使用特定的脚本：

**构建编译器（Linux/macOS）：**
```bash
./scripts/build/build_compiler.sh
```

**设置Windows环境：**
```cmd
scripts\platform\windows\setup-windows.bat
```

**跨平台构建：**
```bash
python scripts/cross-platform/build.py --help
```

## 脚本分类说明

### build/ - 构建脚本
- 包含编译器、IDE等组件的构建脚本
- 主要是Shell脚本，适用于Linux/macOS

### pack/ - 打包脚本
- CMOD/CJMOD模块打包
- 支持批量打包

### clean/ - 清理脚本
- 清理构建产物
- 重置项目状态

### platform/ - 平台特定脚本
- Windows批处理文件
- 平台特定的优化和设置

### cross-platform/ - 跨平台脚本
- 使用Python编写
- 在所有平台上提供一致体验

## 开发指南

1. 新脚本应放在相应的功能目录下
2. 跨平台脚本优先使用Python
3. 平台特定脚本放在platform/下
4. 在根目录提供便捷入口脚本