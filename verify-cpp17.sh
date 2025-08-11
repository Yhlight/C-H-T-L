#!/bin/bash

echo "=== C++17 Compatibility Verification ==="
echo

# 要测试的关键文件
files=(
    "src/Loader/ImportResolver.cpp"
    "src/CJmod/CJmodLoader.cpp"
    "src/CJmod/CJmodProcessor.cpp"
    "src/CJmod/CJmodRegistry.cpp"
    "src/CJmod/CHTLJSProcessor.cpp"
)

success=true

for file in "${files[@]}"; do
    echo -n "Testing $file... "
    if g++ -std=c++17 -I./include -c "$file" -o /tmp/test.o 2>/tmp/errors.txt; then
        echo "✓ OK"
    else
        echo "✗ FAILED"
        success=false
        echo "First few errors:"
        head -5 /tmp/errors.txt
        echo
    fi
done

# 检查 C++20 特性
echo
echo "=== Checking for C++20 features ==="

patterns=(
    "\.ends_with\("
    "\.starts_with\("
    "\.contains\("
    "std::span"
    "std::ranges"
    "co_await"
    "co_yield"
    "co_return"
    "concept\s"
    "requires\s"
    "<=>|spaceship"
    "std::format"
    "\[\[likely\]\]"
    "\[\[unlikely\]\]"
)

for pattern in "${patterns[@]}"; do
    echo -n "Checking for $pattern... "
    count=$(grep -r "$pattern" src include 2>/dev/null | grep -v "node_modules" | wc -l)
    if [ $count -eq 0 ]; then
        echo "✓ None found"
    else
        echo "✗ Found $count occurrences"
        success=false
    fi
done

# 清理
rm -f /tmp/test.o /tmp/errors.txt

echo
if $success; then
    echo "✅ All checks passed! The code is C++17 compatible."
else
    echo "❌ Some checks failed. Please review the issues above."
fi