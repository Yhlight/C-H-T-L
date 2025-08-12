grammar JavaScript;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;

// 关键字
BREAK: 'break';
DO: 'do';
INSTANCEOF: 'instanceof';
TYPEOF: 'typeof';
CASE: 'case';
ELSE: 'else';
NEW: 'new';
VAR: 'var';
CATCH: 'catch';
FINALLY: 'finally';
RETURN: 'return';
VOID: 'void';
CONTINUE: 'continue';
FOR: 'for';
SWITCH: 'switch';
WHILE: 'while';
DEBUGGER: 'debugger';
FUNCTION: 'function';
THIS: 'this';
WITH: 'with';
DEFAULT: 'default';
IF: 'if';
THROW: 'throw';
DELETE: 'delete';
IN: 'in';
TRY: 'try';
CLASS: 'class';
ENUM: 'enum';
EXTENDS: 'extends';
SUPER: 'super';
CONST: 'const';
EXPORT: 'export';
IMPORT: 'import';
LET: 'let';
STATIC: 'static';
YIELD: 'yield';
IMPLEMENTS: 'implements';
INTERFACE: 'interface';
PACKAGE: 'package';
PRIVATE: 'private';
PROTECTED: 'protected';
PUBLIC: 'public';
ABSTRACT: 'abstract';
BOOLEAN: 'boolean';
BYTE: 'byte';
CHAR: 'char';
DOUBLE: 'double';
FINAL: 'final';
FLOAT: 'float';
GOTO: 'goto';
INT: 'int';
LONG: 'long';
NATIVE: 'native';
SHORT: 'short';
SYNCHRONIZED: 'synchronized';
THROWS: 'throws';
TRANSIENT: 'transient';
VOLATILE: 'volatile';
NULL: 'null';
TRUE: 'true';
FALSE: 'false';
ARROW: '=>';
ASYNC: 'async';
AWAIT: 'await';
GET: 'get';
SET: 'set';

// 字面量
LITERAL: NULL | TRUE | FALSE | STRING | NUMBER | REGEX;
STRING: '"' (~["\\] | '\\' .)* '"' | '\'' (~['\\] | '\\' .)* '\'';
NUMBER: DECIMAL_LITERAL | HEX_INTEGER_LITERAL | OCTAL_INTEGER_LITERAL | BINARY_INTEGER_LITERAL;
DECIMAL_LITERAL: [0-9]+ '.' [0-9]* EXPONENT_PART? | '.' [0-9]+ EXPONENT_PART? | [0-9]+ EXPONENT_PART?;
HEX_INTEGER_LITERAL: '0' [xX] [0-9a-fA-F]+;
OCTAL_INTEGER_LITERAL: '0' [0-7]+;
BINARY_INTEGER_LITERAL: '0' [bB] [01]+;
EXPONENT_PART: [eE] [+-]? [0-9]+;
REGEX: '/' REGEX_BODY '/' REGEX_FLAGS;
REGEX_BODY: (~[/\\] | '\\' .)*;
REGEX_FLAGS: [a-zA-Z]*;

// 标识符
IDENTIFIER: [a-zA-Z_$][a-zA-Z0-9_$]*;

// 标点符号
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
SEMICOLON: ';';
COLON: ':';
COMMA: ',';
DOT: '.';
ASSIGN: '=';
GT: '>';
LT: '<';
BANG: '!';
TILDE: '~';
QUESTION: '?';
INC: '++';
DEC: '--';
ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';
MOD: '%';
POWER: '**';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
MOD_ASSIGN: '%=';
POWER_ASSIGN: '**=';
LSHIFT: '<<';
RSHIFT: '>>';
URSHIFT: '>>>';
LSHIFT_ASSIGN: '<<=';
RSHIFT_ASSIGN: '>>=';
URSHIFT_ASSIGN: '>>>=';
BITAND: '&';
BITOR: '|';
CARET: '^';
AND_ASSIGN: '&=';
OR_ASSIGN: '|=';
XOR_ASSIGN: '^=';
ELLIPSIS: '...';

// 语法规则
program: sourceElement* EOF;

sourceElement: statement | functionDeclaration | classDeclaration;

statement: block | variableStatement | emptyStatement | expressionStatement | ifStatement | iterationStatement | continueStatement | breakStatement | returnStatement | yieldStatement | withStatement | labelledStatement | switchStatement | throwStatement | tryStatement | debuggerStatement | importStatement | exportStatement;

block: LBRACE statementList? RBRACE;
statementList: statement+;

variableStatement: (VAR | LET | CONST) variableDeclarationList SEMICOLON;
variableDeclarationList: variableDeclaration (COMMA variableDeclaration)*;
variableDeclaration: (identifier | bindingPattern) (ASSIGN initializer)?;
bindingPattern: objectBindingPattern | arrayBindingPattern;
objectBindingPattern: LBRACE (bindingProperty (COMMA bindingProperty)*)? RBRACE;
bindingProperty: (propertyName COLON)? bindingElement;
bindingElement: (identifier | bindingPattern) (ASSIGN initializer)?;
arrayBindingPattern: LBRACKET (bindingElement (COMMA bindingElement)*)? RBRACKET;
propertyName: identifierName | stringLiteral | numericLiteral;
identifierName: IDENTIFIER | reservedWord;
reservedWord: keyword | futureReservedWord | (TRUE | FALSE | NULL);
keyword: BREAK | DO | INSTANCEOF | TYPEOF | CASE | ELSE | NEW | VAR | CATCH | FINALLY | RETURN | VOID | CONTINUE | FOR | SWITCH | WHILE | DEBUGGER | FUNCTION | THIS | WITH | DEFAULT | IF | THROW | DELETE | IN | TRY;
futureReservedWord: CLASS | ENUM | EXTENDS | SUPER | CONST | EXPORT | IMPORT | LET | STATIC | YIELD | IMPLEMENTS | INTERFACE | PACKAGE | PRIVATE | PROTECTED | PUBLIC | ABSTRACT | BOOLEAN | BYTE | CHAR | DOUBLE | FINAL | FLOAT | GOTO | INT | LONG | NATIVE | SHORT | SYNCHRONIZED | THROWS | TRANSIENT | VOLATILE;
stringLiteral: STRING;
numericLiteral: NUMBER;
initializer: ASSIGN assignmentExpression;

emptyStatement: SEMICOLON;

expressionStatement: expression SEMICOLON;

ifStatement: IF LPAREN expression RPAREN statement (ELSE statement)?;

iterationStatement: DO statement WHILE LPAREN expression RPAREN SEMICOLON | WHILE LPAREN expression RPAREN statement | FOR LPAREN (expressionNoIn | variableDeclarationList)? SEMICOLON expression? SEMICOLON expression? RPAREN statement | FOR LPAREN (identifier | bindingPattern) IN expression RPAREN statement | FOR LPAREN identifier OF assignmentExpression RPAREN statement | FOR LPAREN identifier OF assignmentExpression RPAREN statement;

continueStatement: CONTINUE (identifier)? SEMICOLON;
breakStatement: BREAK (identifier)? SEMICOLON;
returnStatement: RETURN expression? SEMICOLON;
yieldStatement: YIELD expression? SEMICOLON;

withStatement: WITH LPAREN expression RPAREN statement;

labelledStatement: identifier COLON statement;

switchStatement: SWITCH LPAREN expression RPAREN caseBlock;
caseBlock: LBRACE caseClauses? (defaultClause caseClauses?)? RBRACE;
caseClauses: caseClause+;
caseClause: CASE expression COLON statementList?;
defaultClause: DEFAULT COLON statementList?;

throwStatement: THROW expression SEMICOLON;

tryStatement: TRY block catchBlock? finallyBlock? | TRY block catchBlock finallyBlock;
catchBlock: CATCH LPAREN (identifier | bindingPattern) RPAREN block;
finallyBlock: FINALLY block;

debuggerStatement: DEBUGGER SEMICOLON;

functionDeclaration: FUNCTION identifier LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE;
formalParameterList: formalParameterArg (COMMA formalParameterArg)*;
formalParameterArg: identifier | bindingPattern | ELLIPSIS (identifier | bindingPattern);
functionBody: sourceElements?;

classDeclaration: CLASS identifier (EXTENDS identifier)? LBRACE classBody? RBRACE;
classBody: classElement+;
classElement: methodDefinition;
methodDefinition: (GET | SET)? propertyName LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE;
propertyName: identifierName;

importStatement: IMPORT importClause fromClause SEMICOLON | IMPORT moduleSpecifier SEMICOLON;
importClause: defaultImport | nameSpaceImport | namedImports | defaultImport COMMA nameSpaceImport | defaultImport COMMA namedImports;
defaultImport: identifier;
nameSpaceImport: ASTERISK AS identifier;
namedImports: LBRACE (importSpecifier (COMMA importSpecifier)*)? RBRACE;
importSpecifier: identifier | identifierName AS identifier;
fromClause: FROM moduleSpecifier;
moduleSpecifier: stringLiteral;

exportStatement: EXPORT exportClause (fromClause)? SEMICOLON | EXPORT defaultExport (COMMA exportClause)? (fromClause)? SEMICOLON;
exportClause: ASTERISK | nameSpaceImport | namedExports;
namedExports: LBRACE (exportSpecifier (COMMA exportSpecifier)*)? RBRACE;
exportSpecifier: identifier | identifierName AS identifier;
defaultExport: identifier | functionDeclaration | classDeclaration;

expression: assignmentExpression (COMMA assignmentExpression)*;
assignmentExpression: conditionalExpression | yieldExpression | arrowFunction | assignmentOperator assignmentExpression;
assignmentOperator: ASSIGN | MUL_ASSIGN | DIV_ASSIGN | MOD_ASSIGN | ADD_ASSIGN | SUB_ASSIGN | LSHIFT_ASSIGN | RSHIFT_ASSIGN | URSHIFT_ASSIGN | AND_ASSIGN | XOR_ASSIGN | OR_ASSIGN | POWER_ASSIGN;
conditionalExpression: logicalORExpression (QUESTION assignmentExpression COLON assignmentExpression)?;
logicalORExpression: logicalANDExpression (OR logicalANDExpression)*;
logicalANDExpression: bitwiseORExpression (AND bitwiseORExpression)*;
bitwiseORExpression: bitwiseXORExpression (BITOR bitwiseXORExpression)*;
bitwiseXORExpression: bitwiseANDExpression (CARET bitwiseANDExpression)*;
bitwiseANDExpression: equalityExpression (BITAND equalityExpression)*;
equalityExpression: relationalExpression ((EQUAL | NOTEQUAL) relationalExpression)*;
relationalExpression: shiftExpression ((LT | GT | LE | GE | INSTANCEOF | IN) shiftExpression)*;
shiftExpression: additiveExpression ((LSHIFT | RSHIFT | URSHIFT) additiveExpression)*;
additiveExpression: multiplicativeExpression ((ADD | SUB) additiveExpression)*;
multiplicativeExpression: unaryExpression ((MUL | DIV | MOD) unaryExpression)*;
unaryExpression: unaryOperator unaryExpression | postfixExpression;
unaryOperator: DELETE | VOID | TYPEOF | INC | DEC | ADD | SUB | BANG | TILDE;
postfixExpression: leftHandSideExpression (INC | DEC)?;
leftHandSideExpression: callExpression | newExpression;

callExpression: callExpression LPAREN arguments? RPAREN | callExpression LBRACKET expression RBRACKET | callExpression DOT identifierName | callExpression templateLiteral | superProperty | functionExpression | classExpression | identifier | thisExpression | arrayLiteral | objectLiteral | parenthesizedExpression | newExpression;
arguments: argumentList;
argumentList: assignmentExpression (COMMA assignmentExpression)*;

newExpression: NEW newExpression | NEW newExpression LPAREN arguments? RPAREN | NEW newExpression LBRACKET expression RBRACKET | NEW newExpression DOT identifierName | NEW newExpression templateLiteral | superProperty | functionExpression | classExpression | identifier | thisExpression | arrayLiteral | objectLiteral | parenthesizedExpression;

superProperty: SUPER LBRACKET expression RBRACKET | SUPER DOT identifierName;
functionExpression: FUNCTION identifier? LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE;
classExpression: CLASS identifier? (EXTENDS identifier)? LBRACE classBody? RBRACE;
identifier: IDENTIFIER;
thisExpression: THIS;
arrayLiteral: LBRACKET (elementList COMMA?)? RBRACKET;
elementList: (ELLIPSIS)? assignmentExpression (COMMA (ELLIPSIS)? assignmentExpression)*;
objectLiteral: LBRACE (propertyDefinition (COMMA propertyDefinition)*)? RBRACE;
propertyDefinition: identifierName COLON assignmentExpression | (GET | SET)? propertyName LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE | (ELLIPSIS)? assignmentExpression;
parenthesizedExpression: LPAREN expression RPAREN;
templateLiteral: BACKTICK templateElement* BACKTICK;
templateElement: templateCharacters | templateSubstitution;
templateCharacters: TEMPLATE_CHAR*;
TEMPLATE_CHAR: ~[`$\\] | '\\' .;
templateSubstitution: '$' LBRACE expression RBRACE;
yieldExpression: YIELD (assignmentExpression)?;
arrowFunction: arrowParameters ARROW arrowFunctionBody;
arrowParameters: identifier | LPAREN formalParameterList? RPAREN | bindingPattern;
arrowFunctionBody: assignmentExpression | LBRACE functionBody RBRACE;

expressionNoIn: assignmentExpressionNoIn (COMMA assignmentExpressionNoIn)*;
assignmentExpressionNoIn: conditionalExpressionNoIn | yieldExpression | arrowFunction | assignmentOperator assignmentExpressionNoIn;
conditionalExpressionNoIn: logicalORExpressionNoIn (QUESTION assignmentExpression COLON assignmentExpressionNoIn)?;
logicalORExpressionNoIn: logicalANDExpressionNoIn (OR logicalANDExpressionNoIn)*;
logicalANDExpressionNoIn: bitwiseORExpressionNoIn (AND bitwiseORExpressionNoIn)*;
bitwiseORExpressionNoIn: bitwiseXORExpressionNoIn (BITOR bitwiseXORExpressionNoIn)*;
bitwiseXORExpressionNoIn: bitwiseANDExpressionNoIn (CARET bitwiseANDExpressionNoIn)*;
bitwiseANDExpressionNoIn: equalityExpressionNoIn (BITAND equalityExpressionNoIn)*;
equalityExpressionNoIn: relationalExpressionNoIn ((EQUAL | NOTEQUAL) relationalExpressionNoIn)*;
relationalExpressionNoIn: shiftExpressionNoIn ((LT | GT | LE | GE | INSTANCEOF) shiftExpressionNoIn)*;
shiftExpressionNoIn: additiveExpressionNoIn ((LSHIFT | RSHIFT | URSHIFT) additiveExpressionNoIn)*;
additiveExpressionNoIn: multiplicativeExpressionNoIn ((ADD | SUB) multiplicativeExpressionNoIn)*;
multiplicativeExpressionNoIn: unaryExpressionNoIn ((MUL | DIV | MOD) unaryExpressionNoIn)*;
unaryExpressionNoIn: unaryOperator unaryExpressionNoIn | postfixExpression;

// 辅助规则
ASTERISK: '*';
AS: 'as';
BACKTICK: '`';
OR: '||';
AND: '&&';
EQUAL: '==';
NOTEQUAL: '!=';
LE: '<=';
GE: '>=';
sourceElements: sourceElement+;