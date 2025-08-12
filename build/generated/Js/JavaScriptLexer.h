
// Generated from /workspace/grammar/JavaScript.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  JavaScriptLexer : public antlr4::Lexer {
public:
  enum {
    BREAK = 1, DO = 2, INSTANCEOF = 3, TYPEOF = 4, CASE = 5, ELSE = 6, NEW = 7, 
    VAR = 8, CATCH = 9, FINALLY = 10, RETURN = 11, VOID = 12, CONTINUE = 13, 
    FOR = 14, SWITCH = 15, WHILE = 16, DEBUGGER = 17, FUNCTION = 18, THIS = 19, 
    WITH = 20, DEFAULT = 21, IF = 22, THROW = 23, DELETE = 24, IN = 25, 
    TRY = 26, CLASS = 27, ENUM = 28, EXTENDS = 29, SUPER = 30, CONST = 31, 
    EXPORT = 32, IMPORT = 33, ASYNC = 34, AWAIT = 35, YIELD = 36, LET = 37, 
    STATIC = 38, FROM = 39, AS = 40, OF = 41, GET = 42, SET = 43, NULL_ = 44, 
    BOOLEAN = 45, UNDEFINED = 46, LPAREN = 47, RPAREN = 48, LBRACE = 49, 
    RBRACE = 50, LBRACKET = 51, RBRACKET = 52, SEMICOLON = 53, COMMA = 54, 
    DOT = 55, QUESTION = 56, COLON = 57, ELLIPSIS = 58, EQUALS = 59, STAR_EQUALS = 60, 
    SLASH_EQUALS = 61, PERCENT_EQUALS = 62, PLUS_EQUALS = 63, MINUS_EQUALS = 64, 
    LSHIFT_EQUALS = 65, RSHIFT_EQUALS = 66, URSHIFT_EQUALS = 67, AMPERSAND_EQUALS = 68, 
    CARET_EQUALS = 69, PIPE_EQUALS = 70, POWER_EQUALS = 71, NULLISH_EQUALS = 72, 
    ARROW = 73, PLUSPLUS = 74, MINUSMINUS = 75, PLUS = 76, MINUS = 77, TILDE = 78, 
    EXCLAMATION = 79, STAR = 80, SLASH = 81, PERCENT = 82, POWER = 83, NULLISH_COALESCING = 84, 
    LSHIFT = 85, RSHIFT = 86, URSHIFT = 87, LT = 88, GT = 89, LE = 90, GE = 91, 
    EQUALS_OP = 92, NOT_EQUALS = 93, STRICT_EQUALS = 94, STRICT_NOT_EQUALS = 95, 
    AMPERSAND = 96, CARET = 97, PIPE = 98, AND_OP = 99, OR_OP = 100, NUMBER = 101, 
    BIGINT = 102, STRING = 103, BACKTICK = 104, TEMPLATE_STRING = 105, REGEX = 106, 
    IDENTIFIER = 107, LINE_COMMENT = 108, BLOCK_COMMENT = 109, WS = 110
  };

  explicit JavaScriptLexer(antlr4::CharStream *input);

  ~JavaScriptLexer() override;


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

