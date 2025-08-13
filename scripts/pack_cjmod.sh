#!/bin/bash
# CJMOD模块打包脚本

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# 打印函数
print_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_error() { echo -e "${RED}[ERROR]${NC} $1"; }
print_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }

# 获取脚本目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# 默认参数
MODULE_PATH=""
OUTPUT_DIR="${PROJECT_ROOT}/build/module"
MODULE_NAME=""
VERBOSE=false
BUILD_TYPE="Release"

# 显示帮助
show_help() {
    cat << EOF
CJMOD模块打包脚本

用法: $0 [选项] <模块路径>

选项:
    -h, --help              显示此帮助信息
    -o, --output DIR        输出目录 [默认: ./build/module]
    -n, --name NAME         模块名称 [默认: 从路径推断]
    -b, --build-type TYPE   构建类型 [默认: Release]
    -v, --verbose           显示详细信息

示例:
    $0 module/Chtholly                     # 打包Chtholly模块
    $0 -o dist module/MyCJMOD              # 打包到dist目录
    $0 -b Debug module/MyModule            # Debug构建

CJMOD标准结构:
    ModuleName/
    ├── src/                  # C++源代码目录
    │   ├── *.cpp             # C++源文件
    │   ├── *.h               # C++头文件
    │   └── SubModule/        # 子模块（可选）
    │       ├── src/
    │       └── info/
    └── info/                 # 模块信息目录
        └── ModuleName.chtl   # 模块信息文件

模块文件夹、信息文件必须同名
EOF
}

# 解析参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -o|--output)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        -n|--name)
            MODULE_NAME="$2"
            shift 2
            ;;
        -b|--build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
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
    print_error "错误: 未指定模块路径"
    show_help
    exit 1
fi

# 检查模块路径
if [ ! -d "$MODULE_PATH" ]; then
    print_error "错误: 模块路径不存在: $MODULE_PATH"
    exit 1
fi

# 获取模块名称
if [ -z "$MODULE_NAME" ]; then
    MODULE_NAME=$(basename "$MODULE_PATH")
fi

# 检查CJMOD标准结构
print_info "检查CJMOD标准结构..."

# 检查src目录
if [ ! -d "$MODULE_PATH/src" ]; then
    print_error "错误: 缺少src目录"
    exit 1
fi

# 检查info目录
if [ ! -d "$MODULE_PATH/info" ]; then
    print_error "错误: 缺少info目录"
    exit 1
fi

# 检查模块信息文件
INFO_FILE="$MODULE_PATH/info/$MODULE_NAME.chtl"
if [ ! -f "$INFO_FILE" ]; then
    print_error "错误: 缺少模块信息文件: $INFO_FILE"
    exit 1
fi

# 检查是否有C++源文件
CPP_COUNT=$(find "$MODULE_PATH/src" -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" | wc -l)
if [ "$CPP_COUNT" -eq 0 ]; then
    print_error "错误: src目录中没有找到C++源文件"
    exit 1
fi

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 输出文件名
OUTPUT_FILE="$OUTPUT_DIR/$MODULE_NAME.cjmod"

# 创建临时目录
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

print_info "编译和打包CJMOD模块: $MODULE_NAME"
print_info "模块路径: $MODULE_PATH"
print_info "输出文件: $OUTPUT_FILE"

# 创建构建目录
BUILD_DIR="$TEMP_DIR/build"
mkdir -p "$BUILD_DIR"

# 生成CMakeLists.txt
cat > "$TEMP_DIR/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.16)
project($MODULE_NAME VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 收集源文件
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc" "src/*.cxx")
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp" "src/*.hxx")

# 创建共享库
add_library($MODULE_NAME SHARED \${SOURCES})

# 包含目录
target_include_directories($MODULE_NAME PUBLIC
    \$<BUILD_INTERFACE:\${CMAKE_CURRENT_SOURCE_DIR}/src>
    \$<INSTALL_INTERFACE:include>
)

# 设置输出名称
set_target_properties($MODULE_NAME PROPERTIES
    PREFIX ""
    OUTPUT_NAME "$MODULE_NAME"
)

# 安装规则
install(TARGETS $MODULE_NAME
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES \${HEADERS}
    DESTINATION include/$MODULE_NAME
)
EOF

# 复制源文件
cp -r "$MODULE_PATH/src" "$TEMP_DIR/"
cp -r "$MODULE_PATH/info" "$TEMP_DIR/"

# 编译模块
print_info "编译CJMOD模块..."
cd "$BUILD_DIR"

if cmake "$TEMP_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE > /dev/null 2>&1; then
    if cmake --build . --config $BUILD_TYPE > /dev/null 2>&1; then
        print_success "编译成功"
    else
        print_error "编译失败"
        [ "$VERBOSE" = true ] && cmake --build . --config $BUILD_TYPE
        exit 1
    fi
else
    print_error "CMake配置失败"
    [ "$VERBOSE" = true ] && cmake "$TEMP_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE
    exit 1
fi

# 查找生成的共享库
SHARED_LIB=$(find "$BUILD_DIR" -name "*.so" -o -name "*.dylib" -o -name "*.dll" | head -1)
if [ -z "$SHARED_LIB" ]; then
    print_error "未找到生成的共享库"
    exit 1
fi

print_info "生成的共享库: $(basename "$SHARED_LIB")"

# 创建CJMOD归档
print_info "创建CJMOD归档..."

# 创建归档目录结构
ARCHIVE_DIR="$TEMP_DIR/archive"
mkdir -p "$ARCHIVE_DIR/lib"
mkdir -p "$ARCHIVE_DIR/src"
mkdir -p "$ARCHIVE_DIR/info"

# 复制文件
cp "$SHARED_LIB" "$ARCHIVE_DIR/lib/"
cp -r "$MODULE_PATH/src"/* "$ARCHIVE_DIR/src/"
cp -r "$MODULE_PATH/info"/* "$ARCHIVE_DIR/info/"

# 写入元数据
cat > "$ARCHIVE_DIR/CJMOD_META" << EOF
MODULE_NAME=$MODULE_NAME
BUILD_TYPE=$BUILD_TYPE
BUILD_DATE=$(date -u +"%Y-%m-%d %H:%M:%S UTC")
PLATFORM=$(uname -s)
ARCH=$(uname -m)
EOF

# 创建tar.gz归档
cd "$ARCHIVE_DIR"
tar -czf "$OUTPUT_FILE" .

# 显示结果
ARCHIVE_SIZE=$(stat -f%z "$OUTPUT_FILE" 2>/dev/null || stat -c%s "$OUTPUT_FILE")
print_success "CJMOD打包完成!"
print_success "输出文件: $OUTPUT_FILE"
print_success "文件大小: $ARCHIVE_SIZE bytes"

# 验证归档
if [ "$VERBOSE" = true ]; then
    print_info "归档内容:"
    tar -tzf "$OUTPUT_FILE" | head -20
fi

# 更新模块索引
INDEX_FILE="$OUTPUT_DIR/modules.index"
echo "[CJMOD] $MODULE_NAME - $(date '+%Y-%m-%d %H:%M:%S')" >> "$INDEX_FILE"