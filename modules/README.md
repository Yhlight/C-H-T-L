# CHTL Official Modules

This directory contains the official CHTL modules that are bundled with the VS Code extension.

## Directory Structure

```
modules/
├── std/          # Standard library modules
│   ├── base.chtl # Basic UI components
│   └── ...
├── ui/           # Advanced UI components
├── utils/        # Utility modules
└── README.md     # This file
```

## Module Types

### Standard Library (`std/`)
Core components and utilities that are commonly used in CHTL applications.

### UI Components (`ui/`)
Advanced UI components for building rich user interfaces.

### Utilities (`utils/`)
Helper functions and utilities for common tasks.

## Usage

In your CHTL files, you can import these modules using:

```chtl
[Import] @Chtl from "std/base.chtl";
```

The VS Code extension automatically includes these modules and makes them available to the CHTL compiler.