# CHTL Frontend Compiler

A complete frontend compiler for CHTL (C++ HTML Template Language) built using ANTLR4. CHTL is a hypertext language based on C++ that provides a more developer-friendly way to write HTML code.

## Features

- **Complete ANTLR4-based Parser**: Full lexical and syntactic analysis of CHTL files
- **AST Generation**: Builds a comprehensive Abstract Syntax Tree for semantic analysis
- **Semantic Analysis**: Type checking, symbol resolution, and error detection
- **HTML Generation**: Converts CHTL code to standard HTML/CSS/JavaScript
- **Template System**: Support for reusable templates and custom elements
- **Enhanced JavaScript**: Special syntax for DOM manipulation with `{{selector}}` notation
- **Auto-generated Classes/IDs**: Automatic class and ID generation from CSS selectors
- **Namespace Support**: Modular code organization with namespaces

## Project Structure

```
chtl-frontend/
├── src/
│   ├── main/
│   │   ├── antlr4/
│   │   │   ├── ChtlLexer.g4      # Lexer grammar
│   │   │   └── ChtlParser.g4     # Parser grammar
│   │   └── java/com/chtl/
│   │       ├── ChtlCompiler.java # Main compiler class
│   │       ├── parser/           # ANTLR generated parser
│   │       ├── ast/              # AST node classes
│   │       ├── analyzer/         # Semantic analyzer
│   │       └── generator/        # HTML code generator
│   └── test/                     # Unit tests
├── examples/                     # Example CHTL files
├── pom.xml                      # Maven configuration
└── README.md                    # This file
```

## Building the Project

### Prerequisites

- Java 11 or higher
- Maven 3.6 or higher

### Build Steps

1. Clone the repository:
```bash
cd /workspace/chtl-frontend
```

2. Build the project:
```bash
mvn clean package
```

This will:
- Generate the ANTLR4 parser from the grammar files
- Compile all Java sources
- Run tests
- Create an executable JAR file: `target/chtl-compiler.jar`

## Usage

### Command Line

```bash
java -jar target/chtl-compiler.jar input.chtl [output.html]
```

If no output file is specified, it will generate `input.html` in the same directory.

### Programmatic Usage

```java
import com.chtl.ChtlCompiler;
import com.chtl.CompilationResult;

ChtlCompiler compiler = new ChtlCompiler();
CompilationResult result = compiler.compile("input.chtl");

if (result.isSuccess()) {
    String html = result.getGeneratedCode().getCompleteHtml();
    // Use the generated HTML
} else {
    // Handle errors
    for (String error : result.getErrors()) {
        System.err.println(error);
    }
}
```

## CHTL Syntax Examples

### Basic HTML Structure

```chtl
html {
    head {
        title: "My CHTL Page";
    }
    
    body {
        h1 {
            text {
                "Welcome to CHTL"
            }
        }
        
        p {
            class: "intro";
            text {
                "This is a paragraph"
            }
        }
    }
}
```

### Styles with Auto-generated Classes

```chtl
div {
    style {
        .container {  // Auto-generates class="container"
            width: 100%;
            max-width: 1200px;
            margin: 0 auto;
        }
        
        &:hover {    // Context-aware selector
            background-color: #f0f0f0;
        }
    }
    
    text {
        "Content goes here"
    }
}
```

### Templates and Reusability

```chtl
[Template] @Element Card {
    div {
        style {
            .card {
                border: 1px solid #ddd;
                padding: 16px;
                border-radius: 8px;
            }
        }
        
        h3 {
            text { "Card Title" }
        }
        
        p {
            text { "Card content" }
        }
    }
}

// Use the template
body {
    @Element Card;
    @Element Card;
}
```

### Interactive JavaScript

```chtl
button {
    id: my-button;
    text { "Click me" }
    
    script {
        {{my-button}}->addEventListener('click', () => {
            alert('Button clicked!');
        });
    }
}
```

## Key Components

### 1. Lexer (`ChtlLexer.g4`)
- Tokenizes CHTL source code
- Handles comments, strings, identifiers, and special symbols
- Supports CSS-like unquoted literals

### 2. Parser (`ChtlParser.g4`)
- Defines the complete CHTL grammar
- Builds parse tree from tokens
- Supports all CHTL constructs

### 3. AST Builder (`ChtlAstBuilder.java`)
- Converts ANTLR parse tree to custom AST
- Provides cleaner structure for analysis

### 4. Semantic Analyzer (`SemanticAnalyzer.java`)
- Validates CHTL code
- Resolves references and symbols
- Checks for errors and warnings

### 5. HTML Generator (`HtmlGenerator.java`)
- Traverses AST to generate HTML
- Handles style and script aggregation
- Manages template expansion

## Advanced Features

### Custom Elements with Specialization

```chtl
[Custom] @Element FlexBox {
    div {
        style {
            display: flex;
        }
    }
}

// Use with modifications
@Element FlexBox {
    style {
        flex-direction: column;
        gap: 20px;
    }
}
```

### Namespace Support

```chtl
[Namespace] components {
    [Template] @Element Button {
        // Button implementation
    }
}

// Use namespaced element
body {
    @Element Button from components;
}
```

### Variable Groups

```chtl
[Template] @Var ThemeColors {
    primary: "#3498db";
    secondary: "#2ecc71";
}

div {
    style {
        background-color: ThemeColors(primary);
    }
}
```

## Error Handling

The compiler provides detailed error messages with line and column information:

```
ERROR at line 10, column 15: Undefined reference: @Style NonExistent
WARNING at line 25, column 8: 'mycustomtag' is not a standard HTML tag
```

## Contributing

To contribute to the CHTL compiler:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Submit a pull request

## License

This project is released under the MIT License.

## Future Enhancements

- [ ] Support for CMOD (CHTL modules) packaging
- [ ] CSS preprocessor integration
- [ ] Source maps for debugging
- [ ] IDE plugin support
- [ ] Incremental compilation
- [ ] Type checking for JavaScript enhanced selectors
- [ ] Import path resolution and validation

## Acknowledgments

- Built with [ANTLR4](https://www.antlr.org/) - A powerful parser generator
- Inspired by modern template languages and component frameworks