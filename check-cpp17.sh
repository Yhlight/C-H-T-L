#!/bin/bash

echo "Checking C++17 compatibility..."

# 编译选项
CXX="g++"
CXXFLAGS="-std=c++17 -I./include -c"

# 存储有问题的文件
problem_files=()

# 测试编译所有 cpp 文件
for file in $(find src -name "*.cpp"); do
    echo -n "Checking $file... "
    if $CXX $CXXFLAGS "$file" -o /tmp/test.o 2>/tmp/compile_errors.txt; then
        echo "OK"
    else
        echo "FAILED"
        problem_files+=("$file")
        echo "Errors:"
        grep -i "error" /tmp/compile_errors.txt | head -5
        echo "---"
    fi
done

# 清理
rm -f /tmp/test.o /tmp/compile_errors.txt

# 报告结果
echo ""
echo "=== Summary ==="
if [ ${#problem_files[@]} -eq 0 ]; then
    echo "All files are C++17 compatible!"
else
    echo "Files with problems:"
    for file in "${problem_files[@]}"; do
        echo "  - $file"
    done
fi