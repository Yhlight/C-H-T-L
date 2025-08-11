#!/bin/bash

# CHTL 跨平台编译脚本
# 需要安装相应的交叉编译工具链

set -e

echo "CHTL 跨平台编译脚本"
echo "===================="

# 定义输出目录
OUTPUT_BASE="/workspace/vscode-extension/chtl-lang/compilers"
BUILD_DIR="/workspace/build-cross"

# 创建输出目录
mkdir -p "$OUTPUT_BASE"/{linux-x64,linux-arm64,darwin-x64,darwin-arm64,win32-x64}

# 检查并安装交叉编译工具
check_and_install_tools() {
    echo "检查交叉编译工具..."
    
    # 检查 mingw (Windows 交叉编译)
    if ! command -v x86_64-w64-mingw32-g++ &> /dev/null; then
        echo "安装 MinGW 交叉编译工具..."
        sudo apt-get update
        sudo apt-get install -y mingw-w64
    fi
    
    # 检查 osxcross (macOS 交叉编译)
    if [ ! -d "/opt/osxcross" ]; then
        echo "提示: macOS 交叉编译需要手动安装 osxcross"
        echo "访问: https://github.com/tpoechtrager/osxcross"
    fi
}

# 编译函数
compile_for_platform() {
    local platform=$1
    local arch=$2
    local compiler=$3
    local cmake_toolchain=$4
    local output_name=$5
    
    echo ""
    echo "编译 $platform-$arch..."
    
    # 创建构建目录
    local build_path="$BUILD_DIR/$platform-$arch"
    rm -rf "$build_path"
    mkdir -p "$build_path"
    cd "$build_path"
    
    # 配置 CMake
    if [ -n "$cmake_toolchain" ]; then
        cmake /workspace -DCMAKE_TOOLCHAIN_FILE="$cmake_toolchain" -DCMAKE_BUILD_TYPE=Release
    else
        cmake /workspace -DCMAKE_CXX_COMPILER="$compiler" -DCMAKE_BUILD_TYPE=Release
    fi
    
    # 编译
    make -j$(nproc)
    
    # 复制到输出目录
    if [ -f "chtl" ]; then
        cp chtl "$OUTPUT_BASE/$platform-$arch/$output_name"
        echo "✓ 成功: $platform-$arch"
    else
        echo "✗ 失败: $platform-$arch"
        return 1
    fi
}

# 创建 CMake 工具链文件
create_toolchain_files() {
    echo "创建 CMake 工具链文件..."
    
    # Windows x64 工具链
    cat > /tmp/mingw-w64-x86_64.cmake << 'EOF'
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Windows 特定标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
EOF

    # ARM64 Linux 工具链
    cat > /tmp/aarch64-linux-gnu.cmake << 'EOF'
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
EOF
}

# 主函数
main() {
    check_and_install_tools
    create_toolchain_files
    
    # Linux x64 (本地编译)
    compile_for_platform "linux" "x64" "g++" "" "chtl"
    
    # Linux ARM64
    if command -v aarch64-linux-gnu-g++ &> /dev/null; then
        compile_for_platform "linux" "arm64" "" "/tmp/aarch64-linux-gnu.cmake" "chtl"
    else
        echo "跳过 Linux ARM64: 未找到交叉编译器"
    fi
    
    # Windows x64
    compile_for_platform "win32" "x64" "" "/tmp/mingw-w64-x86_64.cmake" "chtl.exe"
    
    # macOS (需要 osxcross)
    if [ -d "/opt/osxcross" ]; then
        export PATH="/opt/osxcross/bin:$PATH"
        compile_for_platform "darwin" "x64" "o64-clang++" "" "chtl"
        compile_for_platform "darwin" "arm64" "oa64-clang++" "" "chtl"
    else
        echo "跳过 macOS: 未安装 osxcross"
    fi
    
    echo ""
    echo "编译完成！"
    echo "输出文件位于: $OUTPUT_BASE"
    ls -la "$OUTPUT_BASE"/*
}

# 运行主函数
main