grammar CHTL;

// 程序入口
program
    : topLevelStatement* EOF
    ;

// 顶层语句
topLevelStatement
    : configurationBlock
    | namespaceDeclaration
    | importStatement
    | templateDeclaration
    | customDeclaration
    | originBlock
    | htmlElement
    | styleBlock
    | scriptBlock
    | comment
    ;

// 配置块
configurationBlock
    : '[Configuration]' '{' configurationItem* '}'
    ;

configurationItem
    : configKey '=' configValue ';'
    | '[Name]' '{' nameConfigItem* '}'
    ;

configKey
    : IDENTIFIER
    ;

configValue
    : STRING_LITERAL
    | NUMBER
    | BOOLEAN
    | configValueArray
    ;

configValueArray
    : '[' configArrayItem (',' configArrayItem)* ']'
    ;

configArrayItem
    : '@' IDENTIFIER
    | STRING_LITERAL
    ;

nameConfigItem
    : IDENTIFIER '=' (configValue | configValueArray) ';'
    ;

// 命名空间
namespaceDeclaration
    : '[Namespace]' IDENTIFIER namespaceBody?
    ;

namespaceBody
    : '{' namespaceContent* '}'
    ;

namespaceContent
    : namespaceDeclaration
    | templateDeclaration
    | customDeclaration
    | exceptConstraint
    ;

// 导入语句
importStatement
    : '[Import]' importType 'from' importPath ('as' IDENTIFIER)? ';'?
    ;

importType
    : '@Html'
    | '@Style'
    | '@JavaScript'
    | '@Chtl'
    | '[Custom]' customType IDENTIFIER
    | '[Template]' templateType IDENTIFIER
    ;

importPath
    : STRING_LITERAL
    | dottedPath
    ;

dottedPath
    : IDENTIFIER ('.' IDENTIFIER)*
    ;

// 模板声明
templateDeclaration
    : '[Template]' templateType IDENTIFIER templateBody
    ;

templateType
    : '@Style'
    | '@Element'
    | '@Var'
    ;

templateBody
    : '{' templateContent* '}'
    ;

templateContent
    : styleProperty
    | htmlElement
    | templateInheritance
    | variableDefinition
    ;

templateInheritance
    : templateType IDENTIFIER ';'
    | 'inherit' templateType IDENTIFIER ';'
    ;

// 自定义声明
customDeclaration
    : '[Custom]' customType IDENTIFIER customBody
    ;

customType
    : '@Style'
    | '@Element'
    | '@Var'
    ;

customBody
    : '{' customContent* '}'
    ;

customContent
    : styleProperty
    | htmlElement
    | customInheritance
    | variableDefinition
    | deleteStatement
    | insertStatement
    ;

customInheritance
    : customType IDENTIFIER customSpecialization? ';'?
    | templateType IDENTIFIER customSpecialization? ';'?
    ;

customSpecialization
    : '{' specializationContent* '}'
    ;

specializationContent
    : styleProperty
    | deleteStatement
    | variableAssignment
    ;

// 删除语句
deleteStatement
    : 'delete' deleteTarget (',' deleteTarget)* ';'
    ;

deleteTarget
    : IDENTIFIER
    | IDENTIFIER '[' NUMBER ']'
    | customType IDENTIFIER
    | templateType IDENTIFIER
    ;

// 插入语句
insertStatement
    : 'insert' insertPosition elementSelector '{' insertContent* '}'
    ;

insertPosition
    : 'after'
    | 'before'
    | 'replace'
    | 'at' 'top'
    | 'at' 'bottom'
    ;

elementSelector
    : IDENTIFIER ('[' NUMBER ']')?
    ;

insertContent
    : htmlElement
    | elementUsage
    ;

// 原始嵌入块
originBlock
    : '[Origin]' originType IDENTIFIER? '{' originContent '}'
    ;

originType
    : '@Html'
    | '@Style'
    | '@JavaScript'
    ;

originContent
    : (~'}')*
    ;

// HTML元素
htmlElement
    : elementName elementIndexAccess? elementBody
    | globalStyleElement  // 添加全局样式元素
    ;

// 全局样式元素（用于head中的style标签）
globalStyleElement
    : 'style' '{' globalStyleContent '}'
    ;

// 全局样式内容（原生CSS）
globalStyleContent
    : (~'}')*  // 匹配任何非}字符，保留原始CSS内容
    ;

elementName
    : IDENTIFIER
    | 'text'
    | 'style'
    | 'script'
    ;

elementIndexAccess
    : '[' NUMBER ']'
    ;

elementBody
    : '{' elementContent* '}'
    ;

elementContent
    : attribute
    | htmlElement
    | styleBlock
    | scriptBlock
    | textContent
    | elementUsage
    | exceptConstraint
    | comment
    ;

// 属性
attribute
    : attributeName ':' attributeValue ';'
    | attributeName '=' attributeValue ';'
    ;

attributeName
    : IDENTIFIER
    ;

attributeValue
    : STRING_LITERAL
    | UNQUOTED_LITERAL
    | variableUsage
    ;

// 文本内容
textContent
    : STRING_LITERAL
    | UNQUOTED_LITERAL
    ;

// 样式块
styleBlock
    : 'style' '{' styleContent* '}'
    ;

styleContent
    : styleProperty
    | cssSelector '{' styleContent* '}'
    | styleUsage
    ;

styleProperty
    : propertyName ':' propertyValue ';'
    | propertyName ','  // 无值属性
    | propertyName ';'
    ;

propertyName
    : IDENTIFIER ('-' IDENTIFIER)*
    ;

propertyValue
    : STRING_LITERAL
    | UNQUOTED_LITERAL
    | variableUsage
    | cssFunction
    ;

cssSelector
    : '.' IDENTIFIER     // 类选择器
    | '#' IDENTIFIER     // ID选择器
    | '&' pseudoClass    // 伪类选择器
    | '&' pseudoElement  // 伪元素选择器
    | '&'                // 上下文推导
    ;

pseudoClass
    : ':' IDENTIFIER
    ;

pseudoElement
    : '::' IDENTIFIER
    ;

cssFunction
    : IDENTIFIER '(' cssArguments? ')'
    ;

cssArguments
    : cssArgument (',' cssArgument)*
    ;

cssArgument
    : propertyValue
    ;

// 脚本块
scriptBlock
    : 'script' '{' scriptContent '}'
    ;

scriptContent
    : (~'}')+  // 至少匹配一个字符，避免空匹配
    |  // 允许空脚本块
    ;

// 元素使用
elementUsage
    : customType IDENTIFIER elementSpecialization? ('from' namespacePath)? ';'
    | templateType IDENTIFIER elementSpecialization? ('from' namespacePath)? ';'
    | '[Custom]' customType IDENTIFIER elementSpecialization? ('from' namespacePath)? ';'
    | '[Template]' templateType IDENTIFIER elementSpecialization? ('from' namespacePath)? ';'
    | '[Origin]' originType IDENTIFIER ';'
    ;

elementSpecialization
    : '{' elementSpecializationContent* '}'
    ;

elementSpecializationContent
    : htmlElement
    | styleBlock
    | deleteStatement
    | insertStatement
    ;

// 样式使用
styleUsage
    : customType IDENTIFIER styleSpecialization? ';'
    | templateType IDENTIFIER styleSpecialization? ';'
    ;

styleSpecialization
    : '{' styleProperty* '}'
    ;

// 变量定义
variableDefinition
    : IDENTIFIER ':' STRING_LITERAL ';'
    ;

// 变量使用
variableUsage
    : IDENTIFIER '(' variableArguments? ')'
    ;

variableArguments
    : variableArgument (',' variableArgument)*
    ;

variableArgument
    : IDENTIFIER '=' propertyValue
    | IDENTIFIER
    ;

// 变量赋值
variableAssignment
    : IDENTIFIER '=' propertyValue ';'
    ;

// 命名空间路径
namespacePath
    : IDENTIFIER ('.' IDENTIFIER)*
    ;

// 约束
exceptConstraint
    : 'except' exceptTarget (',' exceptTarget)* ';'
    ;

exceptTarget
    : IDENTIFIER
    | customType IDENTIFIER
    | templateType IDENTIFIER
    | '[Custom]' customType?
    | '[Template]' templateType?
    | '@Html'
    ;

// 注释
comment
    : SINGLE_LINE_COMMENT
    | MULTI_LINE_COMMENT
    | GENERATOR_COMMENT
    ;

// 词法规则
SINGLE_LINE_COMMENT : '//' ~[\r\n]* -> channel(HIDDEN);
MULTI_LINE_COMMENT : '/*' .*? '*/' -> channel(HIDDEN);
GENERATOR_COMMENT : '--' ~[\r\n]*;

BOOLEAN : 'true' | 'false';
NUMBER : [0-9]+ ('.' [0-9]+)?;
STRING_LITERAL : '"' (~["\r\n] | '\\"')* '"' | '\'' (~['\r\n] | '\\\'')* '\'';
UNQUOTED_LITERAL : [a-zA-Z0-9_#]+ ([a-zA-Z0-9_\-#:()]* [a-zA-Z0-9_#])?;
IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]*;

WS : [ \t\r\n]+ -> skip;