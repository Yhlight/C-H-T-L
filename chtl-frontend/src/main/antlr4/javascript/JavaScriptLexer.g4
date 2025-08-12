lexer grammar JavaScriptLexer;

// 多行注释
MultiLineComment: '/*' .*? '*/' -> channel(HIDDEN);
SingleLineComment: '//' ~[\r\n]* -> channel(HIDDEN);

// 正则表达式字面量
RegularExpressionLiteral: '/' RegularExpressionFirstChar RegularExpressionChar* '/' IdentifierPart*;

// 模板字面量
TemplateStringLiteral: '`' (TemplateStringCharacter | '${' .*? '}')* '`';

// 关键字
Break: 'break';
Do: 'do';
Instanceof: 'instanceof';
Typeof: 'typeof';
Case: 'case';
Else: 'else';
New: 'new';
Var: 'var';
Catch: 'catch';
Finally: 'finally';
Return: 'return';
Void: 'void';
Continue: 'continue';
For: 'for';
Switch: 'switch';
While: 'while';
Debugger: 'debugger';
Function: 'function';
This: 'this';
With: 'with';
Default: 'default';
If: 'if';
Throw: 'throw';
Delete: 'delete';
In: 'in';
Try: 'try';
Class: 'class';
Enum: 'enum';
Extends: 'extends';
Super: 'super';
Const: 'const';
Export: 'export';
Import: 'import';
Async: 'async';
Await: 'await';
Let: 'let';
Static: 'static';
Yield: 'yield';
From: 'from';
As: 'as';
Of: 'of';

// 未来保留字
Implements: 'implements';
Interface: 'interface';
Package: 'package';
Private: 'private';
Protected: 'protected';
Public: 'public';

// 字面量
NullLiteral: 'null';
BooleanLiteral: 'true' | 'false';

// 数字字面量
DecimalLiteral: DecimalIntegerLiteral '.' DecimalDigit* ExponentPart?
              | '.' DecimalDigit+ ExponentPart?
              | DecimalIntegerLiteral ExponentPart?;

HexIntegerLiteral: '0' [xX] HexDigit+;
OctalIntegerLiteral: '0' [oO] OctalDigit+;
BinaryIntegerLiteral: '0' [bB] BinaryDigit+;

// 字符串字面量
StringLiteral: '"' DoubleStringCharacter* '"'
             | '\'' SingleStringCharacter* '\'';

// 标识符
Identifier: IdentifierStart IdentifierPart*;

// 符号
OpenBracket: '[';
CloseBracket: ']';
OpenParen: '(';
CloseParen: ')';
OpenBrace: '{';
CloseBrace: '}';
SemiColon: ';';
Comma: ',';
Assign: '=';
QuestionMark: '?';
Colon: ':';
Ellipsis: '...';
Dot: '.';
PlusPlus: '++';
MinusMinus: '--';
Plus: '+';
Minus: '-';
BitNot: '~';
Not: '!';
Multiply: '*';
Divide: '/';
Modulus: '%';
Power: '**';
NullCoalesce: '??';
Hashtag: '#';
RightShiftArithmetic: '>>';
LeftShiftArithmetic: '<<';
RightShiftLogical: '>>>';
LessThan: '<';
MoreThan: '>';
LessThanEquals: '<=';
GreaterThanEquals: '>=';
Equals_: '==';
NotEquals: '!=';
IdentityEquals: '===';
IdentityNotEquals: '!==';
BitAnd: '&';
BitXOr: '^';
BitOr: '|';
And: '&&';
Or: '||';
MultiplyAssign: '*=';
DivideAssign: '/=';
ModulusAssign: '%=';
PlusAssign: '+=';
MinusAssign: '-=';
LeftShiftArithmeticAssign: '<<=';
RightShiftArithmeticAssign: '>>=';
RightShiftLogicalAssign: '>>>=';
BitAndAssign: '&=';
BitXorAssign: '^=';
BitOrAssign: '|=';
PowerAssign: '**=';
Arrow: '=>';

// 空白和换行
WhiteSpaces: [\t\u000B\u000C\u0020\u00A0]+ -> channel(HIDDEN);
LineTerminator: [\r\n\u2028\u2029] -> channel(HIDDEN);

// 片段规则
fragment DoubleStringCharacter: ~["\\\r\n] | '\\' EscapeSequence;
fragment SingleStringCharacter: ~['\\\r\n] | '\\' EscapeSequence;
fragment TemplateStringCharacter: ~[`\\$] | '\\' EscapeSequence | '$' ~[{];

fragment EscapeSequence: CharacterEscapeSequence
                       | '0'
                       | HexEscapeSequence
                       | UnicodeEscapeSequence;

fragment CharacterEscapeSequence: SingleEscapeCharacter | NonEscapeCharacter;
fragment SingleEscapeCharacter: ['"\\bfnrtv];
fragment NonEscapeCharacter: ~['"\\bfnrtv0-9xu\r\n];
fragment HexEscapeSequence: 'x' HexDigit HexDigit;
fragment UnicodeEscapeSequence: 'u' HexDigit HexDigit HexDigit HexDigit
                               | 'u' '{' HexDigit+ '}';

fragment DecimalIntegerLiteral: '0' | [1-9] DecimalDigit*;
fragment ExponentPart: [eE] [+-]? DecimalDigit+;
fragment DecimalDigit: [0-9];
fragment HexDigit: [0-9a-fA-F];
fragment OctalDigit: [0-7];
fragment BinaryDigit: [01];

fragment IdentifierStart: [a-zA-Z$_] | UnicodeEscapeSequence;
fragment IdentifierPart: IdentifierStart | [0-9];

fragment RegularExpressionFirstChar: ~[*\\/\r\n[] | RegularExpressionBackslashSequence | '[' RegularExpressionClassChar* ']';
fragment RegularExpressionChar: ~[\\/\r\n[] | RegularExpressionBackslashSequence | '[' RegularExpressionClassChar* ']';
fragment RegularExpressionClassChar: ~[\]\\\r\n] | RegularExpressionBackslashSequence;
fragment RegularExpressionBackslashSequence: '\\' ~[\r\n];

// 处理意外字符
UnexpectedCharacter: .;