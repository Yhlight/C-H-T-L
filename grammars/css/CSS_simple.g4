grammar CSS_simple;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '/*' .*? '*/' -> skip;

// 选择器
SELECTOR: '#' | '.' | '*' | '>' | '+' | '~';

// 标识符和字面量
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_-]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"';

// 标点符号
LBRACE: '{';
RBRACE: '}';
LPAREN: '(';
RPAREN: ')';
SEMICOLON: ';';
COLON: ':';
COMMA: ',';
DOT: '.';
HASH: '#';

// 语法规则
stylesheet: rule*;

rule: selector LBRACE declarationList RBRACE;
selector: (DOT | HASH)? IDENTIFIER;
declarationList: declaration*;
declaration: property COLON value SEMICOLON;
property: IDENTIFIER;
value: (STRING | NUMBER | IDENTIFIER)*;