#!/bin/bash
# Download and build ANTLR4 Runtime

set -e

ANTLR4_VERSION="4.13.1"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check dependencies
if ! command -v wget &> /dev/null && ! command -v curl &> /dev/null; then
    print_error "wget or curl is required to download ANTLR4"
    exit 1
fi

if ! command -v cmake &> /dev/null; then
    print_error "CMake is required to build ANTLR4"
    exit 1
fi

# Download ANTLR4 runtime source
print_info "Downloading ANTLR4 runtime v${ANTLR4_VERSION}..."

DOWNLOAD_URL="https://github.com/antlr/antlr4/archive/refs/tags/${ANTLR4_VERSION}.tar.gz"
ARCHIVE_NAME="antlr4-${ANTLR4_VERSION}.tar.gz"

if command -v wget &> /dev/null; then
    wget -O "$ARCHIVE_NAME" "$DOWNLOAD_URL"
else
    curl -L -o "$ARCHIVE_NAME" "$DOWNLOAD_URL"
fi

# Extract
print_info "Extracting archive..."
tar -xzf "$ARCHIVE_NAME"

# Copy runtime source
print_info "Copying runtime source..."
rm -rf src
cp -r "antlr4-${ANTLR4_VERSION}/runtime/Cpp/runtime/src" .

# Build
print_info "Building ANTLR4 runtime..."
mkdir -p build
cd build

cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DANTLR4_BUILD_SHARED=ON \
    -DANTLR4_BUILD_STATIC=ON \
    -DCMAKE_INSTALL_PREFIX=..

cmake --build . --config Release -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Install to local directories
print_info "Installing to local directories..."
cmake --install .

# Clean up
cd ..
rm -rf "build" "antlr4-${ANTLR4_VERSION}" "$ARCHIVE_NAME"

print_success "ANTLR4 runtime v${ANTLR4_VERSION} built successfully!"
print_info "Headers: include/"
print_info "Libraries: lib/"