#!/bin/bash
# Download ANTLR4 Runtime Source

set -e

ANTLR4_VERSION="4.13.1"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
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

echo "========================================"
echo "Downloading ANTLR4 Runtime Source"
echo "========================================"
echo

# Check dependencies
if ! command -v wget &> /dev/null && ! command -v curl &> /dev/null; then
    print_error "wget or curl is required to download ANTLR4"
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

# Clean up
rm -rf "antlr4-${ANTLR4_VERSION}" "$ARCHIVE_NAME"

print_success "ANTLR4 runtime source downloaded successfully!"
print_info "Source location: src/"
echo
print_info "You can now build CHTL with the ANTLR4 runtime."
echo

exit 0