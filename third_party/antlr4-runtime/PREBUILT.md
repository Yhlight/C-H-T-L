# Prebuilt ANTLR4 Runtime

为了方便用户，我们提供了预构建的ANTLR4运行时库。

## 下载预构建版本

从以下位置下载适合您平台的预构建包：

- [Linux x64](https://github.com/Yhlight/C-H-T-L/releases/download/antlr4-runtime/antlr4-runtime-linux-x64.tar.gz)
- [macOS x64](https://github.com/Yhlight/C-H-T-L/releases/download/antlr4-runtime/antlr4-runtime-macos-x64.tar.gz)
- [macOS ARM64](https://github.com/Yhlight/C-H-T-L/releases/download/antlr4-runtime/antlr4-runtime-macos-arm64.tar.gz)
- [Windows x64](https://github.com/Yhlight/C-H-T-L/releases/download/antlr4-runtime/antlr4-runtime-windows-x64.zip)

## 安装步骤

1. 下载对应平台的压缩包
2. 解压到 `third_party/antlr4-runtime/` 目录
3. 确保以下目录结构：
   ```
   third_party/antlr4-runtime/
   ├── include/        # 头文件
   ├── lib/           # 库文件
   └── bin/           # DLL文件 (仅Windows)
   ```

## 从源码构建

如果预构建版本不适合您的平台，请从源码构建：

```bash
# Unix/Linux/macOS
cd third_party/antlr4-runtime
./download_and_build.sh

# Windows
cd third_party\antlr4-runtime
build_windows.bat
```