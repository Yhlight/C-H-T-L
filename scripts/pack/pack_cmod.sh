#!/bin/bash
# CHTL CMOD打包脚本

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
VERBOSE=0
MODULE_PATH=""

# 显示帮助
show_help() {
    cat << EOF
CHTL CMOD打包脚本

用法: $0 <模块路径> [选项]

选项:
  --help, -h          显示帮助信息
  --output DIR, -o    输出目录 [默认: output]
  --verbose, -v       显示详细输出

示例:
  $0 src/module/Chtholly                    # 打包Chtholly模块
  $0 src/module/MyModule -o dist            # 打包到dist目录

支持的模块结构:
  1. 混合模块: ModuleName/CMOD/ModuleName/
  2. 纯CMOD模块: ModuleName/src/ 和 ModuleName/info/

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

# 获取模块名称
MODULE_NAME=$(basename "$MODULE_PATH")

# 查找实际的CMOD路径
ACTUAL_CMOD_PATH=""

# 检查混合模块结构
if [ -d "$MODULE_PATH/CMOD/$MODULE_NAME" ]; then
    ACTUAL_CMOD_PATH="$MODULE_PATH/CMOD/$MODULE_NAME"
    print_info "检测到混合模块结构"
# 检查纯CMOD模块结构
elif [ -d "$MODULE_PATH/src" ] && [ -d "$MODULE_PATH/info" ]; then
    # 确认是CMOD模块（包含.chtl文件）
    if find "$MODULE_PATH/src" -name "*.chtl" | grep -q .; then
        ACTUAL_CMOD_PATH="$MODULE_PATH"
        print_info "检测到纯CMOD模块结构"
    fi
fi

if [ -z "$ACTUAL_CMOD_PATH" ]; then
    print_error "未找到有效的CMOD模块结构"
    print_info "请确保模块包含以下结构之一:"
    print_info "  1. $MODULE_PATH/CMOD/$MODULE_NAME/src/ 和 info/"
    print_info "  2. $MODULE_PATH/src/ 和 info/ (包含.chtl文件)"
    exit 1
fi

# 验证模块结构
if [ ! -d "$ACTUAL_CMOD_PATH/src" ]; then
    print_error "未找到src目录: $ACTUAL_CMOD_PATH/src"
    exit 1
fi

if [ ! -d "$ACTUAL_CMOD_PATH/info" ]; then
    print_error "未找到info目录: $ACTUAL_CMOD_PATH/info"
    exit 1
fi

# 查找info文件
INFO_FILE=""
for file in "$ACTUAL_CMOD_PATH/info"/*.chtl; do
    if [ -f "$file" ]; then
        INFO_FILE="$file"
        break
    fi
done

if [ -z "$INFO_FILE" ]; then
    print_error "未找到info文件"
    exit 1
fi

# 从info文件名获取模块名（而非[Info]中的name字段）
REAL_MODULE_NAME=$(basename "$INFO_FILE" .chtl)
print_info "模块名称: $REAL_MODULE_NAME"

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 创建临时目录
TEMP_DIR=$(mktemp -d)
MODULE_DIR="$TEMP_DIR/$REAL_MODULE_NAME"
mkdir -p "$MODULE_DIR"

# 复制模块文件
print_info "复制模块文件..."
cp -r "$ACTUAL_CMOD_PATH"/* "$MODULE_DIR/"

# 创建元数据文件
cat > "$MODULE_DIR/.cmod_metadata" << EOF
{
  "module_name": "$REAL_MODULE_NAME",
  "package_type": "CMOD",
  "created_at": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "platform": "all",
  "chtl_version": "1.0.0"
}
EOF

# 创建tar.gz包
OUTPUT_FILE="$OUTPUT_DIR/${REAL_MODULE_NAME}.cmod"
print_info "创建CMOD包: $OUTPUT_FILE"

cd "$TEMP_DIR"
if [ $VERBOSE -eq 1 ]; then
    tar -czvf "$OUTPUT_FILE" "$REAL_MODULE_NAME"
else
    tar -czf "$OUTPUT_FILE" "$REAL_MODULE_NAME"
fi

cd "$ROOT_DIR"

# 清理临时目录
rm -rf "$TEMP_DIR"

# 验证输出文件
if [ -f "$OUTPUT_FILE" ]; then
    FILE_SIZE=$(du -h "$OUTPUT_FILE" | cut -f1)
    print_success "CMOD包创建成功"
    print_info "文件: $OUTPUT_FILE"
    print_info "大小: $FILE_SIZE"
    
    # 显示包内容（如果verbose）
    if [ $VERBOSE -eq 1 ]; then
        print_info "包内容:"
        tar -tzf "$OUTPUT_FILE" | head -20
        TOTAL_FILES=$(tar -tzf "$OUTPUT_FILE" | wc -l)
        print_info "总文件数: $TOTAL_FILES"
    fi
else
    print_error "CMOD包创建失败"
    exit 1
fi

exit 0