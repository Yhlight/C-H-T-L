grammar CHTLJavaScript;

import JavaScript;

// 重写表达式以支持CHTL扩展
singleExpression
    : chtlSelector                                                             // CHTL选择器
    | singleExpression CHTL_ARROW identifierName                             // CHTL箭头访问
    | singleExpression CHTL_ARROW identifierName arguments                   // CHTL箭头调用
    | singleExpression CHTL_ARROW LISTEN LPAREN listenObject RPAREN         // 增强监听器
    | singleExpression CHTL_ARROW DELEGATE LPAREN delegateObject RPAREN     // 事件委托
    | animateCall                                                             // 动画调用
    | anonymousFunction
    | arrowFunction
    | singleExpression LBRACKET expressionSequence RBRACKET                    
    | singleExpression DOT identifierName                                      
    | singleExpression arguments                                               
    | NEW singleExpression arguments?                                          
    | singleExpression PLUSPLUS                                                
    | singleExpression MINUSMINUS                                              
    | DELETE singleExpression                                                  
    | VOID singleExpression                                                    
    | TYPEOF singleExpression                                                  
    | PLUSPLUS singleExpression                                                
    | MINUSMINUS singleExpression                                              
    | PLUS singleExpression                                                    
    | MINUS singleExpression                                                   
    | TILDE singleExpression                                                   
    | EXCLAMATION singleExpression                                             
    | AWAIT singleExpression                                                   
    | singleExpression POWER singleExpression                                  
    | singleExpression (STAR | SLASH | PERCENT) singleExpression             
    | singleExpression (PLUS | MINUS) singleExpression                       
    | singleExpression (LSHIFT | RSHIFT | URSHIFT) singleExpression         
    | singleExpression (LT | GT | LE | GE) singleExpression                 
    | singleExpression INSTANCEOF singleExpression                            
    | singleExpression IN singleExpression                                    
    | singleExpression (EQUALS_OP | NOT_EQUALS | STRICT_EQUALS | STRICT_NOT_EQUALS) singleExpression  
    | singleExpression AMPERSAND singleExpression                             
    | singleExpression CARET singleExpression                                 
    | singleExpression PIPE singleExpression                                  
    | singleExpression AND_OP singleExpression                                
    | singleExpression OR_OP singleExpression                                 
    | singleExpression NULLISH_COALESCING singleExpression                   
    | singleExpression QUESTION singleExpression COLON singleExpression      
    | singleExpression EQUALS singleExpression                                
    | singleExpression assignmentOperator singleExpression                    
    | singleExpression templateStringLiteral                                  
    | THIS                                                                    
    | IDENTIFIER                                                              
    | SUPER                                                                   
    | literal                                                                 
    | arrayLiteral                                                            
    | objectLiteral                                                           
    | LPAREN expressionSequence RPAREN                                        
    | typeofExpression                                                        
    ;

// CHTL选择器
chtlSelector: CHTL_SELECTOR_START chtlSelectorContent CHTL_SELECTOR_END;

chtlSelectorContent
    : IDENTIFIER                           // {{box}} - 类名或id
    | DOT IDENTIFIER                       // {{.box}} - 类名
    | HASH IDENTIFIER                      // {{#box}} - id
    | IDENTIFIER LBRACKET NUMBER RBRACKET  // {{button[0]}} - 索引访问
    | cssSelector                          // 复杂CSS选择器
    ;

cssSelector: cssSelectorPart+;

cssSelectorPart
    : IDENTIFIER
    | DOT IDENTIFIER
    | HASH IDENTIFIER
    | LBRACKET NUMBER RBRACKET
    | SPACE
    ;

// 增强监听器对象
listenObject: LBRACE eventBinding (COMMA eventBinding)* RBRACE;

eventBinding: IDENTIFIER COLON (singleExpression | IDENTIFIER);

// 事件委托对象
delegateObject: LBRACE delegateProperty (COMMA delegateProperty)* RBRACE;

delegateProperty
    : TARGET COLON (chtlSelector | selectorArray)     // target属性
    | IDENTIFIER COLON singleExpression                // 事件处理器
    ;

selectorArray: LBRACKET chtlSelector (COMMA chtlSelector)* RBRACKET;

// 动画调用
animateCall: ANIMATE LPAREN animateObject RPAREN;

animateObject: LBRACE animateProperty (COMMA animateProperty)* RBRACE;

animateProperty
    : DURATION COLON NUMBER                            // 持续时间
    | EASING COLON (IDENTIFIER | STRING)               // 缓动函数
    | BEGIN_PROP COLON cssObject                       // 起始状态
    | END_PROP COLON cssObject                         // 结束状态
    | WHEN COLON whenArray                             // when数组
    | LOOP COLON NUMBER                                // 循环次数
    | DIRECTION COLON (IDENTIFIER | STRING)            // 播放方向
    | DELAY COLON NUMBER                               // 延迟
    | CALLBACK COLON (singleExpression | IDENTIFIER)   // 回调函数
    ;

cssObject: LBRACE cssProperty (COMMA cssProperty)* RBRACE;

cssProperty: IDENTIFIER COLON (STRING | NUMBER | singleExpression);

whenArray: LBRACKET whenObject (COMMA whenObject)* RBRACKET;

whenObject: LBRACE whenProperty (COMMA whenProperty)* RBRACE;

whenProperty
    : AT COLON NUMBER                                  // at时间点
    | IDENTIFIER COLON (STRING | NUMBER | singleExpression)  // CSS属性
    ;

// 新增词法规则
CHTL_ARROW: '->';
CHTL_SELECTOR_START: '{{';
CHTL_SELECTOR_END: '}}';
LISTEN: 'listen';
DELEGATE: 'delegate';
TARGET: 'target';
ANIMATE: 'animate';
DURATION: 'duration';
EASING: 'easing';
BEGIN_PROP: 'begin';
END_PROP: 'end';
WHEN: 'when';
LOOP: 'loop';
DIRECTION: 'direction';
DELAY: 'delay';
CALLBACK: 'callback';