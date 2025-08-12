#!/bin/bash

# CHTL 测试运行脚本

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}CHTL Test Runner${NC}"
echo "=================="

# 检查构建目录
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${YELLOW}Build directory not found. Creating and building...${NC}"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake ..
    make -j$(nproc)
fi

# 构建测试
cd "$BUILD_DIR"
echo -e "${YELLOW}Building tests...${NC}"
make chtl_tests

# 运行测试
echo -e "${YELLOW}Running tests...${NC}"

# 运行单元测试
if [ -f "tests/chtl_tests" ]; then
    ./tests/chtl_tests --gtest_color=yes "$@"
else
    echo -e "${RED}Test executable not found!${NC}"
    exit 1
fi

# 生成测试报告（如果安装了 gcov）
if command -v gcov &> /dev/null; then
    echo -e "${YELLOW}Generating coverage report...${NC}"
    # TODO: 添加覆盖率报告生成
fi

echo -e "${GREEN}Test run completed!${NC}"