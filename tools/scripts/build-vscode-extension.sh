#!/bin/bash

# VS Code扩展构建脚本

set -e

# 颜色定义
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 进入扩展目录
cd /workspace/vscode-extension/chtl-lang

print_info "Building CHTL VS Code Extension..."

# 检查是否安装了必要的工具
if ! command -v npm &> /dev/null; then
    print_error "npm is not installed"
    exit 1
fi

if ! command -v node &> /dev/null; then
    print_error "node is not installed"
    exit 1
fi

# 安装依赖
print_info "Installing dependencies..."
npm install

# 编译TypeScript
print_info "Compiling TypeScript..."
npm run compile

# 安装vsce（VS Code Extension工具）
if ! command -v vsce &> /dev/null; then
    print_info "Installing vsce..."
    npm install -g vsce
fi

# 打包扩展
print_info "Packaging extension..."
vsce package --out ../../dist/

print_info "Extension packaged successfully!"
print_info "Output: dist/chtl-lang-1.0.0.vsix"
print_info ""
print_info "To install the extension:"
print_info "  1. Open VS Code"
print_info "  2. Go to Extensions view (Ctrl+Shift+X)"
print_info "  3. Click '...' menu and select 'Install from VSIX...'"
print_info "  4. Select the generated .vsix file"