# CHTL构建系统

## 概述

CHTL项目使用CMake作为主要构建系统，提供了灵活的构建配置和跨平台支持。

## 构建脚本

项目提供了一系列Shell脚本来简化构建过程：

### 1. 统一构建脚本 (`scripts/build_all.sh`)

一键构建整个项目：

```bash
./scripts/build_all.sh [选项]

选项：
  -t, --type TYPE        构建类型 (Debug|Release) [默认: Debug]
  -j, --jobs N          并行编译任务数 [默认: CPU核心数]
  -c, --clean           清理后重新构建
  --test                运行所有测试
  -v, --verbose         显示详细输出
  
  --compiler-only       只构建编译器
  --ide-only           只构建IDE
  --modules-only       只构建模块
```

### 2. 编译器构建脚本 (`scripts/build_compiler.sh`)

专门构建CHTL编译器：

```bash
./scripts/build_compiler.sh [选项]

主要功能：
- 检查依赖（CMake、ANTLR4等）
- 生成ANTLR解析器
- 编译CHTL编译器
- 可选安装到系统
```

### 3. 模块打包脚本

#### CMOD打包 (`scripts/pack_cmod.sh`)
```bash
./scripts/pack_cmod.sh [选项] <模块路径>

# 示例
./scripts/pack_cmod.sh module/Chtholly
```

#### CJMOD打包 (`scripts/pack_cjmod.sh`)
```bash
./scripts/pack_cjmod.sh [选项] <模块路径>

# 示例
./scripts/pack_cjmod.sh module/MyCJMod
```

#### 统一打包 (`scripts/pack_modules.sh`)
```bash
./scripts/pack_modules.sh [选项]

# 自动扫描并打包所有模块
```

### 4. IDE构建脚本 (`scripts/build_ide.sh`)

构建CHTL IDE（基于Qt5）：

```bash
./scripts/build_ide.sh [选项]

特性：
- 检查Qt5依赖
- 准备VSCode编辑器组件
- 支持跨平台打包
```

## CMake配置

### 主CMakeLists.txt

项目根目录的CMakeLists.txt包含：

```cmake
cmake_minimum_required(VERSION 3.10)
project(CHTL VERSION 1.0.0)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 构建选项
option(BUILD_TESTS "Build tests" ON)
option(BUILD_IDE "Build IDE" OFF)
option(GENERATE_PARSERS "Generate ANTLR parsers" ON)

# 子目录
add_subdirectory(src)
add_subdirectory(ide)
add_subdirectory(test)
```

### 编译器配置

```cmake
# src/CMakeLists.txt
add_executable(chtlc
    main.cpp
    chtl/CHTLCompiler.cpp
    chtl/CHTLStateMachine.cpp
    # ... 其他源文件
)

target_link_libraries(chtlc
    antlr4-runtime
    ${CMAKE_DL_LIBS}
)
```

## 构建类型

### Debug构建
- 包含调试符号 (`-g`)
- 禁用优化 (`-O0`)
- 启用断言
- 生成compile_commands.json

### Release构建
- 启用优化 (`-O3`)
- 去除调试符号
- 禁用断言
- 代码体积最小化

### RelWithDebInfo构建
- 启用优化 (`-O2`)
- 保留调试符号
- 适合性能分析

## 依赖管理

### 必需依赖
- CMake 3.10+
- C++17编译器
- ANTLR 4.13.1

### 可选依赖
- Qt5（IDE）
- clang-format（代码格式化）
- ctest（单元测试）

### 安装依赖

Ubuntu/Debian:
```bash
sudo apt-get install \
    cmake build-essential \
    antlr4 libantlr4-runtime-dev \
    qt5-default libqt5webengine5-dev
```

macOS:
```bash
brew install cmake antlr4-cpp-runtime qt@5
```

## 构建目录结构

```
build/
├── bin/                # 可执行文件
│   └── chtlc          # CHTL编译器
├── lib/               # 库文件
├── module/            # 打包的模块
│   ├── *.cmod        # CMOD模块
│   └── *.cjmod       # CJMOD模块
├── generated/         # ANTLR生成的文件
└── CMakeCache.txt     # CMake缓存
```

## 高级配置

### 自定义ANTLR路径

```bash
cmake -DANTLR4_JAR_LOCATION=/path/to/antlr.jar ..
```

### 交叉编译

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
```

### 静态链接

```bash
cmake -DBUILD_SHARED_LIBS=OFF ..
```

## 故障排除

### ANTLR找不到
确保ANTLR jar文件在以下位置之一：
- `/usr/local/lib/antlr-4.13.1-complete.jar`
- `$HOME/antlr4/antlr-4.13.1-complete.jar`

### 链接错误
检查是否安装了所有运行时库：
```bash
ldd build/bin/chtlc
```

### CMake版本过低
升级CMake：
```bash
# Ubuntu/Debian
sudo apt-get install cmake

# 或从源码编译最新版
```

## 持续集成

项目支持GitHub Actions和GitLab CI：

### GitHub Actions
```yaml
# .github/workflows/build.yml
name: Build
on: [push, pull_request]
jobs:
  build:
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, macos-latest]
    steps:
      - uses: actions/checkout@v2
      - name: Build
        run: ./scripts/build_all.sh -t Release
```

### GitLab CI
```yaml
# .gitlab-ci.yml
build:
  stage: build
  script:
    - ./scripts/build_all.sh -t Release
  artifacts:
    paths:
      - build/bin/
```