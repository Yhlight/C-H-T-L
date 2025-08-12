grammar CHTLJS;

// 继承JavaScript语法
import JavaScript;

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

// 语法规则
chtlScriptBlock: CHTL_SCRIPT LBRACE chtlScriptContent RBRACE;
chtlScriptContent: (chtlStatement | statement)*;

chtlStatement: chtlSelectorStatement | chtlListenStatement | chtlDelegateStatement | chtlAnimateStatement;

// CHTL选择器语句
chtlSelectorStatement: chtlSelector (DOT | CHTL_ARROW) methodCall;
chtlSelector: CHTL_DOUBLE_BRACE selectorContent CHTL_DOUBLE_BRACE_CLOSE;
selectorContent: (selectorType)? identifier (selectorModifier)*;
selectorType: DOT | HASH;
selectorModifier: LBRACKET NUMBER RBRACKET | (WS selectorContent)*;

// CHTL监听器语句
chtlListenStatement: chtlSelector DOT CHTL_LISTEN LPAREN chtlListenObject RPAREN;
chtlListenObject: LBRACE chtlListenEvents RBRACE;
chtlListenEvents: chtlListenEvent (COMMA chtlListenEvent)*;
chtlListenEvent: eventType COLON eventHandler;
eventType: identifier;
eventHandler: identifier | functionExpression | arrowFunction;

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
easingValue: identifier | STRING;
chtlBegin: CHTL_BEGIN COLON LBRACE chtlCssProperties RBRACE;
chtlWhen: CHTL_WHEN COLON LBRACKET chtlWhenClause (COMMA chtlWhenClause)* RBRACKET;
chtlWhenClause: LBRACE chtlAt COMMA chtlCssProperties RBRACE;
chtlAt: CHTL_AT COLON NUMBER;
chtlEnd: CHTL_END COLON LBRACE chtlCssProperties RBRACE;
chtlLoop: CHTL_LOOP COLON (NUMBER | MINUS);
chtlDirection: CHTL_DIRECTION COLON directionValue;
directionValue: identifier | STRING;
chtlDelay: CHTL_DELAY COLON NUMBER;
chtlCallback: CHTL_CALLBACK COLON identifier;

chtlCssProperties: chtlCssProperty*;
chtlCssProperty: propertyName COLON propertyValue SEMICOLON;
propertyName: identifier;
propertyValue: (STRING | LITERAL | identifier | functionCall)*;

// 方法调用
methodCall: identifier LPAREN arguments? RPAREN | methodCall DOT identifier LPAREN arguments? RPAREN | methodCall LBRACKET expression RBRACKET | methodCall DOT identifier;

// 函数调用
functionCall: identifier LPAREN (functionArg (COMMA functionArg)*)? RPAREN;
functionArg: (identifier (ASSIGN value)?) | value;
value: STRING | NUMBER | identifier;

// 辅助规则
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
ASSIGN: '=';
WS: [ \t\r\n]+ -> skip;