
// Generated from grammars/css/CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CSSLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, WS = 5, COMMENT = 6, SELECTOR = 7, 
    UNIT = 8, COLOR_KEYWORD = 9, FUNCTION = 10, PSEUDO_CLASS = 11, PSEUDO_ELEMENT = 12, 
    MEDIA_KEYWORD = 13, VALUE_KEYWORD = 14, IDENTIFIER = 15, NUMBER = 16, 
    STRING = 17, LBRACE = 18, RBRACE = 19, LPAREN = 20, RPAREN = 21, LBRACKET = 22, 
    RBRACKET = 23, SEMICOLON = 24, COLON = 25, COMMA = 26, DOT = 27, HASH = 28, 
    ASTERISK = 29, GREATER = 30, PLUS = 31, TILDE = 32, PIPE = 33, CARET = 34, 
    DOLLAR = 35, EQUALS = 36, EXCLAMATION = 37, PERCENT = 38, SLASH = 39, 
    INCLUDES = 40, DASHMATCH = 41, PREFIXMATCH = 42, SUFFIXMATCH = 43, SUBSTRINGMATCH = 44, 
    MINUS = 45, NOT = 46, URL = 47, HEX_CHAR = 48, U_PLUS = 49, QUESTION = 50, 
    MEDIA = 51, ONLY = 52, AND = 53, PAGE = 54, FONTFACE = 55, KEYFRAMES = 56, 
    FROM = 57, TO = 58, PERCENTAGE = 59, SUPPORTS = 60, OR = 61, DOCUMENT = 62, 
    URL_PREFIX = 63, DOMAIN = 64, REGEXP = 65, VIEWPORT = 66, COUNTER_STYLE = 67, 
    FONT_FEATURE_VALUES = 68, ATKEYWORD = 69
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

