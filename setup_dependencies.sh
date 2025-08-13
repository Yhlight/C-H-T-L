#!/bin/bash
# Setup CHTL dependencies

set -e

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

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "========================================"
echo "CHTL Dependencies Setup"
echo "========================================"
echo

# Check if ANTLR4 source is present
if [ -d "third_party/antlr4-runtime/src" ]; then
    print_info "ANTLR4 runtime source already present"
else
    print_info "Downloading ANTLR4 runtime source..."
    
    # Make script executable
    chmod +x third_party/antlr4-runtime/download_source.sh
    
    # Run the download script
    cd third_party/antlr4-runtime
    ./download_source.sh
    if [ $? -ne 0 ]; then
        print_error "Failed to download ANTLR4 runtime source"
        exit 1
    fi
    cd "$SCRIPT_DIR"
    
    print_success "ANTLR4 runtime source downloaded"
fi

# Check if ANTLR4 JAR exists
if [ -f "tools/antlr-4.13.1-complete.jar" ]; then
    print_info "ANTLR4 tool JAR is already present"
else
    print_info "Downloading ANTLR4 tool JAR..."
    
    mkdir -p tools
    cd tools
    
    if command -v wget &> /dev/null; then
        wget https://www.antlr.org/download/antlr-4.13.1-complete.jar
    else
        curl -O https://www.antlr.org/download/antlr-4.13.1-complete.jar
    fi
    
    cd "$SCRIPT_DIR"
    print_success "ANTLR4 tool JAR downloaded"
fi

# Generate parsers
if [ -d "generated/css" ] && [ -d "generated/js" ]; then
    print_info "Parsers already generated"
else
    print_info "Generating parsers..."
    
    # Check Java
    if ! command -v java &> /dev/null; then
        print_warning "Java not found. Parser generation skipped."
        print_warning "Please install Java to generate parsers."
    else
        # Generate CSS parser
        if [ -f "grammars/CSS3.g4" ]; then
            print_info "Generating CSS parser..."
            mkdir -p generated/css
            java -jar tools/antlr-4.13.1-complete.jar \
                -Dlanguage=Cpp -no-listener -visitor \
                -o generated/css grammars/CSS3.g4
        fi
        
        # Generate JS parser
        if [ -f "grammars/JavaScriptLexer.g4" ] && [ -f "grammars/JavaScriptParser.g4" ]; then
            print_info "Generating JavaScript parser..."
            mkdir -p generated/js
            java -jar tools/antlr-4.13.1-complete.jar \
                -Dlanguage=Cpp -no-listener -visitor \
                -o generated/js grammars/JavaScriptLexer.g4
            java -jar tools/antlr-4.13.1-complete.jar \
                -Dlanguage=Cpp -no-listener -visitor \
                -o generated/js grammars/JavaScriptParser.g4
        fi
        
        print_success "Parsers generated"
    fi
fi

echo
echo "========================================"
echo "Setup completed!"
echo "========================================"
echo
print_info "Next steps:"
print_info "  1. Build CHTL: ./build.sh"
print_info "  2. Run tests: ./build.sh --test"
print_info "  3. Install: ./build.sh --install"
echo

exit 0