grammar CHTL;

// 程序入口
program: statement* EOF;

// 语句
statement
    : element
    | textNode
    | styleBlock
    | scriptBlock
    | templateDeclaration
    | customDeclaration
    | originBlock
    | importStatement
    | namespaceDeclaration
    | configurationBlock
    | comment
    ;

// 注释
comment
    : LINE_COMMENT
    | BLOCK_COMMENT
    | GENERATOR_COMMENT
    ;

// 文本节点
textNode: TEXT LBRACE stringLiteral RBRACE;

// 字符串字面量
stringLiteral
    : STRING_LITERAL
    | SINGLE_STRING_LITERAL
    | UNQUOTED_LITERAL
    ;

// 元素节点
element: elementName elementBody?;

elementName: IDENTIFIER;

elementBody: LBRACE elementContent* RBRACE;

elementContent
    : attribute
    | element
    | textNode
    | styleBlock
    | scriptBlock
    | templateUsage
    | customUsage
    | originBlock
    | insertStatement
    | deleteStatement
    | exceptStatement
    ;

// 属性
attribute: attributeName (COLON | EQUALS) attributeValue SEMICOLON;

attributeName: IDENTIFIER;

attributeValue: stringLiteral;

// 样式块
styleBlock: STYLE LBRACE styleContent* RBRACE;

styleContent
    : cssProperty
    | cssSelector
    | templateUsage
    ;

// CSS属性
cssProperty: cssPropertyName COLON cssPropertyValue SEMICOLON;

cssPropertyName: IDENTIFIER (MINUS IDENTIFIER)*;

cssPropertyValue: stringLiteral | cssValue;

cssValue: ~(SEMICOLON | RBRACE)+;

// CSS选择器
cssSelector: selectorPattern LBRACE cssProperty* RBRACE;

selectorPattern
    : classSelector
    | idSelector
    | ampersandSelector
    | pseudoSelector
    ;

classSelector: DOT IDENTIFIER;
idSelector: HASH IDENTIFIER;
ampersandSelector: AMPERSAND (COLON IDENTIFIER)? (COLON COLON IDENTIFIER)?;
pseudoSelector: COLON IDENTIFIER;

// 脚本块
scriptBlock: SCRIPT LBRACE jsCode RBRACE;

jsCode: ~RBRACE*;

// 模板声明
templateDeclaration: LBRACKET TEMPLATE RBRACKET templateType templateName templateBody?;

templateType
    : AT_STYLE
    | AT_ELEMENT
    | AT_VAR
    ;

templateName: IDENTIFIER;

templateBody: LBRACE templateContent* RBRACE;

templateContent
    : cssProperty
    | element
    | varDeclaration
    | templateUsage
    | inheritStatement
    ;

// 变量声明
varDeclaration: IDENTIFIER COLON stringLiteral SEMICOLON;

// 自定义声明
customDeclaration: LBRACKET CUSTOM RBRACKET customType customName customBody?;

customType
    : AT_STYLE
    | AT_ELEMENT
    | AT_VAR
    ;

customName: IDENTIFIER;

customBody: LBRACE customContent* RBRACE;

customContent
    : cssProperty
    | cssPropertyWithoutValue
    | element
    | varDeclaration
    | templateUsage
    | customUsage
    | deleteStatement
    | insertStatement
    | inheritStatement
    ;

// 无值CSS属性
cssPropertyWithoutValue: cssPropertyName (COMMA cssPropertyName)* SEMICOLON;

// 模板使用
templateUsage: templateType templateName templateSpecialization? SEMICOLON;

templateSpecialization: LBRACE specializationContent* RBRACE;

specializationContent
    : cssProperty
    | deleteStatement
    | varAssignment
    ;

// 变量赋值
varAssignment: IDENTIFIER EQUALS stringLiteral;

// 自定义使用
customUsage: (LBRACKET CUSTOM RBRACKET)? customType customName customSpecialization? SEMICOLON;

customSpecialization: LBRACE specializationContent* RBRACE;

// 继承语句
inheritStatement: INHERIT templateType templateName SEMICOLON;

// 删除语句
deleteStatement: DELETE deleteTarget (COMMA deleteTarget)* SEMICOLON;

deleteTarget
    : cssPropertyName
    | elementName elementIndex?
    | templateType templateName
    | customType customName
    ;

elementIndex: LBRACKET NUMBER RBRACKET;

// 插入语句
insertStatement: INSERT insertPosition insertTarget LBRACE insertContent* RBRACE;

insertPosition
    : AFTER
    | BEFORE
    | REPLACE
    | AT TOP
    | AT BOTTOM
    ;

insertTarget: elementName elementIndex?;

insertContent
    : element
    | templateUsage
    ;

// 约束语句
exceptStatement: EXCEPT exceptTarget (COMMA exceptTarget)* SEMICOLON;

exceptTarget
    : elementName
    | templateType templateName?
    | customType customName?
    | AT_HTML
    | LBRACKET CUSTOM RBRACKET
    | LBRACKET TEMPLATE RBRACKET
    ;

// 原始嵌入块
originBlock: LBRACKET ORIGIN RBRACKET originType originName? originBody;

originType
    : AT_HTML
    | AT_STYLE
    | AT_JAVASCRIPT
    ;

originName: IDENTIFIER;

originBody: LBRACE rawContent RBRACE;

rawContent: ~RBRACE*;

// 导入语句
importStatement: LBRACKET IMPORT RBRACKET importContent;

importContent
    : importHtml
    | importCss
    | importJs
    | importChtl
    | importCustom
    | importTemplate
    ;

importHtml: AT_HTML FROM filePath (AS IDENTIFIER)? SEMICOLON;
importCss: AT_STYLE FROM filePath (AS IDENTIFIER)? SEMICOLON;
importJs: AT_JAVASCRIPT FROM filePath (AS IDENTIFIER)? SEMICOLON;
importChtl: AT_CHTL FROM filePath SEMICOLON;

importCustom: LBRACKET CUSTOM RBRACKET customType customName FROM filePath (AS IDENTIFIER)? SEMICOLON;
importTemplate: LBRACKET TEMPLATE RBRACKET templateType templateName FROM filePath (AS IDENTIFIER)? SEMICOLON;

filePath: stringLiteral;

// 命名空间声明
namespaceDeclaration
    : LBRACKET NAMESPACE RBRACKET namespaceName namespaceBody?
    | LBRACKET NAMESPACE RBRACKET namespaceName LBRACE namespaceContent* RBRACE
    ;

namespaceName: IDENTIFIER (DOT IDENTIFIER)*;

namespaceBody: LBRACE namespaceContent* RBRACE;

namespaceContent
    : namespaceDeclaration
    | templateDeclaration
    | customDeclaration
    | exceptStatement
    ;

// 配置块
configurationBlock: LBRACKET CONFIGURATION RBRACKET LBRACE configContent* RBRACE;

configContent
    : configAssignment
    | nameBlock
    ;

configAssignment: IDENTIFIER EQUALS configValue SEMICOLON;

configValue
    : stringLiteral
    | NUMBER
    | BOOLEAN
    ;

nameBlock: LBRACKET NAME RBRACKET LBRACE nameAssignment* RBRACE;

nameAssignment
    : IDENTIFIER EQUALS stringLiteral SEMICOLON
    | IDENTIFIER EQUALS LBRACKET stringLiteral (COMMA stringLiteral)* RBRACKET SEMICOLON
    ;

// 词法规则
// 关键字
TEXT: 'text';
STYLE: 'style';
SCRIPT: 'script';
TEMPLATE: 'Template';
CUSTOM: 'Custom';
ORIGIN: 'Origin';
IMPORT: 'Import';
NAMESPACE: 'Namespace';
CONFIGURATION: 'Configuration';
NAME: 'Name';
INFO: 'Info';
EXPORT: 'Export';

// 模板/自定义类型
AT_STYLE: '@Style' | '@style' | '@CSS' | '@Css' | '@css';
AT_ELEMENT: '@Element';
AT_VAR: '@Var';
AT_HTML: '@Html';
AT_JAVASCRIPT: '@JavaScript';
AT_CHTL: '@Chtl';

// 关键字
INHERIT: 'inherit';
DELETE: 'delete';
INSERT: 'insert';
AFTER: 'after';
BEFORE: 'before';
REPLACE: 'replace';
AT: 'at';
TOP: 'top';
BOTTOM: 'bottom';
FROM: 'from';
AS: 'as';
EXCEPT: 'except';

// 布尔值
BOOLEAN: 'true' | 'false';

// 操作符
COLON: ':';
SEMICOLON: ';';
EQUALS: '=';
COMMA: ',';
DOT: '.';
HASH: '#';
AMPERSAND: '&';
MINUS: '-';

// 括号
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
LPAREN: '(';
RPAREN: ')';

// 注释
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);
BLOCK_COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
GENERATOR_COMMENT: '--' ~[\r\n]*;

// 字符串
STRING_LITERAL: '"' (~["\\\r\n] | '\\' .)* '"';
SINGLE_STRING_LITERAL: '\'' (~['\\\r\n] | '\\' .)* '\'';

// 标识符和数字
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: [0-9]+('.'[0-9]+)?;

// 无引号字面量
UNQUOTED_LITERAL: ~[ \t\r\n{}:;=,"'()[\]]+;

// 空白字符
WS: [ \t\r\n]+ -> skip;