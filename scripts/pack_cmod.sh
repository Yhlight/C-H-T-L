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
    $0 -o dist MyModule                    # 打包到dist目录
    $0 -n CustomName module/MyModule       # 使用自定义名称

CMOD标准结构:
    ModuleName/
    ├── src/                  # 源代码目录
    │   ├── ModuleName.chtl   # 主模块文件(可选)
    │   └── *.chtl            # 其他CHTL文件
    └── info/                 # 信息目录
        └── ModuleName.chtl   # 模块信息文件(必需)
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
            if [ -z "$MODULE_PATH" ]; then
                MODULE_PATH="$1"
            else
                print_error "多余的参数: $1"
                exit 1
            fi
            shift
            ;;
    esac
done

# 检查参数
if [ -z "$MODULE_PATH" ]; then
    print_error "请指定模块路径"
    show_help
    exit 1
fi

# 转换为绝对路径
if [[ ! "$MODULE_PATH" = /* ]]; then
    MODULE_PATH="${PROJECT_ROOT}/${MODULE_PATH}"
fi

# 验证模块结构
validate_module() {
    local module_path="$1"
    
    if [ ! -d "$module_path" ]; then
        print_error "模块路径不存在: $module_path"
        return 1
    fi
    
    if [ ! -d "$module_path/src" ]; then
        print_error "缺少src目录: $module_path/src"
        return 1
    fi
    
    if [ ! -d "$module_path/info" ]; then
        print_error "缺少info目录: $module_path/info"
        return 1
    fi
    
    # 获取模块名称
    if [ -z "$MODULE_NAME" ]; then
        MODULE_NAME=$(basename "$module_path")
    fi
    
    # 检查info文件
    local info_file="$module_path/info/${MODULE_NAME}.chtl"
    if [ ! -f "$info_file" ]; then
        print_error "缺少模块信息文件: $info_file"
        return 1
    fi
    
    # 检查是否有CHTL文件
    local chtl_count=$(find "$module_path/src" -name "*.chtl" | wc -l)
    if [ "$chtl_count" -eq 0 ]; then
        print_error "src目录中没有找到.chtl文件"
        return 1
    fi
    
    # 验证info文件格式
    if ! grep -q "\[Info\]" "$info_file"; then
        print_error "模块信息文件缺少[Info]块"
        return 1
    fi
    
    return 0
}

# 生成导出表
generate_export_table() {
    local module_path="$1"
    local export_content=""
    
    print_info "扫描模块定义..."
    
    # 扫描所有CHTL文件
    while IFS= read -r file; do
        [ "$VERBOSE" = true ] && print_info "  扫描: $file"
        
        # 提取模板定义
        grep -E "^\[Template\]\s*@(Style|Element|Var)\s+\w+" "$file" | while read -r line; do
            if [[ $line =~ \[Template\][[:space:]]*@(Style|Element|Var)[[:space:]]+([[:alnum:]_]+) ]]; then
                export_content="${export_content}    @${BASH_REMATCH[1]} ${BASH_REMATCH[2]};\n"
                [ "$VERBOSE" = true ] && print_info "    找到模板: @${BASH_REMATCH[1]} ${BASH_REMATCH[2]}"
            fi
        done
        
        # 提取自定义定义
        grep -E "^\[Custom\]\s*@(Style|Element|Var)\s+\w+" "$file" | while read -r line; do
            if [[ $line =~ \[Custom\][[:space:]]*@(Style|Element|Var)[[:space:]]+([[:alnum:]_]+) ]]; then
                export_content="${export_content}    @${BASH_REMATCH[1]} ${BASH_REMATCH[2]};\n"
                [ "$VERBOSE" = true ] && print_info "    找到自定义: @${BASH_REMATCH[1]} ${BASH_REMATCH[2]}"
            fi
        done
    done < <(find "$module_path/src" -name "*.chtl")
    
    echo -e "$export_content"
}

# 创建tar归档
create_tar_archive() {
    local module_path="$1"
    local output_file="$2"
    local module_name=$(basename "$module_path")
    
    print_info "创建tar归档..."
    
    # 创建临时目录
    local temp_dir=$(mktemp -d)
    trap "rm -rf $temp_dir" EXIT
    
    # 复制模块文件
    cp -r "$module_path" "$temp_dir/"
    
    # 更新导出表
    local info_file="$temp_dir/$module_name/info/${MODULE_NAME}.chtl"
    if grep -q "\[Export\]" "$info_file"; then
        print_info "更新现有导出表..."
        # 备份原文件
        cp "$info_file" "${info_file}.bak"
        
        # 生成新的导出内容
        local export_content=$(generate_export_table "$module_path")
        
        # 更新导出表
        awk -v exports="$export_content" '
            /\[Export\]/ { 
                print $0
                print "{"
                print exports
                print "}"
                in_export = 1
                next
            }
            in_export && /^}/ { in_export = 0; next }
            !in_export { print }
        ' "${info_file}.bak" > "$info_file"
    else
        print_info "添加导出表..."
        local export_content=$(generate_export_table "$module_path")
        echo -e "\n[Export]\n{\n${export_content}}" >> "$info_file"
    fi
    
    # 创建tar文件
    cd "$temp_dir"
    if command -v tar >/dev/null 2>&1; then
        tar -czf "$output_file" "$module_name"
        print_success "使用tar创建归档"
    else
        print_warning "tar命令不可用，使用简单归档格式"
        # 简单的文本归档格式
        {
            echo "CMOD_ARCHIVE_V1"
            find "$module_name" -type f | while read -r file; do
                echo "FILE:$file"
                echo "SIZE:$(stat -c%s "$file" 2>/dev/null || stat -f%z "$file" 2>/dev/null || echo 0)"
                cat "$file"
                echo "END_FILE"
            done
            echo "END_ARCHIVE"
        } > "$output_file"
    fi
}

# 主函数
main() {
    print_info "CMOD模块打包工具"
    print_info "模块路径: $MODULE_PATH"
    
    # 验证模块
    if ! validate_module "$MODULE_PATH"; then
        exit 1
    fi
    
    print_success "模块验证通过"
    print_info "模块名称: $MODULE_NAME"
    
    # 创建输出目录
    mkdir -p "$OUTPUT_DIR"
    
    # 设置输出文件名
    local output_file="${OUTPUT_DIR}/${MODULE_NAME}.cmod"
    
    # 打包模块
    create_tar_archive "$MODULE_PATH" "$output_file"
    
    # 显示结果
    if [ -f "$output_file" ]; then
        local file_size=$(ls -lh "$output_file" | awk '{print $5}')
        print_success "模块打包完成!"
        print_info "输出文件: $output_file"
        print_info "文件大小: $file_size"
        
        # 更新模块索引
        local index_file="${OUTPUT_DIR}/modules.index"
        echo "[CMOD] $MODULE_NAME - $(date '+%Y-%m-%d %H:%M:%S')" >> "$index_file"
        
        [ "$VERBOSE" = true ] && {
            print_info "模块内容:"
            if [[ "$output_file" == *.tar.gz ]] || [[ "$output_file" == *.tgz ]]; then
                tar -tzf "$output_file" | head -20
            fi
        }
    else
        print_error "打包失败"
        exit 1
    fi
}

# 执行主函数
main