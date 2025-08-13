grammar CSS;

// CSS文档入口
stylesheet
    : statement* EOF
    ;

// CSS语句
statement
    : ruleset
    | atRule
    | comment
    ;

// 规则集
ruleset
    : selectorList '{' declaration* '}'
    ;

// 选择器列表
selectorList
    : selector (',' selector)*
    ;

// 选择器
selector
    : simpleSelector (combinator simpleSelector)*
    ;

// 组合器
combinator
    : '>' // 子选择器
    | '+' // 相邻兄弟选择器
    | '~' // 通用兄弟选择器
    | WS  // 后代选择器（空格）
    ;

// 简单选择器
simpleSelector
    : (typeSelector | universalSelector)? (idSelector | classSelector | attributeSelector | pseudoSelector)*
    | (idSelector | classSelector | attributeSelector | pseudoSelector)+
    ;

// 类型选择器
typeSelector
    : IDENTIFIER
    ;

// 通用选择器
universalSelector
    : '*'
    ;

// ID选择器
idSelector
    : '#' IDENTIFIER
    ;

// 类选择器
classSelector
    : '.' IDENTIFIER
    ;

// 属性选择器
attributeSelector
    : '[' IDENTIFIER (attributeOperator (STRING_LITERAL | IDENTIFIER))? ']'
    ;

attributeOperator
    : '='
    | '~='
    | '|='
    | '^='
    | '$='
    | '*='
    ;

// 伪选择器
pseudoSelector
    : pseudoClass
    | pseudoElement
    ;

pseudoClass
    : ':' IDENTIFIER ('(' pseudoClassArgument ')')?
    | ':' 'not' '(' selectorList ')'
    | ':' ('is' | 'where' | 'has') '(' selectorList ')'
    ;

pseudoClassArgument
    : IDENTIFIER
    | NUMBER
    | STRING_LITERAL
    | expression
    ;

pseudoElement
    : '::' IDENTIFIER
    ;

// 声明
declaration
    : property ':' value (IMPORTANT)? ';'
    | property ':' value (IMPORTANT)?  // 允许最后一个声明没有分号
    ;

// 属性
property
    : IDENTIFIER ('-' IDENTIFIER)*
    | VARIABLE
    ;

// 值
value
    : term (operator? term)*
    ;

// 操作符
operator
    : '/'
    | ','
    | WS
    ;

// 项
term
    : unaryOperator? (numeric | percentage | length | angle | time | frequency | resolution)
    | STRING_LITERAL
    | IDENTIFIER
    | URI
    | hexcolor
    | function
    | VARIABLE
    | calc
    ;

unaryOperator
    : '-'
    | '+'
    ;

// 数值类型
numeric
    : NUMBER
    ;

percentage
    : NUMBER '%'
    ;

length
    : NUMBER (PX | EM | REM | VH | VW | VMIN | VMAX | CH | EX | CM | MM | IN | PT | PC)
    ;

angle
    : NUMBER (DEG | RAD | GRAD | TURN)
    ;

time
    : NUMBER (S | MS)
    ;

frequency
    : NUMBER (HZ | KHZ)
    ;

resolution
    : NUMBER (DPI | DPCM | DPPX)
    ;

// 颜色
hexcolor
    : '#' HEX_DIGIT+
    ;

// 函数
function
    : IDENTIFIER '(' functionArguments? ')'
    ;

functionArguments
    : functionArgument (',' functionArgument)*
    ;

functionArgument
    : value
    ;

// calc表达式
calc
    : 'calc' '(' calcExpression ')'
    ;

calcExpression
    : calcTerm (('+' | '-') calcTerm)*
    ;

calcTerm
    : calcFactor (('*' | '/') calcFactor)*
    ;

calcFactor
    : numeric
    | length
    | percentage
    | '(' calcExpression ')'
    | calc
    | VARIABLE
    ;

// @规则
atRule
    : atImport
    | atMedia
    | atKeyframes
    | atFontFace
    | atSupports
    | atPage
    | atNamespace
    | atCharset
    | atViewport
    | atCounterStyle
    | atFontFeatureValues
    | atProperty
    ;

// @import
atImport
    : '@import' (STRING_LITERAL | URI) mediaQueryList? ';'
    ;

// @media
atMedia
    : '@media' mediaQueryList '{' statement* '}'
    ;

mediaQueryList
    : mediaQuery (',' mediaQuery)*
    ;

mediaQuery
    : (ONLY | NOT)? mediaType (AND mediaFeature)*
    | mediaFeature (AND mediaFeature)*
    ;

mediaType
    : IDENTIFIER
    ;

mediaFeature
    : '(' IDENTIFIER (':' value)? ')'
    ;

// @keyframes
atKeyframes
    : '@keyframes' IDENTIFIER '{' keyframeBlock* '}'
    ;

keyframeBlock
    : keyframeSelector '{' declaration* '}'
    ;

keyframeSelector
    : FROM
    | TO
    | percentage
    | keyframeSelector ',' keyframeSelector
    ;

// @font-face
atFontFace
    : '@font-face' '{' declaration* '}'
    ;

// @supports
atSupports
    : '@supports' supportsCondition '{' statement* '}'
    ;

supportsCondition
    : supportsNegation
    | supportsConjunction
    | supportsDisjunction
    | supportsInParens
    ;

supportsNegation
    : NOT supportsInParens
    ;

supportsConjunction
    : supportsInParens (AND supportsInParens)+
    ;

supportsDisjunction
    : supportsInParens (OR supportsInParens)+
    ;

supportsInParens
    : '(' supportsCondition ')'
    | supportsFeature
    ;

supportsFeature
    : '(' declaration ')'
    ;

// @page
atPage
    : '@page' pseudoPage? '{' declaration* '}'
    ;

pseudoPage
    : ':' IDENTIFIER
    ;

// @namespace
atNamespace
    : '@namespace' IDENTIFIER? (STRING_LITERAL | URI) ';'
    ;

// @charset
atCharset
    : '@charset' STRING_LITERAL ';'
    ;

// @viewport
atViewport
    : '@viewport' '{' declaration* '}'
    ;

// @counter-style
atCounterStyle
    : '@counter-style' IDENTIFIER '{' declaration* '}'
    ;

// @font-feature-values
atFontFeatureValues
    : '@font-feature-values' fontFamilyName+ '{' fontFeatureValueBlock* '}'
    ;

fontFamilyName
    : STRING_LITERAL
    | IDENTIFIER
    ;

fontFeatureValueBlock
    : '@' IDENTIFIER '{' declaration* '}'
    ;

// @property
atProperty
    : '@property' VARIABLE '{' declaration* '}'
    ;

// 表达式
expression
    : term (operator term)*
    ;

// 注释
comment
    : COMMENT
    ;

// 词法规则
COMMENT : '/*' .*? '*/' -> channel(HIDDEN);

// 关键字
IMPORT : '@import';
MEDIA : '@media';
KEYFRAMES : '@keyframes';
FONT_FACE : '@font-face';
SUPPORTS : '@supports';
PAGE : '@page';
NAMESPACE : '@namespace';
CHARSET : '@charset';
VIEWPORT : '@viewport';
COUNTER_STYLE : '@counter-style';
FONT_FEATURE_VALUES : '@font-feature-values';
PROPERTY : '@property';

ONLY : 'only';
NOT : 'not';
AND : 'and';
OR : 'or';
FROM : 'from';
TO : 'to';

IMPORTANT : '!important';

// 单位
PX : 'px';
EM : 'em';
REM : 'rem';
VH : 'vh';
VW : 'vw';
VMIN : 'vmin';
VMAX : 'vmax';
CH : 'ch';
EX : 'ex';
CM : 'cm';
MM : 'mm';
IN : 'in';
PT : 'pt';
PC : 'pc';

DEG : 'deg';
RAD : 'rad';
GRAD : 'grad';
TURN : 'turn';

S : 's';
MS : 'ms';

HZ : 'Hz';
KHZ : 'kHz';

DPI : 'dpi';
DPCM : 'dpcm';
DPPX : 'dppx';

// 基本令牌
VARIABLE : '--' IDENTIFIER;
NUMBER : [0-9]+ ('.' [0-9]+)?;
STRING_LITERAL : '"' (~["\r\n] | '\\"')* '"' | '\'' (~['\r\n] | '\\\'')* '\'';
URI : 'url(' (~[)]+ | STRING_LITERAL) ')';
IDENTIFIER : [a-zA-Z_] [a-zA-Z0-9_-]*;
HEX_DIGIT : [0-9a-fA-F];

WS : [ \t\r\n]+ -> skip;