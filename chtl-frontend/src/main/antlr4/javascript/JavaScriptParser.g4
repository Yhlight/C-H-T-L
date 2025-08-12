parser grammar JavaScriptParser;

options {
    tokenVocab = JavaScriptLexer;
}

// 程序入口
program
    : sourceElements? EOF
    ;

sourceElements
    : sourceElement+
    ;

sourceElement
    : statement
    | functionDeclaration
    | classDeclaration
    | importStatement
    | exportStatement
    ;

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
    | debuggerStatement
    ;

block
    : OpenBrace statementList? CloseBrace
    ;

statementList
    : statement+
    ;

variableStatement
    : variableDeclarationList eos
    ;

variableDeclarationList
    : varModifier variableDeclaration (Comma variableDeclaration)*
    ;

variableDeclaration
    : assignable (Assign singleExpression)?
    ;

varModifier
    : Var
    | Let
    | Const
    ;

emptyStatement
    : SemiColon
    ;

expressionStatement
    : expressionSequence eos
    ;

ifStatement
    : If OpenParen expressionSequence CloseParen statement (Else statement)?
    ;

iterationStatement
    : Do statement While OpenParen expressionSequence CloseParen eos
    | While OpenParen expressionSequence CloseParen statement
    | For OpenParen (expressionSequence | variableDeclarationList)? SemiColon expressionSequence? SemiColon expressionSequence? CloseParen statement
    | For OpenParen (singleExpression | variableDeclarationList) (In | Of) expressionSequence CloseParen statement
    | For Await? OpenParen (singleExpression | variableDeclarationList) (In | Of) expressionSequence CloseParen statement
    ;

continueStatement
    : Continue Identifier? eos
    ;

breakStatement
    : Break Identifier? eos
    ;

returnStatement
    : Return expressionSequence? eos
    ;

withStatement
    : With OpenParen expressionSequence CloseParen statement
    ;

switchStatement
    : Switch OpenParen expressionSequence CloseParen caseBlock
    ;

caseBlock
    : OpenBrace caseClauses? (defaultClause caseClauses?)? CloseBrace
    ;

caseClauses
    : caseClause+
    ;

caseClause
    : Case expressionSequence Colon statementList?
    ;

defaultClause
    : Default Colon statementList?
    ;

labelledStatement
    : Identifier Colon statement
    ;

throwStatement
    : Throw expressionSequence eos
    ;

tryStatement
    : Try block (catchProduction finallyProduction? | finallyProduction)
    ;

catchProduction
    : Catch (OpenParen assignable? CloseParen)? block
    ;

finallyProduction
    : Finally block
    ;

debuggerStatement
    : Debugger eos
    ;

// 函数声明
functionDeclaration
    : Async? Function Identifier OpenParen formalParameterList? CloseParen OpenBrace functionBody CloseBrace
    ;

// 类声明
classDeclaration
    : Class Identifier classHeritage? OpenBrace classElement* CloseBrace
    ;

classHeritage
    : Extends singleExpression
    ;

classElement
    : (Static | Async)? methodDefinition
    | emptyStatement
    ;

methodDefinition
    : propertyName OpenParen formalParameterList? CloseParen OpenBrace functionBody CloseBrace
    | getter OpenParen CloseParen OpenBrace functionBody CloseBrace
    | setter OpenParen formalParameterList CloseParen OpenBrace functionBody CloseBrace
    ;

formalParameterList
    : formalParameterArg (Comma formalParameterArg)* (Comma lastFormalParameterArg)?
    | lastFormalParameterArg
    ;

formalParameterArg
    : assignable (Assign singleExpression)?
    ;

lastFormalParameterArg
    : Ellipsis singleExpression
    ;

functionBody
    : sourceElements?
    ;

// Import/Export
importStatement
    : Import importFromBlock
    ;

importFromBlock
    : importDefault? (importNamespace | moduleItems) From StringLiteral eos
    | StringLiteral eos
    ;

moduleItems
    : OpenBrace (aliasName Comma)* (aliasName Comma?)? CloseBrace
    ;

importDefault
    : aliasName Comma
    ;

importNamespace
    : (Multiply | identifierName) (As identifierName)?
    ;

aliasName
    : identifierName (As identifierName)?
    ;

exportStatement
    : Export (exportFromBlock | declaration) eos
    | Export Default singleExpression eos
    ;

exportFromBlock
    : moduleItems From StringLiteral
    | Multiply (As identifierName)? From StringLiteral
    ;

declaration
    : variableStatement
    | classDeclaration
    | functionDeclaration
    ;

// 表达式
expressionSequence
    : singleExpression (Comma singleExpression)*
    ;

singleExpression
    : functionExpression
    | classExpression
    | singleExpression OpenBracket expressionSequence CloseBracket // 成员访问
    | singleExpression Dot identifierName                          // 成员访问
    | singleExpression arguments                                    // 函数调用
    | New singleExpression arguments?                              // new表达式
    | singleExpression PlusPlus                                    // 后置++
    | singleExpression MinusMinus                                  // 后置--
    | Delete singleExpression                                      // delete
    | Void singleExpression                                        // void
    | Typeof singleExpression                                      // typeof
    | PlusPlus singleExpression                                    // 前置++
    | MinusMinus singleExpression                                  // 前置--
    | Plus singleExpression                                        // 一元+
    | Minus singleExpression                                       // 一元-
    | BitNot singleExpression                                      // ~
    | Not singleExpression                                         // !
    | Await singleExpression                                       // await
    | singleExpression (Multiply | Divide | Modulus) singleExpression            // 乘除模
    | singleExpression (Plus | Minus) singleExpression                           // 加减
    | singleExpression (LeftShiftArithmetic | RightShiftArithmetic | RightShiftLogical) singleExpression  // 位移
    | singleExpression (LessThan | MoreThan | LessThanEquals | GreaterThanEquals) singleExpression       // 比较
    | singleExpression Instanceof singleExpression                                // instanceof
    | singleExpression In singleExpression                                        // in
    | singleExpression (Equals_ | NotEquals | IdentityEquals | IdentityNotEquals) singleExpression       // 相等
    | singleExpression BitAnd singleExpression                                    // &
    | singleExpression BitXOr singleExpression                                    // ^
    | singleExpression BitOr singleExpression                                     // |
    | singleExpression And singleExpression                                       // &&
    | singleExpression Or singleExpression                                        // ||
    | singleExpression NullCoalesce singleExpression                             // ??
    | singleExpression QuestionMark singleExpression Colon singleExpression       // 三元
    | singleExpression Assign singleExpression                                    // 赋值
    | singleExpression assignmentOperator singleExpression                        // 复合赋值
    | singleExpression templateStringLiteral                                      // 标签模板
    | This                                                          // this
    | Identifier                                                    // 标识符
    | Super                                                         // super
    | literal                                                       // 字面量
    | arrayLiteral                                                  // 数组
    | objectLiteral                                                 // 对象
    | OpenParen expressionSequence CloseParen                       // 分组
    | arrowFunctionDeclaration                                      // 箭头函数
    ;

assignmentOperator
    : MultiplyAssign
    | DivideAssign
    | ModulusAssign
    | PlusAssign
    | MinusAssign
    | LeftShiftArithmeticAssign
    | RightShiftArithmeticAssign
    | RightShiftLogicalAssign
    | BitAndAssign
    | BitXorAssign
    | BitOrAssign
    | PowerAssign
    ;

literal
    : NullLiteral
    | BooleanLiteral
    | StringLiteral
    | TemplateStringLiteral
    | RegularExpressionLiteral
    | numericLiteral
    ;

templateStringLiteral
    : TemplateStringLiteral
    ;

numericLiteral
    : DecimalLiteral
    | HexIntegerLiteral
    | OctalIntegerLiteral
    | BinaryIntegerLiteral
    ;

identifierName
    : Identifier
    | reservedWord
    ;

reservedWord
    : keyword
    | NullLiteral
    | BooleanLiteral
    ;

keyword
    : Break
    | Do
    | Instanceof
    | Typeof
    | Case
    | Else
    | New
    | Var
    | Catch
    | Finally
    | Return
    | Void
    | Continue
    | For
    | Switch
    | While
    | Debugger
    | Function
    | This
    | With
    | Default
    | If
    | Throw
    | Delete
    | In
    | Try
    | Class
    | Enum
    | Extends
    | Super
    | Const
    | Export
    | Import
    | Async
    | Await
    | Let
    | Static
    | Yield
    | From
    | As
    | Of
    ;

getter
    : {this.n("get")}? Identifier propertyName
    ;

setter
    : {this.n("set")}? Identifier propertyName
    ;

propertyName
    : identifierName
    | StringLiteral
    | numericLiteral
    | OpenBracket singleExpression CloseBracket
    ;

arguments
    : OpenParen (argument (Comma argument)* Comma?)? CloseParen
    ;

argument
    : Ellipsis? singleExpression
    ;

expressionSequence
    : singleExpression (Comma singleExpression)*
    ;

arrayLiteral
    : OpenBracket elementList? CloseBracket
    ;

elementList
    : (Ellipsis? singleExpression)? (Comma (Ellipsis? singleExpression)?)*
    ;

objectLiteral
    : OpenBrace (propertyAssignment (Comma propertyAssignment)* Comma?)? CloseBrace
    ;

propertyAssignment
    : propertyName (Colon | Assign) singleExpression
    | OpenBracket singleExpression CloseBracket Colon singleExpression
    | methodDefinition
    | identifierName
    | Ellipsis singleExpression
    ;

functionExpression
    : Async? Function Identifier? OpenParen formalParameterList? CloseParen OpenBrace functionBody CloseBrace
    ;

classExpression
    : Class Identifier? classHeritage? OpenBrace classElement* CloseBrace
    ;

arrowFunctionDeclaration
    : Async? arrowFunctionParameters Arrow arrowFunctionBody
    ;

arrowFunctionParameters
    : Identifier
    | OpenParen formalParameterList? CloseParen
    ;

arrowFunctionBody
    : singleExpression
    | OpenBrace functionBody CloseBrace
    ;

assignable
    : Identifier
    | arrayLiteral
    | objectLiteral
    ;

// 语句结束
eos
    : SemiColon
    | EOF
    | {this.lineTerminatorAhead()}?
    | {this.closeBrace()}?
    ;