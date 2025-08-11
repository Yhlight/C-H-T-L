# Building CHTL

## Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.14 or higher
- Ninja (recommended) or Make

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake ninja-build
```

### macOS
```bash
brew install cmake ninja
```

### Windows
Install Visual Studio 2017 or later with C++ development tools, or use MinGW-w64.

## Quick Build

```bash
# Clone the repository
git clone https://github.com/yourusername/chtl.git
cd chtl

# Build with Make
make build

# Or build with CMake directly
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

## Build Options

### Release Build (Optimized)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Debug Build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### With Ninja (Faster builds)
```bash
cmake -B build -G Ninja
ninja -C build
```

## Testing

### Run Tests
```bash
make test
# or
./scripts/run-tests.sh
```

### Run Specific Test
```bash
./build/chtl test-var-function-fixed.chtl -o output
```

## Docker Build

### Production Image
```bash
docker build -t chtl:latest .
```

### Development Environment
```bash
docker-compose run --rm chtl-dev
```

## Installation

### System-wide Installation
```bash
make install
# or
cd build && sudo make install
```

### Local Installation
```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=$HOME/.local
cmake --build build --target install
```

## Development

### Code Formatting
```bash
make format
```

### Linting
```bash
make lint
```

### Generate Documentation
```bash
make docs
```

### Code Coverage
```bash
make coverage
```

## Troubleshooting

### Missing Dependencies
If you encounter "file not found" errors, ensure all submodules are initialized:
```bash
git submodule update --init --recursive
```

### Compilation Errors
1. Ensure your compiler supports C++17
2. Check CMake version: `cmake --version`
3. Clean and rebuild: `make clean && make build`

### Runtime Errors
Set debug environment variable for verbose output:
```bash
export CHTL_DEBUG=1
./chtl your-file.chtl
```

## Platform-Specific Notes

### Linux
- Use system package manager for dependencies
- May need to install `libstdc++-dev` separately

### macOS
- Xcode Command Line Tools required
- Use Homebrew for dependency management

### Windows
- Recommend using vcpkg for dependency management
- MSYS2 provides Unix-like environment
- Visual Studio 2019+ recommended

## CI/CD

The project uses GitHub Actions for continuous integration. See `.github/workflows/ci.yml` for the build matrix.

### Running CI Locally
```bash
act -j build  # Requires 'act' tool
```