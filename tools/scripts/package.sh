#!/bin/bash

# CHTL打包脚本

set -e

# 版本信息
VERSION=$(grep "VERSION" CMakeLists.txt | head -1 | sed 's/.*VERSION \([0-9.]*\).*/\1/')
PACKAGE_NAME="chtl-${VERSION}"

# 颜色定义
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

# 打包格式
FORMATS=("tar.gz" "zip")
OUTPUT_DIR="dist"

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 首先构建项目
print_info "Building CHTL..."
./scripts/build.sh --clean

# 创建临时打包目录
TEMP_DIR=$(mktemp -d)
PACKAGE_DIR="$TEMP_DIR/$PACKAGE_NAME"
mkdir -p "$PACKAGE_DIR"

print_info "Preparing package contents..."

# 复制文件
cp -r include "$PACKAGE_DIR/"
cp -r src "$PACKAGE_DIR/"
cp -r modules "$PACKAGE_DIR/"
cp -r examples "$PACKAGE_DIR/"
cp -r docs "$PACKAGE_DIR/"
cp -r scripts "$PACKAGE_DIR/"
cp CMakeLists.txt "$PACKAGE_DIR/"
cp README.md "$PACKAGE_DIR/" 2>/dev/null || echo "# CHTL Compiler" > "$PACKAGE_DIR/README.md"
cp LICENSE "$PACKAGE_DIR/" 2>/dev/null || echo "MIT License" > "$PACKAGE_DIR/LICENSE"

# 创建二进制包
BINARY_DIR="$PACKAGE_DIR/bin"
mkdir -p "$BINARY_DIR"
cp build/chtl "$BINARY_DIR/" 2>/dev/null || print_warn "Binary not found"

# 创建安装脚本
cat > "$PACKAGE_DIR/install.sh" << 'EOF'
#!/bin/bash
set -e

echo "Installing CHTL..."

# 默认安装路径
PREFIX=${PREFIX:-/usr/local}

# 创建目录
sudo mkdir -p "$PREFIX/bin"
sudo mkdir -p "$PREFIX/include/chtl"
sudo mkdir -p "$PREFIX/share/chtl/modules"
sudo mkdir -p "$PREFIX/share/chtl/examples"

# 复制文件
sudo cp bin/chtl "$PREFIX/bin/"
sudo cp -r include/* "$PREFIX/include/chtl/"
sudo cp -r modules/* "$PREFIX/share/chtl/modules/"
sudo cp -r examples/* "$PREFIX/share/chtl/examples/"

# 设置权限
sudo chmod +x "$PREFIX/bin/chtl"

echo "CHTL installed successfully!"
echo "Add $PREFIX/bin to your PATH if not already added."
EOF

chmod +x "$PACKAGE_DIR/install.sh"

# 创建不同格式的包
for format in "${FORMATS[@]}"; do
    print_info "Creating $format package..."
    
    case $format in
        "tar.gz")
            cd "$TEMP_DIR"
            tar -czf "$OLDPWD/$OUTPUT_DIR/${PACKAGE_NAME}.tar.gz" "$PACKAGE_NAME"
            cd - > /dev/null
            print_info "Created: $OUTPUT_DIR/${PACKAGE_NAME}.tar.gz"
            ;;
        "zip")
            cd "$TEMP_DIR"
            zip -qr "$OLDPWD/$OUTPUT_DIR/${PACKAGE_NAME}.zip" "$PACKAGE_NAME"
            cd - > /dev/null
            print_info "Created: $OUTPUT_DIR/${PACKAGE_NAME}.zip"
            ;;
    esac
done

# 创建DEB包（如果在Debian/Ubuntu系统上）
if command -v dpkg-deb &> /dev/null; then
    print_info "Creating DEB package..."
    
    DEB_DIR="$TEMP_DIR/chtl_${VERSION}_amd64"
    mkdir -p "$DEB_DIR/DEBIAN"
    mkdir -p "$DEB_DIR/usr/bin"
    mkdir -p "$DEB_DIR/usr/include/chtl"
    mkdir -p "$DEB_DIR/usr/share/chtl/modules"
    mkdir -p "$DEB_DIR/usr/share/chtl/examples"
    
    # 复制文件
    cp build/chtl "$DEB_DIR/usr/bin/" 2>/dev/null || true
    cp -r include/* "$DEB_DIR/usr/include/chtl/"
    cp -r modules/* "$DEB_DIR/usr/share/chtl/modules/"
    cp -r examples/* "$DEB_DIR/usr/share/chtl/examples/"
    
    # 创建control文件
    cat > "$DEB_DIR/DEBIAN/control" << EOF
Package: chtl
Version: $VERSION
Section: devel
Priority: optional
Architecture: amd64
Maintainer: CHTL Development Team
Description: CHTL Compiler
 Component HTML Template Language compiler
 A modern template language for web development
EOF
    
    # 构建DEB包
    dpkg-deb --build "$DEB_DIR"
    mv "$TEMP_DIR/chtl_${VERSION}_amd64.deb" "$OUTPUT_DIR/"
    print_info "Created: $OUTPUT_DIR/chtl_${VERSION}_amd64.deb"
fi

# 创建RPM包（如果在RedHat/Fedora系统上）
if command -v rpmbuild &> /dev/null; then
    print_info "Creating RPM package..."
    # TODO: 实现RPM打包
    print_warn "RPM packaging not implemented yet"
fi

# 清理临时目录
rm -rf "$TEMP_DIR"

print_info "Packaging completed!"
print_info "Packages are available in: $OUTPUT_DIR/"
ls -la "$OUTPUT_DIR/"