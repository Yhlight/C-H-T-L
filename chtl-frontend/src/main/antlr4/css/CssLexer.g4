lexer grammar CssLexer;

// 符号
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
GT: '>';
PLUS: '+';
TILDE: '~';
STAR: '*';
PIPE: '|';
CARET: '^';
DOLLAR: '$';
EQUALS: '=';
EXCLAMATION: '!';
AT: '@';
PERCENT: '%';
AMPERSAND: '&';
IMPORTANT: '!important';

// 操作符
PLUS_EQUALS: '+=';
TILDE_EQUALS: '~=';
PIPE_EQUALS: '|=';
CARET_EQUALS: '^=';
DOLLAR_EQUALS: '$=';
STAR_EQUALS: '*=';

// 伪类和伪元素
COLON_COLON: '::';
COLON_NOT: ':not';
COLON_NTH_CHILD: ':nth-child';
COLON_NTH_OF_TYPE: ':nth-of-type';
COLON_FIRST_CHILD: ':first-child';
COLON_LAST_CHILD: ':last-child';
COLON_HOVER: ':hover';
COLON_FOCUS: ':focus';
COLON_ACTIVE: ':active';
COLON_VISITED: ':visited';
COLON_BEFORE: ':before';
COLON_AFTER: ':after';
DOUBLE_COLON_BEFORE: '::before';
DOUBLE_COLON_AFTER: '::after';

// At规则
AT_IMPORT: '@import';
AT_MEDIA: '@media';
AT_CHARSET: '@charset';
AT_NAMESPACE: '@namespace';
AT_SUPPORTS: '@supports';
AT_DOCUMENT: '@document';
AT_PAGE: '@page';
AT_FONT_FACE: '@font-face';
AT_KEYFRAMES: '@keyframes';
AT_VIEWPORT: '@viewport';

// 单位
PX: 'px';
EM: 'em';
REM: 'rem';
VW: 'vw';
VH: 'vh';
VMIN: 'vmin';
VMAX: 'vmax';
CM: 'cm';
MM: 'mm';
IN: 'in';
PT: 'pt';
PC: 'pc';
EX: 'ex';
CH: 'ch';
PERCENT_UNIT: '%';
DEG: 'deg';
RAD: 'rad';
GRAD: 'grad';
TURN: 'turn';
S: 's';
MS: 'ms';
HZ: 'Hz' | 'hz';
KHZ: 'kHz' | 'khz';
DPI: 'dpi';
DPCM: 'dpcm';
DPPX: 'dppx';

// 数字
NUMBER: '-'? (DIGIT+ ('.' DIGIT*)? | '.' DIGIT+);
fragment DIGIT: [0-9];

// 颜色
HEX_COLOR: '#' HEX_DIGIT+;
fragment HEX_DIGIT: [0-9a-fA-F];

// 函数
FUNCTION: IDENTIFIER '(';

// 标识符
IDENTIFIER: NMSTART NMCHAR*;
fragment NMSTART: [a-zA-Z_] | NON_ASCII | ESCAPE;
fragment NMCHAR: [a-zA-Z0-9_-] | NON_ASCII | ESCAPE;
fragment NON_ASCII: ~[\u0000-\u007F];
fragment ESCAPE: '\\' (~[\r\n\f] | HEX_DIGIT{1,6} WS?);

// 字符串
STRING: '"' (~["\\\r\n] | ESCAPE | '\\\n')* '"'
      | '\'' (~['\\\r\n] | ESCAPE | '\\\n')* '\'';

// URL
URL: 'url(' WS* (STRING | (~[)'"\\\r\n\t ] | ESCAPE)*) WS* ')';

// 注释
COMMENT: '/*' .*? '*/' -> skip;

// 空白
WS: [ \t\r\n\f]+ -> skip;

// CDO/CDC (用于兼容性)
CDO: '<!--';
CDC: '-->';

// 通用选择器
UNIVERSAL: '*';

// Class和ID前缀已经在上面定义为DOT和HASH

// 媒体查询操作符
AND: 'and';
OR: 'or';
NOT: 'not';
ONLY: 'only';

// 捕获所有其他字符
ANY: .;