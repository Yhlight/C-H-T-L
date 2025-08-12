
// Generated from /workspace/grammar/CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CSSLexer : public antlr4::Lexer {
public:
  enum {
    CHARSET = 1, IMPORT = 2, NAMESPACE = 3, MEDIA = 4, PAGE = 5, FONT_FACE = 6, 
    KEYFRAMES = 7, SUPPORTS = 8, ONLY = 9, NOT = 10, AND = 11, OR = 12, 
    FROM = 13, TO = 14, IMPORTANT = 15, LPAREN = 16, RPAREN = 17, LBRACE = 18, 
    RBRACE = 19, LBRACKET = 20, RBRACKET = 21, COLON = 22, SEMICOLON = 23, 
    COMMA = 24, DOT = 25, HASH = 26, PLUS = 27, MINUS = 28, GREATER = 29, 
    TILDE = 30, STAR = 31, PIPE = 32, SLASH = 33, EQUALS = 34, INCLUDES = 35, 
    DASHMATCH = 36, PREFIXMATCH = 37, SUFFIXMATCH = 38, SUBSTRINGMATCH = 39, 
    LENGTH = 40, EMS = 41, EXS = 42, ANGLE = 43, TIME = 44, FREQ = 45, PERCENTAGE = 46, 
    FUNCTION = 47, URL = 48, NUMBER = 49, STRING = 50, IDENT = 51, HEXDIGIT = 52, 
    COMMENT = 53, SPACE = 54, ANY = 55
  };

  explicit CSSLexer(antlr4::CharStream *input);

  ~CSSLexer() override;


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

