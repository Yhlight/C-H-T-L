# CHTL Scripts Directory Structure

This directory contains all CHTL project scripts, organized by function and platform.

## Directory Structure

```
scripts/
├── build/              # Build scripts
│   ├── build_all.sh        # Build all components
│   ├── build_compiler.sh   # Build compiler only
│   └── build_ide.sh        # Build IDE only
│
├── pack/               # Packaging scripts
│   ├── pack_all.sh         # Pack all modules
│   ├── pack_cmod.sh        # Pack CMOD modules
│   ├── pack_cjmod.sh       # Pack CJMOD modules
│   └── pack_modules.sh     # Pack multiple modules
│
├── clean/              # Cleanup scripts
│   └── clean_project.sh    # Clean project
│
├── setup/              # Setup scripts
│   └── (to be added)
│
├── utils/              # Utility scripts
│   └── extract_antlr_runtime.sh  # Extract ANTLR runtime
│
└── platform/           # Platform-specific scripts
    ├── windows/            # Windows batch scripts
    │   ├── build.bat           # Windows build script
    │   ├── pack.bat            # Windows pack script
    │   └── setup-windows.bat   # Windows environment setup
    ├── linux/              # Linux-specific scripts
    └── macos/              # macOS-specific scripts
```

## Usage

### Recommended Method (Using root directory entry scripts)

From the project root directory, we provide convenient entry scripts:

**Windows:**
```cmd
build.bat --type Release
pack.bat --all
```

**Linux/macOS:**
```bash
./build.sh --type Release
./pack.sh --all
```

### Direct Script Usage

If you need to use specific scripts:

**Build compiler (Linux/macOS):**
```bash
./scripts/build/build_compiler.sh
```

**Setup Windows environment:**
```cmd
scripts\platform\windows\setup-windows.bat
```

## Script Categories

### build/ - Build Scripts
- Contains build scripts for compiler, IDE, and other components
- Mainly shell scripts for Linux/macOS

### pack/ - Packaging Scripts
- CMOD/CJMOD module packaging
- Supports batch packaging

### clean/ - Cleanup Scripts
- Clean build artifacts
- Reset project state

### platform/ - Platform-Specific Scripts
- Windows batch files
- Platform-specific optimizations and settings

## Development Guidelines

1. New scripts should be placed in the appropriate functional directory
2. Use native platform scripts (batch for Windows, shell for Unix)
3. Platform-specific scripts go under platform/
4. Provide convenient entry scripts in the root directory