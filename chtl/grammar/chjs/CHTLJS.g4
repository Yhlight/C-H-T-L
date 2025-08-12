grammar CHTLJS;

program: piece* EOF;

piece
  : moustache
  | arrowUse
  | keywordUse
  | OTHER
  ;

moustache
  : LBRACE2 selector RBRACE2
  ;

arrowUse
  : moustache ARROW IDENT (LPAREN argChunk* RPAREN)?
  ;

keywordUse
  : (LISTEN|DELEGATE|ANIMATE) LPAREN argChunk* RPAREN
  ;

selector
  : simpleSelector (WS? simpleSelector)*
  ;

simpleSelector
  : HASH IDENT (LBRACK NUMBER RBRACK)?
  | DOT IDENT (WS IDENT)*
  | IDENT (LBRACK NUMBER RBRACK)?
  ;

argChunk
  : ARGCHUNK | LPAREN | RPAREN
  ;

LBRACE2: '{{';
RBRACE2: '}}';
ARROW: '->';

DOT: '.';
HASH: '#';
LBRACK: '[';
RBRACK: ']';
LPAREN: '(';
RPAREN: ')';
COMMA: ',';
SEMI: ';';
COLON: ':';

NUMBER: [0-9]+;
IDENT: [a-zA-Z_] [a-zA-Z0-9_-]*;

LISTEN: 'listen';
DELEGATE: 'delegate';
ANIMATE: 'animate';

ARGCHUNK: ~[()]+;

OTHER: .;

WS: [ \t\r\n]+ -> skip;