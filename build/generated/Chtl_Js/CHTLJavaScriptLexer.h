
// Generated from /workspace/grammar/CHTLJavaScript.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"




class  CHTLJavaScriptLexer : public antlr4::Lexer {
public:
  enum {
    CHTL_ARROW = 1, CHTL_SELECTOR_START = 2, CHTL_SELECTOR_END = 3, HASH = 4, 
    AT = 5, SPACE = 6, LISTEN = 7, DELEGATE = 8, TARGET = 9, ANIMATE = 10, 
    DURATION = 11, EASING = 12, BEGIN_PROP = 13, END_PROP = 14, WHEN = 15, 
    LOOP = 16, DIRECTION = 17, DELAY = 18, CALLBACK = 19, BACKTICK = 20, 
    TEMPLATE_STRING = 21, REGEX = 22, IDENTIFIER = 23, LINE_COMMENT = 24, 
    BLOCK_COMMENT = 25, WS = 26, BREAK = 27, DO = 28, INSTANCEOF = 29, TYPEOF = 30, 
    CASE = 31, ELSE = 32, NEW = 33, VAR = 34, CATCH = 35, FINALLY = 36, 
    RETURN = 37, VOID = 38, CONTINUE = 39, FOR = 40, SWITCH = 41, WHILE = 42, 
    DEBUGGER = 43, FUNCTION = 44, THIS = 45, WITH = 46, DEFAULT = 47, IF = 48, 
    THROW = 49, DELETE = 50, IN = 51, TRY = 52, CLASS = 53, ENUM = 54, EXTENDS = 55, 
    SUPER = 56, CONST = 57, EXPORT = 58, IMPORT = 59, ASYNC = 60, AWAIT = 61, 
    YIELD = 62, LET = 63, STATIC = 64, FROM = 65, AS = 66, OF = 67, GET = 68, 
    SET = 69, NULL_LITERAL = 70, BOOLEAN = 71, UNDEFINED = 72, LPAREN = 73, 
    RPAREN = 74, LBRACE = 75, RBRACE = 76, LBRACKET = 77, RBRACKET = 78, 
    SEMICOLON = 79, COMMA = 80, DOT = 81, QUESTION = 82, COLON = 83, ELLIPSIS = 84, 
    EQUALS = 85, STAR_EQUALS = 86, SLASH_EQUALS = 87, PERCENT_EQUALS = 88, 
    PLUS_EQUALS = 89, MINUS_EQUALS = 90, LSHIFT_EQUALS = 91, RSHIFT_EQUALS = 92, 
    URSHIFT_EQUALS = 93, AMPERSAND_EQUALS = 94, CARET_EQUALS = 95, PIPE_EQUALS = 96, 
    POWER_EQUALS = 97, NULLISH_EQUALS = 98, ARROW = 99, PLUSPLUS = 100, 
    MINUSMINUS = 101, PLUS = 102, MINUS = 103, TILDE = 104, EXCLAMATION = 105, 
    STAR = 106, SLASH = 107, PERCENT = 108, POWER = 109, NULLISH_COALESCING = 110, 
    LSHIFT = 111, RSHIFT = 112, URSHIFT = 113, LT = 114, GT = 115, LE = 116, 
    GE = 117, EQUALS_OP = 118, NOT_EQUALS = 119, STRICT_EQUALS = 120, STRICT_NOT_EQUALS = 121, 
    AMPERSAND = 122, CARET = 123, PIPE = 124, AND_OP = 125, OR_OP = 126, 
    NUMBER = 127, BIGINT = 128, STRING = 129
  };

  explicit CHTLJavaScriptLexer(antlr4::CharStream *input);

  ~CHTLJavaScriptLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

