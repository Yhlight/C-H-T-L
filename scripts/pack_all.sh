#!/bin/bash
# 统一打包脚本 - 自动检测并打包CMOD和CJMOD

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

# 脚本目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# 默认参数
MODULE_PATH=""
OUTPUT_DIR="${PROJECT_ROOT}/build/modules"
VERBOSE=false
BUILD_TYPE="Release"

# 显示帮助
show_help() {
    cat << EOF
统一打包脚本

用法: $0 [选项] <模块路径>

选项:
    -h, --help              显示此帮助信息
    -o, --output DIR        输出目录 [默认: ./build/modules]
    -b, --build-type TYPE   构建类型 (Debug/Release) [默认: Release]
    -v, --verbose           显示详细信息

示例:
    $0 module/Chtholly                 # 打包Chtholly模块（自动检测CMOD和CJMOD）
    $0 -o dist module/MyModule         # 打包到dist目录
    $0 --verbose module/*              # 打包所有模块

支持的模块结构:
    1. 纯CMOD模块
    2. 纯CJMOD模块
    3. 混合模块（同时包含CMOD和CJMOD）

EOF
}

# 解析命令行参数
MODULES=()
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
        -b|--build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        *)
            MODULES+=("$1")
            shift
            ;;
    esac
done

# 检查参数
if [ ${#MODULES[@]} -eq 0 ]; then
    print_error "请指定至少一个模块路径"
    show_help
    exit 1
fi

# 检测模块类型
detect_module_type() {
    local module_path="$1"
    local has_cmod=false
    local has_cjmod=false
    
    # 检查CMOD
    if [ -d "$module_path/CMOD" ]; then
        for dir in "$module_path/CMOD"/*; do
            if [ -d "$dir/src" ] && [ -d "$dir/info" ]; then
                has_cmod=true
                break
            fi
        done
    elif [ -d "$module_path/src" ] && [ -d "$module_path/info" ] && [ -f "$module_path/src/"*.chtl ]; then
        has_cmod=true
    fi
    
    # 检查CJMOD
    if [ -d "$module_path/CJMOD" ]; then
        for dir in "$module_path/CJMOD"/*; do
            if [ -d "$dir/src" ] && [ -d "$dir/info" ] && [ -f "$dir/src/"*.cpp ]; then
                has_cjmod=true
                break
            fi
        done
    elif [ -d "$module_path/src" ] && [ -d "$module_path/info" ] && [ -f "$module_path/src/"*.cpp ]; then
        has_cjmod=true
    fi
    
    if [ "$has_cmod" = true ] && [ "$has_cjmod" = true ]; then
        echo "mixed"
    elif [ "$has_cmod" = true ]; then
        echo "cmod"
    elif [ "$has_cjmod" = true ]; then
        echo "cjmod"
    else
        echo "unknown"
    fi
}

# 打包单个模块
pack_module() {
    local module_path="$1"
    local module_name=$(basename "$module_path")
    
    print_info "处理模块: $module_name"
    
    # 检测模块类型
    local module_type=$(detect_module_type "$module_path")
    
    case $module_type in
        "mixed")
            print_info "检测到混合模块（CMOD + CJMOD）"
            
            # 打包CMOD部分
            if [ "$VERBOSE" = true ]; then
                "$SCRIPT_DIR/pack_cmod.sh" -o "$OUTPUT_DIR" -v "$module_path"
            else
                "$SCRIPT_DIR/pack_cmod.sh" -o "$OUTPUT_DIR" "$module_path"
            fi
            
            # 打包CJMOD部分
            if [ "$VERBOSE" = true ]; then
                "$SCRIPT_DIR/pack_cjmod.sh" -o "$OUTPUT_DIR" -b "$BUILD_TYPE" -v "$module_path"
            else
                "$SCRIPT_DIR/pack_cjmod.sh" -o "$OUTPUT_DIR" -b "$BUILD_TYPE" "$module_path"
            fi
            ;;
        "cmod")
            print_info "检测到CMOD模块"
            if [ "$VERBOSE" = true ]; then
                "$SCRIPT_DIR/pack_cmod.sh" -o "$OUTPUT_DIR" -v "$module_path"
            else
                "$SCRIPT_DIR/pack_cmod.sh" -o "$OUTPUT_DIR" "$module_path"
            fi
            ;;
        "cjmod")
            print_info "检测到CJMOD模块"
            if [ "$VERBOSE" = true ]; then
                "$SCRIPT_DIR/pack_cjmod.sh" -o "$OUTPUT_DIR" -b "$BUILD_TYPE" -v "$module_path"
            else
                "$SCRIPT_DIR/pack_cjmod.sh" -o "$OUTPUT_DIR" -b "$BUILD_TYPE" "$module_path"
            fi
            ;;
        *)
            print_warning "无法识别模块类型: $module_name"
            return 1
            ;;
    esac
    
    print_success "模块 $module_name 打包完成"
    echo ""
}

# 主函数
main() {
    print_info "开始统一打包流程"
    print_info "输出目录: $OUTPUT_DIR"
    print_info "构建类型: $BUILD_TYPE"
    echo ""
    
    # 创建输出目录
    mkdir -p "$OUTPUT_DIR"
    
    # 统计信息
    local total_modules=${#MODULES[@]}
    local success_count=0
    local failed_count=0
    local failed_modules=()
    
    # 处理每个模块
    for module in "${MODULES[@]}"; do
        # 展开通配符
        for path in $module; do
            if [ -d "$path" ]; then
                if pack_module "$path"; then
                    ((success_count++))
                else
                    ((failed_count++))
                    failed_modules+=("$path")
                fi
            else
                print_warning "跳过非目录: $path"
            fi
        done
    done
    
    # 显示统计结果
    echo ""
    print_info "=== 打包统计 ==="
    print_info "总模块数: $total_modules"
    print_success "成功: $success_count"
    if [ $failed_count -gt 0 ]; then
        print_error "失败: $failed_count"
        print_error "失败的模块:"
        for module in "${failed_modules[@]}"; do
            echo "  - $module"
        done
    fi
    
    # 列出生成的文件
    echo ""
    print_info "=== 生成的文件 ==="
    if [ -d "$OUTPUT_DIR" ]; then
        ls -la "$OUTPUT_DIR"/*.cmod 2>/dev/null || true
        ls -la "$OUTPUT_DIR"/*.cjmod 2>/dev/null || true
    fi
    
    if [ $failed_count -eq 0 ]; then
        print_success "所有模块打包完成！"
        return 0
    else
        print_warning "部分模块打包失败"
        return 1
    fi
}

# 执行主函数
main