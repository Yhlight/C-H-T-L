
// Generated from grammars/chtljs/CHTLJS.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  CHTLJSLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, MULTILINE_COMMENT = 3, CHTL_SCRIPT = 4, CHTL_LISTEN = 5, 
    CHTL_DELEGATE = 6, CHTL_ANIMATE = 7, CHTL_AT = 8, CHTL_WHEN = 9, CHTL_BEGIN = 10, 
    CHTL_END = 11, CHTL_LOOP = 12, CHTL_DIRECTION = 13, CHTL_DELAY = 14, 
    CHTL_CALLBACK = 15, CHTL_TARGET = 16, CHTL_EASING = 17, CHTL_DURATION = 18, 
    FUNCTION = 19, VAR = 20, LET = 21, CONST = 22, IF = 23, ELSE = 24, FOR = 25, 
    WHILE = 26, DO = 27, SWITCH = 28, CASE = 29, DEFAULT = 30, BREAK = 31, 
    CONTINUE = 32, RETURN = 33, TRY = 34, CATCH = 35, FINALLY = 36, THROW = 37, 
    NEW = 38, THIS = 39, SUPER = 40, CLASS = 41, EXTENDS = 42, STATIC = 43, 
    ASYNC = 44, AWAIT = 45, YIELD = 46, GET = 47, SET = 48, IMPORT = 49, 
    EXPORT = 50, FROM = 51, AS = 52, OF = 53, IN = 54, INSTANCEOF = 55, 
    TYPEOF = 56, DELETE = 57, VOID = 58, WITH = 59, DEBUGGER = 60, NULL_TOKEN = 61, 
    TRUE = 62, FALSE = 63, NUMBER = 64, STRING = 65, REGEX = 66, REGEX_BODY = 67, 
    REGEX_FLAGS = 68, IDENTIFIER = 69, LBRACE = 70, RBRACE = 71, LPAREN = 72, 
    RPAREN = 73, LBRACKET = 74, RBRACKET = 75, SEMICOLON = 76, COLON = 77, 
    EQUALS = 78, ASSIGN = 79, MINUS = 80, PLUS = 81, MUL = 82, DIV = 83, 
    MOD = 84, POWER = 85, GT = 86, LT = 87, GE = 88, LE = 89, EQUAL = 90, 
    NOTEQUAL = 91, AND = 92, OR = 93, BANG = 94, TILDE = 95, QUESTION = 96, 
    INC = 97, DEC = 98, ADD_ASSIGN = 99, SUB_ASSIGN = 100, MUL_ASSIGN = 101, 
    DIV_ASSIGN = 102, MOD_ASSIGN = 103, POWER_ASSIGN = 104, LSHIFT = 105, 
    RSHIFT = 106, URSHIFT = 107, LSHIFT_ASSIGN = 108, RSHIFT_ASSIGN = 109, 
    URSHIFT_ASSIGN = 110, BITAND = 111, BITOR = 112, CARET = 113, AND_ASSIGN = 114, 
    OR_ASSIGN = 115, XOR_ASSIGN = 116, ELLIPSIS = 117, ARROW = 118, CHTL_DOUBLE_BRACE = 119, 
    CHTL_DOUBLE_BRACE_CLOSE = 120, CHTL_ARROW = 121, LITERAL = 122, HASH = 123, 
    DOT = 124, COMMA = 125
  };

  explicit CHTLJSLexer(antlr4::CharStream *input);
  ~CHTLJSLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual antlr4::atn::SerializedATNView getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

