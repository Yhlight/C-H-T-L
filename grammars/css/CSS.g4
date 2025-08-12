grammar CSS;

// 词法规则
WS: [ \t\r\n]+ -> skip;
COMMENT: '/*' .*? '*/' -> skip;

// 选择器
SELECTOR: '#' | '.' | '*' | '>' | '+' | '~' | '|' | '^' | '$' | '=' | '~=' | '|=' | '^=' | '$=' | '*=';

// 单位
UNIT: 'px' | 'em' | 'rem' | 'vh' | 'vw' | '%' | 'deg' | 'rad' | 'turn' | 'ms' | 's' | 'Hz' | 'kHz';

// 颜色关键字
COLOR_KEYWORD: 'transparent' | 'currentColor' | 'inherit' | 'initial' | 'unset' | 'revert' | 'revert-layer';

// 函数
FUNCTION: 'calc' | 'var' | 'url' | 'rgb' | 'rgba' | 'hsl' | 'hsla' | 'linear-gradient' | 'radial-gradient' | 'conic-gradient' | 'repeating-linear-gradient' | 'repeating-radial-gradient' | 'repeating-conic-gradient' | 'matrix' | 'translate' | 'scale' | 'rotate' | 'skew' | 'perspective' | 'translate3d' | 'scale3d' | 'rotate3d' | 'skew3d' | 'matrix3d' | 'translateX' | 'translateY' | 'translateZ' | 'scaleX' | 'scaleY' | 'scaleZ' | 'rotateX' | 'rotateY' | 'rotateZ' | 'skewX' | 'skewY' | 'perspective-origin' | 'backface-visibility' | 'transform-style' | 'transform-origin' | 'transform-box' | 'will-change' | 'contain' | 'content-visibility' | 'contain-intrinsic-size' | 'contain-intrinsic-block-size' | 'contain-intrinsic-inline-size' | 'contain-intrinsic-width' | 'contain-intrinsic-height' | 'contain-intrinsic-min-width' | 'contain-intrinsic-max-width' | 'contain-intrinsic-min-height' | 'contain-intrinsic-max-height';

// 伪类
PSEUDO_CLASS: 'active' | 'any' | 'checked' | 'default' | 'defined' | 'disabled' | 'empty' | 'enabled' | 'first' | 'first-child' | 'first-of-type' | 'fullscreen' | 'focus' | 'focus-visible' | 'focus-within' | 'host' | 'hover' | 'indeterminate' | 'in-range' | 'invalid' | 'last-child' | 'last-of-type' | 'left' | 'link' | 'not' | 'nth-child' | 'nth-last-child' | 'nth-last-of-type' | 'nth-of-type' | 'only-child' | 'only-of-type' | 'optional' | 'out-of-range' | 'past' | 'placeholder-shown' | 'read-only' | 'read-write' | 'required' | 'right' | 'root' | 'scope' | 'target' | 'valid' | 'visited';

// 伪元素
PSEUDO_ELEMENT: 'after' | 'before' | 'cue' | 'first-letter' | 'first-line' | 'grammar-error' | 'marker' | 'part' | 'placeholder' | 'selection' | 'slotted' | 'spelling-error';

// 媒体查询关键字
MEDIA_KEYWORD: 'all' | 'print' | 'screen' | 'speech' | 'only' | 'not' | 'and' | 'or';

// 属性值关键字
VALUE_KEYWORD: 'auto' | 'none' | 'normal' | 'inherit' | 'initial' | 'unset' | 'revert' | 'revert-layer' | 'static' | 'relative' | 'absolute' | 'fixed' | 'sticky' | 'block' | 'inline' | 'inline-block' | 'flex' | 'inline-flex' | 'grid' | 'inline-grid' | 'table' | 'inline-table' | 'table-row' | 'table-cell' | 'table-column' | 'table-column-group' | 'table-header-group' | 'table-footer-group' | 'table-row-group' | 'table-caption' | 'list-item' | 'run-in' | 'compact' | 'marker' | 'table-header-group' | 'table-footer-group' | 'table-row-group' | 'table-column-group' | 'table-column' | 'table-cell' | 'table-row' | 'table-caption' | 'table-header-group' | 'table-footer-group' | 'table-row-group' | 'table-column-group' | 'table-column' | 'table-cell' | 'table-row' | 'table-caption';

// 标识符
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_-]*;
NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' (~["\\] | '\\' .)* '"';

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
ASTERISK: '*';
GREATER: '>';
PLUS: '+';
TILDE: '~';
PIPE: '|';
CARET: '^';
DOLLAR: '$';
EQUALS: '=';
EXCLAMATION: '!';
PERCENT: '%';
SLASH: '/';

// 语法规则
stylesheet: (charset | import | namespace | nestedStatement)*;

charset: '@charset' STRING SEMICOLON;
import: '@import' importList SEMICOLON;
importList: (STRING | url) (mediaQueryList)?;
namespace: '@namespace' (prefix)? (STRING | url) SEMICOLON;
prefix: IDENTIFIER;

nestedStatement: ruleset | media | page | fontFace | keyframes | supports | document | viewport | counterStyle | fontFeatureValues | atRule;

ruleset: selectorList LBRACE declarationList? RBRACE;
selectorList: selector (COMMA selector)*;
selector: simpleSelectorSequence (combinator simpleSelectorSequence)*;
combinator: (PLUS | GREATER | TILDE | PLUS GREATER) | (GREATER GREATER) | (PLUS PLUS) | (TILDE TILDE);

simpleSelectorSequence: (typeSelector | universal) (hash | class | attrib | pseudo | negation)* | (hash | class | attrib | pseudo | negation)+;
typeSelector: namespacePrefix? elementName;
namespacePrefix: (IDENTIFIER | '*')? PIPE;
elementName: IDENTIFIER;
universal: namespacePrefix? ASTERISK;
class: DOT IDENTIFIER;
hash: HASH IDENTIFIER;
attrib: LBRACKET namespacePrefix? IDENTIFIER (attribOperator attribValue)? RBRACKET;
attribOperator: EQUALS | INCLUDES | DASHMATCH | PREFIXMATCH | SUFFIXMATCH | SUBSTRINGMATCH;
attribValue: STRING | IDENTIFIER;
INCLUDES: '~=';
DASHMATCH: '|=';
PREFIXMATCH: '^=';
SUFFIXMATCH: '$=';
SUBSTRINGMATCH: '*=';

pseudo: COLON COLON? (IDENTIFIER | functionalPseudo);
functionalPseudo: FUNCTION LPAREN expression RPAREN;
expression: (PLUS | MINUS | DIMENSION | unknownDimension | NUMBER | IDENTIFIER | STRING | url | hexcolor | unicodeRange | subexpression)*;
subexpression: LPAREN expression RPAREN;
MINUS: '-';

negation: COLON NOT LPAREN negationArg RPAREN;
NOT: 'not';
negationArg: typeSelector | universal | hash | class | attrib | pseudo;

declarationList: (SEMICOLON)* declaration (SEMICOLON declaration)* (SEMICOLON)*;
declaration: property COLON expr (important)?;
property: IDENTIFIER;
expr: (PLUS | MINUS | DIMENSION | unknownDimension | NUMBER | IDENTIFIER | STRING | url | hexcolor | unicodeRange | subexpression)*;
important: EXCLAMATION (WS | COMMENT)* 'important';

url: URL LPAREN (STRING | urlContent) RPAREN;
URL: 'url';
urlContent: (PLUS | MINUS | DIMENSION | unknownDimension | NUMBER | IDENTIFIER | STRING | hexcolor | unicodeRange | subexpression)*;

hexcolor: HASH (NUMBER | [a-fA-F])+;
unicodeRange: U_PLUS (NUMBER | [a-fA-F])+ (QUESTION | [a-fA-F])* | U_PLUS QUESTION+;
U_PLUS: 'U+' | 'u+';
QUESTION: '?';

media: MEDIA mediaQueryList LBRACE ruleset* RBRACE;
MEDIA: '@media';
mediaQueryList: (mediaQuery (COMMA mediaQuery)*)?;
mediaQuery: (ONLY | NOT)? mediaType (AND mediaExpression)* | mediaExpression (AND mediaExpression)*;
ONLY: 'only';
AND: 'and';
mediaType: IDENTIFIER;
mediaExpression: LPAREN mediaFeature (COLON expr)? RPAREN;
mediaFeature: IDENTIFIER;

page: PAGE pseudoPage? LBRACE declarationList? RBRACE;
PAGE: '@page';
pseudoPage: COLON IDENTIFIER;

fontFace: FONTFACE LBRACE declarationList? RBRACE;
FONTFACE: '@font-face';

keyframes: KEYFRAMES keyframesName LBRACE keyframesBlocks RBRACE;
KEYFRAMES: '@keyframes' | '@-webkit-keyframes' | '@-moz-keyframes' | '@-o-keyframes';
keyframesName: IDENTIFIER | STRING;
keyframesBlocks: (keyframeSelector LBRACE declarationList? RBRACE)*;
keyframeSelector: (FROM | TO | PERCENTAGE) (COMMA (FROM | TO | PERCENTAGE))*;
FROM: 'from';
TO: 'to';
PERCENTAGE: PERCENT;

supports: SUPPORTS supportsCondition LBRACE ruleset* RBRACE;
SUPPORTS: '@supports';
supportsCondition: supportsConditionInParens (AND supportsConditionInParens)* | supportsConditionInParens (OR supportsConditionInParens)*;
supportsConditionInParens: LPAREN supportsCondition RPAREN | LPAREN supportsDeclarationCondition RPAREN | LPAREN supportsFeatureType RPAREN | LPAREN supportsFeature RPAREN;
supportsDeclarationCondition: declaration;
supportsFeatureType: IDENTIFIER;
supportsFeature: supportsFeatureName COLON supportsFeatureValue;
supportsFeatureName: IDENTIFIER;
supportsFeatureValue: expr;
OR: 'or';

document: DOCUMENT documentFunction LBRACE ruleset* RBRACE;
DOCUMENT: '@document';
documentFunction: url | urlPrefix | domain | regexp;
urlPrefix: URL_PREFIX LPAREN STRING RPAREN;
URL_PREFIX: 'url-prefix';
domain: DOMAIN LPAREN STRING RPAREN;
DOMAIN: 'domain';
regexp: REGEXP LPAREN STRING RPAREN;
REGEXP: 'regexp';

viewport: VIEWPORT LBRACE declarationList? RBRACE;
VIEWPORT: '@viewport';

counterStyle: COUNTER_STYLE IDENTIFIER LBRACE declarationList? RBRACE;
COUNTER_STYLE: '@counter-style';

fontFeatureValues: FONT_FEATURE_VALUES fontFamilyNameList LBRACE featureValueBlock* RBRACE;
FONT_FEATURE_VALUES: '@font-feature-values';
fontFamilyNameList: fontFamilyName (COMMA fontFamilyName)*;
fontFamilyName: (STRING | IDENTIFIER) (WS IDENTIFIER)*;
featureValueBlock: featureType LBRACE featureValueDefinition* RBRACE;
featureType: ATKEYWORD;
ATKEYWORD: '@' IDENTIFIER;
featureValueDefinition: IDENTIFIER COLON NUMBER+ SEMICOLON;

atRule: ATKEYWORD (ruleset | declarationList | mediaQueryList | mediaQuery | keyframesName | keyframesBlocks | fontFamilyNameList | featureValueBlock | supportsCondition | supportsConditionInParens | supportsDeclarationCondition | supportsFeatureType | supportsFeature | supportsFeatureName | supportsFeatureValue | documentFunction | url | urlPrefix | domain | regexp | expression | subexpression | LPAREN | RPAREN | LBRACE | RBRACE | LBRACKET | RBRACKET | SEMICOLON | COLON | COMMA | DOT | HASH | ASTERISK | GREATER | PLUS | TILDE | PIPE | CARET | DOLLAR | EQUALS | EXCLAMATION | PERCENT | SLASH | MINUS | QUESTION | IDENTIFIER | NUMBER | STRING | FUNCTION | PSEUDO_CLASS | PSEUDO_ELEMENT | MEDIA_KEYWORD | VALUE_KEYWORD | COLOR_KEYWORD | UNIT)*;

unknownDimension: NUMBER IDENTIFIER;