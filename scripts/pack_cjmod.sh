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
BUILD_TYPE="Release"
VERBOSE=false
CLEAN=false

# 显示帮助
show_help() {
    cat << EOF
CJMOD模块打包脚本

用法: $0 [选项] <模块路径>

选项:
    -h, --help              显示此帮助信息
    -o, --output DIR        输出目录 [默认: ./build/module]
    -n, --name NAME         模块名称 [默认: 从路径推断]
    -t, --type TYPE         构建类型 (Debug|Release) [默认: Release]
    -c, --clean             清理后重新构建
    -v, --verbose           显示详细信息

示例:
    $0 module/MyCJMod                      # 打包CJMOD模块
    $0 -t Debug -o dist MyModule           # Debug构建并输出到dist
    $0 --clean module/Extension            # 清理构建后打包

CJMOD标准结构:
    ModuleName/
    ├── src/                  # C++源代码目录
    │   ├── extension.cpp     # 扩展实现
    │   ├── extension.h       # 扩展头文件
    │   └── CMakeLists.txt    # CMake配置(可选)
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
        -t|--type)
            BUILD_TYPE="$2"
            shift 2
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
    
    # 检查是否有C++源文件
    local cpp_count=$(find "$module_path/src" \( -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" \) | wc -l)
    local h_count=$(find "$module_path/src" \( -name "*.h" -o -name "*.hpp" -o -name "*.hxx" \) | wc -l)
    
    if [ "$cpp_count" -eq 0 ] && [ "$h_count" -eq 0 ]; then
        print_error "src目录中没有找到C++源文件"
        return 1
    fi
    
    # 验证info文件格式
    if ! grep -q "\[Info\]" "$info_file"; then
        print_error "模块信息文件缺少[Info]块"
        return 1
    fi
    
    return 0
}

# 创建CMakeLists.txt
create_cmake_file() {
    local module_path="$1"
    local module_name="$2"
    
    # 如果已经存在CMakeLists.txt，跳过
    if [ -f "$module_path/src/CMakeLists.txt" ]; then
        [ "$VERBOSE" = true ] && print_info "使用现有的CMakeLists.txt"
        return 0
    fi
    
    print_info "生成CMakeLists.txt..."
    
    cat > "$module_path/src/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.10)
project(${module_name}_cjmod)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 查找源文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.cxx")
file(GLOB_RECURSE HEADERS "*.h" "*.hpp" "*.hxx")

# 创建共享库
add_library(${module_name} SHARED \${SOURCES} \${HEADERS})

# 设置输出名称
set_target_properties(${module_name} PROPERTIES
    OUTPUT_NAME "${module_name}"
    PREFIX ""
    SUFFIX ".cjmod"
)

# 包含CHTL头文件
target_include_directories(${module_name} PRIVATE
    \${CMAKE_CURRENT_SOURCE_DIR}
    /usr/include/chtl
    ${PROJECT_ROOT}/src/chtl
)

# 链接选项
target_link_options(${module_name} PRIVATE
    -Wl,--no-undefined
    -Wl,--as-needed
)

# 优化选项
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${module_name} PRIVATE -O3 -DNDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${module_name} PRIVATE -g -O0)
endif()
EOF
}

# 编译模块
compile_module() {
    local module_path="$1"
    local output_dir="$2"
    local module_name="$3"
    
    print_info "编译CJMOD模块..."
    
    # 创建构建目录
    local build_dir="$module_path/build"
    
    if [ "$CLEAN" = true ] && [ -d "$build_dir" ]; then
        print_info "清理构建目录..."
        rm -rf "$build_dir"
    fi
    
    mkdir -p "$build_dir"
    cd "$build_dir"
    
    # 配置CMake
    print_info "配置CMake..."
    local cmake_args=(
        "-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
        "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$output_dir"
    )
    
    if [ "$VERBOSE" = true ]; then
        cmake_args+=("-DCMAKE_VERBOSE_MAKEFILE=ON")
    fi
    
    if ! cmake "${cmake_args[@]}" "$module_path/src"; then
        print_error "CMake配置失败"
        return 1
    fi
    
    # 编译
    print_info "开始编译..."
    local make_args=()
    
    if [ "$VERBOSE" = true ]; then
        make_args+=("VERBOSE=1")
    fi
    
    if ! make "${make_args[@]}"; then
        print_error "编译失败"
        return 1
    fi
    
    print_success "编译完成"
    return 0
}

# 打包模块
package_module() {
    local module_path="$1"
    local output_dir="$2"
    local module_name="$3"
    
    # 检查编译输出
    local cjmod_file="${output_dir}/${module_name}.cjmod"
    if [ ! -f "$cjmod_file" ]; then
        print_error "未找到编译输出: $cjmod_file"
        return 1
    fi
    
    # 复制info文件到输出目录
    print_info "复制模块信息..."
    cp -r "$module_path/info" "$output_dir/${module_name}_info"
    
    # 创建模块元数据
    local metadata_file="$output_dir/${module_name}.meta"
    cat > "$metadata_file" << EOF
{
    "name": "$module_name",
    "type": "cjmod",
    "build_type": "$BUILD_TYPE",
    "build_date": "$(date -u '+%Y-%m-%d %H:%M:%S UTC')",
    "compiler": "$(g++ --version | head -n1)",
    "files": {
        "library": "${module_name}.cjmod",
        "info": "${module_name}_info/",
        "size": $(stat -c%s "$cjmod_file" 2>/dev/null || stat -f%z "$cjmod_file" 2>/dev/null || echo 0)
    }
}
EOF
    
    return 0
}

# 主函数
main() {
    print_info "CJMOD模块打包工具"
    print_info "模块路径: $MODULE_PATH"
    
    # 验证模块
    if ! validate_module "$MODULE_PATH"; then
        exit 1
    fi
    
    print_success "模块验证通过"
    print_info "模块名称: $MODULE_NAME"
    print_info "构建类型: $BUILD_TYPE"
    
    # 创建输出目录
    mkdir -p "$OUTPUT_DIR"
    
    # 创建CMakeLists.txt（如果需要）
    create_cmake_file "$MODULE_PATH" "$MODULE_NAME"
    
    # 编译模块
    if ! compile_module "$MODULE_PATH" "$OUTPUT_DIR" "$MODULE_NAME"; then
        exit 1
    fi
    
    # 打包模块
    if ! package_module "$MODULE_PATH" "$OUTPUT_DIR" "$MODULE_NAME"; then
        exit 1
    fi
    
    # 显示结果
    local cjmod_file="${OUTPUT_DIR}/${MODULE_NAME}.cjmod"
    if [ -f "$cjmod_file" ]; then
        local file_size=$(ls -lh "$cjmod_file" | awk '{print $5}')
        print_success "CJMOD模块打包完成!"
        print_info "输出文件: $cjmod_file"
        print_info "文件大小: $file_size"
        
        # 更新模块索引
        local index_file="${OUTPUT_DIR}/modules.index"
        echo "[CJMOD] $MODULE_NAME - $(date '+%Y-%m-%d %H:%M:%S')" >> "$index_file"
        
        [ "$VERBOSE" = true ] && {
            print_info "模块信息:"
            if command -v nm >/dev/null 2>&1; then
                print_info "导出符号:"
                nm -D "$cjmod_file" | grep " T " | head -10
            fi
        }
    else
        print_error "打包失败"
        exit 1
    fi
}

# 执行主函数
main