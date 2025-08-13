# CHTL 快速开始指南

本指南帮助您快速开始使用 CHTL。

## 🚀 5分钟快速开始

### 1. 克隆项目

```bash
git clone https://github.com/chtl/chtl.git
cd chtl
```

### 2. 构建项目

**方式一：使用 Python（推荐，跨平台）**
```bash
python build.py --type Release
```

**方式二：使用平台特定脚本**

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
├── build.py          # 🔨 构建脚本（跨平台）
├── pack.py           # 📦 打包脚本（跨平台）
├── src/              # 💻 源代码
├── module/           # 📚 模块库
├── docs/             # 📖 文档
├── examples/         # 🎯 示例
└── scripts/          # 🛠️ 更多脚本
    ├── build/        # 构建脚本
    ├── pack/         # 打包脚本
    └── cross-platform/ # 跨平台脚本
```

## 🛠️ 常用命令

### 构建命令

```bash
# 构建 Release 版本
python build.py --type Release

# 构建 Debug 版本
python build.py --type Debug

# 清理并重新构建
python build.py --clean --type Release

# 构建并运行测试
python build.py --type Release --test

# 构建并安装
python build.py --type Release --install
```

### 打包命令

```bash
# 打包所有模块
python pack.py --all

# 打包特定模块
python pack.py module/Chtholly

# 指定输出目录
python pack.py --all -o dist/
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