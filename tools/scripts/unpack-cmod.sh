#!/bin/bash

# CMOD解包脚本
# 将.cmod文件解压到指定目录

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 显示帮助信息
show_help() {
    echo "Usage: $0 [OPTIONS] <cmod-file>"
    echo ""
    echo "Unpack a .cmod file into a directory"
    echo ""
    echo "Options:"
    echo "  -o, --output <dir>     Output directory (default: current directory)"
    echo "  -f, --force            Overwrite existing files"
    echo "  -v, --verbose          Verbose output"
    echo "  -i, --info             Show module info only (don't extract)"
    echo "  -h, --help             Show this help message"
    echo ""
    echo "Example:"
    echo "  $0 mymodule.cmod"
    echo "  $0 -o ./modules/ mymodule.cmod"
    echo "  $0 -i mymodule.cmod"
}

# 参数解析
CMOD_FILE=""
OUTPUT_DIR="."
FORCE=false
VERBOSE=false
INFO_ONLY=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -o|--output)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        -f|--force)
            FORCE=true
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -i|--info)
            INFO_ONLY=true
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            CMOD_FILE="$1"
            shift
            ;;
    esac
done

# 检查CMOD文件
if [ -z "$CMOD_FILE" ]; then
    echo -e "${RED}Error: No CMOD file specified${NC}"
    show_help
    exit 1
fi

if [ ! -f "$CMOD_FILE" ]; then
    echo -e "${RED}Error: File '$CMOD_FILE' does not exist${NC}"
    exit 1
fi

# 验证文件扩展名
if [[ ! "$CMOD_FILE" =~ \.cmod$ ]]; then
    echo -e "${YELLOW}Warning: File does not have .cmod extension${NC}"
fi

# 检测文件格式
echo -e "${BLUE}Detecting archive format...${NC}"

# 使用更通用的方法检测文件格式
if tar -tzf "$CMOD_FILE" >/dev/null 2>&1; then
    FORMAT="tar.gz"
elif unzip -l "$CMOD_FILE" >/dev/null 2>&1; then
    FORMAT="zip"
else
    echo -e "${RED}Error: Unknown archive format or corrupted file${NC}"
    echo "Supported formats: tar.gz, zip"
    exit 1
fi

echo "Format: $FORMAT"

# 如果只是查看信息
if $INFO_ONLY; then
    echo -e "\n${BLUE}Module Information:${NC}"
    
    TEMP_DIR=$(mktemp -d)
    trap "rm -rf $TEMP_DIR" EXIT
    
    case $FORMAT in
        tar.gz)
            tar -xzf "$CMOD_FILE" -C "$TEMP_DIR"
            ;;
        zip)
            unzip -q "$CMOD_FILE" -d "$TEMP_DIR"
            ;;
    esac
    
    # 查找info文件
    INFO_FILE=$(find "$TEMP_DIR" -path "*/info/*.chtl" -type f | head -1)
    
    if [ -f "$INFO_FILE" ]; then
        echo -e "\n${GREEN}Info file content:${NC}"
        cat "$INFO_FILE"
    else
        echo -e "${RED}Error: No info file found in CMOD${NC}"
    fi
    
    # 显示目录结构
    echo -e "\n${BLUE}Module structure:${NC}"
    tree -L 3 "$TEMP_DIR" 2>/dev/null || find "$TEMP_DIR" -type d | sed 's|[^/]*/|- |g'
    
    exit 0
fi

# 创建输出目录
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# 获取模块名称
MODULE_NAME=$(basename "$CMOD_FILE" .cmod)

# 检查目标目录是否已存在
TARGET_DIR="$OUTPUT_DIR/$MODULE_NAME"
if [ -d "$TARGET_DIR" ] && [ "$FORCE" != true ]; then
    echo -e "${RED}Error: Directory '$TARGET_DIR' already exists${NC}"
    echo "Use -f/--force to overwrite"
    exit 1
fi

# 解压文件
echo -e "${BLUE}Extracting CMOD file...${NC}"

case $FORMAT in
    tar.gz)
        if $VERBOSE; then
            tar -xzvf "$CMOD_FILE" -C "$OUTPUT_DIR"
        else
            tar -xzf "$CMOD_FILE" -C "$OUTPUT_DIR"
        fi
        ;;
    zip)
        if $VERBOSE; then
            unzip "$CMOD_FILE" -d "$OUTPUT_DIR"
        else
            unzip -q "$CMOD_FILE" -d "$OUTPUT_DIR"
        fi
        ;;
esac

# 验证解压结果
if [ ! -d "$TARGET_DIR" ]; then
    # 可能解压出来的目录名与预期不同
    EXTRACTED_DIR=$(find "$OUTPUT_DIR" -maxdepth 1 -type d -newer "$CMOD_FILE" | head -1)
    if [ -n "$EXTRACTED_DIR" ] && [ "$EXTRACTED_DIR" != "$OUTPUT_DIR" ]; then
        TARGET_DIR="$EXTRACTED_DIR"
    else
        echo -e "${RED}Error: Failed to extract CMOD file${NC}"
        exit 1
    fi
fi

# 验证CMOD结构
echo -e "${BLUE}Validating extracted module...${NC}"

if [ ! -d "$TARGET_DIR/info" ]; then
    echo -e "${YELLOW}Warning: 'info' directory not found in extracted module${NC}"
fi

# 查找并显示模块信息
INFO_FILE=$(find "$TARGET_DIR/info" -name "*.chtl" -type f 2>/dev/null | head -1)
if [ -f "$INFO_FILE" ]; then
    echo -e "\n${GREEN}Module info:${NC}"
    grep -E "name|version|description" "$INFO_FILE" | sed 's/^/  /'
fi

# 显示解压结果
echo -e "\n${GREEN}✓ Successfully unpacked CMOD file:${NC}"
echo "  Location: $TARGET_DIR"

if $VERBOSE; then
    echo -e "\n${BLUE}Module contents:${NC}"
    tree -L 3 "$TARGET_DIR" 2>/dev/null || ls -la "$TARGET_DIR"
fi

echo -e "\n${GREEN}CMOD unpacking completed!${NC}"