grammar CHTL_simple;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;

// 关键字
TEMPLATE: '[Template]';
CUSTOM: '[Custom]';
ORIGIN: '[Origin]';
TEXT: 'text';
STYLE: 'style';
SCRIPT: 'script';

// 标点符号
LBRACE: '{';
RBRACE: '}';
SEMICOLON: ';';
COLON: ':';
EQUALS: '=';
DOT: '.';

// 标识符和字面量
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"';

// 语法规则
program: statement*;

statement: elementStatement | templateStatement | customStatement | originStatement;

elementStatement: IDENTIFIER (attributes)? (LBRACE elementContent RBRACE)?;
attributes: attribute*;
attribute: IDENTIFIER (COLON | EQUALS) (STRING | IDENTIFIER) SEMICOLON;
elementContent: (elementStatement | textBlock | styleBlock | scriptBlock)*;

textBlock: TEXT LBRACE (STRING | IDENTIFIER)* RBRACE;
styleBlock: STYLE LBRACE (STRING | IDENTIFIER)* RBRACE;
scriptBlock: SCRIPT LBRACE (STRING | IDENTIFIER)* RBRACE;

templateStatement: TEMPLATE IDENTIFIER LBRACE elementContent RBRACE;
customStatement: CUSTOM IDENTIFIER LBRACE elementContent RBRACE;
originStatement: ORIGIN IDENTIFIER LBRACE elementContent RBRACE;