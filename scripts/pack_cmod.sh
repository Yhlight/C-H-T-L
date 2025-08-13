#!/bin/bash
# CMOD模块打包脚本

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

# 显示帮助
show_help() {
    cat << EOF
CMOD模块打包脚本

用法: $0 [选项] <模块路径>

选项:
    -h, --help              显示此帮助信息
    -o, --output DIR        输出目录 [默认: ./build/module]
    -n, --name NAME         模块名称 [默认: 从路径推断]
    -v, --verbose           显示详细信息

示例:
    $0 module/Chtholly                     # 打包Chtholly模块
    $0 -o dist module/Chtl.Core            # 打包到dist目录
    $0 -n CustomName module/MyModule       # 使用自定义名称

CMOD标准结构:
    ModuleName/
    ├── src/                  # 源代码目录
    │   ├── ModuleName.chtl   # 主模块文件
    │   └── *.chtl            # 其他CHTL文件
    └── info/                 # 模块信息目录
        └── ModuleName.chtl   # 模块信息文件

模块文件夹、主模块文件、信息文件必须同名
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

# 从info文件中读取实际的模块名
INFO_FILE="$MODULE_PATH/info/$MODULE_NAME.chtl"
if [ -f "$INFO_FILE" ]; then
    # 尝试从[Info]块中提取name字段
    ACTUAL_NAME=$(grep -A20 "^\[Info\]" "$INFO_FILE" | grep -E "name\s*=\s*" | head -1 | sed -E 's/.*name\s*=\s*"([^"]+)".*/\1/' | tr -d '\r')
    if [ ! -z "$ACTUAL_NAME" ]; then
        MODULE_NAME="$ACTUAL_NAME"
        print_info "从info文件读取模块名: $MODULE_NAME"
    fi
fi

# 检查CMOD标准结构
print_info "检查CMOD标准结构..."

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

# 检查主模块文件（如果没有子模块则必须存在）
MAIN_MODULE_FILE="$MODULE_PATH/src/$MODULE_NAME.chtl"
HAS_SUBMODULES=false

# 检查是否有子模块
for dir in "$MODULE_PATH/src"/*; do
    if [ -d "$dir" ] && [ -f "$dir/info/"$(basename "$dir")".chtl" ]; then
        HAS_SUBMODULES=true
        break
    fi
done

if [ ! -f "$MAIN_MODULE_FILE" ] && [ "$HAS_SUBMODULES" = false ]; then
    print_error "错误: 缺少主模块文件: $MAIN_MODULE_FILE"
    exit 1
fi

# 检查模块信息文件
if [ ! -f "$INFO_FILE" ]; then
    print_error "错误: 缺少模块信息文件: $INFO_FILE"
    exit 1
fi

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 输出文件名
OUTPUT_FILE="$OUTPUT_DIR/$MODULE_NAME.cmod"

# 创建临时目录
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

print_info "打包CMOD模块: $MODULE_NAME"
print_info "模块路径: $MODULE_PATH"
print_info "输出文件: $OUTPUT_FILE"

# 收集所有需要打包的文件
FILES_LIST="$TEMP_DIR/files.list"
touch "$FILES_LIST"

# 添加src目录下的所有文件（递归）
print_info "收集源文件..."
cd "$MODULE_PATH"
find src -type f -name "*.chtl" | sort >> "$FILES_LIST"

# 添加info目录下的所有文件
print_info "收集信息文件..."
find info -type f -name "*.chtl" | sort >> "$FILES_LIST"

# 显示文件列表
if [ "$VERBOSE" = true ]; then
    print_info "文件列表:"
    cat "$FILES_LIST" | while read file; do
        echo "  - $file"
    done
fi

# 创建CMOD归档
print_info "创建CMOD归档..."

# 写入魔术字符串
echo "CHTL_CMOD_ARCHIVE_V1" > "$OUTPUT_FILE"

# 写入模块信息
echo "MODULE:$MODULE_NAME" >> "$OUTPUT_FILE"

# 写入文件数量
FILE_COUNT=$(wc -l < "$FILES_LIST")
echo "FILES:$FILE_COUNT" >> "$OUTPUT_FILE"

# 写入每个文件
while IFS= read -r file; do
    if [ -f "$file" ]; then
        # 文件大小
        FILE_SIZE=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file")
        
        # 写入文件头
        echo "FILE:$file:$FILE_SIZE" >> "$OUTPUT_FILE"
        
        # 写入文件内容
        cat "$file" >> "$OUTPUT_FILE"
        
        # 写入分隔符
        echo "" >> "$OUTPUT_FILE"
        
        if [ "$VERBOSE" = true ]; then
            print_info "  添加: $file ($FILE_SIZE bytes)"
        fi
    fi
done < "$FILES_LIST"

# 写入结束标记
echo "END_ARCHIVE" >> "$OUTPUT_FILE"

# 显示结果
ARCHIVE_SIZE=$(stat -f%z "$OUTPUT_FILE" 2>/dev/null || stat -c%s "$OUTPUT_FILE")
print_success "CMOD打包完成!"
print_success "输出文件: $OUTPUT_FILE"
print_success "文件大小: $ARCHIVE_SIZE bytes"
print_success "包含文件: $FILE_COUNT"

# 验证归档
if [ "$VERBOSE" = true ]; then
    print_info "验证归档..."
    if grep -q "^CHTL_CMOD_ARCHIVE_V1" "$OUTPUT_FILE" && grep -q "^END_ARCHIVE" "$OUTPUT_FILE"; then
        print_success "归档验证通过"
    else
        print_error "归档验证失败"
        exit 1
    fi
fi