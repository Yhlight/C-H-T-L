#!/bin/bash

# CHTL编译器构建脚本

set -e

echo "🚀 开始构建CHTL编译器..."

# 检查系统要求
echo "📋 检查系统要求..."

# 检查C++编译器
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "❌ 错误: 未找到C++编译器 (g++ 或 clang++)"
    exit 1
fi

# 检查CMake
if ! command -v cmake &> /dev/null; then
    echo "❌ 错误: 未找到CMake"
    echo "请安装CMake: https://cmake.org/install/"
    exit 1
fi

# 检查ANTLR4运行时
if ! pkg-config --exists antlr4-runtime 2>/dev/null; then
    echo "⚠️  警告: 未找到ANTLR4运行时库"
    echo "请安装ANTLR4运行时库:"
    echo "  Ubuntu/Debian: sudo apt-get install antlr4-runtime"
    echo "  macOS: brew install antlr4-runtime"
    echo "  Windows: vcpkg install antlr4-runtime"
    echo ""
    echo "继续构建可能会失败..."
    read -p "是否继续? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# 创建构建目录
echo "📁 创建构建目录..."
rm -rf build
mkdir -p build
cd build

# 配置项目
echo "⚙️  配置项目..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译项目
echo "🔨 编译项目..."
make -j$(nproc)

echo "✅ 构建完成!"

# 显示可执行文件信息
if [ -f chtl-compiler ]; then
    echo ""
    echo "📦 构建产物:"
    echo "  - 可执行文件: $(pwd)/chtl-compiler"
    echo "  - 大小: $(du -h chtl-compiler | cut -f1)"
    echo ""
    echo "🧪 测试编译器..."
    ./chtl-compiler --version
    
    echo ""
    echo "🎉 构建成功! 现在可以使用以下命令编译CHTL文件:"
    echo "  ./chtl-compiler input.chtl"
    echo "  ./chtl-compiler --help"
else
    echo "❌ 构建失败: 未找到可执行文件"
    exit 1
fi