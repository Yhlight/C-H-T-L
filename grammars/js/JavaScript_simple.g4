grammar JavaScript_simple;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;

// 关键字
FUNCTION: 'function';
VAR: 'var';
LET: 'let';
CONST: 'const';
IF: 'if';
ELSE: 'else';
FOR: 'for';
WHILE: 'while';
RETURN: 'return';

// 标识符和字面量
IDENTIFIER: [a-zA-Z_$][a-zA-Z0-9_$]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"';

// 标点符号
LBRACE: '{';
RBRACE: '}';
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';
SEMICOLON: ';';
COMMA: ',';
DOT: '.';
EQUALS: '=';
PLUS: '+';
MINUS: '-';
MULTIPLY: '*';
DIVIDE: '/';

// 语法规则
program: statement*;

statement: expressionStatement | variableDeclaration | functionDeclaration | ifStatement | forStatement | whileStatement | returnStatement | blockStatement;

expressionStatement: expression SEMICOLON;
expression: assignmentExpression | functionCall | identifier | literal;
assignmentExpression: IDENTIFIER EQUALS expression;
functionCall: IDENTIFIER LPAREN argumentList? RPAREN;
argumentList: expression (COMMA expression)*;
identifier: IDENTIFIER;
literal: STRING | NUMBER;

variableDeclaration: (VAR | LET | CONST) IDENTIFIER (EQUALS expression)? SEMICOLON;

functionDeclaration: FUNCTION IDENTIFIER LPAREN parameterList? RPAREN blockStatement;
parameterList: IDENTIFIER (COMMA IDENTIFIER)*;

ifStatement: IF LPAREN expression RPAREN statement (ELSE statement)?;

forStatement: FOR LPAREN forInitializer? SEMICOLON expression? SEMICOLON expression? RPAREN statement;
forInitializer: variableDeclaration | expressionStatement;

whileStatement: WHILE LPAREN expression RPAREN statement;

returnStatement: RETURN expression? SEMICOLON;

blockStatement: LBRACE statement* RBRACE;