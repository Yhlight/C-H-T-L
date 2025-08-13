# CHTL 快速开始指南

本指南帮助您快速开始使用 CHTL。

## 🚀 5分钟快速开始

### 1. 克隆项目

```bash
git clone https://github.com/chtl/chtl.git
cd chtl
```

### 2. 构建项目

Windows:
```cmd
build.bat --type Release
```

Linux/macOS:
```bash
./build.sh --type Release
```

### 3. 创建第一个 CHTL 文件

创建 `hello.chtl`:

```chtl
-- 导入珂朵莉模块
[Import] @Chtl from Chtholly

-- 创建页面
html {
    head {
        title { "Hello CHTL!" }
    }
    
    body {
        @Element ChthollysCard from Chtholly {
            h1 { "欢迎使用 CHTL! 🎉" }
            p { "这是您的第一个 CHTL 页面" }
        }
    }
}
```

### 4. 编译

```bash
./build/bin/chtl hello.chtl -o hello.html
```

### 5. 查看结果

在浏览器中打开 `hello.html`。

## 📁 项目结构一览

```
chtl/
├── build.bat         # 🔨 Windows构建脚本
├── build.sh          # 🔨 Unix构建脚本
├── pack.bat          # 📦 Windows打包脚本
├── pack.sh           # 📦 Unix打包脚本
├── src/              # 💻 源代码
├── src/module/       # 📚 模块库
├── docs/             # 📖 文档
├── examples/         # 🎯 示例
└── scripts/          # 🛠️ 更多脚本
    ├── build/        # 构建脚本
    ├── pack/         # 打包脚本
    └── platform/     # 平台特定脚本
```

## 🛠️ 常用命令

### 构建命令

**Windows:**
```cmd
rem Build Release version
build.bat --type Release

rem Build Debug version  
build.bat --type Debug

rem Clean and rebuild
build.bat --clean --type Release

rem Build and run tests
build.bat --type Release --test

rem Build and install
build.bat --type Release --install
```

**Linux/macOS:**
```bash
# Build Release version
./build.sh --type Release

# Build Debug version
./build.sh --type Debug

# Clean and rebuild
./build.sh --clean --type Release

# Build and run tests
./build.sh --type Release --test

# Build and install
./build.sh --type Release --install
```

### 打包命令

**Windows:**
```cmd
rem Pack all modules
pack.bat --all

rem Pack specific module
pack.bat module\Chtholly

rem Specify output directory
pack.bat --all -o dist
```

**Linux/macOS:**
```bash
# Pack all modules
./pack.sh --all

# Pack specific module
./pack.sh src/module/Chtholly

# Specify output directory
./pack.sh --all -o dist/
```

## 💡 VSCode 开发

1. **打开项目**
   ```bash
   code .
   ```

2. **安装推荐扩展**
   - 打开命令面板 (Ctrl+Shift+P)
   - 运行 "Extensions: Show Recommended Extensions"
   - 安装所有推荐扩展

3. **使用 CHTL 语法高亮**
   - CHTL 文件会自动识别
   - 使用代码片段快速编写

4. **调试**
   - 按 F5 启动调试
   - 在代码中设置断点

## 🌐 平台特定说明

### Windows 用户

首次使用请运行环境设置（需管理员权限）：
```cmd
scripts\platform\windows\setup-windows.bat
```

### Linux/macOS 用户

确保已安装必要依赖：
```bash
# Ubuntu/Debian
sudo apt install build-essential cmake python3

# macOS
brew install cmake python3
```

## 📚 下一步

- 📖 阅读[完整文档](docs/README.md)
- 🎯 查看[更多示例](examples/)
- 🔧 了解[模块开发](docs/module_structure.md)
- 🌍 查看[跨平台指南](docs/Cross_Platform_Guide.md)

## ❓ 遇到问题？

- 查看 [常见问题](docs/FAQ.md)
- 提交 [Issue](https://github.com/chtl/chtl/issues)
- 加入 [社区讨论](https://discord.gg/chtl)

---

🎉 **恭喜！** 您已经准备好开始使用 CHTL 了！