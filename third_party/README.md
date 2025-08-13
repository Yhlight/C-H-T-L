# Third Party Libraries

此目录包含CHTL项目所需的第三方库。

## ANTLR4 Runtime (4.13.1)

ANTLR4运行时库用于CSS和JavaScript解析器的支持。

### 目录结构
```
antlr4-runtime/
├── include/        # ANTLR4头文件
├── lib/           # 预编译的库文件
└── CMakeLists.txt # CMake集成文件
```

### 支持的平台
- Linux (x64)
- macOS (x64, arm64)
- Windows (x64)

### 许可证
ANTLR4使用BSD 3-Clause许可证。

## 构建说明

如果需要重新构建ANTLR4运行时：

```bash
cd antlr4-runtime
./build.sh  # Unix/Linux/macOS
build.bat   # Windows
```