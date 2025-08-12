grammar CHTLJS;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;

// CHTL JS特有的词法规则
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

// CHTL JS特有的标点符号
CHTL_DOUBLE_BRACE: '{{';
CHTL_DOUBLE_BRACE_CLOSE: '}}';
CHTL_ARROW: '->';

// 基本词法规则
IDENTIFIER: [a-zA-Z_$] [a-zA-Z0-9_$]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"' | '\'' (~['\\] | '\\' .)* '\'';
LITERAL: ~[ \t\r\n{}[]();:="'\n\r]+;

// 标点符号
LBRACE: '{';
RBRACE: '}';
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';
SEMICOLON: ';';
COLON: ':';
COMMA: ',';
DOT: '.';
HASH: '#';
EQUALS: '=';
MINUS: '-';

// 语法规则
chtlScriptBlock: CHTL_SCRIPT LBRACE chtlScriptContent RBRACE;
chtlScriptContent: (chtlStatement | basicStatement)*;

chtlStatement: chtlSelectorStatement | chtlListenStatement | chtlDelegateStatement | chtlAnimateStatement;

// CHTL选择器语句
chtlSelectorStatement: chtlSelector (DOT | CHTL_ARROW) methodCall;
chtlSelector: CHTL_DOUBLE_BRACE selectorContent CHTL_DOUBLE_BRACE_CLOSE;
selectorContent: (selectorType)? IDENTIFIER (selectorModifier)*;
selectorType: DOT | HASH;
selectorModifier: LBRACKET NUMBER RBRACKET | (WS selectorContent)*;

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
functionArg: (IDENTIFIER (EQUALS value)?) | value;
value: STRING | NUMBER | IDENTIFIER;

// 基本语句（简化版）
basicStatement: IDENTIFIER | STRING | NUMBER | LITERAL;
expression: IDENTIFIER | STRING | NUMBER | LITERAL;
arguments: argumentList;
argumentList: expression (COMMA expression)*;
functionExpression: IDENTIFIER | STRING;
arrowFunction: IDENTIFIER | STRING;