# CHTL Language Support for Visual Studio Code

This extension provides rich language support for CHTL (Component HTML Template Language) in Visual Studio Code.

## Features

### Syntax Highlighting
- Full syntax highlighting for CHTL files
- Embedded CSS and JavaScript highlighting
- Special highlighting for CHTL-specific syntax like `{{&}}` and `->`

### IntelliSense
- Auto-completion for:
  - HTML elements
  - CHTL keywords (`Import`, `Export`, `Custom`, etc.)
  - Attributes
  - CHTL JS methods (`listen`, `animate`, `delegate`)
- Hover information for keywords and functions
- Signature help

### Code Snippets
- Quick snippets for common patterns:
  - `imp` - Import statement
  - `custom` - Custom element
  - `template` - Template function
  - `style` - Style block
  - `script` - Script block
  - `btn` - Button with event handler
  - And many more!

### Commands
- **CHTL: Compile Current File** (`Ctrl+Shift+C` / `Cmd+Shift+C`)
- **CHTL: Preview in Browser**
- **CHTL: Create New Component**

### Formatting
- Automatic code formatting
- Configurable indentation

### Linting
- Real-time error checking
- Bracket matching validation
- Import syntax validation

## Requirements

- CHTL compiler installed and available in PATH
- VS Code 1.74.0 or higher

## Extension Settings

This extension contributes the following settings:

* `chtl.compiler.path`: Path to CHTL compiler executable (default: `chtl`)
* `chtl.format.enable`: Enable/disable formatting (default: `true`)
* `chtl.format.indentSize`: Number of spaces for indentation (default: `2`)
* `chtl.lint.enable`: Enable/disable linting (default: `true`)
* `chtl.autocomplete.enable`: Enable/disable auto-completion (default: `true`)

## Usage

1. Install the extension from VS Code Marketplace
2. Open any `.chtl` file
3. Enjoy syntax highlighting, IntelliSense, and other features!

### Compiling CHTL Files

1. Open a `.chtl` file
2. Press `Ctrl+Shift+C` (or `Cmd+Shift+C` on Mac)
3. The compiled output will be saved to the `dist` directory

### Creating Components

1. Run command: `CHTL: Create New Component`
2. Enter component name
3. A new component file will be created in the `components` directory

## Keyboard Shortcuts

- `Ctrl+Shift+C` / `Cmd+Shift+C` - Compile current file
- Standard VS Code shortcuts for formatting, etc.

## Known Issues

- Preview feature requires compiled output
- Some advanced CHTL features may not be fully supported yet

## Release Notes

### 1.0.0

Initial release with:
- Syntax highlighting
- Basic IntelliSense
- Code snippets
- Compilation support
- Formatting and linting

## Contributing

Found a bug or want to contribute? Visit our [GitHub repository](https://github.com/your-org/chtl-vscode).

## License

This extension is licensed under the MIT License.