#!/bin/bash
# CHTL IDE构建脚本

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
IDE_ROOT="${PROJECT_ROOT}/ide"

# 默认参数
BUILD_TYPE="Debug"
BUILD_DIR="${IDE_ROOT}/build"
INSTALL_PREFIX="${PROJECT_ROOT}/install"
PARALLEL_JOBS=$(nproc 2>/dev/null || echo 4)
CLEAN_BUILD=false
RUN_TESTS=false
VERBOSE=false
PACKAGE=false

# 显示帮助
show_help() {
    cat << EOF
CHTL IDE构建脚本

用法: $0 [选项]

选项:
    -h, --help              显示此帮助信息
    -t, --type TYPE         构建类型 (Debug|Release|RelWithDebInfo) [默认: Debug]
    -d, --build-dir DIR     构建目录 [默认: ./ide/build]
    -p, --prefix DIR        安装前缀 [默认: ./install]
    -j, --jobs N            并行编译任务数 [默认: $(nproc)]
    -c, --clean             清理构建目录后重新构建
    --test                  运行测试
    --package               打包IDE
    -v, --verbose           显示详细输出

示例:
    $0                      # 默认Debug构建
    $0 -t Release --package # Release构建并打包
    $0 --clean -j 8         # 清理构建，8个并行任务

功能:
    - 基于Qt5的跨平台IDE
    - 集成VSCode核心编辑器
    - 支持CHTL语法高亮和智能提示
    - 内置编译器和调试器
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
        --test)
            RUN_TESTS=true
            shift
            ;;
        --package)
            PACKAGE=true
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

# 检查依赖
check_dependencies() {
    print_info "检查IDE构建依赖..."
    
    local missing_deps=()
    
    # 基础工具
    command -v cmake >/dev/null 2>&1 || missing_deps+=("cmake")
    command -v make >/dev/null 2>&1 || missing_deps+=("make")
    command -v g++ >/dev/null 2>&1 || missing_deps+=("g++")
    
    # Qt5检查
    if ! pkg-config --exists Qt5Core Qt5Widgets Qt5WebEngineWidgets 2>/dev/null; then
        missing_deps+=("qt5-default" "libqt5webengine5-dev")
    fi
    
    # Node.js检查（用于VSCode集成）
    if ! command -v node >/dev/null 2>&1; then
        print_warning "未找到Node.js，将跳过VSCode编辑器集成"
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        print_error "缺少以下依赖: ${missing_deps[*]}"
        print_info "安装命令:"
        print_info "  Ubuntu/Debian: sudo apt-get install ${missing_deps[*]}"
        print_info "  macOS: brew install qt5 cmake"
        exit 1
    fi
    
    print_success "依赖检查通过"
}

# 清理构建目录
clean_build() {
    if [ "$CLEAN_BUILD" = true ] && [ -d "$BUILD_DIR" ]; then
        print_info "清理IDE构建目录..."
        rm -rf "$BUILD_DIR"
        print_success "清理完成"
    fi
}

# 准备VSCode编辑器
prepare_vscode_editor() {
    print_info "准备VSCode编辑器组件..."
    
    local vscode_dir="${IDE_ROOT}/src/editor/vscode"
    
    if [ ! -d "$vscode_dir" ]; then
        print_info "创建VSCode编辑器目录..."
        mkdir -p "$vscode_dir"
        
        # 创建编辑器配置
        cat > "$vscode_dir/editor-config.json" << EOF
{
    "editor": {
        "theme": "vs-dark",
        "fontSize": 14,
        "fontFamily": "Consolas, 'Courier New', monospace",
        "lineNumbers": "on",
        "minimap": {
            "enabled": true
        },
        "suggest": {
            "snippetsPreventQuickSuggestions": false
        }
    },
    "languages": [{
        "id": "chtl",
        "extensions": [".chtl"],
        "aliases": ["CHTL", "chtl"]
    }]
}
EOF
    fi
    
    # 检查是否需要下载Monaco编辑器
    if [ ! -f "$vscode_dir/monaco.min.js" ] && command -v wget >/dev/null 2>&1; then
        print_info "下载Monaco编辑器..."
        wget -q -O "$vscode_dir/monaco.min.js" \
            "https://unpkg.com/monaco-editor@latest/min/vs/loader.js" || \
            print_warning "无法下载Monaco编辑器，将使用基础编辑器"
    fi
}

# 配置CMake
configure_cmake() {
    print_info "配置IDE CMake..."
    
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    local cmake_args=(
        "-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
        "-DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX"
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
        "-DCHTL_COMPILER_PATH=${PROJECT_ROOT}/build/bin/chtlc"
    )
    
    if [ "$VERBOSE" = true ]; then
        cmake_args+=("-DCMAKE_VERBOSE_MAKEFILE=ON")
    fi
    
    # Qt5特定配置
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS Qt5路径
        cmake_args+=("-DCMAKE_PREFIX_PATH=/usr/local/opt/qt@5")
    fi
    
    cmake "${cmake_args[@]}" "$IDE_ROOT"
    
    print_success "CMake配置完成"
}

# 构建IDE
build_project() {
    print_info "开始构建IDE..."
    cd "$BUILD_DIR"
    
    local make_args=("-j$PARALLEL_JOBS")
    
    if [ "$VERBOSE" = true ]; then
        make_args+=("VERBOSE=1")
    fi
    
    if make "${make_args[@]}"; then
        print_success "IDE构建完成"
    else
        print_error "IDE构建失败"
        exit 1
    fi
}

# 运行测试
run_tests() {
    if [ "$RUN_TESTS" = true ]; then
        print_info "运行IDE测试..."
        cd "$BUILD_DIR"
        
        if [ -f "CTestTestfile.cmake" ]; then
            if ctest --output-on-failure; then
                print_success "所有测试通过"
            else
                print_error "某些测试失败"
                exit 1
            fi
        else
            print_warning "没有找到测试文件"
        fi
    fi
}

# 打包IDE
package_ide() {
    if [ "$PACKAGE" = true ]; then
        print_info "打包IDE..."
        
        local package_dir="${BUILD_DIR}/package"
        local app_name="CHTL-IDE"
        
        mkdir -p "$package_dir"
        
        # 根据平台创建不同的包
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            # Linux AppImage
            print_info "创建Linux AppImage..."
            
            # 创建AppDir结构
            local app_dir="$package_dir/${app_name}.AppDir"
            mkdir -p "$app_dir/usr/bin"
            mkdir -p "$app_dir/usr/share/applications"
            mkdir -p "$app_dir/usr/share/icons/hicolor/256x256/apps"
            
            # 复制可执行文件
            cp "$BUILD_DIR/bin/chtl-ide" "$app_dir/usr/bin/"
            
            # 创建desktop文件
            cat > "$app_dir/usr/share/applications/chtl-ide.desktop" << EOF
[Desktop Entry]
Type=Application
Name=CHTL IDE
Comment=Integrated Development Environment for CHTL
Exec=chtl-ide
Icon=chtl-ide
Categories=Development;IDE;
Terminal=false
EOF
            
            # 复制图标（假设存在）
            if [ -f "${IDE_ROOT}/resources/icon.png" ]; then
                cp "${IDE_ROOT}/resources/icon.png" "$app_dir/usr/share/icons/hicolor/256x256/apps/chtl-ide.png"
            fi
            
            print_success "Linux包准备完成: $app_dir"
            
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            # macOS App Bundle
            print_info "创建macOS App Bundle..."
            
            local app_bundle="$package_dir/${app_name}.app"
            mkdir -p "$app_bundle/Contents/MacOS"
            mkdir -p "$app_bundle/Contents/Resources"
            
            # 复制可执行文件
            cp "$BUILD_DIR/bin/chtl-ide" "$app_bundle/Contents/MacOS/"
            
            # 创建Info.plist
            cat > "$app_bundle/Contents/Info.plist" << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>chtl-ide</string>
    <key>CFBundleIdentifier</key>
    <string>org.chtl.ide</string>
    <key>CFBundleName</key>
    <string>CHTL IDE</string>
    <key>CFBundleVersion</key>
    <string>1.0.0</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
</dict>
</plist>
EOF
            
            print_success "macOS App Bundle创建完成: $app_bundle"
            
        elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
            # Windows
            print_info "创建Windows包..."
            
            local win_dir="$package_dir/${app_name}-Windows"
            mkdir -p "$win_dir"
            
            # 复制可执行文件和依赖
            cp "$BUILD_DIR/bin/chtl-ide.exe" "$win_dir/" 2>/dev/null || \
                cp "$BUILD_DIR/bin/chtl-ide" "$win_dir/"
            
            # 创建启动脚本
            cat > "$win_dir/start-ide.bat" << EOF
@echo off
cd /d "%~dp0"
start chtl-ide.exe
EOF
            
            print_success "Windows包创建完成: $win_dir"
        fi
        
        print_info "打包输出目录: $package_dir"
    fi
}

# 安装IDE
install_ide() {
    print_info "安装IDE到 ${INSTALL_PREFIX}..."
    cd "$BUILD_DIR"
    
    if make install; then
        print_success "IDE安装完成"
        
        # 显示安装的文件
        print_info "已安装:"
        print_info "  IDE可执行文件: ${INSTALL_PREFIX}/bin/chtl-ide"
        print_info "  资源文件: ${INSTALL_PREFIX}/share/chtl-ide/"
        
        # 创建桌面快捷方式（Linux）
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            local desktop_file="$HOME/.local/share/applications/chtl-ide.desktop"
            mkdir -p "$(dirname "$desktop_file")"
            cat > "$desktop_file" << EOF
[Desktop Entry]
Type=Application
Name=CHTL IDE
Comment=Integrated Development Environment for CHTL
Exec=${INSTALL_PREFIX}/bin/chtl-ide
Icon=chtl-ide
Categories=Development;IDE;
Terminal=false
EOF
            print_success "已创建桌面快捷方式"
        fi
    else
        print_error "IDE安装失败"
        exit 1
    fi
}

# 主函数
main() {
    print_info "开始构建CHTL IDE..."
    print_info "构建类型: $BUILD_TYPE"
    print_info "构建目录: $BUILD_DIR"
    echo
    
    # 检查IDE源代码
    if [ ! -d "$IDE_ROOT" ]; then
        print_error "IDE源代码目录不存在: $IDE_ROOT"
        exit 1
    fi
    
    # 执行构建步骤
    check_dependencies
    clean_build
    prepare_vscode_editor
    configure_cmake
    build_project
    run_tests
    package_ide
    
    # 询问是否安装
    if [ -t 0 ]; then
        read -p "是否安装IDE到 ${INSTALL_PREFIX}? [y/N] " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            install_ide
        fi
    fi
    
    echo
    print_success "CHTL IDE构建完成!"
    print_info "IDE位置: ${BUILD_DIR}/bin/chtl-ide"
    
    # 显示下一步提示
    echo
    print_info "下一步:"
    print_info "  1. 运行IDE: ${BUILD_DIR}/bin/chtl-ide"
    print_info "  2. 安装IDE: cd ${BUILD_DIR} && make install"
    print_info "  3. 打包发布: $0 -t Release --package"
}

# 执行主函数
main