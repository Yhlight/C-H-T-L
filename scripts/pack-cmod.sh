#!/bin/bash

# CMOD打包脚本
# 将CMOD目录结构打包成.cmod文件（压缩包）

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 显示帮助信息
show_help() {
    echo "Usage: $0 [OPTIONS] <module-directory>"
    echo ""
    echo "Pack a CHTL module directory into a .cmod file"
    echo ""
    echo "Options:"
    echo "  -o, --output <file>    Output filename (default: <module-name>.cmod)"
    echo "  -f, --format <format>  Archive format: tar.gz, zip (default: tar.gz)"
    echo "  -v, --verbose          Verbose output"
    echo "  -h, --help             Show this help message"
    echo ""
    echo "Example:"
    echo "  $0 MyModule/"
    echo "  $0 -o mymodule-v1.0.cmod -f zip MyModule/"
}

# 参数解析
MODULE_DIR=""
OUTPUT_FILE=""
FORMAT="tar.gz"
VERBOSE=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -o|--output)
            OUTPUT_FILE="$2"
            shift 2
            ;;
        -f|--format)
            FORMAT="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            MODULE_DIR="$1"
            shift
            ;;
    esac
done

# 检查模块目录
if [ -z "$MODULE_DIR" ]; then
    echo -e "${RED}Error: No module directory specified${NC}"
    show_help
    exit 1
fi

if [ ! -d "$MODULE_DIR" ]; then
    echo -e "${RED}Error: Directory '$MODULE_DIR' does not exist${NC}"
    exit 1
fi

# 规范化路径
MODULE_DIR=$(realpath "$MODULE_DIR")
MODULE_NAME=$(basename "$MODULE_DIR")

# 验证CMOD结构
echo -e "${BLUE}Validating CMOD structure...${NC}"

# 检查info目录
if [ ! -d "$MODULE_DIR/info" ]; then
    echo -e "${YELLOW}Warning: 'info' directory not found${NC}"
    echo -n "Create info directory? (y/n): "
    read -r response
    if [[ "$response" =~ ^[Yy]$ ]]; then
        mkdir -p "$MODULE_DIR/info"
        # 创建默认的info文件
        cat > "$MODULE_DIR/info/$MODULE_NAME.chtl" << EOF
[Info] {
    name = "$MODULE_NAME";
    version = "1.0.0";
    description = "CMOD module";
    author = "Unknown";
    license = "MIT";
}

[Export] {
    // Auto-generated export list
}
EOF
        echo -e "${GREEN}Created default info file${NC}"
    else
        echo -e "${RED}Error: CMOD requires an info directory${NC}"
        exit 1
    fi
fi

# 检查src目录（可选）
if [ ! -d "$MODULE_DIR/src" ]; then
    echo -e "${YELLOW}Note: 'src' directory not found (optional for CMOD)${NC}"
fi

# 检查info文件
INFO_FILE="$MODULE_DIR/info/$MODULE_NAME.chtl"
if [ ! -f "$INFO_FILE" ]; then
    echo -e "${RED}Error: Info file '$INFO_FILE' not found${NC}"
    exit 1
fi

# 设置输出文件名
if [ -z "$OUTPUT_FILE" ]; then
    OUTPUT_FILE="$MODULE_NAME.cmod"
fi

# 确保输出文件有.cmod扩展名
if [[ ! "$OUTPUT_FILE" =~ \.cmod$ ]]; then
    OUTPUT_FILE="$OUTPUT_FILE.cmod"
fi

# 创建临时目录
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

# 复制模块内容到临时目录
echo -e "${BLUE}Preparing module contents...${NC}"
cp -r "$MODULE_DIR" "$TEMP_DIR/"

# 清理不需要的文件
echo -e "${BLUE}Cleaning up unnecessary files...${NC}"
find "$TEMP_DIR/$MODULE_NAME" -name "*.o" -delete
find "$TEMP_DIR/$MODULE_NAME" -name "*.tmp" -delete
find "$TEMP_DIR/$MODULE_NAME" -name ".DS_Store" -delete
find "$TEMP_DIR/$MODULE_NAME" -name "Thumbs.db" -delete
find "$TEMP_DIR/$MODULE_NAME" -type d -name ".git" -exec rm -rf {} + 2>/dev/null || true
find "$TEMP_DIR/$MODULE_NAME" -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true

# 生成导出列表（如果编译器可用）
if command -v chtl &> /dev/null; then
    echo -e "${BLUE}Generating export list...${NC}"
    # 这里应该调用编译器来分析并生成导出列表
    # chtl --generate-exports "$MODULE_DIR" > "$TEMP_DIR/$MODULE_NAME/info/exports.chtl"
else
    echo -e "${YELLOW}Note: CHTL compiler not found, skipping export generation${NC}"
fi

# 创建CMOD文件
echo -e "${BLUE}Creating CMOD archive...${NC}"

case $FORMAT in
    tar.gz)
        if $VERBOSE; then
            tar -czvf "$OUTPUT_FILE" -C "$TEMP_DIR" "$MODULE_NAME"
        else
            tar -czf "$OUTPUT_FILE" -C "$TEMP_DIR" "$MODULE_NAME"
        fi
        ;;
    zip)
        cd "$TEMP_DIR"
        if $VERBOSE; then
            zip -r "$OLDPWD/$OUTPUT_FILE" "$MODULE_NAME"
        else
            zip -qr "$OLDPWD/$OUTPUT_FILE" "$MODULE_NAME"
        fi
        cd "$OLDPWD"
        ;;
    *)
        echo -e "${RED}Error: Unsupported format '$FORMAT'${NC}"
        echo "Supported formats: tar.gz, zip"
        exit 1
        ;;
esac

# 显示文件信息
if [ -f "$OUTPUT_FILE" ]; then
    FILE_SIZE=$(du -h "$OUTPUT_FILE" | cut -f1)
    echo -e "${GREEN}✓ Successfully created CMOD file:${NC}"
    echo "  File: $OUTPUT_FILE"
    echo "  Size: $FILE_SIZE"
    echo "  Format: $FORMAT"
    
    # 显示内容预览
    if $VERBOSE; then
        echo -e "\n${BLUE}Archive contents:${NC}"
        case $FORMAT in
            tar.gz)
                tar -tzf "$OUTPUT_FILE" | head -20
                ;;
            zip)
                unzip -l "$OUTPUT_FILE" | head -20
                ;;
        esac
    fi
else
    echo -e "${RED}Error: Failed to create CMOD file${NC}"
    exit 1
fi

echo -e "\n${GREEN}CMOD packaging completed!${NC}"