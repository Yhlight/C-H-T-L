grammar CHTLJavaScript;

// 导入基础JavaScript语法
import JavaScript;

// 重写主表达式以支持CHTL扩展
primaryExpression
    : 'this'
    | identifier
    | literal
    | arrayLiteral
    | objectLiteral
    | functionExpression
    | classExpression
    | generatorExpression
    | asyncFunctionExpression
    | asyncGeneratorExpression
    | regularExpressionLiteral
    | templateLiteral
    | parenthesizedExpression
    | chtlSelector  // CHTL增强选择器
    ;

// CHTL增强选择器
chtlSelector
    : '{{' selectorExpression '}}'
    ;

selectorExpression
    : selectorIdentifier selectorIndex?  // {{box}} 或 {{button[0]}}
    | '.' selectorIdentifier              // {{.box}}
    | '#' selectorIdentifier              // {{#box}}
    | selectorIdentifier selectorIndex?   // {{button}}
    | complexSelector                     // {{.box button}}
    ;

selectorIdentifier
    : IDENTIFIER
    ;

selectorIndex
    : '[' NUMBER ']'
    ;

complexSelector
    : selectorPart (WS selectorPart)+
    ;

selectorPart
    : '.' selectorIdentifier
    | '#' selectorIdentifier
    | selectorIdentifier
    ;

// 重写成员表达式以支持->操作符
memberExpression
    : primaryExpression
    | memberExpression '[' expression ']'
    | memberExpression '.' identifierName
    | memberExpression '->' identifierName  // CHTL扩展：->操作符
    | memberExpression templateLiteral
    | 'super' '[' expression ']'
    | 'super' '.' identifierName
    | metaProperty
    | 'new' memberExpression arguments
    | memberExpression '?.' identifierName
    | memberExpression '?.' '[' expression ']'
    ;

// 重写调用表达式以支持CHTL方法
callExpression
    : memberExpression arguments
    | superCall
    | importCall
    | callExpression arguments
    | callExpression '[' expression ']'
    | callExpression '.' identifierName
    | callExpression '->' identifierName  // CHTL扩展：->操作符
    | callExpression templateLiteral
    | callExpression '?.' identifierName
    | callExpression '?.' '[' expression ']'
    | callExpression '->' 'listen' '(' listenConfig ')'     // CHTL listen方法
    | callExpression '->' 'delegate' '(' delegateConfig ')'  // CHTL delegate方法
    | animateCall  // 独立的animate调用
    ;

// animate调用（非递归）
animateCall
    : 'animate' '(' animateConfig ')'
    ;

// listen配置
listenConfig
    : '{' eventHandlerList '}'
    ;

eventHandlerList
    : eventHandler (',' eventHandler)*
    ;

eventHandler
    : IDENTIFIER ':' (assignmentExpression | arrowFunction | functionExpression)
    ;

// delegate配置
delegateConfig
    : '{' delegateProperty (',' delegateProperty)* '}'
    ;

delegateProperty
    : 'target' ':' (chtlSelector | selectorArray)
    | eventHandler
    ;

selectorArray
    : '[' chtlSelector (',' chtlSelector)* ']'
    ;

// animate配置
animateConfig
    : '{' animateProperty (',' animateProperty)* '}'
    ;

animateProperty
    : 'duration' ':' NUMBER
    | 'easing' ':' (IDENTIFIER | STRING_LITERAL)
    | 'begin' ':' cssBlock
    | 'when' ':' whenArray
    | 'end' ':' cssBlock
    | 'loop' ':' (NUMBER | '-1')
    | 'direction' ':' (IDENTIFIER | STRING_LITERAL)
    | 'delay' ':' NUMBER
    | 'callback' ':' (assignmentExpression | arrowFunction | functionExpression)
    ;

cssBlock
    : '{' cssProperty* '}'
    ;

cssProperty
    : propertyName ':' propertyValue (',' | ';')?
    ;

propertyName
    : IDENTIFIER ('-' IDENTIFIER)*
    ;

propertyValue
    : STRING_LITERAL
    | NUMBER
    | IDENTIFIER
    | cssFunction
    ;

cssFunction
    : IDENTIFIER '(' cssFunctionArguments? ')'
    ;

cssFunctionArguments
    : propertyValue (',' propertyValue)*
    ;

whenArray
    : '[' whenItem (',' whenItem)* ']'
    ;

whenItem
    : '{' whenProperty (',' whenProperty)* '}'
    ;

whenProperty
    : 'at' ':' NUMBER
    | cssProperty
    ;

// 词法规则扩展
ARROW : '->';

// 继承JavaScript的其他词法规则
NUMBER : [0-9]+ ('.' [0-9]+)?;
IDENTIFIER : [a-zA-Z_$] [a-zA-Z0-9_$]*;
STRING_LITERAL
    : '"' (~["\r\n\\] | '\\' .)* '"'
    | '\'' (~['\r\n\\] | '\\' .)* '\''
    ;

WS : [ \t\r\n]+ -> skip;

// 字面量
literal
    : DecimalLiteral
    | HexIntegerLiteral
    | OctalIntegerLiteral
    | OctalIntegerLiteral2
    | BinaryIntegerLiteral
    | BooleanLiteral
    | StringLiteral
    | NullLiteral
    | UnquotedLiteral     // 添加无修饰字面量
    ;

// 无修饰字面量（在某些上下文中允许）
UnquotedLiteral
    : UnquotedIdentifier
    ;

// 无修饰标识符
UnquotedIdentifier
    : [a-zA-Z_] [a-zA-Z0-9_-]*
    ;