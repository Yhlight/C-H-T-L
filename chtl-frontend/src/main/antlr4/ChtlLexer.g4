lexer grammar ChtlLexer;

// Keywords
TEXT: 'text';
STYLE: 'style';
SCRIPT: 'script';
INHERIT: 'inherit';
DELETE: 'delete';
INSERT: 'insert';
AFTER: 'after';
BEFORE: 'before';
REPLACE: 'replace';
AT_TOP: 'at' WS+ 'top';
AT_BOTTOM: 'at' WS+ 'bottom';
FROM: 'from';
AS: 'as';
EXCEPT: 'except';

// Template and Custom keywords
TEMPLATE: '[Template]';
CUSTOM: '[Custom]';
ORIGIN: '[Origin]';
IMPORT: '[Import]';
NAMESPACE: '[Namespace]';
CONFIGURATION: '[Configuration]';
INFO: '[Info]';
EXPORT: '[Export]';

// Special symbols
AT_STYLE: '@Style';
AT_ELEMENT: '@Element';
AT_VAR: '@Var';
AT_HTML: '@Html';
AT_JAVASCRIPT: '@JavaScript';
AT_CHTL: '@Chtl';

// Operators
COLON: ':';
SEMICOLON: ';';
EQUALS: '=';
COMMA: ',';
DOT: '.';
ARROW: '->';
AMPERSAND: '&';
LBRACE: '{';
RBRACE: '}';
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';

// Special JavaScript operators
DOUBLE_LBRACE: '{{';
DOUBLE_RBRACE: '}}';

// Comments
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
HTML_COMMENT: '--' ~[\r\n]*;

// String literals
DOUBLE_QUOTE_STRING: '"' (~["\\\r\n] | '\\' .)* '"';
SINGLE_QUOTE_STRING: '\'' (~['\\\r\n] | '\\' .)* '\'';

// Identifiers
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_-]*;
NUMBER: [0-9]+;
DECIMAL: [0-9]+ '.' [0-9]+;

// CSS-like unquoted literals (for style values)
UNQUOTED_LITERAL: ~[{};:,\s\"\'()]+ 
    {
        // Allow unquoted literals in style contexts
        String text = getText();
        // Don't match if it's a keyword
        if (text.equals("text") || text.equals("style") || text.equals("script") ||
            text.equals("inherit") || text.equals("delete") || text.equals("insert") ||
            text.equals("from") || text.equals("as") || text.equals("except")) {
            setType(IDENTIFIER);
        }
    };

// Whitespace
WS: [ \t\r\n]+ -> skip;

// Catch-all for any other character
ANY: .;