#!/bin/bash
# CHTL CJMOD打包脚本

# 脚本目录和根目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$ROOT_DIR"

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# 打印函数
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 默认参数
OUTPUT_DIR="output"
BUILD_TYPE="Release"
VERBOSE=0
MODULE_PATH=""
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 显示帮助
show_help() {
    cat << EOF
CHTL CJMOD打包脚本

用法: $0 <模块路径> [选项]

选项:
  --help, -h          显示帮助信息
  --output DIR, -o    输出目录 [默认: output]
  --build-type TYPE   构建类型 (Debug/Release) [默认: Release]
  --jobs N, -j N      并行编译任务数 [默认: $JOBS]
  --verbose, -v       显示详细输出

示例:
  $0 src/module/Chtholly                    # 打包Chtholly模块的CJMOD部分
  $0 src/module/MyModule -o dist            # 打包到dist目录
  $0 src/module/MyModule --build-type Debug # Debug构建

支持的模块结构:
  1. 混合模块: ModuleName/CJMOD/ModuleName/
  2. 纯CJMOD模块: ModuleName/src/ (包含C++文件)

EOF
    exit 0
}

# 解析参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            ;;
        -o|--output)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        --build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=1
            shift
            ;;
        *)
            MODULE_PATH="$1"
            shift
            ;;
    esac
done

# 检查参数
if [ -z "$MODULE_PATH" ]; then
    print_error "请指定模块路径"
    show_help
fi

if [ ! -d "$MODULE_PATH" ]; then
    print_error "模块路径不存在: $MODULE_PATH"
    exit 1
fi

# 检查依赖
if ! command -v cmake &> /dev/null; then
    print_error "未找到CMake，CJMOD编译需要CMake"
    exit 1
fi

if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    print_error "未找到C++编译器"
    exit 1
fi

# 获取模块名称
MODULE_NAME=$(basename "$MODULE_PATH")

# 查找实际的CJMOD路径
ACTUAL_CJMOD_PATH=""

# 检查混合模块结构
if [ -d "$MODULE_PATH/CJMOD/$MODULE_NAME" ]; then
    ACTUAL_CJMOD_PATH="$MODULE_PATH/CJMOD/$MODULE_NAME"
    print_info "检测到混合模块结构"
# 检查纯CJMOD模块结构
elif [ -d "$MODULE_PATH/src" ]; then
    # 确认是CJMOD模块（包含C++文件）
    if find "$MODULE_PATH/src" -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" | grep -q .; then
        ACTUAL_CJMOD_PATH="$MODULE_PATH"
        print_info "检测到纯CJMOD模块结构"
    fi
fi

if [ -z "$ACTUAL_CJMOD_PATH" ]; then
    print_error "未找到有效的CJMOD模块结构"
    print_info "请确保模块包含以下结构之一:"
    print_info "  1. $MODULE_PATH/CJMOD/$MODULE_NAME/src/ (包含C++文件)"
    print_info "  2. $MODULE_PATH/src/ (包含C++文件)"
    exit 1
fi

# 验证模块结构
if [ ! -d "$ACTUAL_CJMOD_PATH/src" ]; then
    print_error "未找到src目录: $ACTUAL_CJMOD_PATH/src"
    exit 1
fi

# 查找C++源文件
CPP_FILES=$(find "$ACTUAL_CJMOD_PATH/src" -name "*.cpp" -o -name "*.cc" -o -name "*.cxx")
if [ -z "$CPP_FILES" ]; then
    print_error "未找到C++源文件"
    exit 1
fi

# 查找info文件
INFO_FILE=""
if [ -d "$ACTUAL_CJMOD_PATH/info" ]; then
    for file in "$ACTUAL_CJMOD_PATH/info"/*.chtl; do
        if [ -f "$file" ]; then
            INFO_FILE="$file"
            break
        fi
    done
fi

# 从info文件名获取模块名（如果存在）
if [ -n "$INFO_FILE" ]; then
    REAL_MODULE_NAME=$(basename "$INFO_FILE" .chtl)
else
    REAL_MODULE_NAME="$MODULE_NAME"
fi

print_info "模块名称: $REAL_MODULE_NAME"
print_info "构建类型: $BUILD_TYPE"

# 创建构建目录
BUILD_DIR=$(mktemp -d)
print_info "构建目录: $BUILD_DIR"

# 创建CMakeLists.txt
cat > "$BUILD_DIR/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.16)
project($REAL_MODULE_NAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 查找源文件
file(GLOB_RECURSE SOURCES "$ACTUAL_CJMOD_PATH/src/*.cpp" "$ACTUAL_CJMOD_PATH/src/*.cc" "$ACTUAL_CJMOD_PATH/src/*.cxx")

# 创建共享库
add_library($REAL_MODULE_NAME SHARED \${SOURCES})

# 包含目录
target_include_directories($REAL_MODULE_NAME PRIVATE
    "$ROOT_DIR/src"
    "$ROOT_DIR/src/chtl"
    "$ACTUAL_CJMOD_PATH/src"
)

# 设置输出名称
set_target_properties($REAL_MODULE_NAME PROPERTIES
    PREFIX ""
    OUTPUT_NAME "$REAL_MODULE_NAME"
)

# 平台特定设置
if(WIN32)
    target_compile_definitions($REAL_MODULE_NAME PRIVATE CJMOD_EXPORTS)
elseif(APPLE)
    set_target_properties($REAL_MODULE_NAME PROPERTIES
        SUFFIX ".dylib"
    )
endif()

# 优化设置
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options($REAL_MODULE_NAME PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-O3 -DNDEBUG>
        $<$<CXX_COMPILER_ID:MSVC>:/O2 /DNDEBUG>
    )
endif()
EOF

# 配置和构建
cd "$BUILD_DIR"

print_info "配置CMake..."
if [ $VERBOSE -eq 1 ]; then
    cmake . -DCMAKE_BUILD_TYPE=$BUILD_TYPE
else
    cmake . -DCMAKE_BUILD_TYPE=$BUILD_TYPE > /dev/null 2>&1
fi

if [ $? -ne 0 ]; then
    print_error "CMake配置失败"
    cd "$ROOT_DIR"
    rm -rf "$BUILD_DIR"
    exit 1
fi

print_info "编译模块..."
if [ $VERBOSE -eq 1 ]; then
    cmake --build . --config $BUILD_TYPE -j $JOBS
else
    cmake --build . --config $BUILD_TYPE -j $JOBS > /dev/null 2>&1
fi

if [ $? -ne 0 ]; then
    print_error "编译失败"
    cd "$ROOT_DIR"
    rm -rf "$BUILD_DIR"
    exit 1
fi

cd "$ROOT_DIR"

# 查找生成的库文件
LIB_FILE=""
for ext in so dylib dll; do
    if [ -f "$BUILD_DIR/$REAL_MODULE_NAME.$ext" ]; then
        LIB_FILE="$BUILD_DIR/$REAL_MODULE_NAME.$ext"
        break
    elif [ -f "$BUILD_DIR/lib$REAL_MODULE_NAME.$ext" ]; then
        LIB_FILE="$BUILD_DIR/lib$REAL_MODULE_NAME.$ext"
        break
    elif [ -f "$BUILD_DIR/$BUILD_TYPE/$REAL_MODULE_NAME.$ext" ]; then
        LIB_FILE="$BUILD_DIR/$BUILD_TYPE/$REAL_MODULE_NAME.$ext"
        break
    fi
done

if [ -z "$LIB_FILE" ]; then
    print_error "未找到生成的库文件"
    rm -rf "$BUILD_DIR"
    exit 1
fi

print_success "编译成功: $(basename "$LIB_FILE")"

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 创建临时打包目录
TEMP_DIR=$(mktemp -d)
PACKAGE_DIR="$TEMP_DIR/$REAL_MODULE_NAME"
mkdir -p "$PACKAGE_DIR/lib"
mkdir -p "$PACKAGE_DIR/src"

# 复制文件
print_info "准备打包文件..."
cp "$LIB_FILE" "$PACKAGE_DIR/lib/"
cp -r "$ACTUAL_CJMOD_PATH/src"/* "$PACKAGE_DIR/src/"

# 复制info文件（如果存在）
if [ -d "$ACTUAL_CJMOD_PATH/info" ]; then
    mkdir -p "$PACKAGE_DIR/info"
    cp -r "$ACTUAL_CJMOD_PATH/info"/* "$PACKAGE_DIR/info/"
fi

# 创建元数据文件
cat > "$PACKAGE_DIR/.cjmod_metadata" << EOF
{
  "module_name": "$REAL_MODULE_NAME",
  "package_type": "CJMOD",
  "created_at": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "platform": "$(uname -s | tr '[:upper:]' '[:lower:]')",
  "architecture": "$(uname -m)",
  "build_type": "$BUILD_TYPE",
  "chtl_version": "1.0.0"
}
EOF

# 创建tar.gz包
OUTPUT_FILE="$OUTPUT_DIR/${REAL_MODULE_NAME}.cjmod"
print_info "创建CJMOD包: $OUTPUT_FILE"

cd "$TEMP_DIR"
if [ $VERBOSE -eq 1 ]; then
    tar -czvf "$OUTPUT_FILE" "$REAL_MODULE_NAME"
else
    tar -czf "$OUTPUT_FILE" "$REAL_MODULE_NAME"
fi

cd "$ROOT_DIR"

# 清理
rm -rf "$BUILD_DIR"
rm -rf "$TEMP_DIR"

# 验证输出文件
if [ -f "$OUTPUT_FILE" ]; then
    FILE_SIZE=$(du -h "$OUTPUT_FILE" | cut -f1)
    print_success "CJMOD包创建成功"
    print_info "文件: $OUTPUT_FILE"
    print_info "大小: $FILE_SIZE"
    print_info "平台: $(uname -s)"
    print_info "架构: $(uname -m)"
    
    # 显示包内容（如果verbose）
    if [ $VERBOSE -eq 1 ]; then
        print_info "包内容:"
        tar -tzf "$OUTPUT_FILE" | head -20
        TOTAL_FILES=$(tar -tzf "$OUTPUT_FILE" | wc -l)
        print_info "总文件数: $TOTAL_FILES"
    fi
else
    print_error "CJMOD包创建失败"
    exit 1
fi

exit 0