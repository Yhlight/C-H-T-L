grammar CHTL;

// Parser rules
program
    : statement* EOF
    ;

statement
    : elementNode
    | textBlock
    | styleBlock
    | scriptBlock
    | templateDecl
    | customDecl
    | originDecl
    | configurationDecl
    | importStmt
    | namespaceDecl
    | SEMI
    ;

// Elements like: div { ... }
// HTML tag names are treated as IDENT by default
elementNode
    : elementName block
    ;

// Allow keywords as element names as well (except ones we treat specially)
elementName
    : IDENT
    | KEYWORD_HTML
    | KEYWORD_HEAD
    | KEYWORD_BODY
    | KEYWORD_SPAN
    | KEYWORD_DIV
    | KEYWORD_BUTTON
    | KEYWORD_SCRIPT_KW // only when used as element name without special parsing
    ;

block
    : LBRACE blockItem* RBRACE
    ;

blockItem
    : attribute
    | elementNode
    | textBlock
    | styleBlock
    | scriptBlock
    | templateUsage
    | deleteStmt
    | inheritStmt
    | insertStmt
    | exceptStmt
    | SEMI
    ;

// text { ... }
textBlock
    : KEYWORD_TEXT blockText
    ;

blockText
    : LBRACE textLine* RBRACE
    ;

textLine
    : textPiece+
    ;

textPiece
    : STRING
    | IDENT
    | NUMBER
    | DOT
    | HASH
    | COMMA
    | LPAREN
    | RPAREN
    | COLON
    | EQUAL
    ;

// style { inline declarations only for now }
styleBlock
    : KEYWORD_STYLE blockStyle
    ;

blockStyle
    : LBRACE styleItem* RBRACE
    ;

styleItem
    : attribute
    | templateUsage
    | SEMI
    ;

// script { ... } kept permissive; capture as nested free-form tokens
scriptBlock
    : KEYWORD_SCRIPT_KW blockScript
    ;

blockScript
    : LBRACE scriptLine* RBRACE
    ;

scriptLine
    : scriptPiece+
    ;

scriptPiece
    : STRING
    | IDENT
    | NUMBER
    | DOT
    | HASH
    | COMMA
    | LPAREN
    | RPAREN
    | COLON
    | EQUAL
    ;

// attribute: key : value ;  (':' and '=' are equivalent)
attribute
    : IDENT (COLON|EQUAL) value SEMI
    ;

value
    : valuePiece+
    ;

valuePiece
    : STRING
    | IDENT
    | NUMBER
    | DOT
    | HASH
    | COMMA
    | LPAREN
    | RPAREN
    ;

// @Element Box;  or @Style WhiteText; or @Var ThemeColor;
templateUsage
    : atType IDENT SEMI
    ;

// [Template] @Style Name { ... }
templateDecl
    : KEYWORD_TEMPLATE atType IDENT block
    ;

// [Custom] @Style Name { ... } / [Custom] @Element Name { ... }
customDecl
    : KEYWORD_CUSTOM atType IDENT block
    ;

// [Origin] @Html (name)? { ... }
originDecl
    : KEYWORD_ORIGIN atType (IDENT)? block
    ;

// [Configuration] { ... } (permissive)
configurationDecl
    : KEYWORD_CONFIGURATION block
    ;

// [Import] ... from X (as Y)?
importStmt
    : KEYWORD_IMPORT importTarget FROM importPath (AS IDENT)? SEMI?
    ;

importTarget
    : atType
    | AT_CHTL
    | KEYWORD_CUSTOM atType
    | KEYWORD_TEMPLATE atType
    ;

importPath
    : STRING
    ;

// [Namespace] name (block)?
namespaceDecl
    : KEYWORD_NAMESPACE IDENT (block)?
    ;

// inherit @Style Name;
inheritStmt
    : KEYWORD_INHERIT atType IDENT SEMI
    ;

// delete property1, property2; OR delete @Style Name;
deleteStmt
    : KEYWORD_DELETE (atType IDENT | identList) SEMI
    ;

identList
    : IDENT (COMMA IDENT)*
    ;

// insert after div[0] { ... }  (simplified)
insertStmt
    : KEYWORD_INSERT (KEYWORD_AFTER|KEYWORD_BEFORE|KEYWORD_REPLACE|KEYWORD_AT TOP_KW|KEYWORD_AT BOTTOM_KW)? selector? block
    ;

selector
    : IDENT (LBRACK NUMBER RBRACK)?
    ;

exceptStmt
    : KEYWORD_EXCEPT exceptTargetList SEMI
    ;

exceptTargetList
    : exceptTarget (COMMA exceptTarget)*
    ;

exceptTarget
    : IDENT
    | KEYWORD_CUSTOM
    | KEYWORD_TEMPLATE atType
    | atType
    ;

atType
    : AT_STYLE
    | AT_ELEMENT
    | AT_VAR
    | AT_HTML
    | AT_JS
    ;

// Lexer rules
KEYWORD_TEXT: 'text';
KEYWORD_STYLE: 'style';
KEYWORD_SCRIPT_KW: 'script';
KEYWORD_TEMPLATE: '[Template]';
KEYWORD_CUSTOM: '[Custom]';
KEYWORD_ORIGIN: '[Origin]';
KEYWORD_CONFIGURATION: '[Configuration]';
KEYWORD_IMPORT: '[Import]';
KEYWORD_NAMESPACE: '[Namespace]';
KEYWORD_HTML: 'html';
KEYWORD_HEAD: 'head';
KEYWORD_BODY: 'body';
KEYWORD_DIV: 'div';
KEYWORD_SPAN: 'span';
KEYWORD_BUTTON: 'button';

KEYWORD_INHERIT: 'inherit';
KEYWORD_DELETE: 'delete';
KEYWORD_INSERT: 'insert';
KEYWORD_AFTER: 'after';
KEYWORD_BEFORE: 'before';
KEYWORD_REPLACE: 'replace';
KEYWORD_AT: 'at';
TOP_KW: 'top';
BOTTOM_KW: 'bottom';
KEYWORD_FROM: 'from';
KEYWORD_AS: 'as';
KEYWORD_EXCEPT: 'except';

AT_STYLE: '@Style' | '@style' | '@CSS' | '@Css' | '@css';
AT_ELEMENT: '@Element';
AT_VAR: '@Var';
AT_HTML: '@Html';
AT_JS: '@JavaScript';
AT_CHTL: '@Chtl';

FROM: KEYWORD_FROM;
AS: KEYWORD_AS;

LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
LPAREN: '(';
RPAREN: ')';
COLON: ':';
EQUAL: '=';
SEMI: ';';
COMMA: ',';
DOT: '.';
HASH: '#';

NUMBER: [0-9]+ ('.' [0-9]+)?;

// IDENT allows hyphen and underscore to be friendly with CSS-like names
IDENT: [a-zA-Z_] [a-zA-Z0-9_-]*;

STRING
    : '"' (ESC | ~["\\])* '"'
    | '\'' (ESC | ~['\\])* '\''
    ;

fragment ESC: '\\' [btnfr"'\\];

LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
SPECIAL_COMMENT: '--' ~[\r\n]* -> skip;

WS: [ \t\r\n]+ -> skip;