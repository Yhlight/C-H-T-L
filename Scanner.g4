grammar Scanner;

// 扫描器主入口
document
    : codeBlock* EOF
    ;

// 代码块类型
codeBlock
    : chtlBlock
    | cssBlock
    | jsBlock
    | chtlJsBlock
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
    | 'text' '{'
    ;

elementEnd
    : '}'
    ;

elementContent
    : chtlAttribute
    | nestedElement
    | styleBlockMarker
    | scriptBlockMarker
    | textContent
    ;

// CHTL属性
chtlAttribute
    : IDENTIFIER (':' | '=') attributeValue ';'
    ;

attributeValue
    : ~[;]+
    ;

// 嵌套元素
nestedElement
    : chtlElement
    ;

// 样式块标记
styleBlockMarker
    : 'style' '{' { pushMode(CSS_MODE); }
    ;

// 脚本块标记
scriptBlockMarker
    : 'script' '{' { pushMode(SCRIPT_MODE); }
    ;

// CHTL声明
chtlDeclaration
    : templateDeclaration
    | customDeclaration
    | configurationBlock
    | namespaceDeclaration
    ;

templateDeclaration
    : '[Template]' ~'}'+ '}'
    ;

customDeclaration
    : '[Custom]' ~'}'+ '}'
    ;

configurationBlock
    : '[Configuration]' ~'}'+ '}'
    ;

namespaceDeclaration
    : '[Namespace]' ~'}'+ '}'
    ;

// CHTL语句
chtlStatement
    : importStatement
    | originBlock
    ;

importStatement
    : '[Import]' ~[;\n]+ ';'?
    ;

originBlock
    : originHtmlBlock
    | originStyleBlock
    | originJsBlock
    ;

originHtmlBlock
    : '[Origin]' '@Html' IDENTIFIER? '{' { pushMode(HTML_MODE); }
    ;

originStyleBlock
    : '[Origin]' '@Style' IDENTIFIER? '{' { pushMode(CSS_MODE); }
    ;

originJsBlock
    : '[Origin]' '@JavaScript' IDENTIFIER? '{' { pushMode(JS_MODE); }
    ;

// CSS代码块（在CSS模式下）
cssBlock
    : cssContent
    ;

cssContent
    : ~'}'*
    ;

// JS代码块（在JS模式下）
jsBlock
    : jsContent
    ;

jsContent
    : ~'}'*
    ;

// CHTL JS代码块（在脚本块中检测CHTL扩展）
chtlJsBlock
    : chtlJsContent
    ;

chtlJsContent
    : (chtlSelector | normalJsCode)*
    ;

chtlSelector
    : '{{' ~'}}'* '}}'
    ;

normalJsCode
    : ~[{]+ 
    | '{' ~[{]
    ;

// 文本内容
textBlock
    : textContent
    ;

textContent
    : STRING_LITERAL
    | UNQUOTED_LITERAL
    ;

// 基础词法规则
IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]*;
STRING_LITERAL : '"' (~["\r\n] | '\\"')* '"' | '\'' (~['\r\n] | '\\\'')* '\'';
UNQUOTED_LITERAL : [a-zA-Z0-9_#]+ ([a-zA-Z0-9_\-#:()]* [a-zA-Z0-9_#])?;

WS : [ \t\r\n]+ -> skip;
COMMENT : '//' ~[\r\n]* -> skip;
MULTI_COMMENT : '/*' .*? '*/' -> skip;

// 模式定义
mode CSS_MODE;
CSS_CONTENT : ~'}'+ -> type(cssContent);
CSS_CLOSE : '}' -> popMode;

mode JS_MODE;
JS_CHTL_SELECTOR : '{{' ~'}}'* '}}' -> type(chtlSelector);
JS_CONTENT : ~[{}]+ -> type(jsContent);
JS_OPEN : '{' -> type(jsContent);
JS_CLOSE : '}' -> popMode;

mode HTML_MODE;
HTML_CONTENT : ~'}'+ -> type(textContent);
HTML_CLOSE : '}' -> popMode;

// 扫描器动作接口（伪代码）
@parser::members {
    // 编译器接口
    interface Compiler {
        void process(String code);
    }
    
    // 四个编译器实例
    private Compiler chtlCompiler;
    private Compiler cssCompiler;
    private Compiler jsCompiler;
    private Compiler chtlJsCompiler;
    
    // 代码分发方法
    private void dispatchToCompiler(CodeType type, String code) {
        switch(type) {
            case CHTL:
                chtlCompiler.process(code);
                break;
            case CSS:
                cssCompiler.process(code);
                break;
            case JS:
                jsCompiler.process(code);
                break;
            case CHTL_JS:
                chtlJsCompiler.process(code);
                break;
        }
    }
    
    // 代码类型枚举
    enum CodeType {
        CHTL, CSS, JS, CHTL_JS
    }
    
    // 检测JavaScript代码是否包含CHTL扩展
    private boolean hasCHTLExtensions(String jsCode) {
        return jsCode.contains("{{") || 
               jsCode.contains("->") || 
               jsCode.contains("listen") ||
               jsCode.contains("delegate") ||
               jsCode.contains("animate");
    }
}