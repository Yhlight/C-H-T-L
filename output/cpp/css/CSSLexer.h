
// Generated from CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CSSLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, COMMENT = 31, IMPORT = 32, 
    MEDIA = 33, KEYFRAMES = 34, FONT_FACE = 35, SUPPORTS = 36, PAGE = 37, 
    NAMESPACE = 38, CHARSET = 39, VIEWPORT = 40, COUNTER_STYLE = 41, FONT_FEATURE_VALUES = 42, 
    PROPERTY = 43, ONLY = 44, NOT = 45, AND = 46, OR = 47, FROM = 48, TO = 49, 
    IMPORTANT = 50, PX = 51, EM = 52, REM = 53, VH = 54, VW = 55, VMIN = 56, 
    VMAX = 57, CH = 58, EX = 59, CM = 60, MM = 61, IN = 62, PT = 63, PC = 64, 
    DEG = 65, RAD = 66, GRAD = 67, TURN = 68, S = 69, MS = 70, HZ = 71, 
    KHZ = 72, DPI = 73, DPCM = 74, DPPX = 75, VARIABLE = 76, NUMBER = 77, 
    STRING_LITERAL = 78, URI = 79, IDENTIFIER = 80, HEX_DIGIT = 81, WS = 82
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

