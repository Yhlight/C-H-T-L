parser grammar CssParser;

options {
    tokenVocab = CssLexer;
}

// 顶级规则
stylesheet
    : (CDO | CDC | WS | statement)*
    ;

statement
    : ruleset
    | atRule
    ;

// At规则
atRule
    : AT_IMPORT importRule
    | AT_MEDIA mediaRule
    | AT_CHARSET charsetRule
    | AT_NAMESPACE namespaceRule
    | AT_SUPPORTS supportsRule
    | AT_PAGE pageRule
    | AT_FONT_FACE fontFaceRule
    | AT_KEYFRAMES keyframesRule
    | AT_VIEWPORT viewportRule
    | atRuleGeneric
    ;

importRule
    : (STRING | URL) mediaQueryList? SEMICOLON
    ;

mediaRule
    : mediaQueryList LBRACE ruleset* RBRACE
    ;

mediaQueryList
    : mediaQuery (COMMA mediaQuery)*
    ;

mediaQuery
    : (ONLY | NOT)? mediaType (AND mediaExpression)*
    | mediaExpression (AND mediaExpression)*
    ;

mediaType
    : IDENTIFIER
    ;

mediaExpression
    : LPAREN mediaFeature (COLON value)? RPAREN
    ;

mediaFeature
    : IDENTIFIER
    ;

charsetRule
    : STRING SEMICOLON
    ;

namespaceRule
    : namespacePrefix? (STRING | URL) SEMICOLON
    ;

namespacePrefix
    : IDENTIFIER
    ;

supportsRule
    : supportsCondition LBRACE ruleset* RBRACE
    ;

supportsCondition
    : supportsNegation
    | supportsConjunction
    | supportsDisjunction
    | supportsConditionInParens
    ;

supportsNegation
    : NOT supportsConditionInParens
    ;

supportsConjunction
    : supportsConditionInParens (AND supportsConditionInParens)+
    ;

supportsDisjunction
    : supportsConditionInParens (OR supportsConditionInParens)+
    ;

supportsConditionInParens
    : LPAREN supportsCondition RPAREN
    | supportsDeclaration
    ;

supportsDeclaration
    : LPAREN property COLON value RPAREN
    ;

pageRule
    : pageSelector? LBRACE declaration* RBRACE
    ;

pageSelector
    : COLON IDENTIFIER
    ;

fontFaceRule
    : LBRACE declaration* RBRACE
    ;

keyframesRule
    : IDENTIFIER LBRACE keyframeRule* RBRACE
    ;

keyframeRule
    : keyframeSelector LBRACE declaration* RBRACE
    ;

keyframeSelector
    : (FROM | TO | PERCENTAGE) (COMMA (FROM | TO | PERCENTAGE))*
    ;

viewportRule
    : LBRACE declaration* RBRACE
    ;

atRuleGeneric
    : AT IDENTIFIER any* (LBRACE any* RBRACE | SEMICOLON)
    ;

// 规则集
ruleset
    : selectorList LBRACE declaration* RBRACE
    ;

selectorList
    : selector (COMMA selector)*
    ;

selector
    : simpleSelector (combinator simpleSelector)*
    ;

combinator
    : PLUS      // 相邻兄弟选择器
    | GT        // 子选择器
    | TILDE     // 通用兄弟选择器
    | WS+       // 后代选择器（空格）
    ;

simpleSelector
    : typeSelector (attributeSelector | classSelector | idSelector | pseudoSelector)*
    | (attributeSelector | classSelector | idSelector | pseudoSelector)+
    ;

typeSelector
    : (namespacePrefix PIPE)? (IDENTIFIER | STAR)
    ;

classSelector
    : DOT IDENTIFIER
    ;

idSelector
    : HASH IDENTIFIER
    ;

attributeSelector
    : LBRACKET attributeName (attributeOperator attributeValue)? RBRACKET
    ;

attributeName
    : (namespacePrefix PIPE)? IDENTIFIER
    ;

attributeOperator
    : EQUALS
    | TILDE_EQUALS
    | PIPE_EQUALS
    | CARET_EQUALS
    | DOLLAR_EQUALS
    | STAR_EQUALS
    ;

attributeValue
    : IDENTIFIER | STRING
    ;

pseudoSelector
    : COLON COLON? (IDENTIFIER | functionalPseudo)
    ;

functionalPseudo
    : FUNCTION (NUMBER | IDENTIFIER | selector)? RPAREN
    ;

// 声明
declaration
    : property COLON value (IMPORTANT)? SEMICOLON?
    ;

property
    : IDENTIFIER
    ;

value
    : term (operator? term)*
    ;

term
    : unaryOperator? (NUMBER | PERCENTAGE | LENGTH | EMS | REM | VW | VH | VMIN | VMAX | ANGLE | TIME | FREQ | RESOLUTION)
    | STRING
    | IDENTIFIER
    | URL
    | HEX_COLOR
    | function
    ;

function
    : FUNCTION value? RPAREN
    ;

operator
    : COMMA | SLASH | WS+
    ;

unaryOperator
    : PLUS | MINUS
    ;

// 通用规则
any
    : (~(LBRACE | RBRACE | SEMICOLON))+
    ;

// 长度单位
LENGTH: NUMBER (PX | EM | REM | VW | VH | VMIN | VMAX | CM | MM | IN | PT | PC | EX | CH);

// 百分比
PERCENTAGE: NUMBER PERCENT_UNIT;

// 角度
ANGLE: NUMBER (DEG | RAD | GRAD | TURN);

// 时间
TIME: NUMBER (S | MS);

// 频率
FREQ: NUMBER (HZ | KHZ);

// 分辨率
RESOLUTION: NUMBER (DPI | DPCM | DPPX);

// EMS单位（为了兼容性单独处理）
EMS: NUMBER EM;

// 其他单位和关键字
FROM: 'from';
TO: 'to';
SLASH: '/';
MINUS: '-';