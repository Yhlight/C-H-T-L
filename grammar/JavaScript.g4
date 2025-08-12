grammar JavaScript;

// 程序入口
program: statement* EOF;

// 语句
statement
    : block
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
    | functionDeclaration
    | classDeclaration
    | importStatement
    | exportStatement
    ;

// 块语句
block: LBRACE statement* RBRACE;

// 变量声明
variableStatement: variableDeclarationList SEMICOLON;

variableDeclarationList: varModifier variableDeclaration (COMMA variableDeclaration)*;

varModifier: VAR | LET | CONST;

variableDeclaration: assignable (EQUALS singleExpression)?;

// 空语句
emptyStatement: SEMICOLON;

// 表达式语句
expressionStatement: expressionSequence SEMICOLON;

// if语句
ifStatement: IF LPAREN expressionSequence RPAREN statement (ELSE statement)?;

// 循环语句
iterationStatement
    : DO statement WHILE LPAREN expressionSequence RPAREN SEMICOLON
    | WHILE LPAREN expressionSequence RPAREN statement
    | FOR LPAREN (expressionSequence | variableDeclarationList)? SEMICOLON expressionSequence? SEMICOLON expressionSequence? RPAREN statement
    | FOR LPAREN (singleExpression | variableDeclarationList) IN expressionSequence RPAREN statement
    | FOR LPAREN (singleExpression | variableDeclarationList) OF expressionSequence RPAREN statement
    | FOR AWAIT LPAREN (singleExpression | variableDeclarationList) OF expressionSequence RPAREN statement
    ;

// continue语句
continueStatement: CONTINUE IDENTIFIER? SEMICOLON;

// break语句
breakStatement: BREAK IDENTIFIER? SEMICOLON;

// return语句
returnStatement: RETURN expressionSequence? SEMICOLON;

// with语句
withStatement: WITH LPAREN expressionSequence RPAREN statement;

// 标签语句
labelledStatement: IDENTIFIER COLON statement;

// switch语句
switchStatement: SWITCH LPAREN expressionSequence RPAREN caseBlock;

caseBlock: LBRACE caseClauses? (defaultClause caseClauses?)? RBRACE;

caseClauses: caseClause+;

caseClause: CASE expressionSequence COLON statement*;

defaultClause: DEFAULT COLON statement*;

// throw语句
throwStatement: THROW expressionSequence SEMICOLON;

// try语句
tryStatement: TRY block (catchClause finallyClause? | finallyClause);

catchClause: CATCH (LPAREN assignable RPAREN)? block;

finallyClause: FINALLY block;

// 函数声明
functionDeclaration: ASYNC? FUNCTION STAR? IDENTIFIER LPAREN formalParameterList? RPAREN block;

// 类声明
classDeclaration: CLASS IDENTIFIER (EXTENDS singleExpression)? classTail;

classTail: LBRACE classElement* RBRACE;

classElement
    : STATIC? methodDefinition
    | emptyStatement
    | propertyName EQUALS singleExpression SEMICOLON
    ;

methodDefinition
    : propertyName LPAREN formalParameterList? RPAREN block
    | getter
    | setter
    | generatorMethod
    | asyncMethod
    ;

getter: GET propertyName LPAREN RPAREN block;

setter: SET propertyName LPAREN formalParameterList RPAREN block;

generatorMethod: STAR propertyName LPAREN formalParameterList? RPAREN block;

asyncMethod: ASYNC propertyName LPAREN formalParameterList? RPAREN block;

// 导入语句
importStatement: IMPORT (importFromBlock | STRING) SEMICOLON;

importFromBlock: (STAR AS IDENTIFIER | importNamespace) FROM STRING;

importNamespace: LBRACE (importSpecifier (COMMA importSpecifier)*)? RBRACE;

importSpecifier: (IDENTIFIER | moduleExportName) (AS IDENTIFIER)?;

moduleExportName: STRING | IDENTIFIER;

// 导出语句
exportStatement
    : EXPORT (exportFromBlock | declaration) SEMICOLON
    | EXPORT DEFAULT singleExpression SEMICOLON
    ;

exportFromBlock: (STAR | exportNamespace) FROM STRING;

exportNamespace: LBRACE (exportSpecifier (COMMA exportSpecifier)*)? RBRACE;

exportSpecifier: (IDENTIFIER | moduleExportName) (AS moduleExportName)?;

declaration: variableStatement | classDeclaration | functionDeclaration;

// 形参列表
formalParameterList: formalParameter (COMMA formalParameter)* (COMMA restParameter)?
                   | restParameter;

formalParameter: assignable (EQUALS singleExpression)?;

restParameter: ELLIPSIS assignable;

// 赋值目标
assignable: IDENTIFIER | arrayLiteral | objectLiteral;

// 属性名
propertyName
    : identifierName
    | STRING
    | NUMBER
    | LBRACKET singleExpression RBRACKET
    ;

// 表达式
expressionSequence: singleExpression (COMMA singleExpression)*;

singleExpression
    : anonymousFunction
    | arrowFunction
    | singleExpression LBRACKET expressionSequence RBRACKET                    // 成员索引
    | singleExpression DOT identifierName                                      // 成员访问
    | singleExpression arguments                                               // 函数调用
    | NEW singleExpression arguments?                                          // new表达式
    | singleExpression PLUSPLUS                                                // 后置递增
    | singleExpression MINUSMINUS                                              // 后置递减
    | DELETE singleExpression                                                  // delete
    | VOID singleExpression                                                    // void
    | TYPEOF singleExpression                                                  // typeof
    | PLUSPLUS singleExpression                                                // 前置递增
    | MINUSMINUS singleExpression                                              // 前置递减
    | PLUS singleExpression                                                    // 一元加
    | MINUS singleExpression                                                   // 一元减
    | TILDE singleExpression                                                   // 按位非
    | EXCLAMATION singleExpression                                             // 逻辑非
    | AWAIT singleExpression                                                   // await
    | singleExpression POWER singleExpression                                  // 幂运算
    | singleExpression (STAR | SLASH | PERCENT) singleExpression             // 乘除取余
    | singleExpression (PLUS | MINUS) singleExpression                       // 加减
    | singleExpression (LSHIFT | RSHIFT | URSHIFT) singleExpression         // 位移
    | singleExpression (LT | GT | LE | GE) singleExpression                 // 比较
    | singleExpression INSTANCEOF singleExpression                            // instanceof
    | singleExpression IN singleExpression                                    // in
    | singleExpression (EQUALS_OP | NOT_EQUALS | STRICT_EQUALS | STRICT_NOT_EQUALS) singleExpression  // 相等
    | singleExpression AMPERSAND singleExpression                             // 按位与
    | singleExpression CARET singleExpression                                 // 按位异或
    | singleExpression PIPE singleExpression                                  // 按位或
    | singleExpression AND_OP singleExpression                                // 逻辑与
    | singleExpression OR_OP singleExpression                                 // 逻辑或
    | singleExpression NULLISH_COALESCING singleExpression                   // 空值合并
    | singleExpression QUESTION singleExpression COLON singleExpression      // 三元
    | singleExpression EQUALS singleExpression                                // 赋值
    | singleExpression assignmentOperator singleExpression                    // 复合赋值
    // | singleExpression templateStringLiteral                                  // 模板字符串 - 已注释，改用TEMPLATE_STRING
    | THIS                                                                    // this
    | IDENTIFIER                                                              // 标识符
    | SUPER                                                                   // super
    | literal                                                                 // 字面量
    | arrayLiteral                                                            // 数组
    | objectLiteral                                                           // 对象
    | LPAREN expressionSequence RPAREN                                        // 分组
    | typeofExpression                                                        // typeof表达式
    ;

// 赋值操作符
assignmentOperator
    : STAR_EQUALS
    | SLASH_EQUALS
    | PERCENT_EQUALS
    | PLUS_EQUALS
    | MINUS_EQUALS
    | LSHIFT_EQUALS
    | RSHIFT_EQUALS
    | URSHIFT_EQUALS
    | AMPERSAND_EQUALS
    | CARET_EQUALS
    | PIPE_EQUALS
    | POWER_EQUALS
    | NULLISH_EQUALS
    ;

// 字面量
literal
    : NUMBER
    | STRING
    | TEMPLATE_STRING  // 使用新的TEMPLATE_STRING token
    | BOOLEAN
    | NULL
    | UNDEFINED
    | REGEX
    ;

// 注释掉旧的模板字符串规则，因为现在使用TEMPLATE_STRING token
// templateStringLiteral: BACKTICK templateStringAtom* BACKTICK;

// templateStringAtom
//     : TEMPLATE_STRING_ATOM
//     | DOLLAR_LBRACE singleExpression RBRACE
//     ;

// 数组字面量
arrayLiteral: LBRACKET elementList? RBRACKET;

elementList: arrayElement (COMMA arrayElement)*;

arrayElement: ELLIPSIS? singleExpression | COMMA;

// 对象字面量
objectLiteral: LBRACE propertyAssignment (COMMA propertyAssignment)* COMMA? RBRACE;

propertyAssignment
    : propertyName COLON singleExpression                          // 属性
    | LBRACKET singleExpression RBRACKET COLON singleExpression   // 计算属性
    | methodDefinition                                             // 方法
    | IDENTIFIER                                                   // 简写属性
    | ELLIPSIS singleExpression                                    // 扩展
    ;

// 参数列表
arguments: LPAREN argumentList? RPAREN;

argumentList: argument (COMMA argument)*;

argument: ELLIPSIS? singleExpression;

// 匿名函数
anonymousFunction: ASYNC? FUNCTION STAR? LPAREN formalParameterList? RPAREN block;

// 箭头函数
arrowFunction
    : ASYNC? arrowFunctionParameters ARROW arrowFunctionBody
    ;

arrowFunctionParameters
    : IDENTIFIER
    | LPAREN formalParameterList? RPAREN
    ;

arrowFunctionBody
    : singleExpression
    | block
    ;

// typeof表达式
typeofExpression: TYPEOF singleExpression;

// 标识符名称
identifierName: IDENTIFIER | reservedWord;

reservedWord: keyword | NULL | BOOLEAN;

keyword
    : BREAK | DO | INSTANCEOF | TYPEOF | CASE | ELSE | NEW | VAR | CATCH
    | FINALLY | RETURN | VOID | CONTINUE | FOR | SWITCH | WHILE | DEBUGGER
    | FUNCTION | THIS | WITH | DEFAULT | IF | THROW | DELETE | IN | TRY
    | CLASS | ENUM | EXTENDS | SUPER | CONST | EXPORT | IMPORT | ASYNC
    | AWAIT | YIELD | LET | STATIC | FROM | AS | OF
    ;

// 词法规则
// 关键字
BREAK: 'break';
DO: 'do';
INSTANCEOF: 'instanceof';
TYPEOF: 'typeof';
CASE: 'case';
ELSE: 'else';
NEW: 'new';
VAR: 'var';
CATCH: 'catch';
FINALLY: 'finally';
RETURN: 'return';
VOID: 'void';
CONTINUE: 'continue';
FOR: 'for';
SWITCH: 'switch';
WHILE: 'while';
DEBUGGER: 'debugger';
FUNCTION: 'function';
THIS: 'this';
WITH: 'with';
DEFAULT: 'default';
IF: 'if';
THROW: 'throw';
DELETE: 'delete';
IN: 'in';
TRY: 'try';
CLASS: 'class';
ENUM: 'enum';
EXTENDS: 'extends';
SUPER: 'super';
CONST: 'const';
EXPORT: 'export';
IMPORT: 'import';
ASYNC: 'async';
AWAIT: 'await';
YIELD: 'yield';
LET: 'let';
STATIC: 'static';
FROM: 'from';
AS: 'as';
OF: 'of';
GET: 'get';
SET: 'set';

// 字面量
NULL: 'null';
BOOLEAN: 'true' | 'false';
UNDEFINED: 'undefined';

// 操作符
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
SEMICOLON: ';';
COMMA: ',';
DOT: '.';
QUESTION: '?';
COLON: ':';
ELLIPSIS: '...';
EQUALS: '=';
STAR_EQUALS: '*=';
SLASH_EQUALS: '/=';
PERCENT_EQUALS: '%=';
PLUS_EQUALS: '+=';
MINUS_EQUALS: '-=';
LSHIFT_EQUALS: '<<=';
RSHIFT_EQUALS: '>>=';
URSHIFT_EQUALS: '>>>=';
AMPERSAND_EQUALS: '&=';
CARET_EQUALS: '^=';
PIPE_EQUALS: '|=';
POWER_EQUALS: '**=';
NULLISH_EQUALS: '??=';
ARROW: '=>';
PLUSPLUS: '++';
MINUSMINUS: '--';
PLUS: '+';
MINUS: '-';
TILDE: '~';
EXCLAMATION: '!';
STAR: '*';
SLASH: '/';
PERCENT: '%';
POWER: '**';
NULLISH_COALESCING: '??';
LSHIFT: '<<';
RSHIFT: '>>';
URSHIFT: '>>>';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
EQUALS_OP: '==';
NOT_EQUALS: '!=';
STRICT_EQUALS: '===';
STRICT_NOT_EQUALS: '!==';
AMPERSAND: '&';
CARET: '^';
PIPE: '|';
AND_OP: '&&';
OR_OP: '||';

// 数字
NUMBER: [0-9]+ ('.' [0-9]+)? ([eE] [+-]? [0-9]+)?;
BIGINT: [0-9]+ 'n';

// 字符串
STRING: '"' (~["\\\r\n] | '\\' .)* '"' | '\'' (~['\\\r\n] | '\\' .)* '\'';

// 模板字符串
BACKTICK: '`';
TEMPLATE_STRING: '`' (TEMPLATE_STRING_ATOM | TEMPLATE_EXPRESSION)* '`';
fragment TEMPLATE_STRING_ATOM: ~[`\\$]+ | '\\' . | '$' ~[{];
fragment TEMPLATE_EXPRESSION: '${' .*? '}';

// 正则表达式
REGEX: '/' REGEX_BODY '/' REGEX_FLAGS?;
fragment REGEX_BODY: (~[/\\\r\n] | '\\' .)+;
fragment REGEX_FLAGS: [gimsuvy]+;

// 标识符
IDENTIFIER: [a-zA-Z_$][a-zA-Z0-9_$]*;

// 注释
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;

// 空白
WS: [ \t\r\n]+ -> skip;