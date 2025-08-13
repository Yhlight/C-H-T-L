grammar CHTLJS;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;

// CHTL JS特有的关键字
CHTL_SCRIPT: 'script';
CHTL_LISTEN: 'listen';
CHTL_DELEGATE: 'delegate';
CHTL_ANIMATE: 'animate';
CHTL_AT: 'at';
CHTL_WHEN: 'when';
CHTL_BEGIN: 'begin';
CHTL_END: 'end';
CHTL_LOOP: 'loop';
CHTL_DIRECTION: 'direction';
CHTL_DELAY: 'delay';
CHTL_CALLBACK: 'callback';
CHTL_TARGET: 'target';
CHTL_EASING: 'easing';
CHTL_DURATION: 'duration';

// JavaScript基础关键字
FUNCTION: 'function';
VAR: 'var';
LET: 'let';
CONST: 'const';
IF: 'if';
ELSE: 'else';
FOR: 'for';
WHILE: 'while';
DO: 'do';
SWITCH: 'switch';
CASE: 'case';
DEFAULT: 'default';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';
TRY: 'try';
CATCH: 'catch';
FINALLY: 'finally';
THROW: 'throw';
NEW: 'new';
THIS: 'this';
SUPER: 'super';
CLASS: 'class';
EXTENDS: 'extends';
STATIC: 'static';
ASYNC: 'async';
AWAIT: 'await';
YIELD: 'yield';
GET: 'get';
SET: 'set';
IMPORT: 'import';
EXPORT: 'export';
FROM: 'from';
AS: 'as';
OF: 'of';
IN: 'in';
INSTANCEOF: 'instanceof';
TYPEOF: 'typeof';
DELETE: 'delete';
VOID: 'void';
WITH: 'with';
DEBUGGER: 'debugger';

// 字面量
NULL: 'null';
TRUE: 'true';
FALSE: 'false';
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"';
REGEX: '/' REGEX_BODY '/' REGEX_FLAGS;
REGEX_BODY: (~[/\\] | '\\' .)*;
REGEX_FLAGS: [a-zA-Z]*;

// 标识符
IDENTIFIER: [a-zA-Z_$][a-zA-Z0-9_$]*;

// 标点符号
LBRACE: '{';
RBRACE: '}';
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';
SEMICOLON: ';';
COLON: ':';
EQUALS: '=';
ASSIGN: '=';
MINUS: '-';
PLUS: '+';
MUL: '*';
DIV: '/';
MOD: '%';
POWER: '**';
GT: '>';
LT: '<';
GE: '>=';
LE: '<=';
EQUAL: '==';
NOTEQUAL: '!=';
AND: '&&';
OR: '||';
BANG: '!';
TILDE: '~';
QUESTION: '?';
INC: '++';
DEC: '--';
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
ARROW: '=>';

// CHTL JS特有的标点符号
CHTL_DOUBLE_BRACE: '{{';
CHTL_DOUBLE_BRACE_CLOSE: '}}';
CHTL_ARROW: '->';

// 语法规则
program: sourceElement* EOF;

sourceElement: statement | functionDeclaration | classDeclaration | chtlStatement;

// 基本语句
statement: block | variableStatement | emptyStatement | expressionStatement | ifStatement | iterationStatement | continueStatement | breakStatement | returnStatement | withStatement | labelledStatement | switchStatement | throwStatement | tryStatement | debuggerStatement;

block: LBRACE statementList? RBRACE;
statementList: statement+;

variableStatement: (VAR | LET | CONST) variableDeclarationList SEMICOLON;
variableDeclarationList: variableDeclaration (COMMA variableDeclaration)*;
variableDeclaration: IDENTIFIER (ASSIGN assignmentExpression)?;
assignmentExpression: conditionalExpression | assignmentOperator assignmentExpression;
assignmentOperator: ASSIGN | ADD_ASSIGN | SUB_ASSIGN | MUL_ASSIGN | DIV_ASSIGN | MOD_ASSIGN | POWER_ASSIGN | LSHIFT_ASSIGN | RSHIFT_ASSIGN | URSHIFT_ASSIGN | AND_ASSIGN | OR_ASSIGN | XOR_ASSIGN;

emptyStatement: SEMICOLON;
expressionStatement: expression SEMICOLON;

ifStatement: IF LPAREN expression RPAREN statement (ELSE statement)?;
iterationStatement: DO statement WHILE LPAREN expression RPAREN SEMICOLON | WHILE LPAREN expression RPAREN statement | FOR LPAREN (expression | variableStatement)? SEMICOLON expression? SEMICOLON expression? RPAREN statement;

continueStatement: CONTINUE (IDENTIFIER)? SEMICOLON;
breakStatement: BREAK (IDENTIFIER)? SEMICOLON;
returnStatement: RETURN expression? SEMICOLON;

withStatement: WITH LPAREN expression RPAREN statement;
labelledStatement: IDENTIFIER COLON statement;
switchStatement: SWITCH LPAREN expression RPAREN caseBlock;
caseBlock: LBRACE caseClauses? (defaultClause caseClauses?)? RBRACE;
caseClauses: caseClause+;
caseClause: CASE expression COLON statementList?;
defaultClause: DEFAULT COLON statementList?;

throwStatement: THROW expression SEMICOLON;
tryStatement: TRY block catchBlock? finallyBlock? | TRY block catchBlock finallyBlock;
catchBlock: CATCH LPAREN IDENTIFIER RPAREN block;
finallyBlock: FINALLY block;

debuggerStatement: DEBUGGER SEMICOLON;

// 函数声明
functionDeclaration: FUNCTION IDENTIFIER LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE;
formalParameterList: IDENTIFIER (COMMA IDENTIFIER)*;
functionBody: sourceElements?;

// 类声明
classDeclaration: CLASS IDENTIFIER (EXTENDS IDENTIFIER)? LBRACE classBody? RBRACE;
classBody: classElement+;
classElement: methodDefinition;
methodDefinition: (GET | SET)? IDENTIFIER LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE;

// 表达式
expression: assignmentExpression (COMMA assignmentExpression)*;
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

callExpression: callExpression LPAREN arguments? RPAREN | callExpression LBRACKET expression RBRACKET | callExpression DOT IDENTIFIER | superProperty | functionExpression | classExpression | IDENTIFIER | thisExpression | arrayLiteral | objectLiteral | parenthesizedExpression | newExpression;
arguments: argumentList;
argumentList: assignmentExpression (COMMA assignmentExpression)*;

newExpression: NEW newExpression | NEW newExpression LPAREN arguments? RPAREN | NEW newExpression LBRACKET expression RBRACKET | NEW newExpression DOT IDENTIFIER | superProperty | functionExpression | classExpression | IDENTIFIER | thisExpression | arrayLiteral | objectLiteral | parenthesizedExpression;

superProperty: SUPER LBRACKET expression RBRACKET | SUPER DOT IDENTIFIER;
functionExpression: FUNCTION IDENTIFIER? LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE;
classExpression: CLASS IDENTIFIER? (EXTENDS IDENTIFIER)? LBRACE classBody? RBRACE;
thisExpression: THIS;
arrayLiteral: LBRACKET (elementList COMMA?)? RBRACKET;
elementList: (ELLIPSIS)? assignmentExpression (COMMA (ELLIPSIS)? assignmentExpression)*;
objectLiteral: LBRACE (propertyDefinition (COMMA propertyDefinition)*)? RBRACE;
propertyDefinition: IDENTIFIER COLON assignmentExpression | (GET | SET)? IDENTIFIER LPAREN formalParameterList? RPAREN LBRACE functionBody RBRACE | (ELLIPSIS)? assignmentExpression;
parenthesizedExpression: LPAREN expression RPAREN;

// 箭头函数
arrowFunction: arrowParameters ARROW arrowFunctionBody;
arrowParameters: IDENTIFIER | LPAREN formalParameterList? RPAREN;
arrowFunctionBody: assignmentExpression | LBRACE functionBody RBRACE;

// CHTL JS特有语句
chtlStatement: chtlSelectorStatement | chtlListenStatement | chtlDelegateStatement | chtlAnimateStatement;

// CHTL选择器语句
chtlSelectorStatement: chtlSelector (DOT | CHTL_ARROW) methodCall;
chtlSelector: CHTL_DOUBLE_BRACE selectorContent CHTL_DOUBLE_BRACE_CLOSE;
selectorContent: (selectorType)? IDENTIFIER (selectorModifier)+;
selectorType: DOT | HASH;
selectorModifier: LBRACKET NUMBER RBRACKET | (WS selectorContent)+;

// CHTL监听器语句
chtlListenStatement: chtlSelector DOT CHTL_LISTEN LPAREN chtlListenObject RPAREN;
chtlListenObject: LBRACE chtlListenEvents RBRACE;
chtlListenEvents: chtlListenEvent (COMMA chtlListenEvent)*;
chtlListenEvent: eventType COLON eventHandler;
eventType: IDENTIFIER;
eventHandler: IDENTIFIER | functionExpression | arrowFunction;

// CHTL事件委托语句
chtlDelegateStatement: chtlSelector DOT CHTL_DELEGATE LPAREN chtlDelegateObject RPAREN;
chtlDelegateObject: LBRACE chtlDelegateConfig RBRACE;
chtlDelegateConfig: chtlTargetConfig COMMA chtlEventConfig;
chtlTargetConfig: CHTL_TARGET COLON (chtlSelector | chtlSelectorArray);
chtlSelectorArray: LBRACKET chtlSelector (COMMA chtlSelector)* RBRACKET;
chtlEventConfig: chtlListenEvents;

// CHTL动画语句
chtlAnimateStatement: CHTL_ANIMATE LPAREN chtlAnimateObject RPAREN;
chtlAnimateObject: LBRACE chtlAnimateConfig RBRACE;
chtlAnimateConfig: chtlAnimateProperty (COMMA chtlAnimateProperty)*;
chtlAnimateProperty: chtlDuration | chtlEasing | chtlBegin | chtlWhen | chtlEnd | chtlLoop | chtlDirection | chtlDelay | chtlCallback;

chtlDuration: CHTL_DURATION COLON NUMBER;
chtlEasing: CHTL_EASING COLON easingValue;
easingValue: IDENTIFIER | STRING;
chtlBegin: CHTL_BEGIN COLON LBRACE chtlCssProperties RBRACE;
chtlWhen: CHTL_WHEN COLON LBRACKET chtlWhenClause (COMMA chtlWhenClause)* RBRACKET;
chtlWhenClause: LBRACE chtlAt COMMA chtlCssProperties RBRACE;
chtlAt: CHTL_AT COLON NUMBER;
chtlEnd: CHTL_END COLON LBRACE chtlCssProperties RBRACE;
chtlLoop: CHTL_LOOP COLON (NUMBER | MINUS);
chtlDirection: CHTL_DIRECTION COLON directionValue;
directionValue: IDENTIFIER | STRING;
chtlDelay: CHTL_DELAY COLON NUMBER;
chtlCallback: CHTL_CALLBACK COLON IDENTIFIER;

chtlCssProperties: chtlCssProperty*;
chtlCssProperty: propertyName COLON propertyValue SEMICOLON;
propertyName: IDENTIFIER;
propertyValue: (STRING | LITERAL | IDENTIFIER | functionCall)*;

// 方法调用
methodCall: IDENTIFIER LPAREN arguments? RPAREN | methodCall DOT IDENTIFIER LPAREN arguments? RPAREN | methodCall LBRACKET expression RBRACKET | methodCall DOT IDENTIFIER;

// 函数调用
functionCall: IDENTIFIER LPAREN (functionArg (COMMA functionArg)*)? RPAREN;
functionArg: (IDENTIFIER (ASSIGN value)?) | value;
value: STRING | NUMBER | IDENTIFIER;

// 辅助规则
LITERAL: [a-zA-Z0-9_]+;
HASH: '#';
DOT: '.';
COMMA: ',';
sourceElements: sourceElement+;