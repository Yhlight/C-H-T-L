#!/bin/bash
# 统一模块打包脚本

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
MODULE_DIR="${PROJECT_ROOT}/module"
OUTPUT_DIR="${PROJECT_ROOT}/build/module"
PACK_CMOD=true
PACK_CJMOD=true
CLEAN=false
VERBOSE=false

# 显示帮助
show_help() {
    cat << EOF
统一模块打包脚本

用法: $0 [选项]

选项:
    -h, --help              显示此帮助信息
    -m, --module-dir DIR    模块目录 [默认: ./module]
    -o, --output DIR        输出目录 [默认: ./build/module]
    --cmod-only             只打包CMOD模块
    --cjmod-only            只打包CJMOD模块
    -c, --clean             清理输出目录
    -v, --verbose           显示详细信息

示例:
    $0                              # 打包所有模块
    $0 --cmod-only                  # 只打包CMOD模块
    $0 -m custom/modules -o dist    # 从自定义目录打包

功能:
    1. 自动扫描模块目录
    2. 识别CMOD和CJMOD模块
    3. 调用相应的打包脚本
    4. 生成模块索引文件
EOF
}

# 解析参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -m|--module-dir)
            MODULE_DIR="$2"
            shift 2
            ;;
        -o|--output)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        --cmod-only)
            PACK_CJMOD=false
            shift
            ;;
        --cjmod-only)
            PACK_CMOD=false
            shift
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        *)
            print_error "未知选项: $1"
            show_help
            exit 1
            ;;
    esac
done

# 检查模块目录
if [ ! -d "$MODULE_DIR" ]; then
    print_error "模块目录不存在: $MODULE_DIR"
    exit 1
fi

# 创建输出目录
if [ "$CLEAN" = true ] && [ -d "$OUTPUT_DIR" ]; then
    print_info "清理输出目录..."
    rm -rf "$OUTPUT_DIR"
fi
mkdir -p "$OUTPUT_DIR"

# 判断模块类型
is_cmod() {
    local module_path="$1"
    local module_name=$(basename "$module_path")
    
    # CMOD特征：有info/<ModuleName>.chtl，src目录包含.chtl文件
    if [ -f "$module_path/info/${module_name}.chtl" ] && \
       [ -d "$module_path/src" ] && \
       [ $(find "$module_path/src" -name "*.chtl" | wc -l) -gt 0 ]; then
        return 0
    fi
    return 1
}

is_cjmod() {
    local module_path="$1"
    local module_name=$(basename "$module_path")
    
    # CJMOD特征：有info/<ModuleName>.chtl，src目录包含C++源文件
    if [ -f "$module_path/info/${module_name}.chtl" ] && \
       [ -d "$module_path/src" ] && \
       [ $(find "$module_path/src" \( -name "*.cpp" -o -name "*.cc" -o -name "*.h" -o -name "*.hpp" \) | wc -l) -gt 0 ]; then
        return 0
    fi
    return 1
}

# 打包单个模块
pack_module() {
    local module_path="$1"
    local module_name=$(basename "$module_path")
    local module_type=""
    
    # 判断模块类型
    if is_cmod "$module_path"; then
        module_type="CMOD"
        if [ "$PACK_CMOD" = false ]; then
            [ "$VERBOSE" = true ] && print_info "跳过CMOD模块: $module_name"
            return 0
        fi
    elif is_cjmod "$module_path"; then
        module_type="CJMOD"
        if [ "$PACK_CJMOD" = false ]; then
            [ "$VERBOSE" = true ] && print_info "跳过CJMOD模块: $module_name"
            return 0
        fi
    else
        print_warning "无法识别模块类型: $module_name"
        return 1
    fi
    
    print_info "打包${module_type}模块: $module_name"
    
    # 调用相应的打包脚本
    local pack_script=""
    local pack_args=("-o" "$OUTPUT_DIR")
    
    if [ "$VERBOSE" = true ]; then
        pack_args+=("-v")
    fi
    
    if [ "$module_type" = "CMOD" ]; then
        pack_script="${SCRIPT_DIR}/pack_cmod.sh"
    else
        pack_script="${SCRIPT_DIR}/pack_cjmod.sh"
    fi
    
    # 检查打包脚本是否存在
    if [ ! -f "$pack_script" ]; then
        print_error "打包脚本不存在: $pack_script"
        return 1
    fi
    
    # 执行打包
    if bash "$pack_script" "${pack_args[@]}" "$module_path"; then
        print_success "成功打包: $module_name"
        return 0
    else
        print_error "打包失败: $module_name"
        return 1
    fi
}

# 扫描并打包所有模块
scan_and_pack_modules() {
    local success_count=0
    local fail_count=0
    local skip_count=0
    
    print_info "扫描模块目录: $MODULE_DIR"
    
    # 查找所有可能的模块目录
    while IFS= read -r -d '' module_path; do
        local module_name=$(basename "$module_path")
        
        # 跳过隐藏目录和特殊目录
        if [[ "$module_name" =~ ^\. ]] || \
           [[ "$module_name" = "build" ]] || \
           [[ "$module_name" = "dist" ]]; then
            [ "$VERBOSE" = true ] && print_info "跳过: $module_name"
            ((skip_count++))
            continue
        fi
        
        # 检查是否是有效的模块
        if [ -d "$module_path/src" ] && [ -d "$module_path/info" ]; then
            if pack_module "$module_path"; then
                ((success_count++))
            else
                ((fail_count++))
            fi
        else
            [ "$VERBOSE" = true ] && print_info "不是有效模块: $module_name"
            ((skip_count++))
        fi
        
    done < <(find "$MODULE_DIR" -mindepth 1 -maxdepth 1 -type d -print0)
    
    # 显示统计
    echo
    print_info "打包统计:"
    print_info "  成功: $success_count"
    print_info "  失败: $fail_count"
    print_info "  跳过: $skip_count"
    
    return $([ $fail_count -eq 0 ] && echo 0 || echo 1)
}

# 生成模块索引
generate_module_index() {
    local index_file="${OUTPUT_DIR}/modules.index"
    
    print_info "生成模块索引..."
    
    # 创建索引头部
    cat > "$index_file" << EOF
# CHTL模块索引
# 生成时间: $(date -u '+%Y-%m-%d %H:%M:%S UTC')
# 模块目录: $MODULE_DIR
# 输出目录: $OUTPUT_DIR

EOF
    
    # 添加CMOD模块
    if [ "$PACK_CMOD" = true ]; then
        echo "## CMOD模块" >> "$index_file"
        find "$OUTPUT_DIR" -name "*.cmod" -type f | sort | while read -r file; do
            local name=$(basename "$file" .cmod)
            local size=$(ls -lh "$file" | awk '{print $5}')
            echo "- $name (大小: $size)" >> "$index_file"
        done
        echo >> "$index_file"
    fi
    
    # 添加CJMOD模块
    if [ "$PACK_CJMOD" = true ]; then
        echo "## CJMOD模块" >> "$index_file"
        find "$OUTPUT_DIR" -name "*.cjmod" -type f | sort | while read -r file; do
            local name=$(basename "$file" .cjmod)
            local size=$(ls -lh "$file" | awk '{print $5}')
            local meta_file="${OUTPUT_DIR}/${name}.meta"
            if [ -f "$meta_file" ]; then
                echo "- $name (大小: $size) [有元数据]" >> "$index_file"
            else
                echo "- $name (大小: $size)" >> "$index_file"
            fi
        done
        echo >> "$index_file"
    fi
    
    # 统计信息
    local total_cmod=$(find "$OUTPUT_DIR" -name "*.cmod" -type f | wc -l)
    local total_cjmod=$(find "$OUTPUT_DIR" -name "*.cjmod" -type f | wc -l)
    
    echo "## 统计" >> "$index_file"
    echo "- CMOD模块总数: $total_cmod" >> "$index_file"
    echo "- CJMOD模块总数: $total_cjmod" >> "$index_file"
    echo "- 模块总数: $((total_cmod + total_cjmod))" >> "$index_file"
    
    print_success "模块索引已生成: $index_file"
}

# 主函数
main() {
    print_info "统一模块打包工具"
    print_info "模块目录: $MODULE_DIR"
    print_info "输出目录: $OUTPUT_DIR"
    
    if [ "$PACK_CMOD" = true ] && [ "$PACK_CJMOD" = true ]; then
        print_info "打包类型: CMOD和CJMOD"
    elif [ "$PACK_CMOD" = true ]; then
        print_info "打包类型: 仅CMOD"
    elif [ "$PACK_CJMOD" = true ]; then
        print_info "打包类型: 仅CJMOD"
    else
        print_error "没有选择任何打包类型"
        exit 1
    fi
    
    echo
    
    # 扫描并打包模块
    if scan_and_pack_modules; then
        # 生成索引
        generate_module_index
        
        print_success "模块打包完成!"
        
        # 显示输出目录内容
        if [ "$VERBOSE" = true ]; then
            echo
            print_info "输出目录内容:"
            ls -la "$OUTPUT_DIR" | sed 's/^/  /'
        fi
    else
        print_error "部分模块打包失败"
        exit 1
    fi
}

# 确保打包脚本可执行
chmod +x "${SCRIPT_DIR}/pack_cmod.sh" 2>/dev/null || true
chmod +x "${SCRIPT_DIR}/pack_cjmod.sh" 2>/dev/null || true

# 执行主函数
main