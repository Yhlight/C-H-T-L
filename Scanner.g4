grammar Scanner;

// 扫描器主入口
document
    : codeBlock* EOF
    ;

// 代码块类型
codeBlock
    : chtlBlock
    | textBlock
    ;

// CHTL代码块
chtlBlock
    : chtlElement
    | chtlDeclaration
    | chtlStatement
    ;

// CHTL元素
chtlElement
    : elementStart elementContent* elementEnd
    ;

elementStart
    : IDENTIFIER '{'
    | TEXT '{'
    | STYLE '{'
    | SCRIPT '{'
    ;

elementEnd
    : '}'
    ;

elementContent
    : chtlAttribute
    | chtlElement
    | textContent
    | ANY_CONTENT
    ;

// CHTL属性
chtlAttribute
    : IDENTIFIER COLON_OR_EQUAL ATTR_VALUE ';'
    ;

// CHTL声明
chtlDeclaration
    : TEMPLATE_START ANY_CONTENT* '}'
    | CUSTOM_START ANY_CONTENT* '}'
    | CONFIG_START ANY_CONTENT* '}'
    | NAMESPACE_START ANY_CONTENT* '}'
    ;

// CHTL语句
chtlStatement
    : IMPORT_START ANY_CONTENT* ';'?
    | ORIGIN_START ANY_CONTENT* '}'
    ;

// 文本内容
textBlock
    : textContent
    ;

textContent
    : STRING_LITERAL
    | UNQUOTED_LITERAL
    | ANY_CONTENT
    ;

// 词法规则
TEXT : 'text';
STYLE : 'style';
SCRIPT : 'script';

TEMPLATE_START : '[Template]';
CUSTOM_START : '[Custom]';
CONFIG_START : '[Configuration]';
NAMESPACE_START : '[Namespace]';
IMPORT_START : '[Import]';
ORIGIN_START : '[Origin]';

COLON_OR_EQUAL : ':' | '=';

IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]*;
STRING_LITERAL : '"' (~["\r\n\\] | '\\' .)* '"' | '\'' (~['\r\n\\] | '\\' .)* '\'';
UNQUOTED_LITERAL : [a-zA-Z0-9_#]+ ([a-zA-Z0-9_\-#:()]* [a-zA-Z0-9_#])?;
ATTR_VALUE : ~[;\r\n]+;
ANY_CONTENT : ~[{};\r\n]+;

WS : [ \t\r\n]+ -> skip;
COMMENT : '//' ~[\r\n]* -> skip;
MULTI_COMMENT : '/*' .*? '*/' -> skip;