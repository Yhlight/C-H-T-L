#!/bin/bash
# CJMOD打包脚本

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
OUTPUT_DIR="${PROJECT_ROOT}/build/cjmod"
MODULE_NAME=""
BUILD_TYPE="Release"
VERBOSE=false

# 显示帮助
show_help() {
    cat << EOF
CJMOD打包脚本

用法: $0 [选项] <模块路径>

选项:
    -h, --help              显示此帮助信息
    -o, --output DIR        输出目录 [默认: ./build/cjmod]
    -n, --name NAME         模块名称 [默认: 从info文件读取]
    -b, --build-type TYPE   构建类型 (Debug/Release) [默认: Release]
    -v, --verbose           显示详细信息

示例:
    $0 module/Chtholly                         # 打包Chtholly模块（自动检测CJMOD部分）
    $0 module/Chtholly/CJMOD/Chtholly         # 直接打包CJMOD部分
    $0 -o dist module/MyModule                 # 打包到dist目录

CJMOD标准结构:
    ModuleName/
    ├── CMOD/                     # CMOD部分（可选）
    └── CJMOD/                    # CJMOD部分
        └── ModuleName/
            ├── src/              # C++源代码
            │   └── modulename.cpp
            └── info/             # 模块信息
                └── ModuleName.chtl

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
    # 检查是否是直接的CJMOD模块
    elif [ -d "$path/src" ] && [ -f "$path/src/"*.cpp ]; then
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

# 验证CJMOD结构
validate_cjmod() {
    local cjmod_dir="$1"
    local errors=0
    
    print_info "验证CJMOD结构: $cjmod_dir"
    
    # 检查必要的目录
    if [ ! -d "$cjmod_dir/src" ]; then
        print_error "缺少src目录"
        ((errors++))
    fi
    
    if [ ! -d "$cjmod_dir/info" ]; then
        print_error "缺少info目录"
        ((errors++))
    fi
    
    # 检查是否有C++源文件
    if ! ls "$cjmod_dir/src"/*.cpp >/dev/null 2>&1; then
        print_error "src目录中没有找到C++源文件"
        ((errors++))
    fi
    
    # 获取模块名
    local module_name=$(get_module_name "$cjmod_dir")
    
    # 检查info文件
    if [ ! -f "$cjmod_dir/info/$module_name.chtl" ]; then
        print_error "缺少模块信息文件: info/$module_name.chtl"
        ((errors++))
    fi
    
    return $errors
}

# 编译CJMOD
compile_cjmod() {
    local cjmod_dir="$1"
    local build_dir="$2"
    local module_name="$3"
    
    print_info "编译CJMOD模块: $module_name"
    
    # 创建构建目录
    mkdir -p "$build_dir"
    
    # 创建CMakeLists.txt
    cat > "$build_dir/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.16)
project($module_name VERSION 1.0.0 LANGUAGES CXX)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含项目头文件
include_directories("${PROJECT_ROOT}/src")
include_directories("${PROJECT_ROOT}/include")

# 查找源文件
file(GLOB SOURCES "${cjmod_dir}/src/*.cpp")

# 创建共享库
add_library($module_name SHARED \${SOURCES})

# 设置输出名称（小写）
set_target_properties($module_name PROPERTIES 
    OUTPUT_NAME "${module_name,,}"
    PREFIX ""
)

# 平台特定设置
if(WIN32)
    set_target_properties($module_name PROPERTIES
        SUFFIX ".dll"
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
elseif(APPLE)
    set_target_properties($module_name PROPERTIES
        SUFFIX ".dylib"
    )
else()
    set_target_properties($module_name PROPERTIES
        SUFFIX ".so"
    )
endif()

# 优化设置
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options($module_name PRIVATE -O3 -DNDEBUG)
endif()

# 导出符号
target_compile_definitions($module_name PRIVATE BUILDING_CJMOD)
EOF
    
    # 配置项目
    print_info "配置CMake项目..."
    (cd "$build_dir" && cmake . -DCMAKE_BUILD_TYPE="$BUILD_TYPE")
    
    # 编译
    print_info "编译共享库..."
    (cd "$build_dir" && cmake --build . --config "$BUILD_TYPE")
    
    # 查找生成的库文件
    local lib_file=""
    for ext in "so" "dll" "dylib"; do
        if [ -f "$build_dir/${module_name,,}.$ext" ]; then
            lib_file="$build_dir/${module_name,,}.$ext"
            break
        fi
    done
    
    if [ -z "$lib_file" ] || [ ! -f "$lib_file" ]; then
        print_error "编译失败：未找到生成的库文件"
        return 1
    fi
    
    print_success "编译成功: $(basename "$lib_file")"
    echo "$lib_file"
}

# 创建CJMOD包
create_cjmod_package() {
    local cjmod_dir="$1"
    local output_dir="$2"
    local module_name="$3"
    
    # 如果没有指定模块名，从info文件获取
    if [ -z "$module_name" ]; then
        module_name=$(get_module_name "$cjmod_dir")
    fi
    
    print_info "打包CJMOD模块: $module_name"
    
    # 创建输出目录
    mkdir -p "$output_dir"
    
    # 创建临时构建目录
    local temp_dir=$(mktemp -d)
    local build_dir="$temp_dir/build"
    
    # 编译模块
    local lib_file=$(compile_cjmod "$cjmod_dir" "$build_dir" "$module_name")
    if [ $? -ne 0 ]; then
        rm -rf "$temp_dir"
        return 1
    fi
    
    # 创建打包目录
    local package_dir="$temp_dir/package/$module_name"
    mkdir -p "$package_dir/lib"
    mkdir -p "$package_dir/src"
    mkdir -p "$package_dir/info"
    
    # 复制文件
    print_info "准备打包文件..."
    cp "$lib_file" "$package_dir/lib/"
    cp -r "$cjmod_dir/src"/* "$package_dir/src/"
    cp -r "$cjmod_dir/info"/* "$package_dir/info/"
    
    # 创建元数据文件
    local metadata_file="$package_dir/.cjmod_metadata"
    cat > "$metadata_file" << EOF
{
    "format_version": "1.0",
    "package_type": "CJMOD",
    "created_at": "$(date -u +"%Y-%m-%dT%H:%M:%SZ")",
    "compiler_version": "1.0.0",
    "build_type": "$BUILD_TYPE",
    "platform": "$(uname -s)",
    "architecture": "$(uname -m)"
}
EOF
    
    # 创建tar.gz包
    local output_file="$output_dir/${module_name}.cjmod"
    print_info "创建压缩包: $output_file"
    
    (cd "$temp_dir/package" && tar -czf "$output_file" "$module_name")
    
    # 清理临时文件
    rm -rf "$temp_dir"
    
    # 显示包信息
    local size=$(du -h "$output_file" | cut -f1)
    print_success "CJMOD包创建成功"
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
    print_info "开始CJMOD打包流程"
    
    # 检测模块结构
    local structure=$(detect_module_structure "$MODULE_PATH")
    local cjmod_path=""
    
    case $structure in
        "mixed")
            # 混合模块，查找CJMOD部分
            if [ -d "$MODULE_PATH/CJMOD" ]; then
                # 查找CJMOD子目录
                for dir in "$MODULE_PATH/CJMOD"/*; do
                    if [ -d "$dir" ] && [ -d "$dir/src" ] && [ -d "$dir/info" ]; then
                        cjmod_path="$dir"
                        break
                    fi
                done
            fi
            
            if [ -z "$cjmod_path" ]; then
                print_error "在混合模块中未找到有效的CJMOD部分"
                exit 1
            fi
            ;;
        "direct")
            # 直接的CJMOD模块
            cjmod_path="$MODULE_PATH"
            ;;
        *)
            print_error "无法识别的模块结构"
            print_error "请确保模块遵循CJMOD标准结构"
            exit 1
            ;;
    esac
    
    # 验证CJMOD结构
    if ! validate_cjmod "$cjmod_path"; then
        print_error "CJMOD结构验证失败"
        exit 1
    fi
    
    # 创建CJMOD包
    create_cjmod_package "$cjmod_path" "$OUTPUT_DIR" "$MODULE_NAME"
    
    print_success "CJMOD打包完成！"
}

# 执行主函数
main