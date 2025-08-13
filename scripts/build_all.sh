#!/bin/bash
# CHTL项目统一构建脚本

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m'

# 打印函数
print_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_error() { echo -e "${RED}[ERROR]${NC} $1"; }
print_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
print_step() { echo -e "${PURPLE}[STEP]${NC} $1"; }

# 获取脚本目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# 默认参数
BUILD_TYPE="Debug"
BUILD_COMPILER=true
BUILD_IDE=true
BUILD_MODULES=true
CLEAN=false
TEST=false
VERBOSE=false
PARALLEL_JOBS=$(nproc 2>/dev/null || echo 4)

# 构建步骤计数
CURRENT_STEP=0
TOTAL_STEPS=0

# 显示帮助
show_help() {
    cat << EOF
CHTL项目统一构建脚本

用法: $0 [选项]

选项:
    -h, --help              显示此帮助信息
    -t, --type TYPE         构建类型 (Debug|Release) [默认: Debug]
    -j, --jobs N            并行编译任务数 [默认: $(nproc)]
    -c, --clean             清理后重新构建
    --test                  运行所有测试
    -v, --verbose           显示详细输出
    
    --compiler-only         只构建编译器
    --ide-only             只构建IDE
    --modules-only         只构建模块
    --no-compiler          跳过编译器构建
    --no-ide               跳过IDE构建
    --no-modules           跳过模块构建

示例:
    $0                      # 构建所有组件
    $0 -t Release           # Release构建
    $0 --compiler-only      # 只构建编译器
    $0 -c --test            # 清理构建并运行测试

构建顺序:
    1. CHTL编译器
    2. CHTL模块（CMOD/CJMOD）
    3. CHTL IDE
EOF
}

# 解析参数
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
        -j|--jobs)
            PARALLEL_JOBS="$2"
            shift 2
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        --test)
            TEST=true
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        --compiler-only)
            BUILD_IDE=false
            BUILD_MODULES=false
            shift
            ;;
        --ide-only)
            BUILD_COMPILER=false
            BUILD_MODULES=false
            shift
            ;;
        --modules-only)
            BUILD_COMPILER=false
            BUILD_IDE=false
            shift
            ;;
        --no-compiler)
            BUILD_COMPILER=false
            shift
            ;;
        --no-ide)
            BUILD_IDE=false
            shift
            ;;
        --no-modules)
            BUILD_MODULES=false
            shift
            ;;
        *)
            print_error "未知选项: $1"
            show_help
            exit 1
            ;;
    esac
done

# 计算总步骤数
calculate_steps() {
    TOTAL_STEPS=0
    [ "$BUILD_COMPILER" = true ] && ((TOTAL_STEPS++))
    [ "$BUILD_MODULES" = true ] && ((TOTAL_STEPS++))
    [ "$BUILD_IDE" = true ] && ((TOTAL_STEPS++))
    [ "$TEST" = true ] && ((TOTAL_STEPS++))
}

# 显示进度
show_progress() {
    local step_name="$1"
    ((CURRENT_STEP++))
    echo
    echo -e "${PURPLE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${PURPLE}[$CURRENT_STEP/$TOTAL_STEPS] $step_name${NC}"
    echo -e "${PURPLE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo
}

# 构建编译器
build_compiler() {
    if [ "$BUILD_COMPILER" = true ]; then
        show_progress "构建CHTL编译器"
        
        local args=("-t" "$BUILD_TYPE" "-j" "$PARALLEL_JOBS")
        [ "$CLEAN" = true ] && args+=("-c")
        [ "$VERBOSE" = true ] && args+=("-v")
        [ "$TEST" = true ] && args+=("--test")
        
        if bash "${SCRIPT_DIR}/build_compiler.sh" "${args[@]}"; then
            print_success "编译器构建成功"
            return 0
        else
            print_error "编译器构建失败"
            return 1
        fi
    fi
    return 0
}

# 构建模块
build_modules() {
    if [ "$BUILD_MODULES" = true ]; then
        show_progress "构建CHTL模块"
        
        # 确保编译器存在
        if [ ! -f "${PROJECT_ROOT}/build/bin/chtlc" ] && [ "$BUILD_COMPILER" = false ]; then
            print_warning "编译器不存在，跳过模块构建"
            return 0
        fi
        
        local args=()
        [ "$CLEAN" = true ] && args+=("-c")
        [ "$VERBOSE" = true ] && args+=("-v")
        
        if bash "${SCRIPT_DIR}/pack_modules.sh" "${args[@]}"; then
            print_success "模块构建成功"
            return 0
        else
            print_error "模块构建失败"
            return 1
        fi
    fi
    return 0
}

# 构建IDE
build_ide() {
    if [ "$BUILD_IDE" = true ]; then
        show_progress "构建CHTL IDE"
        
        local args=("-t" "$BUILD_TYPE" "-j" "$PARALLEL_JOBS")
        [ "$CLEAN" = true ] && args+=("-c")
        [ "$VERBOSE" = true ] && args+=("-v")
        [ "$TEST" = true ] && args+=("--test")
        
        if bash "${SCRIPT_DIR}/build_ide.sh" "${args[@]}"; then
            print_success "IDE构建成功"
            return 0
        else
            print_error "IDE构建失败"
            return 1
        fi
    fi
    return 0
}

# 运行所有测试
run_all_tests() {
    if [ "$TEST" = true ]; then
        show_progress "运行测试套件"
        
        local test_failed=false
        
        # 编译器测试
        if [ -f "${PROJECT_ROOT}/build/CTestTestfile.cmake" ]; then
            print_info "运行编译器测试..."
            cd "${PROJECT_ROOT}/build"
            if ! ctest --output-on-failure; then
                test_failed=true
            fi
        fi
        
        # IDE测试
        if [ -f "${PROJECT_ROOT}/ide/build/CTestTestfile.cmake" ]; then
            print_info "运行IDE测试..."
            cd "${PROJECT_ROOT}/ide/build"
            if ! ctest --output-on-failure; then
                test_failed=true
            fi
        fi
        
        # 集成测试
        if [ -f "${PROJECT_ROOT}/test/run_integration_tests.sh" ]; then
            print_info "运行集成测试..."
            if ! bash "${PROJECT_ROOT}/test/run_integration_tests.sh"; then
                test_failed=true
            fi
        fi
        
        if [ "$test_failed" = true ]; then
            print_error "某些测试失败"
            return 1
        else
            print_success "所有测试通过"
            return 0
        fi
    fi
    return 0
}

# 显示构建摘要
show_summary() {
    echo
    echo -e "${PURPLE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${PURPLE}构建摘要${NC}"
    echo -e "${PURPLE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    
    print_info "构建类型: $BUILD_TYPE"
    print_info "并行任务: $PARALLEL_JOBS"
    
    echo
    print_info "构建组件:"
    [ "$BUILD_COMPILER" = true ] && echo "  ✓ CHTL编译器"
    [ "$BUILD_MODULES" = true ] && echo "  ✓ CHTL模块"
    [ "$BUILD_IDE" = true ] && echo "  ✓ CHTL IDE"
    
    echo
    print_info "构建产物:"
    
    # 编译器
    if [ -f "${PROJECT_ROOT}/build/bin/chtlc" ]; then
        local compiler_size=$(ls -lh "${PROJECT_ROOT}/build/bin/chtlc" | awk '{print $5}')
        echo "  • 编译器: ${PROJECT_ROOT}/build/bin/chtlc ($compiler_size)"
    fi
    
    # 模块
    if [ -d "${PROJECT_ROOT}/build/module" ]; then
        local module_count=$(find "${PROJECT_ROOT}/build/module" -name "*.cmod" -o -name "*.cjmod" | wc -l)
        echo "  • 模块数: $module_count"
    fi
    
    # IDE
    if [ -f "${PROJECT_ROOT}/ide/build/bin/chtl-ide" ]; then
        local ide_size=$(ls -lh "${PROJECT_ROOT}/ide/build/bin/chtl-ide" | awk '{print $5}')
        echo "  • IDE: ${PROJECT_ROOT}/ide/build/bin/chtl-ide ($ide_size)"
    fi
    
    echo -e "${PURPLE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

# 确保脚本可执行
ensure_scripts_executable() {
    chmod +x "${SCRIPT_DIR}"/*.sh 2>/dev/null || true
}

# 主函数
main() {
    local start_time=$(date +%s)
    
    # 显示标题
    echo -e "${PURPLE}╔════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${PURPLE}║                    CHTL 统一构建系统                       ║${NC}"
    echo -e "${PURPLE}╚════════════════════════════════════════════════════════════╝${NC}"
    echo
    
    # 计算步骤
    calculate_steps
    
    # 显示构建配置
    print_info "构建配置:"
    print_info "  项目根目录: $PROJECT_ROOT"
    print_info "  构建类型: $BUILD_TYPE"
    print_info "  并行任务: $PARALLEL_JOBS"
    print_info "  清理构建: $CLEAN"
    print_info "  运行测试: $TEST"
    
    # 确保脚本可执行
    ensure_scripts_executable
    
    # 执行构建
    local build_failed=false
    
    if ! build_compiler; then
        build_failed=true
    fi
    
    if [ "$build_failed" = false ] && ! build_modules; then
        build_failed=true
    fi
    
    if [ "$build_failed" = false ] && ! build_ide; then
        build_failed=true
    fi
    
    if [ "$build_failed" = false ] && ! run_all_tests; then
        build_failed=true
    fi
    
    # 计算耗时
    local end_time=$(date +%s)
    local duration=$((end_time - start_time))
    local minutes=$((duration / 60))
    local seconds=$((duration % 60))
    
    # 显示结果
    echo
    if [ "$build_failed" = true ]; then
        print_error "构建失败！"
        show_summary
        print_info "总耗时: ${minutes}分${seconds}秒"
        exit 1
    else
        print_success "构建成功！"
        show_summary
        print_info "总耗时: ${minutes}分${seconds}秒"
        
        # 显示下一步提示
        echo
        print_info "下一步操作:"
        print_info "  1. 运行编译器: ${PROJECT_ROOT}/build/bin/chtlc <file.chtl>"
        print_info "  2. 运行IDE: ${PROJECT_ROOT}/ide/build/bin/chtl-ide"
        print_info "  3. 安装到系统: sudo make install"
    fi
}

# 执行主函数
main