grammar CSS;

// CSS文档
stylesheet: statement* EOF;

statement
    : ruleset
    | media
    | page
    | fontFace
    | keyframes
    | supports
    | import
    | namespace
    | charset
    | nestedStatement
    ;

// 字符集声明
charset: CHARSET STRING SEMICOLON;

// 导入
import: IMPORT (STRING | url) mediaQueryList? SEMICOLON;

// 命名空间
namespace: NAMESPACE (IDENTIFIER)? (STRING | url) SEMICOLON;

// 媒体查询
media: MEDIA mediaQueryList LBRACE ruleset* RBRACE;

mediaQueryList: mediaQuery (COMMA mediaQuery)*;

mediaQuery: (ONLY | NOT)? mediaType (AND mediaExpression)*
          | mediaExpression (AND mediaExpression)*;

mediaType: IDENTIFIER;

mediaExpression: LPAREN mediaFeature (COLON value)? RPAREN;

mediaFeature: IDENTIFIER;

// 页面规则
page: PAGE pseudoPage? LBRACE declaration* RBRACE;

pseudoPage: COLON IDENTIFIER;

// 字体规则
fontFace: FONT_FACE LBRACE declaration* RBRACE;

// 关键帧
keyframes: KEYFRAMES IDENTIFIER LBRACE keyframeRule* RBRACE;

keyframeRule: keyframeSelector LBRACE declaration* RBRACE;

keyframeSelector: (FROM | TO | PERCENTAGE) (COMMA (FROM | TO | PERCENTAGE))*;

// 支持规则
supports: SUPPORTS supportsCondition LBRACE ruleset* RBRACE;

supportsCondition: supportsNegation | supportsConjunction | supportsDisjunction | supportsConditionInParens;

supportsNegation: NOT SPACE supportsConditionInParens;

supportsConjunction: supportsConditionInParens (SPACE AND SPACE supportsConditionInParens)+;

supportsDisjunction: supportsConditionInParens (SPACE OR SPACE supportsConditionInParens)+;

supportsConditionInParens: LPAREN supportsCondition RPAREN | supportsDeclarationCondition | generalEnclosed;

supportsDeclarationCondition: LPAREN declaration RPAREN;

generalEnclosed: LPAREN (~RPAREN)+ RPAREN;

// 规则集
ruleset: selectorList LBRACE declaration* RBRACE;

selectorList: selector (COMMA selector)*;

selector: simpleSelector (combinator simpleSelector)*;

combinator: PLUS | GREATER | TILDE | SPACE;

simpleSelector: (typeSelector | universal)? (idSelector | classSelector | attributeSelector | pseudoClass | pseudoElement)*
              | (idSelector | classSelector | attributeSelector | pseudoClass | pseudoElement)+;

typeSelector: typeNamespacePrefix? elementName;

typeNamespacePrefix: (IDENTIFIER | STAR)? PIPE;

elementName: IDENTIFIER;

universal: typeNamespacePrefix? STAR;

idSelector: HASH IDENTIFIER;

classSelector: DOT IDENTIFIER;

attributeSelector: LBRACKET IDENTIFIER (attributeOperator (STRING | IDENTIFIER))? RBRACKET;

attributeOperator: EQUALS | INCLUDES | DASHMATCH | PREFIXMATCH | SUFFIXMATCH | SUBSTRINGMATCH;

pseudoClass: COLON COLON? (IDENTIFIER | functionalPseudoClass);

functionalPseudoClass: FUNCTION (selector | NUMBER | STRING | IDENTIFIER)* RPAREN;

pseudoElement: COLON COLON IDENTIFIER;

// 声明
declaration: property COLON value important? SEMICOLON?;

property: IDENTIFIER (MINUS IDENTIFIER)*;

value: term (operator? term)*;

term
    : NUMBER
    | PERCENTAGE
    | LENGTH
    | EMS
    | EXS
    | ANGLE
    | TIME
    | FREQ
    | STRING
    | IDENTIFIER
    | url
    | hexcolor
    | function
    ;

function: FUNCTION value* RPAREN;

hexcolor: HASH HEXDIGIT+;

url: URL LPAREN STRING RPAREN;

operator: COMMA | SPACE | SLASH;

important: IMPORTANT;

// 嵌套语句（用于@规则内部）
nestedStatement: SEMICOLON;

// 词法规则
// 关键字
CHARSET: '@charset';
IMPORT: '@import';
NAMESPACE: '@namespace';
MEDIA: '@media';
PAGE: '@page';
FONT_FACE: '@font-face';
KEYFRAMES: '@keyframes' | '@-webkit-keyframes' | '@-moz-keyframes';
SUPPORTS: '@supports';

// 媒体查询关键字
ONLY: 'only';
NOT: 'not';
AND: 'and';
OR: 'or';
FROM: 'from';
TO: 'to';

// 重要性
IMPORTANT: '!important';

// 操作符
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
COLON: ':';
SEMICOLON: ';';
COMMA: ',';
DOT: '.';
HASH: '#';
PLUS: '+';
GREATER: '>';
TILDE: '~';
STAR: '*';
PIPE: '|';
SLASH: '/';
EQUALS: '=';
INCLUDES: '~=';
DASHMATCH: '|=';
PREFIXMATCH: '^=';
SUFFIXMATCH: '$=';
SUBSTRINGMATCH: '*=';

// 单位
LENGTH: NUMBER ('px' | 'cm' | 'mm' | 'in' | 'pt' | 'pc' | 'rem' | 'em' | 'ex' | 'ch' | 'vw' | 'vh' | 'vmin' | 'vmax');
EMS: NUMBER 'em';
EXS: NUMBER 'ex';
ANGLE: NUMBER ('deg' | 'rad' | 'grad' | 'turn');
TIME: NUMBER ('s' | 'ms');
FREQ: NUMBER ('hz' | 'khz');
PERCENTAGE: NUMBER '%';

// 函数
FUNCTION: IDENTIFIER LPAREN;
URL: 'url';

// 基本类型
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\\r\n] | '\\' .)* '"' | '\'' (~['\\\r\n] | '\\' .)* '\'';
IDENTIFIER: [a-zA-Z_-][a-zA-Z0-9_-]*;
HEXDIGIT: [0-9a-fA-F];

// 注释
COMMENT: '/*' .*? '*/' -> skip;

// 空格
SPACE: [ \t\r\n]+ -> skip;

// 其他字符
ANY: .;