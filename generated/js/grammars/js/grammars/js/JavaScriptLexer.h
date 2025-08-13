
// Generated from grammars/js/JavaScript.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  JavaScriptLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, WS = 2, COMMENT = 3, MULTILINE_COMMENT = 4, BREAK = 5, DO = 6, 
    INSTANCEOF = 7, TYPEOF = 8, CASE = 9, ELSE = 10, NEW = 11, VAR = 12, 
    CATCH = 13, FINALLY = 14, RETURN = 15, VOID = 16, CONTINUE = 17, FOR = 18, 
    SWITCH = 19, WHILE = 20, DEBUGGER = 21, FUNCTION = 22, THIS = 23, WITH = 24, 
    DEFAULT = 25, IF = 26, THROW = 27, DELETE = 28, IN = 29, TRY = 30, CLASS = 31, 
    ENUM = 32, EXTENDS = 33, SUPER = 34, CONST = 35, EXPORT = 36, IMPORT = 37, 
    LET = 38, STATIC = 39, YIELD = 40, IMPLEMENTS = 41, INTERFACE = 42, 
    PACKAGE = 43, PRIVATE = 44, PROTECTED = 45, PUBLIC = 46, ABSTRACT = 47, 
    BOOLEAN = 48, BYTE = 49, CHAR = 50, DOUBLE = 51, FINAL = 52, FLOAT = 53, 
    GOTO = 54, INT = 55, LONG = 56, NATIVE = 57, SHORT = 58, SYNCHRONIZED = 59, 
    THROWS = 60, TRANSIENT = 61, VOLATILE = 62, NULL = 63, TRUE = 64, FALSE = 65, 
    ARROW = 66, ASYNC = 67, AWAIT = 68, GET = 69, SET = 70, LITERAL = 71, 
    STRING = 72, NUMBER = 73, DECIMAL_LITERAL = 74, HEX_INTEGER_LITERAL = 75, 
    OCTAL_INTEGER_LITERAL = 76, BINARY_INTEGER_LITERAL = 77, EXPONENT_PART = 78, 
    REGEX = 79, REGEX_BODY = 80, REGEX_FLAGS = 81, IDENTIFIER = 82, LPAREN = 83, 
    RPAREN = 84, LBRACE = 85, RBRACE = 86, LBRACKET = 87, RBRACKET = 88, 
    SEMICOLON = 89, COLON = 90, COMMA = 91, DOT = 92, ASSIGN = 93, GT = 94, 
    LT = 95, BANG = 96, TILDE = 97, QUESTION = 98, INC = 99, DEC = 100, 
    ADD = 101, SUB = 102, MUL = 103, DIV = 104, MOD = 105, POWER = 106, 
    ADD_ASSIGN = 107, SUB_ASSIGN = 108, MUL_ASSIGN = 109, DIV_ASSIGN = 110, 
    MOD_ASSIGN = 111, POWER_ASSIGN = 112, LSHIFT = 113, RSHIFT = 114, URSHIFT = 115, 
    LSHIFT_ASSIGN = 116, RSHIFT_ASSIGN = 117, URSHIFT_ASSIGN = 118, BITAND = 119, 
    BITOR = 120, CARET = 121, AND_ASSIGN = 122, OR_ASSIGN = 123, XOR_ASSIGN = 124, 
    ELLIPSIS = 125, TEMPLATE_CHAR = 126, ASTERISK = 127, AS = 128, BACKTICK = 129, 
    OR = 130, AND = 131, EQUAL = 132, NOTEQUAL = 133, LE = 134, GE = 135
  };

  explicit JavaScriptLexer(antlr4::CharStream *input);
  ~JavaScriptLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
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

