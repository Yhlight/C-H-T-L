# CHTL 跨平台开发指南

## 概述

CHTL 现在提供完整的跨平台支持，可以在 Windows、Linux 和 macOS 上构建和运行。本指南介绍如何在不同平台上设置开发环境和使用 CHTL。

## 支持的平台

- **Windows**: Windows 10/11 (x64)
- **Linux**: Ubuntu 20.04+, Debian 10+, RHEL 8+, Fedora 34+
- **macOS**: macOS 10.15+ (Intel 和 Apple Silicon)

## 跨平台脚本

CHTL 提供了两套脚本系统：

### 1. Python 脚本（推荐）

跨平台的 Python 脚本，在所有平台上提供一致的体验：

- `scripts/cross-platform/build.py` - 构建脚本
- `scripts/cross-platform/pack.py` - 打包脚本

### 2. 平台特定脚本

- **Windows**: `.bat` 批处理文件
- **Linux/macOS**: `.sh` Shell 脚本

## Windows 开发环境设置

### 自动设置（推荐）

1. 以管理员身份运行：
   ```cmd
   scripts\setup-windows.bat
   ```

   这将自动安装：
   - Python 3.x
   - CMake
   - Git
   - Java (用于 ANTLR)
   - Visual Studio Build Tools 或 MinGW

### 手动设置

1. **安装 Python 3.6+**
   - 下载: https://www.python.org/downloads/
   - 确保勾选 "Add Python to PATH"

2. **安装 CMake**
   - 下载: https://cmake.org/download/
   - 选择 Windows Installer

3. **安装 C++ 编译器**
   
   选项 A - Visual Studio (推荐):
   - 下载 Visual Studio Community
   - 安装时选择 "使用 C++ 的桌面开发"
   
   选项 B - MinGW-w64:
   - 下载: https://www.mingw-w64.org/downloads/
   - 添加 bin 目录到 PATH

4. **安装 Java (可选，用于 ANTLR)**
   - 下载: https://adoptium.net/

### Windows 构建命令

```cmd
# 使用便捷脚本（推荐）
build.bat --type Release
pack.bat --all

# 或直接使用 Python
python build.py --type Release
python pack.py --all

# 或使用完整路径
scripts\platform\windows\build.bat --type Release
python scripts\cross-platform\build.py --type Release
```

## Linux 开发环境设置

### Ubuntu/Debian

```bash
# 更新包管理器
sudo apt update

# 安装基础工具
sudo apt install -y build-essential cmake git python3 python3-pip

# 安装 Java (用于 ANTLR)
sudo apt install -y default-jdk

# 安装 ANTLR4 运行时
sudo apt install -y libantlr4-runtime-dev
```

### RHEL/CentOS/Fedora

```bash
# 安装开发工具
sudo dnf groupinstall -y "Development Tools"
sudo dnf install -y cmake git python3 python3-pip

# 安装 Java
sudo dnf install -y java-11-openjdk-devel

# 安装 ANTLR4 运行时
# 可能需要从源码编译或使用第三方仓库
```

### Linux 构建命令

```bash
# 使用 Shell 脚本
./scripts/build_compiler.sh

# 或使用 Python 脚本
python3 scripts/build.py --type Release

# 打包模块
python3 scripts/pack.py --all
```

## macOS 开发环境设置

### 使用 Homebrew

```bash
# 安装 Homebrew (如果未安装)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 安装依赖
brew install cmake python3 openjdk@11

# 安装 ANTLR4
brew install antlr4-cpp-runtime

# 安装 Xcode 命令行工具
xcode-select --install
```

### macOS 构建命令

```bash
# 使用 Python 脚本
python3 scripts/build.py --type Release

# 打包模块
python3 scripts/pack.py --all
```

## 跨平台构建选项

### build.py 选项

```bash
python scripts/build.py [选项]

选项:
  --type {Debug,Release,RelWithDebInfo}
                        构建类型 (默认: Release)
  --generator GENERATOR CMake 生成器
  --jobs JOBS, -j JOBS  并行构建任务数
  --prefix PREFIX       安装前缀
  --clean              清理构建
  --test               运行测试
  --no-parsers         跳过解析器生成
  --install            安装项目
  --target TARGET      构建特定目标
```

### pack.py 选项

```bash
python scripts/pack.py [模块...] [选项]

选项:
  -o OUTPUT, --output OUTPUT
                        输出目录
  -t {cmod,cjmod,auto}, --type {cmod,cjmod,auto}
                        模块类型 (默认: auto)
  --all                打包所有模块
```

## 平台特定注意事项

### Windows

1. **路径分隔符**: Windows 使用反斜杠 `\`，但 CHTL 内部统一使用正斜杠 `/`
2. **文件扩展名**: CJMOD 在 Windows 上生成 `.dll` 文件
3. **权限**: 某些操作可能需要管理员权限

### Linux

1. **库路径**: 可能需要设置 `LD_LIBRARY_PATH`
2. **权限**: 安装到系统目录需要 `sudo`

### macOS

1. **代码签名**: 可能需要对生成的二进制文件进行签名
2. **架构**: 支持 Intel 和 Apple Silicon (通过 Rosetta 2)

## 故障排除

### Windows 常见问题

**问题**: "未找到 Python"
```cmd
# 解决方案: 添加 Python 到 PATH
set PATH=%PATH%;C:\Python39;C:\Python39\Scripts
```

**问题**: "无法找到 vcvarsall.bat"
```cmd
# 解决方案: 使用 Visual Studio 开发者命令提示符
# 或安装 Visual Studio Build Tools
```

### Linux 常见问题

**问题**: "cmake: command not found"
```bash
# 解决方案: 安装 CMake
sudo apt install cmake  # Ubuntu/Debian
sudo dnf install cmake  # Fedora
```

### macOS 常见问题

**问题**: "xcrun: error: invalid active developer path"
```bash
# 解决方案: 安装 Xcode 命令行工具
xcode-select --install
```

## 持续集成

CHTL 项目包含了跨平台 CI 配置：

### GitHub Actions

```yaml
# .github/workflows/cross-platform.yml
name: Cross Platform Build

on: [push, pull_request]

jobs:
  build:
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
    
    runs-on: ${{ matrix.os }}
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.9'
    
    - name: Build
      run: python scripts/build.py --type Release --test
```

## 最佳实践

1. **使用 Python 脚本**: 提供最一致的跨平台体验
2. **测试所有平台**: 在目标平台上进行测试
3. **使用 CI/CD**: 自动化跨平台构建和测试
4. **文档化平台差异**: 记录任何平台特定的行为

## 贡献指南

如果您想为 CHTL 的跨平台支持做出贡献：

1. 确保代码在所有支持的平台上编译
2. 避免使用平台特定的 API
3. 使用条件编译处理平台差异
4. 更新相关文档

## 总结

CHTL 的跨平台支持让开发者可以在任何主流操作系统上使用。通过 Python 脚本和自动化工具，我们努力提供一致且简单的开发体验。如果遇到任何问题，请查看故障排除部分或在 GitHub 上提交 issue。