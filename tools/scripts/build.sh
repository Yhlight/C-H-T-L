#!/bin/bash

# CHTL构建脚本

set -e  # 遇到错误立即退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 打印带颜色的消息
print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 默认值
BUILD_TYPE="Release"
BUILD_DIR="build"
INSTALL_PREFIX="/usr/local"
CLEAN_BUILD=false
RUN_TESTS=true

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        --prefix)
            INSTALL_PREFIX="$2"
            shift 2
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        --no-tests)
            RUN_TESTS=false
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --debug          Build in debug mode"
            echo "  --build-dir DIR  Build directory (default: build)"
            echo "  --prefix PATH    Install prefix (default: /usr/local)"
            echo "  --clean          Clean build"
            echo "  --no-tests       Skip running tests"
            echo "  -h, --help       Show this help message"
            exit 0
            ;;
        *)
            print_error "Unknown option: $1"
            exit 1
            ;;
    esac
done

# 打印构建配置
print_info "CHTL Build Configuration:"
print_info "  Build Type: $BUILD_TYPE"
print_info "  Build Directory: $BUILD_DIR"
print_info "  Install Prefix: $INSTALL_PREFIX"
print_info "  Clean Build: $CLEAN_BUILD"
print_info "  Run Tests: $RUN_TESTS"

# 清理构建目录
if [ "$CLEAN_BUILD" = true ]; then
    print_info "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# 创建构建目录
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 配置
print_info "Configuring..."
cmake .. \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# 构建
print_info "Building..."
cmake --build . --parallel $(nproc)

# 运行测试
if [ "$RUN_TESTS" = true ]; then
    print_info "Running tests..."
    ctest --output-on-failure || print_warn "Some tests failed"
fi

print_info "Build completed successfully!"
print_info "To install, run: cd $BUILD_DIR && sudo make install"