grammar CHTL;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTILINE_COMMENT: '/**/' .*? '/**/' -> skip;
GENERATOR_COMMENT: '--' ~[\r\n]* -> skip;

// 关键字
TEMPLATE: '[Template]';
CUSTOM: '[Custom]';
ORIGIN: '[Origin]';
CONFIGURATION: '[Configuration]';
IMPORT: '[Import]';
NAMESPACE: '[Namespace]';
INFO: '[Info]';
EXPORT: '[Export]';

// 类型标识符
STYLE: '@Style';
ELEMENT: '@Element';
VAR: '@Var';
HTML: '@Html';
CSS: '@Style';
JAVASCRIPT: '@JavaScript';
CHTL: '@Chtl';

// 操作关键字
INHERIT: 'inherit';
DELETE: 'delete';
INSERT: 'insert';
AFTER: 'after';
BEFORE: 'before';
REPLACE: 'replace';
AT_TOP: 'at top';
AT_BOTTOM: 'at bottom';
FROM: 'from';
AS: 'as';
EXCEPT: 'except';
TEXT: 'text';
STYLE_BLOCK: 'style';
SCRIPT: 'script';

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
AMPERSAND: '&';

// 标识符
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"' | '\'' (~['\\] | '\\' .)* '\'';
LITERAL: ~[ \t\r\n{}[]();:="'\n\r]+;

// 语法规则
program: (importStatement | namespaceStatement | configurationStatement | templateStatement | customStatement | originStatement | elementStatement)*;

importStatement: IMPORT importType FROM filePath (AS identifier)? SEMICOLON;
importType: (CUSTOM | TEMPLATE)? (STYLE | ELEMENT | VAR) identifier | HTML | CSS | JAVASCRIPT | CHTL;
filePath: STRING | identifier (DOT identifier)*;

namespaceStatement: NAMESPACE identifier (LBRACE namespaceContent RBRACE)?;
namespaceContent: (namespaceStatement | templateStatement | customStatement)*;

configurationStatement: CONFIGURATION LBRACE configContent RBRACE;
configContent: (configItem | nameGroup)*;
configItem: identifier EQUALS value SEMICOLON;
nameGroup: NAME LBRACE nameItems RBRACE;
nameItems: nameItem*;
nameItem: identifier EQUALS (value | arrayValue) SEMICOLON;
arrayValue: LBRACKET value (COMMA value)* RBRACKET;
value: STRING | NUMBER | identifier;

templateStatement: TEMPLATE templateType identifier LBRACE templateContent RBRACE;
templateType: STYLE | ELEMENT | VAR;
templateContent: (elementStatement | styleBlock | varDeclaration | templateInheritance)*;

customStatement: CUSTOM customType identifier LBRACE customContent RBRACE;
customType: STYLE | ELEMENT | VAR;
customContent: (elementStatement | styleBlock | varDeclaration | customInheritance | customModification)*;

originStatement: ORIGIN originType (identifier)? LBRACE originContent RBRACE;
originType: HTML | CSS | JAVASCRIPT;
originContent: .*?;

// 元素语句 - 支持HTML元素、text文本块、style样式块、script脚本块
elementStatement: elementName (attributes)? (LBRACE elementContent RBRACE)?;
elementName: identifier | textElement | styleElement | scriptElement;

// text文本块
textElement: TEXT LBRACE textContent RBRACE;
textContent: (STRING | LITERAL)*;

// style样式块 - 支持局部样式和上下文推导
styleElement: STYLE_BLOCK LBRACE styleContent RBRACE;
styleContent: (cssRule | templateUsage | customUsage)*;

// script脚本块
scriptElement: SCRIPT LBRACE scriptContent RBRACE;
scriptContent: .*?;

// CSS规则 - 支持选择器和上下文推导
cssRule: selector LBRACE cssProperties RBRACE;
selector: (DOT | HASH | AMPERSAND)? identifier (pseudoSelector)?;
pseudoSelector: (COLON | AMPERSAND COLON) identifier;
cssProperties: cssProperty*;
cssProperty: propertyName (COLON | EQUALS) propertyValue SEMICOLON;
propertyName: identifier;
propertyValue: (STRING | LITERAL | identifier | functionCall)*;

// 属性
attributes: attribute*;
attribute: attributeName (COLON | EQUALS) attributeValue SEMICOLON;
attributeName: identifier;
attributeValue: STRING | LITERAL | identifier;

// 元素内容
elementContent: (elementStatement | styleBlock | scriptBlock | templateUsage | customUsage | originStatement | constraintStatement)*;

// 样式块 - 支持局部样式管理
styleBlock: STYLE_BLOCK LBRACE styleContent RBRACE;

// 脚本块
scriptBlock: SCRIPT LBRACE scriptContent RBRACE;

// 模板使用
templateUsage: (TEMPLATE | CUSTOM)? (STYLE | ELEMENT | VAR) identifier (templateModification)? (FROM identifier)? SEMICOLON;
templateModification: LBRACE modificationContent RBRACE;
modificationContent: (modificationItem | templateInheritance | customInheritance)*;
modificationItem: (DELETE | INSERT) modificationTarget SEMICOLON;
modificationTarget: identifier | arrayAccess | templateReference;
arrayAccess: identifier LBRACKET NUMBER RBRACKET;
templateReference: (TEMPLATE | CUSTOM) (STYLE | ELEMENT | VAR) identifier;

// 自定义使用
customUsage: (CUSTOM)? (STYLE | ELEMENT | VAR) identifier (customModification)? (FROM identifier)? SEMICOLON;
customModification: LBRACE customModContent RBRACE;
customModContent: (customModItem | customInheritance)*;
customModItem: (DELETE | INSERT) customModTarget SEMICOLON;
customModTarget: identifier | arrayAccess | templateReference;

// 模板继承
templateInheritance: INHERIT (TEMPLATE | CUSTOM)? (STYLE | ELEMENT | VAR) identifier SEMICOLON;
customInheritance: (TEMPLATE | CUSTOM)? (STYLE | ELEMENT | VAR) identifier (customInheritanceMod)?;
customInheritanceMod: LBRACE customInheritanceContent RBRACE;
customInheritanceContent: (customInheritanceItem | templateInheritance)*;
customInheritanceItem: (DELETE | INSERT) customInheritanceTarget SEMICOLON;
customInheritanceTarget: identifier | arrayAccess | templateReference;

// 约束语句
constraintStatement: EXCEPT constraintTarget (COMMA constraintTarget)* SEMICOLON;
constraintTarget: identifier | templateReference | customReference;
customReference: CUSTOM (STYLE | ELEMENT | VAR) identifier;

// 函数调用
functionCall: identifier LPAREN (functionArg (COMMA functionArg)*)? RPAREN;
functionArg: (identifier (EQUALS value)?) | value;

// 变量声明
varDeclaration: identifier (COLON | EQUALS) value SEMICOLON;

// 辅助规则
NAME: 'Name';
identifier: IDENTIFIER;