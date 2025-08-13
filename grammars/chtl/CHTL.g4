grammar CHTL;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;
GENERATOR_COMMENT: '[Generator]' ~[\r\n]* -> skip;

// 关键字
TEMPLATE: '[Template]';
CUSTOM: '[Custom]';
ORIGIN: '[Origin]';
CONFIGURATION: '[Configuration]';
IMPORT: '[Import]';
NAMESPACE: '[Namespace]';
INFO: '[Info]';
EXPORT: '[Export]';
STYLE: '[Style]';
ELEMENT: '[Element]';
VAR: '[Var]';
HTML: '[HTML]';
CSS: '[CSS]';
JAVASCRIPT: '[JavaScript]';
CHTL: '[CHTL]';
INHERIT: '[Inherit]';
DELETE: '[Delete]';
INSERT: '[Insert]';
AFTER: '[After]';
BEFORE: '[Before]';
REPLACE: '[Replace]';
AT_TOP: '[AtTop]';
AT_BOTTOM: '[AtBottom]';
FROM: '[From]';
AS: '[As]';
EXCEPT: '[Except]';
TEXT: '[Text]';
STYLE_BLOCK: '[StyleBlock]';
SCRIPT: '[Script]';

// 标点符号
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
LPAREN: '(';
RPAREN: ')';
SEMICOLON: ';';
COLON: ':';
EQUALS: '=';
COMMA: ',';
DOT: '.';
HASH: '#';
PERIOD: '.';

// 标识符
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"';
LITERAL: [a-zA-Z0-9_]+;

// 语法规则
program: (importStatement | namespaceStatement | configurationStatement | templateStatement | customStatement | originStatement | elementStatement)*;

// 导入语句
importStatement: IMPORT STRING SEMICOLON;

// 命名空间语句
namespaceStatement: NAMESPACE IDENTIFIER EQUALS STRING SEMICOLON;

// 配置语句
configurationStatement: CONFIGURATION LBRACE configurationContent RBRACE;
configurationContent: (keyValuePair)*;
keyValuePair: IDENTIFIER EQUALS (STRING | NUMBER) SEMICOLON;

// 模板语句
templateStatement: TEMPLATE IDENTIFIER LBRACE templateContent RBRACE;
templateContent: (elementStatement | styleBlock | scriptBlock | rawContent)+;

// 自定义语句
customStatement: CUSTOM IDENTIFIER LBRACE customContent RBRACE;
customContent: (elementStatement | styleBlock | scriptBlock | rawContent)+;

// 原始语句
originStatement: ORIGIN originType (IDENTIFIER)? LBRACE originContent RBRACE;
originType: HTML | CSS | JAVASCRIPT;
originContent: (elementStatement | styleBlock | scriptBlock | rawContent)+;
rawContent: (STRING | LITERAL | IDENTIFIER | NUMBER)+;

// 元素语句 - 支持HTML元素、text文本块、style样式块、script脚本块
elementStatement: elementName (attributes)? (LBRACE elementContent RBRACE)?;
elementName: IDENTIFIER;
attributes: LBRACKET attributeList RBRACKET;
attributeList: attribute (COMMA attribute)*;
attribute: IDENTIFIER EQUALS (STRING | NUMBER | IDENTIFIER);
elementContent: (elementStatement | textBlock | styleBlock | scriptBlock | rawContent)+;

// text文本块
textBlock: TEXT LBRACE textContent RBRACE;
textContent: (STRING | LITERAL | IDENTIFIER)+;

// style样式块
styleBlock: STYLE LBRACE styleContent RBRACE;
styleContent: (cssRule | rawContent)+;

// script脚本块
scriptBlock: SCRIPT LBRACE scriptContent RBRACE;
scriptContent: (elementStatement | STRING | LITERAL | IDENTIFIER | functionCall | rawContent)+;

// CSS规则 - 支持选择器和上下文推导
cssRule: selector LBRACE cssProperties RBRACE;
selector: (IDENTIFIER | HASH | DOT IDENTIFIER | selectorWithContext)*;
selectorWithContext: LBRACKET contextSelector RBRACKET;
contextSelector: IDENTIFIER (COMMA IDENTIFIER)*;
cssProperties: cssProperty*;
cssProperty: IDENTIFIER COLON (STRING | NUMBER | IDENTIFIER) SEMICOLON;

// 函数调用
functionCall: IDENTIFIER LPAREN (argumentList)? RPAREN;
argumentList: argument (COMMA argument)*;
argument: (STRING | NUMBER | IDENTIFIER);