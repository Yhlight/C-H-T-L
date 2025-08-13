#!/bin/bash
# CHTL编译器构建脚本

set -e  # 遇到错误立即退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 打印带颜色的消息
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# 默认参数
BUILD_TYPE="Debug"
BUILD_DIR="${PROJECT_ROOT}/build"
INSTALL_PREFIX="${PROJECT_ROOT}/install"
PARALLEL_JOBS=$(nproc 2>/dev/null || echo 4)
CLEAN_BUILD=false
GENERATE_PARSERS=true
PACK_MODULES=true
RUN_TESTS=false
VERBOSE=false

# 显示帮助信息
show_help() {
    cat << EOF
CHTL编译器构建脚本

用法: $0 [选项]

选项:
    -h, --help              显示此帮助信息
    -t, --type TYPE         构建类型 (Debug|Release|RelWithDebInfo) [默认: Debug]
    -d, --build-dir DIR     构建目录 [默认: ./build]
    -p, --prefix DIR        安装前缀 [默认: ./install]
    -j, --jobs N            并行编译任务数 [默认: $(nproc)]
    -c, --clean             清理构建目录后重新构建
    --no-parsers            不生成ANTLR解析器
    --no-modules            不打包模块
    --test                  运行测试
    -v, --verbose           显示详细输出

示例:
    $0                      # 默认Debug构建
    $0 -t Release -j 8      # Release构建，8个并行任务
    $0 --clean --test       # 清理构建并运行测试
EOF
}

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -t|--type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -d|--build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        -p|--prefix)
            INSTALL_PREFIX="$2"
            shift 2
            ;;
        -j|--jobs)
            PARALLEL_JOBS="$2"
            shift 2
            ;;
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        --no-parsers)
            GENERATE_PARSERS=false
            shift
            ;;
        --no-modules)
            PACK_MODULES=false
            shift
            ;;
        --test)
            RUN_TESTS=true
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

# 显示构建配置
print_info "CHTL编译器构建配置:"
print_info "  项目根目录: ${PROJECT_ROOT}"
print_info "  构建类型: ${BUILD_TYPE}"
print_info "  构建目录: ${BUILD_DIR}"
print_info "  安装前缀: ${INSTALL_PREFIX}"
print_info "  并行任务: ${PARALLEL_JOBS}"
print_info "  生成解析器: ${GENERATE_PARSERS}"
print_info "  打包模块: ${PACK_MODULES}"
print_info "  运行测试: ${RUN_TESTS}"
echo

# 检查依赖
check_dependencies() {
    print_info "检查依赖..."
    
    local missing_deps=()
    
    # 检查必要的工具
    command -v cmake >/dev/null 2>&1 || missing_deps+=("cmake")
    command -v make >/dev/null 2>&1 || missing_deps+=("make")
    command -v g++ >/dev/null 2>&1 && command -v gcc >/dev/null 2>&1 || missing_deps+=("build-essential")
    
    # 检查ANTLR4
    if [ "$GENERATE_PARSERS" = true ]; then
        if [ ! -f "/usr/local/lib/antlr-4.13.1-complete.jar" ] && [ ! -f "$HOME/antlr4/antlr-4.13.1-complete.jar" ]; then
            print_warning "未找到ANTLR4，将跳过解析器生成"
            GENERATE_PARSERS=false
        fi
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        print_error "缺少以下依赖: ${missing_deps[*]}"
        print_info "请安装: sudo apt-get install ${missing_deps[*]}"
        exit 1
    fi
    
    print_success "依赖检查通过"
}

# 清理构建目录
clean_build() {
    if [ "$CLEAN_BUILD" = true ] && [ -d "$BUILD_DIR" ]; then
        print_info "清理构建目录..."
        rm -rf "$BUILD_DIR"
        print_success "清理完成"
    fi
}

# 创建构建目录
create_build_dir() {
    if [ ! -d "$BUILD_DIR" ]; then
        print_info "创建构建目录..."
        mkdir -p "$BUILD_DIR"
    fi
}

# 配置CMake
configure_cmake() {
    print_info "配置CMake..."
    cd "$BUILD_DIR"
    
    local cmake_args=(
        "-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
        "-DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX"
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    )
    
    if [ "$VERBOSE" = true ]; then
        cmake_args+=("-DCMAKE_VERBOSE_MAKEFILE=ON")
    fi
    
    cmake "${cmake_args[@]}" "$PROJECT_ROOT"
    
    print_success "CMake配置完成"
}

# 生成ANTLR解析器
generate_parsers() {
    if [ "$GENERATE_PARSERS" = true ]; then
        print_info "生成ANTLR解析器..."
        cd "$BUILD_DIR"
        
        if make generate-parsers; then
            print_success "解析器生成完成"
        else
            print_warning "解析器生成失败，继续构建..."
        fi
    fi
}

# 构建项目
build_project() {
    print_info "开始构建..."
    cd "$BUILD_DIR"
    
    local make_args=("-j$PARALLEL_JOBS")
    
    if [ "$VERBOSE" = true ]; then
        make_args+=("VERBOSE=1")
    fi
    
    if make "${make_args[@]}"; then
        print_success "构建完成"
    else
        print_error "构建失败"
        exit 1
    fi
}

# 打包模块
pack_modules() {
    if [ "$PACK_MODULES" = true ]; then
        print_info "打包模块..."
        cd "$BUILD_DIR"
        
        if make pack-modules; then
            print_success "模块打包完成"
            
            # 显示打包的模块
            if [ -f "module/modules.index" ]; then
                print_info "已打包的模块:"
                cat "module/modules.index" | sed 's/^/    /'
            fi
        else
            print_warning "模块打包失败"
        fi
    fi
}

# 运行测试
run_tests() {
    if [ "$RUN_TESTS" = true ]; then
        print_info "运行测试..."
        cd "$BUILD_DIR"
        
        if ctest --output-on-failure; then
            print_success "所有测试通过"
        else
            print_error "某些测试失败"
            exit 1
        fi
    fi
}

# 安装
install_project() {
    print_info "安装到 ${INSTALL_PREFIX}..."
    cd "$BUILD_DIR"
    
    if make install; then
        print_success "安装完成"
        
        # 显示安装的文件
        print_info "已安装:"
        print_info "  编译器: ${INSTALL_PREFIX}/bin/chtlc"
        print_info "  模块: ${INSTALL_PREFIX}/share/chtl/module/"
    else
        print_error "安装失败"
        exit 1
    fi
}

# 主函数
main() {
    print_info "开始构建CHTL编译器..."
    echo
    
    # 执行构建步骤
    check_dependencies
    clean_build
    create_build_dir
    configure_cmake
    generate_parsers
    build_project
    pack_modules
    run_tests
    
    # 询问是否安装
    if [ -t 0 ]; then  # 检查是否在交互式终端
        read -p "是否安装到 ${INSTALL_PREFIX}? [y/N] " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            install_project
        fi
    fi
    
    echo
    print_success "CHTL编译器构建完成!"
    print_info "编译器位置: ${BUILD_DIR}/bin/chtlc"
    
    # 显示下一步提示
    echo
    print_info "下一步:"
    print_info "  1. 测试编译器: ${BUILD_DIR}/bin/chtlc examples/test.chtl"
    print_info "  2. 安装编译器: cd ${BUILD_DIR} && make install"
    print_info "  3. 添加到PATH: export PATH=\$PATH:${INSTALL_PREFIX}/bin"
}

# 执行主函数
main