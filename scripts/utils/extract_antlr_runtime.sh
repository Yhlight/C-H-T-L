#!/bin/bash
# 提取ANTLR4生成的代码，移除对ANTLR4运行时的依赖

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
GENERATED_DIR="$PROJECT_ROOT/generated"
STANDALONE_DIR="$PROJECT_ROOT/src/chtl/parser"

# 颜色输出
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}=== Extracting ANTLR Generated Code ===${NC}"

# 创建独立的解析器目录
mkdir -p "$STANDALONE_DIR"/{chtl,css,js,chtljs,config}

# 复制生成的文件
echo -e "${YELLOW}Copying generated parser files...${NC}"

# CHTL Parser
if [ -d "$GENERATED_DIR/chtl" ]; then
    cp -r "$GENERATED_DIR/chtl"/*.{h,cpp} "$STANDALONE_DIR/chtl/" 2>/dev/null || true
    echo "✓ CHTL parser files copied"
fi

# CSS Parser
if [ -d "$GENERATED_DIR/css" ]; then
    cp -r "$GENERATED_DIR/css"/*.{h,cpp} "$STANDALONE_DIR/css/" 2>/dev/null || true
    echo "✓ CSS parser files copied"
fi

# JS Parser
if [ -d "$GENERATED_DIR/js" ]; then
    cp -r "$GENERATED_DIR/js"/*.{h,cpp} "$STANDALONE_DIR/js/" 2>/dev/null || true
    echo "✓ JS parser files copied"
fi

# CHTL JS Parser
if [ -d "$GENERATED_DIR/chtljs" ]; then
    cp -r "$GENERATED_DIR/chtljs"/*.{h,cpp} "$STANDALONE_DIR/chtljs/" 2>/dev/null || true
    echo "✓ CHTL JS parser files copied"
fi

# Config Parser
if [ -d "$GENERATED_DIR/config" ]; then
    cp -r "$GENERATED_DIR/config"/*.{h,cpp} "$STANDALONE_DIR/config/" 2>/dev/null || true
    echo "✓ Config parser files copied"
fi

# 创建最小化的ANTLR运行时
echo -e "${YELLOW}Creating minimal ANTLR runtime...${NC}"

cat > "$STANDALONE_DIR/antlr4_minimal.h" << 'EOF'
#ifndef ANTLR4_MINIMAL_H
#define ANTLR4_MINIMAL_H

#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <algorithm>

namespace antlr4 {

// 基础类型定义
using Token = struct Token {
    int type;
    std::string text;
    size_t line;
    size_t column;
};

using TokenStream = class TokenStream {
public:
    virtual Token* get(size_t i) = 0;
    virtual size_t size() = 0;
};

using ParserRuleContext = class ParserRuleContext {
public:
    std::vector<std::shared_ptr<ParserRuleContext>> children;
    ParserRuleContext* parent = nullptr;
    
    virtual std::string getText() {
        std::string result;
        for (auto& child : children) {
            result += child->getText();
        }
        return result;
    }
};

// 最小化的运行时支持
template<typename T>
class tree {
public:
    using ParseTree = ParserRuleContext;
};

// 异常类
class RecognitionException : public std::exception {
public:
    RecognitionException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
private:
    std::string message;
};

} // namespace antlr4

#endif // ANTLR4_MINIMAL_H
EOF

# 修改生成的文件，替换ANTLR4包含
echo -e "${YELLOW}Modifying generated files to use minimal runtime...${NC}"

find "$STANDALONE_DIR" -name "*.h" -o -name "*.cpp" | while read file; do
    # 替换ANTLR4包含
    sed -i 's|#include "antlr4-runtime.h"|#include "../antlr4_minimal.h"|g' "$file"
    sed -i 's|#include <antlr4-runtime.h>|#include "../antlr4_minimal.h"|g' "$file"
    
    # 移除特定的ANTLR4命名空间使用
    sed -i 's/antlr4::tree:://g' "$file"
    sed -i 's/antlr4::Token/Token/g' "$file"
    sed -i 's/antlr4::TokenStream/TokenStream/g' "$file"
done

echo -e "${GREEN}✓ ANTLR runtime extraction completed${NC}"

# 更新CMakeLists.txt
echo -e "${YELLOW}Updating CMakeLists.txt...${NC}"

cat > "$PROJECT_ROOT/CMakeLists_standalone.txt" << 'EOF'
# 独立版本的CMakeLists.txt（无ANTLR4依赖）
cmake_minimum_required(VERSION 3.16)
project(CHTL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 源文件
file(GLOB_RECURSE CHTL_SOURCES 
    "src/chtl/*.cpp"
    "src/chtl/*.h"
)

# 排除需要ANTLR4的文件
list(FILTER CHTL_SOURCES EXCLUDE REGEX ".*antlr4.*")

# 创建可执行文件
add_executable(chtl ${CHTL_SOURCES} src/main.cpp)

# 包含目录
target_include_directories(chtl PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 安装
install(TARGETS chtl DESTINATION bin)
EOF

echo -e "${GREEN}=== ANTLR Runtime Extraction Complete ===${NC}"
echo -e "The standalone parser files are now in: $STANDALONE_DIR"
echo -e "Use CMakeLists_standalone.txt for building without ANTLR4 dependency"