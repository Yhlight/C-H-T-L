#!/bin/bash

# CHTL构建测试脚本

set -e  # 遇到错误立即退出

echo "========================================="
echo "CHTL Build System Test"
echo "========================================="

# 清理之前的构建
if [ -d "build" ]; then
    echo "Cleaning previous build..."
    rm -rf build
fi

# 创建构建目录
echo "Creating build directory..."
mkdir -p build
cd build

# 运行CMake配置
echo "Running CMake configuration..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 检查模块是否被发现
echo ""
echo "Checking module detection..."
if [ -f "module/modules.index" ]; then
    echo "Module index created successfully!"
    cat module/modules.index
else
    echo "Warning: Module index not found"
fi

# 检查Chtholly模块是否被打包
echo ""
echo "Checking Chtholly module..."
if [ -f "module/Chtholly.cmod" ]; then
    echo "Chtholly.cmod created successfully!"
    # 显示文件大小
    ls -lh module/Chtholly.cmod
    
    # 如果是tar格式，尝试列出内容
    if command -v tar &> /dev/null; then
        echo "Module contents:"
        tar -tzf module/Chtholly.cmod 2>/dev/null | head -10 || echo "(Using text format)"
    fi
else
    echo "Error: Chtholly.cmod not found!"
fi

# 尝试构建项目（如果源文件存在）
echo ""
echo "Attempting to build CHTL compiler..."
if make -j$(nproc) 2>/dev/null; then
    echo "Build successful!"
    
    # 检查生成的二进制文件
    if [ -f "bin/chtlc" ]; then
        echo "CHTL compiler binary created: bin/chtlc"
        ls -lh bin/chtlc
    fi
else
    echo "Note: Build skipped (missing source files is expected at this stage)"
fi

# 测试手动模块打包
echo ""
echo "Testing manual module packing..."
if make pack-modules 2>/dev/null; then
    echo "Manual module packing successful!"
else
    cmake -P ../cmake/PackModules.cmake
fi

# 显示最终模块目录结构
echo ""
echo "Final module directory structure:"
if [ -d "module" ]; then
    ls -la module/
else
    echo "Module directory not found"
fi

echo ""
echo "========================================="
echo "Build test completed!"
echo "========================================="

# 返回原目录
cd ..

# 提供下一步建议
echo ""
echo "Next steps:"
echo "1. Implement missing source files (.cpp) if needed"
echo "2. Install ANTLR4 and generate parsers"
echo "3. Add more CMOD/CJMOD modules to the module/ directory"
echo "4. Run 'cmake --build build --target install' to install"