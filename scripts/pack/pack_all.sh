#!/bin/bash
# CHTL Module Packing Script for Unix

# Script directory and root directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$ROOT_DIR"

# Default values
OUTPUT_DIR="output"
PACK_TYPE="auto"
PACK_ALL=0
VERBOSE=0
BUILD_TYPE="Release"
MODULES=()
SUCCESS_COUNT=0
FAILED_COUNT=0
FAILED_MODULES=()

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Print functions
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Show help
show_help() {
    cat << EOF
CHTL Module Packing Script for Unix

Usage: $0 [modules...] [options]

Options:
  --help, -h          Show this help message
  --output DIR, -o    Output directory [default: output]
  --type TYPE, -t     Pack type (cmod, cjmod, auto) [default: auto]
  --all               Pack all modules in the module directory
  --build-type TYPE   Build type for CJMOD (Debug, Release) [default: Release]
  --verbose, -v       Enable verbose output

Examples:
  $0 --all
  $0 module/Chtholly
  $0 module/MyModule --type cmod
  $0 --all -o dist

EOF
    exit 0
}

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            ;;
        -o|--output)
            OUTPUT_DIR="$2"
            shift 2
            ;;
        -t|--type)
            PACK_TYPE="$2"
            shift 2
            ;;
        --all)
            PACK_ALL=1
            shift
            ;;
        --build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=1
            shift
            ;;
        *)
            MODULES+=("$1")
            shift
            ;;
    esac
done

# Check if we have modules to pack
if [ $PACK_ALL -eq 0 ] && [ ${#MODULES[@]} -eq 0 ]; then
    print_error "No modules specified. Use --all or specify module paths."
    show_help
fi

# Create output directory
mkdir -p "$OUTPUT_DIR"

echo "========================================"
echo "CHTL Module Packing"
echo "========================================"
echo "Output Directory: $OUTPUT_DIR"
echo "Pack Type: $PACK_TYPE"
echo "Build Type: $BUILD_TYPE"
echo "========================================"
echo

# Check dependencies
if ! command -v cmake &> /dev/null; then
    print_error "CMake not found. Required for CJMOD compilation."
    exit 1
fi

# Function to detect module type
detect_module_type() {
    local module_path="$1"
    
    local has_cmod=0
    local has_cjmod=0
    
    # Check for mixed module structure
    [ -d "$module_path/CMOD" ] && has_cmod=1
    [ -d "$module_path/CJMOD" ] && has_cjmod=1
    
    # Check for direct module structure
    if [ $has_cmod -eq 0 ] && [ $has_cjmod -eq 0 ]; then
        if [ -d "$module_path/src" ] && [ -d "$module_path/info" ]; then
            # Check file types
            if find "$module_path/src" -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" | grep -q .; then
                has_cjmod=1
            elif find "$module_path/src" -name "*.chtl" | grep -q .; then
                has_cmod=1
            fi
        fi
    fi
    
    if [ $has_cmod -eq 1 ] && [ $has_cjmod -eq 1 ]; then
        echo "mixed"
    elif [ $has_cmod -eq 1 ]; then
        echo "cmod"
    elif [ $has_cjmod -eq 1 ]; then
        echo "cjmod"
    else
        echo "unknown"
    fi
}

# Function to get module name
get_module_name() {
    local module_path="$1"
    local module_name=""
    
    # Try to find from info file
    for info_file in $(find "$module_path" -path "*/info/*.chtl" 2>/dev/null | head -1); do
        if [ -f "$info_file" ]; then
            module_name=$(basename "$info_file" .chtl)
            break
        fi
    done
    
    # Fallback to directory name
    [ -z "$module_name" ] && module_name=$(basename "$module_path")
    echo "$module_name"
}

# Function to pack CMOD
pack_cmod() {
    local module_path="$1"
    local module_name=$(get_module_name "$module_path")
    
    print_info "Packing CMOD: $module_name"
    
    # Find actual CMOD directory
    local actual_cmod_path=""
    if [ -d "$module_path/CMOD/$module_name" ]; then
        actual_cmod_path="$module_path/CMOD/$module_name"
    elif [ -d "$module_path/src" ] && [ -d "$module_path/info" ]; then
        actual_cmod_path="$module_path"
    fi
    
    if [ -z "$actual_cmod_path" ]; then
        print_error "No valid CMOD structure found"
        return 1
    fi
    
    # Create temporary directory
    local temp_dir=$(mktemp -d)
    mkdir -p "$temp_dir/$module_name"
    
    # Copy module files
    cp -r "$actual_cmod_path"/* "$temp_dir/$module_name/"
    
    # Create metadata
    cat > "$temp_dir/$module_name/.cmod_metadata" << EOF
{
  "module_name": "$module_name",
  "package_type": "CMOD",
  "created_at": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "platform": "all",
  "chtl_version": "1.0.0"
}
EOF
    
    # Create archive
    local output_file="$OUTPUT_DIR/${module_name}.cmod"
    rm -f "$output_file"
    
    # Create tar.gz archive
    (cd "$temp_dir" && tar -czf "$output_file" "$module_name")
    
    # Cleanup
    rm -rf "$temp_dir"
    
    if [ -f "$output_file" ]; then
        print_success "Created $output_file"
        return 0
    else
        print_error "Failed to create $output_file"
        return 1
    fi
}

# Function to pack CJMOD
pack_cjmod() {
    local module_path="$1"
    local module_name=$(get_module_name "$module_path")
    
    print_info "Packing CJMOD: $module_name"
    
    # Find actual CJMOD directory
    local actual_cjmod_path=""
    if [ -d "$module_path/CJMOD/$module_name" ]; then
        actual_cjmod_path="$module_path/CJMOD/$module_name"
    elif [ -d "$module_path/src" ]; then
        # Check for C++ files
        if find "$module_path/src" -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" | grep -q .; then
            actual_cjmod_path="$module_path"
        fi
    fi
    
    if [ -z "$actual_cjmod_path" ]; then
        print_error "No valid CJMOD structure found"
        return 1
    fi
    
    # Create build directory
    local build_dir=$(mktemp -d)
    
    # Create CMakeLists.txt
    cat > "$build_dir/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.16)
project($module_name LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE SOURCES "$actual_cjmod_path/src/*.cpp")

add_library($module_name SHARED \${SOURCES})

target_include_directories($module_name PRIVATE
    "$ROOT_DIR/src"
    "$actual_cjmod_path/src"
)

set_target_properties($module_name PROPERTIES
    PREFIX ""
    OUTPUT_NAME "$module_name"
)

if(APPLE)
    set_target_properties($module_name PROPERTIES
        SUFFIX ".dylib"
    )
endif()
EOF
    
    # Configure and build
    cd "$build_dir"
    if [ $VERBOSE -eq 1 ]; then
        cmake . -DCMAKE_BUILD_TYPE=$BUILD_TYPE
        cmake --build . --config $BUILD_TYPE
    else
        cmake . -DCMAKE_BUILD_TYPE=$BUILD_TYPE > /dev/null 2>&1
        cmake --build . --config $BUILD_TYPE > /dev/null 2>&1
    fi
    
    if [ $? -ne 0 ]; then
        print_error "Build failed"
        cd "$ROOT_DIR"
        rm -rf "$build_dir"
        return 1
    fi
    
    cd "$ROOT_DIR"
    
    # Find the built library
    local lib_file=""
    for ext in so dylib dll; do
        if [ -f "$build_dir/$module_name.$ext" ]; then
            lib_file="$build_dir/$module_name.$ext"
            break
        elif [ -f "$build_dir/lib$module_name.$ext" ]; then
            lib_file="$build_dir/lib$module_name.$ext"
            break
        fi
    done
    
    if [ -z "$lib_file" ]; then
        print_error "Built library not found"
        rm -rf "$build_dir"
        return 1
    fi
    
    # Create temporary directory for packaging
    local temp_dir=$(mktemp -d)
    mkdir -p "$temp_dir/$module_name/lib"
    
    # Copy files
    cp "$lib_file" "$temp_dir/$module_name/lib/"
    [ -d "$actual_cjmod_path/src" ] && cp -r "$actual_cjmod_path/src" "$temp_dir/$module_name/"
    [ -d "$actual_cjmod_path/info" ] && cp -r "$actual_cjmod_path/info" "$temp_dir/$module_name/"
    
    # Create metadata
    cat > "$temp_dir/$module_name/.cjmod_metadata" << EOF
{
  "module_name": "$module_name",
  "package_type": "CJMOD",
  "created_at": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "platform": "$(uname -s | tr '[:upper:]' '[:lower:]')",
  "architecture": "$(uname -m)",
  "chtl_version": "1.0.0"
}
EOF
    
    # Create archive
    local output_file="$OUTPUT_DIR/${module_name}.cjmod"
    rm -f "$output_file"
    
    # Create tar.gz archive
    (cd "$temp_dir" && tar -czf "$output_file" "$module_name")
    
    # Cleanup
    rm -rf "$temp_dir"
    rm -rf "$build_dir"
    
    if [ -f "$output_file" ]; then
        print_success "Created $output_file"
        return 0
    else
        print_error "Failed to create $output_file"
        return 1
    fi
}

# Function to pack a module
pack_module() {
    local module_path="$1"
    local module_name=$(basename "$module_path")
    
    echo "Processing module: $module_name"
    
    # Detect module type
    local module_type=$(detect_module_type "$module_path")
    echo "Module type: $module_type"
    
    if [ "$module_type" = "unknown" ]; then
        print_error "Unknown module type for $module_name"
        ((FAILED_COUNT++))
        FAILED_MODULES+=("$module_name")
        return 1
    fi
    
    # Pack based on type
    local pack_success=1
    
    if [ "$PACK_TYPE" = "auto" ]; then
        case "$module_type" in
            mixed)
                pack_cmod "$module_path" && ((SUCCESS_COUNT++)) || pack_success=0
                pack_cjmod "$module_path" && ((SUCCESS_COUNT++)) || pack_success=0
                ;;
            cmod)
                pack_cmod "$module_path" && ((SUCCESS_COUNT++)) || pack_success=0
                ;;
            cjmod)
                pack_cjmod "$module_path" && ((SUCCESS_COUNT++)) || pack_success=0
                ;;
        esac
    elif [ "$PACK_TYPE" = "cmod" ]; then
        pack_cmod "$module_path" && ((SUCCESS_COUNT++)) || pack_success=0
    elif [ "$PACK_TYPE" = "cjmod" ]; then
        pack_cjmod "$module_path" && ((SUCCESS_COUNT++)) || pack_success=0
    fi
    
    if [ $pack_success -eq 0 ]; then
        ((FAILED_COUNT++))
        FAILED_MODULES+=("$module_name")
    fi
    
    echo
}

# Main execution
if [ $PACK_ALL -eq 1 ]; then
    print_info "Packing all modules..."
    for module_dir in src/module/*/; do
        if [ -d "$module_dir" ]; then
            pack_module "$module_dir"
        fi
    done
else
    for module in "${MODULES[@]}"; do
        if [ -d "$module" ]; then
            pack_module "$module"
        else
            print_warning "Module not found: $module"
            ((FAILED_COUNT++))
            FAILED_MODULES+=("$module")
        fi
    done
fi

# Show summary
echo
echo "========================================"
echo "Packing Summary"
echo "========================================"
echo "Total processed: $((SUCCESS_COUNT + FAILED_COUNT))"
echo "Success: $SUCCESS_COUNT"
echo "Failed: $FAILED_COUNT"

if [ ${#FAILED_MODULES[@]} -gt 0 ]; then
    echo
    echo "Failed modules:"
    for module in "${FAILED_MODULES[@]}"; do
        echo "  - $module"
    done
fi

echo "========================================"

[ $FAILED_COUNT -eq 0 ] && exit 0 || exit 1