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
    -n, --name NAME         模块名称 [默认: 从info文件读取]
    -v, --verbose           显示详细信息

示例:
    $0 module/Chtholly                         # 打包Chtholly模块（自动检测CMOD部分）
    $0 module/Chtholly/CMOD/Chtholly          # 直接打包CMOD部分
    $0 -o dist module/MyModule                 # 打包到dist目录

CMOD标准结构:
    ModuleName/
    ├── CMOD/                     # CMOD部分（可选）
    │   └── ModuleName/
    │       ├── src/              # 源代码目录
    │       │   └── ModuleName.chtl
    │       └── info/             # 模块信息
    │           └── ModuleName.chtl
    └── CJMOD/                    # CJMOD部分（可选）
        └── ModuleName/
            ├── src/              # C++源代码
            └── info/             # 模块信息

EOF
}

# 解析命令行参数
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
    print_error "请指定模块路径"
    show_help
    exit 1
fi

# 转换为绝对路径
MODULE_PATH="$(cd "$MODULE_PATH" 2>/dev/null && pwd)" || {
    print_error "模块路径不存在: $MODULE_PATH"
    exit 1
}

# 检测模块结构
detect_module_structure() {
    local path="$1"
    
    # 检查是否是混合模块（包含CMOD和/或CJMOD）
    if [ -d "$path/CMOD" ] || [ -d "$path/CJMOD" ]; then
        echo "mixed"
    # 检查是否是直接的CMOD模块
    elif [ -d "$path/src" ] && [ -d "$path/info" ]; then
        echo "direct"
    else
        echo "unknown"
    fi
}

# 获取模块名称
get_module_name() {
    local module_dir="$1"
    local info_file=""
    
    # 查找info文件
    if [ -f "$module_dir/info/$(basename "$module_dir").chtl" ]; then
        info_file="$module_dir/info/$(basename "$module_dir").chtl"
    elif [ -f "$module_dir/info/module.info" ]; then
        info_file="$module_dir/info/module.info"
    fi
    
    if [ -n "$info_file" ] && [ -f "$info_file" ]; then
        # 从info文件中提取name字段
        local name=$(grep -E '^\s*name\s*=' "$info_file" | sed 's/.*=\s*"\?\([^"]*\)"\?;*/\1/' | tr -d ' ')
        if [ -n "$name" ]; then
            echo "$name"
            return
        fi
    fi
    
    # 默认使用目录名
    basename "$module_dir"
}

# 验证CMOD结构
validate_cmod() {
    local cmod_dir="$1"
    local errors=0
    
    print_info "验证CMOD结构: $cmod_dir"
    
    # 检查必要的目录
    if [ ! -d "$cmod_dir/src" ]; then
        print_error "缺少src目录"
        ((errors++))
    fi
    
    if [ ! -d "$cmod_dir/info" ]; then
        print_error "缺少info目录"
        ((errors++))
    fi
    
    # 获取模块名
    local module_name=$(get_module_name "$cmod_dir")
    
    # 检查主模块文件
    if [ ! -f "$cmod_dir/src/$module_name.chtl" ]; then
        print_warning "缺少主模块文件: src/$module_name.chtl"
    fi
    
    # 检查info文件
    if [ ! -f "$cmod_dir/info/$module_name.chtl" ]; then
        print_error "缺少模块信息文件: info/$module_name.chtl"
        ((errors++))
    fi
    
    return $errors
}

# 创建CMOD包
create_cmod_package() {
    local cmod_dir="$1"
    local output_dir="$2"
    local module_name="$3"
    
    # 如果没有指定模块名，从info文件获取
    if [ -z "$module_name" ]; then
        module_name=$(get_module_name "$cmod_dir")
    fi
    
    print_info "打包CMOD模块: $module_name"
    
    # 创建输出目录
    mkdir -p "$output_dir"
    
    # 创建临时目录
    local temp_dir=$(mktemp -d)
    local package_dir="$temp_dir/$module_name"
    mkdir -p "$package_dir"
    
    # 复制文件
    print_info "复制模块文件..."
    cp -r "$cmod_dir"/* "$package_dir/"
    
    # 创建元数据文件
    local metadata_file="$package_dir/.cmod_metadata"
    cat > "$metadata_file" << EOF
{
    "format_version": "1.0",
    "package_type": "CMOD",
    "created_at": "$(date -u +"%Y-%m-%dT%H:%M:%SZ")",
    "compiler_version": "1.0.0"
}
EOF
    
    # 创建tar.gz包
    local output_file="$output_dir/${module_name}.cmod"
    print_info "创建压缩包: $output_file"
    
    (cd "$temp_dir" && tar -czf "$output_file" "$module_name")
    
    # 清理临时文件
    rm -rf "$temp_dir"
    
    # 显示包信息
    local size=$(du -h "$output_file" | cut -f1)
    print_success "CMOD包创建成功"
    print_info "文件: $output_file"
    print_info "大小: $size"
    
    if [ "$VERBOSE" = true ]; then
        print_info "包含内容:"
        tar -tzf "$output_file" | head -20
        echo "..."
    fi
}

# 主函数
main() {
    print_info "开始CMOD打包流程"
    
    # 检测模块结构
    local structure=$(detect_module_structure "$MODULE_PATH")
    local cmod_path=""
    
    case $structure in
        "mixed")
            # 混合模块，查找CMOD部分
            if [ -d "$MODULE_PATH/CMOD" ]; then
                # 查找CMOD子目录
                for dir in "$MODULE_PATH/CMOD"/*; do
                    if [ -d "$dir" ] && [ -d "$dir/src" ] && [ -d "$dir/info" ]; then
                        cmod_path="$dir"
                        break
                    fi
                done
            fi
            
            if [ -z "$cmod_path" ]; then
                print_error "在混合模块中未找到有效的CMOD部分"
                exit 1
            fi
            ;;
        "direct")
            # 直接的CMOD模块
            cmod_path="$MODULE_PATH"
            ;;
        *)
            print_error "无法识别的模块结构"
            print_error "请确保模块遵循CMOD标准结构"
            exit 1
            ;;
    esac
    
    # 验证CMOD结构
    if ! validate_cmod "$cmod_path"; then
        print_error "CMOD结构验证失败"
        exit 1
    fi
    
    # 创建CMOD包
    create_cmod_package "$cmod_path" "$OUTPUT_DIR" "$MODULE_NAME"
    
    print_success "CMOD打包完成！"
}

# 执行主函数
main