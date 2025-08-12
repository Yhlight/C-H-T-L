parser grammar ChtlParser;

options {
    tokenVocab = ChtlLexer;
}

// Root rule
chtlFile
    : declaration* EOF
    ;

declaration
    : elementNode
    | textNode
    | templateDeclaration
    | customDeclaration
    | originDeclaration
    | importDeclaration
    | namespaceDeclaration
    | configurationDeclaration
    | infoDeclaration
    | exportDeclaration
    | styleBlock
    | scriptBlock
    ;

// Element nodes
elementNode
    : IDENTIFIER LBRACE elementContent* RBRACE
    | atReference SEMICOLON
    | atReference LBRACE specialization* RBRACE
    ;

elementContent
    : attribute
    | elementNode
    | textNode
    | styleBlock
    | scriptBlock
    | atReference SEMICOLON
    | atReference LBRACE specialization* RBRACE
    | inheritStatement
    | exceptStatement
    | originDeclaration
    ;

// Text nodes
textNode
    : TEXT LBRACE stringLiteral RBRACE
    ;

// Attributes
attribute
    : IDENTIFIER (COLON | EQUALS) attributeValue SEMICOLON
    ;

attributeValue
    : stringLiteral
    | IDENTIFIER
    | UNQUOTED_LITERAL
    | NUMBER
    | DECIMAL
    ;

// Style blocks
styleBlock
    : STYLE LBRACE styleContent* RBRACE
    ;

styleContent
    : cssProperty
    | cssRule
    | atReference SEMICOLON
    | atReference LBRACE specialization* RBRACE
    ;

cssProperty
    : IDENTIFIER (COLON | EQUALS) cssValue SEMICOLON
    ;

cssValue
    : stringLiteral
    | IDENTIFIER
    | UNQUOTED_LITERAL
    | NUMBER
    | DECIMAL
    | cssValue cssValue+  // Multiple values (e.g., margin: 10px 20px)
    | functionCall
    ;

cssRule
    : cssSelector LBRACE cssProperty* RBRACE
    ;

cssSelector
    : DOT IDENTIFIER  // Class selector
    | '#' IDENTIFIER  // ID selector
    | AMPERSAND (COLON IDENTIFIER)?  // & or &:hover
    | AMPERSAND '::' IDENTIFIER  // &::before
    ;

// Script blocks
scriptBlock
    : SCRIPT LBRACE jsContent* RBRACE
    ;

jsContent
    : enhancedSelector
    | jsStatement
    ;

enhancedSelector
    : DOUBLE_LBRACE selectorExpression DOUBLE_RBRACE
    ;

selectorExpression
    : IDENTIFIER (LBRACKET NUMBER RBRACKET)?  // box or box[0]
    | DOT IDENTIFIER  // .box
    | '#' IDENTIFIER  // #box
    | cssComplexSelector
    ;

cssComplexSelector
    : selectorPart (selectorPart)*
    ;

selectorPart
    : IDENTIFIER
    | DOT IDENTIFIER
    | '#' IDENTIFIER
    ;

jsStatement
    : ~(LBRACE | RBRACE | DOUBLE_LBRACE)+
    ;

// Template declarations
templateDeclaration
    : TEMPLATE templateType IDENTIFIER LBRACE templateContent* RBRACE
    ;

templateType
    : AT_STYLE
    | AT_ELEMENT
    | AT_VAR
    ;

templateContent
    : elementContent
    | cssProperty
    | varDeclaration
    | inheritStatement
    ;

// Custom declarations
customDeclaration
    : CUSTOM templateType IDENTIFIER LBRACE customContent* RBRACE
    ;

customContent
    : templateContent
    | deleteStatement
    | insertStatement
    | specialization
    ;

// Specialization (for custom usage)
specialization
    : elementSpecialization
    | styleSpecialization
    | deleteStatement
    | insertStatement
    ;

elementSpecialization
    : IDENTIFIER (LBRACKET NUMBER RBRACKET)? LBRACE elementContent* RBRACE
    ;

styleSpecialization
    : cssProperty
    | IDENTIFIER (COLON | EQUALS) cssValue (EQUALS cssValue)? SEMICOLON  // Variable override
    ;

// Delete statement
deleteStatement
    : DELETE deleteTarget (COMMA deleteTarget)* SEMICOLON
    ;

deleteTarget
    : IDENTIFIER (LBRACKET NUMBER RBRACKET)?
    | atReference
    ;

// Insert statement
insertStatement
    : INSERT insertPosition IDENTIFIER (LBRACKET NUMBER RBRACKET)? LBRACE elementContent* RBRACE
    ;

insertPosition
    : AFTER
    | BEFORE
    | REPLACE
    | AT_TOP
    | AT_BOTTOM
    ;

// Origin declarations
originDeclaration
    : ORIGIN originType IDENTIFIER? LBRACE rawContent RBRACE
    ;

originType
    : AT_HTML
    | AT_STYLE
    | AT_JAVASCRIPT
    ;

rawContent
    : ~RBRACE*
    ;

// Import declarations
importDeclaration
    : IMPORT importTarget FROM stringLiteral (AS IDENTIFIER)? SEMICOLON
    ;

importTarget
    : AT_HTML
    | AT_STYLE
    | AT_JAVASCRIPT
    | AT_CHTL
    | (CUSTOM | TEMPLATE)? templateType IDENTIFIER
    ;

// Namespace declarations
namespaceDeclaration
    : NAMESPACE IDENTIFIER (LBRACE namespaceContent* RBRACE)?
    ;

namespaceContent
    : declaration
    | exceptStatement
    ;

// Configuration declarations
configurationDeclaration
    : CONFIGURATION LBRACE configContent* RBRACE
    ;

configContent
    : configProperty
    | nameBlock
    ;

configProperty
    : IDENTIFIER EQUALS configValue SEMICOLON
    ;

configValue
    : stringLiteral
    | IDENTIFIER
    | NUMBER
    | booleanLiteral
    ;

nameBlock
    : LBRACKET IDENTIFIER RBRACKET LBRACE nameProperty* RBRACE
    ;

nameProperty
    : IDENTIFIER EQUALS (configValue | configValueList) SEMICOLON
    ;

configValueList
    : LBRACKET configValue (COMMA configValue)* RBRACKET
    ;

// Common rules
atReference
    : templateType IDENTIFIER (FROM namespaceQualifier)?
    ;

namespaceQualifier
    : IDENTIFIER (DOT IDENTIFIER)*
    ;

inheritStatement
    : INHERIT atReference SEMICOLON
    | atReference SEMICOLON
    ;

exceptStatement
    : EXCEPT exceptTarget (COMMA exceptTarget)* SEMICOLON
    ;

exceptTarget
    : IDENTIFIER
    | atReference
    | templateType
    | CUSTOM
    | TEMPLATE
    ;

functionCall
    : IDENTIFIER LPAREN argumentList? RPAREN
    ;

argumentList
    : cssValue (COMMA cssValue)*
    ;

stringLiteral
    : DOUBLE_QUOTE_STRING
    | SINGLE_QUOTE_STRING
    | UNQUOTED_LITERAL
    | IDENTIFIER
    ;

booleanLiteral
    : 'true'
    | 'false'
    ;

// Info declaration (CMOD)
infoDeclaration
    : INFO LBRACE infoProperty* RBRACE
    ;

infoProperty
    : IDENTIFIER EQUALS stringLiteral SEMICOLON
    ;

// Export declaration (CMOD)
exportDeclaration
    : EXPORT LBRACE exportItem* RBRACE
    ;

exportItem
    : templateType exportNameList SEMICOLON
    ;

exportNameList
    : IDENTIFIER (COMMA IDENTIFIER)*
    ;