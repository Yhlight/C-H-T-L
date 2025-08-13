#!/bin/bash

# CHTL项目清理脚本
# 用于清理构建产物和临时文件，使项目达到可发布状态

echo "=== CHTL项目清理脚本 ==="
echo "清理构建产物和临时文件..."

# 进入项目根目录
cd "$(dirname "$0")/.." || exit 1

# 1. 清理构建目录
if [ -d "build" ]; then
    echo "清理build目录..."
    rm -rf build/*
fi

# 2. 清理生成的解析器文件（保留语法文件）
if [ -d "generated" ]; then
    echo "清理generated目录..."
    rm -rf generated
fi

# 3. 清理输出目录
if [ -d "output" ]; then
    echo "清理output目录..."
    rm -rf output/*
fi

# 4. 清理临时文件
echo "清理临时文件..."
find . -type f \( -name "*.o" -o -name "*.a" -o -name "*.so" \
    -o -name "*.dylib" -o -name "*.exe" -o -name "*.dll" \
    -o -name "*.log" -o -name "*.tmp" -o -name "*~" \
    -o -name ".DS_Store" -o -name "*.swp" \) -delete

# 5. 清理测试产物
if [ -d "test" ]; then
    find test -type f -name "*.out" -o -name "*.result" -delete
fi

# 6. 清理IDE临时文件
find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
find . -type f -name "*.pyc" -delete

# 7. 整理文档
echo "整理文档..."
mkdir -p docs/internal

# 移动内部开发文档到docs/internal
for doc in *_DOCS.md; do
    if [ -f "$doc" ]; then
        mv "$doc" docs/internal/ 2>/dev/null || true
    fi
done

# 移动临时的CMakeLists备份
if ls CMakeLists_*.txt 1> /dev/null 2>&1; then
    mkdir -p docs/internal/cmake_backups
    mv CMakeLists_*.txt docs/internal/cmake_backups/
fi

# 8. 确保必要的目录存在
mkdir -p build
mkdir -p output
mkdir -p examples
mkdir -p tests/unit
mkdir -p tests/integration

# 9. 创建.gitkeep文件保持空目录
touch build/.gitkeep
touch output/.gitkeep

# 10. 生成清理报告
echo ""
echo "=== 清理完成 ==="
echo "项目结构："
echo "- src/        源代码"
echo "- include/    头文件"
echo "- tests/      测试代码"
echo "- docs/       文档"
echo "- examples/   示例"
echo "- scripts/    脚本"
echo "- module/     模块"
echo "- grammars/   语法文件"
echo ""
echo "项目已清理至可发布状态！"