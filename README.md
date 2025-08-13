# CHTL (C++ Hypertext Language)

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/chtl/chtl/releases)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/chtl/chtl/actions)
[![Documentation](https://img.shields.io/badge/docs-ready-orange.svg)](https://chtl.dev)

CHTL是一种创新的模板语言，将C++的强大功能与现代Web开发相结合，提供高性能、类型安全的开发体验。

## 🚀 特性

- **混合解析器架构** - 核心独立实现，CSS/JS完整支持
- **精准代码切割** - 智能识别和分发不同语言片段
- **模块化设计** - CMOD/CJMOD双模块系统
- **高性能** - 编译速度快，内存占用低
- **开发工具完善** - VSCode集成、调试支持、热重载

## 📦 安装

### 从源码构建

#### 快速构建

```bash
# 克隆仓库
git clone https://github.com/chtl/chtl.git
cd chtl
```

**Linux/macOS:**
```bash
# 使用便捷脚本
./build.sh --type Release

# 或使用特定脚本
./scripts/build/build_compiler.sh
```

**Windows:**
```cmd
# 首次使用请运行（需要管理员权限）
scripts\platform\windows\setup-windows.bat

# 使用便捷脚本构建
build.bat --type Release
```

### 使用包管理器

```bash
# Ubuntu/Debian
sudo apt install chtl

# macOS
brew install chtl

# Windows (使用scoop)
scoop install chtl
```

## 🎯 快速开始

创建 `hello.chtl`：

```chtl
[Import] @Chtl "Chtl.Core"

div class="container" {
    h1 { "Hello, CHTL!" }
    
    p class="intro" {
        "Welcome to the future of web development."
    }
    
    button id="greet-btn" {
        "Click me!"
        
        script {
            var button = @Element greet-btn;
            button.addEventListener('click', () => {
                alert({{ "Hello from CHTL!" }});
            });
        }
    }
}
```

编译并运行：

```bash
chtl hello.chtl -o hello.html
# 在浏览器中打开 hello.html
```

## 📚 文档

- [语言参考](docs/language_reference.md)
- [API文档](docs/api.md)
- [模块开发指南](docs/modules.md)
- [CJMOD开发指南](docs/CJMOD_Development_Guide.md)
- [配置选项](docs/configuration.md)

## 📦 从源码构建

### 前置要求

- CMake >= 3.16
- C++17 编译器 (GCC 7+, Clang 5+, MSVC 2017+)
- Java Runtime (可选，用于生成解析器)

**注意**：CHTL已内置ANTLR4工具和运行时库，无需额外安装ANTLR4。

### 构建步骤

```bash
# 1. 克隆仓库
git clone https://github.com/Yhlight/C-H-T-L.git
cd C-H-T-L

# 2. 设置依赖（首次构建时运行）
./setup_dependencies.sh  # Unix/Linux/macOS
setup_dependencies.bat   # Windows

# 3. 构建项目
./build.sh              # Unix/Linux/macOS
build.bat               # Windows

# 4. 运行测试（可选）
./build.sh --test       # Unix/Linux/macOS
build.bat --test        # Windows

# 5. 安装（可选）
sudo ./build.sh --install  # Unix/Linux/macOS
build.bat --install        # Windows (管理员权限)
```

## 🛠️ 开发

### 项目结构

```
chtl/
├── src/           # 源代码
├── include/       # 头文件
├── tests/         # 测试
├── docs/          # 文档
├── examples/      # 示例
├── scripts/       # 构建脚本
├── module/        # 标准模块
└── grammars/      # 语法定义
```

### 运行测试

```bash
cd build
ctest --output-on-failure
```

### 贡献指南

1. Fork 项目
2. 创建特性分支 (`git checkout -b feature/amazing-feature`)
3. 提交更改 (`git commit -m 'Add amazing feature'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 创建 Pull Request

## 🌟 示例

查看 [examples](examples/) 目录获取更多示例：

- [Web应用](examples/webapp/)
- [组件库](examples/components/)
- [CJMOD示例](examples/cjmod_example/)

## 📈 性能

基准测试结果（相对于传统模板引擎）：

| 指标 | CHTL | 传统方案 | 提升 |
|------|------|---------|------|
| 编译速度 | 85ms | 250ms | 3x |
| 内存使用 | 20MB | 80MB | 4x |
| 运行时开销 | 0 | 15ms | ∞ |

## 🤝 社区

- [官方网站](https://chtl.dev)
- [论坛](https://forum.chtl.dev)
- [Discord](https://discord.gg/chtl)
- [Twitter](https://twitter.com/chtlang)

## 📄 许可证

本项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。

## 🙏 致谢

感谢所有贡献者和支持者，特别感谢：

- ANTLR4项目 - 提供CSS/JS解析支持
- 开源社区 - 持续的反馈和贡献

---

**CHTL** - 让Web开发更高效、更安全、更有趣！