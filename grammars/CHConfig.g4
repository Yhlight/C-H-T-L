grammar CHConfig;

// 配置文件
configFile
    : configBlock* EOF
    ;

// 配置块
configBlock
    : configHeader LBRACE configItem* RBRACE
    | configHeader configItem*  // 允许不使用大括号
    ;

// 配置头（完全灵活）
configHeader
    : LBRACKET configName RBRACKET    // [Configuration]
    | configName                       // Configuration
    | anyToken+ configName            // 任意前缀 + Configuration
    ;

configName
    : IDENTIFIER
    | STRING_LITERAL
    ;

// 配置项
configItem
    : key ASSIGN value SEMICOLON?
    | key COLON value SEMICOLON?      // 支持冒号语法
    | key value SEMICOLON?            // 支持无分隔符语法
    | nestedConfig
    ;

// 嵌套配置
nestedConfig
    : configHeader LBRACE configItem* RBRACE
    | configHeader configItem*
    ;

// 键
key
    : IDENTIFIER
    | STRING_LITERAL
    | keywordAlias                    // 允许使用任意关键字别名
    ;

// 关键字别名（可以是任意形式）
keywordAlias
    : anyToken+
    ;

// 值
value
    : STRING_LITERAL
    | NUMBER
    | BOOLEAN
    | arrayValue
    | objectValue
    | keywordValue
    ;

// 数组值
arrayValue
    : LBRACKET (value (COMMA value)*)? RBRACKET
    | value (COMMA value)+            // 允许无括号的数组
    ;

// 对象值
objectValue
    : LBRACE (objectPair (COMMA objectPair)*)? RBRACE
    ;

objectPair
    : key (ASSIGN | COLON)? value
    ;

// 关键字值（完全自定义）
keywordValue
    : prefixedKeyword
    | unprefixedKeyword
    | customPattern
    ;

// 带前缀的关键字
prefixedKeyword
    : AT_SIGN? anyToken+              // @Style 或 Style
    | LBRACKET anyToken+ RBRACKET     // [Template]
    | anyPrefix anyToken+             // 任意前缀
    ;

// 无前缀关键字
unprefixedKeyword
    : IDENTIFIER (DOT IDENTIFIER)*     // 支持点号分隔
    ;

// 自定义模式
customPattern
    : anyToken+ LPAREN anyToken* RPAREN  // 函数式语法
    | anyToken+ LBRACE anyToken* RBRACE  // 块式语法
    | anyToken+                           // 任意标记
    ;

// 任意前缀
anyPrefix
    : ~(IDENTIFIER | WHITESPACE)+
    ;

// 任意标记
anyToken
    : IDENTIFIER
    | STRING_LITERAL
    | NUMBER
    | BOOLEAN
    | SPECIAL_CHAR
    | AT_SIGN
    | HASH
    | DOLLAR
    | PERCENT
    | CARET
    | AMPERSAND
    | STAR
    | PLUS
    | MINUS
    | SLASH
    | BACKSLASH
    | PIPE
    | TILDE
    | EXCLAMATION
    | QUESTION
    | LT
    | GT
    ;

// 词法规则

// 布尔值
BOOLEAN : 'true' | 'false' | 'yes' | 'no' | 'on' | 'off';

// 数字
NUMBER
    : '-'? INT ('.' INT)?
    | '0x' HEX+
    | '0b' BIN+
    ;

// 字符串
STRING_LITERAL
    : '"' (~["\\\r\n] | EscapeSequence)* '"'
    | '\'' (~['\\\r\n] | EscapeSequence)* '\''
    | '`' (~[`\\] | EscapeSequence)* '`'
    ;

// 标识符（支持Unicode）
IDENTIFIER
    : [\p{L}_$][\p{L}\p{N}_$]*        // 支持所有语言的字母
    | [\u4E00-\u9FFF]+                 // 中文字符
    | [\u3040-\u309F]+                 // 平假名
    | [\u30A0-\u30FF]+                 // 片假名
    | [\uAC00-\uD7AF]+                 // 韩文
    ;

// 操作符
ASSIGN : '=';
COLON : ':';
SEMICOLON : ';';
COMMA : ',';
DOT : '.';

// 括号
LPAREN : '(';
RPAREN : ')';
LBRACKET : '[';
RBRACKET : ']';
LBRACE : '{';
RBRACE : '}';

// 特殊字符
AT_SIGN : '@';
HASH : '#';
DOLLAR : '$';
PERCENT : '%';
CARET : '^';
AMPERSAND : '&';
STAR : '*';
PLUS : '+';
MINUS : '-';
SLASH : '/';
BACKSLASH : '\\';
PIPE : '|';
TILDE : '~';
EXCLAMATION : '!';
QUESTION : '?';
LT : '<';
GT : '>';

// 其他特殊字符
SPECIAL_CHAR
    : ~[\p{L}\p{N}\s"'`(){}\[\]=:;,.\-@#$%^&*+/\\|~!?<>]+
    ;

// 注释
COMMENT
    : '/*' .*? '*/' -> skip
    ;

LINE_COMMENT
    : '//' ~[\r\n]* -> skip
    ;

// 空白
WHITESPACE
    : [ \t\r\n]+ -> skip
    ;

// 转义序列
fragment EscapeSequence
    : '\\' [btnfr"'\\]
    | '\\' ([0-3]? [0-7])? [0-7]
    | '\\' 'u'+ HEX HEX HEX HEX
    ;

fragment INT : [0-9]+;
fragment HEX : [0-9a-fA-F];
fragment BIN : [01];