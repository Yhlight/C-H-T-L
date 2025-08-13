grammar JavaScript;

// 程序入口
program
    : sourceElements? EOF
    ;

sourceElements
    : sourceElement+
    ;

sourceElement
    : statement
    | declaration
    ;

// 声明
declaration
    : hoistableDeclaration
    | classDeclaration
    | lexicalDeclaration
    ;

hoistableDeclaration
    : functionDeclaration
    | generatorDeclaration
    | asyncFunctionDeclaration
    | asyncGeneratorDeclaration
    ;

// 函数声明
functionDeclaration
    : 'function' identifier '(' formalParameterList? ')' '{' functionBody '}'
    ;

generatorDeclaration
    : 'function' '*' identifier '(' formalParameterList? ')' '{' functionBody '}'
    ;

asyncFunctionDeclaration
    : 'async' 'function' identifier '(' formalParameterList? ')' '{' functionBody '}'
    ;

asyncGeneratorDeclaration
    : 'async' 'function' '*' identifier '(' formalParameterList? ')' '{' functionBody '}'
    ;

// 类声明
classDeclaration
    : 'class' identifier classExtends? '{' classBody '}'
    ;

classExtends
    : 'extends' leftHandSideExpression
    ;

classBody
    : classElement*
    ;

classElement
    : methodDefinition
    | 'static' methodDefinition
    | fieldDefinition
    | 'static' fieldDefinition
    | ';'
    ;

methodDefinition
    : propertyName '(' formalParameterList? ')' '{' functionBody '}'
    | 'get' propertyName '(' ')' '{' functionBody '}'
    | 'set' propertyName '(' formalParameter ')' '{' functionBody '}'
    | 'async' propertyName '(' formalParameterList? ')' '{' functionBody '}'
    | '*' propertyName '(' formalParameterList? ')' '{' functionBody '}'
    | 'async' '*' propertyName '(' formalParameterList? ')' '{' functionBody '}'
    ;

fieldDefinition
    : propertyName initializer?
    ;

// 词法声明
lexicalDeclaration
    : letOrConst bindingList ';'
    ;

letOrConst
    : 'let'
    | 'const'
    ;

bindingList
    : lexicalBinding (',' lexicalBinding)*
    ;

lexicalBinding
    : bindingIdentifier initializer?
    | bindingPattern initializer
    ;

// 语句
statement
    : blockStatement
    | variableStatement
    | emptyStatement
    | expressionStatement
    | ifStatement
    | iterationStatement
    | continueStatement
    | breakStatement
    | returnStatement
    | withStatement
    | labelledStatement
    | switchStatement
    | throwStatement
    | tryStatement
    | debuggerStatement
    | importStatement
    | exportStatement
    ;

// 块语句
blockStatement
    : '{' statementList? '}'
    ;

statementList
    : statement+
    ;

// 变量语句
variableStatement
    : 'var' variableDeclarationList ';'
    ;

variableDeclarationList
    : variableDeclaration (',' variableDeclaration)*
    ;

variableDeclaration
    : bindingIdentifier initializer?
    | bindingPattern initializer
    ;

// 空语句
emptyStatement
    : ';'
    ;

// 表达式语句
expressionStatement
    : expression ';'
    ;

// if语句
ifStatement
    : 'if' '(' expression ')' statement ('else' statement)?
    ;

// 迭代语句
iterationStatement
    : doWhileStatement
    | whileStatement
    | forStatement
    | forInStatement
    | forOfStatement
    ;

doWhileStatement
    : 'do' statement 'while' '(' expression ')' ';'
    ;

whileStatement
    : 'while' '(' expression ')' statement
    ;

forStatement
    : 'for' '(' forInit? ';' expression? ';' expression? ')' statement
    ;

forInit
    : expression
    | 'var' variableDeclarationList
    | lexicalDeclaration
    ;

forInStatement
    : 'for' '(' forInBinding 'in' expression ')' statement
    ;

forOfStatement
    : 'for' 'await'? '(' forInBinding 'of' expression ')' statement
    ;

forInBinding
    : bindingIdentifier
    | bindingPattern
    | 'var' bindingIdentifier initializer?
    | 'var' bindingPattern initializer
    | letOrConst bindingIdentifier
    | letOrConst bindingPattern
    ;

// continue语句
continueStatement
    : 'continue' identifier? ';'
    ;

// break语句
breakStatement
    : 'break' identifier? ';'
    ;

// return语句
returnStatement
    : 'return' expression? ';'
    ;

// with语句
withStatement
    : 'with' '(' expression ')' statement
    ;

// 标签语句
labelledStatement
    : identifier ':' statement
    ;

// switch语句
switchStatement
    : 'switch' '(' expression ')' '{' caseClause* defaultClause? caseClause* '}'
    ;

caseClause
    : 'case' expression ':' statementList?
    ;

defaultClause
    : 'default' ':' statementList?
    ;

// throw语句
throwStatement
    : 'throw' expression ';'
    ;

// try语句
tryStatement
    : 'try' blockStatement catchClause? finallyClause?
    | 'try' blockStatement finallyClause
    ;

catchClause
    : 'catch' ('(' catchParameter ')')? blockStatement
    ;

catchParameter
    : bindingIdentifier
    | bindingPattern
    ;

finallyClause
    : 'finally' blockStatement
    ;

// debugger语句
debuggerStatement
    : 'debugger' ';'
    ;

// 模块语句
importStatement
    : 'import' importClause 'from' moduleSpecifier ';'
    | 'import' moduleSpecifier ';'
    ;

importClause
    : importedDefaultBinding
    | namedImports
    | importedDefaultBinding ',' namedImports
    | importedDefaultBinding ',' namespaceImport
    | namespaceImport
    ;

importedDefaultBinding
    : bindingIdentifier
    ;

namespaceImport
    : '*' 'as' bindingIdentifier
    ;

namedImports
    : '{' '}'
    | '{' importsList ','? '}'
    ;

importsList
    : importSpecifier (',' importSpecifier)*
    ;

importSpecifier
    : bindingIdentifier
    | identifierName 'as' bindingIdentifier
    ;

moduleSpecifier
    : STRING_LITERAL
    ;

exportStatement
    : 'export' exportClause 'from' moduleSpecifier ';'
    | 'export' exportClause ';'
    | 'export' variableStatement
    | 'export' declaration
    | 'export' 'default' hoistableDeclaration
    | 'export' 'default' classDeclaration
    | 'export' 'default' assignmentExpression ';'
    ;

exportClause
    : '{' '}'
    | '{' exportsList ','? '}'
    | '*'
    | '*' 'as' identifierName
    ;

exportsList
    : exportSpecifier (',' exportSpecifier)*
    ;

exportSpecifier
    : identifierName
    | identifierName 'as' identifierName
    ;

// 表达式
expression
    : assignmentExpression (',' assignmentExpression)*
    ;

assignmentExpression
    : conditionalExpression
    | yieldExpression
    | arrowFunction
    | asyncArrowFunction
    | leftHandSideExpression assignmentOperator assignmentExpression
    ;

assignmentOperator
    : '='
    | '*='
    | '/='
    | '%='
    | '+='
    | '-='
    | '<<='
    | '>>='
    | '>>>='
    | '&='
    | '^='
    | '|='
    | '**='
    | '&&='
    | '||='
    | '??='
    ;

conditionalExpression
    : coalesceExpression ('?' assignmentExpression ':' assignmentExpression)?
    ;

coalesceExpression
    : logicalORExpression ('??' coalesceExpression)?
    ;

logicalORExpression
    : logicalANDExpression ('||' logicalANDExpression)*
    ;

logicalANDExpression
    : bitwiseORExpression ('&&' bitwiseORExpression)*
    ;

bitwiseORExpression
    : bitwiseXORExpression ('|' bitwiseXORExpression)*
    ;

bitwiseXORExpression
    : bitwiseANDExpression ('^' bitwiseANDExpression)*
    ;

bitwiseANDExpression
    : equalityExpression ('&' equalityExpression)*
    ;

equalityExpression
    : relationalExpression (('==' | '!=' | '===' | '!==') relationalExpression)*
    ;

relationalExpression
    : shiftExpression (('<' | '>' | '<=' | '>=' | 'instanceof' | 'in') shiftExpression)*
    ;

shiftExpression
    : additiveExpression (('<<' | '>>' | '>>>') additiveExpression)*
    ;

additiveExpression
    : multiplicativeExpression (('+' | '-') multiplicativeExpression)*
    ;

multiplicativeExpression
    : exponentiationExpression (('*' | '/' | '%') exponentiationExpression)*
    ;

exponentiationExpression
    : unaryExpression ('**' exponentiationExpression)?
    ;

unaryExpression
    : updateExpression
    | 'delete' unaryExpression
    | 'void' unaryExpression
    | 'typeof' unaryExpression
    | '+' unaryExpression
    | '-' unaryExpression
    | '~' unaryExpression
    | '!' unaryExpression
    | 'await' unaryExpression
    ;

updateExpression
    : leftHandSideExpression
    | leftHandSideExpression '++'
    | leftHandSideExpression '--'
    | '++' unaryExpression
    | '--' unaryExpression
    ;

leftHandSideExpression
    : newExpression
    | callExpression
    ;

newExpression
    : memberExpression
    | 'new' newExpression
    ;

callExpression
    : memberExpression arguments
    | superCall
    | importCall
    | callExpression arguments
    | callExpression '[' expression ']'
    | callExpression '.' identifierName
    | callExpression templateLiteral
    | callExpression '?.' identifierName
    | callExpression '?.' '[' expression ']'
    ;

superCall
    : 'super' arguments
    ;

importCall
    : 'import' '(' assignmentExpression ')'
    ;

arguments
    : '(' argumentList? ')'
    ;

argumentList
    : argument (',' argument)*
    ;

argument
    : assignmentExpression
    | '...' assignmentExpression
    ;

memberExpression
    : primaryExpression
    | memberExpression '[' expression ']'
    | memberExpression '.' identifierName
    | memberExpression templateLiteral
    | 'super' '[' expression ']'
    | 'super' '.' identifierName
    | metaProperty
    | 'new' memberExpression arguments
    | memberExpression '?.' identifierName
    | memberExpression '?.' '[' expression ']'
    ;

metaProperty
    : 'new' '.' 'target'
    | 'import' '.' 'meta'
    ;

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
    ;

parenthesizedExpression
    : '(' expression ')'
    ;

// 字面量
literal
    : nullLiteral
    | booleanLiteral
    | numericLiteral
    | stringLiteral
    ;

nullLiteral
    : 'null'
    ;

booleanLiteral
    : 'true'
    | 'false'
    ;

numericLiteral
    : DECIMAL_LITERAL
    | BINARY_LITERAL
    | OCTAL_LITERAL
    | HEX_LITERAL
    ;

stringLiteral
    : STRING_LITERAL
    ;

// 数组字面量
arrayLiteral
    : '[' elementList? ']'
    ;

elementList
    : arrayElement (',' arrayElement)*
    ;

arrayElement
    : assignmentExpression
    | '...' assignmentExpression
    |  // 省略的元素
    ;

// 对象字面量
objectLiteral
    : '{' propertyDefinitionList? '}'
    | '{' propertyDefinitionList ',' '}'
    ;

propertyDefinitionList
    : propertyDefinition (',' propertyDefinition)*
    ;

propertyDefinition
    : identifierName
    | propertyName ':' assignmentExpression
    | methodDefinition
    | '...' assignmentExpression
    ;

propertyName
    : identifierName
    | stringLiteral
    | numericLiteral
    | '[' assignmentExpression ']'
    ;

// 函数表达式
functionExpression
    : 'function' identifier? '(' formalParameterList? ')' '{' functionBody '}'
    ;

generatorExpression
    : 'function' '*' identifier? '(' formalParameterList? ')' '{' functionBody '}'
    ;

asyncFunctionExpression
    : 'async' 'function' identifier? '(' formalParameterList? ')' '{' functionBody '}'
    ;

asyncGeneratorExpression
    : 'async' 'function' '*' identifier? '(' formalParameterList? ')' '{' functionBody '}'
    ;

// 类表达式
classExpression
    : 'class' identifier? classExtends? '{' classBody '}'
    ;

// 箭头函数
arrowFunction
    : arrowParameters '=>' arrowBody
    ;

asyncArrowFunction
    : 'async' arrowParameters '=>' arrowBody
    ;

arrowParameters
    : bindingIdentifier
    | '(' formalParameterList? ')'
    ;

arrowBody
    : assignmentExpression
    | '{' functionBody '}'
    ;

// yield表达式
yieldExpression
    : 'yield'
    | 'yield' assignmentExpression
    | 'yield' '*' assignmentExpression
    ;

// 模板字面量
templateLiteral
    : '`' templateSpans? '`'
    ;

templateSpans
    : templateSpan+
    ;

templateSpan
    : TEMPLATE_STRING_LITERAL
    | TEMPLATE_STRING_START expression templateMiddle* TEMPLATE_STRING_END
    ;

templateMiddle
    : TEMPLATE_STRING_MIDDLE expression
    ;

// 正则表达式
regularExpressionLiteral
    : REGEX_LITERAL
    ;

// 形参
formalParameterList
    : formalParameter (',' formalParameter)* (',' restParameter)?
    | restParameter
    ;

formalParameter
    : bindingElement
    ;

restParameter
    : '...' bindingIdentifier
    | '...' bindingPattern
    ;

bindingElement
    : bindingIdentifier initializer?
    | bindingPattern initializer?
    ;

// 绑定模式
bindingPattern
    : objectBindingPattern
    | arrayBindingPattern
    ;

objectBindingPattern
    : '{' bindingPropertyList? '}'
    | '{' bindingPropertyList ',' '}'
    ;

bindingPropertyList
    : bindingProperty (',' bindingProperty)*
    ;

bindingProperty
    : bindingIdentifier
    | propertyName ':' bindingElement
    | '...' bindingIdentifier
    ;

arrayBindingPattern
    : '[' bindingElementList? ']'
    ;

bindingElementList
    : bindingElision? bindingElement (',' bindingElision? bindingElement)* (',' bindingElision?)?
    ;

bindingElision
    : ','
    ;

// 函数体
functionBody
    : sourceElements?
    ;

// 初始化器
initializer
    : '=' assignmentExpression
    ;

// 标识符
bindingIdentifier
    : identifier
    | 'yield'
    | 'await'
    ;

identifier
    : IDENTIFIER
    | 'yield'
    | 'await'
    ;

identifierName
    : IDENTIFIER
    | reservedWord
    ;

reservedWord
    : keyword
    | futureReservedWord
    | nullLiteral
    | booleanLiteral
    ;

keyword
    : 'break'
    | 'case'
    | 'catch'
    | 'class'
    | 'const'
    | 'continue'
    | 'debugger'
    | 'default'
    | 'delete'
    | 'do'
    | 'else'
    | 'export'
    | 'extends'
    | 'finally'
    | 'for'
    | 'function'
    | 'if'
    | 'import'
    | 'in'
    | 'instanceof'
    | 'new'
    | 'return'
    | 'super'
    | 'switch'
    | 'this'
    | 'throw'
    | 'try'
    | 'typeof'
    | 'var'
    | 'void'
    | 'while'
    | 'with'
    | 'yield'
    | 'let'
    | 'static'
    | 'await'
    | 'async'
    ;

futureReservedWord
    : 'enum'
    | 'implements'
    | 'interface'
    | 'package'
    | 'private'
    | 'protected'
    | 'public'
    ;

// 词法规则
DECIMAL_LITERAL : [0-9]+ ('.' [0-9]+)? ([eE] [+-]? [0-9]+)?;
BINARY_LITERAL : '0' [bB] [01]+;
OCTAL_LITERAL : '0' [oO] [0-7]+;
HEX_LITERAL : '0' [xX] [0-9a-fA-F]+;

STRING_LITERAL
    : '"' (~["\r\n\\] | '\\' .)* '"'
    | '\'' (~['\r\n\\] | '\\' .)* '\''
    ;

TEMPLATE_STRING_LITERAL : '`' (~[`\\] | '\\' .)* '`';
TEMPLATE_STRING_START : '`' (~[`\\$] | '\\' . | '$' ~[{])* '${';
TEMPLATE_STRING_MIDDLE : '}' (~[`\\$] | '\\' . | '$' ~[{])* '${';
TEMPLATE_STRING_END : '}' (~[`\\$] | '\\' . | '$' ~[{])* '`';

REGEX_LITERAL : '/' (~[/\r\n\\] | '\\' .)+ '/' [gimsuvy]*;

IDENTIFIER : [a-zA-Z_$] [a-zA-Z0-9_$]*;

SINGLE_LINE_COMMENT : '//' ~[\r\n]* -> channel(HIDDEN);
MULTI_LINE_COMMENT : '/*' .*? '*/' -> channel(HIDDEN);

WS : [ \t\r\n]+ -> skip;
LINE_TERMINATOR : [\r\n]+;