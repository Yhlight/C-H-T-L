grammar CHTLJS_simple;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;

// CHTL JS特有的词法规则
CHTL_SCRIPT: 'script';
CHTL_LISTEN: 'listen';
CHTL_DELEGATE: 'delegate';
CHTL_ANIMATE: 'animate';

// CHTL JS特有的标点符号
CHTL_DOUBLE_BRACE: '{{';
CHTL_DOUBLE_BRACE_CLOSE: '}}';
CHTL_ARROW: '->';

// 基本词法规则
IDENTIFIER: [a-zA-Z_$][a-zA-Z0-9_$]*;
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
chtlScriptBlock: CHTL_SCRIPT LBRACE chtlScriptContent RBRACE;
chtlScriptContent: (chtlStatement | basicStatement)*;

chtlStatement: chtlSelectorStatement | chtlListenStatement | chtlDelegateStatement | chtlAnimateStatement;

// CHTL选择器语句
chtlSelectorStatement: chtlSelector DOT methodCall;
chtlSelector: CHTL_DOUBLE_BRACE selectorContent CHTL_DOUBLE_BRACE_CLOSE;
selectorContent: (DOT | HASH)? IDENTIFIER;

// CHTL监听器语句
chtlListenStatement: chtlSelector DOT CHTL_LISTEN LPAREN chtlListenObject RPAREN;
chtlListenObject: LBRACE chtlListenEvents RBRACE;
chtlListenEvents: chtlListenEvent (COMMA chtlListenEvent)*;
chtlListenEvent: eventType COLON eventHandler;
eventType: IDENTIFIER;
eventHandler: IDENTIFIER | STRING;

// CHTL事件委托语句
chtlDelegateStatement: chtlSelector DOT CHTL_DELEGATE LPAREN chtlDelegateObject RPAREN;
chtlDelegateObject: LBRACE chtlDelegateConfig RBRACE;
chtlDelegateConfig: chtlTargetConfig COMMA chtlEventConfig;
chtlTargetConfig: IDENTIFIER COLON chtlSelector;
chtlEventConfig: chtlListenEvents;

// CHTL动画语句
chtlAnimateStatement: CHTL_ANIMATE LPAREN chtlAnimateObject RPAREN;
chtlAnimateObject: LBRACE chtlAnimateConfig RBRACE;
chtlAnimateConfig: chtlAnimateProperty (COMMA chtlAnimateProperty)*;
chtlAnimateProperty: chtlDuration | chtlEasing | chtlBegin | chtlEnd;

chtlDuration: IDENTIFIER COLON NUMBER;
chtlEasing: IDENTIFIER COLON easingValue;
easingValue: IDENTIFIER | STRING;
chtlBegin: IDENTIFIER COLON LBRACE chtlCssProperties RBRACE;
chtlEnd: IDENTIFIER COLON LBRACE chtlCssProperties RBRACE;

chtlCssProperties: chtlCssProperty*;
chtlCssProperty: propertyName COLON propertyValue SEMICOLON;
propertyName: IDENTIFIER;
propertyValue: (STRING | NUMBER | IDENTIFIER)*;

// 方法调用
methodCall: IDENTIFIER LPAREN arguments? RPAREN;
arguments: argumentList;
argumentList: (STRING | NUMBER | IDENTIFIER) (COMMA (STRING | NUMBER | IDENTIFIER))*;

// 基本语句
basicStatement: IDENTIFIER | STRING | NUMBER;